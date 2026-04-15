/*******************************************************************************
  Interface definition of SDL SysTick Driver

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_drv_systick.h

  Summary:
    Interface definition of the SDL SysTick Driver.

  Description:
    This file defines the interface for the SDL SysTick Driver
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

#ifndef SDL_DRV_SYSTICK_H    // Guards against multiple inclusion
#define SDL_DRV_SYSTICK_H

#include "sdl_drv_systick_config.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus // Provide C++ Compatibility
    extern "C" {
#endif

#define SDL_SYSTICK_ERROR_NOT_ENABLED           (1U)

#define SDL_SYSTICK_ERROR_INVALID_PARAMETER     (2U)

// *****************************************************************************
// *****************************************************************************
// Section: Interface
// *****************************************************************************
// *****************************************************************************

typedef struct
{
    uint32_t start;
    uint32_t count;
}SDL_SYSTICK_TIMEOUT;

/***************************** SYSTICK API *******************************/
void SDL_DRV_SYSTICK_DelayUs ( uint32_t delay_us );
void SDL_DRV_SYSTICK_StartTimeOut(SDL_SYSTICK_TIMEOUT* timeout, uint32_t delay_us);
bool SDL_DRV_SYSTICK_IsTimeoutReached(SDL_SYSTICK_TIMEOUT* timeout);
void SDL_DRV_SYSTICK_Callback(void);

#ifdef __cplusplus // Provide C++ Compatibility
 }
#endif

#endif
