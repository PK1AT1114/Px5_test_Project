/*******************************************************************************
  SAMD21DA1HAx SDLnostic library project

  Company:
    Microchip Technology Inc.

  File Name:
    SDL_commmon.h

  Summary:
    Common header file for SDLnostic routine.

  Description:
    This file provides common function prototypes, macros and datatypes for the
    SDLnostics library.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef SDL_DRV_COMMON_H
#define SDL_DRV_COMMON_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

/*------------------------------------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "sdl/systick/drv_systick/sdl_drv_systick.h"

/*------------------------------------------------------------------------------------------------------------
* Constants
*------------------------------------------------------------------------------------------------------------*/

#define SDL_COMMON_ERROR_INVALID_WR_PROPERTY   (0xE100U)


/*------------------------------------------------------------------------------------------------------------
* Data Types
*------------------------------------------------------------------------------------------------------------*/

        
extern uint32_t sdlErrorStatus;

// *****************************************************************************

/* SDLnostic bool

  Summary:
    SDLnostic bool for true and false

  Description:
    SDLnostic bool for true and false

  Remarks:
    None.
*/
typedef enum sdl_bool
{
    SDL_FALSE  = 0x5A5AU,
    SDL_TRUE = 0xA5A5U
} SDL_BOOL;

// *****************************************************************************
/* SDLnostic return status

  Summary:
    Status returned by SDLnostic routine

  Description:
    SDLnostic routines status will have one of the following values.

  Remarks:
    None.
*/

/* Conditional compilation to avoid conflict with peripheral SDLnostic library. */

typedef enum sdl_DRV_status
{
    SDL_DRV_STATUS_NOT_EXECUTED  = 0x3333U,
    SDL_DRV_STATUS_IN_PROGRESS = 0x5555U,
    SDL_DRV_STATUS_PASSED = 0xAAAAU,
    SDL_DRV_STATUS_FAILED = 0xCCCCU
} SDL_DRV_STATUS;

typedef enum
{
  TIMEOUT_OCCURRED = 0xAA,
  TIMEOUT_NOT_OCCURRED = 0x55,
}TIMEOUT_STATUS;
// *****************************************************************************

/* SFR Reset state

  Summary:
  Structure to define register write read property.

  Description:
    SDL_WRITE_1_READ_1 - Write '1' into register bit, Read '1' from register bit
    SDL_WRITE_1_READ_0 -   Write '1' into register bit, Read '0' from register bit
    SDL_WRITE_1_0_READ_1_0 - Write '1' into register bit, Read '1' from register bit then
                              Write '1' into register bit, Read '0' from register bit
  Remarks:
    None.
*/
typedef enum SDL_write_read_property
{
    SDL_WRITE_1_READ_1     = 0x11,
    SDL_WRITE_1_READ_0     = 0x22,
    SDL_WRITE_1_0_READ_1_0 = 0x33,
}SDL_WRITE_READ_PROPERTY;

/* SFR Reset state

  Summary:
  Structure to hold reset value of SFR.

  Description:
    This can be used when checking reset value of SFRs.
    If the register is an RW (read-write) register, then regClear, regSet and
    regStatus shall be the same register.
    Certain peripherals have write-only registers for enabling and disabling
    specific features, in this case, status is read from a third register.
    eg. In PIO peripheral, PIO_PER, PIO_PDR, PIO_PSR corresponds to
    regClear, regSet and regStatus.
    statusInverted parameter indicates whether the status bit is active high
    or active low. ie; if the status bit 0 indicates that the feature is enabled
    then statusInverted shall be set as 'true'.

  Remarks:
    None.
*/

typedef struct
{
    uint32_t regOffset;
    uint32_t regDefaultValue;
    uint8_t regSize;
} SDL_SFR_RESET_INFO;

/* SFR read/write info

  Summary:
  Structure to hold details of read/write registers.

  Description:
    This can be used when checking write/read operation of SFRs.
    If the register is an RW (read-write) register, then writeReg and readReg shall be the same register.
    Certain peripherals have write-only registers for enabling and disabling
    specific features, in this case, status is read from a readReg register.
    regSize is for 1 byte, 2 byte or 4 byte wide register.
    wrProperty is for Register write-read property type.

  Remarks:
    None.
*/
typedef struct
{
    uint32_t writeReg;
    uint32_t readReg;
    uint32_t mask;
    uint8_t regSize;
    SDL_WRITE_READ_PROPERTY wrProperty;
} SDL_SFR_RW_INFO;


/*------------------------------------------------------------------------------------------------------------
* Global Extern Variables
*------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------
* Public Function Declarations
*-----------------------------------------------------------------------------------------------------------*/
void SDL_DRV_COMMON_UpdateErrorStatus(uint32_t errStatus);

SDL_DRV_STATUS SDL_DRV_COMMON_SFRReset(uint32_t periphBase, const SDL_SFR_RESET_INFO *sfrInfo, uint16_t numReg, uint32_t *failRegOffset);

SDL_DRV_STATUS SDL_DRV_COMMON_SFRWriteRead(uint32_t periphBase, const SDL_SFR_RW_INFO *sfrInfo, uint16_t numReg, uint32_t *failRegOffset);

TIMEOUT_STATUS SDL_DRV_COMMON_IsTimeoutReached_us(void);

int32_t SDL_DRV_COMMON_memcmp(const void *data1, const void *data2, size_t size);

void SDL_DRV_COMMON_memset(void *data, char ch, size_t size);

void SDL_DRV_COMMON_TimerStart_us(uint32_t delay_us);

void SDL_DRV_COMMON_TimerDelay_us(uint32_t delay_us);

void SDL_DRV_COMMON_SetTimeout_us(uint32_t timeout_us);

uint32_t SDL_DRV_COMMON_GetTimeout_us(void);






// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // SDL_DRV_COMMON_H
