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

#ifndef PX5_PTHREADTYPES_HEADER
#define PX5_PTHREADTYPES_HEADER


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Constants
   Section II:  Base types

******************************************************************************/

/******************************************************************************
 ************** Section I: Constants, Enumerations, and Macros ****************
 *****************************************************************************/


/* Define object handle IDs.  */

#define PX5_CONDITION_VAR_HANDLE_ID                         0x434F4E48UL
#define PX5_EVENT_FLAGS_HANDLE_ID                           0x45564548UL
#define PX5_FASTQUEUE_HANDLE_ID                             0x46515548UL
#define PX5_MEMORYPOOL_HANDLE_ID                            0x4D454D48UL
#define PX5_PARTITIONPOOL_HANDLE_ID                         0x50415248UL
#define PX5_MUTEX_HANDLE_ID                                 0x4D555448UL
#define PX5_TICKTIMER_HANDLE_ID                             0x54494348UL


/* Default attribute extensions to whitespace.  */

#ifndef PX5_PTHREAD_ATTR_T_EXTENSIONS
#define PX5_PTHREAD_ATTR_T_EXTENSIONS
#endif  /* PX5_PTHREAD_ATTR_T_EXTENSIONS */

#ifndef PX5_PTHREAD_CONDATTR_T_EXTENSIONS
#define PX5_PTHREAD_CONDATTR_T_EXTENSIONS
#endif  /* PX5_PTHREAD_CONDATTR_T_EXTENSIONS */

#ifndef PX5_PTHREAD_EVENT_FLAGSATTR_T_EXTENSIONS
#define PX5_PTHREAD_EVENT_FLAGSATTR_T_EXTENSIONS
#endif  /* PX5_PTHREAD_EVENT_FLAGSATTR_T_EXTENSIONS */

#ifndef PX5_PTHREAD_FASTQUEUEATTR_T_EXTENSIONS
#define PX5_PTHREAD_FASTQUEUEATTR_T_EXTENSIONS
#endif  /* PX5_PTHREAD_FASTQUEUEATTR_T_EXTENSIONS */

#ifndef PX5_PTHREAD_MEMORYPOOLATTR_T_EXTENSIONS
#define PX5_PTHREAD_MEMORYPOOLATTR_T_EXTENSIONS
#endif  /* PX5_PTHREAD_MEMORYPOOLATTR_T_EXTENSIONS */

#ifndef PX5_PTHREAD_MUTEXATTR_T_EXTENSIONS
#define PX5_PTHREAD_MUTEXATTR_T_EXTENSIONS
#endif  /* PX5_PTHREAD_MUTEXATTR_T_EXTENSIONS */

#ifndef PX5_PTHREAD_PARTITIONPOOLATTR_T_EXTENSIONS
#define PX5_PTHREAD_PARTITIONPOOLATTR_T_EXTENSIONS
#endif  /* PX5_PTHREAD_PARTITIONPOOLATTR_T_EXTENSIONS */

#ifndef PX5_PTHREAD_TICKTIMERATTR_T_EXTENSIONS
#define PX5_PTHREAD_TICKTIMERATTR_T_EXTENSIONS
#endif  /* PX5_PTHREAD_TICKTIMERATTR_T_EXTENSIONS */


/******************************************************************************
 ************************** Section II: Base types ****************************
 *****************************************************************************/

/* Define base pthread types.  */


/* Define the cpu set for thread processor affinity.  Each bit in the type represents a core the thread is allowed to execute on.  */

typedef u_long  cpu_set_t;


/* Define the thread attribute type, which contains various information for thread creation.  */

typedef struct pthread_attr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  attributes_id;

    /* Define name.  */
    const char *                                            name;

    /* Detach state - either PTHREAD_CREATE_JOINABLE (default) or PTHREAD_CREATE_DETACHED. */
    int                                                     detach_state;

    /* Address of thread stack memory provided by application.  */
    void *                                                  stack_address;

    /* Size of thread stack (in bytes).  */
    size_t                                                  stack_size;

    /* Address of the thread control structure provided by the application.  */
    void *                                                  thread_control_address;

    /* Size of thread control structure (in bytes).  */
    size_t                                                  thread_control_size;

    /* Priority of thread.  */
    int                                                     priority;

    /* Time-slice of the thread (0 is default and represents no time-slice).  */
    u_long                                                  time_slice;                     

    /* Automatic start selection.  */
    int                                                     automatic_start;

#if PX5_MAXIMUM_CORES>1

    /* Initial core affinity.  */
    cpu_set_t                                               core_affinity;

#endif /* PX5_MAXIMUM_CORES>1  */


    /* Define extensions to the pthread_attr_t structure.  */
    PX5_PTHREAD_ATTR_T_EXTENSIONS

} pthread_attr_t;


/* Define the condition variable attribute type, which is optionally used to initialize a conditional variable.  */

typedef struct pthread_condattr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  condition_var_attr_id;

    /* Define name.  */
    const char *                                            name;

    /* Define the condition variable shared designation.  */
    int                                                     shared_designation;

    /* Define the user-specified condition variable control memory address.  */
    void *                                                  condition_var_control_address;

    /* Define extensions to the pthread_condattr_t structure.  */
    PX5_PTHREAD_CONDATTR_T_EXTENSIONS

} pthread_condattr_t;


/* Define forward references for internal condition variable control structures.  */

struct px5_condition_var_control_struct; 


/* Define the condition variable handle type, which is effectively contains a pointer to the internal condition variable control structure.  */

typedef struct pthread_cond_t_struct
{

    /* Define the ID of condition variable handle structure.  */
    u_long                                                  condition_var_handle_id;

    /* Pointer to the internal condition variable control structure.  */
    struct px5_condition_var_control_struct *               internal_condition_var_control;
    
} pthread_cond_t;


/* Define the event flags attribute type, which is optionally used to create an event flags group.  */

typedef struct pthread_event_flagsattr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  event_flagsattr_id;

    /* Define name.  */
    const char *                                            name;

    /* Define the user-specified event flags control memory address.  */
    void *                                                  event_flags_control_address;

#ifndef PX5_EVENT_FLAG_CONSUMPTION_MASK_DISABLE

    /* Define the automatic event consumption mask, which can be used to disable automatic consumption of any event.  */
    u_long                                                  automatic_event_consumption_mask;
#endif  /* PX5_EVENT_FLAG_CONSUMPTION_MASK_DISABLE  */

    /* Define extensions to the pthread_event_flagsattr_t structure.  */
    PX5_PTHREAD_EVENT_FLAGSATTR_T_EXTENSIONS

} pthread_event_flagsattr_t;


/* Define forward references for internal event flags control structures.  */

struct px5_event_flags_control_struct; 


/* Define the event flags handle type, which is effectively contains a pointer to the internal event flags control structure.  */

typedef struct pthread_event_flags_t_struct
{

    /* Define the ID of event flags handle structure.  */
    u_long                                                  event_flags_handle_id;

    /* Pointer to the internal event flags control structure.  */
    struct px5_event_flags_control_struct *                 internal_event_flags_control;
    
} pthread_event_flags_t;


/* Define the fastqueue attribute type, which is optionally used to create an fastqueue.  */

typedef struct pthread_fastqueueattr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  fastqueueattr_id;

    /* Define name.  */
    const char *                                            name;

    /* Define the user-specified fastqueue control memory address.  */
    void *                                                  fastqueue_control_address;

    /* Define the user-specified fastqueue message area address.  */
    void *                                                  fastqueue_message_area_address;

    /* Define the user-specified fastqueue message area size.  */
    size_t                                                  fastqueue_message_area_size;

    /* Define extensions to the pthread_fastqueueattr_t structure.  */
    PX5_PTHREAD_FASTQUEUEATTR_T_EXTENSIONS

} pthread_fastqueueattr_t;


/* Define forward references for internal fastqueue control structures.  */

struct px5_fastqueue_control_struct; 


/* Define the fastqueue handle type, which is effectively contains a pointer to the internal fastqueue control structure.  */

typedef struct pthread_fastqueue_t_struct
{

    /* Define the ID of fastqueue handle structure.  */
    u_long                                                  fastqueue_handle_id;

    /* Pointer to the internal fastqueue control structure.  */
    struct px5_fastqueue_control_struct *                   internal_fastqueue_control;
    
} pthread_fastqueue_t;


/* Define the memory pool attribute type, which is optionally used to create a memory pool.  */

typedef struct pthread_memorypoolattr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  memorypoolattr_id;

    /* Define name.  */
    const char *                                            name;

    /* Define the user-specified memory pool control memory address.  */
    void *                                                  memorypool_control_address;

    /* Define extensions to the pthread_memorypoolattr_t structure.  */
    PX5_PTHREAD_MEMORYPOOLATTR_T_EXTENSIONS

} pthread_memorypoolattr_t;


/* Define forward references for internal memory control structures.  */

struct px5_memorypool_control_struct; 


/* Define the memory pool handle type, which is effectively contains a pointer to the internal memory pool control structure.  */

typedef struct pthread_memorypool_t_struct
{

    /* Define the ID of memory pool handle structure.  */
    u_long                                                  memorypool_handle_id;

    /* Pointer to the internal memory pool control structure.  */
    struct px5_memorypool_control_struct *                  internal_memorypool_control;
    
} pthread_memorypool_t;


/* Define the mutex attribute type, which is optionally used to initialize a mutex.  */

typedef struct pthread_mutexattr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  mutexattr_id;

    /* Define name.  */
    const char *                                            name;

    /* Define the mutex shared designation.  */
    int                                                     shared_designation;

    /* Define the mutex type.  */
    int                                                     type;

    /* Define the maximum nesting.  */
    u_long                                                  maximum_nesting;

    /* Define the mutex protocol.  */
    int                                                     protocol;

    /* Define the user-specified mutex control memory address.  */
    void *                                                  mutex_control_address;

    /* Define extensions to the pthread_mutexattr_t structure.  */
    PX5_PTHREAD_MUTEXATTR_T_EXTENSIONS

} pthread_mutexattr_t;


/* Define forward references for internal mutex control structures.  */

struct px5_mutex_control_struct; 


/* Define the mutex handle type, which is effectively contains a pointer to the internal mutex control structure.  */

typedef struct pthread_mutex_t_struct
{

    /* Define the ID of mutex handle structure.  */
    u_long                                                  mutex_handle_id;

    /* Pointer to the internal mutex control structure.  */
    struct px5_mutex_control_struct *                       internal_mutex_control;
    
} pthread_mutex_t;


/* Define the partition memory pool attribute type, which is optionally used to create a partition pool.  */

typedef struct pthread_partitionpoolattr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  partitionpoolattr_id;

    /* Define name.  */
    const char *                                            name;

    /* Define the user-specified partition memory pool control memory address.  */
    void *                                                  partitionpool_control_address;

    /* Define extensions to the pthread_partitionpoolattr_t structure.  */
    PX5_PTHREAD_PARTITIONPOOLATTR_T_EXTENSIONS

} pthread_partitionpoolattr_t;


/* Define forward references for internal partition memory control structures.  */

struct px5_partitionpool_control_struct; 


/* Define the partition pool handle type, which is effectively contains a pointer to the internal partition pool control structure.  */

typedef struct pthread_partitionpool_t_struct
{

    /* Define the ID of partition pool handle structure.  */
    u_long                                                  partitionpool_handle_id;

    /* Pointer to the internal partition pool control structure.  */
    struct px5_partitionpool_control_struct *               internal_partitionpool_control;
    
} pthread_partitionpool_t;


/* Define the basic timertick type.  */

typedef unsigned long                                       tick_t;


/* Define the ticktimer attribute type, which is optionally used to initialize a ticktimer.  */

typedef struct pthread_ticktimerattr_t_struct
{

    /* Define ID of attributes structure. */
    u_long                                                  ticktimerattr_id;

    /* Define name.  */
    const char *                                            name;

    /* Define the user-specified ticktimer control memory address.  */
    void *                                                  ticktimer_control_address;

    /* Define extensions to the pthread_ticktimerattr_t structure.  */
    PX5_PTHREAD_TICKTIMERATTR_T_EXTENSIONS

} pthread_ticktimerattr_t;


/* Define forward references for internal ticktimer control structures.  */

struct px5_ticktimer_control_struct; 


/* Define the ticktimer handle type, which is effectively contains a pointer to the internal ticktimer control structure.  */

typedef struct pthread_ticktimer_t_struct
{

    /* Define the ID of ticktimer handle structure.  */
    u_long                                                  ticktimer_handle_id;

    /* Pointer to the internal ticktimer control structure.  */
    struct px5_ticktimer_control_struct *                   internal_ticktimer_control;
    
} pthread_ticktimer_t;


/* Define the thread handle type, which is used by the application to access threads 
   through the pthreads API.  */

typedef const void *                                        pthread_t;


/* Define the thread once type, which is used as a flag to perform one-time initialization.  */

typedef u_long                                              pthread_once_t;


/* Define the key type for thread local storage.  */

typedef u_long                                              pthread_key_t;


#endif  /* PX5_PTHREADTYPES_HEADER */
