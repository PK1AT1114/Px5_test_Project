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

#ifndef PX5_PTHREAD_HEADER
#define PX5_PTHREAD_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  Constants
   Section III: PX5 API Mapping
   Section IV:  Actual PX5 API prototypes

******************************************************************************/


/******************************************************************************
 ************************** Section I: Include Files **************************
 *****************************************************************************/

#include "sys/types.h"
#include "bits/pthreadtypes.h"
#include "px5_time.h"
#include "px5_errno.h"


/******************************************************************************
 ************************** Section II:  Constants ****************************
 *****************************************************************************/

#define PTHREAD_CREATE_JOINABLE                             1L
#define PTHREAD_CREATE_DETACHED                             2L
#define PTHREAD_PROCESS_SHARED                              3L
#define PTHREAD_PROCESS_PRIVATE                             4L
#define PTHREAD_CANCEL_DISABLE                              5L
#define PTHREAD_CANCEL_ENABLE                               6L
#define PTHREAD_CANCEL_ASYNCHRONOUS                         7L
#define PTHREAD_CANCEL_DEFERRED                             8L
#define PTHREAD_ALL_EVENTS                                  9L
#define PTHREAD_ANY_EVENT                                   10L
#define PTHREAD_MUTEX_NORMAL                                11L
#define PTHREAD_MUTEX_RECURSIVE                             12L
#define PTHREAD_MUTEX_ERRORCHECK                            13L
#ifndef PTHREAD_MUTEX_DEFAULT 
#define PTHREAD_MUTEX_DEFAULT                               (PTHREAD_MUTEX_ERRORCHECK)
#endif
#define PTHREAD_MUTEX_MAX_NESTING                           0xFFFFFFFFUL
#define PTHREAD_PRIO_NONE                                   14L
#define PTHREAD_PRIO_INHERIT                                15L
#define PTHREAD_PRIO_PROTECT                                16L


/* Define the automatic thread start constants.  */

#define PX5_AUTO_START                                      1
#define PX5_DONT_START                                      0


/* Define the minimal stack size, as determined by the binding layer.  */

#define PTHREAD_STACK_MIN                                   (PX5_BINDING_MINIMUM_STACK_SIZE)


/* Define the no time-slice constant.  */

#define PX5_NO_TIME_SLICE                                   0UL


/* Define the cancled return type.  */

#ifdef  PX5_MISRA_ENABLE
#define PTHREAD_CANCELED                                    (px5_misra_pthread_canceled())
#else
#define PTHREAD_CANCELED                                    ((void *) -1)
#endif  /* PX5_MISRA_ENABLE  */


/* Define the default maximum number of 32 priorities (0-31 where 31 is the 
   highest priority. In the future, this may be overridden by the application, but 
   for now only 32 priorities are supported.  */                          

#define PX5_MAXIMUM_PRIORITIES                              32L


/* Define the default priority to the middle of the maximum number of priorities.  */

#ifndef PX5_DEFAULT_PRIORITY
#define PX5_DEFAULT_PRIORITY                                (PX5_MAXIMUM_PRIORITIES/2L)
#endif  /* PX5_DEFAULT_PRIORITY */


/* Define the initialization macro for pthread once variables.  */

#define PTHREAD_ONCE_INIT                                   ((pthread_once_t) 0)


/* Define the maximum number of thread local storage keys.  */

#ifndef PTHREAD_KEYS_MAX                                    
#define PTHREAD_KEYS_MAX                                    1
#endif  /* PTHREAD_KEYS_MAX  */


/******************************************************************************
 ********************** Section III: PX5 API Mapping **************************
 *****************************************************************************/

/* Determine if PX5 source is present. If so, skip remapping.  */

#ifndef PX5_SOURCE_CODE


/* Determine if parameter checking is disabled. If so, skip parameter checking veneer.  */

#ifndef PX5_PARAMETER_CHECKING_DISABLE

#define pthread_attr_destroy                                px5_pthread_attr_destroy
#define pthread_attr_getdetachstate                         px5_pthread_attr_getdetachstate
#define pthread_attr_getstackaddr                           px5_pthread_attr_getstackaddr
#define pthread_attr_getstacksize                           px5_pthread_attr_getstacksize
#define pthread_attr_init                                   px5_pthread_attr_init
#define pthread_attr_setdetachstate                         px5_pthread_attr_setdetachstate
#define pthread_attr_setstackaddr                           px5_pthread_attr_setstackaddr
#define pthread_attr_setstacksize                           px5_pthread_attr_setstacksize
#define pthread_cancel                                      px5_pthread_cancel
#define pthread_cleanup_pop                                 px5_pthread_cleanup_pop
#define pthread_cleanup_push                                px5_pthread_cleanup_push
#define pthread_cond_broadcast                              px5_pthread_cond_broadcast_check_params
#define pthread_cond_destroy                                px5_pthread_cond_destroy_check_params
#define pthread_cond_init                                   px5_pthread_cond_init_check_params
#define pthread_cond_signal                                 px5_pthread_cond_signal_check_params
#define pthread_cond_timedwait                              px5_pthread_cond_timedwait_check_params
#define pthread_cond_wait                                   px5_pthread_cond_wait_check_params
#define pthread_condattr_destroy                            px5_pthread_condattr_destroy
#define pthread_condattr_getpshared                         px5_pthread_condattr_getpshared
#define pthread_condattr_init                               px5_pthread_condattr_init
#define pthread_condattr_setpshared                         px5_pthread_condattr_setpshared
#define pthread_create                                      px5_pthread_create_check_params
#define pthread_detach                                      px5_pthread_detach
#define pthread_equal                                       px5_pthread_equal
#define pthread_exit                                        px5_pthread_exit
#if PX5_MAXIMUM_CORES>1
#define pthread_getaffinity_np                              px5_pthread_getaffinity_np
#endif /* PX5_MAXIMUM_CORES>1  */
#define pthread_getspecific                                 px5_pthread_getspecific
#define pthread_key_create                                  px5_pthread_key_create
#define pthread_key_delete                                  px5_pthread_key_delete
#define pthread_join                                        px5_pthread_join_check_params
#define pthread_mutex_destroy                               px5_pthread_mutex_destroy_check_params
#define pthread_mutex_init                                  px5_pthread_mutex_init_check_params
#define pthread_mutex_lock                                  px5_pthread_mutex_lock_check_params
#define pthread_mutex_trylock                               px5_pthread_mutex_trylock_check_params
#define pthread_mutex_unlock                                px5_pthread_mutex_unlock_check_params
#define pthread_mutexattr_destroy                           px5_pthread_mutexattr_destroy
#define pthread_mutexattr_getprotocol                       px5_pthread_mutexattr_getprotocol
#define pthread_mutexattr_getpshared                        px5_pthread_mutexattr_getpshared
#define pthread_mutexattr_gettype                           px5_pthread_mutexattr_gettype
#define pthread_mutexattr_init                              px5_pthread_mutexattr_init
#define pthread_mutexattr_setprotocol                       px5_pthread_mutexattr_setprotocol
#define pthread_mutexattr_setpshared                        px5_pthread_mutexattr_setpshared
#define pthread_mutexattr_settype                           px5_pthread_mutexattr_settype
#define pthread_once                                        px5_pthread_once
#define pthread_self                                        px5_pthread_self
#if PX5_MAXIMUM_CORES>1
#define pthread_setaffinity_np                              px5_pthread_setaffinity_np
#endif /* PX5_MAXIMUM_CORES>1  */
#define pthread_setcancelstate                              px5_pthread_setcancelstate
#define pthread_setcanceltype                               px5_pthread_setcanceltype
#define pthread_setspecific                                 px5_pthread_setspecific
#define pthread_testcancel                                  px5_pthread_testcancel
#define px5_pthread_event_flags_clear                       px5_pthread_event_flags_clear_check_params
#define px5_pthread_event_flags_clearspecific               px5_pthread_event_flags_clearspecific_check_params
#define px5_pthread_event_flags_create                      px5_pthread_event_flags_create_check_params
#define px5_pthread_event_flags_destroy                     px5_pthread_event_flags_destroy_check_params
#define px5_pthread_event_flags_set                         px5_pthread_event_flags_set_check_params
#define px5_pthread_event_flags_timedwait                   px5_pthread_event_flags_timedwait_check_params
#define px5_pthread_event_flags_trywait                     px5_pthread_event_flags_trywait_check_params
#define px5_pthread_event_flags_wait                        px5_pthread_event_flags_wait_check_params
#define px5_pthread_fastqueue_create                        px5_pthread_fastqueue_create_check_params
#define px5_pthread_fastqueue_destroy                       px5_pthread_fastqueue_destroy_check_params
#define px5_pthread_fastqueue_receive                       px5_pthread_fastqueue_receive_check_params
#define px5_pthread_fastqueue_timedreceive                  px5_pthread_fastqueue_timedreceive_check_params
#define px5_pthread_fastqueue_timedsend                     px5_pthread_fastqueue_timedsend_check_params
#define px5_pthread_fastqueue_send                          px5_pthread_fastqueue_send_check_params
#define px5_pthread_fastqueue_tryreceive                    px5_pthread_fastqueue_tryreceive_check_params
#define px5_pthread_fastqueue_trysend                       px5_pthread_fastqueue_trysend_check_params
#define px5_pthread_memorypool_allocate                     px5_pthread_memorypool_allocate_check_params
#define px5_pthread_memorypool_create                       px5_pthread_memorypool_create_check_params
#define px5_pthread_memorypool_destroy                      px5_pthread_memorypool_destroy_check_params
#define px5_pthread_memorypool_free                         px5_pthread_memorypool_free_check_params
#define px5_pthread_memorypool_timedallocate                px5_pthread_memorypool_timedallocate_check_params
#define px5_pthread_memorypool_tryallocate                  px5_pthread_memorypool_tryallocate_check_params
#define px5_pthread_partitionpool_allocate                  px5_pthread_partitionpool_allocate_check_params
#define px5_pthread_partitionpool_create                    px5_pthread_partitionpool_create_check_params
#define px5_pthread_partitionpool_destroy                   px5_pthread_partitionpool_destroy_check_params
#define px5_pthread_partitionpool_free                      px5_pthread_partitionpool_free_check_params
#define px5_pthread_partitionpool_timedallocate             px5_pthread_partitionpool_timedallocate_check_params
#define px5_pthread_partitionpool_tryallocate               px5_pthread_partitionpool_tryallocate_check_params
#define px5_pthread_resume                                  px5_pthread_resume_check_params
#define px5_pthread_suspend                                 px5_pthread_suspend_check_params
#define px5_pthread_ticktimer_create                        px5_pthread_ticktimer_create_check_params
#define px5_pthread_ticktimer_destroy                       px5_pthread_ticktimer_destroy_check_params
#define px5_pthread_ticktimer_start                         px5_pthread_ticktimer_start_check_params
#define px5_pthread_ticktimer_stop                          px5_pthread_ticktimer_stop_check_params
#define px5_pthread_ticktimer_update                        px5_pthread_ticktimer_update_check_params
#define px5_pthread_timeslice_change                        px5_pthread_timeslice_change_check_params

#else

#define pthread_attr_destroy                                px5_pthread_attr_destroy
#define pthread_attr_getdetachstate                         px5_pthread_attr_getdetachstate
#define pthread_attr_getstackaddr                           px5_pthread_attr_getstackaddr
#define pthread_attr_getstacksize                           px5_pthread_attr_getstacksize
#define pthread_attr_init                                   px5_pthread_attr_init
#define pthread_attr_setdetachstate                         px5_pthread_attr_setdetachstate
#define pthread_attr_setstackaddr                           px5_pthread_attr_setstackaddr
#define pthread_attr_setstacksize                           px5_pthread_attr_setstacksize
#define pthread_cancel                                      px5_pthread_cancel
#define pthread_cleanup_pop                                 px5_pthread_cleanup_pop
#define pthread_cleanup_push                                px5_pthread_cleanup_push
#define pthread_cond_broadcast                              px5_pthread_cond_broadcast
#define pthread_cond_destroy                                px5_pthread_cond_destroy
#define pthread_cond_init                                   px5_pthread_cond_init
#define pthread_cond_signal                                 px5_pthread_cond_signal
#define pthread_cond_timedwait                              px5_pthread_cond_timedwait
#define pthread_cond_wait                                   px5_pthread_cond_wait
#define pthread_condattr_destroy                            px5_pthread_condattr_destroy
#define pthread_condattr_getpshared                         px5_pthread_condattr_getpshared
#define pthread_condattr_init                               px5_pthread_condattr_init
#define pthread_condattr_setpshared                         px5_pthread_condattr_setpshared
#define pthread_create                                      px5_pthread_create
#define pthread_detach                                      px5_pthread_detach
#define pthread_equal                                       px5_pthread_equal
#define pthread_exit                                        px5_pthread_exit
#if PX5_MAXIMUM_CORES>1
#define pthread_getaffinity_np                              px5_pthread_getaffinity_np
#endif /* PX5_MAXIMUM_CORES>1  */
#define pthread_getspecific                                 px5_pthread_getspecific
#define pthread_key_create                                  px5_pthread_key_create
#define pthread_key_delete                                  px5_pthread_key_delete
#define pthread_join                                        px5_pthread_join
#define pthread_mutex_destroy                               px5_pthread_mutex_destroy
#define pthread_mutex_init                                  px5_pthread_mutex_init
#define pthread_mutex_lock                                  px5_pthread_mutex_lock
#define pthread_mutex_trylock                               px5_pthread_mutex_trylock
#define pthread_mutex_unlock                                px5_pthread_mutex_unlock
#define pthread_mutexattr_destroy                           px5_pthread_mutexattr_destroy
#define pthread_mutexattr_getprotocol                       px5_pthread_mutexattr_getprotocol
#define pthread_mutexattr_getpshared                        px5_pthread_mutexattr_getpshared
#define pthread_mutexattr_gettype                           px5_pthread_mutexattr_gettype
#define pthread_mutexattr_init                              px5_pthread_mutexattr_init
#define pthread_mutexattr_setprotocol                       px5_pthread_mutexattr_setprotocol
#define pthread_mutexattr_setpshared                        px5_pthread_mutexattr_setpshared
#define pthread_mutexattr_settype                           px5_pthread_mutexattr_settype
#define pthread_once                                        px5_pthread_once
#define pthread_self                                        px5_pthread_self
#if PX5_MAXIMUM_CORES>1
#define pthread_setaffinity_np                              px5_pthread_setaffinity_np
#endif /* PX5_MAXIMUM_CORES>1  */
#define pthread_setcancelstate                              px5_pthread_setcancelstate
#define pthread_setcanceltype                               px5_pthread_setcanceltype
#define pthread_setspecific                                 px5_pthread_setspecific
#define pthread_testcancel                                  px5_pthread_testcancel


#endif /* PX5_PARAMETER_CHECKING_DISABLE */

#endif /* PX5_SOURCE_CODE */


/******************************************************************************
 ******************** Section IV: Actual PX5 API prototypes *******************
 *****************************************************************************/

int             px5_pthread_attr_destroy(pthread_attr_t *  thread_attributes);
int             px5_pthread_attr_getaffinity(const pthread_attr_t *  thread_attributes, size_t  cpusetsize, cpu_set_t *  core_affinity);
int             px5_pthread_attr_getautostart(const pthread_attr_t *  thread_attributes, int *  automatic_start);
int             px5_pthread_attr_getcontroladdr(const pthread_attr_t *  thread_attributes, void **  thread_control_address);
int             px5_pthread_attr_getcontrolsize(const pthread_attr_t *  thread_attributes, size_t *  thread_control_size);
int             px5_pthread_attr_getdetachstate(const pthread_attr_t *  thread_attributes, int *  detach_state);
int             px5_pthread_attr_getname(const pthread_attr_t *  thread_attributes, char **  name);
int             px5_pthread_attr_getpriority(const pthread_attr_t *  thread_attributes, int *  priority);
int             px5_pthread_attr_getstackaddr(const pthread_attr_t *  thread_attributes, void **  stack_address);
int             px5_pthread_attr_getstacksize(const pthread_attr_t *  thread_attributes, size_t *  stack_size);
int             px5_pthread_attr_gettimeslice(const pthread_attr_t *  thread_attributes, u_long *  thread_time_slice);
int             px5_pthread_attr_init(pthread_attr_t *  thread_attributes);
int             px5_pthread_attr_setaffinity(pthread_attr_t *  thread_attributes, size_t  cpusetsize, const cpu_set_t *  core_affinity);
int             px5_pthread_attr_setautostart(pthread_attr_t *  thread_attributes, int  automatic_start);
int             px5_pthread_attr_setcontroladdr(pthread_attr_t *  thread_attributes, void *  thread_control_address, size_t thread_control_size);
int             px5_pthread_attr_setdetachstate(pthread_attr_t *  thread_attributes, int detach_state);
int             px5_pthread_attr_setname(pthread_attr_t *  thread_attributes, const char *  name);
int             px5_pthread_attr_setpriority(pthread_attr_t *  thread_attributes, int  priority);
int             px5_pthread_attr_setstackaddr(pthread_attr_t *  thread_attributes, void *  stack_address);
int             px5_pthread_attr_setstacksize(pthread_attr_t *  thread_attributes, size_t  stack_size);
int             px5_pthread_attr_settimeslice(pthread_attr_t *  thread_attributes, u_long  thread_time_slice);
int             px5_pthread_cancel(pthread_t thread_handle);
void            px5_pthread_cleanup_pop(int execute);
void            px5_pthread_cleanup_push(void (* cleanup_handler)(void *), void *  argument);
int             px5_pthread_cond_broadcast(const pthread_cond_t *  condition_var_handle);
int             px5_pthread_cond_broadcast_check_params(const pthread_cond_t *  condition_var_handle);
int             px5_pthread_cond_destroy(pthread_cond_t *  condition_var_handle);
int             px5_pthread_cond_destroy_check_params(pthread_cond_t *  condition_var_handle);
int             px5_pthread_cond_information_get(const pthread_cond_t *  condition_var_handle, char **  name,  u_long *  signal_count,  u_long *  threads_suspended,  pthread_t *first_suspended_thread,  pthread_cond_t *  next_cond_var_handle);
int             px5_pthread_cond_init(pthread_cond_t *  condition_var_handle, pthread_condattr_t *  condition_var_attributes);
int             px5_pthread_cond_init_check_params(pthread_cond_t *  condition_var_handle, pthread_condattr_t *  condition_var_attributes);
int             px5_pthread_cond_signal(const pthread_cond_t *  condition_var_handle);
int             px5_pthread_cond_signal_check_params(const pthread_cond_t *  condition_var_handle);
int             px5_pthread_cond_timedwait(const pthread_cond_t *  condition_var_handle, const pthread_mutex_t *  mutex_handle, const struct px5_timespec *  absolute_time);
int             px5_pthread_cond_timedwait_check_params(const pthread_cond_t *  condition_var_handle, const pthread_mutex_t *  mutex_handle, const struct px5_timespec *  absolute_time);
int             px5_pthread_cond_wait(const pthread_cond_t *  condition_var_handle, const pthread_mutex_t *  mutex_handle);
int             px5_pthread_cond_wait_check_params(const pthread_cond_t *  condition_var_handle, const pthread_mutex_t *  mutex_handle);
int             px5_pthread_condattr_destroy(pthread_condattr_t *  condition_var_attributes);
int             px5_pthread_condattr_getcontroladdr(const pthread_condattr_t *  condition_var_attributes, void ** condition_var_control_address);
int             px5_pthread_condattr_getcontrolsize(const pthread_condattr_t *  condition_var_attributes, size_t *  condition_var_control_size);
int             px5_pthread_condattr_getname(const pthread_condattr_t *  condition_var_attributes, char **  name);
int             px5_pthread_condattr_getpshared(const pthread_condattr_t *  condition_var_attributes, int *  process_sharing_designation);
int             px5_pthread_condattr_init(pthread_condattr_t *  condition_var_attributes);
int             px5_pthread_condattr_setcontroladdr(pthread_condattr_t *  condition_var_attributes, void *  condition_var_control_address, size_t  condition_var_control_size);
int             px5_pthread_condattr_setname(pthread_condattr_t *  condition_var_attributes, const char *  name);
int             px5_pthread_condattr_setpshared(pthread_condattr_t *  condition_var_attributes, int   process_sharing_designation);
int             px5_pthread_create(pthread_t *  thread_handle, pthread_attr_t *  attr,  void *(* start_routine)(void *), void *arg);
int             px5_pthread_create_check_params(pthread_t *  thread_handle, pthread_attr_t *  attr,  void *(* start_routine)(void *), void *arg);
int             px5_pthread_detach(pthread_t thread_handle);
int             px5_pthread_equal(pthread_t first_thread, pthread_t second_thread);
void            px5_pthread_exit(void *  exit_value);
int             px5_pthread_event_flags_clear(const pthread_event_flags_t *  event_flags_handle);
int             px5_pthread_event_flags_clear_check_params(const pthread_event_flags_t *  event_flags_handle);
int             px5_pthread_event_flags_clearspecific(const pthread_event_flags_t *  event_flags_handle, u_long flags_to_clear);
int             px5_pthread_event_flags_clearspecific_check_params(const pthread_event_flags_t *  event_flags_handle, u_long flags_to_clear);
int             px5_pthread_event_flags_create(pthread_event_flags_t *  event_flags_handle, pthread_event_flagsattr_t *  event_flags_attributes);
int             px5_pthread_event_flags_create_check_params(pthread_event_flags_t *  event_flags_handle, pthread_event_flagsattr_t *  event_flags_attributes);
int             px5_pthread_event_flags_destroy(pthread_event_flags_t *  event_flags_handle);
int             px5_pthread_event_flags_destroy_check_params(pthread_event_flags_t *  event_flags_handle);
int             px5_pthread_event_flags_information_get(const pthread_event_flags_t *  event_flags_handle, char **name, u_long *current_events, u_long *consumption_mask, u_long *threads_suspended, pthread_t *first_suspended_thread, pthread_event_flags_t * next_event_flags_handle);
int             px5_pthread_event_flags_set(const pthread_event_flags_t *  event_flags_handle, u_long events_to_set);
int             px5_pthread_event_flags_set_check_params(const pthread_event_flags_t *  event_flags_handle, u_long events_to_set);
int             px5_pthread_event_flags_set_notify(const pthread_event_flags_t *  event_flags_handle, void (*set_callback)(pthread_event_flags_t *));
int             px5_pthread_event_flags_timedwait(const pthread_event_flags_t *  event_flags_handle, u_long requested_events, int all_or_any, u_long *  received_events, tick_t  timeout_ticks);
int             px5_pthread_event_flags_timedwait_check_params(const pthread_event_flags_t *  event_flags_handle, u_long requested_events, int all_or_any, u_long *  received_events, tick_t  timeout_ticks);
int             px5_pthread_event_flags_trywait(const pthread_event_flags_t *  event_flags_handle, u_long requested_events, int all_or_any, u_long *  received_events);
int             px5_pthread_event_flags_trywait_check_params(const pthread_event_flags_t *  event_flags_handle, u_long requested_events, int all_or_any, u_long *  received_events);
int             px5_pthread_event_flags_wait(const pthread_event_flags_t *  event_flags_handle, u_long requested_events, int all_or_any, u_long *  received_events);
int             px5_pthread_event_flags_wait_check_params(const pthread_event_flags_t *  event_flags_handle, u_long requested_events, int all_or_any, u_long *  received_events);
int             px5_pthread_event_flagsattr_destroy(pthread_event_flagsattr_t *  event_flags_attributes);
#ifdef PX5_EVENT_FLAG_CONSUMPTION_MASK_ENABLE
int             px5_pthread_event_flagsattr_getautoconsumemask(const pthread_event_flagsattr_t *  event_flags_attributes, u_long *  event_flags_auto_consume_mask);
#else
int             px5_pthread_event_flagsattr_getautoconsumemask(const pthread_event_flagsattr_t *  event_flags_attributes, const u_long *  event_flags_auto_consume_mask);
#endif /* PX5_EVENT_FLAG_CONSUMPTION_MASK_ENABLE  */
int             px5_pthread_event_flagsattr_getcontroladdr(const pthread_event_flagsattr_t *  event_flags_attributes, void **  event_flags_control_address);
int             px5_pthread_event_flagsattr_getcontrolsize(const pthread_event_flagsattr_t *  event_flags_attributes, size_t *  event_flags_control_size);
int             px5_pthread_event_flagsattr_getname(const pthread_event_flagsattr_t *  event_flags_attributes, char ** name);
int             px5_pthread_event_flagsattr_init(pthread_event_flagsattr_t *  event_flags_attributes);
#ifdef PX5_EVENT_FLAG_CONSUMPTION_MASK_ENABLE
int             px5_pthread_event_flagsattr_setautoconsumemask(pthread_event_flagsattr_t *  event_flags_attributes, u_long  event_flags_auto_consume_mask);
#else
int             px5_pthread_event_flagsattr_setautoconsumemask(const pthread_event_flagsattr_t *  event_flags_attributes, const u_long  event_flags_auto_consume_mask);
#endif /* PX5_EVENT_FLAG_CONSUMPTION_MASK_ENABLE  */
int             px5_pthread_event_flagsattr_setcontroladdr(pthread_event_flagsattr_t *  event_flags_attributes, void *  event_flags_control_address, size_t  event_flags_control_size);
int             px5_pthread_event_flagsattr_setname(pthread_event_flagsattr_t *  event_flags_attributes, const char *  name);
int             px5_pthread_fastqueue_create(pthread_fastqueue_t *  fastqueue_handle, pthread_fastqueueattr_t *  fastqueue_attributes, size_t message_size, u_long  max_messages);
int             px5_pthread_fastqueue_create_check_params(pthread_fastqueue_t *  fastqueue_handle, pthread_fastqueueattr_t *  fastqueue_attributes, size_t message_size, u_long  max_messages);
int             px5_pthread_fastqueue_destroy(const pthread_fastqueue_t *  fastqueue_handle);
int             px5_pthread_fastqueue_destroy_check_params(const pthread_fastqueue_t *  fastqueue_handle);
int             px5_pthread_fastqueue_information_get(const pthread_fastqueue_t *  queue_handle, char **  name, u_long *  messages_queued,  u_long *  message_size,  u_long *  maximum_messages, u_long *  threads_suspended,  pthread_t *first_suspended_thread, pthread_fastqueue_t *  next_queue_handle);
int             px5_pthread_fastqueue_receive(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_destination, size_t message_size);
int             px5_pthread_fastqueue_receive_check_params(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_destination, size_t message_size);
int             px5_pthread_fastqueue_send(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_source, size_t message_size);
int             px5_pthread_fastqueue_send_check_params(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_source, size_t message_size);
int             px5_pthread_fastqueue_send_notify(const pthread_fastqueue_t *  fastqueue_handle, void (*send_callback)(pthread_fastqueue_t *));
int             px5_pthread_fastqueue_timedreceive(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_destination, size_t message_size, tick_t timeout_ticks);
int             px5_pthread_fastqueue_timedreceive_check_params(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_destination, size_t message_size, tick_t timeout_ticks);
int             px5_pthread_fastqueue_timedsend(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_source, size_t message_size, tick_t  timeout_ticks);
int             px5_pthread_fastqueue_timedsend_check_params(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_source, size_t message_size, tick_t  timeout_ticks);
int             px5_pthread_fastqueue_tryreceive(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_destination, size_t message_size);
int             px5_pthread_fastqueue_tryreceive_check_params(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_destination, size_t message_size);
int             px5_pthread_fastqueue_trysend(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_source, size_t message_size);
int             px5_pthread_fastqueue_trysend_check_params(const pthread_fastqueue_t *  fastqueue_handle, u_long *  message_source, size_t message_size);
int             px5_pthread_fastqueueattr_destroy(pthread_fastqueueattr_t *  fastqueue_attributes);
int             px5_pthread_fastqueueattr_getcontroladdr(const pthread_fastqueueattr_t *  fastqueue_attributes, void ** fastqueue_control_address);
int             px5_pthread_fastqueueattr_getcontrolsize(const pthread_fastqueueattr_t *  fastqueue_attributes, size_t *  fastqueue_control_size);
int             px5_pthread_fastqueueattr_getname(const pthread_fastqueueattr_t *  fastqueue_attributes, char ** fastqueue_name);
int             px5_pthread_fastqueueattr_getqueueaddr(const pthread_fastqueueattr_t *  fastqueue_attributes, void ** fastqueue_memory_address);
int             px5_pthread_fastqueueattr_getqueuesize(const pthread_fastqueueattr_t *  fastqeueu_attributes, size_t *  fastqueue_memory_size);
int             px5_pthread_fastqueueattr_init(pthread_fastqueueattr_t *  fastqueue_attributes);
int             px5_pthread_fastqueueattr_setcontroladdr(pthread_fastqueueattr_t *  fastqueue_attributes, void *  fastqueue_control_address, size_t fastqueue_control_size);
int             px5_pthread_fastqueueattr_setname(pthread_fastqueueattr_t *  fastqueue_attributes, const char *  fastqueue_name);
int             px5_pthread_fastqueueattr_setqueueaddr(pthread_fastqueueattr_t *  fastqueue_attributes, void *  fastqueue_memory_address, size_t fastqueue_memory_size);
#if PX5_MAXIMUM_CORES>1
int             px5_pthread_getaffinity_np(pthread_t  thread_handle,  size_t  cpusetsize, cpu_set_t  *cpuset);
#endif /* PX5_MAXIMUM_CORES>1  */
void *          px5_pthread_getspecific(pthread_key_t  key);
int             px5_pthread_information_get(pthread_t  thread_handle, char **  name,  int *  state, int *  priority, void **  stack_limit, void **  stack_pointer, u_long *  minimum_stack, pthread_t *  next_thread);
int             px5_pthread_key_create(pthread_key_t *  key, void (* destructor)(void *));
int             px5_pthread_key_delete(pthread_key_t  key);
int             px5_pthread_join(pthread_t  thread_handle, void **  value_destination);
int             px5_pthread_join_check_params(pthread_t  thread_handle, void **  value_destination);
int             px5_pthread_memory_manager_enable(void);
int             px5_pthread_memory_manager_get(void * (** memory_allocate_pointer)(u_int type, u_long size), void (** memory_release_pointer)(u_int type, void *  memory_to_release));
int             px5_pthread_memory_manager_set(void * (* memory_allocate_pointer)(u_int type, u_long size), void (* memory_release_pointer)(u_int type, void *  memory_to_release));
int             px5_pthread_memorypool_allocate(const pthread_memorypool_t *  memorypool_handle, void **  allocated_memory, size_t  request_size);
int             px5_pthread_memorypool_allocate_check_params(const pthread_memorypool_t *  memorypool_handle, void **  allocated_memory, size_t  request_size);
int             px5_pthread_memorypool_create(pthread_memorypool_t *  memorypool_handle, pthread_memorypoolattr_t *  memorypool_attributes, void *  pool_start, size_t  pool_size);
int             px5_pthread_memorypool_create_check_params(pthread_memorypool_t *  memorypool_handle, pthread_memorypoolattr_t *  memorypool_attributes, void *  pool_start, size_t  pool_size);
int             px5_pthread_memorypool_destroy(pthread_memorypool_t *  memorypool_handle);
int             px5_pthread_memorypool_destroy_check_params(pthread_memorypool_t *  memorypool_handle);
int             px5_pthread_memorypool_free(void *  allocated_memory);
int             px5_pthread_memorypool_free_check_params(void *  allocated_memory);
int             px5_pthread_memorypool_information_get(const pthread_memorypool_t *  memorypool_handle, char **  name,  u_long *  maximum_available, u_long *  total_size, u_long *  fragments, u_long *  threads_suspended,  pthread_t *first_suspended_thread,  pthread_memorypool_t *  next_memorypool_handle);
int             px5_pthread_memorypool_timedallocate(const pthread_memorypool_t *  memorypool_handle, void **  allocated_memory, size_t  request_size, tick_t  timeout_ticks);
int             px5_pthread_memorypool_timedallocate_check_params(const pthread_memorypool_t *  memorypool_handle, void **  allocated_memory, size_t  request_size, tick_t  timeout_ticks);
int             px5_pthread_memorypool_tryallocate(const pthread_memorypool_t *  memorypool_handle, void **  allocated_memory, size_t  request_size);
int             px5_pthread_memorypool_tryallocate_check_params(const pthread_memorypool_t *  memorypool_handle, void **  allocated_memory, size_t  request_size);
int             px5_pthread_memorypoolattr_destroy(pthread_memorypoolattr_t *  memorypool_attributes);
int             px5_pthread_memorypoolattr_getcontroladdr(const pthread_memorypoolattr_t *  memorypool_attributes, void ** memorypool_control_address);
int             px5_pthread_memorypoolattr_getcontrolsize(const pthread_memorypoolattr_t *  memorypool_attributes, size_t *  memorypool_control_size);
int             px5_pthread_memorypoolattr_getname(const pthread_memorypoolattr_t *  memorypool_attributes, char ** name);
int             px5_pthread_memorypoolattr_init(pthread_memorypoolattr_t *  memorypool_attributes);
int             px5_pthread_memorypoolattr_setcontroladdr(pthread_memorypoolattr_t *  memorypool_attributes, void *  memorypool_control_address, size_t  memorypool_control_size);
int             px5_pthread_memorypoolattr_setname(pthread_memorypoolattr_t *  memorypool_attributes, const char *  name);
int             px5_pthread_mutex_destroy(pthread_mutex_t *  mutex_handle);
int             px5_pthread_mutex_destroy_check_params(pthread_mutex_t *  mutex_handle);
int             px5_pthread_mutex_information_get(const pthread_mutex_t *  mutex_handle,  char **  name,  u_long *   nested_count,  u_long *  maximum_nesting,  pthread_t *  owner,  u_long *  threads_suspended,  pthread_t *first_suspended_thread,  pthread_mutex_t *   next_mutex_handle);
int             px5_pthread_mutex_init(pthread_mutex_t *  mutex_handle, pthread_mutexattr_t *  mutex_attributes);
int             px5_pthread_mutex_init_check_params(pthread_mutex_t *  mutex_handle, pthread_mutexattr_t *  mutex_attributes);
int             px5_pthread_mutex_lock(const pthread_mutex_t *  mutex_handle);
int             px5_pthread_mutex_lock_check_params(const pthread_mutex_t *  mutex_handle);
int             px5_pthread_mutex_trylock(const pthread_mutex_t *  mutex_handle);
int             px5_pthread_mutex_trylock_check_params(const pthread_mutex_t *  mutex_handle);
int             px5_pthread_mutex_unlock(const pthread_mutex_t *  mutex_handle);
int             px5_pthread_mutex_unlock_check_params(const pthread_mutex_t *  mutex_handle);
int             px5_pthread_mutexattr_destroy(pthread_mutexattr_t *  mutex_attributes);
int             px5_pthread_mutexattr_getcontroladdr(const pthread_mutexattr_t *  mutex_attributes, void **  mutex_control_address);
int             px5_pthread_mutexattr_getcontrolsize(const pthread_mutexattr_t *  mutex_attributes, size_t *  mutex_control_size);
int             px5_pthread_mutexattr_getname(const pthread_mutexattr_t *  mutex_attributes, char **  name);
int             px5_pthread_mutexattr_getprotocol(const pthread_mutexattr_t *  mutex_attributes, int *  protocol);
int             px5_pthread_mutexattr_getpshared(const pthread_mutexattr_t *  mutex_attributes, int *  process_sharing_designation);
int             px5_pthread_mutexattr_gettype(const pthread_mutexattr_t *  mutex_attributes, int *  type);
int             px5_pthread_mutexattr_init(pthread_mutexattr_t *  mutex_attributes);
int             px5_pthread_mutexattr_setcontroladdr(pthread_mutexattr_t *  mutex_attributes, void *  mutex_control_address, size_t  mutex_control_size);
int             px5_pthread_mutexattr_setname(pthread_mutexattr_t *  mutex_attributes, const char *  name);
int             px5_pthread_mutexattr_setprotocol(pthread_mutexattr_t *  mutex_attributes, int   protocol);
int             px5_pthread_mutexattr_setpshared(pthread_mutexattr_t *  mutex_attributes, int   process_sharing_designation);
int             px5_pthread_mutexattr_settype(pthread_mutexattr_t *  mutex_attributes, int   type);
int             px5_pthread_once(pthread_once_t  *once_control, void (*init_routine)(void));
int             px5_pthread_partitionpool_allocate(const pthread_partitionpool_t *  partitionpool_handle, void **  allocated_memory, size_t  request_size);
int             px5_pthread_partitionpool_allocate_check_params(const pthread_partitionpool_t *  partitionpool_handle, void **  allocated_memory, size_t  request_size);
int             px5_pthread_partitionpool_create(pthread_partitionpool_t *  partitionpool_handle, pthread_partitionpoolattr_t *  partitionpool_attributes, void *  pool_start, size_t  pool_size, size_t partition_size);
int             px5_pthread_partitionpool_create_check_params(pthread_partitionpool_t *  partitionpool_handle, pthread_partitionpoolattr_t *  partitionpool_attributes, void *  pool_start, size_t  pool_size, size_t partition_size);
int             px5_pthread_partitionpool_destroy(pthread_partitionpool_t *  partitionpool_handle);
int             px5_pthread_partitionpool_destroy_check_params(pthread_partitionpool_t *  partitionpool_handle);
int             px5_pthread_partitionpool_free(void *  allocated_memory);
int             px5_pthread_partitionpool_free_check_params(void *  allocated_memory);
int             px5_pthread_partitionpool_information_get(const pthread_partitionpool_t *  partitionpool_handle, char **  name,  u_long *  available_partitions, u_long *  total_partitions, u_long *  partition_size, u_long *  threads_suspended,  pthread_t *first_suspended_thread,  pthread_partitionpool_t *  next_partitionpool_handle);
int             px5_pthread_partitionpool_timedallocate(const pthread_partitionpool_t *  partitionpool_handle, void **  allocated_memory, size_t  request_size, tick_t  timeout_ticks);
int             px5_pthread_partitionpool_timedallocate_check_params(const pthread_partitionpool_t *  partitionpool_handle, void **  allocated_memory, size_t  request_size, tick_t  timeout_ticks);
int             px5_pthread_partitionpool_tryallocate(const pthread_partitionpool_t *  partitionpool_handle, void **  allocated_memory, size_t  request_size);
int             px5_pthread_partitionpool_tryallocate_check_params(const pthread_partitionpool_t *  partitionpool_handle, void **  allocated_memory, size_t  request_size);
int             px5_pthread_partitionpoolattr_destroy(pthread_partitionpoolattr_t *  partitionpool_attributes);
int             px5_pthread_partitionpoolattr_getcontroladdr(const pthread_partitionpoolattr_t *  partitionpool_attributes, void ** partitionpool_control_address);
int             px5_pthread_partitionpoolattr_getcontrolsize(const pthread_partitionpoolattr_t *  partitionpool_attributes, size_t *  partitionpool_control_size);
int             px5_pthread_partitionpoolattr_getname(const pthread_partitionpoolattr_t *  partitionpool_attributes, char ** name);
int             px5_pthread_partitionpoolattr_init(pthread_partitionpoolattr_t *  partitionpool_attributes);
int             px5_pthread_partitionpoolattr_setcontroladdr(pthread_partitionpoolattr_t *  partitionpool_attributes, void *  partitionpool_control_address, size_t  partitionpool_control_size);
int             px5_pthread_partitionpoolattr_setname(pthread_partitionpoolattr_t *  partitionpool_attributes, const char *  name);
int             px5_pthread_priority_change(pthread_t thread_handle, int  new_priority, int *  old_priority);
int             px5_pthread_resume(pthread_t thread_handle);
int             px5_pthread_resume_check_params(pthread_t thread_handle);
pthread_t       px5_pthread_self(void);
#if PX5_MAXIMUM_CORES>1
int             px5_pthread_setaffinity_np(pthread_t  thread_handle,  size_t  cpusetsize, const cpu_set_t  *cpuset);
#endif /* PX5_MAXIMUM_CORES>1  */
int             px5_pthread_setcancelstate(int  new_state, int *  old_state);
int             px5_pthread_setcanceltype(int  new_type, int *  old_type);
int             px5_pthread_setspecific(pthread_key_t  key, const void *  value);
int             px5_pthread_start(u_long run_time_id, void *  memory_start, u_long memory_size);
int             px5_pthread_stack_check(pthread_t thread_handle, u_long *  minimum_available_stack);
int             px5_pthread_suspend(pthread_t thread_handle);
int             px5_pthread_suspend_check_params(pthread_t thread_handle);
void            px5_pthread_testcancel(void);
int             px5_pthread_tick_sleep(tick_t ticks_to_sleep);
tick_t          px5_pthread_ticks_get(void);
int             px5_pthread_ticktimer_create(pthread_ticktimer_t *  ticktimer_handle, pthread_ticktimerattr_t *  attributes, void (* expiration_routine)(pthread_ticktimer_t *, void *), void *  argument, tick_t initial_ticks, tick_t reload_ticks);
int             px5_pthread_ticktimer_create_check_params(pthread_ticktimer_t *  ticktimer_handle, pthread_ticktimerattr_t *  attributes, void (* expiration_routine)(pthread_ticktimer_t *, void *), void *  argument, tick_t initial_ticks, tick_t reload_ticks);
int             px5_pthread_ticktimer_destroy(pthread_ticktimer_t *  ticktimer_handle);
int             px5_pthread_ticktimer_destroy_check_params(pthread_ticktimer_t *  ticktimer_handle);
int             px5_pthread_ticktimer_information_get(const pthread_ticktimer_t *  ticktimer_handle, char **  name, int *  active, tick_t *  remaining_ticks, tick_t *  reload_ticks, pthread_ticktimer_t *  next_ticktimer_handle);
int             px5_pthread_ticktimer_start(const pthread_ticktimer_t *  ticktimer_handle);
int             px5_pthread_ticktimer_start_check_params(const pthread_ticktimer_t *  ticktimer_handle);
int             px5_pthread_ticktimer_stop(const pthread_ticktimer_t *  ticktimer_handle);
int             px5_pthread_ticktimer_stop_check_params(const pthread_ticktimer_t *  ticktimer_handle);
int             px5_pthread_ticktimer_update(const pthread_ticktimer_t *  ticktimer_handle, tick_t  initial_ticks, tick_t  reload_ticks);
int             px5_pthread_ticktimer_update_check_params(const pthread_ticktimer_t *  ticktimer_handle, tick_t  initial_ticks, tick_t  reload_ticks);
int             px5_pthread_ticktimerattr_destroy(pthread_ticktimerattr_t *  ticktimer_attributes);
int             px5_pthread_ticktimerattr_getcontroladdr(const pthread_ticktimerattr_t *  ticktimer_attributes, void **  ticktimer_control_address);
int             px5_pthread_ticktimerattr_getcontrolsize(const pthread_ticktimerattr_t *  ticktimer_attributes, size_t *  ticktimer_control_size);
int             px5_pthread_ticktimerattr_getname(const pthread_ticktimerattr_t *  ticktimer_attributes, char **  name);
int             px5_pthread_ticktimerattr_init(pthread_ticktimerattr_t *  ticktimer_attributes);
int             px5_pthread_ticktimerattr_setcontroladdr(pthread_ticktimerattr_t *  ticktimer_attributes, void *  ticktimer_control_address, size_t  ticktimer_control_size);
int             px5_pthread_ticktimerattr_setname(pthread_ticktimerattr_t *  ticktimer_attributes, const char *  name);
int             px5_pthread_timeslice_change(pthread_t  thread_handle, u_long  new_timeslice, u_long *   previous_timeslice);
int             px5_pthread_timeslice_change_check_params(pthread_t  thread_handle, u_long  new_timeslice, u_long *   previous_timeslice);
void            px5_timer_interrupt_process(void);


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_PTHREAD_HEADER */
