/*******************************************************************************
  SDL SysTick Driver

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_drv_systick.c

  Summary:
    SDL Systick Source File

  Description:
    None

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

#include "device.h"
#include "sdl_drv_systick.h"

volatile static uint32_t tickCounter = 0;
volatile static uint32_t start_tickCounter = 0;

void SDL_DRV_SYSTICK_DelayUs ( uint32_t delay_us)
{
    uint32_t elapsedCount=0U, delayCount;
    uint32_t deltaCount, oldCount, newCount, period;

    period = SysTick->LOAD + 1U;

    /* Calculate the count for the given delay */
    delayCount=((uint32_t)SDL_SYSTICK_FREQ/1000000U)*delay_us;

    if((SysTick->CTRL & SysTick_CTRL_ENABLE_Msk) == SysTick_CTRL_ENABLE_Msk)
    {
        oldCount = SysTick->VAL;

        while (elapsedCount < delayCount)
        {
            newCount = SysTick->VAL;
            deltaCount = oldCount - newCount;

            if(newCount > oldCount)
            {
                deltaCount = period - newCount + oldCount;
            }

            oldCount = newCount;
            elapsedCount = elapsedCount + deltaCount;
        }
    }
    else
    {
        /* Do Nothing */
    }
}

void SDL_DRV_SYSTICK_StartTimeOut(SDL_SYSTICK_TIMEOUT* timeout, uint32_t delay_us)
{
    if(timeout != NULL)
    {
        timeout->start = SysTick->VAL;
        timeout->count = ((uint32_t)SDL_SYSTICK_FREQ / 1000000U) * delay_us;
        start_tickCounter =  tickCounter;
    }
    else
    {
        /* Do Nothing */
    }
}

bool SDL_DRV_SYSTICK_IsTimeoutReached(SDL_SYSTICK_TIMEOUT* timeout)
{
    bool isTimeout  = false;
    uint32_t currentCount = SysTick->VAL;
    uint32_t deltaCount;
    uint32_t overFlowCounter = ((SysTick->LOAD + 1U) * (tickCounter - start_tickCounter));

    if(timeout != NULL)
    {
        if(currentCount > timeout->start)
        {
            deltaCount = ((overFlowCounter - currentCount) + timeout->start);
        }
        else
        {
            deltaCount = (overFlowCounter + (timeout->start - currentCount));
        }

        if (deltaCount < timeout->count)
        {
            isTimeout = false;
        }
        else
        {
            isTimeout = true;
        }
    }
    else
    {
        isTimeout = true;
    }

    return isTimeout;
}

void SDL_DRV_SYSTICK_Callback(void)
{
   /* Reading control register clears the count flag */
   uint32_t sysCtrl = SysTick->CTRL;
   tickCounter++;
   (void)sysCtrl;
}
