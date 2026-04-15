#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "click/Click.h"
/* Define the SysTick information.  */

#define SYSTICK_CONTROL_REG     0xE000E010
#define SYSTICK_RELOAD_REG      0xE000E014
#define SYSTICK_VALUE_REG       0xE000E018
#define SYSTICK_PRIORITY_REG    0xE000ED23
#define SYSTICK_PRIORITY        0x7
#define SYSTICK_COUNT           72000
volatile SYSTICK_OBJECT systick;
/* Define the periodic tick timer interrupt handler.  */
void px5_timer_interrupt_process(void);

void px5_timer_SYSTICK_DelayMs ( uint32_t delay_ms)
{
   uint32_t elapsedCount=0U, delayCount;
   uint32_t deltaCount, oldCount, newCount, period;

   period = SysTick->LOAD + 1U;

   /* Calculate the count for the given delay */
   delayCount=(SYSTICK_FREQ/1000U)*delay_ms;

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
}

void SysTick_Handler(void)
{

    /* Call PX5 RTOS timer interrupt processing.  */
    uintptr_t context = systick.context;

   /* Reading control register clears the count flag */
   (void)SysTick->CTRL;

   systick.tickCounter++;
   if(systick.callback != NULL)
   {
       systick.callback(context);
   }
    px5_timer_interrupt_process();
}



void  platform_setup( void )
{


    /* Set up the SysTick Handler interrupt priority.  */
    *((unsigned char *) SYSTICK_PRIORITY_REG) =  (unsigned char) SYSTICK_PRIORITY;

    /* Set the SysTick reload register.  */
    *((unsigned long *) SYSTICK_RELOAD_REG) =  (unsigned long) (SYSTICK_COUNT - 1);

    /* Set the SysTick value register.  */
    *((unsigned long *) SYSTICK_VALUE_REG) =  (unsigned long) 0;

    /* Enable the SysTick timer. */
    *((unsigned long *) SYSTICK_CONTROL_REG) =  (unsigned long) 7;

    /* Initialize all modules */
    SYS_Initialize ( NULL );
}


