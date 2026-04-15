/*******************************************************************************
  CAN Application Module Header

  Company:
    Microchip Technology Inc.

  File Name:
    app_can.h

  Summary:
    CAN application module for transmit/receive operations.

  Description:
    This module provides a simplified interface for CAN TX/RX operations
    built on top of the Harmony CAN PLIB. Users can integrate this module
    to quickly add CAN communication with sensor data.
 *******************************************************************************/

#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Section: Constants
// *****************************************************************************

#define APP_CAN_MAX_DATA_LENGTH     64U

/* Standard identifier id[28:18] */
#define APP_CAN_WRITE_ID(id)        ((id) << 18)
#define APP_CAN_READ_ID(id)         ((id) >> 18)

// *****************************************************************************
// Section: Data Types
// *****************************************************************************

/* Application CAN states */
typedef enum {
    APP_CAN_STATE_IDLE = 0,
    APP_CAN_STATE_TX_PENDING,
    APP_CAN_STATE_TX_SUCCESS,
    APP_CAN_STATE_TX_ERROR,
    APP_CAN_STATE_RX_SUCCESS,
    APP_CAN_STATE_RX_ERROR
} APP_CAN_STATE;

/* Message type configuration */
typedef enum {
    APP_CAN_MSG_STANDARD = 0,       /* 11-bit ID, Classic CAN */
    APP_CAN_MSG_STANDARD_FD,        /* 11-bit ID, CAN FD with BRS */
    APP_CAN_MSG_EXTENDED,           /* 29-bit ID, Classic CAN */
    APP_CAN_MSG_EXTENDED_FD         /* 29-bit ID, CAN FD with BRS */
} APP_CAN_MSG_TYPE;

/* RX message source */
typedef enum {
    APP_CAN_RX_FIFO0 = 0,
    APP_CAN_RX_FIFO1,
    APP_CAN_RX_BUFFER
} APP_CAN_RX_SOURCE;

/* User-friendly message structure */
typedef struct {
    uint32_t    id;                             /* Message ID */
    uint8_t     data[APP_CAN_MAX_DATA_LENGTH];  /* Payload */
    uint8_t     length;                         /* Data length (1-8 classic, 1-64 FD) */
    uint16_t    timestamp;                      /* RX timestamp */
    APP_CAN_MSG_TYPE type;                      /* Message type */
} APP_CAN_MSG;

/* Callback for received messages - user implements this */
typedef void (*APP_CAN_RX_CALLBACK)(const APP_CAN_MSG *msg, APP_CAN_RX_SOURCE source);

/* Callback for transmit complete */
typedef void (*APP_CAN_TX_CALLBACK)(bool success);

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

/**
 * @brief Initialize CAN module with Message RAM
 * @param msgRAM Pointer to Message RAM buffer (must be 32-byte aligned)
 * @note  Buffer should be CAN0_MESSAGE_RAM_CONFIG_SIZE bytes
 */
void APP_CAN_Initialize(uint8_t *msgRAM);

/**
 * @brief Register callback for received messages
 * @param callback Function called when message received (NULL to disable)
 */
void APP_CAN_RegisterRxCallback(APP_CAN_RX_CALLBACK callback);

/**
 * @brief Register callback for transmit complete
 * @param callback Function called when TX completes (NULL to disable)
 */
void APP_CAN_RegisterTxCallback(APP_CAN_TX_CALLBACK callback);

/**
 * @brief Transmit a CAN message
 * @param msg Message to send
 * @return true if message queued successfully
 */
bool APP_CAN_Transmit(const APP_CAN_MSG *msg);

/**
 * @brief Get current state
 * @return Current APP_CAN_STATE
 */
APP_CAN_STATE APP_CAN_GetState(void);

/**
 * @brief Check if transmitter is ready
 * @return true if ready to transmit
 */
bool APP_CAN_IsTxReady(void);

/**
 * @brief Get last CAN error
 * @return CAN error code
 */
uint32_t APP_CAN_GetLastError(void);

/**
 * @brief Process CAN tasks (call from main loop)
 * @note  Handles state transitions and callbacks
 */
void APP_CAN_Tasks(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_DRIVER_H */
