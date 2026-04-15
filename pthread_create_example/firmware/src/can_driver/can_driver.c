/*******************************************************************************
  CAN Application Module Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    app_can.c

  Summary:
    CAN application module for transmit/receive operations.

  Description:
    Implementation of CAN TX/RX operations using Harmony CAN PLIB.
 *******************************************************************************/

#include "can_driver.h"
#include <string.h>

// *****************************************************************************
// Section: Local Data
// *****************************************************************************

/* Module state */
static volatile APP_CAN_STATE appCanState = APP_CAN_STATE_IDLE;
static uint32_t lastError = 0;

/* TX/RX Buffers */
static uint8_t txFifoBuffer[CAN0_TX_FIFO_BUFFER_SIZE];
static uint8_t rxFifo0Buffer[CAN0_RX_FIFO0_SIZE];
static uint8_t rxFifo1Buffer[CAN0_RX_FIFO1_SIZE];
static uint8_t rxBuffer[CAN0_RX_BUFFER_SIZE];

/* User callbacks */
static APP_CAN_RX_CALLBACK rxCallback = NULL;
static APP_CAN_TX_CALLBACK txCallback = NULL;

// *****************************************************************************
// Section: Local Functions
// *****************************************************************************

/* Convert message length to DLC */
static uint8_t LengthToDlc(uint8_t length)
{
    if (length <= 8U)  return length;
    if (length <= 12U) return 0x9U;
    if (length <= 16U) return 0xAU;
    if (length <= 20U) return 0xBU;
    if (length <= 24U) return 0xCU;
    if (length <= 32U) return 0xDU;
    if (length <= 48U) return 0xEU;
    return 0xFU;
}

/* Convert DLC to message length */
static uint8_t DlcToLength(uint8_t dlc)
{
    static const uint8_t lengths[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
    return (dlc < 16U) ? lengths[dlc] : 64U;
}

/* Process received message and invoke user callback */
static void ProcessRxMessage(CAN_RX_BUFFER *rxBuf, APP_CAN_RX_SOURCE source)
{
    if (rxCallback == NULL) return;

    APP_CAN_MSG msg;
    msg.id = rxBuf->xtd ? rxBuf->id : APP_CAN_READ_ID(rxBuf->id);
    msg.length = DlcToLength(rxBuf->dlc);
    msg.timestamp = rxBuf->rxts;

    /* Determine message type */
    if (rxBuf->xtd) {
        msg.type = rxBuf->fdf ? APP_CAN_MSG_EXTENDED_FD : APP_CAN_MSG_EXTENDED;
    } else {
        msg.type = rxBuf->fdf ? APP_CAN_MSG_STANDARD_FD : APP_CAN_MSG_STANDARD;
    }

    /* Copy data */
    memcpy(msg.data, rxBuf->data, msg.length);

    rxCallback(&msg, source);
}

/* TX FIFO Callback - called by PLIB */
static void TxFifoCallback(uintptr_t context)
{
    (void)context;
    uint32_t status = CAN0_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) ||
        ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC)) {
        appCanState = APP_CAN_STATE_TX_SUCCESS;
    } else {
        lastError = status;
        appCanState = APP_CAN_STATE_TX_ERROR;
    }
}

/* RX FIFO0 Callback - called by PLIB */
static void RxFifo0Callback(uint8_t numberOfMessage, uintptr_t context)
{
    (void)context;
    uint32_t status = CAN0_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) ||
        ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC)) {

        memset(rxFifo0Buffer, 0x00, (numberOfMessage * CAN0_RX_FIFO0_ELEMENT_SIZE));
        if (CAN0_MessageReceiveFifo(CAN_RX_FIFO_0, numberOfMessage, (CAN_RX_BUFFER *)rxFifo0Buffer)) {
            CAN_RX_BUFFER *rxBuf = (CAN_RX_BUFFER *)rxFifo0Buffer;
            for (uint8_t i = 0; i < numberOfMessage; i++) {
                ProcessRxMessage(rxBuf, APP_CAN_RX_FIFO0);
                rxBuf = (CAN_RX_BUFFER *)((uint8_t *)rxBuf + CAN0_RX_FIFO0_ELEMENT_SIZE);
            }
            appCanState = APP_CAN_STATE_RX_SUCCESS;
        } else {
            appCanState = APP_CAN_STATE_RX_ERROR;
        }
    } else {
        lastError = status;
        appCanState = APP_CAN_STATE_RX_ERROR;
    }
}

/* RX FIFO1 Callback - called by PLIB */
static void RxFifo1Callback(uint8_t numberOfMessage, uintptr_t context)
{
    (void)context;
    uint32_t status = CAN0_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) ||
        ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC)) {

        memset(rxFifo1Buffer, 0x00, (numberOfMessage * CAN0_RX_FIFO1_ELEMENT_SIZE));
        if (CAN0_MessageReceiveFifo(CAN_RX_FIFO_1, numberOfMessage, (CAN_RX_BUFFER *)rxFifo1Buffer)) {
            CAN_RX_BUFFER *rxBuf = (CAN_RX_BUFFER *)rxFifo1Buffer;
            for (uint8_t i = 0; i < numberOfMessage; i++) {
                ProcessRxMessage(rxBuf, APP_CAN_RX_FIFO1);
                rxBuf = (CAN_RX_BUFFER *)((uint8_t *)rxBuf + CAN0_RX_FIFO1_ELEMENT_SIZE);
            }
            appCanState = APP_CAN_STATE_RX_SUCCESS;
        } else {
            appCanState = APP_CAN_STATE_RX_ERROR;
        }
    } else {
        lastError = status;
        appCanState = APP_CAN_STATE_RX_ERROR;
    }
}

/* RX Buffer Callback - called by PLIB */
static void RxBufferCallback(uint8_t bufferNumber, uintptr_t context)
{
    (void)context;
    uint32_t status = CAN0_ErrorGet();

    if (((status & CAN_PSR_LEC_Msk) == CAN_ERROR_NONE) ||
        ((status & CAN_PSR_LEC_Msk) == CAN_ERROR_LEC_NC)) {

        memset(rxBuffer, 0x00, CAN0_RX_BUFFER_ELEMENT_SIZE);
        if (CAN0_MessageReceive(bufferNumber, (CAN_RX_BUFFER *)rxBuffer)) {
            ProcessRxMessage((CAN_RX_BUFFER *)rxBuffer, APP_CAN_RX_BUFFER);
            appCanState = APP_CAN_STATE_RX_SUCCESS;
        } else {
            appCanState = APP_CAN_STATE_RX_ERROR;
        }
    } else {
        lastError = status;
        appCanState = APP_CAN_STATE_RX_ERROR;
    }
}

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void APP_CAN_Initialize(uint8_t *msgRAM)
{
    
    /* Configure Message RAM */
    CAN0_MessageRAMConfigSet(msgRAM);

    /* Register internal callbacks */
    CAN0_RxFifoCallbackRegister(CAN_RX_FIFO_0, RxFifo0Callback, 0);
    CAN0_RxFifoCallbackRegister(CAN_RX_FIFO_1, RxFifo1Callback, 0);
    CAN0_RxBuffersCallbackRegister(RxBufferCallback, 0);

    appCanState = APP_CAN_STATE_IDLE;
}

void APP_CAN_RegisterRxCallback(APP_CAN_RX_CALLBACK callback)
{
    rxCallback = callback;
}

void APP_CAN_RegisterTxCallback(APP_CAN_TX_CALLBACK callback)
{
    txCallback = callback;
}

bool APP_CAN_Transmit(const APP_CAN_MSG *msg)
{
    if (msg == NULL || msg->length > APP_CAN_MAX_DATA_LENGTH) {
        return false;
    }

    /* Prepare TX buffer */
    memset(txFifoBuffer, 0x00, CAN0_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN_TX_BUFFER *txBuf = (CAN_TX_BUFFER *)txFifoBuffer;

    /* Set message ID */
    if (msg->type == APP_CAN_MSG_EXTENDED || msg->type == APP_CAN_MSG_EXTENDED_FD) {
        txBuf->id = msg->id;
        txBuf->xtd = 1;
    } else {
        txBuf->id = APP_CAN_WRITE_ID(msg->id);
        txBuf->xtd = 0;
    }

    /* Set FD and BRS flags */
    if (msg->type == APP_CAN_MSG_STANDARD_FD || msg->type == APP_CAN_MSG_EXTENDED_FD) {
        txBuf->fdf = 1;
        txBuf->brs = 1;
    }

    /* Set DLC and data */
    txBuf->dlc = LengthToDlc(msg->length);
    memcpy(txBuf->data, msg->data, msg->length);

    /* Register TX callback and transmit */
    CAN0_TxFifoCallbackRegister(TxFifoCallback, 0);
    appCanState = APP_CAN_STATE_TX_PENDING;

    if (!CAN0_MessageTransmitFifo(1, txBuf)) {
        appCanState = APP_CAN_STATE_TX_ERROR;
        return false;
    }

    return true;
}

APP_CAN_STATE APP_CAN_GetState(void)
{
    return appCanState;
}

bool APP_CAN_IsTxReady(void)
{
    return (appCanState != APP_CAN_STATE_TX_PENDING);
}

uint32_t APP_CAN_GetLastError(void)
{
    return lastError;
}

void APP_CAN_Tasks(void)
{
    switch (appCanState) {
        case APP_CAN_STATE_TX_SUCCESS:
            if (txCallback != NULL) {
                txCallback(true);
            }
            appCanState = APP_CAN_STATE_IDLE;
            break;

        case APP_CAN_STATE_TX_ERROR:
            if (txCallback != NULL) {
                txCallback(false);
            }
            appCanState = APP_CAN_STATE_IDLE;
            break;

        case APP_CAN_STATE_RX_SUCCESS:
        case APP_CAN_STATE_RX_ERROR:
            /* RX callback already invoked in ISR context */
            appCanState = APP_CAN_STATE_IDLE;
            break;

        default:
            break;
    }
}

/*******************************************************************************
 End of File
*/
