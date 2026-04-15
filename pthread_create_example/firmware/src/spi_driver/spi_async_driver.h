/*------------------------------------------------------------------------------------------------*/
/* SPI Asynchronous DMA Driver optimized for TC6 usage                                            */
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
#ifndef SPI_ASYNC_DRIVER_H_
#define SPI_ASYNC_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                       User Adjustable Defines                        */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

#define DRV_CS_MAX_INST             (3)  /* Maximum support chip select pins */
#define DRV_NON_ZERO_CPY_BUF_SIZE   (768) /* If zero copy was set to false, this is the maximum buffer size */

#define GPIO_BITMASK_OLED_DC        (1 << 0) /* Data / Control Pin for OLED */

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                       Public Type Definitions                        */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

/**
 * \brief Callback when ever a SPI transfer was executed.
 * \note This function may be implemented by the integrator and passed as parameter to SpiDrvAsync_Transfer.
 * \ntoe It will be called from interrupt context.
 *  \param spiInstance - The SPI instance. Starting with 0 for the first SPI instance.
 *  \param csInstance - The SPI Chip Select instance number. Starting with 0 for the first chip select pin.
 *  \param success - true, if there were no errors while transferring on SPI.
 *  \param pTxBuf - Transmission buffer. This buffer was sent on the MOSI line of SPI.
 *  \param pRxBuf - Reception buffer. This buffer is now filled by the data came from the MISO line of SPI.
 *  \param bufSize - Length in Bytes for both the TX and RX buffer.
 *  \param tag - Any pointer the integrator gave along with the call of SpiDrvAsync_Transfer.
 */
typedef void (*SpiDrvAsync_TransferCB_t)(uint8_t spiInstance, uint8_t csInstance, bool success, const uint8_t *pTxBuf, uint8_t *pRxBuf, uint16_t bufSize, void *tag);

typedef struct
{
    uint8_t spiInstance;    /** The SPI instance. Starting with 0 for the first SPI instance */
    uint8_t csInstance;     /** The SPI Chip Select instance number. Starting with 0 for the first chip select pin */   
    uint32_t gpioMask;      /** Bit mask for GPIOs to set/clear (does not include chip select) */
    
    const uint8_t *pTxBuf;  /** Transmission buffer. This buffer will be sent on the MOSI line of SPI. If NULL, Dummy data is getting sent */ 
    uint8_t *pRxBuf;        /** Reception buffer. This buffer will be filled by the data coming from the MISO line of SPI. If zeroCopyRx is false, this pointer can set to NULL. Otherwise, RX data will be discarded on NULL pointer */   
    uint16_t bufSize;       /** Length in Bytes for both the TX and RX buffer. If zeroCopy is set to false, this value must be smaller or equal to DRV_NON_ZERO_CPY_BUF_SIZE */
    
    void *tag;              /** Any pointer the integrator wants to give along with this transfer. Exact the same value will be given back on the SpiDrvAsync_CB_OnTransfer callback. This driver will never use this value for internal usage */
    
    SpiDrvAsync_TransferCB_t pCallback; /** User may register a callback function, when the transfer has been completed. NULL will disable callback */
    bool zeroCopyTx;        /** true, if the given pTxBuf is valid until pCallback is getting raised. false, the driver will copy pTxBuf into its own memory */
    bool zeroCopyRx;        /** true, if the given pRxBuf is valid until pCallback is getting raised. false, the driver will provide buffer for RX */

} SpiDrvAsync_TransferParam_t;

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                            Public API                                */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

/** \brief Initializes the SPI driver.
 *  \note Must be called before any other functions of this component.
 */
void SpiDrvAsync_Init(void);

bool SpiDrvAsync_TransferReady(uint8_t spiInstance);

/** \brief Initializes the SPI driver.
 *  \param pParam - Pointer to the filled out transfer parameters. All elements of the structure will copied internally, so structure can be destroyed after calling this function.
 *  \return true, if SPI transfer was successful enqueued. false, there was an error or no empty queue space. The integrator shall try again later.
 */
bool SpiDrvAsync_Transfer(SpiDrvAsync_TransferParam_t *pParam);

/** \brief Gives driver CPU time to do maintenance. Also from this function the callbacks will be raised.
 */
void SpiDrvAsync_Service(void);

/** \brief Sets the driver in a particular mode for a given chip select instance.
 *  \param spiInstance - The SPI instance. Starting with 0 for the first SPI instance.
 *  \param csInstance - Chip Select instance, starting with 0 for the first instance.
 *  \param speedHz - SPI speed in Hertz (Baudrate)
 *  \param phaseValidLeadingEdge - true, if data sampled on leading SCK edge. false, if data sampled on trailing edge.
 *  \param polarityIdleLow - true, if SCK is low when idle. false, if SCK is high when idle.
 *  \return true, if parameters where accepted and set to the driver. false, one ore more parameters where not accepted, no changes are done.
 */
bool SpiDrvAsync_SetSpiConfig(uint8_t spiInstance, uint8_t csInstance, uint32_t speedHz, bool phaseValidLeadingEdge, bool polarityIdleLow);

#ifdef __cplusplus
}
#endif
#endif // SPI_ASYNC_DRIVER_H_
