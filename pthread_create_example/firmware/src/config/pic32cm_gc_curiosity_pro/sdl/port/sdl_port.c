/*******************************************************************************
  Software diagnostic library project

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_port.c

  Summary:
    Source file for port diagnostic routines.

  Description:
    This file provides diagnostic functions used by PORT peripheral diagnostics.

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
/*------------------------------------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------------------------------------*/
#include "drv_port/sdl_drv_port.h"
#include "sdl_port.h"

/*------------------------------------------------------------------------------------------------------------
* Constants
*------------------------------------------------------------------------------------------------------------*/
#define SDL_PORT_FIVE_BIT_MASK      0x1FU
#define SDL_PORT_SYNC_DELAY         100U

/*------------------------------------------------------------------------------------------------------------
* Data Types
*------------------------------------------------------------------------------------------------------------*/
/* None */

/*------------------------------------------------------------------------------------------------------------
* Global Variables
*------------------------------------------------------------------------------------------------------------*/
/* None */

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
    SDL_STATUS SDL_PORT_OutputMonitoring(SDL_PORT_CONFIG * const sdlPortConfig)

  Description:
    Drives the specified PORT pin to the requested HIGH or LOW state based
    on the operation mode and verifies whether the pin has reached the
    expected state by reading back the pin value.

  Precondition:
    - The PORT module must be initialized.
    - The SDL_PORT_CONFIG structure must be properly populated with a valid
      pin, pin state, and operation mode.
    - For SDL_CONTEXT_ON_DEMAND mode:
        * The pin direction must already be configured as output.
    - For SDL_CONTEXT_IN_USE mode:
        * The pin direction must already be configured as output.
        * The output state must already be driven prior to calling this function.

  Parameters:
    SDL_PORT_CONFIG * const sdlPortConfig - Pointer to configuration structure
    containing the PORT pin, desired pin state, and operation mode.

  Returns:
    SDL_STATUS - Status of the output monitoring operation.
                 SDL_STATUS_PASSED        : Pin state verified successfully.
                 SDL_STATUS_FAILED        : Pin state verification failed.
                 SDL_STATUS_NOT_EXECUTED  : Invalid parameters or operation not performed.

  Remarks:
    In SDL_CONTEXT_POST mode, the pin direction is configured and the output
    state is driven before verification.
*/
SDL_STATUS SDL_PORT_OutputMonitoring(SDL_PORT_CONFIG * const sdlPortConfig)
{
    uint8_t sdlPortGroup;
    uint8_t sdlPinNum;
    SDL_STATUS sdlRetVal = SDL_STATUS_NOT_EXECUTED;

    /* Validate pointer */
    if (sdlPortConfig == NULL)
    {
        return SDL_STATUS_NOT_EXECUTED;
    }

    /* Validate pin and pin state */
    if ((SDL_FALSE == SDL_DRV_PORT_IsPinValid((uint8_t)sdlPortConfig->sdlPortPin)) ||
        ((sdlPortConfig->sdlPortPinState != SDL_PORT_PIN_LOW) &&
         (sdlPortConfig->sdlPortPinState != SDL_PORT_PIN_HIGH)))
    {
        return SDL_STATUS_NOT_EXECUTED;
    }

    /* Extract port group and pin number */
    sdlPortGroup = SDL_GET_PORT_GROUP(sdlPortConfig->sdlPortPin);
    sdlPinNum = (uint8_t)((uint8_t)sdlPortConfig->sdlPortPin & SDL_PORT_FIVE_BIT_MASK);

    if(sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST)
    {
        SDL_DRV_PORT_DirSet(sdlPortGroup, sdlPinNum);
    }
    if(sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_ON_DEMAND)
    {
        if (sdlPortConfig->sdlPortPinState == SDL_PORT_PIN_HIGH)
        {
            SDL_DRV_PORT_OutSet(sdlPortGroup, sdlPinNum);
        }
        else
        {
            SDL_DRV_PORT_OutClr(sdlPortGroup, sdlPinNum);
        }
    }
    if(sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_ON_DEMAND || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_IN_USE)
    {
        uint32_t portPinRegValue =(SDL_DRV_PORT_PinRead(sdlPortGroup) >> (uint32_t)sdlPinNum) & 1UL;

        if ((SDL_PORT_PIN_STATE)portPinRegValue == sdlPortConfig->sdlPortPinState)
        {
            sdlRetVal = SDL_STATUS_PASSED;
        }
        else
        {
            sdlRetVal = SDL_STATUS_FAILED;
        }
    }

    return sdlRetVal;
}

/* Function:
    SDL_STATUS SDL_PORT_InputOutputDirection(SDL_PORT_CONFIG * const sdlPortConfig)

  Description:
    Sets the direction of the specified PORT pin as input or output based
    on the operation mode and verifies the applied direction by reading
    back the direction register.

  Precondition:
    - The PORT module must be initialized.
    - The SDL_PORT_CONFIG structure must be properly populated with a valid
      pin, desired pin direction, and operation mode.
    - For SDL_CONTEXT_IN_USE mode:
        * The pin direction must already be configured.

  Parameters:
    SDL_PORT_CONFIG * const sdlPortConfig - Pointer to configuration structure
    containing the PORT pin, desired pin direction, and operation mode.

  Returns:
    SDL_STATUS - Status of the input/output direction operation.
                 SDL_STATUS_PASSED        : Pin direction verified successfully.
                 SDL_STATUS_FAILED        : Pin direction verification failed.
                 SDL_STATUS_NOT_EXECUTED  : Invalid parameters or operation not performed.

  Remarks:
    In SDL_CONTEXT_POST and SDL_CONTEXT_ON_DEMAND modes, the pin direction
    is configured prior to verification.
*/
SDL_STATUS SDL_PORT_InputOutputDirection(SDL_PORT_CONFIG * const sdlPortConfig)
{
    uint8_t sdlPortGroup;
    uint8_t sdlPinNum;
    SDL_STATUS sdlRetVal = SDL_STATUS_NOT_EXECUTED;

    /* Validate pointer */
    if (sdlPortConfig == NULL)
    {
        return SDL_STATUS_NOT_EXECUTED;
    }

    /* Validate pin and direction */
    if ((SDL_FALSE == SDL_DRV_PORT_IsPinValid((uint8_t)sdlPortConfig->sdlPortPin)) ||
        ((sdlPortConfig->sdlPortDir != SDL_PORT_PIN_INPUT) &&
         (sdlPortConfig->sdlPortDir != SDL_PORT_PIN_OUTPUT)))
    {
        return SDL_STATUS_NOT_EXECUTED;
    }

    /* Extract port group and pin number */
    sdlPortGroup = SDL_GET_PORT_GROUP(sdlPortConfig->sdlPortPin);
    sdlPinNum = (uint8_t)((uint8_t)sdlPortConfig->sdlPortPin & SDL_PORT_FIVE_BIT_MASK);

    if(sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_ON_DEMAND)
    {
        if (sdlPortConfig->sdlPortDir == SDL_PORT_PIN_OUTPUT)
        {
            SDL_DRV_PORT_DirSet(sdlPortGroup, sdlPinNum);
        }
        else
        {
            SDL_DRV_PORT_DirClr(sdlPortGroup, sdlPinNum);
        }
    }
    if(sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_ON_DEMAND || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_IN_USE)
    {
        uint32_t sdlPortPinDirRegValue = (SDL_DRV_PORT_DirRead(sdlPortGroup) >> (uint32_t)sdlPinNum) & 1UL;

        if ((SDL_PORT_PIN_DIR)sdlPortPinDirRegValue == sdlPortConfig->sdlPortDir)
        {
            sdlRetVal = SDL_STATUS_PASSED;
        }
        else
        {
            sdlRetVal = SDL_STATUS_FAILED;
        }
    }


    return sdlRetVal;
}


/* Function:
    SDL_STATUS SDL_PORT_PullUpPullDown(SDL_PORT_CONFIG * const sdlPortConfig)

  Description:
    Configures the pull-up or pull-down state of the specified PORT pin
    based on the operation mode and verifies the applied state by reading
    back the pin value.

  Precondition:
    - The PORT module must be initialized.
    - The SDL_PORT_CONFIG structure must be properly populated with a valid
      pin, pull-up/pull-down state, and operation mode.
    - For SDL_CONTEXT_ON_DEMAND mode:
        * The pin direction must already be configured as input.
    - For SDL_CONTEXT_IN_USE mode:
        * The pin direction and pull-up/pull-down configuration must already
          be applied prior to calling this function.

  Parameters:
    SDL_PORT_CONFIG * const sdlPortConfig - Pointer to configuration structure
    containing the PORT pin and pull-up/pull-down state.

  Returns:
    SDL_STATUS - Status of the pull-up/pull-down operation.
                 SDL_STATUS_PASSED        : Pin state verified successfully.
                 SDL_STATUS_FAILED        : Pin state verification failed.
                 SDL_STATUS_NOT_EXECUTED  : Invalid parameters or operation not performed.

  Remarks:
    A synchronization delay is applied before pin state verification to
    allow the pull configuration to take effect.
*/
SDL_STATUS SDL_PORT_PullUpPullDown(SDL_PORT_CONFIG * const sdlPortConfig)
{
    uint8_t sdlPortGroup;
    uint8_t sdlPinNum;
    SDL_PORT_PIN_STATE sdlPortPinState;
    SDL_STATUS sdlRetVal = SDL_STATUS_NOT_EXECUTED;

    /* Validate pointer */
    if (sdlPortConfig == NULL)
    {
        return SDL_STATUS_NOT_EXECUTED;
    }

    /* Validate pin and direction */
    if ((SDL_FALSE == SDL_DRV_PORT_IsPinValid((uint8_t)sdlPortConfig->sdlPortPin)) ||
        ((sdlPortConfig->sdlPortDir != SDL_PORT_PIN_INPUT) &&
         (sdlPortConfig->sdlPortDir != SDL_PORT_PIN_OUTPUT)))
    {
        return SDL_STATUS_NOT_EXECUTED;
    }

    /* Extract port group and pin number */
    sdlPortGroup = SDL_GET_PORT_GROUP(sdlPortConfig->sdlPortPin);
    sdlPinNum = (uint8_t)((uint8_t)sdlPortConfig->sdlPortPin & SDL_PORT_FIVE_BIT_MASK);

    if(sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST)
    {
        /* Configure pin as input */
        SDL_DRV_PORT_DirClr(sdlPortGroup, sdlPinNum);

        /* Enable pull-up */
        SDL_DRV_PORT_PullupEnable(sdlPortGroup, sdlPinNum);
    }
    if(sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_ON_DEMAND)
    {
        if (sdlPortConfig->sdlPortPullupState == SDL_PORT_PIN_PULL_UP)
        {
            SDL_DRV_PORT_OutSet(sdlPortGroup, sdlPinNum);
        }
        else
        {
            SDL_DRV_PORT_OutClr(sdlPortGroup, sdlPinNum);
        }

        /* Synchronization delay */
        SDL_DRV_COMMON_TimerDelay_us(SDL_PORT_SYNC_DELAY);
    }
    if(sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_ON_DEMAND || sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_IN_USE)
    {
        if (sdlPortConfig->sdlPortPullupState == SDL_PORT_PIN_PULL_UP)
        {
            sdlPortPinState = SDL_PORT_PIN_HIGH;
        }
        else
        {
            sdlPortPinState = SDL_PORT_PIN_LOW;
        }

        uint32_t sdlPortPinRegValue = (SDL_DRV_PORT_PinRead(sdlPortGroup) >> (uint32_t)sdlPinNum) & 1UL;

        if ((SDL_PORT_PIN_STATE)sdlPortPinRegValue == sdlPortPinState)
        {
            sdlRetVal = SDL_STATUS_PASSED;
        }
        else
        {
            sdlRetVal = SDL_STATUS_FAILED;
        }
    }
    return sdlRetVal;
}

/* Function:
    SDL_STATUS SDL_PORT_SFRReset(SDL_PORT_CONFIG * const sdlPortConfig,
                                 uint32_t *failRegOffset)

  Description:
    Resets the PORT Special Function Registers (SFRs) for the specified
    port group and reports the offset of the register that failed to reset,
    if any.

  Precondition:
    - The PORT module must be initialized.
    - The SDL_PORT_CONFIG structure must contain a valid port group.
    - The operation mode must be SDL_CONTEXT_POST.
    - The failRegOffset pointer must be non-NULL.

  Parameters:
    SDL_PORT_CONFIG * const sdlPortConfig - Pointer to configuration structure
    containing the PORT group and operation mode.
    uint32_t *failRegOffset - Pointer to store the offset of the SFR that
    failed to reset.

  Returns:
    SDL_STATUS - Status of the SFR reset operation.
                 SDL_STATUS_PASSED        : All SFRs reset successfully.
                 SDL_STATUS_FAILED        : One or more SFRs failed to reset.
                 SDL_STATUS_NOT_EXECUTED  : Invalid parameters or operation not performed.

  Remarks:
    This API performs no action when called in operation modes other than
    SDL_CONTEXT_POST.
*/
SDL_STATUS SDL_PORT_SFRReset(SDL_PORT_CONFIG * const sdlPortConfig,uint32_t *failRegOffset)
{
    SDL_STATUS retVal = SDL_STATUS_NOT_EXECUTED;

    if (( NULL != failRegOffset ) && ( SDL_DRV_PORT_IsPortValid(sdlPortConfig->sdlPortGroup)== SDL_TRUE) && (sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST))
    {      
        uint32_t portGroupAddress = 0x0U;
        portGroupAddress = SDL_DRV_PORT_GetPortGroupAddress(sdlPortConfig->sdlPortGroup);
        retVal = (SDL_STATUS)SDL_DRV_COMMON_SFRReset(portGroupAddress,sdlPortResetSFRInfo,(sizeof(SDL_SFR_RESET_INFO)/sizeof(SDL_SFR_RESET_INFO)),failRegOffset);
    }
    else
    {
        /* Do Nothing */
    }

    return retVal;
}

/* Function:
    SDL_STATUS SDL_PORT_SFRWriteRead(SDL_PORT_CONFIG * const sdlPortConfig,
                                     uint32_t *failRegOffset)

  Description:
    Performs a write and read-back test on the PORT Special Function Registers
    (SFRs) for the specified port group to verify correct register behavior.

  Precondition:
    - The PORT module must be initialized.
    - The SDL_PORT_CONFIG structure must contain a valid port group.
    - The operation mode must be SDL_CONTEXT_POST.
    - The failRegOffset pointer must be non-NULL.

  Parameters:
    SDL_PORT_CONFIG * const sdlPortConfig - Pointer to configuration structure
    containing the PORT group and operation mode.
    uint32_t *failRegOffset - Pointer to store the offset of the SFR that
    failed during the write/read operation.

  Returns:
    SDL_STATUS - Status of the SFR write/read operation.
                 SDL_STATUS_PASSED        : All SFRs passed the write/read test.
                 SDL_STATUS_FAILED        : One or more SFRs failed the write/read test.
                 SDL_STATUS_NOT_EXECUTED  : Invalid parameters or operation not performed.

  Remarks:
    This API performs no action when called in operation modes other than
    SDL_CONTEXT_POST.
*/
SDL_STATUS SDL_PORT_SFRWriteRead(SDL_PORT_CONFIG * const sdlPortConfig, uint32_t *failRegOffset)
{
    SDL_STATUS retVal = SDL_STATUS_NOT_EXECUTED;

    if (( NULL != failRegOffset ) && ( SDL_DRV_PORT_IsPortValid(sdlPortConfig->sdlPortGroup)== SDL_TRUE) && (sdlPortConfig->sdlPortOprMode == SDL_CONTEXT_POST))
    {
        /* SFR write/read register table index for the required PORT sdlPortGroup*/
        uint32_t portGroupAddress = SDL_DRV_PORT_GetPortGroupAddress(sdlPortConfig->sdlPortGroup);

        retVal = (SDL_STATUS)SDL_DRV_COMMON_SFRWriteRead(portGroupAddress,sdlPortWRSFRInfo[sdlPortConfig->sdlPortGroup],\
                (sizeof(sdlPortWRSFRInfo[sdlPortConfig->sdlPortGroup])/sizeof(SDL_SFR_RW_INFO)),failRegOffset);
    }
    else
    {
        /* Do Nothing */
    }

    return retVal;
}

