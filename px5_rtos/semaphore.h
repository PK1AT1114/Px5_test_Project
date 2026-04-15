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

#ifndef PX5_SEMAPHORE_HEADER
#define PX5_SEMAPHORE_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  Semaphore Constants
   Section III: Semaphore Types
   Section IV:  PX5 API Mapping
   Section V:   Actual PX5 API prototypes

******************************************************************************/


/******************************************************************************
 ************************** Section I: Include Files **************************
 *****************************************************************************/

#include "sys/types.h"
#include "pthread.h"
#include "px5_errno.h"


/******************************************************************************
 ******************* Section II:  Semaphore Constants *************************
 *****************************************************************************/

#ifndef SEM_VALUE_MAX
#define SEM_VALUE_MAX                                       0xFFFFFFFFUL
#endif  /* SEM_VALUE_MAX */


/* Define semaphore object handle ID.  */

#define PX5_SEMAPHORE_HANDLE_ID                             0x53455448UL
#define PX5_SEMAPHORE_ATTR_ID                               0x53455441UL


/* Default attribute extension to whitespace.  */

#ifndef PX5_SEMATTR_T_EXTENSIONS
#define PX5_SEMATTR_T_EXTENSIONS
#endif  /* PX5_SEMATTR_T_EXTENSIONS */


/******************************************************************************
 ********************* Section III:  Semaphore Types **************************
 *****************************************************************************/


/* Define the semaphore attribute type, which is optionally used to initialize a semaphore.  */

typedef struct semattr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  semaphore_attr_id;

    /* Define name.  */
    const char *                                            name;

    /* Define the user-specified semaphore control memory address.  */
    void *                                                  semaphore_control_address;

    /* Define extensions to the semattr_t structure.  */
    PX5_SEMATTR_T_EXTENSIONS

} semattr_t;



/* Define forward references for internal control structures.  */

struct px5_semaphore_control_struct; 


/* Define the semaphore type, which is effectively contains a pointer to the internal semaphore control structure.  */

typedef struct sem_t_struct
{

    /* Define the ID of semaphore handle structure.  */
    u_long                                                  semaphore_handle_id;

    /* Pointer to the internal semaphore control structure.  */
    struct px5_semaphore_control_struct *                   internal_semaphore_control;
    
} sem_t;


/******************************************************************************
 *********************** Section IV: PX5 API Mapping **************************
 *****************************************************************************/

/* Determine if PX5 source is present. If so, skip remapping.  */

#ifndef PX5_SOURCE_CODE


/* Determine if parameter checking is disabled. If so, skip parameter checking veneer.  */

#ifndef PX5_PARAMETER_CHECKING_DISABLE

#define sem_destroy                                         px5_sem_destroy_check_params
#define px5_sem_extend_init                                 px5_sem_extend_init_check_params
#define sem_init                                            px5_sem_init_check_params
#define sem_post                                            px5_sem_post_check_params
#define px5_sem_tickwait                                    px5_sem_tickwait_check_params
#define sem_timedwait                                       px5_sem_timedwait_check_params
#define sem_trywait                                         px5_sem_trywait_check_params
#define sem_wait                                            px5_sem_wait_check_params

#else

#define sem_destroy                                         px5_sem_destroy
#define sem_init                                            px5_sem_init
#define sem_post                                            px5_sem_post
#define sem_timedwait                                       px5_sem_timedwait
#define sem_trywait                                         px5_sem_trywait
#define sem_wait                                            px5_sem_wait


#endif /* PX5_PARAMETER_CHECKING_DISABLE */

#endif /* PX5_SOURCE_CODE */


/******************************************************************************
 ******************** Section IV: Actual PX5 API prototypes *******************
 *****************************************************************************/

int             px5_sem_destroy(sem_t *  semaphore_handle);
int             px5_sem_destroy_check_params(sem_t *  semaphore_handle);
int             px5_sem_extend_init(sem_t *  semaphore_handle, int pshared, unsigned int value, semattr_t *  semaphore_attributes);
int             px5_sem_extend_init_check_params(sem_t *  semaphore_handle, int pshared, unsigned int value, semattr_t *  semaphore_attributes);
int             px5_sem_information_get(const sem_t *  semaphore_handle, char **  name,  u_long *  current_count, u_long *  threads_suspended,  pthread_t *first_suspended_thread,  sem_t *  next_semaphore_handle);
int             px5_sem_init(sem_t *  semaphore_handle, int pshared, unsigned int value);
int             px5_sem_init_check_params(sem_t *  semaphore_handle, int pshared, unsigned int value);
int             px5_sem_post(const sem_t *  semaphore_handle);
int             px5_sem_post_check_params(const sem_t *  semaphore_handle);
int             px5_sem_post_notify(const sem_t *  semaphore_handle, void (*post_callback)(sem_t *));
int             px5_sem_tickwait(const sem_t *  semaphore_handle, tick_t  timemout_ticks);
int             px5_sem_tickwait_check_params(const sem_t *  semaphore_handle, tick_t  timemout_ticks);
int             px5_sem_timedwait(const sem_t *  semaphore_handle, const struct px5_timespec *  absolute_time);
int             px5_sem_timedwait_check_params(const sem_t *  semaphore_handle, const struct px5_timespec *  absolute_time);
int             px5_sem_trywait(const sem_t *  semaphore_handle);
int             px5_sem_trywait_check_params(const sem_t *  semaphore_handle);
int             px5_sem_wait(const sem_t *  semaphore_handle);
int             px5_sem_wait_check_params(const sem_t *  semaphore_handle);
int             px5_semattr_destroy(semattr_t *  semaphore_attributes);
int             px5_semattr_getcontroladdr(const semattr_t *  semaphore_attributes, void **  semaphore_control_address);
int             px5_semattr_getcontrolsize(const semattr_t *  semaphore_attributes, size_t *  semaphore_control_size);
int             px5_semattr_getname(const semattr_t *  semaphore_attributes, char **  semaphore_name);
int             px5_semattr_init(semattr_t *  semaphore_attributes);
int             px5_semattr_setcontroladdr(semattr_t *  semaphore_attributes, void *  semaphore_control_address, size_t  semaphore_control_size);
int             px5_semattr_setname(semattr_t *  semaphore_attributes, const char *  semaphore_name);


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_SEMAPHORE_HEADER */
