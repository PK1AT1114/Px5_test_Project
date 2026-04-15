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

#ifndef PX5_TYPES_HEADER
#define PX5_TYPES_HEADER


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  PX5 Identification
   Section III: Base types
   Section IV:  Base constants

******************************************************************************/

/******************************************************************************
 ************************** Section I: Include Files **************************
 *****************************************************************************/

#include "px5_user_config.h"
#include "px5_binding.h"


/******************************************************************************
 *********************** Section II: PX5 Identification ***********************
 *****************************************************************************/

#ifndef PX5
#define PX5
#endif  /* PX5 */


/******************************************************************************
 ************************** Section III: Base types ***************************
 *****************************************************************************/

/* Define base types.  */

#ifndef _U_CHAR
typedef unsigned char                                       u_char;
#endif  /* _U_CHAR */

#ifndef _U_INT
typedef unsigned int                                        u_int;
#endif

#ifndef _U_LONG
typedef unsigned long                                       u_long;
#endif  /* _U_LONG */

#ifndef _U_SHORT
typedef unsigned short                                      u_short;
#endif  /* _U_SHORT */

#ifndef _SIZE_T
typedef unsigned int                                        size_t;
#endif  /* _SIZE_T  */

#ifndef _SSIZE_T
typedef int                                                 ssize_t;
#endif  /* _SIZE_T  */

#ifndef _OFF_T
typedef long                                                off_t;
#endif  /* _OFF_T  */

#ifndef _U_UINT4
typedef unsigned int                                        u_int4;
#endif  /* _U_UINT4  */

#ifndef _PTR_VAL_T
typedef unsigned long                                       ptr_val_t;
#endif  /* _PTR_VAL_T  */


/******************************************************************************
 ************************* Section IV: Base constants *************************
 *****************************************************************************/

#ifndef NULL 
#define NULL                                                ((void *) 0)
#endif  /* NULL */

#endif  /* PX5_TYPES_HEADER */
