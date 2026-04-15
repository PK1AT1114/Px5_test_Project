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
  

#ifndef PX5_HEADER 
#define PX5_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:    Include Files
   Section II:   Constants, Enumerations, and Macros
   Section III:  Typedefs
   Section IV:   MISRA Prototypes & Macros 
   Section V:    Internal Core Prototypes
   Section VI:   Internal Utility Prototypes
   Section VII:  Internal Error Handling Prototypes
   Section VIII: Binding Function Prototypes
   Section IX:   Middleware Support 


   Note: The px5.h file is only included by the px5.c file, i.e., it is not 
         meant to be included directly by the application software.

******************************************************************************/


/******************************************************************************
 ************************* Section I: Include Files ***************************
 *****************************************************************************/

#include "px5_user_config.h"
#include "px5_binding.h"
#include "px5_time.h"
#include "pthread.h"
#include "sched.h"
#include "mqueue.h"
#include "semaphore.h"
#include "signal.h"
#include "unistd.h"
#include "px5_errno.h"


/******************************************************************************
 ************** Section II: Constants, Enumerations, and Macros ***************
 *****************************************************************************/
 
/* Define this version of PX5.  */

#define PX5_MAJOR_VERSION                                   5U
#define PX5_MINOR_VERSION                                   3U
#define PX5_UPDATE_VERSION                                  0U
#define PX5_PATCH_VERSION                                   0U


/* Define the default maximum number of processors. Since most implementations 
   are for single processors, the default value is 1.  */

#ifndef PX5_MAXIMUM_CORES
#define PX5_MAXIMUM_CORES                                   1
#endif  /* PX5_MAXIMUM_CORES */


/* Define the currently executing core. For all non-SMP versions this is simply 
   mapped to 0.  */

#ifndef PX5_EXECUTING_CORE
#define PX5_EXECUTING_CORE                                  ((int) 0)
#endif  /* PX5_EXECUTING_CORE */


/* Define the natural word size to be 32-bits, e.g., C "int" and "long" types are 
   32-bits. This may be overridden in the px5_binding.h file.  */

#ifndef PX5_NATURAL_WORD_SIZE
#define PX5_NATURAL_WORD_SIZE                               32
#endif  /* PX5_NATURAL_WORD_SIZE */


/* Define the highest active priority when there are ready threads to an invalid priority.  */

#define PX5_NO_READY_THREADS                                (-1)


/* Define default stack size based on minimum binding stack size.  */

#ifndef PX5_DEFAULT_STACK_SIZE
#define PX5_DEFAULT_STACK_SIZE                              (PX5_BINDING_MINIMUM_STACK_SIZE*10UL)
#endif  /* PX5_DEFAULT_STACK_SIZE */


/* Define the stack fill pattern (for byte and for 32-bit word).  */

#ifndef PX5_STACK_FILL
#define PX5_STACK_FILL                                      0xEF
#endif  /* PX5_STACK_FILL */


#ifndef PX5_STACK_FILL_LWORD                    
#define PX5_STACK_FILL_LWORD                                0xEFEFEFEFUL
#endif  /* PX5_STACK_FILL_LWORD */


/* Define the active timer list size.  This can be redefined by the application, but must always be a power of 2.  */

#ifndef PX5_ACTIVE_TIMER_LIST_SIZE
#define PX5_ACTIVE_TIMER_LIST_SIZE                          32UL
#endif  /* PX5_ACTIVE_TIMER_LIST_SIZE */


/* Define the maximum number of cleanup handlers for each thread.  */

#ifndef PX5_MAXIMUM_CLEANUP_HANDLERS
#define PX5_MAXIMUM_CLEANUP_HANDLERS                        3
#endif  /* PX5_MAXIMUM_CLEANUP_HANDLERS */


/* Define NULL pointer constant.  */

#define PX5_NULL                                            ((void *) 0)


/* Define empty list constant.  */

#define PX5_LIST_EMPTY                                      0UL


/* Define preempt/no-preempt constants.  */

#define PX5_PREEMPT                                         1L
#define PX5_NO_PREEMPT                                      0L


/* Define true/false constants.  */

#define PX5_TRUE                                            1L
#define PX5_FALSE                                           0L


/* The following symbol allows the internal source code to mute compiler warnings on unused input parameters. */

#ifndef PX5_UNUSED_PARAMETER
#define PX5_UNUSED_PARAMETER(p)                             ((void)(p));
#endif  /* PX5_UNUSED_PARAMETER  */


/* Define system structure IDs.  */

#define PX5_GLOBALS_ID                                      0x50583520UL
#define PX5_THREAD_ID                                       0x50583554UL  
#define PX5_ATTRIBUTES_ID                                   0x41545452UL
#define PX5_CONDITION_VAR_ID                                0x434F4E56UL
#define PX5_CONDITION_VAR_ATTR_ID                           0x434F4E41UL
#define PX5_EVENT_FLAGS_ID                                  0x4556454EUL
#define PX5_EVENT_FLAGSATTR_ID                              0x45564541UL
#define PX5_FASTQUEUE_ID                                    0x46515545UL
#define PX5_FASTQUEUEATTR_ID                                0x46515541UL
#define PX5_MEMORYPOOL_ID                                   0x4D454D50UL
#define PX5_MEMORYPOOLATTR_ID                               0x4D454D41UL
#define PX5_MUTEX_ID                                        0x4D555458UL
#define PX5_MUTEXATTR_ID                                    0x4D555441UL
#define PX5_PARTITIONPOOL_ID                                0x50415250UL
#define PX5_PARTITIONPOOLATTR_ID                            0x50415241UL
#define PX5_QUEUE_ID                                        0x4D515545UL
#define PX5_DELETED_ID                                      0x44454C20UL
#define PX5_SEMAPHORE_ID                                    0x53454D20UL
#define PX5_TICKTIMER_ID                                    0x54494320UL
#define PX5_TICKTIMER_ATTR_ID                               0x54494345UL


/* Define thread states of execution.  */

#define PX5_THREAD_READY                                    0L
#define PX5_THREAD_RETURNED                                 1L
#define PX5_THREAD_EXITED                                   2L
#define PX5_THREAD_TERMINATED                               3L
#define PX5_THREAD_CANCELED                                 4L 
#define PX5_THREAD_DEFERRED_CLEANUP                         5L
#define PX5_THREAD_DEFERRED_RESUME                          6L
#define PX5_THREAD_SUSPENDED                                7L
#define PX5_THREAD_JOIN_SUSPENDED                           8L
#define PX5_THREAD_CONDITION_VAR_SUSPENDED                  9L
#define PX5_THREAD_MEMORYPOOL_SUSPENDED                     10L
#define PX5_THREAD_MUTEX_SUSPENDED                          11L
#define PX5_THREAD_PARTITIONPOOL_SUSPENDED                  12L
#define PX5_THREAD_QUEUE_SUSPENDED                          13L
#define PX5_THREAD_SEMAPHORE_SUSPENDED                      14L
#define PX5_THREAD_SIGNAL_SUSPENDED                         15L
#define PX5_THREAD_SLEEP_SUSPENDED                          16L
#define PX5_THREAD_TICKSLEEP_SUSPENDED                      17L
#define PX5_THREAD_EVENT_FLAGS_SUSPENDED                    18L
#define PX5_THREAD_FASTQUEUE_SUSPENDED                      19L
#define PX5_THREAD_TCPIP_SUSPENDED                          20L


/* Define internal memory usage types.  */

#define PX5_THREAD_CONTROL_MEMORY                           1UL
#define PX5_THREAD_STACK_MEMORY                             2UL
#define PX5_CONDITION_VAR_CONTROL_MEMORY                    3UL
#define PX5_EVENT_FLAGS_CONTROL_MEMORY                      4UL
#define PX5_FASTQUEUE_CONTROL_MEMORY                        5UL
#define PX5_FASTQUEUE_AREA_MEMORY                           6UL
#define PX5_MEMORYPOOL_CONTROL_MEMORY                       7UL
#define PX5_PARTITIONPOOL_CONTROL_MEMORY                    8UL
#define PX5_MUTEX_CONTROL_MEMORY                            9UL
#define PX5_QUEUE_CONTROL_MEMORY                            10UL
#define PX5_QUEUE_AREA_MEMORY                               11UL
#define PX5_SEMAPHORE_CONTROL_MEMORY                        12UL
#define PX5_TIMER_CONTROL_MEMORY                            13UL
#define PX5_TICKTIMER_CONTROL_MEMORY                        14UL


/* Define the allocated and free memory block constants.  */

#define PX5_BLOCK_ALLOCATED                                 0xAAAAAAAAUL
#define PX5_BLOCK_FREE                                      0xFFFFFFFFUL


/* Define internal system error types.  */

#define PX5_LEVEL_3_ERROR                                   3UL
#define PX5_LEVEL_2_ERROR                                   2UL
#define PX5_LEVEL_1_ERROR                                   1UL


/* Define internal system error sub-types.  */

#define PX5_MEMORY_CORRUPTION                               1UL
#define PX5_INVALID_EXECUTION                               2UL
#define PX5_MISSING_SIGNAL_HANDLER                          3UL
#define PX5_INVALID_API_REQUEST                             4UL
#define PX5_STACK_SIZE_TOO_SMALL                            5UL
#define PX5_STACK_OVERFLOW                                  6UL


/* Define function IDs for tracing and error checking.  */

#define PX5_CLOCK_GETRES_CHECK_PARAMS_ID                    1UL
#define PX5_CLOCK_GETTIME_CHECK_PARAMS_ID                   2UL
#define PX5_CLOCK_SETTIME_CHECK_PARAMS_ID                   3UL
#define PX5_MQ_CLOSE_CHECK_PARAMS_ID                        6UL
#define PX5_MQ_EXTEND_OPEN_CHECK_PARAMS_ID                  7UL
#define PX5_MQ_GETATTR_CHECK_PARAMS_ID                      8UL
#define PX5_MQ_OPEN_CHECK_PARAMS_ID                         9UL
#define PX5_MQ_RECEIVE_CHECK_PARAMS_ID                      10UL
#define PX5_MQ_SEND_CHECK_PARAMS_ID                         11UL
#define PX5_MQ_SETATTR_CHECK_PARAMS_ID                      12UL
#define PX5_MQ_TIMEDRECEIVE_CHECK_PARAMS_ID                 13UL
#define PX5_MQ_TIMEDSEND_CHECK_PARAMS_ID                    14UL
#define PX5_NANOSLEEP_CHECK_PARAMS_ID                       15UL
#define PX5_PTHREAD_COND_BROADCAST_CHECK_PARAMS_ID          16UL
#define PX5_PTHREAD_COND_DESTROY_CHECK_PARAMS_ID            17UL
#define PX5_PTHREAD_COND_INIT_CHECK_PARAMS_ID               18UL
#define PX5_PTHREAD_COND_SIGNAL_CHECK_PARAMS_ID             19UL
#define PX5_PTHREAD_COND_TIMEDWAIT_CHECK_PARAMS_ID          20UL
#define PX5_PTHREAD_COND_WAIT_CHECK_PARAMS_ID               21UL
#define PX5_PTHREAD_CREATE_CHECK_PARAMS_ID                  22UL
#define PX5_PTHREAD_EVENT_FLAGS_CLEAR_CHECK_PARAMS_ID       23UL
#define PX5_PTHREAD_EVENT_FLAGS_CLEARSPECIFIC_CHECK_PARAMS_ID 24UL
#define PX5_PTHREAD_EVENT_FLAGS_CREATE_CHECK_PARAMS_ID      25UL
#define PX5_PTHREAD_EVENT_FLAGS_DESTROY_CHECK_PARAMS_ID     26UL
#define PX5_PTHREAD_EVENT_FLAGS_SET_CHECK_PARAMS_ID         27UL 
#define PX5_PTHREAD_EVENT_FLAGS_TIMEDWAIT_CHECK_PARAMS_ID   28UL
#define PX5_PTHREAD_EVENT_FLAGS_TRYWAIT_CHECK_PARAMS_ID     29UL
#define PX5_PTHREAD_EVENT_FLAGS_WAIT_CHECK_PARAMS_ID        30UL
#define PX5_PTHREAD_FASTQUEUE_CREATE_CHECK_PARAMS_ID        31UL
#define PX5_PTHREAD_FASTQUEUE_DESTROY_CHECK_PARAMS_ID       32UL
#define PX5_PTHREAD_FASTQUEUE_RECEIVE_CHECK_PARAMS_ID       33UL
#define PX5_PTHREAD_FASTQUEUE_SEND_CHECK_PARAMS_ID          34UL
#define PX5_PTHREAD_FASTQUEUE_TIMEDRECEIVE_CHECK_PARAMS_ID  35UL
#define PX5_PTHREAD_FASTQUEUE_TIMEDSEND_CHECK_PARAMS_ID     36UL
#define PX5_PTHREAD_FASTQUEUE_TRYRECEIVE_CHECK_PARAMS_ID    37UL
#define PX5_PTHREAD_FASTQUEUE_TRYSEND_CHECK_PARAMS_ID       38UL
#define PX5_PTHREAD_JOIN_CHECK_PARAMS_ID                    39UL
#define PX5_PTHREAD_KILL_CHECK_PARAMS_ID                    40UL
#define PX5_PTHREAD_MEMORYPOOL_ALLOCATE_CHECK_PARAMS_ID     41UL
#define PX5_PTHREAD_MEMORYPOOL_CREATE_CHECK_PARAMS_ID       42UL
#define PX5_PTHREAD_MEMORYPOOL_DESTROY_CHECK_PARAMS_ID      43UL
#define PX5_PTHREAD_MEMORYPOOL_FREE_CHECK_PARAMS_ID         44UL
#define PX5_PTHREAD_MEMORYPOOL_TIMEDALLOCATE_CHECK_PARAMS_ID 45UL
#define PX5_PTHREAD_MEMORYPOOL_TRYALLOCATE_CHECK_PARAMS_ID  46UL
#define PX5_PTHREAD_MUTEX_DESTROY_CHECK_PARAMS_ID           47UL
#define PX5_PTHREAD_MUTEX_INIT_CHECK_PARAMS_ID              48UL
#define PX5_PTHREAD_MUTEX_LOCK_CHECK_PARAMS_ID              49UL
#define PX5_PTHREAD_MUTEX_TRYLOCK_CHECK_PARAMS_ID           50UL
#define PX5_PTHREAD_MUTEX_UNLOCK_CHECK_PARAMS_ID            51UL
#define PX5_PTHREAD_PARTITIONPOOL_ALLOCATE_CHECK_PARAMS_ID  52UL
#define PX5_PTHREAD_PARTITIONPOOL_CREATE_CHECK_PARAMS_ID    53UL
#define PX5_PTHREAD_PARTITIONPOOL_DESTROY_CHECK_PARAMS_ID   54UL
#define PX5_PTHREAD_PARTITIONPOOL_FREE_CHECK_PARAMS_ID      55UL
#define PX5_PTHREAD_PARTITIONPOOL_TIMEDALLOCATE_CHECK_PARAMS_ID 56UL
#define PX5_PTHREAD_PARTITIONPOOL_TRYALLOCATE_CHECK_PARAMS_ID   57UL
#define PX5_PTHREAD_RESUME_CHECK_PARAMS_ID                  58UL
#define PX5_PTHREAD_SIGMASK_CHECK_PARAMS_ID                 59UL
#define PX5_PTHREAD_SUSPEND_CHECK_PARAMS_ID                 60UL
#define PX5_PTHREAD_TICKTIMER_CREATE_CHECK_PARAMS_ID        61UL
#define PX5_PTHREAD_TICKTIMER_DESTROY_CHECK_PARAMS_ID       62UL
#define PX5_PTHREAD_TICKTIMER_START_CHECK_PARAMS_ID         63UL
#define PX5_PTHREAD_TICKTIMER_STOP_CHECK_PARAMS_ID          64UL
#define PX5_PTHREAD_TICKTIMER_UPDATE_CHECK_PARAMS_ID        65UL
#define PX5_PTHREAD_TIMESLICE_CHANGE_CHECK_PARAMS_ID        66UL
#define PX5_SCHED_YIELD_CHECK_PARAMS_ID                     67UL
#define PX5_SEM_DESTROY_CHECK_PARAMS_ID                     68UL
#define PX5_SEM_EXTEND_INIT_CHECK_PARAMS_ID                 69UL
#define PX5_SEM_INIT_CHECK_PARAMS_ID                        70UL
#define PX5_SEM_POST_CHECK_PARAMS_ID                        71UL
#define PX5_SEM_TICKWAIT_CHECK_PARAMS_ID                    72UL
#define PX5_SEM_TIMEDWAIT_CHECK_PARAMS_ID                   73UL
#define PX5_SEM_TRYWAIT_CHECK_PARAMS_ID                     74UL
#define PX5_SEM_WAIT_CHECK_PARAMS_ID                        75UL
#define PX5_SIGTIMEDWAIT_CHECK_PARAMS_ID                    76UL
#define PX5_SIGWAIT_CHECK_PARAMS_ID                         77UL
#define PX5_SIGWAITINFO_CHECK_PARAMS_ID                     78UL

#define PX5_CLOCK_GETRES_ID                                 1000UL
#define PX5_CLOCK_GETTIME_ID                                1001UL
#define PX5_CLOCK_SETTIME_ID                                1002UL
#define PX5_ERRNO_GET_ID                                    1003UL
#define PX5_ERRNO_SET_ID                                    1004UL
#define PX5_MQ_CLOSE_ID                                     1005UL
#define PX5_MQ_EXTEND_OPEN_ID                               1006UL
#define PX5_MQ_EXTENDATTR_DESTROY_ID                        1007UL
#define PX5_MQ_EXTENDATTR_GETCONTROLADDR_ID                 1008UL
#define PX5_MQ_EXTENDATTR_GETCONTROLSIZE_ID                 1009UL
#define PX5_MQ_EXTENDATTR_GETQUEUEADDR_ID                   1010UL
#define PX5_MQ_EXTENDATTR_GETQUEUESIZE_ID                   1011UL
#define PX5_MQ_EXTENDATTR_INIT_ID                           1012UL
#define PX5_MQ_EXTENDATTR_SETCONTROLADDR_ID                 1013UL
#define PX5_MQ_EXTENDATTR_SETQUEUEADDR_ID                   1014UL
#define PX5_MQ_GETATTR_ID                                   1015UL
#define PX5_MQ_INFORMATION_GET_ID                           1016UL
#define PX5_MQ_OPEN_ID                                      1017UL
#define PX5_MQ_RECEIVE_ID                                   1018UL
#define PX5_MQ_SEND_ID                                      1019UL
#define PX5_MQ_SEND_NOTIFY_ID                               1020UL
#define PX5_MQ_SETATTR_ID                                   1021UL
#define PX5_MQ_TIMEDRECEIVE_ID                              1022UL
#define PX5_MQ_TIMEDSEND_ID                                 1023UL
#define PX5_NANOSLEEP_ID                                    1024UL
#define PX5_PTHREAD_ATTR_GETAFFINITY_ID                     1025UL
#define PX5_PTHREAD_ATTR_GETAUTOSTART_ID                    1026UL
#define PX5_PTHREAD_ATTR_GETCONTROLADDR_ID                  1027UL
#define PX5_PTHREAD_ATTR_GETCONTROLSIZE_ID                  1028UL
#define PX5_PTHREAD_ATTR_DESTROY_ID                         1029UL
#define PX5_PTHREAD_ATTR_GETDETACHSTATE_ID                  1030UL
#define PX5_PTHREAD_ATTR_GETNAME_ID                         1031UL
#define PX5_PTHREAD_ATTR_GETPRIORITY_ID                     1032UL
#define PX5_PTHREAD_ATTR_GETSTACKADDR_ID                    1033UL
#define PX5_PTHREAD_ATTR_GETSTACKSIZE_ID                    1034UL 
#define PX5_PTHREAD_ATTR_GETTIMESLICE_ID                    1035UL
#define PX5_PTHREAD_ATTR_INIT_ID                            1036UL
#define PX5_PTHREAD_ATTR_SETAFFINITY_ID                     1037UL
#define PX5_PTHREAD_ATTR_SETAUTOSTART_ID                    1038UL
#define PX5_PTHREAD_ATTR_SETCONTROLADDR_ID                  1039UL
#define PX5_PTHREAD_ATTR_SETDETACHSTATE_ID                  1040UL
#define PX5_PTHREAD_ATTR_SETNAME_ID                         1041UL
#define PX5_PTHREAD_ATTR_SETPRIORITY_ID                     1042UL
#define PX5_PTHREAD_ATTR_SETSTACKADDR_ID                    1043UL
#define PX5_PTHREAD_ATTR_SETSTACKSIZE_ID                    1044UL
#define PX5_PTHREAD_ATTR_SETTIMESLICE_ID                    1045UL
#define PX5_PTHREAD_CANCEL_ID                               1046UL
#define PX5_PTHREAD_CLEANUP_POP_ID                          1047UL
#define PX5_PTHREAD_CLEANUP_PUSH_ID                         1048UL 
#define PX5_PTHREAD_COND_BROADCAST_ID                       1049UL 
#define PX5_PTHREAD_COND_DESTROY_ID                         1050UL
#define PX5_PTHREAD_COND_INFORMATION_GET_ID                 1051UL
#define PX5_PTHREAD_COND_INIT_ID                            1052UL
#define PX5_PTHREAD_COND_SIGNAL_ID                          1053UL
#define PX5_PTHREAD_COND_TIMEDWAIT_ID                       1054UL
#define PX5_PTHREAD_COND_WAIT_ID                            1055UL
#define PX5_PTHREAD_CONDATTR_DESTROY_ID                     1056UL
#define PX5_PTHREAD_CONDATTR_GETCONTROLADDR_ID              1057UL
#define PX5_PTHREAD_CONDATTR_GETCONTROLSIZE_ID              1058UL
#define PX5_PTHREAD_CONDATTR_GETNAME_ID                     1059UL
#define PX5_PTHREAD_CONDATTR_GETPSHARED_ID                  1060UL
#define PX5_PTHREAD_CONDATTR_INIT_ID                        1061UL
#define PX5_PTHREAD_CONDATTR_SETCONTROLADDR_ID              1062UL
#define PX5_PTHREAD_CONDATTR_SETNAME_ID                     1063UL
#define PX5_PTHREAD_CONDATTR_SETPSHARED_ID                  1064UL
#define PX5_PTHREAD_CREATE_ID                               1065UL
#define PX5_PTHREAD_DETACH_ID                               1066UL
#define PX5_PTHREAD_EQUAL_ID                                1067UL
#define PX5_PTHREAD_EVENT_FLAGS_CLEAR_ID                    1068UL
#define PX5_PTHREAD_EVENT_FLAGS_CLEARSPECIFIC_ID            1069UL
#define PX5_PTHREAD_EVENT_FLAGS_CREATE_ID                   1070UL
#define PX5_PTHREAD_EVENT_FLAGS_DESTROY_ID                  1071UL
#define PX5_PTHREAD_EVENT_FLAGS_INFORMATION_GET_ID          1072UL
#define PX5_PTHREAD_EVENT_FLAGS_SET_ID                      1073UL
#define PX5_PTHREAD_EVENT_FLAGS_SET_NOTIFY_ID               1074UL
#define PX5_PTHREAD_EVENT_FLAGS_TIMEDWAIT_ID                1075UL
#define PX5_PTHREAD_EVENT_FLAGS_TRYWAIT_ID                  1076UL
#define PX5_PTHREAD_EVENT_FLAGS_WAIT_ID                     1077UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_DESTROY_ID              1078UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_GETAUTOCONSUMEMASK_ID   1079UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_GETCONTROLADDR_ID       1080UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_GETCONTROLSIZE_ID       1081UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_GETNAME_ID              1082UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_INIT_ID                 1083UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_SETAUTOCONSUMEMASK_ID   1084UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_SETCONTROLADDR_ID       1085UL
#define PX5_PTHREAD_EVENT_FLAGSATTR_SETNAME_ID              1086UL
#define PX5_PTHREAD_EXIT_ID                                 1087UL
#define PX5_PTHREAD_FASTQUEUE_CREATE_ID                     1088UL
#define PX5_PTHREAD_FASTQUEUE_DESTROY_ID                    1089UL
#define PX5_PTHREAD_FASTQUEUE_INFORMATION_GET_ID            1090UL
#define PX5_PTHREAD_FASTQUEUE_RECEIVE_ID                    1091UL
#define PX5_PTHREAD_FASTQUEUE_SEND_ID                       1092UL
#define PX5_PTHREAD_FASTQUEUE_SEND_NOTIFY_ID                1093UL
#define PX5_PTHREAD_FASTQUEUE_TIMEDRECEIVE_ID               1094UL
#define PX5_PTHREAD_FASTQUEUE_TIMEDSEND_ID                  1095UL
#define PX5_PTHREAD_FASTQUEUE_TRYRECEIVE_ID                 1096UL
#define PX5_PTHREAD_FASTQUEUE_TRYSEND_ID                    1097UL
#define PX5_PTHREAD_FASTQUEUEATTR_DESTROY_ID                1098UL
#define PX5_PTHREAD_FASTQUEUEATTR_GETCONTROLADDR_ID         1099UL
#define PX5_PTHREAD_FASTQUEUEATTR_GETCONTROLSIZE_ID         1100UL
#define PX5_PTHREAD_FASTQUEUEATTR_GETNAME_ID                1101UL
#define PX5_PTHREAD_FASTQUEUEATTR_GETQUEUEADDR_ID           1102UL
#define PX5_PTHREAD_FASTQUEUEATTR_GETQUEUESIZE_ID           1103UL
#define PX5_PTHREAD_FASTQUEUEATTR_INIT_ID                   1104UL
#define PX5_PTHREAD_FASTQUEUEATTR_SETCONTROLADDR_ID         1105UL
#define PX5_PTHREAD_FASTQUEUEATTR_SETNAME_ID                1106UL
#define PX5_PTHREAD_FASTQUEUEATTR_SETQUEUEADDR_ID           1107UL
#if PX5_MAXIMUM_CORES>1
#define PX5_PTHREAD_GETAFFINITY_NP_ID                       1108UL
#endif /* PX5_MAXIMUM_CORES>1  */
#define PX5_PTHREAD_GETSPECIFIC_ID                          1109UL
#define PX5_PTHREAD_INFORMATION_GET_ID                      1110UL
#define PX5_PTHREAD_JOIN_ID                                 1111UL
#define PX5_PTHREAD_KEY_CREATE_ID                           1112UL
#define PX5_PTHREAD_KEY_DELETE_ID                           1113UL
#define PX5_PTHREAD_KILL_ID                                 1114UL
#define PX5_PTHREAD_MEMORY_MANAGER_ENABLE_ID                1115UL
#define PX5_PTHREAD_MEMORY_MANAGER_GET_ID                   1116UL
#define PX5_PTHREAD_MEMORY_MANAGER_SET_ID                   1117UL
#define PX5_PTHREAD_MEMORYPOOL_ALLOCATE_ID                  1118UL
#define PX5_PTHREAD_MEMORYPOOL_CREATE_ID                    1119UL
#define PX5_PTHREAD_MEMORYPOOL_DESTROY_ID                   1120UL
#define PX5_PTHREAD_MEMORYPOOL_INFORMATION_GET_ID           1121UL
#define PX5_PTHREAD_MEMORYPOOL_FREE_ID                      1122UL
#define PX5_PTHREAD_MEMORYPOOL_TIMEDALLOCATE_ID             1123UL
#define PX5_PTHREAD_MEMORYPOOL_TRYALLOCATE_ID               1124UL
#define PX5_PTHREAD_MEMORYPOOLATTR_DESTROY_ID               1125UL
#define PX5_PTHREAD_MEMORYPOOLATTR_GETCONTROLADDR_ID        1126UL
#define PX5_PTHREAD_MEMORYPOOLATTR_GETCONTROLSIZE_ID        1127UL
#define PX5_PTHREAD_MEMORYPOOLATTR_GETNAME_ID               1128UL
#define PX5_PTHREAD_MEMORYPOOLATTR_INIT_ID                  1129UL
#define PX5_PTHREAD_MEMORYPOOLATTR_SETCONTROLADDR_ID        1130UL
#define PX5_PTHREAD_MEMORYPOOLATTR_SETNAME_ID               1131UL
#define PX5_PTHREAD_MUTEX_DESTROY_ID                        1132UL
#define PX5_PTHREAD_MUTEX_INFORMATION_GET_ID                1133UL
#define PX5_PTHREAD_MUTEX_INIT_ID                           1134UL
#define PX5_PTHREAD_MUTEX_LOCK_ID                           1135UL
#define PX5_PTHREAD_MUTEX_TRYLOCK_ID                        1136UL
#define PX5_PTHREAD_MUTEX_UNLOCK_ID                         1137UL
#define PX5_PTHREAD_MUTEXATTR_DESTROY_ID                    1138UL
#define PX5_PTHREAD_MUTEXATTR_GETCONTROLADDR_ID             1139UL
#define PX5_PTHREAD_MUTEXATTR_GETCONTROLSIZE_ID             1140UL
#define PX5_PTHREAD_MUTEXATTR_GETNAME_ID                    1141UL
#define PX5_PTHREAD_MUTEXATTR_GETPROTOCOL_ID                1142UL
#define PX5_PTHREAD_MUTEXATTR_GETPSHARED_ID                 1143UL
#define PX5_PTHREAD_MUTEXATTR_GETTYPE_ID                    1144UL
#define PX5_PTHREAD_MUTEXATTR_INIT_ID                       1145UL
#define PX5_PTHREAD_MUTEXATTR_SETCONTROLADDR_ID             1146UL
#define PX5_PTHREAD_MUTEXATTR_SETNAME_ID                    1147UL
#define PX5_PTHREAD_MUTEXATTR_SETPROTOCOL_ID                1148UL
#define PX5_PTHREAD_MUTEXATTR_SETPSHARED_ID                 1149UL
#define PX5_PTHREAD_MUTEXATTR_SETTYPE_ID                    1150UL
#define PX5_PTHREAD_ONCE_ID                                 1151UL
#define PX5_PTHREAD_PARTITIONPOOL_ALLOCATE_ID               1152UL
#define PX5_PTHREAD_PARTITIONPOOL_CREATE_ID                 1153UL
#define PX5_PTHREAD_PARTITIONPOOL_DESTROY_ID                1154UL
#define PX5_PTHREAD_PARTITIONPOOL_FREE_ID                   1155UL
#define PX5_PTHREAD_PARTITIONPOOL_INFORMATION_GET_ID        1156UL
#define PX5_PTHREAD_PARTITIONPOOL_TIMEDALLOCATE_ID          1157UL
#define PX5_PTHREAD_PARTITIONPOOL_TRYALLOCATE_ID            1158UL
#define PX5_PTHREAD_PARTITIONPOOLATTR_DESTROY_ID            1159UL
#define PX5_PTHREAD_PARTITIONPOOLATTR_GETCONTROLADDR_ID     1160UL
#define PX5_PTHREAD_PARTITIONPOOLATTR_GETCONTROLSIZE_ID     1161UL
#define PX5_PTHREAD_PARTITIONPOOLATTR_GETNAME_ID            1162UL
#define PX5_PTHREAD_PARTITIONPOOLATTR_INIT_ID               1163UL
#define PX5_PTHREAD_PARTITIONPOOLATTR_SETCONTROLADDR_ID     1164UL
#define PX5_PTHREAD_PARTITIONPOOLATTR_SETNAME_ID            1165UL
#define PX5_PTHREAD_PRIORITY_CHANGE_ID                      1166UL
#define PX5_PTHREAD_RESUME_ID                               1167UL
#define PX5_PTHREAD_SELF_ID                                 1168UL
#if PX5_MAXIMUM_CORES>1
#define PX5_PTHREAD_SETAFFINITY_NP_ID                       1169UL
#endif /* PX5_MAXIMUM_CORES>1  */
#define PX5_PTHREAD_SETCANCELSTATE_ID                       1170UL
#define PX5_PTHREAD_SETCANCELTYPE_ID                        1171UL
#define PX5_PTHREAD_SETSPECIFIC_ID                          1172UL
#define PX5_PTHREAD_SIGMASK_ID                              1173UL
#define PX5_PTHREAD_STACK_CHECK_ID                          1174UL
#define PX5_PTHREAD_START_ID                                1175UL
#define PX5_PTHREAD_SUSPEND_ID                              1176UL
#define PX5_PTHREAD_TESTCANCEL_ID                           1177UL
#define PX5_PTHREAD_TICK_SLEEP_ID                           1178UL
#define PX5_PTHREAD_TICKS_GET_ID                            1179UL
#define PX5_PTHREAD_TICKTIMER_CREATE_ID                     1180UL
#define PX5_PTHREAD_TICKTIMER_DESTROY_ID                    1181UL
#define PX5_PTHREAD_TICKTIMER_INFORMATION_GET_ID            1182UL
#define PX5_PTHREAD_TICKTIMER_START_ID                      1183UL
#define PX5_PTHREAD_TICKTIMER_STOP_ID                       1184UL
#define PX5_PTHREAD_TICKTIMER_UPDATE_ID                     1185UL
#define PX5_PTHREAD_TICKTIMERATTR_DESTROY_ID                1186UL
#define PX5_PTHREAD_TICKTIMERATTR_GETCONTROLADDR_ID         1187UL
#define PX5_PTHREAD_TICKTIMERATTR_GETCONTROLSIZE_ID         1188UL
#define PX5_PTHREAD_TICKTIMERATTR_GETNAME_ID                1189UL
#define PX5_PTHREAD_TICKTIMERATTR_INIT_ID                   1190UL
#define PX5_PTHREAD_TICKTIMERATTR_SETCONTROLADDR_ID         1191UL
#define PX5_PTHREAD_TICKTIMERATTR_SETNAME_ID                1192UL
#define PX5_PTHREAD_TIMESLICE_CHANGE_ID                     1193UL
#define PX5_SCHED_YIELD_ID                                  1194UL
#define PX5_SEM_DESTROY_ID                                  1195UL
#define PX5_SEM_EXTEND_INIT_ID                              1196UL
#define PX5_SEM_INFORMATION_GET_ID                          1197UL
#define PX5_SEM_INIT_ID                                     1198UL
#define PX5_SEM_POST_ID                                     1199UL
#define PX5_SEM_POST_NOTIFY_ID                              1200UL
#define PX5_SEM_TICKWAIT_ID                                 1201UL
#define PX5_SEM_TIMEDWAIT_ID                                1202UL
#define PX5_SEM_TRYWAIT_ID                                  1203UL
#define PX5_SEM_WAIT_ID                                     1204UL
#define PX5_SEMATTR_DESTROY_ID                              1205UL
#define PX5_SEMATTR_GETCONTROLADDR_ID                       1206UL  
#define PX5_SEMATTR_GETCONTROLSIZE_ID                       1207UL
#define PX5_SEMATTR_GETNAME_ID                              1208UL
#define PX5_SEMATTR_INIT_ID                                 1209UL  
#define PX5_SEMATTR_SETCONTROLADDR_ID                       1210UL
#define PX5_SEMATTR_SETNAME_ID                              1211UL
#define PX5_SIGACTION_ID                                    1212UL 
#define PX5_SIGADDSET_ID                                    1213UL
#define PX5_SIGDELSET_ID                                    1214UL
#define PX5_SIGEMPTYSET_ID                                  1215UL
#define PX5_SIGFILLSET_ID                                   1216UL
#define PX5_SIGISMEMBER_ID                                  1217UL  
#define PX5_SIGPENDING_ID                                   1218UL
#define PX5_SIGTIMEDWAIT_ID                                 1219UL
#define PX5_SIGWAIT_ID                                      1220UL
#define PX5_SIGWAITINFO_ID                                  1221UL
#define PX5_SLEEP_ID                                        1222UL    
#define PX5_TIME_ID                                         1223UL
#define PX5_TIMER_INTERRUPT_PROCESS_ID                      1224UL
#define PX5_USLEEP_ID                                       1225UL

#define PX5_INTERNAL_CENTRAL_ERROR_ID                       2000UL
#define PX5_INTERNAL_FILE_CLOSE_ROUTINE_ERROR               2001UL
#define PX5_INTERNAL_FILE_READ_ROUTINE_ERROR                2002UL
#define PX5_INTERNAL_FILE_WRITE_ROUTINE_ERROR               2003UL
#define PX5_INTERNAL_FUNCTION_CALL_FAILED                   2004UL
#define PX5_INTERNAL_HIGHEST_SET_BIT_GET_ID                 2005UL
#define PX5_INTERNAL_ISR_ENTER_ID                           2006UL
#define PX5_INTERNAL_ISR_EXIT_ID                            2007UL
#define PX5_INTERNAL_MEMORY_ALLOCATE_ID                     2008UL
#define PX5_INTERNAL_MEMORY_MANAGER_ALLOCATE_ID             2009UL
#define PX5_INTERNAL_MEMORY_MANAGER_RELEASE_ID              2010UL
#define PX5_INTERNAL_NET_CLOSE_ROUTINE_ERROR                2011UL
#define PX5_INTERNAL_NET_READ_ROUTINE_ERROR                 2012UL
#define PX5_INTERNAL_NET_WRITE_ROUTINE_ERROR                2013UL
#define PX5_INTERNAL_THREAD_ENTER_ID                        2014UL
#define PX5_INTERNAL_THREAD_EXIT_ID                         2015UL
#define PX5_INTERNAL_THREAD_PRIORITY_CHANGE_ID              2016UL
#define PX5_INTERNAL_THREAD_READY_ID                        2017UL
#define PX5_INTERNAL_THREAD_SUSPEND_ID                      2018UL
#define PX5_INTERNAL_THREAD_SWITCH_TO                       2019UL
#define PX5_INTERNAL_THREAD_SWITCH_FROM                     2020UL
#define PX5_INTERNAL_THREAD_TIMER_PROCESS_ID                2021UL 
#define PX5_INTERNAL_THREAD_WRAPPER_ID                      2022UL
#define PX5_INTERNAL_TICKTIMER_EXPIRE_ID                    2023UL
#define PX5_INTERNAL_TIME_SLICE_PROCESS_ID                  2024UL
#define PX5_INTERNAL_TIMER_ACTIVATE_ID                      2025UL
#define PX5_INTERNAL_TIMER_DEACTIVATE_ID                    2026UL
#define PX5_INTERNAL_TIMER_LIST_PROCESS_ID                  2027UL
#define PX5_INTERNAL_CLEANUP_HANDLERS_EXECUTE_ID            2028UL
#define PX5_INTERNAL_THREAD_DEFERRED_MEMORY_RELEASE_ID      2029UL


/* Define internal system error identification codes that indicate where the error occurred.  */

#define PX5_CONDITION_VAR_OBJECT_CORRUPTION_ERROR           3001UL
#define PX5_EVENT_FLAGS_OBJECT_CORRUPTION_ERROR             3002UL
#define PX5_GLOBAL_OBJECT_CORRUPTION_ERROR                  3003UL
#define PX5_INTERNAL_THREAD_INVALID_RETURN_ERROR            3004UL
#define PX5_INTERNAL_THREAD_DEFERRED_MEM_RELEASE_ERROR      3005UL
#define PX5_INTERNAL_THREAD_DEFERRED_MEM_RELEASE_ERROR1     3006UL
#define PX5_INTERNAL_THREAD_WRAPPER_ERROR                   3007UL
#define PX5_INTERNAL_THREAD_WRAPPER_ERROR1                  3008UL
#define PX5_INTERNAL_TICKTIMER_EXPIRE_ERROR                 3009UL
#define PX5_INTERNAL_TIMER_LIST_PROCESS_ERROR               3010UL
#define PX5_MEMORYPOOL_FRAGMENT_CORRUPTION_ERROR            3011UL
#define PX5_MUTEX_OBJECT_CORRUPTION_ERROR                   3012UL
#define PX5_PARTITIONPOOL_OBJECT_CORRUPTION_ERROR           3013UL
#define PX5_PARTITIONPOOL_CORRUPTION_ERROR                  3014UL
#define PX5_QUEUE_CLOSE_ERROR                               3015UL
#define PX5_QUEUE_CLOSE_ERROR1                              3016UL
#define PX5_QUEUE_OBJECT_CORRUPTION_ERROR                   3017UL
#define PX5_QUEUE_OPEN_ERROR                                3018UL
#define PX5_QUEUE_OPEN_ERROR1                               3019UL
#define PX5_PTHREAD_CANCEL_ERROR                            3020UL
#define PX5_PTHREAD_CANCEL_ERROR1                           3021UL
#define PX5_PTHREAD_CLEANUP_POP_ERROR                       3022UL
#define PX5_PTHREAD_COND_DESTROY_ERROR                      3023UL
#define PX5_PTHREAD_COND_INIT_ERROR                         3024UL
#define PX5_PTHREAD_COND_INIT_ERROR1                        3025UL
#define PX5_PTHREAD_CREATE_ERROR                            3026UL
#define PX5_PTHREAD_CREATE_ERROR1                           3027UL
#define PX5_PTHREAD_EVENT_FLAGS_CREATE_ERROR                3028UL
#define PX5_PTHREAD_EVENT_FLAGS_CREATE_ERROR1               3029UL
#define PX5_PTHREAD_EVENT_FLAGS_DESTROY_ERROR               3030UL
#define PX5_PTHREAD_EXIT_ERROR                              3031UL
#define PX5_PTHREAD_FASTQUEUE_CREATE_ERROR                  3032UL
#define PX5_PTHREAD_FASTQUEUE_CREATE_ERROR1                 3033UL
#define PX5_PTHREAD_FASTQUEUE_DESTROY_ERROR                 3034UL
#define PX5_PTHREAD_FASTQUEUE_DESTROY_ERROR1                3035UL
#define PX5_FASTQUEUE_OBJECT_CORRUPTION_ERROR               3036UL
#define PX5_PTHREAD_JOIN_ERROR                              3037UL
#define PX5_PTHREAD_JOIN_ERROR1                             3038UL
#define PX5_PTHREAD_KILL_ERROR                              3039UL
#define PX5_PTHREAD_KILL_ERROR1                             3040UL
#define PX5_PTHREAD_MEMORY_MANAGER_GET_ERROR                3041UL
#define PX5_PTHREAD_MEMORY_MANAGER_GET_ERROR1               3042UL
#define PX5_PTHREAD_MEMORYPOOL_CREATE_ERROR                 3043UL
#define PX5_PTHREAD_MEMORYPOOL_CREATE_ERROR1                3044UL
#define PX5_PTHREAD_MEMORYPOOL_DESTROY_ERROR                3045UL
#define PX5_PTHREAD_MUTEX_DESTROY_ERROR                     3046UL
#define PX5_PTHREAD_MUTEX_INIT_ERROR                        3047UL
#define PX5_PTHREAD_MUTEX_INIT_ERROR1                       3048UL
#define PX5_PTHREAD_PARTITIONPOOL_CREATE_ERROR              3049UL
#define PX5_PTHREAD_PARTITIONPOOL_CREATE_ERROR1             3050UL
#define PX5_PTHREAD_PARTITIONPOOL_DESTROY_ERROR             3051UL
#define PX5_PTHREAD_SIGMASK_ERROR                           3052UL
#define PX5_PTHREAD_SIGMASK_ERROR1                          3053UL
#define PX5_PTHREAD_TICKTIMER_CREATE_ERROR                  3054UL
#define PX5_PTHREAD_TICKTIMER_CREATE_ERROR1                 3055UL
#define PX5_PTHREAD_TICKTIMER_DESTROY_ERROR                 3056UL
#define PX5_SEM_DESTROY_ERROR                               3057UL
#define PX5_SEM_EXTEND_INIT_ERROR                           3058UL
#define PX5_SEM_EXTEND_INIT_ERROR1                          3059UL
#define PX5_SEM_INIT_ERROR                                  3060UL
#define PX5_SEM_INIT_ERROR1                                 3061UL
#define PX5_MEMORYPOOL_OBJECT_CORRUPTION_ERROR              3062UL
#define PX5_SEMAPHORE_OBJECT_CORRUPTION_ERROR               3063UL
#define PX5_THREAD_OBJECT_CORRUPTION_ERROR                  3064UL
#define PX5_TICKTIMER_OBJECT_CORRUPTION_ERROR               3065UL
#define PX5_SEM_POST_NOTIFY_ERROR                           3066UL
#define PX5_EVENT_FLAGS_SET_NOTIFY_ERROR                    3067UL
#define PX5_FASTQUEUE_SEND_NOTIFY_ERROR                     3068UL
#define PX5_QUEUE_SEND_NOTIFY_ERROR                         3069UL
#define PX5_PTHREAD_KEY_ERROR                               3070UL


/* Default internal system error processing to white-space.  */

#ifndef PX5_LEVEL_3_ERROR_PROCESSING
#define PX5_LEVEL_3_ERROR_PROCESSING
#endif  /* PX5_LEVEL_3_ERROR_PROCESSING */

#ifndef PX5_LEVEL_2_ERROR_PROCESSING
#define PX5_LEVEL_2_ERROR_PROCESSING
#endif  /* PX5_LEVEL_2_ERROR_PROCESSING */

#ifndef PX5_LEVEL_1_ERROR_PROCESSING
#define PX5_LEVEL_1_ERROR_PROCESSING
#endif  /* PX5_LEVEL_1_ERROR_PROCESSING */


/* Default memory copy routine to internal utility.  */

#ifndef MEMCPY
#define MEMCPY(destination, source, bytes_to_copy)          px5_internal_memcpy((destination), (source), (bytes_to_copy));
#endif  /* MEMCPY */


/* Default memory set routine to internal utility.  */

#ifndef MEMSET
#define MEMSET(destination, value, bytes_to_set)            px5_internal_memset((destination), (value), (bytes_to_set));
#endif  /* MEMSET */


/* Define bit map manipulation macros.  */  

#ifndef PX5_MAXIMUM_BITS
#define PX5_MAXIMUM_BITS                                    32UL
#endif

#ifndef PX5_BIT_SET
#define PX5_BIT_SET(w,b)                                    (w) =  (w) | (((u_long) 1UL) << (b))
#endif  /* PX5_BIT_SET */

#ifndef PX5_BIT_CLEAR
#define PX5_BIT_CLEAR(w,b)                                  (w) =  (w) & ~(((u_long) 1UL) << (b))
#endif  /* PX5_BIT_CLEAR */

#ifndef PX5_ANY_BIT_SET 
#define PX5_ANY_BIT_SET(w)                                  (w)
#endif  /* PX5_ANY_BIT_SET */

#ifndef PX5_HIGHEST_BIT_SET_GET
#define PX5_HIGHEST_BIT_SET_GET(b,w)                        (b) = px5_internal_highest_set_bit_get((w));
#endif  /* PX5_HIGHEST_BIT_SET_GET */            


/* Define interrupt nesting level macro that is used to determine if processing is in an interrupt context.   */

#ifndef PX5_INTERRUPT_LEVEL_GET
#define PX5_INTERRUPT_LEVEL_GET(l)                          l =  px5_globals.interrupt_nesting_level[PX5_EXECUTING_CORE];
#endif


/* Define Pointer\Data Verification Code computation, which can be overridden by the application.  */

#ifndef PX5_POINTER_DATA_VERIFY_CODE_COMPUTE
#define PX5_POINTER_DATA_VERIFY_CODE_COMPUTE(a, b)          (((a) + (b)) ^ px5_globals.run_time_id)
#endif  /* PX5_POINTER_DATA_VERIFY_CODE_COMPUTE */


/* Default function pointer verification macros to white-space, unless enabled by the application.  */

#ifndef PX5_FUNCTION_POINTER_VERIFY_ENABLE
#define PX5_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_MEMORY_ALLOCATE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_MEMORY_RELEASE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_CLEANUP_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_CLOSE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_READ_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_WRITE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_SIGNAL_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_EXPIRATION_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_THREAD_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_INTERNAL_TIMER_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_SEMAPHORE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_EVENT_FLAGS_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_FASTQUEUE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_QUEUE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#define PX5_PTHREAD_KEY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)
#else
#ifndef PX5_FUNCTION_POINTER_CODE_ENABLE
#define PX5_FUNCTION_POINTER_CODE_ENABLE
#endif  /* PX5_FUNCTION_POINTER_CODE_ENABLE */
#ifndef PX5_MISRA_ENABLE
#define PX5_FUNCTION_POINTER_CODE_VERIFY(a, b, i)                   px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_MEMORY_ALLOCATE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)   px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_MEMORY_RELEASE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)    px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_CLEANUP_FUNCTION_POINTER_CODE_VERIFY(a, b, i)           px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_CLOSE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)             px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_READ_FUNCTION_POINTER_CODE_VERIFY(a, b, i)              px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_WRITE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)             px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_SIGNAL_FUNCTION_POINTER_CODE_VERIFY(a, b, i)            px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_EXPIRATION_FUNCTION_POINTER_CODE_VERIFY(a, b, i)        px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_THREAD_FUNCTION_POINTER_CODE_VERIFY(a, b, i)            px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_INTERNAL_TIMER_FUNCTION_POINTER_CODE_VERIFY(a, b, i)    px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_SEMAPHORE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)  px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_EVENT_FLAGS_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i) px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_FASTQUEUE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)  px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_QUEUE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)      px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_PTHREAD_KEY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)       px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#else
#define PX5_FUNCTION_POINTER_CODE_VERIFY(a, b, i)                   px5_internal_pointer_verification_code_verify((void *) (a), (b), (i));
#define PX5_MEMORY_ALLOCATE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)   { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_memory_allocate_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_MEMORY_RELEASE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)    { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_memory_release_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_CLEANUP_FUNCTION_POINTER_CODE_VERIFY(a, b, i)           { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_cleanup_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), px5_misra_const_u_long_pointer_convert((b)), (i)); \
                                                                    }
#define PX5_CLOSE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)             { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_close_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_READ_FUNCTION_POINTER_CODE_VERIFY(a, b, i)              { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_read_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_WRITE_FUNCTION_POINTER_CODE_VERIFY(a, b, i)             { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_write_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_SIGNAL_FUNCTION_POINTER_CODE_VERIFY(a, b, i)            { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_signal_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_EXPIRATION_FUNCTION_POINTER_CODE_VERIFY(a, b, i)        { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_expiration_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_THREAD_FUNCTION_POINTER_CODE_VERIFY(a, b, i)            { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_thread_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_INTERNAL_TIMER_FUNCTION_POINTER_CODE_VERIFY(a, b, i)    { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_internal_timer_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_SEMAPHORE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)  { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_semaphore_notify_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_EVENT_FLAGS_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i) { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_event_flags_notify_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_FASTQUEUE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)  { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_fastqueue_notify_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_QUEUE_NOTIFY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)      { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_queue_notify_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#define PX5_PTHREAD_KEY_FUNCTION_POINTER_CODE_VERIFY(a, b, i)       { \
                                                                    void *          pointer;  \
                                                                        pointer =  px5_misra_pthread_key_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_verify((pointer), (b), (i)); \
                                                                    }
#endif  /* PX5_MISRA_ENABLE  */
#endif  /* PX5_FUNCION_POINTER_VERIFY_ENABLE */

#ifndef PX5_FUNCTION_POINTER_CODE_ENABLE
#define PX5_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_MEMORY_ALLOCATE_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_MEMORY_RELEASE_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_CLEANUP_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_CLOSE_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_READ_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_WRITE_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_SIGNAL_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_EXPIRATION_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_THREAD_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_INTERNAL_TIMER_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_SEMAPHORE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_EVENT_FLAGS_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_FASTQUEUE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_QUEUE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)
#define PX5_PTHREAD_KEY_FUNCTION_POINTER_CODE_CREATE(a, b)
#else
#ifndef PX5_MISRA_ENABLE
#define PX5_FUNCTION_POINTER_CODE_CREATE(a, b)                    px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_MEMORY_ALLOCATE_FUNCTION_POINTER_CODE_CREATE(a, b)    px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_MEMORY_RELEASE_FUNCTION_POINTER_CODE_CREATE(a, b)     px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_CLEANUP_FUNCTION_POINTER_CODE_CREATE(a, b)            px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_CLOSE_FUNCTION_POINTER_CODE_CREATE(a, b)              px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_READ_FUNCTION_POINTER_CODE_CREATE(a, b)               px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_WRITE_FUNCTION_POINTER_CODE_CREATE(a, b)              px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_SIGNAL_FUNCTION_POINTER_CODE_CREATE(a, b)             px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_EXPIRATION_FUNCTION_POINTER_CODE_CREATE(a, b)         px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_THREAD_FUNCTION_POINTER_CODE_CREATE(a, b)             px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_INTERNAL_TIMER_FUNCTION_POINTER_CODE_CREATE(a, b)     px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_SEMAPHORE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)   px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_EVENT_FLAGS_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b) px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_FASTQUEUE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)   px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_QUEUE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)       px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_PTHREAD_KEY_FUNCTION_POINTER_CODE_CREATE(a, b)        px5_internal_pointer_verification_code_create((void *) (a), (b));
#else
#define PX5_FUNCTION_POINTER_CODE_CREATE(a, b)                    px5_internal_pointer_verification_code_create((void *) (a), (b));
#define PX5_MEMORY_ALLOCATE_FUNCTION_POINTER_CODE_CREATE(a, b)    { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_memory_allocate_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_MEMORY_RELEASE_FUNCTION_POINTER_CODE_CREATE(a, b)     { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_memory_release_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_CLEANUP_FUNCTION_POINTER_CODE_CREATE(a, b)            { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_cleanup_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_CLOSE_FUNCTION_POINTER_CODE_CREATE(a, b)              { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_close_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_READ_FUNCTION_POINTER_CODE_CREATE(a, b)               { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_read_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_WRITE_FUNCTION_POINTER_CODE_CREATE(a, b)              { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_write_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_SIGNAL_FUNCTION_POINTER_CODE_CREATE(a, b)             { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_signal_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_EXPIRATION_FUNCTION_POINTER_CODE_CREATE(a, b)         { \
                                                                  void *          pointer;  \
                                                                  misra_ticktimer_expiration expiration; \
                                                                  expiration =  px5_misra_ticktimer_expiration_const_convert((a));  \
                                                                  pointer =  px5_misra_expiration_to_void_pointer_convert((expiration)); \
                                                                  px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_THREAD_FUNCTION_POINTER_CODE_CREATE(a, b)             { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_thread_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_INTERNAL_TIMER_FUNCTION_POINTER_CODE_CREATE(a, b)     { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_internal_timer_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_SEMAPHORE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)   { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_semaphore_notify_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_EVENT_FLAGS_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b) { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_event_flags_notify_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_FASTQUEUE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)   { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_fastqueue_notify_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_QUEUE_NOTIFY_FUNCTION_POINTER_CODE_CREATE(a, b)       { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_queue_notify_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#define PX5_PTHREAD_KEY_FUNCTION_POINTER_CODE_CREATE(a, b)        { \
                                                                  void *          pointer;  \
                                                                        pointer =  px5_misra_pthread_key_to_void_pointer_convert((a)); \
                                                                        px5_internal_pointer_verification_code_create((pointer), (b)); \
                                                                  }
#endif  /* PX5_MISRA_ENABLE  */
#endif  /* PX5_FUNCTION_POINTER_CODE_ENABLE */


/* Default memory pool verification macros to white-space, unless enabled by the application.  */

#ifndef PX5_MEMORYPOOL_VERIFY_ENABLE
#define PX5_MEMORYPOOL_CODE_VERIFY(a, b, i)
#else
#ifndef PX5_MEMORYPOOL_CODE_ENABLE
#define PX5_MEMORYPOOL_CODE_ENABLE
#endif  /* PX5_MEMORYPOOL_CODE_ENABLE */
#define PX5_MEMORYPOOL_CODE_VERIFY(a, b, i)                 px5_internal_pointer_verification_code_verify((a), (b), (i));
#endif  /* PX5_MEMORYPOOL_VERIFY_ENABLE */

#ifndef PX5_MEMORYPOOL_CODE_ENABLE
#define PX5_MEMORYPOOL_CODE_CREATE(a, b)
#else
#define PX5_MEMORYPOOL_CODE_CREATE(a, b)                    px5_internal_pointer_verification_code_create((a), (b));
#endif  /* PX5_MEMORYPOOL_CODE_ENABLE */


/* Default object pointer verification macros to white-space, unless enabled by the application.  */

#ifndef PX5_OBJECT_VERIFY_ENABLE
#define PX5_OBJECT_CODE_VERIFY(a, b, i)
#else
#ifndef PX5_OBJECT_CODE_ENABLE
#define PX5_OBJECT_CODE_ENABLE
#endif  /* PX5_OBJECT_CODE_ENABLE */
#define PX5_OBJECT_CODE_VERIFY(a, b, i)                     px5_internal_data_verification_code_verify((a), (b), (i));
#endif  /* PX5_OBJECT_VERIFY_ENABLE */

#ifndef PX5_OBJECT_CODE_ENABLE
#define PX5_OBJECT_CODE_CREATE(a, b)
#else
#define PX5_OBJECT_CODE_CREATE(a, b)                        px5_internal_data_verification_code_create((a), (b));
#endif  /* PX5_OBJECT_CODE_ENABLE */


/* Default partition memory pool verification macros to white-space, unless enabled by the application.  */

#ifndef PX5_PARTITIONPOOL_VERIFY_ENABLE
#define PX5_PARTITIONPOOL_CODE_VERIFY(a, b, i)
#else
#ifndef PX5_PARTITIONPOOL_CODE_ENABLE
#define PX5_PARTITIONPOOL_CODE_ENABLE
#endif  /* PX5_PARTITIONPOOL_CODE_ENABLE */
#define PX5_PARTITIONPOOL_CODE_VERIFY(a, b, i)              px5_internal_pointer_verification_code_verify((a), (b), (i));
#endif  /* PX5_PARTITIONPOOL_VERIFY_ENABLE */

#ifndef PX5_PARTITIONPOOL_CODE_ENABLE
#define PX5_PARTITIONPOOL_CODE_CREATE(a, b)
#else
#define PX5_PARTITIONPOOL_CODE_CREATE(a, b)                 px5_internal_pointer_verification_code_create((a), (b));
#endif  /* PX5_PARTITIONPOOL_CODE_ENABLE */


/* Default stack verification macros to white-space, unless enabled by the application.  */

#ifndef PX5_STACK_VERIFY_ID
#define PX5_STACK_VERIFY_ID                                 0x5354434BUL
#endif  /* PX5_STACK_VERIFY_ID */

#ifndef PX5_STACK_VERIFY_ENABLE
#define PX5_STACK_VERIFY_INFO
#define PX5_STACK_VERIFY_SETUP(i)
#define PX5_STACK_VERIFY(i)
#else
#ifdef PX5_MISRA_ENABLE
#define PX5_STACK_VERIFY_INFO                               px5_internal_stack_verification     stack_verification =  {(u_long) 0, (u_long) 0};
#else
#define PX5_STACK_VERIFY_INFO                               px5_internal_stack_verification     stack_verification;
#endif /* PX5_MISRA_ENABLE  */
#define PX5_STACK_VERIFY_SETUP(i)                           stack_verification.stack_verification_id =    ((u_long) PX5_STACK_VERIFY_ID);   \
                                                            px5_internal_data_verification_code_create(stack_verification.stack_verification_id, &stack_verification.stack_verification_code);
#define PX5_STACK_VERIFY(i)                                 px5_internal_data_verification_code_verify((stack_verification.stack_verification_id + (stack_verification.stack_verification_id - (PX5_STACK_VERIFY_ID))), &stack_verification.stack_verification_code, (i));
#endif  /* PX5_STACK_VERIFY_ENABLE */


/* Determine if MISRA is enabled.  */

#ifdef  PX5_MISRA_ENABLE
#ifndef PX5_INTERNAL_CALL_ERROR_CHECKING_ENABLE
#define PX5_INTERNAL_CALL_ERROR_CHECKING_ENABLE
#endif  /* PX5_INTERNAL_CALL_ERROR_CHECKING_ENABLE  */
#endif  /* PX5_MISRA_ENABLE  */


/* Define the internal function call error checking support.  */

#ifdef PX5_INTERNAL_CALL_ERROR_CHECKING_ENABLE
#define PX5_INTERNAL_CALL(a)                                px5_internal_call_error_check((a))
#else
#define PX5_INTERNAL_CALL(a)                                ((a))
#endif  /* PX5_INTERNAL_CALL_ERROR_CHECKING_ENABLE  */


/* Default stack size checking macros to white-space, unless enabled by the application.  */

#ifndef PX5_STACK_CHECK_ENABLE
#define PX5_STACK_SIZE_CHECK(i) 
#else                                                     
#define PX5_STACK_SIZE_CHECK(i)                             px5_internal_thread_stack_size_check(i);
#endif  /* PX5_STACK_CHECK_ENABLE */


/* Default PX5 global data extensions to white-space.  */

#ifndef PX5_GLOBAL_DATA_BINDING_EXTENSION
#define PX5_GLOBAL_DATA_BINDING_EXTENSION
#endif  /* PX5_GLOBAL_DATA_BINDING_EXTENSION */

#ifndef PX5_GLOBAL_DATA_EXTENSION
#define PX5_GLOBAL_DATA_EXTENSION
#endif  /* PX5_GLOBAL_DATA_EXTENSION */


/* Default the binding verification processing extension to white-space.  */

#ifndef PX5_BINDING_VERIFICATION_EXTENSION
#define PX5_BINDING_VERIFICATION_EXTENSION
#endif  /* PX5_BINDING_VERIFICATION_EXTENSION */


/* Default the px5_pthread_start extensions to white-space.  */

#ifndef PX5_PTHREAD_START_PRE_EXTENSION
#define PX5_PTHREAD_START_PRE_EXTENSION
#endif  /* PX5_PTHREAD_START_PRE_EXTENSION */

#ifndef PX5_PTHREAD_START_ENVIRONMENT_EXTENSION
#define PX5_PTHREAD_START_ENVIRONMENT_EXTENSION
#endif  /* PX5_PTHREAD_START_ENVIRONMENT_EXTENSION  */

#ifndef PX5_PTHREAD_START_POST_EXTENSION
#define PX5_PTHREAD_START_POST_EXTENSION
#endif  /* PX5_PTHREAD_START_POST_EXTENSION */


/* Default the PX5 thread entry extension processing to white-space.  */

#ifndef PX5_PTHREAD_ENTRY_PRE_EXTENSION
#define PX5_PTHREAD_ENTRY_PRE_EXTENSION
#endif  /* PX5_PTHREAD_ENTRY_PRE_EXTENSION */

#ifndef PX5_PTHREAD_ENTRY_ENVIRONMENT_EXTENSION
#define PX5_PTHREAD_ENTRY_ENVIRONMENT_EXTENSION
#endif  /* PX5_PTHREAD_ENTRY_ENVIRONMENT_EXTENSION  */

#ifndef PX5_PTHREAD_ENTRY_POST_EXTENSION
#define PX5_PTHREAD_ENTRY_POST_EXTENSION
#endif  /* PX5_PTHREAD_ENTRY_POST_EXTENSION */


/* Default the PX5 thread exit (pre and post) extension processing to white-space.  */

#ifndef PX5_PTHREAD_EXIT_PRE_EXTENSION
#define PX5_PTHREAD_EXIT_PRE_EXTENSION
#endif  /* PX5_PTHREAD_EXIT_PRE_EXTENSION */

#ifndef PX5_PTHREAD_EXIT_ENVIRONMENT_EXTENSION
#define PX5_PTHREAD_EXIT_ENVIRONMENT_EXTENSION
#endif  /* PX5_PTHREAD_EXIT_ENVIRONMENT_EXTENSION  */

#ifndef PX5_PTHREAD_EXIT_POST_EXTENSION
#define PX5_PTHREAD_EXIT_POST_EXTENSION
#endif  /* PX5_PTHREAD_EXIT_POST_EXTENSION */


/* Default the PX5 asynchronous pre-cancel extension processing to white-space.  */

#ifndef PX5_PTHREAD_CANCEL_PRE_EXTENSION
#define PX5_PTHREAD_CANCEL_PRE_EXTENSION
#endif  /* PX5_PTHREAD_CANCEL_PRE_EXTENSION  */
                                                            
#ifndef PX5_PTHREAD_CANCEL_ENVIRONMENT_EXTENSION
#define PX5_PTHREAD_CANCEL_ENVIRONMENT_EXTENSION
#endif  /* PX5_PTHREAD_CANCEL_ENVIRONMENT_EXTENSION  */
                                                            

/* Default the PX5 create/init/open extensions to white-space.  */

#ifndef PX5_MQ_EXTEND_OPEN_EXTENSION
#define PX5_MQ_EXTEND_OPEN_EXTENSION
#endif  /* PX5_MQ_EXTEND_OPEN_EXTENSION */

#ifndef PX5_MQ_OPEN_EXTENSION 
#define PX5_MQ_OPEN_EXTENSION 
#endif  /* PX5_MQ_OPEN_EXTENSION */

#ifndef PX5_PTHREAD_COND_INIT_EXTENSION 
#define PX5_PTHREAD_COND_INIT_EXTENSION 
#endif  /* PX5_PTHREAD_COND_INIT_EXTENSION */

#ifndef PX5_PTHREAD_CREATE_EXTENSION
#define PX5_PTHREAD_CREATE_EXTENSION
#endif  /* PX5_PTHREAD_CREATE_EXTENSION */

#ifndef PX5_PTHREAD_EVENT_FLAGS_CREATE_EXTENSION
#define PX5_PTHREAD_EVENT_FLAGS_CREATE_EXTENSION
#endif  /* PX5_PTHREAD_EVENT_FLAGS_CREATE_EXTENSION */

#ifndef PX5_PTHREAD_FASTQUEUE_CREATE_EXTENSION
#define PX5_PTHREAD_FASTQUEUE_CREATE_EXTENSION
#endif  /* PX5_PTHREAD_FASTQUEUE_CREATE_EXTENSION */

#ifndef PX5_PTHREAD_MEMORYPOOL_CREATE_EXTENSION 
#define PX5_PTHREAD_MEMORYPOOL_CREATE_EXTENSION 
#endif  /* PX5_PTHREAD_MEMORYPOOL_CREATE_EXTENSION */

#ifndef PX5_PTHREAD_MUTEX_INIT_EXTENSION
#define PX5_PTHREAD_MUTEX_INIT_EXTENSION
#endif  /* PX5_PTHREAD_MUTEX_INIT_EXTENSION */

#ifndef PX5_PTHREAD_PARTITIONPOOL_CREATE_EXTENSION 
#define PX5_PTHREAD_PARTITIONPOOL_CREATE_EXTENSION 
#endif  /* PX5_PTHREAD_PARTITIONPOOL_CREATE_EXTENSION */

#ifndef PX5_PTHREAD_TICKTIMER_CREATE_EXTENSION
#define PX5_PTHREAD_TICKTIMER_CREATE_EXTENSION
#endif  /* PX5_PTHREAD_TICKTIMER_CREATE_EXTENSION */

#ifndef PX5_SEM_EXTEND_INIT_EXTENSION
#define PX5_SEM_EXTEND_INIT_EXTENSION
#endif  /* PX5_SEM_EXTEND_INIT_EXTENSION */

#ifndef PX5_SEM_INIT_EXTENSION
#define PX5_SEM_INIT_EXTENSION
#endif  /* PX5_SEM_INIT_EXTENSION */


/* Default the PX5 function prologue and epilogue extensions to white-space.  */

#ifndef PX5_FUNCTION_ENTRY_EXTENSION
#define PX5_FUNCTION_ENTRY_EXTENSION(a)
#endif  /* PX5_FUNCTION_ENTRY_EXTENSION */

#ifndef PX5_FUNCTION_EXIT_EXTENSION
#define PX5_FUNCTION_EXIT_EXTENSION(a)
#endif  /* PX5_FUNCTION_EXIT_EXTENSION */


/* Default the PX5 system trace extensions to white-space.  */

#ifndef PX5_SYSTEM_TRACE_API_EXTENSION
#define PX5_SYSTEM_TRACE_API_EXTENSION(a, b, c, d)
#endif  /* PX5_SYSTEM_TRACE_API_EXTENSION */

#ifndef PX5_SYSTEM_TRACE_ERROR_EXTENSION
#define PX5_SYSTEM_TRACE_ERROR_EXTENSION(a, b, c, d)
#endif  /* PX5_SYSTEM_TRACE_ERROR_EXTENSION */

#ifndef PX5_SYSTEM_TRACE_THREAD_ENTER_EXTENSION
#define PX5_SYSTEM_TRACE_THREAD_ENTER_EXTENSION(a, b, c, d)      ((void)(b)); 
#endif  /* PX5_SYSTEM_TRACE_THREAD_ENTER_EXTENSION */

#ifndef PX5_SYSTEM_TRACE_THREAD_EXIT_EXTENSION
#define PX5_SYSTEM_TRACE_THREAD_EXIT_EXTENSION(a, b, c, d)       ((void)(b)); 
#endif  /* PX5_SYSTEM_TRACE_THREAD_EXIT_EXTENSION */

#ifndef PX5_SYSTEM_TRACE_THREAD_PRIORITY_CHANGE_EXTENSION
#define PX5_SYSTEM_TRACE_THREAD_PRIORITY_CHANGE_EXTENSION(a, b, c, d)
#endif  /* PX5_SYSTEM_TRACE_THREAD_PRIORITY_CHANGE_EXTENSION */

#ifndef PX5_SYSTEM_TRACE_THREAD_READY_EXTENSION
#define PX5_SYSTEM_TRACE_THREAD_READY_EXTENSION(a, b, c, d)
#endif  /* PX5_SYSTEM_TRACE_THREAD_READY_EXTENSION */

#ifndef PX5_SYSTEM_TRACE_THREAD_SUSPEND_EXTENSION
#define PX5_SYSTEM_TRACE_THREAD_SUSPEND_EXTENSION(a, b, c, d)
#endif  /* PX5_SYSTEM_TRACE_THREAD_SUSPEND_EXTENSION */

#ifndef PX5_SYSTEM_TRACE_TIMER_INTERRUPT_EXTENSION
#define PX5_SYSTEM_TRACE_TIMER_INTERRUPT_EXTENSION(a, b, c, d)
#endif  /* PX5_SYSTEM_TRACE_TIMER_INTERRUPT_EXTENSION */


/* Define the PX5 thread entry/exit extensions to white-space.  */

#ifndef PX5_BINDING_THREAD_ENTRY_EXTENSION
#define PX5_BINDING_THREAD_ENTRY_EXTENSION(a)
#endif  /* PX5_BINDING_THREAD_ENTRY_EXTENSION */

#ifndef PX5_BINDING_THREAD_EXIT_EXTENSION
#define PX5_BINDING_THREAD_EXIT_EXTENSION(a)
#endif  /* PX5_BINDING_THREAD_EXIT_EXTENSION */

#ifndef PX5_USER_THREAD_ENTRY_EXTENSION
#define PX5_USER_THREAD_ENTRY_EXTENSION(a)
#endif  /* PX5_BINDING_THREAD_ENTRY_EXTENSION */

#ifndef PX5_USER_THREAD_EXIT_EXTENSION
#define PX5_USER_THREAD_EXIT_EXTENSION(a)
#endif  /* PX5_USER_THREAD_EXIT_EXTENSION */


/* Default the PX5 timer interrupt pre-processing extension to white-space.  */

#ifndef PX5_TIMER_INTERRUPT_PRE_PROCESS_EXTENSION
#define PX5_TIMER_INTERRUPT_PRE_PROCESS_EXTENSION
#endif  /* PX5_TIMER_INTERRUPT_PRE_PROCESS_EXTENSION */


/* Default the PX5 timer interrupt post-processing extension to white-space.  */

#ifndef PX5_TIMER_INTERRUPT_POST_PROCESS_EXTENSION
#define PX5_TIMER_INTERRUPT_POST_PROCESS_EXTENSION
#endif  /* PX5_TIMER_INTERRUPT_POST_PROCESS_EXTENSION */


/* Default the PX5 condition variable timed wait processing extension to white-space.  */

#ifndef PX5_PTHREAD_COND_TIMEDWAIT_PROCESSING_EXTENSION
#define PX5_PTHREAD_COND_TIMEDWAIT_PROCESSING_EXTENSION
#endif  /* PX5_PTHREAD_COND_TIMEDWAIT_PROCESSING_EXTENSION */


/* Default the PX5 condition variable wait processing extension to white-space.  */

#ifndef PX5_PTHREAD_COND_WAIT_PROCESSING_EXTENSION
#define PX5_PTHREAD_COND_WAIT_PROCESSING_EXTENSION
#endif  /* PX5_PTHREAD_COND_WAIT_PROCESSING_EXTENSION */


/* Default PX5 thread control structure extensions to white-space.  */

#ifndef PX5_THREAD_CONTROL_BINDING_EXTENSION
#define PX5_THREAD_CONTROL_BINDING_EXTENSION
#endif  /* PX5_THREAD_CONTROL_BINDING_EXTENSION */

#ifndef PX5_THREAD_CONTROL_ENVIRONMENT_EXTENSION
#define PX5_THREAD_CONTROL_ENVIRONMENT_EXTENSION
#endif  /* PX5_THREAD_CONTROL_ENVIRONMENT_EXTENSION  */

#ifndef PX5_THREAD_CONTROL_EXTENSION
#define PX5_THREAD_CONTROL_EXTENSION
#endif  /* PX5_THREAD_CONTROL_EXTENSION */


/* Default PX5 condition variable control structure extension to white-space.  */

#ifndef PX5_CONDITION_VAR_CONTROL_EXTENSION
#define PX5_CONDITION_VAR_CONTROL_EXTENSION
#endif  /* PX5_CONDITION_VAR_CONTROL_EXTENSION */


/* Default PX5 event flags control structure extension to white-space.  */

#ifndef PX5_EVENT_FLAGS_CONTROL_EXTENSION
#define PX5_EVENT_FLAGS_CONTROL_EXTENSION
#endif  /* PX5_EVENT_FLAGS_CONTROL_EXTENSION */


/* Default PX5 fastqueue control structure extension to white-space.  */

#ifndef PX5_FASTQUEUE_CONTROL_EXTENSION
#define PX5_FASTQUEUE_CONTROL_EXTENSION
#endif  /* PX5_FASTQUEUE_CONTROL_EXTENSION */


/* Default PX5 memory pool control structure extension to white-space.  */

#ifndef PX5_MEMORYPOOL_CONTROL_EXTENSION
#define PX5_MEMORYPOOL_CONTROL_EXTENSION
#endif  /* PX5_MEMORYPOOL_CONTROL_EXTENSION */


/* Default PX5 memory pool control structure extension to white-space.  */

#ifndef PX5_MEMORYPOOL_BLOCK_INFO_EXTENSION
#define PX5_MEMORYPOOL_BLOCK_INFO_EXTENSION
#endif  /* PX5_MEMORYPOOL_BLOCK_INFO_EXTENSION */


/* Default the PX5 memory allocate processing extension to white-space.  */

#ifndef PX5_PTHREAD_MEMORYPOOL_ALLOCATE_PROCESSING_EXTENSION
#define PX5_PTHREAD_MEMORYPOOL_ALLOCATE_PROCESSING_EXTENSION
#endif  /* PX5_PTHREAD_MEMORYPOOL_ALLOCATE_PROCESSING_EXTENSION */


/* Default the PX5 memory timed allocate processing extension to white-space.  */

#ifndef PX5_PTHREAD_MEMORYPOOL_TIMEDALLOCATE_PROCESSING_EXTENSION
#define PX5_PTHREAD_MEMORYPOOL_TIMEDALLOCATE_PROCESSING_EXTENSION
#endif  /* PX5_PTHREAD_MEMORYPOOL_TIMEDALLOCATE_PROCESSING_EXTENSION */


/* Default PX5 partition memory pool control structure extension to white-space.  */

#ifndef PX5_PARTITIONPOOL_CONTROL_EXTENSION
#define PX5_PARTITIONPOOL_CONTROL_EXTENSION
#endif  /* PX5_PARTITIONPOOL_CONTROL_EXTENSION */


/* Default PX5 partition memory pool control structure extension to white-space.  */

#ifndef PX5_PARTITION_INFO_EXTENSION
#define PX5_PARTITION_INFO_EXTENSION
#endif  /* PX5_PARTIT_INFO_EXTENSION */


/* Default PX5 message timed receive extension to white-space.  */

#ifndef PX5_MESSAGE_TIMEDRECEIVE_SEARCH_EXTENSION
#define PX5_MESSAGE_TIMEDRECEIVE_SEARCH_EXTENSION
#endif  /* PX5_MESSAGE_RECEIVE_SEARCH_EXTENSION */


/* Default PX5 message timed receive extension to white-space.  */

#ifndef PX5_MESSAGE_TIMEDRECEIVE_SEARCH_EXTENSION1
#define PX5_MESSAGE_TIMEDRECEIVE_SEARCH_EXTENSION1
#endif  /* PX5_MESSAGE_RECEIVE_SEARCH_EXTENSION1 */


/* Default PX5 message receive extension to white-space.  */

#ifndef PX5_MESSAGE_RECEIVE_SEARCH_EXTENSION
#define PX5_MESSAGE_RECEIVE_SEARCH_EXTENSION
#endif  /* PX5_MESSAGE_RECEIVE_SEARCH_EXTENSION */


/* Default PX5 message receive extension to white-space.  */

#ifndef PX5_MESSAGE_RECEIVE_SEARCH_EXTENSION1
#define PX5_MESSAGE_RECEIVE_SEARCH_EXTENSION1
#endif  /* PX5_MESSAGE_RECEIVE_SEARCH_EXTENSION1 */


/* Default PX5 message send extension to white-space.  */

#ifndef PX5_MESSAGE_SEND_SEARCH_EXTENSION
#define PX5_MESSAGE_SEND_SEARCH_EXTENSION
#endif  /* PX5_MESSAGE_SEND_SEARCH_EXTENSION */


/* Default PX5 message timed send extension to white-space.  */

#ifndef PX5_MESSAGE_TIMEDSEND_SEARCH_EXTENSION
#define PX5_MESSAGE_TIMEDSEND_SEARCH_EXTENSION
#endif  /* PX5_MESSAGE_TIMEDSEND_SEARCH_EXTENSION */


/* Define PX5 condition variable signal search extension to white-space.  */

#ifndef PX5_PTHREAD_COND_SIGNAL_SEARCH_EXTENSION
#define PX5_PTHREAD_COND_SIGNAL_SEARCH_EXTENSION
#endif  /* PX5_PTHREAD_COND_SIGNAL_SEARCH_EXTENSION */
                                                    

/* Define PX5 event flags set search extension to white-space.  */

#ifndef PX5_PTHREAD_EVENT_FLAGS_SET_SEARCH_EXTENSION
#define PX5_PTHREAD_EVENT_FLAGS_SET_SEARCH_EXTENSION
#endif  /* PX5_PTHREAD_EVENT_FLAGS_SET_SEARCH_EXTENSION */


/* Default PX5 mutex control structure extension to white-space.  */

#ifndef PX5_MUTEX_CONTROL_EXTENSION
#define PX5_MUTEX_CONTROL_EXTENSION
#endif  /* PX5_MUTEX_CONTROL_EXTENSION */


/* Define PX5 mutex unlock search extension to white-space.  */

#ifndef PX5_PTHREAD_MUTEX_UNLOCK_SEARCH_EXTENSION
#define PX5_PTHREAD_MUTEX_UNLOCK_SEARCH_EXTENSION
#endif  /* PX5_PTHREAD_MUTEX_UNLOCK_SEARCH_EXTENSION */


/* Define PX5 semaphore post search extension to white-space.  */
#ifndef PX5_SEMAPHORE_POST_SEARCH_EXTENSION
#define PX5_SEMAPHORE_POST_SEARCH_EXTENSION
#endif


/* Default PX5 message queue control structure extension to white-space.  */

#ifndef PX5_QUEUE_CONTROL_EXTENSION
#define PX5_QUEUE_CONTROL_EXTENSION
#endif  /* PX5_QUEUE_CONTROL_EXTENSION */


/* Default PX5 semaphore control structure extension to white-space.  */

#ifndef PX5_SEMAPHORE_CONTROL_EXTENSION
#define PX5_SEMAPHORE_CONTROL_EXTENSION
#endif  /* PX5_SEMAPHORE_CONTROL_EXTENSION */


/* Default PX5 ticktimer control structure extension to white-space.  */

#ifndef PX5_TICKTIMER_CONTROL_EXTENSION
#define PX5_TICKTIMER_CONTROL_EXTENSION
#endif  /* PX5_TICKTIMER_CONTROL_EXTENSION */


/* Default PX5 internal timer control structure extension to white-space.  */

#ifndef PX5_INTERNAL_TIMER_CONTROL_EXTENSION
#define PX5_INTERNAL_TIMER_CONTROL_EXTENSION
#endif  /* PX5_INTERNAL_TIMER_CONTROL_EXTENSION */


/* Default PX5 binding C-extension utilities to white-space.  */

#ifndef PX5_BINDING_C_EXTENSION_UTILITIES
#define PX5_BINDING_C_EXTENSION_UTILITIES
#endif  /* PX5_BINDING_C_EXTENSION_UTILITIES */


/* Default internal thread ready processing extension to white-space.  */

#ifndef PX5_INTERNAL_THREAD_READY_EXTENSION
#define PX5_INTERNAL_THREAD_READY_EXTENSION
#endif  /* PX5_INTERNAL_THREAD_READY_EXTENSION  */


/* Default internal thread suspend processing extension to white-space.  */

#ifndef PX5_INTERNAL_THREAD_SUSPEND_EXTENSION
#define PX5_INTERNAL_THREAD_SUSPEND_EXTENSION
#endif  /* PX5_INTERNAL_THREAD_SUSPEND_EXTENSION  */


/* Default pthread attribute initialize extension to white-space.  */

#ifndef PX5_PTHREAD_ATTR_INIT_EXTENSION
#define PX5_PTHREAD_ATTR_INIT_EXTENSION
#endif  /* PX5_PTHREAD_ATTR_INIT_EXTENSION  */


/******************************************************************************
 *************************** Section III: Typedefs ****************************
 *****************************************************************************/


/* Define internal stack verification typedef.  */

typedef struct px5_internal_stack_verification_struct
{
    
    /* Define stack verification ID and verification code.   */
    u_long                                                  stack_verification_id;
    u_long                                                  stack_verification_code;
} px5_internal_stack_verification;


/* Define forward reference for internal timer control structure, which
   will be defined in full later.  */

struct px5_internal_timer_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_internal_timer_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_internal_timer_control_struct *              next_internal_timer;
    struct px5_internal_timer_control_struct *              previous_internal_timer;

} px5_internal_timer_links;


/* Define the internal timer control structure that is for internal use only, i.e., 
   it is not directly exposed to the application code.  */

typedef struct px5_internal_timer_control_struct
{

    /* Define the amount of remaining amount of ticks.  */
    tick_t                                                  remaining_ticks;

    /* Define the reload number of ticks for periodic internal timers.  */
    tick_t                                                  reload_ticks;

    /* Define the expiration function to call when the internal timer ticks expire.  */
    void                                                    (*expiration_routine)(const struct px5_internal_timer_control_struct *);

    /* Define the expiration function verification code.  */
    u_long                                                  expiration_routine_pointer_verification_code;

    /* Define the auxiliary information pointer.  */
    void *                                                  auxilliary_timer_information;

    /* Define the pointer to the head list, since the timer may be on different lists.  When the list head
       is non-NULL, the internal timer is active.  When NULL, the internal timer in inactive.  */
    struct px5_internal_timer_control_struct **             list_head;

    /* Define the linked list pointers for the internal timer active list.  */
    px5_internal_timer_links                                active_list;

    /* Define an area for general extensions to the internal timer control structure. By default, this is defined as 
       white-space above.  */
    PX5_INTERNAL_TIMER_CONTROL_EXTENSION

} px5_internal_timer_control;


/* Define forward reference for thread control structure, which
   will be defined in full later.  */

struct px5_thread_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_thread_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_thread_control_struct *                      next_thread;
    struct px5_thread_control_struct *                      previous_thread;

} px5_thread_links;


/* Define the cleanup routine type.  */

typedef struct px5_thread_cleanup_info_struct
{

    /* Define the cleanup handler function pointer and verification code.  */
    void                                                    (*cleanup_handler)(void *);
    u_long                                                  cleanup_handler_verification_code;
    void *                                                  argument;

} px5_thread_cleanup_info;


/* Define the thread local storage key information contained in the thread.  */

typedef struct px5_thread_local_storage_struct 
{

    /* Define the pointer value.  */
    const void *                                            value;

    /* Define the destructor function pointer.  */
    void                                                    (*destructor)(void *); 
} px5_thread_local_storage;


/* Define the global key list that defines the thread local storage instance.  */

typedef struct px5_global_key_struct 
{

    /* Define the allocated flag.  */
    int                                                     allocated;

    /* Define the destructor function pointer.  */
    void                                                    (*destructor)(void *); 

    /* Define the destructor verification code.  */
    u_long                                                  destructor_verification_code;
} px5_global_key;


/* Define forward reference for mutex control structure, which
   will be defined in full later.  */

struct px5_mutex_control_struct;


/* Define forward reference for object suspension list structure, which
   will be defined in full later.  */

struct px5_suspension_list_struct;


/* Define the internal thread control structure that is for internal use only, i.e., 
   it is not directly exposed to the application code.  */

typedef struct px5_thread_control_struct
{

    /* This first section of the PX5 thread control structure is accessed by the binding assembly code
       and therefore should not be modified.  */

    /* Define the ID of the PX5 thread control structure.  */
    u_long                                                  thread_control_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the thread control 
       structure - when enabled.  */
    u_long                                                  thread_verification_id;

    /* Define the stack pointers of the thread.  */
    u_long *                                                stack_limit_address;
    u_long *                                                stack_base_address;
    u_long *                                                current_stack_pointer;
    u_long                                                  total_stack_size_in_bytes;
    u_long                                                  minimum_available_stack_bytes;

    /* Define the number of times this thread has been scheduled.  */
    u_long                                                  scheduled_count;

    /* Define an area accessible to the binding assembly language for extensions to the thread
       control structure. By default, this is defined as white-space above.  */
    PX5_THREAD_CONTROL_BINDING_EXTENSION

    /* Define the thread control extension for environment use, such as per-thread C library 
       extensions.  */
    PX5_THREAD_CONTROL_ENVIRONMENT_EXTENSION

#if PX5_MAXIMUM_CORES>1

    int                                                     executing_core; 
    u_long                                                  core_affinity;  
#endif /* PX5_MAXIMUM_CORES>1  */

    /* Define name of the thread.  */
    const char *                                            name;

    /* Define the thread state.  */
    int                                                     state;

    /* Define the thread priority.  */      
    int                                                     priority;
    int                                                     user_priority;
    int                                                     inheritance_priority;

    /* Define the thread detach state.  */
    int                                                     detach_state;

    /* Define the thread's cancel state and type.  */
    int                                                     cancel_state;
    int                                                     cancel_type;
    int                                                     cancel_pending;

    /* Define the thread time-slice information.  */
    tick_t                                                  time_slice_remaining;
    tick_t                                                  time_slice_reload;

    /* Define the signal mask and the pending signals for this thread.  */
    sigset_t                                                pending_signals;
    sigset_t                                                signal_mask;

    /* Define the signal set that the thread is suspended on.  */
    sigset_t                                                suspended_for_signals;
    int                                                     signal_received;

    /* Define the context the signal handler runs in.  */
    struct px5_thread_control_struct  *                     signal_thread;

    /* Define the thread-specific error variable. */
    int                                                     error;

    /* Define the entry point for the thread.  */
    void *                                                  (*entry_routine)(void *);
    u_long                                                  entry_routine_verification_code;
    void *                                                  argument;
    void *                                                  exit_value;
    
    /* Define the memory release function for the control structure.  */
    void                                                    (*control_memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  control_memory_release_pointer_verification_code;

    /* Define the memory release function for the thread's stack.  */
    void                                                    (*stack_memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  stack_memory_release_pointer_verification_code;

    /* Define the join information for this thread.  */
    struct px5_thread_control_struct *                      thread_that_joined;
    void **                                                 exit_value_destination;

    /* Define the owned priority inheritance list.  */
    struct px5_mutex_control_struct *                       owned_prio_inheritance_mutexes;
    u_long                                                  owned_prio_inheritance_count;

    /* Define the linked list pointers for the thread created list.  */
    px5_thread_links                                        created_list;

    /* Define the linked list pointers for the thread ready list.  */
    px5_thread_links volatile                               ready_list;

    /* Define an auxiliary thread pointer for internal object use. */
    struct px5_thread_control_struct *                      thread_pointer;

    /* Define the pointers to the suspension list information.  */
    struct px5_suspension_info_struct *                     suspension_info_pointer;

    /* Define the actual suspension list next/previous pointers.  */
    px5_thread_links volatile                               suspension_list;

    /* Define the suspended internal pointer.  */
    u_long *                                                suspended_pointer;

    /* Define the suspended data.  */
    size_t                                                  suspended_size;
    int                                                     suspended_type;
    u_long                                                  suspended_events;
    unsigned int                                            suspended_priority;

    /* Define the internal timer control block used for sleep requests.  */
    px5_internal_timer_control                              timer;

    /* Define cleanup handler information.  */
    int                                                     stacked_cleanup_handlers;
    px5_thread_cleanup_info                                 cleanup_handlers[PX5_MAXIMUM_CLEANUP_HANDLERS];

    /* Define the thread local storage keys.  */
    px5_thread_local_storage                                thread_local_storage_keys[PTHREAD_KEYS_MAX];

    /* Define an area for general extensions to the thread control structure. By default, this is defined as 
       white-space above.  */
    PX5_THREAD_CONTROL_EXTENSION

    /* Define the optional verification code for the thread structure.  */
    u_long                                                  thread_verification_code;

} px5_thread_control;


/* Define the mutex doubly linked, circular list type.  */

typedef struct px5_mutex_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_mutex_control_struct *                       next_mutex;
    struct px5_mutex_control_struct *                       previous_mutex;

} px5_mutex_links;


/* Define the object suspension information type.  */

typedef struct px5_suspension_info_struct
{

    /* Define the list of threads waiting on the object.  */
    px5_thread_control *                                    suspended_list;

    /* Define the number of threads waiting on the object.  */
    u_long                                                  suspended_count;

    /* Define the current access for this object.  */
    px5_thread_control * volatile                           current_access;
} px5_suspension_info;


/* Define the internal mutex control structure, which is used for mutual exclusion.  */

typedef struct px5_mutex_control_struct
{

    /* Define the ID of mutex control structure.  */
    u_long                                                  mutex_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the mutex control 
       structure - when enabled.  */
    u_long                                                  mutex_verification_id;

    /* Define the name of the mutex.  */
    const char *                                            name;

    /* Define the type of the mutex.  */
    int                                                     type;

    /* Define the protocol of the mutex.  */
    int                                                     protocol;

    /* Define the routine to call when the mutex control memory is no longer needed.  */
    void                                                    (*memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  memory_release_pointer_verification_code;

    /* Define the owner of the mutex.  */
    px5_thread_control *                                    owner;               

    /* Define the nested ownership of the mutex, i.e., how many times the current owner has obtained
       the mutex.  */
    u_long                                                  nested_count;

    /* Define the counter for the number of condition variable waits (and timed waits) active. This is necessary to prevent destruction of 
       the mutex while conditional variable waits are pending.  */
    u_long                                                  condition_var_waits;

    /* Define the maximum nested ownership of the mutex.  Since by default, mutexes are not created recursive, this count is set to 1.  */
    u_long                                                  maximum_nesting;

    /* Define the suspension information for threads waiting on the mutex.  */
    px5_suspension_info                                     suspension_info;

    /* Define the highest-priority suspended thread.  */
    int                                                     suspended_highest_priority;

    /* Define the mutex priority inheritance list, next and previous pointers.  */
    px5_mutex_links                                         owned_prio_inheritance_list;

    /* Define the mutex created list, next and previous pointers.  */
    px5_mutex_links                                         created_list;

    /* Define an area for general extensions to the mutex control structure. By default, this is defined as 
       white-space above.  */
    PX5_MUTEX_CONTROL_EXTENSION

    /* Define the optional verification code for the mutex structure.  */
    u_long                                                  mutex_verification_code;

} px5_mutex_control;


/* Define forward reference for condition variable control structure, which
   will be defined in full later.  */

struct px5_condition_var_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_condition_var_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_condition_var_control_struct *               next_condition_var;
    struct px5_condition_var_control_struct *               previous_condition_var;

} px5_condition_var_links;


/* Define the internal condition variable control structure, which is used for thread synchronization.  */

typedef struct px5_condition_var_control_struct
{

    /* Define the ID of condition variable control structure.  */
    u_long                                                  condition_var_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the condition variable control 
       structure - when enabled.  */
    u_long                                                  condition_var_verification_id;

    /* Define the name of the condition variable.  */
    const char *                                            name;

    /* Define the routine to call when the condition_var control memory is no longer needed.  */
    void                                                    (*memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  memory_release_pointer_verification_code;

    /* Define the signal counter that is incremented on every signal for this condition variable.  */
    u_long                                                  signal_count;

    /* Define the mutex associated with waiters on this condition variable.  */
    px5_mutex_control *                                     associated_mutex;

    /* Define the suspension information for threads waiting on the condition variable.  */
    px5_suspension_info                                     suspension_info;

    /* Define the condition_var created list, next and previous pointers.  */
    px5_condition_var_links                                 created_list;

    /* Define an area for general extensions to the condition variable control structure. By default, this is defined as 
       white-space above.  */
    PX5_CONDITION_VAR_CONTROL_EXTENSION

    /* Define the optional verification code for the condition variable structure.  */
    u_long                                                  condition_var_verification_code;

} px5_condition_var_control;


/* Define forward reference for event flags control structure, which
   will be defined in full later.  */

struct px5_event_flags_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_event_flags_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_event_flags_control_struct *                 next_event_flags;
    struct px5_event_flags_control_struct *                 previous_event_flags;

} px5_event_flags_links;


/* Define the internal event flags control structure, which is used for thread synchronization.  */

typedef struct px5_event_flags_control_struct
{

    /* Define the ID of event flags control structure.  */
    u_long                                                  event_flags_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the event flags control 
       structure - when enabled.  */
    u_long                                                  event_flags_verification_id;

    /* Define the name of the event flags.  */
    const char *                                            name;

    /* Define the current event flags for this set.  */
    u_long                                                  current_events;

#ifdef PX5_EVENT_FLAG_CONSUMPTION_MASK_ENABLE

    /* Define the automatic event consumption mask, which can be used to disable automatic consumption of any event.  */
    u_long                                                  automatic_event_consumption_mask;
#endif /* PX5_EVENT_FLAG_CONSUMPTION_MASK_ENABLE  */

    /* Define the routine to call when the event flags control memory is no longer needed.  */
    void                                                    (*memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  memory_release_pointer_verification_code;

    /* Define the suspension information for threads waiting for the event flags.  */
    px5_suspension_info                                     suspension_info;

    /* Define the event flags created list, next and previous pointers.  */
    px5_event_flags_links                                   created_list;

#ifdef PX5_NOTIFICATION_ENABLE

    /* Define the function pointer that can be registered by the application such that it is called
       whenever an event flag is set. By default, this pointer is NULL, and nothing is called on an 
       event flag set request.  */
    void                                                    (*set_callback)(pthread_event_flags_t *  event_flags_handle);

#ifdef PX5_FUNCTION_POINTER_CODE_ENABLE

    /* Define the callback function pointer verification code, when enabled.  */
    u_long                                                  set_callback_verification_code;

#endif /* PX5_FUNCTION_POINTER_CODE_ENABLE  */

    /* Define the handle to provide to the specified callback routine when event flags are set.  */
    pthread_event_flags_t                                   set_callback_handle;

#endif /* PX5_NOTIFICATION_ENABLE  */

    /* Define an area for general extensions to the event flags control structure. By default, this is defined as 
       white-space above.  */
    PX5_EVENT_FLAGS_CONTROL_EXTENSION

    /* Define the optional verification code for the event flags structure.  */
    u_long                                                  event_flags_verification_code;

} px5_event_flags_control;


/* Define forward reference for fastqueue control structure, which
   will be defined in full later.  */

struct px5_fastqueue_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_fastqueue_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_fastqueue_control_struct *                   next_fastqueue;
    struct px5_fastqueue_control_struct *                   previous_fastqueue;

} px5_fastqueue_links;


/* Define the internal fastqueue control structure, which is used for message passing between threads.  */

typedef struct px5_fastqueue_control_struct
{

    /* Define the ID of fastqueue control structure.  */
    u_long                                                  fastqueue_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the fastqueue control 
       structure - when enabled.  */
    u_long                                                  fastqueue_verification_id;

    /* Define the name of the fastqueue.  */
    const char *                                            fastqueue_name;

    /* Define the routine to call when the fastqueue control memory is no longer needed.  */
    void                                                    (*control_memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  control_memory_release_pointer_verification_code;

    /* Define the routine to call when the fastqueue queue memory is no longer needed.  */
    void                                                    (*queue_memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  queue_memory_release_pointer_verification_code;

    /* Define the maximum number of messages in the fastqueue.  */
    u_long                                                  maximum_messages;

    /* Define the message size.  */
    size_t                                                  message_size;

    /* Define the number of words per message.  */
    size_t                                                  message_words;

    /* Define the start of the fastqueue memory.  */
    u_long *                                                fastqueue_memory_start;

    /* Define the end of the fastqueue memory.  */
    u_long *                                                fastqueue_memory_end;

    /* Define the first and last message pointers in the fastqueue memory.  */
    u_long *                                                first_message;
    u_long *                                                last_message;

    /* Define the total number of messages in the fastqueue.  */
    u_long                                                  messages_queued;

    /* Define the suspension information for threads waiting on the fastqueue.  */
    px5_suspension_info                                     suspension_info;

    /* Define the fastqueue created list, next and previous pointers.  */
    px5_fastqueue_links                                     created_list;

#ifdef PX5_NOTIFICATION_ENABLE

    /* Define the function pointer that can be registered by the application such that it is called
       whenever a message is sent to this fastqueue. By default, this pointer is NULL, and nothing 
       is called on a fastqueue send request.  */
    void                                                    (*send_callback)(pthread_fastqueue_t *  fastqueue_handle);

#ifdef PX5_FUNCTION_POINTER_CODE_ENABLE

    /* Define the callback function pointer verification code, when enabled.  */
    u_long                                                  send_callback_verification_code;

#endif /* PX5_FUNCTION_POINTER_CODE_ENABLE  */

    /* Define the handle to provide to the specified callback routine when a message is sent to the fastqueue.  */
    pthread_fastqueue_t                                     send_callback_handle;

#endif /* PX5_NOTIFICATION_ENABLE  */

    /* Define an area for general extensions to the fastqueue control structure. By default, this is defined as 
       white-space above.  */
    PX5_FASTQUEUE_CONTROL_EXTENSION

    /* Define the optional verification code for the fastqueue structure.  */
    u_long                                                  fastqueue_verification_code;

} px5_fastqueue_control;


/* Define forward reference for memory pool control structure, which
   will be defined in full later.  */

struct px5_memorypool_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_memorypool_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_memorypool_control_struct *                 next_memorypool;
    struct px5_memorypool_control_struct *                 previous_memorypool;

} px5_memorypool_links;


/* Define the information ahead of each memory block in the pool.  */

typedef struct px5_memorypool_block_info_struct
{

    /* Define the storage for the verification code if enabled.  */
    u_long                                                  memorypool_pointer_verification_code;

    /* Define memory pool link.  */
    struct px5_memorypool_control_struct *                  pool_control;

    /* Define the next block pointer.  */
    struct px5_memorypool_block_info_struct *               next_block;

    /* Define the allocated or free flag.  */
    u_long                                                  allocated_status;

    /* Define an area for general extensions to the block information structure. By default, this is defined as 
       white-space above.  */
    PX5_MEMORYPOOL_BLOCK_INFO_EXTENSION

} px5_memorypool_block_info;


/* Define the internal memory pool control structure, which is used for memory management.  */

typedef struct px5_memorypool_control_struct
{

    /* Define the ID of memory pool control structure.  */
    u_long                                                  memorypool_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the memory pool control 
       structure - when enabled.  */
    u_long                                                  memorypool_verification_id;

    /* Define the name of the memory pool.  */
    const char *                                            name;

    /* Define the routine to call when the memory pool control memory is no longer needed.  */
    void                                                    (*memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  memory_release_pointer_verification_code;

    /* Define the mutex for controlling access to the memory pool.  */
    pthread_mutex_t                                         pool_mutex_handle;
    px5_mutex_control                                       pool_mutex;

    /* Define memory pool memory area starting pointer.  */
    px5_memorypool_block_info *                             pool_start;

    /* Define memory pool memory area starting pointer.  */
    px5_memorypool_block_info *                             search_start;

    /* Define memory pool size.  */
    size_t                                                  pool_size;

    /* Define the maximum available size.  */
    size_t                                                  max_available;

    /* Define the number of fragments in the pool.  */
    u_long                                                  fragments;

    /* Define permanently allocated block at the end of the memory pool.  */
    px5_memorypool_block_info *                             pool_end;

    /* Define the suspension information for threads waiting on the memory pool.  */
    px5_suspension_info                                     suspension_info;

    /* Define the memory pool created list, next and previous pointers.  */
    px5_memorypool_links                                    created_list;

    /* Define an area for general extensions to the memory pool control structure. By default, this is defined as 
       white-space above.  */
    PX5_MEMORYPOOL_CONTROL_EXTENSION

    /* Define the optional verification code for the memory pool structure.  */
    u_long                                                  memorypool_verification_code;

} px5_memorypool_control;


/* Define forward reference for partition memory pool control structure, which
   will be defined in full later.  */

struct px5_partitionpool_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_partitionpool_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_partitionpool_control_struct *              next_partitionpool;
    struct px5_partitionpool_control_struct *              previous_partitionpool;

} px5_partitionpool_links;


/* Define the information ahead of each partition in the partition pool.  */

typedef struct px5_partition_info_struct
{

    /* Define the storage for the verification code if enabled.  */
    u_long                                                  partition_pointer_verification_code;

    /* Define partition memory pool link.  */
    struct px5_partitionpool_control_struct *               pool_control;

    /* Define the next partition pointer.  */
    struct px5_partition_info_struct *                      next_partition;

    /* Define the next created partition.  */
    struct px5_partition_info_struct *                      next_created;

    /* Define an area for general extensions to the partition information structure. By default, this is defined as 
       white-space above.  */
    PX5_PARTITION_INFO_EXTENSION

} px5_partition_info;


/* Define the internal partition memory pool control structure, which is used for memory management.  */

typedef struct px5_partitionpool_control_struct
{

    /* Define the ID of partition memory pool control structure.  */
    u_long                                                  partitionpool_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the partition memory pool control 
       structure - when enabled.  */
    u_long                                                  partitionpool_verification_id;

    /* Define the name of the partition memory pool.  */
    const char *                                            name;

    /* Define the routine to call when the partition memory pool control memory is no longer needed.  */
    void                                                    (*memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  memory_release_pointer_verification_code;

    /* Define partition memory pool memory area starting pointer.  */
    px5_partition_info *                                    pool_start;

    /* Define partition memory pool memory area starting pointer.  */
    px5_partition_info *                                    free_partition_list;

    /* Define partition memory pool size.  */
    size_t                                                  pool_size;

#ifndef PX5_INTERNAL_STATISTICS_DISABLE

    /* Define the currently available number of partitions.  */
    u_long                                                  available_partitions;
#endif 

    /* Define partition size.  */
    size_t                                                  partition_size;

    /* Define the suspension information for threads waiting on the partition pool.  */
    px5_suspension_info                                     suspension_info;

    /* Define the partition memory pool created list, next and previous pointers.  */
    px5_partitionpool_links                                 created_list;

    /* Define an area for general extensions to the partition memory pool control structure. By default, this is defined as 
       white-space above.  */
    PX5_PARTITIONPOOL_CONTROL_EXTENSION

    /* Define the optional verification code for the memory pool structure.  */
    u_long                                                  partitionpool_verification_code;

} px5_partitionpool_control;


/* Define forward reference for queue control structure, which
   will be defined in full later.  */

struct px5_queue_control_struct;


/* Define the queue message header. Each message has a header of this type in front of the actual message data.  */

typedef struct px5_queue_message_header_struct
{

    /* Define the next message pointer.  */
    struct px5_queue_message_header_struct *                next_message;

    /* Define the message size.  */
    size_t                                                  size;

    /* Define the message priority.  */
    unsigned int                                            priority;

} px5_queue_message_header;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_queue_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_queue_control_struct *                       next_queue;
    struct px5_queue_control_struct *                       previous_queue;

} px5_queue_links;


/* Define the internal queue control structure, which is used for message passing between threads.  */

typedef struct px5_queue_control_struct
{

    /* Define the ID of queue control structure.  */
    u_long                                                  queue_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the queue control 
       structure - when enabled.  */
    u_long                                                  queue_verification_id;

    /* Define the name of the queue.  */
    const char *                                            queue_name;

    /* Define the routines to call when the queue control memory or queue message memory is no longer needed.  */
    void                                                    (*control_memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  control_memory_release_pointer_verification_code;
    void                                                    (*queue_memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  queue_memory_release_pointer_verification_code;

    /* Define the queue operation information.  */
    u_long                                                  operation;

    /* Define the maximum number of messages in the queue.  */
    u_long                                                  maximum_messages;

    /* Define the maximum message size.  */
    size_t                                                  maximum_message_size;

    /* Define the start of the queue memory.  */
    u_long *                                                queue_memory_start;

    /* Define the end of the queue memory.  */
    u_long *                                                queue_memory_end;

    /* Define the head and tail pointer of the queue.  */
    px5_queue_message_header *                              first_message;
    px5_queue_message_header *                              last_message;

    /* Define the available messages, i.e., messages not in the queue.  */
    px5_queue_message_header *                              available_messages;

    /* Define the total number of messages in the queue.  */
    u_long                                                  messages_queued;

    /* Define the suspension information for threads waiting on the queue.  */
    px5_suspension_info                                     suspension_info;

    /* Define the queue created list, next and previous pointers.  */
    px5_queue_links                                         created_list;

#ifdef PX5_NOTIFICATION_ENABLE

    /* Define the function pointer that can be registered by the application such that it is called
       whenever a message is sent to this queue. By default, this pointer is NULL, and nothing 
       is called on a queue send request.  */
    void                                                    (*send_callback)(mqd_t  queue_handle);

#ifdef PX5_FUNCTION_POINTER_CODE_ENABLE

    /* Define the callback function pointer verification code, when enabled.  */
    u_long                                                  send_callback_verification_code;

#endif /* PX5_FUNCTION_POINTER_CODE_ENABLE  */

    /* Define the handle to provide to the specified callback routine when a message is sent to the queue.  */
    mqd_t                                                   send_callback_handle;

#endif /* PX5_NOTIFICATION_ENABLE  */

    /* Define an area for general extensions to the queue control structure. By default, this is defined as 
       white-space above.  */
    PX5_QUEUE_CONTROL_EXTENSION

    /* Define the optional verification code for the queue structure.  */
    u_long                                                  queue_verification_code;

} px5_queue_control;


/* Define forward reference for semaphore control structure, which
   will be defined in full later.  */

struct px5_semaphore_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_semaphore_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_semaphore_control_struct *                   next_semaphore;
    struct px5_semaphore_control_struct *                   previous_semaphore;

} px5_semaphore_links;


/* Define the internal semaphore control structure, which is used for consumer/producer and mutual exclusion.  */

typedef struct px5_semaphore_control_struct
{

    /* Define the ID of semaphore control structure.  */
    u_long                                                  semaphore_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the semaphore control 
       structure - when enabled.  */
    u_long                                                  semaphore_verification_id;

    /* Define the name of the semaphore.  */
    const char *                                            name;

    /* Define the routine to call when the semaphore control memory is no longer needed.  */
    void                                                    (*memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  memory_release_pointer_verification_code;

    /* Define the semaphore count.  */
    u_long                                                  count;

    /* Define the suspension information for threads waiting on the semaphore.  */
    px5_suspension_info                                     suspension_info;

    /* Define the semaphore created list, next and previous pointers.  */
    px5_semaphore_links                                     created_list;

#ifdef PX5_NOTIFICATION_ENABLE

    /* Define the function pointer that can be registered by the application such that it is called
       whenever a semaphore is posted. By default, this pointer is NULL, and nothing is called on a 
       semaphore post.  */
    void                                                    (*post_callback)(sem_t *  semaphore_handle);

#ifdef PX5_FUNCTION_POINTER_CODE_ENABLE

    /* Define the callback function pointer verification code, when enabled.  */
    u_long                                                  post_callback_verification_code;

#endif /* PX5_FUNCTION_POINTER_CODE_ENABLE  */

    /* Define the handle to provide to the specified callback routine when the semaphore is posted.  */
    sem_t                                                   post_callback_handle;

#endif /* PX5_NOTIFICATION_ENABLE  */

    /* Define an area for general extensions to the semaphore control structure. By default, this is defined as 
       white-space above.  */
    PX5_SEMAPHORE_CONTROL_EXTENSION

    /* Define the optional verification code for the semaphore structure.  */
    u_long                                                  semaphore_verification_code;

} px5_semaphore_control;


/* Define forward reference for ticktimer control structure, which
   will be defined in full later.  */

struct px5_ticktimer_control_struct;


/* Define the base doubly linked, circular list type.  */

typedef struct px5_ticktimer_links_struct
{
    
    /* Define next and previous links.  */
    struct px5_ticktimer_control_struct *                   next_ticktimer;
    struct px5_ticktimer_control_struct *                   previous_ticktimer;

} px5_ticktimer_links;


/* Define the internal ticktimer control structure, which is used for one-shot or periodic execution of an expiration routine.  */

typedef struct px5_ticktimer_control_struct
{

    /* Define the ID of ticktimer control structure.  */
    u_long                                                  ticktimer_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the ticktimer control 
       structure - when enabled.  */
    u_long                                                  ticktimer_verification_id;

    /* Define the name of the ticktimer.  */
    const char *                                            name;

    /* Define the routine to call when the ticktimer control memory is no longer needed.  */
    void                                                    (*memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  memory_release_pointer_verification_code;

    /* Define the ticktimer expiration routine.  */
    void                                                    (*expiration_routine)(const pthread_ticktimer_t *, void *);
    u_long                                                  expiration_routine_pointer_verification_code;

    /* Define a handle that is supplied to the expiration routine.  */
    pthread_ticktimer_t                                     ticktimer_handle;

    /* Define the user-supplied pointer that will be passed to the expiration routine.  */
    void *                                                  argument;

    /* Define the internal timer control structure.  */
    px5_internal_timer_control                              internal_timer;

    /* Define the ticktimer created list, next and previous pointers.  */
    px5_ticktimer_links                                     created_list;

    /* Define an area for general extensions to the ticktimer control structure. By default, this is defined as 
       white-space above.  */
    PX5_TICKTIMER_CONTROL_EXTENSION

    /* Define the optional verification code for the ticktimer structure.  */
    u_long                                                  ticktimer_verification_code;

} px5_ticktimer_control;


/* Define the global variable typedef for all of the PX5 RTOS global variables.  */

typedef struct px5_global_data_struct
{

    /* This first section of global data for PX5 is accessed by the binding assembly code
       and therefore should not be modified.  */

    /* Define the ID of the PX5 global data structure.  */
    u_long                                                  global_data_id;

    /* Define the verification ID that is used to create the verification code that this stored at the end of the PX5 RTOS global variables.  */
    u_long                                                  global_verification_id;

    /* Define the executing thread pointer. When this is non-NULL, the thread 
       associated with this thread control structure is running.  */
    px5_thread_control *                                    executing_thread[PX5_MAXIMUM_CORES];

    /* Define the next highest-priority thread to execute. When this is different 
       than the "executing_thread" a context switch (preemption/suspension) is 
       required.  */
    px5_thread_control *                                    highest_priority_thread[PX5_MAXIMUM_CORES];

    /* Define the PX5 system stack pointer.  This pointer is used when no thread is 
       is running. */
    u_long *                                                system_stack[PX5_MAXIMUM_CORES];

    /* Define the interrupt nesting level used in some binding layers.  */
    u_int                                                   interrupt_nesting_level[PX5_MAXIMUM_CORES];

    /* Define an area accessible to the binding assembly language for extensions to the PX5 global data. 
       By default, this is defined as white-space above.  */
    PX5_GLOBAL_DATA_BINDING_EXTENSION

#if PX5_MAXIMUM_CORES>1

    /* Define some of the SMP control structures used internally.  */
    px5_thread_control *                                    new_highest_priority_threads[PX5_MAXIMUM_CORES];  
    px5_thread_control *                                    top_priority_threads[PX5_MAXIMUM_CORES];          
    px5_thread_control *                                    remap_thread_list[PX5_MAXIMUM_CORES];           
    u_long                                                  total_ready_threads;
#endif /* PX5_MAXIMUM_CORES>1  */

    /* Define the version IDs for PX5, both the C code and the binding code.  */
    u_char                                                  major_version;
    u_char                                                  minor_version;
    u_char                                                  update_version;
    u_char                                                  patch_version;
    u_char                                                  binding_major_version;
    u_char                                                  binding_minor_version;
    u_char                                                  binding_update_version;
    u_char                                                  binding_patch_version;

    /* Define the binding identifier string.  */
    const char *                                            binding_identifier; 

    /* Information after this point is not accessible by the binding assembly code and
       therefore can be modified without disturbing the binding.  */

    /* Define the run-time ID.  */
    u_long                                                  run_time_id;

    /* Define central error counters.  */
    u_long                                                  level_3_system_errors;
    u_long                                                  level_2_system_errors;
    u_long                                                  level_1_system_errors;

    /* Define the last interrupt error indication.  */
    PX5_INTERNAL_ERRNO_INTERRUPT_STORAGE

    /* Define the most recent error.  */
    u_int                                                   last_error_class;
    u_int                                                   last_error_sub_class;
    u_int                                                   last_error_id;
    const px5_thread_control *                              last_error_thread;
    u_long                                                  last_error_interrupt_level;

    /* Define the user-supplied memory information. This is used by default for allocating internal control
       blocks, stacks and other memory areas.  */
    void *                                                  memory_start;
    u_long                                                  memory_size;
    u_long *                                                available_memory_pointer;
    u_long                                                  available_size;
    void *                                                  (*memory_allocate_pointer)(u_int type, u_long size);
    u_long                                                  memory_allocate_pointer_verification_code;
    void                                                    (*memory_release_pointer)(u_int type, void *memory_to_release);
    u_long                                                  memory_release_pointer_verification_code;
    pthread_memorypool_t                                    memory_manager_pool;

    /* Define the highest priority ready at any given moment.  */
    int                                                     highest_active_priority;

    /* Defined the bitmap for the number of ready threads. Each bit represents
       a priority where one or more threads are ready for execution. If the bit
       is zero, there are no threads ready at that priority level.  */
    u_long                                                  ready_thread_bit_map[PX5_MAXIMUM_PRIORITIES/32];

    /* Define the list of ready threads. The list is indexed by priority.  */
    px5_thread_control *                                    ready_thread_list[PX5_MAXIMUM_PRIORITIES];

    /* Define the periodic timer interrupt count. This simply increments on every periodic timer interrupt.  */
    tick_t                                                  timer_interrupts;

    /* Define the mapping of physical time to internal timer ticks.  */
    u_long                                                  ticks_per_second;
    u_long                                                  nanoseconds_per_tick;

    /* Define the epoch.  */
    px5_time_t                                              epoch_seconds;
    u_long                                                  epoch_nanoseconds;

    /* Define the list of activated timers.  */
    px5_internal_timer_control *                            active_timer_list[PX5_ACTIVE_TIMER_LIST_SIZE];

    /* Define the current timer list pointer.  */
    px5_internal_timer_control **                           current_active_timer_list_pointer;

    /* Define the signal handler information.  */
    const px5_sigaction_t *                                 signal_handlers[PX5_MAXIMUM_SIGNALS];

    /* Define the created thread list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           threads_current_access;
    u_long                                                  total_created_threads;
    px5_thread_control *                                    created_thread_list;

    /* Define the created condition variable list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           condition_vars_current_access;
    u_long                                                  total_created_condition_vars;
    px5_condition_var_control *                             created_condition_var_list;

    /* Define the created event flags group list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           event_flags_current_access;
    u_long                                                  total_created_event_flags;
    px5_event_flags_control *                               created_event_flags_list;

    /* Define the created fastqueue list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           fastqueues_current_access;
    u_long                                                  total_created_fastqueues;
    px5_fastqueue_control *                                 created_fastqueue_list;

    /* Define the created memory pool list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           memorypools_current_access;
    u_long                                                  total_created_memorypools;
    px5_memorypool_control *                                created_memorypool_list;

    /* Define the created mutex list head pointer, created count, and current thread access.  */
    px5_thread_control volatile *                           mutexes_current_access;
    u_long                                                  total_created_mutexes;
    px5_mutex_control *                                     created_mutex_list;

    /* Define the created partition memory pool list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           partitionpools_current_access;
    u_long                                                  total_created_partitionpools;
    px5_partitionpool_control *                             created_partitionpool_list;

    /* Define the created queue list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           queues_current_access;
    u_long                                                  total_created_queues;
    px5_queue_control *                                     created_queue_list;

    /* Define the created semaphore list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           semaphores_current_access;
    u_long                                                  total_created_semaphores;
    px5_semaphore_control *                                 created_semaphore_list;

    /* Define the created ticktimer list head pointer, created count, and current thread access.  */
    px5_thread_control * volatile                           ticktimers_current_access;
    u_long                                                  total_created_ticktimers;
    px5_ticktimer_control *                                 created_ticktimer_list;

    /* Define the "main" thread control structure.  */
    px5_thread_control                                      main_thread;

    /* Define the deferred thread cleanup pointer.  */
    px5_thread_control *                                    deferred_memory_release_thread;

    /* Define the thread local storage global keys.  */
    px5_global_key                                          thread_local_storage_keys[PTHREAD_KEYS_MAX];


    /* Define the middleware function pointers.  */
    int                                                     (*file_close_routine)(int handle);
    u_long                                                  file_close_routine_verification_code;
    ssize_t                                                 (*file_read_routine)(int handle, void *  buffer, size_t  bytes_to_read);
    u_long                                                  file_read_routine_verification_code;
    ssize_t                                                 (*file_write_routine)(int handle, void *  buffer, size_t  bytes_to_write);
    u_long                                                  file_write_routine_verification_code;
    int                                                     (*net_close_routine)(int handle);
    u_long                                                  net_close_routine_verification_code;
    ssize_t                                                 (*net_read_routine)(int handle, void *  buffer, size_t  bytes_to_read);
    u_long                                                  net_read_routine_verification_code;
    ssize_t                                                 (*net_write_routine)(int handle, void *  buffer, size_t  bytest_to_write);
    u_long                                                  net_write_routine_verification_code; 

    /* Define an area for general extensions to the PX5 global data. By default, this is defined as 
       white-space above.  */
    PX5_GLOBAL_DATA_EXTENSION

    /* Define the optional verification code for the PX5 RTOS global variables.  */
    u_long                                                  global_verification_code;

} px5_global_data;


/* Define external reference of the PX5 RTOS global data.  */

extern px5_global_data                              px5_globals;


/******************************************************************************
 ******************* Section IV: MISRA Prototypes & Macros ********************
 *****************************************************************************/

/* Define MISRA and non-MISRA mappings.  */

#ifdef PX5_MISRA_ENABLE

/* Define the MISRA compliance function prototypes, that are typically written in assembly code.  */

typedef void                  (*misra_ticktimer_expiration)(const pthread_ticktimer_t *, void *);

void                          px5_misra_binding_interrupt_enable(void);
u_long                        px5_misra_binding_interrupt_disable(void);
u_long                        px5_misra_binding_interrupt_level_get(void);
void                          px5_misra_binding_interrupt_restore(u_long  previous_posture);
void                          px5_misra_binding_thread_preempt(void);
u_long *                      px5_misra_char_to_u_long_pointer_convert(char *  pointer);
void *                        px5_misra_cleanup_to_void_pointer_convert(void  (* cleanup_pointer)(void *));
void *                        px5_misra_close_to_void_pointer_convert(int  (* close_routine)(int  handle));
char *                        px5_misra_const_char_to_char_pointer_convert(const char *  pointer);
px5_mutex_control *           px5_misra_const_mutex_pointer_convert(const px5_mutex_control *  pointer);
px5_thread_control *          px5_misra_const_thread_pointer_convert(const px5_thread_control *  pointer);
u_long *                      px5_misra_const_u_long_pointer_convert(const u_long *  pointer);
void *                        px5_misra_const_void_pointer_convert(const void *  pointer);
void *                        px5_misra_expiration_to_void_pointer_convert(void  (* expiration_routine)(const pthread_ticktimer_t *, void *));
void *                        px5_misra_internal_timer_to_void_pointer_convert(void  (* internal_expiration_routine)(const struct px5_internal_timer_control_struct *));
mqd_t                         px5_misra_long_to_mqd_t(long value);
void *                        px5_misra_memory_allocate_to_void_pointer_convert(void *  (* memory_allocate_pointer)(u_int  type, u_long  size));
void *                        px5_misra_memory_release_to_void_pointer_convert(void  (* memory_release_pointer)(u_int  type, void *  memory_to_release));
u_char *                      px5_misra_memorypool_info_to_u_char_pointer_convert(px5_memorypool_block_info *  pointer);
u_long *                      px5_misra_message_header_to_u_long_pointer_convert(px5_queue_message_header *  header_pointer);
px5_queue_control *           px5_misra_mqd_t_handle_convert(mqd_t  handle);
u_char *                      px5_misra_partititon_info_to_u_char_pointer_convert(px5_partition_info *  pointer);
void *                        px5_misra_pthread_canceled(void);
px5_thread_control *          px5_misra_pthread_t_handle_convert(pthread_t  handle);
void *                        px5_misra_read_to_void_pointer_convert(ssize_t  (* read_routine)(int  handle, void *  buffer, size_t  bytes_to_read));
px5_thread_control **         px5_misra_schedule_list_index(px5_thread_control **  schedule_list, int  core);
void *                        px5_misra_signal_to_void_pointer_convert(void  (* signal_handler)(int  number));
void *                        px5_misra_thread_to_void_pointer_convert(void *  (* thread_entry_routine)(void *  argument));
px5_thread_control *          px5_misra_thread_control_pointer_add(px5_thread_control *  pointer, u_long  threads, u_long  size_of_thread_control);
misra_ticktimer_expiration    px5_misra_ticktimer_expiration_const_convert(void (*  expiration)(pthread_ticktimer_t *  ticktimer_pointer, void *  argument));
px5_internal_timer_control ** px5_misra_timer_control_pointer_add(px5_internal_timer_control **  pointer, u_long  timers);
int                           px5_misra_timer_control_pointer_gteq_compare(px5_internal_timer_control **  pointer1, px5_internal_timer_control **  pointer2);
int                           px5_misra_timer_control_pointer_lteq_compare(px5_internal_timer_control **  pointer1, px5_internal_timer_control **  pointer2);
unsigned int                  px5_misra_timer_control_pointers_subtract(px5_internal_timer_control **  pointer1, px5_internal_timer_control **  pointer2);
u_char *                      px5_misra_u_char_pointer_add(u_char *  pointer, u_long  bytes);
u_char *                      px5_misra_u_char_pointer_subtract(u_char *  pointer, u_long  bytes);
size_t                        px5_misra_u_char_pointers_subtract(u_char *  pointer1, u_char *  pointer2);
px5_memorypool_block_info *   px5_misra_u_char_to_memorypool_info_pointer_convert(u_char *  pointer);
px5_partition_info *          px5_misra_u_char_to_partition_info_pointer_convert(u_char *  pointer);
int                           px5_misra_u_long_pointer_gt_compare(u_long *  pointer1, u_long *  pointer2);
u_long *                      px5_misra_u_long_pointer_lword_add(u_long *  pointer, u_long  words);
u_long *                      px5_misra_u_long_pointer_lword_subtract(u_long *  pointer, u_long  words);
u_long                        px5_misra_u_long_pointer_to_u_long_convert(u_long *  pointer);
u_long *                      px5_misra_u_long_pointer_word_add(u_long *  pointer, size_t  words);
u_long                        px5_misra_u_long_pointers_subtract(u_long *  pointer1, u_long *  pointer2);
px5_queue_message_header *    px5_misra_u_long_to_message_header_pointer_convert(u_long *  pointer);
px5_thread_control *          px5_misra_u_long_to_thread_pointer_convert(u_long  value);
u_char *                      px5_misra_u_long_to_u_char_pointer_convert(u_long *  pointer);
u_long                        px5_misra_void_pointer_to_u_long_convert(void *  pointer);
px5_condition_var_control *   px5_misra_void_to_condition_var_pointer_convert(void *  pointer);
px5_event_flags_control *     px5_misra_void_to_event_flags_pointer_convert(void *  pointer);
px5_fastqueue_control *       px5_misra_void_to_fastqueue_pointer_convert(void *  pointer);
px5_memorypool_control *      px5_misra_void_to_memorypool_pointer_convert(void *  pointer);
px5_mutex_control *           px5_misra_void_to_mutex_pointer_convert(void *  pointer);
px5_queue_control *           px5_misra_void_to_queue_pointer_convert(void *  pointer);
px5_partitionpool_control *   px5_misra_void_to_partitionpool_pointer_convert(void *  pointer);
px5_partition_info *          px5_misra_void_to_partition_info_pointer_convert(void *  pointer);
px5_semaphore_control *       px5_misra_void_to_semaphore_pointer_convert(void *  pointer);
px5_thread_control *          px5_misra_void_to_thread_pointer_convert(void *  pointer);
px5_ticktimer_control *       px5_misra_void_to_ticktimer_pointer_convert(void *  pointer);
u_char *                      px5_misra_void_to_u_char_pointer_convert(void *  pointer);
u_long *                      px5_misra_void_to_u_long_pointer_convert(void *  pointer);
void *                        px5_misra_write_to_void_pointer_convert(ssize_t  (* write_routine)(int handle, void *  buffer, size_t  bytes_to_write));
void *                        px5_misra_semaphore_notify_to_void_pointer_convert(void (*post_callback)(sem_t *));
void *                        px5_misra_event_flags_notify_to_void_pointer_convert(void (*set_callback)(pthread_event_flags_t *));
void *                        px5_misra_fastqueue_notify_to_void_pointer_convert(void (*send_callback)(pthread_fastqueue_t *));
void *                        px5_misra_queue_notify_to_void_pointer_convert(void (*send_callback)(mqd_t));
void *                        px5_misra_pthread_key_to_void_pointer_convert(void (*key_destructor)(void *));
void                          px5_misra_send_notify_callback_access(void (*send_callback)(mqd_t));
void                          px5_misra_set_notify_callback_access(void (*set_callback)(pthread_event_flags_t *));
void                          px5_misra_fastsend_notify_callback_access(void (*send_callback)(pthread_fastqueue_t *));
void                          px5_misra_post_notify_callback_access(void (*post_callback)(sem_t *));


/* Define the MISRA compliance macros that utilize the MISRA function prototypes.  */

#define PX5_CHAR_TO_U_LONG_POINTER(a)                       px5_misra_char_to_u_long_pointer_convert((a))
#define PX5_CONST_CHAR_TO_CHAR_POINTER(a)                   px5_misra_const_char_to_char_pointer_convert((a))
#define PX5_CONST_MUTEX_POINTER_CONVERT(a)                  px5_misra_const_mutex_pointer_convert((a))
#define PX5_CONST_THREAD_POINTER_CONVERT(a)                 px5_misra_const_thread_pointer_convert((a))
#define PX5_CONST_U_LONG_POINTER_CONVERT(a)                 px5_misra_const_u_long_pointer_convert((a))
#define PX5_CONST_VOID_POINTER_CONVERT(a)                   px5_misra_const_void_pointer_convert((a))
#define PX5_LONG_TO_MQD_T(a)                                px5_misra_long_to_mqd_t((a))
#define PX5_MEMORYPOOL_INFO_TO_U_CHAR_POINTER(a)            px5_misra_memorypool_info_to_u_char_pointer_convert((a))
#define PX5_MESSAGE_HEADER_TO_U_LONG_POINTER(a)             px5_misra_message_header_to_u_long_pointer_convert((a))
#define PX5_MQ_HANDLE_CONVERT(a)                            px5_misra_mqd_t_handle_convert((a))
#define PX5_PARTITION_INFO_TO_U_CHAR_POINTER(a)             px5_misra_partititon_info_to_u_char_pointer_convert((a))
#define PX5_PTHREAD_HANDLE_CONVERT(a)                       px5_misra_pthread_t_handle_convert((a))
#define PX5_SCHEDULE_LIST_INDEX(a, b)                       px5_misra_schedule_list_index((a), (b))
#define PX5_THREAD_CONTROL_POINTER_ADD(a,b)                 px5_misra_thread_control_pointer_add((a), (b), ((u_long) sizeof(px5_thread_control)))
#define PX5_TICKTIMER_EXPIRATION_CONVERT(a)                 px5_misra_ticktimer_expiration_const_convert((a))
#define PX5_TIMER_CONTROL_POINTER_ADD(a,b)                  px5_misra_timer_control_pointer_add((a), (b))
#define PX5_TIMER_CONTROL_POINTER_GTEQ_COMPARE(a,b)         px5_misra_timer_control_pointer_gteq_compare((a), (b))
#define PX5_TIMER_CONTROL_POINTER_LTEQ_COMPARE(a,b)         px5_misra_timer_control_pointer_lteq_compare((a), (b))
#define PX5_TIMER_CONTROL_POINTERS_SUBTRACT(a,b)            px5_misra_timer_control_pointers_subtract((a), (b))
#define PX5_U_CHAR_POINTER_ADD(a,b)                         px5_misra_u_char_pointer_add((a), (b))
#define PX5_U_CHAR_POINTER_SUBTRACT(a,b)                    px5_misra_u_char_pointer_subtract((a), (b))
#define PX5_U_CHAR_POINTERS_SUBTRACT(a,b)                   px5_misra_u_char_pointers_subtract((a), (b))
#define PX5_U_CHAR_TO_MEMORYPOOL_INFO_POINTER(a)            px5_misra_u_char_to_memorypool_info_pointer_convert((a))
#define PX5_U_CHAR_TO_PARTITION_INFO_POINTER(a)             px5_misra_u_char_to_partition_info_pointer_convert((a))
#define PX5_U_LONG_GT_COMPARE(a,b)                          px5_misra_u_long_pointer_gt_compare((a), (b))
#define PX5_U_LONG_POINTER_LWORD_ADD(a,b)                   px5_misra_u_long_pointer_lword_add((a), (b))
#define PX5_U_LONG_POINTER_LWORD_SUBTRACT(a,b)              px5_misra_u_long_pointer_lword_subtract((a), (b))
#define PX5_U_LONG_POINTER_TO_U_LONG(a)                     px5_misra_u_long_pointer_to_u_long_convert((a))
#define PX5_U_LONG_POINTER_WORD_ADD(a,b)                    px5_misra_u_long_pointer_word_add((a), (b))
#define PX5_U_LONG_POINTERS_SUBTRACT(a,b)                   px5_misra_u_long_pointers_subtract((a), (b))
#define PX5_U_LONG_TO_MESSAGE_HEADER_POINTER(a)             px5_misra_u_long_to_message_header_pointer_convert((a))
#define PX5_U_LONG_TO_THREAD_POINTER(a)                     px5_misra_u_long_to_thread_pointer_convert((a))
#define PX5_U_LONG_TO_U_CHAR_POINTER(a)                     px5_misra_u_long_to_u_char_pointer_convert((a))
#define PX5_VOID_POINTER_TO_U_LONG(a)                       px5_misra_void_pointer_to_u_long_convert((a))
#define PX5_VOID_TO_CONDITION_VAR_POINTER(a)                px5_misra_void_to_condition_var_pointer_convert((a))
#define PX5_VOID_TO_EVENT_FLAGS_POINTER(a)                  px5_misra_void_to_event_flags_pointer_convert((a))
#define PX5_VOID_TO_FASTQUEUE_POINTER(a)                    px5_misra_void_to_fastqueue_pointer_convert((a))
#define PX5_VOID_TO_MEMORYPOOL_POINTER(a)                   px5_misra_void_to_memorypool_pointer_convert((a))
#define PX5_VOID_TO_MUTEX_POINTER(a)                        px5_misra_void_to_mutex_pointer_convert((a))
#define PX5_VOID_TO_QUEUE_POINTER(a)                        px5_misra_void_to_queue_pointer_convert((a))
#define PX5_VOID_TO_PARTITIONPOOL_POINTER(a)                px5_misra_void_to_partitionpool_pointer_convert((a))
#define PX5_VOID_TO_PARTITION_INFO_POINTER(a)               px5_misra_void_to_partition_info_pointer_convert((a))
#define PX5_VOID_TO_SEMAPHHORE_POINTER(a)                   px5_misra_void_to_semaphore_pointer_convert((a))
#define PX5_VOID_TO_THREAD_POINTER(a)                       px5_misra_void_to_thread_pointer_convert((a))
#define PX5_VOID_TO_TICKTIMER_POINTER(a)                    px5_misra_void_to_ticktimer_pointer_convert((a))
#define PX5_VOID_TO_U_CHAR_POINTER(a)                       px5_misra_void_to_u_char_pointer_convert((a))
#define PX5_VOID_TO_U_LONG_POINTER(a)                       px5_misra_void_to_u_long_pointer_convert((a))

#else

/* Define the standard macro mappings that are not MISRA compliant.  */

#define PX5_CHAR_TO_U_LONG_POINTER(a)                       ((u_long *) (a))
#define PX5_CONST_CHAR_TO_CHAR_POINTER(a)                   ((char *) (a))
#define PX5_CONST_MUTEX_POINTER_CONVERT(a)                  ((px5_mutex_control *) (a))
#define PX5_CONST_THREAD_POINTER_CONVERT(a)                 ((px5_thread_control *) (a))
#define PX5_CONST_U_LONG_POINTER_CONVERT(a)                 ((u_long *) (a))
#define PX5_CONST_VOID_POINTER_CONVERT(a)                   ((void *) (a))
#define PX5_LONG_TO_MQD_T(a)                                ((mqd_t) (a))
#define PX5_MEMORYPOOL_INFO_TO_U_CHAR_POINTER(a)            ((u_char *) (a))
#define PX5_MESSAGE_HEADER_TO_U_LONG_POINTER(a)             ((u_long *) (a))
#define PX5_MQ_HANDLE_CONVERT(a)                            ((px5_queue_control *) (a))
#define PX5_PARTITION_INFO_TO_U_CHAR_POINTER(a)             ((u_char *) (a))
#define PX5_PTHREAD_HANDLE_CONVERT(a)                       ((px5_thread_control *) (a))
#define PX5_SCHEDULE_LIST_INDEX(a, b)                       ((a) + (b))
#define PX5_THREAD_CONTROL_POINTER_ADD(a,b)                 ((a) + (b))
#define PX5_TICKTIMER_EXPIRATION_CONVERT(a)                 ((void (* )(const pthread_ticktimer_t *, void *)) (a))
#define PX5_TIMER_CONTROL_POINTER_ADD(a,b)                  ((a) + (b))
#define PX5_TIMER_CONTROL_POINTER_GTEQ_COMPARE(a,b)         ((a) >= (b))
#define PX5_TIMER_CONTROL_POINTER_LTEQ_COMPARE(a,b)         ((a) <= (b))
#define PX5_TIMER_CONTROL_POINTERS_SUBTRACT(a,b)            ((a) - (b))
#define PX5_U_CHAR_POINTER_ADD(a,b)                         ((a) + (b))
#define PX5_U_CHAR_POINTER_SUBTRACT(a,b)                    ((a) - (b))
#define PX5_U_CHAR_POINTERS_SUBTRACT(a,b)                   ((a) - (b))
#define PX5_U_CHAR_TO_MEMORYPOOL_INFO_POINTER(a)            ((px5_memorypool_block_info *) (a))
#define PX5_U_CHAR_TO_PARTITION_INFO_POINTER(a)             ((px5_partition_info *) (a))
#define PX5_U_LONG_GT_COMPARE(a,b)                          ((a) > (b))
#define PX5_U_LONG_POINTER_LWORD_ADD(a,b)                   ((a) + (b))
#define PX5_U_LONG_POINTER_LWORD_SUBTRACT(a,b)              ((a) - (b))
#define PX5_U_LONG_POINTER_TO_U_LONG(a)                     ((u_long) (a))
#define PX5_U_LONG_POINTER_WORD_ADD(a,b)                    ((a) + (b))
#define PX5_U_LONG_POINTERS_SUBTRACT(a,b)                   ((a) - (b))
#define PX5_U_LONG_TO_MESSAGE_HEADER_POINTER(a)             ((px5_queue_message_header *) (a))
#define PX5_U_LONG_TO_THREAD_POINTER(a)                     ((px5_thread_control *) (a))
#define PX5_U_LONG_TO_U_CHAR_POINTER(a)                     ((u_char *) (a))
#define PX5_VOID_POINTER_TO_U_LONG(a)                       ((u_long) (a))
#define PX5_VOID_TO_CONDITION_VAR_POINTER(a)                ((px5_condition_var_control *) (a))
#define PX5_VOID_TO_EVENT_FLAGS_POINTER(a)                  ((px5_event_flags_control *) (a))
#define PX5_VOID_TO_FASTQUEUE_POINTER(a)                    ((px5_fastqueue_control *) (a))
#define PX5_VOID_TO_MEMORYPOOL_POINTER(a)                   ((px5_memorypool_control *) (a))
#define PX5_VOID_TO_MUTEX_POINTER(a)                        ((px5_mutex_control *) (a))
#define PX5_VOID_TO_QUEUE_POINTER(a)                        ((px5_queue_control *) (a))
#define PX5_VOID_TO_PARTITIONPOOL_POINTER(a)                ((px5_partitionpool_control *) (a))
#define PX5_VOID_TO_PARTITION_INFO_POINTER(a)               ((px5_partition_info *) (a))
#define PX5_VOID_TO_SEMAPHHORE_POINTER(a)                   ((px5_semaphore_control *) (a))
#define PX5_VOID_TO_THREAD_POINTER(a)                       ((px5_thread_control *) (a))
#define PX5_VOID_TO_TICKTIMER_POINTER(a)                    ((px5_ticktimer_control *) (a))
#define PX5_VOID_TO_U_CHAR_POINTER(a)                       ((u_char *) (a))
#define PX5_VOID_TO_U_LONG_POINTER(a)                       ((u_long *) (a))

#endif 


/******************************************************************************
 ********************* Section V: Internal Core Prototypes ********************
 *****************************************************************************/

void *          px5_internal_memory_allocate(u_int type, u_long  size);
void *          px5_internal_memory_manager_allocate(u_int type, u_long size);
void            px5_internal_memory_manager_release(u_int type, void *  memory_to_release);
#if PX5_MAXIMUM_CORES>1
int             px5_internal_smp_core_insert(const px5_thread_control *  thread_pointer, u_long  target_cores, px5_thread_control **  schedule_list);
void            px5_internal_smp_load_balance(void);
int             px5_internal_smp_lowest_core_get(u_long  examine_cores);
int             px5_internal_smp_remap_check(px5_thread_control *   thread_pointer);
#endif /* PX5_MAXIMUM_CORES>1  */
void            px5_internal_thread_enter_notify(const px5_thread_control *  thread_pointer);
void            px5_internal_thread_exit_notify(const px5_thread_control *  thread_pointer);
void            px5_internal_thread_local_storage_cleanup(px5_thread_control *  thread_pointer);
void            px5_internal_thread_priority_change(px5_thread_control *  thread_pointer);
void            px5_internal_thread_ready(px5_thread_control *  thread_pointer, px5_suspension_info *  suspension_info);
void            px5_internal_thread_suspend(px5_thread_control *  thread_pointer, int  suspension_state, px5_suspension_info *  suspension_info, tick_t  suspension_timeout);
void            px5_internal_thread_timer_process(const px5_internal_timer_control *  internal_timer);
void            px5_internal_thread_wrapper(void);
void            px5_internal_ticktimer_expire(const px5_internal_timer_control *  internal_timer);
void            px5_internal_time_slice_process(void);
void            px5_internal_timer_activate(px5_internal_timer_control *  internal_timer);
void            px5_internal_timer_deactivate(px5_internal_timer_control *  internal_timer_pointer);
void            px5_internal_timer_list_process(void);


/******************************************************************************
 ****************** Section VI: Internal Utility Prototypes *******************
 *****************************************************************************/

void            px5_internal_call_error_check(int status);
px5_thread_control * 
                px5_internal_current_context_get(void);
u_long          px5_internal_data_verification_code_compute(u_long  data, u_long *  code_destination);
void            px5_internal_data_verification_code_create(u_long  data, u_long *  code_destination);
void            px5_internal_data_verification_code_verify(u_long  data, u_long *  code_destination, u_int  error_id);
int             px5_internal_highest_set_bit_get(u_long word);
u_int           px5_internal_highest_signal_get(sigset_t  signal_set);
void            px5_internal_memcpy(void *  destination, void *  source, size_t  bytes_to_copy);
void            px5_internal_memset(void *  destination, int  value, size_t  bytes_to_set);
u_long          px5_internal_pointer_verification_code_compute(void *  pointer, u_long *  code_destination);
void            px5_internal_pointer_verification_code_create(void *  pointer, u_long *  code_destination);
void            px5_internal_pointer_verification_code_verify(void *  pointer, u_long *  code_destination, u_int  error_id);
void            px5_internal_thread_cleanup_handlers_execute(px5_thread_control *  this_thread);
void            px5_internal_thread_control_created_list_append(px5_thread_control *  this_thread);
void            px5_internal_thread_control_created_list_remove(px5_thread_control *  this_thread);
void            px5_internal_thread_deferred_memory_release(void);
void            px5_internal_thread_stack_size_check(u_int id);


/******************************************************************************
 *************** Section VII: Internal Error Handling Prototypes **************
 *****************************************************************************/

void            px5_internal_central_error_process(u_int error_class, u_int error_sub_class, u_int  error_id); 
void            px5_internal_thread_entry_validity_check(px5_thread_control *  this_thread);
void            px5_internal_thread_invalid_return_error_handler(void);
void            px5_internal_thread_validity_check(px5_thread_control *  this_thread);


/******************************************************************************
 ***************** Section VIII: Binding Function Prototypes ******************
 *****************************************************************************/

void            px5_binding_initialize_begin(void);
void            px5_binding_initialize_finish(void);
u_long *        px5_binding_main_stack_base_get(void);
u_long *        px5_binding_main_stack_limit_get(void);
u_long          px5_binding_main_stack_minimum_stack_size_get(void);
u_long *        px5_binding_main_stack_pointer_get(void);
u_long          px5_binding_main_stack_size_get(void);
void            px5_binding_stack_frame_build(px5_thread_control *  this_thread, void (* execution_pointer)(void));
u_long *        px5_binding_system_stack_pointer_get(void);
int             px5_binding_verify(px5_thread_control *  this_thread, u_int thread_control_sizeof);


/******************************************************************************
 *********************** Section IX: Middleware Support ***********************
 *****************************************************************************/

/* Map close, read, and write function calls to the RTOS dispatch call.  */

#define close                                               px5_rtos_close_dispatch
#define read                                                px5_rtos_read_dispatch
#define write                                               px5_rtos_write_dispatch


/* Define the starting PX5 FILE base handle value.  */

#ifndef PX5_FILE_HANDLE_BASE
#define PX5_FILE_HANDLE_BASE                                8192
#endif  /* PX5_FILE_HANDLE_BASE */

void           px5_rtos_file_close_register(int  (* close_routine)(int handle));
void           px5_rtos_file_read_register(ssize_t  (* read_routine)(int handle, void *  buffer, size_t  bytes_to_read));
void           px5_rtos_file_write_register(ssize_t  (* write_routine)(int handle, void *  buffer, size_t  bytes_to_write));
void           px5_rtos_net_close_register(int  (* close_routine)(int handle));
void           px5_rtos_net_read_register(ssize_t  (* read_routine)(int handle, void *  buffer, size_t  bytes_to_read));
void           px5_rtos_net_write_register(ssize_t  (* write_routine)(int handle, void *  buffer, size_t  bytest_to_write));
int            px5_rtos_close_dispatch(int  handle);
ssize_t        px5_rtos_read_dispatch(int  handle, const void *  buffer, size_t  bytes_to_read);
ssize_t        px5_rtos_write_dispatch(int  handle, const void *  buffer, size_t  bytes_to_write);


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_HEADER */
