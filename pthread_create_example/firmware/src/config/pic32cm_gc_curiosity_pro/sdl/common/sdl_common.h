/*******************************************************************************
  PIC32CM SG GC SDL

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_commmon.h

  Summary:
    Common header file for diagnostic routine.

  Description:
    This file provides common function prototypes, macros and datatypes for the
    diagnostics library.

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

#ifndef SDL_COMMON_H
#define SDL_COMMON_H

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

/*------------------------------------------------------------------------------------------------------------
* Constants
*------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------
* Data Types
*------------------------------------------------------------------------------------------------------------*/

// *****************************************************************************

/* Diagnostic return status

  Summary:
    Status returned by diagnostic routine

  Description:
    Diagnostic routines status will have one of the following values.

  Remarks:
    None.
*/

/* Conditional compilation to avoid conflict with peripheral diagnostic library. */

typedef enum sdl_status
{
    SDL_STATUS_NOT_EXECUTED  = 0x3333U,
    SDL_STATUS_IN_PROGRESS = 0x5555U,
    SDL_STATUS_PASSED = 0xAAAAU,
    SDL_STATUS_FAILED = 0xCCCCU
} SDL_STATUS;


// *****************************************************************************
/* SDL context

  Summary:
    Diagnostic routine can be called in context of POST, On-Demand or In-Use.

  Description:
    None

  Remarks:
    None.
*/
typedef enum sdl_context
{
    SDL_CONTEXT_POST  = 0U,
    SDL_CONTEXT_ON_DEMAND = 1U,
    SDL_CONTEXT_IN_USE = 2U
} SDL_CONTEXT;

/*------------------------------------------------------------------------------------------------------------
* Global Extern Variables
*------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------
* Public Function Declarations
*-----------------------------------------------------------------------------------------------------------*/

/* Function:
    uint32_t SDL_COMMON_GetErrorStatus(void)

  Description:
    Returns the global error status for diagnostic routine. Returns last error status sets by
    SDL_COMMON_UpdateErrorStatus interface.

  Precondition:
    None

  Parameters:
    uint32_t errStatus - Error Id

  Returns:
    uint32_t - Error ID

  Remarks:
    None

  Sample code:
    errorId = SDL_COMMON_GetErrorStatus()
*/
uint32_t SDL_COMMON_GetErrorStatus(void);


/* Function:
    void SDL_COMMON_ResetErrorStatus(void)

  Description:
    Resets the global error status to 0.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None

  Sample code:
    SDL_COMMON_ResetErrorStatus()
*/
void SDL_COMMON_ResetErrorStatus(void);

/* Function:
    void SDL_COMMON_SysTickCallback(void)

  Description:
    Call the Systick Callback function.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None

  Sample code:
    SDL_COMMON_SysTickCallback()
*/
void SDL_COMMON_SysTickCallback(void);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // SDL_COMMON_H
