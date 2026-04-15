/*------------------------------------------------------------------------------------------------*/
/* SPI Asynchronous Driver                                                                        */
/* Copyright 2020, Microchip Technology Inc. and its subsidiaries.                                */
/*                                                                                                */
/* Redistribution and use in source and binary forms, with or without                             */
/* modification, are permitted provided that the following conditions are met:                    */
/*                                                                                                */
/* 1. Redistributions of source code must retain the above copyright notice, this                 */
/*    list of conditions and the following disclaimer.                                            */
/*                                                                                                */
/* 2. Redistributions in binary form must reproduce the above copyright notice,                   */
/*    this list of conditions and the following disclaimer in the documentation                   */
/*    and/or other materials provided with the distribution.                                      */
/*                                                                                                */
/* 3. Neither the name of the copyright holder nor the names of its                               */
/*    contributors may be used to endorse or promote products derived from                        */
/*    this software without specific prior written permission.                                    */
/*                                                                                                */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"                    */
/* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE                      */
/* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                 */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE                   */
/* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL                     */
/* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR                     */
/* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER                     */
/* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,                  */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE                  */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/*------------------------------------------------------------------------------------------------*/
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <ASSERT.h>
#include "definitions.h"
#include "spidrv-queue.h"
#include "spi_async_driver.h"

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                          USER ADJUSTABLE                             */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

#define SPI_TRACE               (false)
#define DRV_MAX_QUEUE_ENTRIES   (1)
#define DEFAULT_SPI_SPEED       (15000000)
#define ASSERT(x)               __conditional_software_breakpoint(x)

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                      DEFINES AND LOCAL VARIABLES                     */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/


#ifdef QGEN_
$ {

#include <stdint.h>
#include <stdbool.h>
#include <spi_async_driver.h>

struct SpiDrvEntry {
    SpiDrvAsync_TransferCB_t pCallback;
    uint8_t txBufferStatic[DRV_NON_ZERO_CPY_BUF_SIZE];
    uint8_t rxBufferStatic[DRV_NON_ZERO_CPY_BUF_SIZE];
    const uint8_t *txBuffer;
    uint8_t *rxBuffer;
    void *tag;
    DRV_SPI_TRANSFER_EVENT event;
    uint32_t gpioMask;
    uint16_t length;
    uint8_t csInstance;
    bool useStatic;
    bool csDeASSERT;
};

$ generate_queue qspidrv "struct SpiDrvEntry" enqueue send interrupt event

$ } | mk_include "${D}/spidrv-queue.h" "SPIDRV_QUEUE_"
#endif

typedef struct
{
    DRV_SPI_TRANSFER_SETUP spiSetup[DRV_CS_MAX_INST];
    struct qspidrv_queue q;
    struct SpiDrvEntry q_buffer[DRV_MAX_QUEUE_ENTRIES];
    bool csActive[DRV_CS_MAX_INST];
    DRV_HANDLE handle;
    unsigned producer;
    unsigned consumer;
    uint8_t idx;
    uint8_t lastCsInstance;
    bool spiBusy;
    bool needService;
} SpiAsync_Local_t;

static SpiAsync_Local_t h[DRV_SPI_INSTANCES_NUMBER];
static bool h_init = false;

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                      PRIVATE FUNCTION PROTOTYPES                     */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

static void SetCustomGpio(uint8_t idx, uint32_t bitmask);
static void ChipSelect(uint8_t idx, uint8_t csInstance, bool active);
static bool IsChipSelectAvailable(uint8_t idx, uint8_t csInstance);
static void ChipSelect(uint8_t idx, uint8_t csInstance, bool active);
static bool StartSpiDma(uint8_t idx, uint8_t csInstance, const uint8_t *tx,
                        uint8_t *rx, uint16_t length);
static bool TrySendNext(uint8_t idx);
static void EventHandlerSPI(DRV_SPI_TRANSFER_EVENT event,
                            DRV_SPI_TRANSFER_HANDLE transferHandle,
                            uintptr_t context);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                         PUBLIC FUNCTIONS                             */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

void SpiDrvAsync_Init(void)
{
    uint8_t i, j;
    if (h_init)
        return; /* Avoid initializing multiple times */
    h_init = true;
    memset(&h, 0, sizeof(h));
    for (i = 0; i < DRV_SPI_INSTANCES_NUMBER; i++) {
        h[i].consumer = 0xCCCCCCCC;
        h[i].lastCsInstance = 0xFF;
        init_qspidrv_queue(&h[i].q, h[i].q_buffer, DRV_MAX_QUEUE_ENTRIES);
        h[i].handle = DRV_SPI_Open(i, DRV_IO_INTENT_EXCLUSIVE);
        ASSERT(h[i].handle != DRV_HANDLE_INVALID);
        DRV_SPI_TransferEventHandlerSet(h[i].handle, EventHandlerSPI, (uintptr_t)&h[i]);
        h[i].idx = i;

        for (j = 0; j < DRV_CS_MAX_INST; j++) {
            h[i].spiSetup[j].baudRateInHz = DEFAULT_SPI_SPEED;
            h[i].spiSetup[j].clockPhase = DRV_SPI_CLOCK_PHASE_VALID_LEADING_EDGE;
            h[i].spiSetup[j].clockPolarity = DRV_SPI_CLOCK_POLARITY_IDLE_LOW;
            h[i].spiSetup[j].dataBits = DRV_SPI_DATA_BITS_8;
            h[i].spiSetup[j].chipSelect = SYS_PORT_PIN_NONE;
            h[i].spiSetup[j].csPolarity = DRV_SPI_CS_POLARITY_ACTIVE_LOW;
        }
    }
}

bool SpiDrvAsync_TransferReady(uint8_t idx)
{
    if (idx >= DRV_SPI_INSTANCES_NUMBER) {
        ASSERT(false);
        return false;
    }
    return qspidrv_enqueue_ready(&h[idx].q);
}

bool SpiDrvAsync_Transfer(SpiDrvAsync_TransferParam_t *param)
{
    uint8_t idx;
    struct SpiDrvEntry *entry;
    if (!param) {
        ASSERT(false);
        return false;
    }
    idx = param->spiInstance;
    if (idx >= DRV_SPI_INSTANCES_NUMBER) {
        ASSERT(false);
        return false;
    }
    if (param->csInstance >= DRV_CS_MAX_INST) {
        ASSERT(false);
        return false;
    }
    if ((!param->zeroCopyTx || !param->zeroCopyRx) && param->bufSize > DRV_NON_ZERO_CPY_BUF_SIZE) {
        ASSERT(false);
        return false;
    }
    if (param->zeroCopyTx && !param->pTxBuf) {
        ASSERT(false);
        return false;
    }
    if (param->zeroCopyRx && !param->pRxBuf) {
        ASSERT(false);
        return false;
    }
    if (!qspidrv_enqueue_ready(&h[idx].q))
        return false;

    entry = qspidrv_enqueue_ptr(&h[idx].q);
    entry->csInstance = param->csInstance;
    entry->txBuffer = param->pTxBuf;
    entry->rxBuffer = param->pRxBuf;
    entry->length = param->bufSize;
    entry->gpioMask = param->gpioMask;
    entry->tag = param->tag;
    entry->pCallback = param->pCallback;
    entry->useStaticTx = !param->zeroCopyTx;
    entry->useStaticRx = !param->zeroCopyRx;
    if (entry->useStaticTx) {
        memcpy(entry->txBufferStatic, param->pTxBuf, param->bufSize);
    }

    qspidrv_enqueue_done(&h[idx].q);
    if (h[idx].consumer != h[idx].producer) {
        TrySendNext(idx);
    }

    return true;
}

void SpiDrvAsync_Service(void)
{
    uint8_t i;
    for (i = 0; i < DRV_SPI_INSTANCES_NUMBER; i++) {
        if (!h[i].needService)
            continue;
        h[i].needService = false;
        while (qspidrv_event_ready(&h[i].q)) {
            struct SpiDrvEntry *item = qspidrv_event_ptr(&h[i].q);
#if (SPI_TRACE)
            {
                uint16_t j;
                printf("MOSI(%d:%d) [ ", i, item->csInstance);
                for (j = 0; j < item->length; j++) {
                    printf("%02X ", (item->useStaticTx) ? item->txBufferStatic[j] : item->txBuffer[j]);
                }
                printf("]\r\nMISO      [ ");
                for (j = 0; j < item->length; j++) {
                    printf("%02X ", (item->useStaticRx) ? item->rxBufferStatic[j] : item->rxBuffer[j]);
                }
                printf("]:%dBytes\r\n\r\n", item->length);
            }
#endif
            if (item->pCallback) {
                item->pCallback(i, item->csInstance, (DRV_SPI_TRANSFER_EVENT_COMPLETE == item->event),
                    (item->useStaticTx) ? item->txBufferStatic : item->txBuffer,
                    (item->useStaticRx) ? item->rxBufferStatic : item->rxBuffer,
                    item->length, item->tag);
#ifdef DEBUG
                /* Try to raise errors if integrator try to keep item longer than this function call back */
                memset(item, 0xCC, sizeof(struct SpiDrvEntry));
#endif
            }
            qspidrv_event_done(&h[i].q);
        }
    }
}

bool SpiDrvAsync_SetSpiConfig(uint8_t idx, uint8_t csInstance, uint32_t speedHz, bool phaseValidLeadingEdge, bool polarityIdleLow)
{
    if (csInstance >= DRV_CS_MAX_INST)
        return false;
    if (speedHz == 0 || speedHz > 25000000)
        return false;
    h[idx].spiSetup[csInstance].baudRateInHz = speedHz;
    h[idx].spiSetup[csInstance].clockPhase = phaseValidLeadingEdge ? DRV_SPI_CLOCK_PHASE_VALID_LEADING_EDGE : DRV_SPI_CLOCK_PHASE_VALID_TRAILING_EDGE;
    h[idx].spiSetup[csInstance].clockPolarity = polarityIdleLow ? DRV_SPI_CLOCK_POLARITY_IDLE_LOW : DRV_SPI_CLOCK_POLARITY_IDLE_HIGH;
    return true;
}

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                  PRIVATE FUNCTION IMPLEMENTATIONS                    */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

static void SetCustomGpio(uint8_t idx, uint32_t bitmask)
{
    if (idx != DRV_SPI_INDEX_0)
        return;

    if (GPIO_BITMASK_OLED_DC & bitmask) {
        //GPIO_PWM2_Set();
        PORT_REGS->GROUP[0].PORT_OUTSET = 1 << 4;

    } else {
      // GPIO_PWM2_Clear();
        PORT_REGS->GROUP[0].PORT_OUTCLR = 1 << 4;
    }
}

static bool IsChipSelectAvailable(uint8_t idx, uint8_t csInstance)
{
    uint8_t i;
    for (i = 0; i < DRV_CS_MAX_INST; i++) {
        if (i != csInstance && h[idx].csActive[i]) {
            return false;
        }
    }
    return true;
}

static void ChipSelect(uint8_t idx, uint8_t csInstance, bool active)
{
    if (idx != DRV_SPI_INDEX_0)
        return;

    if (csInstance >= DRV_CS_MAX_INST) {
        ASSERT(false);
        return;
    }
    h[idx].csActive[csInstance] = active;
    if (active) {
        
        GPIO_CS1_Clear();
//        switch(csInstance) {
//        case 0:
//            GPIO_CS1_Clear();
//            break;
//        case 1:
//            GPIO_CS2_Clear();
//            break;
//        case 2:
//            GPIO_CS3_Clear();
//            break;
//        default:
//            ASSERT(false);
//            break;
//        }
    } else {
        
        GPIO_CS1_Set();
//        switch(csInstance) {
//        case 0:
//            GPIO_CS1_Set();
//            break;
//        case 1:
//            GPIO_CS2_Set();
//            break;
//        case 2:
//            GPIO_CS3_Set();
//            break;
//        default:
//            ASSERT(false);
//            break;
//        }
    }
}

static bool StartSpiDma(uint8_t idx, uint8_t csInstance, const uint8_t *tx,
                        uint8_t *rx, uint16_t length)
{
    DRV_SPI_TRANSFER_HANDLE transferHandle;
    h[idx].spiBusy = true;
    ChipSelect(idx, csInstance, true);
    if (csInstance != h[idx].lastCsInstance) {
        h[idx].lastCsInstance = csInstance;
        DRV_SPI_TransferSetup(h[idx].handle, &h[idx].spiSetup[csInstance]);
    }
    if (tx && rx) {
        DRV_SPI_WriteReadTransferAdd(h[idx].handle, (uint8_t *)tx, length, rx, length, &transferHandle);
    } else if (tx) {
        DRV_SPI_WriteTransferAdd(h[idx].handle, (uint8_t *)tx, length, &transferHandle);
    } else if (rx) {
        DRV_SPI_ReadTransferAdd(h[idx].handle, (uint8_t *)rx, length, &transferHandle);
    } else {
        ASSERT(false);
    }
    if (transferHandle == DRV_SPI_TRANSFER_HANDLE_INVALID) {
        h[idx].spiBusy = false;
        ChipSelect(idx, csInstance, false);
        return false;
    }
    return true;
}

static bool TrySendNext(uint8_t idx)
{
    bool started = false;

    while (!h[idx].spiBusy && qspidrv_send_ready(&h[idx].q)) {
        const uint8_t *tx;
        uint8_t *rx;
        struct SpiDrvEntry *item = qspidrv_send_ptr(&h[idx].q);
        if (!IsChipSelectAvailable(idx, item->csInstance)) {
            /* Another chip select is still active, we are not allowed to proceed */
            item->event = DRV_SPI_TRANSFER_EVENT_ERROR;
            qspidrv_send_done(&h[idx].q);
            qspidrv_interrupt_done(&h[idx].q);
            continue;
        }
        tx = item->useStaticTx ? item->txBufferStatic : item->txBuffer;
        rx = item->useStaticRx ? item->rxBufferStatic : item->rxBuffer;
        qspidrv_send_done(&h[idx].q);
        SetCustomGpio(idx, item->gpioMask);
        if(StartSpiDma(idx, item->csInstance, tx, rx, item->length)) {
            started = true;
        } else {
            qspidrv_send_undo(&h[idx].q);
        }
        break;
    }

    return started;
}

static void EventHandlerSPI(DRV_SPI_TRANSFER_EVENT event,
                            DRV_SPI_TRANSFER_HANDLE transferHandle,
                            uintptr_t context)
{
    (void)transferHandle;
    SpiAsync_Local_t *f = (SpiAsync_Local_t *)context;

    if (event == DRV_SPI_TRANSFER_EVENT_ERROR)
        ASSERT(false);

    if (event == DRV_SPI_TRANSFER_EVENT_PENDING)
        return;

    f->spiBusy = false;

    if (qspidrv_interrupt_ready(&f->q)) {
        struct SpiDrvEntry *item = qspidrv_interrupt_ptr(&f->q);
        ASSERT(item);
        item->event = event;
        ChipSelect(f->idx, item->csInstance, false);
    } else {
        ASSERT(false);
    }

    qspidrv_interrupt_done(&f->q);
    if (!TrySendNext(f->idx)) {
        ++f->producer;
    }
    f->needService = true;
}
