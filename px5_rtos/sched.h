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

#ifndef PX5_SCHED_HEADER
#define PX5_SCHED_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  Pthread Constants
   Section III: PX5 API Mapping
   Section IV:  Actual pthread API prototypes

******************************************************************************/


/******************************************************************************
 ************************** Section I: Include Files **************************
 *****************************************************************************/

#include "sys/types.h"
#include "bits/pthreadtypes.h"
#include "px5_errno.h"


/******************************************************************************
 ********************* Section II:  Pthread Constants *************************
 *****************************************************************************/



/******************************************************************************
 ********************** Section III: PX5 API Mapping **************************
 *****************************************************************************/

/* Determine if PX5 source is present. If so, skip remapping.  */

#ifndef PX5_SOURCE_CODE


/* Determine if parameter checking is disabled. If so, skip parameter checking veener.  */

#ifndef PX5_PARAMETER_CHECKING_DISABLE

#define sched_yield                                         px5_sched_yield_check_params

#else

#define sched_yield                                         px5_sched_yield


#endif /* PX5_PARAMETER_CHECKING_DISABLE */

#endif /* PX5_SOURCE_CODE */


/******************************************************************************
 **************** Section IV: Actual pthread API prototypes *******************
 *****************************************************************************/

int             px5_sched_yield(void);
int             px5_sched_yield_check_params(void);


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_SCHED_HEADER */
