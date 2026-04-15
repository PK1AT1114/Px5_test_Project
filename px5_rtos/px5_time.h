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

#ifndef PX5_TIME_HEADER
#define PX5_TIME_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  Time Constants
   Section III: Time Types
   Section IV:  PX5 API Mapping
   Section V:   Actual PX5 API prototypes

******************************************************************************/


/******************************************************************************
 ************************** Section I: Include Files **************************
 *****************************************************************************/

#include "sys/types.h"
#include "px5_errno.h"


/******************************************************************************
 ************************ Section II:  Time Constants *************************
 *****************************************************************************/

/* Define the default 10ms periodic tick constants. These may be overridden by the
   application and/or the PX5 binding layer.  */

#ifndef PX5_TICKS_PER_SECOND            
#define PX5_TICKS_PER_SECOND                                1000UL
#endif  /* PX5_TICKS_PER_SECOND */


/* Define the default clock ID.  */

#define CLOCK_REALTIME                                      1UL
#define CLOCK_MONOTONIC                                     (CLOCK_REALTIME)


/* Define number of nanoseconds in a second.  */

#define PX5_NANOSECONDS_PER_SECOND                          1000000000UL


/* Define number of microseconds in a second.  */

#define PX5_MICROSECONDS_PER_SECOND                         1000000UL


/* Define the number of nanoseconds per tick.  */

#define PX5_NANOSECONDS_PER_TICK                            (PX5_NANOSECONDS_PER_SECOND/PX5_TICKS_PER_SECOND)


/* Define the number of microseconds per tick.  */

#define PX5_MICROSECONDS_PER_TICK                           (PX5_MICROSECONDS_PER_SECOND/PX5_TICKS_PER_SECOND)


/* Define the maximum number of seconds the tick timer can support.  */

#define PX5_MAXIMUM_SECONDS                                 (0xFFFFFFFEUL/PX5_TICKS_PER_SECOND)


/* Define the default epoch value.  */

#ifndef PX5_DEFAULT_EPOCH
#define PX5_DEFAULT_EPOCH                                   1756694400  /* September 1, 2025  00:00:00 UTC  */
#endif  /* PX5_DEFAULT_EPOCH */


/******************************************************************************
 ************************* Section III:  Time Types ***************************
 *****************************************************************************/

/* Define the clock ID handle type.  */

typedef unsigned long                                       clockid_t;


/* Define the basic time type, default to 32-bit time and allow for external override.  */

#ifndef _PX5_TIME_T
#ifdef  PX5_64BIT_TIME_T
typedef unsigned long long                                  px5_time_t;
#else   /* PX5_64BIT_TIME_T  */
typedef unsigned long                                       px5_time_t;
#endif
#endif  /* _PX5_TIME_T */


/* Define the timer specification structure.  */

struct px5_timespec
{

    /* Number of seconds  */
    px5_time_t                                              tv_sec;

    /* Number of nanoseconds.  */
    unsigned long                                           tv_nsec;
};


/* Define forward references for internal control structures.  */

struct px5_time_control_struct; 


/* Define the timer type, which is effectively contains a pointer to the internal timer control structure.  */

typedef struct timer_t_struct
{

    /* Pointer to the internal timer control structure.  */
    struct px5_timer_control_struct *                       internal_timer_control;
    
} timer_t;


/******************************************************************************
 *********************** Section IV: PX5 API Mapping **************************
 *****************************************************************************/

/* Determine if PX5 source is present. If so, skip remapping.  */

#ifndef PX5_SOURCE_CODE


/* Determine if parameter checking is disabled. If so, skip parameter checking veneer.  */

#ifndef PX5_PARAMETER_CHECKING_DISABLE

#define clock_getres                                        px5_clock_getres_check_params
#define clock_gettime                                       px5_clock_gettime_check_params
#define clock_settime                                       px5_clock_settime_check_params
#define nanosleep                                           px5_nanosleep_check_params
#ifndef PX5_TIME_REMAPPING_DISABLE
#define time                                                px5_time
#endif  /* PX5_TIME_REMAPPING_DISABLE */

#else

#define clock_getres                                        px5_clock_getres
#define clock_gettime                                       px5_clock_gettime
#define clock_settime                                       px5_clock_settime
#define nanosleep                                           px5_nanosleep
#ifndef PX5_TIME_REMAPPING_DISABLE
#define time                                                px5_time
#endif  /* PX5_TIME_REMAPPING_DISABLE */

#endif /* PX5_PARAMETER_CHECKING_DISABLE */

#endif /* PX5_SOURCE_CODE */


/* By default, the basic time-types are mapped to PX5 internal versions.  */

#ifndef PX5_TIME_REMAPPING_DISABLE
#define timespec                                            px5_timespec
#define time_t                                              px5_time_t
#endif  /* PX5_TIME_REMAPPING_DISABLE */


/******************************************************************************
 ******************** Section IV: Actual PX5 API prototypes *******************
 *****************************************************************************/

int             px5_clock_getres(clockid_t  clock_id,  struct px5_timespec *  resolution);
int             px5_clock_getres_check_params(clockid_t  clock_id,  struct px5_timespec *  resolution);
int             px5_clock_gettime(clockid_t  clock_id,  struct px5_timespec *  current_time);
int             px5_clock_gettime_check_params(clockid_t  clock_id,  struct px5_timespec *  current_time);
int             px5_clock_settime(clockid_t  clock_id,  const struct px5_timespec *  new_time);
int             px5_clock_settime_check_params(clockid_t  clock_id,  const struct px5_timespec *  new_time);
int             px5_nanosleep(const struct px5_timespec *  request_time, struct px5_timespec *  remaining_time);
int             px5_nanosleep_check_params(const struct px5_timespec *  request_time, struct px5_timespec *  remaining_time);
px5_time_t      px5_time(px5_time_t *  return_seconds);


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_TIME_HEADER */
