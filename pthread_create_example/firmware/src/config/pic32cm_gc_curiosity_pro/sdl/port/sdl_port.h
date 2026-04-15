/*******************************************************************************
  Software diagnostic library project

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_port.h

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

#ifndef SDL_PORT_H    /* Guard against multiple inclusion */
#define SDL_PORT_H

/*------------------------------------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------------------------------------*/

#include "../common/sdl_common.h"
/*------------------------------------------------------------------------------------------------------------
* Constants
*------------------------------------------------------------------------------------------------------------*/
/* None */

/*------------------------------------------------------------------------------------------------------------
* Data Types
*------------------------------------------------------------------------------------------------------------*/

typedef uint8_t SDL_PORT_GROUP;



typedef enum {
    /* =========================
     * PORT A PINS
     * ========================= */
#ifdef PIN_PA00
    SDL_PIN_PA00 = PIN_PA00,
#endif
#ifdef PIN_PA01
    SDL_PIN_PA01 = PIN_PA01,
#endif
#ifdef PIN_PA02
    SDL_PIN_PA02 = PIN_PA02,
#endif
#ifdef PIN_PA03
    SDL_PIN_PA03 = PIN_PA03,
#endif
#ifdef PIN_PA04
    SDL_PIN_PA04 = PIN_PA04,
#endif
#ifdef PIN_PA05
    SDL_PIN_PA05 = PIN_PA05,
#endif
#ifdef PIN_PA06
    SDL_PIN_PA06 = PIN_PA06,
#endif
#ifdef PIN_PA07
    SDL_PIN_PA07 = PIN_PA07,
#endif
#ifdef PIN_PA08
    SDL_PIN_PA08 = PIN_PA08,
#endif
#ifdef PIN_PA09
    SDL_PIN_PA09 = PIN_PA09,
#endif
#ifdef PIN_PA10
    SDL_PIN_PA10 = PIN_PA10,
#endif
#ifdef PIN_PA11
    SDL_PIN_PA11 = PIN_PA11,
#endif
#ifdef PIN_PA12
    SDL_PIN_PA12 = PIN_PA12,
#endif
#ifdef PIN_PA13
    SDL_PIN_PA13 = PIN_PA13,
#endif
#ifdef PIN_PA14
    SDL_PIN_PA14 = PIN_PA14,
#endif
#ifdef PIN_PA15
    SDL_PIN_PA15 = PIN_PA15,
#endif
#ifdef PIN_PA16
    SDL_PIN_PA16 = PIN_PA16,
#endif
#ifdef PIN_PA17
    SDL_PIN_PA17 = PIN_PA17,
#endif
#ifdef PIN_PA18
    SDL_PIN_PA18 = PIN_PA18,
#endif
#ifdef PIN_PA19
    SDL_PIN_PA19 = PIN_PA19,
#endif
#ifdef PIN_PA20
    SDL_PIN_PA20 = PIN_PA20,
#endif
#ifdef PIN_PA21
    SDL_PIN_PA21 = PIN_PA21,
#endif
#ifdef PIN_PA22
    SDL_PIN_PA22 = PIN_PA22,
#endif
#ifdef PIN_PA23
    SDL_PIN_PA23 = PIN_PA23,
#endif
#ifdef PIN_PA24
    SDL_PIN_PA24 = PIN_PA24,
#endif
#ifdef PIN_PA25
    SDL_PIN_PA25 = PIN_PA25,
#endif
#ifdef PIN_PA26
    SDL_PIN_PA26 = PIN_PA26,
#endif
#ifdef PIN_PA27
    SDL_PIN_PA27 = PIN_PA27,
#endif
#ifdef PIN_PA28
    SDL_PIN_PA28 = PIN_PA28,
#endif
#ifdef PIN_PA29
    SDL_PIN_PA29 = PIN_PA29,
#endif
#ifdef PIN_PA30
    SDL_PIN_PA30 = PIN_PA30,
#endif
#ifdef PIN_PA31
    SDL_PIN_PA31 = PIN_PA31,
#endif

    /* =========================
     * PORT B PINS
     * ========================= */
#ifdef PIN_PB00
    SDL_PIN_PB00 = PIN_PB00,
#endif
#ifdef PIN_PB01
    SDL_PIN_PB01 = PIN_PB01,
#endif
#ifdef PIN_PB02
    SDL_PIN_PB02 = PIN_PB02,
#endif
#ifdef PIN_PB03
    SDL_PIN_PB03 = PIN_PB03,
#endif
#ifdef PIN_PB04
    SDL_PIN_PB04 = PIN_PB04,
#endif
#ifdef PIN_PB05
    SDL_PIN_PB05 = PIN_PB05,
#endif
#ifdef PIN_PB06
    SDL_PIN_PB06 = PIN_PB06,
#endif
#ifdef PIN_PB07
    SDL_PIN_PB07 = PIN_PB07,
#endif
#ifdef PIN_PB08
    SDL_PIN_PB08 = PIN_PB08,
#endif
#ifdef PIN_PB09
    SDL_PIN_PB09 = PIN_PB09,
#endif
#ifdef PIN_PB10
    SDL_PIN_PB10 = PIN_PB10,
#endif
#ifdef PIN_PB11
    SDL_PIN_PB11 = PIN_PB11,
#endif
#ifdef PIN_PB12
    SDL_PIN_PB12 = PIN_PB12,
#endif
#ifdef PIN_PB13
    SDL_PIN_PB13 = PIN_PB13,
#endif
#ifdef PIN_PB14
    SDL_PIN_PB14 = PIN_PB14,
#endif
#ifdef PIN_PB15
    SDL_PIN_PB15 = PIN_PB15,
#endif
#ifdef PIN_PB16
    SDL_PIN_PB16 = PIN_PB16,
#endif
#ifdef PIN_PB17
    SDL_PIN_PB17 = PIN_PB17,
#endif
#ifdef PIN_PB18
    SDL_PIN_PB18 = PIN_PB18,
#endif
#ifdef PIN_PB19
    SDL_PIN_PB19 = PIN_PB19,
#endif
#ifdef PIN_PB20
    SDL_PIN_PB20 = PIN_PB20,
#endif
#ifdef PIN_PB21
    SDL_PIN_PB21 = PIN_PB21,
#endif
#ifdef PIN_PB22
    SDL_PIN_PB22 = PIN_PB22,
#endif
#ifdef PIN_PB23
    SDL_PIN_PB23 = PIN_PB23,
#endif
#ifdef PIN_PB24
    SDL_PIN_PB24 = PIN_PB24,
#endif
#ifdef PIN_PB25
    SDL_PIN_PB25 = PIN_PB25,
#endif
#ifdef PIN_PB26
    SDL_PIN_PB26 = PIN_PB26,
#endif
#ifdef PIN_PB27
    SDL_PIN_PB27 = PIN_PB27,
#endif
#ifdef PIN_PB28
    SDL_PIN_PB28 = PIN_PB28,
#endif
#ifdef PIN_PB29
    SDL_PIN_PB29 = PIN_PB29,
#endif
#ifdef PIN_PB30
    SDL_PIN_PB30 = PIN_PB30,
#endif
#ifdef PIN_PB31
    SDL_PIN_PB31 = PIN_PIN_PB31,
#endif

    /* =========================
     * PORT C PINS
     * ========================= */
#ifdef PIN_PC00
    SDL_PIN_PC00 = PIN_PC00,
#endif
#ifdef PIN_PC01
    SDL_PIN_PC01 = PIN_PC01,
#endif
#ifdef PIN_PC02
    SDL_PIN_PC02 = PIN_PC02,
#endif
#ifdef PIN_PC03
    SDL_PIN_PC03 = PIN_PC03,
#endif
#ifdef PIN_PC04
    SDL_PIN_PC04 = PIN_PC04,
#endif
#ifdef PIN_PC05
    SDL_PIN_PC05 = PIN_PC05,
#endif
#ifdef PIN_PC06
    SDL_PIN_PC06 = PIN_PC06,
#endif
#ifdef PIN_PC07
    SDL_PIN_PC07 = PIN_PC07,
#endif
#ifdef PIN_PC08
    SDL_PIN_PC08 = PIN_PC08,
#endif
#ifdef PIN_PC09
    SDL_PIN_PC09 = PIN_PC09,
#endif
#ifdef PIN_PC10
    SDL_PIN_PC10 = PIN_PC10,
#endif
#ifdef PIN_PC11
    SDL_PIN_PC11 = PIN_PC11,
#endif
#ifdef PIN_PC12
    SDL_PIN_PC12 = PIN_PC12,
#endif
#ifdef PIN_PC13
    SDL_PIN_PC13 = PIN_PC13,
#endif
#ifdef PIN_PC14
    SDL_PIN_PC14 = PIN_PC14,
#endif
#ifdef PIN_PC15
    SDL_PIN_PC15 = PIN_PC15,
#endif
#ifdef PIN_PC16
    SDL_PIN_PC16 = PIN_PC16,
#endif
#ifdef PIN_PC17
    SDL_PIN_PC17 = PIN_PC17,
#endif
#ifdef PIN_PC18
    SDL_PIN_PC18 = PIN_PC18,
#endif
#ifdef PIN_PC19
    SDL_PIN_PC19 = PIN_PC19,
#endif
#ifdef PIN_PC20
    SDL_PIN_PC20 = PIN_PC20,
#endif
#ifdef PIN_PC21
    SDL_PIN_PC21 = PIN_PC21,
#endif
#ifdef PIN_PC22
    SDL_PIN_PC22 = PIN_PC22,
#endif
#ifdef PIN_PC23
    SDL_PIN_PC23 = PIN_PC23,
#endif
#ifdef PIN_PC24
    SDL_PIN_PC24 = PIN_PC24,
#endif
#ifdef PIN_PC25
    SDL_PIN_PC25 = PIN_PC25,
#endif
#ifdef PIN_PC26
    SDL_PIN_PC26 = PIN_PC26,
#endif
#ifdef PIN_PC27
    SDL_PIN_PC27 = PIN_PC27,
#endif
#ifdef PIN_PC28
    SDL_PIN_PC28 = PIN_PC28,
#endif
#ifdef PIN_PC29
    SDL_PIN_PC29 = PIN_PC29,
#endif
#ifdef PIN_PC30
    SDL_PIN_PC30 = PIN_PC30,
#endif
#ifdef PIN_PC31
    SDL_PIN_PC31 = PIN_PC31,
#endif

    /* =========================
     * PORT D PINS
     * ========================= */
#ifdef PIN_PD00
    SDL_PIN_PD00 = PIN_PD00,
#endif
#ifdef PIN_PD01
    SDL_PIN_PD01 = PIN_PD01,
#endif
#ifdef PIN_PD02
    SDL_PIN_PD02 = PIN_PD02,
#endif
#ifdef PIN_PD03
    SDL_PIN_PD03 = PIN_PD03,
#endif
#ifdef PIN_PD04
    SDL_PIN_PD04 = PIN_PD04,
#endif
#ifdef PIN_PD05
    SDL_PIN_PD05 = PIN_PD05,
#endif
#ifdef PIN_PD06
    SDL_PIN_PD06 = PIN_PD06,
#endif
#ifdef PIN_PD07
    SDL_PIN_PD07 = PIN_PD07,
#endif
#ifdef PIN_PD08
    SDL_PIN_PD08 = PIN_PD08,
#endif
#ifdef PIN_PD09
    SDL_PIN_PD09 = PIN_PD09,
#endif
#ifdef PIN_PD10
    SDL_PIN_PD10 = PIN_PD10,
#endif
#ifdef PIN_PD11
    SDL_PIN_PD11 = PIN_PD11,
#endif
#ifdef PIN_PD12
    SDL_PIN_PD12 = PIN_PD12,
#endif
#ifdef PIN_PD13
    SDL_PIN_PD13 = PIN_PD13,
#endif
#ifdef PIN_PD14
    SDL_PIN_PD14 = PIN_PD14,
#endif
#ifdef PIN_PD15
    SDL_PIN_PD15 = PIN_PD15,
#endif
#ifdef PIN_PD16
    SDL_PIN_PD16 = PIN_PD16,
#endif
#ifdef PIN_PD17
    SDL_PIN_PD17 = PIN_PD17,
#endif
#ifdef PIN_PD18
    SDL_PIN_PD18 = PIN_PD18,
#endif
#ifdef PIN_PD19
    SDL_PIN_PD19 = PIN_PD19,
#endif
#ifdef PIN_PD20
    SDL_PIN_PD20 = PIN_PD20,
#endif
#ifdef PIN_PD21
    SDL_PIN_PD21 = PIN_PD21,
#endif
#ifdef PIN_PD22
    SDL_PIN_PD22 = PIN_PD22,
#endif
#ifdef PIN_PD23
    SDL_PIN_PD23 = PIN_PD23,
#endif
#ifdef PIN_PD24
    SDL_PIN_PD24 = PIN_PD24,
#endif
#ifdef PIN_PD25
    SDL_PIN_PD25 = PIN_PD25,
#endif
#ifdef PIN_PD26
    SDL_PIN_PD26 = PIN_PD26,
#endif
#ifdef PIN_PD27
    SDL_PIN_PD27 = PIN_PD27,
#endif
#ifdef PIN_PD28
    SDL_PIN_PD28 = PIN_PD28,
#endif
#ifdef PIN_PD29
    SDL_PIN_PD29 = PIN_PD29,
#endif
#ifdef PIN_PD30
    SDL_PIN_PD30 = PIN_PD30,
#endif
#ifdef PIN_PD31
    SDL_PIN_PD31 = PIN_PD31,
#endif

} SDL_PORT_PIN;

/* PORT pin state

  Summary:
    PORT pin state

  Description:
    This data type defines the possible states of a GPIO pin.

  Remarks:
    None.
*/
typedef enum sdl_port_pin_state
{
    SDL_PORT_PIN_LOW  = 0U,
    SDL_PORT_PIN_HIGH
} SDL_PORT_PIN_STATE;

/* PORT pull direction

  Summary:
    PORT pull direction

  Description:
    This data type defines the pull direction of a GPIO pin.

  Remarks:
    None.
*/
typedef enum sdl_port_pin_pull_dir
{
    SDL_PORT_PIN_PULL_UP  = 0U,
    SDL_PORT_PIN_PULL_DOWN
 } SDL_PORT_PIN_PULL_DIR;

/* PORT pin direction

  Summary:
    PORT pin direction

  Description:
    This data type defines the pin direction of a GPIO pin.

  Remarks:
    None.
*/
typedef enum sdl_port_pin_dir
{
    SDL_PORT_PIN_INPUT  = 0,
    SDL_PORT_PIN_OUTPUT
} SDL_PORT_PIN_DIR;

/* PORT configuration
 *

Summary:
PORT operation configuration
*
Description:
This data structure defines input parameters for PORT service APIs to
perform GPIO control and monitoring at runtime.
*
Remarks:
None.
*/
typedef struct
{
    uint8_t sdlPortGroup;
    SDL_PORT_PIN sdlPortPin;
    SDL_PORT_PIN_STATE sdlPortPinState;
    SDL_PORT_PIN_DIR sdlPortDir;
    SDL_PORT_PIN_PULL_DIR sdlPortPullupState;
    SDL_CONTEXT sdlPortOprMode;
} SDL_PORT_CONFIG;
/*------------------------------------------------------------------------------------------------------------
* Global Extern Variables
*------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------
* Public Function Declarations
*-----------------------------------------------------------------------------------------------------------*/

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
SDL_STATUS SDL_PORT_OutputMonitoring(SDL_PORT_CONFIG *const sdlPortConfig);

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
SDL_STATUS SDL_PORT_InputOutputDirection(SDL_PORT_CONFIG *const sdlPortConfig);

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
SDL_STATUS SDL_PORT_PullUpPullDown(SDL_PORT_CONFIG *const sdlPortConfig);

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
SDL_STATUS SDL_PORT_SFRReset(SDL_PORT_CONFIG * const sdlPortConfig,uint32_t *failRegOffset);

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
SDL_STATUS SDL_PORT_SFRWriteRead(SDL_PORT_CONFIG * const sdlPortConfig, uint32_t *failRegOffset);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // SDL_PORT_H
