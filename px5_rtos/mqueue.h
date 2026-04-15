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

#ifndef PX5_MQUEUE_HEADER
#define PX5_MQUEUE_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  Message Queue Constants
   Section III: Message Queue Types
   Section IV:  PX5 API Mapping
   Section V:   Actual PX5 API prototypes

******************************************************************************/


/******************************************************************************
 ************************** Section I: Include Files **************************
 *****************************************************************************/

#include "sys/types.h"
#include "px5_time.h"
#include "px5_errno.h"
#include "fcntl.h"
#include "sys/stat.h"


/******************************************************************************
 ****************** Section II:  Message Queue Constants **********************
 *****************************************************************************/

#define PX5_QUEUE_ATTR_ID                                   0x4D515541UL


/* Default attribute extensions to whitespace.  */

#ifndef PX5_MQ_ATTR_EXTENSIONS
#define PX5_MQ_ATTR_EXTENSIONS
#endif  /* PX5_MQ_ATTR_EXTENSIONS */

#ifndef PX5_MQ_EXTENDATTR_T_EXTENSIONS
#define PX5_MQ_EXTENDATTR_T_EXTENSIONS
#endif  /* PX5_MQ_EXTENDATTR_T_EXTENSIONS */


/******************************************************************************
 ******************* Section III:  Message Queue Types ************************
 *****************************************************************************/


/* Define the message queue type, which is effectively contains a pointer to the internal message queue control structure.  */

typedef const void *                                        mqd_t;


/* Define the message queue attribute structure.  */

struct mq_attr
{

    /* Define flags. Note that these are not used for mq_open call, since they are supplied in the API itself.  */
    u_long                                                  mq_flags;

    /* Define the maximum number of messages.  */
    u_long                                                  mq_maxmsg;

    /* Define the maximum number of bytes per message.  */
    size_t                                                  mq_msgsize;

    /* Define the current number of messages currently in the queue.  Not applicable to mq_open API.  */
    u_long                                                  mq_curmsgs;

    /* Define extensions to the mq_attr structure.  */
    PX5_MQ_ATTR_EXTENSIONS
};


/* Define the message queue extended attribute structure.  */

typedef struct mq_extendattr_t_struct
{

    /* Define ID of extended message queue attributes structure. */
    u_long                                                  mq_extendattr_id;

    /* Define the user-specified message queue control memory address.  */
    void *                                                  mq_control_address;

    /* Define the user-specified message queue memory area address.  */
    void *                                                  mq_memory_area_address;

    /* Define the user-specified message queue memory area size.  */
    size_t                                                  mq_memory_area_size;

    /* Define extensions to the mq_extendattr_t structure.  */
    PX5_MQ_EXTENDATTR_T_EXTENSIONS

} mq_extendattr_t;



/******************************************************************************
 *********************** Section IV: PX5 API Mapping **************************
 *****************************************************************************/

/* Determine if PX5 source is present. If so, skip remapping.  */

#ifndef PX5_SOURCE_CODE


/* Determine if parameter checking is disabled. If so, skip parameter checking veener.  */

#ifndef PX5_PARAMETER_CHECKING_DISABLE

#define mq_close                                            px5_mq_close_check_params
#define px5_mq_extend_open                                  px5_mq_extend_open_check_params
#define mq_getattr                                          px5_mq_getattr_check_params
#define mq_open                                             px5_mq_open_check_params
#define mq_receive                                          px5_mq_receive_check_params
#define mq_send                                             px5_mq_send_check_params
#define mq_setattr                                          px5_mq_setattr_check_params
#define mq_timedreceive                                     px5_mq_timedreceive_check_params
#define mq_timedsend                                        px5_mq_timedsend_check_params

#else

#define mq_close                                            px5_mq_close
#define px5_mq_extend_open                                  px5_mq_extend_open
#define mq_getattr                                          px5_mq_getattr
#define mq_open                                             px5_mq_open
#define mq_receive                                          px5_mq_receive
#define mq_send                                             px5_mq_send
#define mq_setattr                                          px5_mq_setattr
#define mq_timedreceive                                     px5_mq_timedreceive
#define mq_timedsend                                        px5_mq_timedsend

#endif /* PX5_PARAMETER_CHECKING_DISABLE */

#endif /* PX5_SOURCE_CODE */


/******************************************************************************
 ******************** Section IV: Actual PX5 API prototypes *******************
 *****************************************************************************/

int             px5_mq_close(mqd_t  message_queue);
int             px5_mq_close_check_params(mqd_t  message_queue);
mqd_t           px5_mq_extend_open(const char *  queue_name, int operation, mode_t  mode, const struct mq_attr *  queue_attributes, mq_extendattr_t *  extend_attributes);
mqd_t           px5_mq_extend_open_check_params(const char *  queue_name, int operation, mode_t  mode, const struct mq_attr *  queue_attributes, mq_extendattr_t *  extend_attributes);
int             px5_mq_extendattr_destroy(mq_extendattr_t *  queue_attributes);
int             px5_mq_extendattr_getcontroladdr(const mq_extendattr_t *  queue_attributes, void **  queue_control_address);
int             px5_mq_extendattr_getcontrolsize(const mq_extendattr_t *  queue_attributes, size_t *  queue_control_size);
int             px5_mq_extendattr_getqueueaddr(const mq_extendattr_t *  queue_attributes, void **  queue_memory_address);
int             px5_mq_extendattr_getqueuesize(const mq_extendattr_t *  queue_attributes, size_t *  queue_memory_size);
int             px5_mq_extendattr_init(mq_extendattr_t *  queue_attributes);
int             px5_mq_extendattr_setcontroladdr(mq_extendattr_t *  queue_attributes, void *  queue_control_address, size_t  queue_control_size);
int             px5_mq_extendattr_setqueueaddr(mq_extendattr_t *  queue_attributes, void *  queue_memory_address, size_t  queue_memory_size);
int             px5_mq_getattr(mqd_t  message_queue, struct mq_attr *  queue_attributes);
int             px5_mq_getattr_check_params(mqd_t  message_queue, struct mq_attr *  queue_attributes);
int             px5_mq_information_get(const mqd_t *  queue_handle, char **  name, u_long *  messages_queued,  u_long *  maximum_messages,  u_long *  maximum_message_size, u_long *  threads_suspended,  pthread_t *  first_suspended_thread, mqd_t *  next_queue_handle);
mqd_t           px5_mq_open(const char *  queue_name, int operation, mode_t  mode, const struct mq_attr *  queue_attributes);
mqd_t           px5_mq_open_check_params(const char *  queue_name, int operation, mode_t  mode, const struct mq_attr *  queue_attributes);
ssize_t         px5_mq_receive(mqd_t  message_queue, char *  message, size_t message_size, unsigned int *  message_priority);
ssize_t         px5_mq_receive_check_params(mqd_t  message_queue, char *  message, size_t message_size, unsigned int *  message_priority);
int             px5_mq_send(mqd_t  message_queue, char *  message, size_t  message_size, unsigned int  message_priority);
int             px5_mq_send_check_params(mqd_t  message_queue, char *  message, size_t  message_size, unsigned int  message_priority);
#ifdef PX5_NOTIFICATION_ENABLE
int             px5_mq_send_notify(mqd_t  queue_handle, void (*send_callback)(mqd_t));
#else
int             px5_mq_send_notify(const mqd_t  queue_handle, void (*send_callback)(mqd_t));
#endif /* PX5_NOTIFICATION_ENABLE */
int             px5_mq_setattr(mqd_t  message_queue, const struct mq_attr *  queue_attributes, struct mq_attr *  previous_attributes);
int             px5_mq_setattr_check_params(mqd_t  message_queue, const struct mq_attr *  queue_attributes, struct mq_attr *  previous_attributes);
ssize_t         px5_mq_timedreceive(mqd_t  message_queue, char *  message, size_t message_size, unsigned int  *  message_priority, const struct px5_timespec *  absolute_timeout);
ssize_t         px5_mq_timedreceive_check_params(mqd_t  message_queue, char *  message, size_t message_size, unsigned int  *  message_priority, const struct px5_timespec *  absolute_timeout);
int             px5_mq_timedsend(mqd_t  message_queue, char *  message, size_t  message_size, unsigned int  message_priority, const struct px5_timespec *  absolute_timeout);
int             px5_mq_timedsend_check_params(mqd_t  message_queue, char *  message, size_t  message_size, unsigned int  message_priority, const struct px5_timespec *  absolute_timeout);


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_MQUEUE_HEADER */
