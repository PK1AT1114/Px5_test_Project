/*******************************************************************************
  PIC32CM SG GC SDL

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_common.c

  Summary:
    Source file for common software diagnostic routine.

  Description:
    This file provides general functions used by multiple peripheral diagnostics.

 *******************************************************************************/

/*******************************************************************************
 * Copyright (C) 2027 Microchip Technology Inc. and its subsidiaries.
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
#include "sdl_common.h"
#include "drv_common/sdl_drv_common.h"

/*------------------------------------------------------------------------------------------------------------
* Constants
*------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------
* Function Declarations
*------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------
* Global Static Variables
*------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------
* Global Extern Variables
*------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------
* Function Definitions
*------------------------------------------------------------------------------------------------------------*/

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
uint32_t SDL_COMMON_GetErrorStatus(void)
{
    return sdlErrorStatus;
}

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
void SDL_COMMON_ResetErrorStatus(void)
{
    sdlErrorStatus = 0;
}

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
void SDL_COMMON_SysTickCallback(void)
{
    SDL_DRV_SYSTICK_Callback();
}

