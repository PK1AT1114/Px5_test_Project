/*******************************************************************************
  Software diagnostic library project

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_drv_port.h

  Summary:
    Header file for PORT diagnostic routines.

  Description:
    This file provides function prototypes, macros and datatypes for the port
    diagnostics library.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2026 Microchip Technology Inc. and its subsidiaries.
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

#ifndef SDL_DRV_PORT_H    /* Guard against multiple inclusion */
#define SDL_DRV_PORT_H


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

/*------------------------------------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------------------------------------*/
#include "../../common/drv_common/sdl_drv_common.h"
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdint.h>
#include "../../sdl_includes.h"

/*------------------------------------------------------------------------------------------------------------
* Constants
*------------------------------------------------------------------------------------------------------------*/
#define SDL_GET_PORT_GROUP(pin)  ((SDL_PORT_GROUP)((uint32_t)(pin)) >> 5U)
#define SDL_GET_PIN_MASK(pin)   (((uint32_t)(0x1U)) << (((uint32_t)(pin)) & 0x1FU))

/*------------------------------------------------------------------------------------------------------------
* Data Types
*------------------------------------------------------------------------------------------------------------*/
/* None */

/*------------------------------------------------------------------------------------------------------------
* Global Variables
*------------------------------------------------------------------------------------------------------------*/

extern const SDL_SFR_RW_INFO sdlPortWRSFRInfo[4][8];
extern const SDL_SFR_RESET_INFO sdlPortResetSFRInfo[];

/*------------------------------------------------------------------------------------------------------------
* Local Variables
*------------------------------------------------------------------------------------------------------------*/
/* None */

/*------------------------------------------------------------------------------------------------------------
* Local Function Prototypes
*------------------------------------------------------------------------------------------------------------*/
/* None */

/*------------------------------------------------------------------------------------------------------------
* Function Definitions
*------------------------------------------------------------------------------------------------------------*/

/* Function:
    uint32_t SDL_DRV_PORT_GetPortGroupAddress(uint8_t sdlPortGroup)

  Description:
    Returns the base register address of the specified PORT group.

  Precondition:
    - The input port group must be valid.

  Parameters:
    uint8_t sdlPortGroup - PORT group index.

  Returns:
    uint32_t - Base address of the PORT group registers.

  Remarks:
    None
*/
uint32_t SDL_DRV_PORT_GetPortGroupAddress(uint8_t sdlPortGroup);

/* Function:
    SDL_BOOL SDL_DRV_PORT_IsPortValid(uint8_t sdlPortGroup)

  Description:
    Checks whether the specified PORT group index is valid for the device.

  Precondition:
    None

  Parameters:
    uint8_t sdlPortGroup - PORT group index to be validated.

  Returns:
    SDL_BOOL
      SDL_TRUE  - Valid PORT group.
      SDL_FALSE - Invalid PORT group.

  Remarks:
    None
*/
SDL_BOOL SDL_DRV_PORT_IsPortValid(uint8_t sdlPortGroup);

/* Function:
    SDL_BOOL SDL_DRV_PORT_IsPinValid(uint8_t sdlPortPin)

  Description:
    Verifies whether the specified logical PORT pin is valid for the device
    based on the available PORT group and pin mask.

  Precondition:
    None

  Parameters:
    uint8_t sdlPortPin - Encoded PORT pin value.

  Returns:
    SDL_BOOL
      SDL_TRUE  - Valid PORT pin.
      SDL_FALSE - Invalid PORT pin.

  Remarks:
    Pin validity is determined using device-specific PORT mask definitions.
*/
SDL_BOOL SDL_DRV_PORT_IsPinValid(uint8_t sdlPortPin);

/* Function:
    void SDL_DRV_PORT_DirSet(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Configures the specified PORT pin direction as output.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid

  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    None
*/
void SDL_DRV_PORT_DirSet(uint8_t sdlPortGroup, uint8_t sdlPortPin);

/* Function:
    void SDL_DRV_PORT_DirClr(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Configures the specified PORT pin direction as input.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid

  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    None
*/
void SDL_DRV_PORT_DirClr(uint8_t sdlPortGroup, uint8_t sdlPortPin);

/* Function:
    void SDL_DRV_PORT_OutSet(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Sets the output level of the specified PORT pin to HIGH.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid

  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    None
*/
void SDL_DRV_PORT_OutSet(uint8_t sdlPortGroup, uint8_t sdlPortPin);

/* Function:
    void SDL_DRV_PORT_OutClr(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Sets the output level of the specified PORT pin to LOW.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid

  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    None
*/
void SDL_DRV_PORT_OutClr(uint8_t sdlPortGroup, uint8_t sdlPortPin);

/* Function:
    uint32_t SDL_DRV_PORT_DirRead(uint8_t sdlPortGroup)

  Description:
    Reads the PORT direction register for the specified group.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.

  Parameters:
    uint8_t sdlPortGroup - PORT group index.

  Returns:
    uint32_t - Direction register value.

  Remarks:
    None
*/
uint32_t SDL_DRV_PORT_DirRead(uint8_t sdlPortGroup);

/* Function:
    uint32_t SDL_DRV_PORT_PinRead(uint8_t sdlPortGroup)

  Description:
    Reads the input status register of the specified PORT group.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.

  Parameters:
    uint8_t sdlPortGroup - PORT group index.

  Returns:
    uint32_t - Input register value.

  Remarks:
    None
*/
uint32_t SDL_DRV_PORT_PinRead(uint8_t sdlPortGroup);

/* Function:
    void SDL_DRV_PORT_PullupEnable(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Enables the internal pull-up resistor for the specified PORT pin.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid.


  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    Input buffer is also enabled when pull-up is configured.
*/
void SDL_DRV_PORT_PullupEnable(uint8_t sdlPortGroup, uint8_t sdlPortPin);

        // DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // SDL_DRV_PORT_H
