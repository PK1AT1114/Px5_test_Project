/*

                             XXXXXXXXXXXXXXXXXXXXXX                          XXXXXXXXXXXXXXXXXXXXXX                                         
                               XXXXXXXXXXXXXXXXXXXXXX                      XXXXXXXXXXXXXXXXXXXXXX                                           
                                 XXXXXXXXXXXXXXXXXXXXXX                  XXXXXXXXXXXXXXXXXXXXXX                                             
                                   XXXXXXXXXXXXXXXXXXXXXX              XXXXXXXXXXXXXXXXXXXXXX                                               
                                     XXXXXXXXXXXXXXXXXXXXXX          XXXXXXXXXXXXXXXXXXXXXX                                                 
                                       XXXXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXXXX                                                   
                                         XXXXXXXXXXXXXXXXXXXXX   XXXXXXXXXXXXXXXXXXXXXX                                                     
PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP           XXXXXXXXXXXXXXXXX   XXXXXXXXXXXXXXXXXXXXXX         555555555  55555555555555555555555555555      
PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP         XXXXXXXXXXXXX   XXXXXXXXXXXXXXXXXXXXXX           555555555  55555555555555555555555555555      
PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP         XXXXXXXXX   XXXXXXXXXXXXXXXXXXXXXX             555555555  55555555555555555555555555555      
PPPPPPPPP                     PPPPPPPPPP         XXXXX   XXXXXXXXXXXXXXXXXXXXXX               555555555                                     
PPPPPPPPP                     PPPPPPPPPP           X   XXXXXXXXXXXXXXXXXXXXXX                 555555555                                     
                              PPPPPPPPPP             XXXXXXXXXXXXXXXXXXXXXX                   55555555555555555555555555555555555555        
PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP             XXXXXXXXXXXXXXXXXXXXXX  XX                 5555555555555555555555555555555555555555      
PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP             XXXXXXXXXXXXXXXXXXXXXX  XXXXXX               55555555555555555555555555555555555555555     
PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP               XXXXXXXXXXXXXXXXXXXXXX  XXXXXXXXXX                                            55555555555    
PPPPPPPPP                                    XXXXXXXXXXXXXXXXXXXXXX  XXXXXXXXXXXXXX           5555555555                     55555555555    
PPPPPPPPP                                  XXXXXXXXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXXXXX         55555555555                   55555555555     
PPPPPPPPP                                XXXXXXXXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXXXXXXXXX        555555555555555555555555555555555555555      
PPPPPPPPP                              XXXXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXXXX       5555555555555555555555555555555555555       
PPPPPPPPP                            XXXXXXXXXXXXXXXXXXXXXX          XXXXXXXXXXXXXXXXXXXXXX       555555555555555555555555555555555         
                                   XXXXXXXXXXXXXXXXXXXXXX              XXXXXXXXXXXXXXXXXXXXXX                                               
                                 XXXXXXXXXXXXXXXXXXXXXX                  XXXXXXXXXXXXXXXXXXXXXX                                             
                               XXXXXXXXXXXXXXXXXXXXXX                      XXXXXXXXXXXXXXXXXXXXXX                                           
                             XXXXXXXXXXXXXXXXXXXXXX                          XXXXXXXXXXXXXXXXXXXXXX                                         
                           XXXXXXXXXXXXXXXXXXXXXX                              XXXXXXXXXXXXXXXXXXXXXX                                       


                             P T H R E A D S +         R T O S         by         B i l l   L a m i e



********************************************************* CONFIDENTIAL *****************************************************************


Version 5.3.0.0


Copyright (C) 2022-2025 PX5 - All Rights Reserved.

You may use this software only under the terms specified in your license 
from PX5. All other use is strictly prohibited. If you do not have a license 
to use this software, please contact www.px5rtos.com to obtain one.

*/


/****************************************************************************
 *                                                                          *
 *         PX5 Binding for Cortex-M0 & GCC Development Tools                *
 *                                                                          *
 ***************************************************************************/


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  Binding-specific Constants and Enumerations
   Section III: Binding-specific Overrides
   Section IV:  Binding Macros

   Note: The px5_binding.h file is only included by the px5.h file, i.e., it 
         is not meant to be included directly by the application software.

******************************************************************************/

#ifndef PX5_BINDING_HEADER
#define PX5_BINDING_HEADER


/******************************************************************************
 ************************* Section I: Include Files ***************************
 *****************************************************************************/

#include "string.h"


/******************************************************************************
 ********** Section II: Binding-specific Constants and Enumerations ***********
 *****************************************************************************/

/* Define the constant string that identifies this binding.  */

#define PX5_BINDING_IDENTIFIER                              "Cortex-M0/GCC"


/* Define this version of the PX5 binding.  */

#define PX5_BINDING_MAJOR_VERSION                           5U
#define PX5_BINDING_MINOR_VERSION                           3U
#define PX5_BINDING_UPDATE_VERSION                          0U
#define PX5_BINDING_PATCH_VERSION                           0U


/* Define the maximum number of cores.  */

#define PX5_MAXIMUM_CORES                                   1


/* Define the minimal remaining stack size for this port. This is generally a function
   of the size of the context save stack frame.  */

#define PX5_BINDING_MINIMUM_STACK_SIZE                      256UL


/* Define the stack frame size for this binding.  */

#define PX5_BINDING_STACK_FRAME_SIZE                        88UL


/* Define stack alignment required for this binding.  */

#define PX5_BINDING_STACK_ALIGNMENT                         8UL           /* Cortex-M requires 8-byte stack alignment  */


/******************************************************************************
 ***************** Section III: Binding-specific Overrides *********************
 *****************************************************************************/


/* Define protection storage and get/restore protection macros, which for this
   binding map to interrupt lockout.  */

#define PX5_PROTECTION_SAVE                                 unsigned int local_interrupt_save_area;
#define PX5_PROTECTION_START                                __asm volatile (" MRS  %0, PRIMASK \n" : "=r" (local_interrupt_save_area) :: "memory" ); \
                                                            __asm volatile (" CPSID  i \n" ::: "memory" );
#define PX5_PROTECTION_END                                  __asm volatile (" MSR  PRIMASK, %0 \n" :: "r" (local_interrupt_save_area) : "memory" );
#define PX5_INTERRUPT_LEVEL_GET(l)                          __asm volatile (" MRS  %0, IPSR \n" : "=r" (interrupt_level) :: "memory" ); 
#define PX5_INTERRUPT_ENABLE                                __asm volatile (" CPSIE i \n" ::: "memory" );


/******************************************************************************
 ************************ Section IV: Binding Macros **************************
 *****************************************************************************/

#define PX5_BINDING_THREAD_PREEMPT                          { \
                                                                __asm volatile (" CPSIE i \n" ::: "memory" ); \
                                                                *((unsigned long *) 0xE000ED04) |= (unsigned long) 0x10000000; \
                                                                __asm volatile (" DMB " ::: "memory" ); \
                                                                __asm volatile (" CPSID  i \n" ::: "memory" ); \
                                                            }

#endif  /* PX5_BINDING_HEADER */
