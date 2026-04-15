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

#ifndef PX5_ERRNO_HEADER
#define PX5_ERRNO_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Error constants
   Section II:  Errno mapping

******************************************************************************/


/******************************************************************************
 ************************ Section I: Errno constants **************************
 *****************************************************************************/

#define PX5_SUCCESS                                         0
#define PX5_ERROR                                          -1
#ifndef EACCES
#define EACCES                                              13
#endif  /* EACCES */
#ifndef EADDRINUSE
#define EADDRINUSE                                          98
#endif  /* EADDRINUSE */
#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL                                       99
#endif  /* EADDRNOTAVAIL */
#ifndef EAGAIN
#define EAGAIN                                              11
#endif  /* EAGAIN */
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT                                        97
#endif  /* EAFNOSUPPORT */
#ifndef EALREADY
#define EALREADY                                            114
#endif  /* EALREADY */
#ifndef EBADF
#define EBADF                                               9
#endif  /* EBADF */
#ifndef EBUSY
#define EBUSY                                               16
#endif  /* EBUSY */
#ifndef ECONNABORTED
#define ECONNABORTED                                        103
#endif  /* ECONNABORTED */
#ifndef ECONNRESET
#define ECONNRESET                                          104
#endif  /* ECONNRESET */
#ifndef EDEADLK
#define EDEADLK                                             35
#endif  /* EDEADLK */
#ifndef EDESTADDRREQ 
#define EDESTADDRREQ                                        89
#endif  /* EDESTADDRREQ */
#ifndef EEXIST
#define EEXIST                                              17
#endif  /* EEXIST */
#ifndef EFAULT
#define EFAULT                                              14
#endif  /* EFAULT */
#ifndef EHOSTUNREACH
#define EHOSTUNREACH                                        113
#endif  /* EHOSTUNREACH */
#ifndef EINPROGRESS
#define EINPROGRESS                                         115
#endif  /* EINPROGRESS */
#ifndef EINTR
#define EINTR                                               4
#endif  /* EINTR */
#ifndef EINVAL
#define EINVAL                                              22
#endif  /* EINVAL */
#ifndef EIO
#define EIO                                                 5
#endif  /* EIO */
#ifndef EISCONN
#define EISCONN                                             106
#endif  /* EISCONN */
#ifndef EISDIR   
#define EISDIR                                              21
#endif  /* EISDIR */
#ifndef EMSGSIZE
#define EMSGSIZE                                            90
#endif  /* EMSGSIZE */
#ifndef EMVSERR
#define EMVSERR                                             200
#endif  /* EMVSERR */
#ifndef ENETUNREACH
#define ENETUNREACH                                         101
#endif  /* ENETUNREACH */
#ifndef ENFILE
#define ENFILE                                              23
#endif  /* ENFILE */
#ifndef ENOBUFS
#define ENOBUFS                                             105
#endif  /* ENOBUFS */
#ifndef ENODEV
#define ENODEV                                              19
#endif  /* ENODEV */
#ifndef ENOENT 
#define ENOENT                                              2
#endif  /* ENOENT */
#ifndef ENOMEM
#define ENOMEM                                              12
#endif  /* ENOMEM */
#ifndef ENOPROTOOPT
#define ENOPROTOOPT                                         92
#endif  /* ENOPROTOOPT */
#ifndef ENOSPC
#define ENOSPC                                              28
#endif  /* ENOSPC */
#ifndef ENOSYS
#define ENOSYS                                              38
#endif  /* ENOSYS */
#ifndef ENOTCONN
#define ENOTCONN                                            107
#endif  /* ENOTCONN */
#ifndef ENOTDIR 
#define ENOTDIR                                             20
#endif  /* ENOTDIR */
#ifndef ENOTEMPTY
#define ENOTEMPTY                                           39
#endif  /* ENOTEMPTY */
#ifndef ENOTSOCK
#define ENOTSOCK                                            88
#endif  /* ENOTSOCK */
#ifndef EOPNOTSUPP
#define EOPNOTSUPP                                          95
#endif  /* EOPNOTSUPP */
#ifndef EOVERFLOW
#define EOVERFLOW                                           75
#endif  /* EOVERFLOW */
#ifndef EPERM
#define EPERM                                               1
#endif  /* EPERM */
#ifndef EPIPE
#define EPIPE                                               32
#endif  /* EPIPE */
#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT                                     93
#endif  /* EPROTONOSUPPORT */
#ifndef ERANGE
#define ERANGE                                              34         
#endif  /* ERANGE */
#ifndef ESRCH
#define ESRCH                                               3
#endif  /* ESRCH */
#ifndef ETIMEDOUT
#define ETIMEDOUT                                           110
#endif  /* ETIMEDOUT */
#ifndef EWOULDBLOCK
#define EWOULDBLOCK                                         EAGAIN
#endif  /* EWOULDBLOCK */
#ifndef EXDEV
#define EXDEV                                               18
#endif  /* EXDEV */


/* Define internal errno get and set macros that can be redefined by specific binding layers.  */

#ifndef PX5_INTERNAL_ERRNO_INTERRUPT_STORAGE
#define PX5_INTERNAL_ERRNO_INTERRUPT_STORAGE                int  interrupt_api_error;
#endif  /* PX5_INTERNAL_ERRNO_INTERRUPT_STORAGE  */

#ifndef PX5_INTERNAL_ERRNO_INTERRUPT_SOURCE       
#define PX5_INTERNAL_ERRNO_INTERRUPT_SOURCE                 px5_globals.interrupt_api_error
#endif  /* PX5_INTERNAL_ERRNO_INTERRUPT_SOURCE  */

#ifndef PX5_INTERNAL_ERRNO_INTERRUPT_DESTINATION       
#define PX5_INTERNAL_ERRNO_INTERRUPT_DESTINATION            px5_globals.interrupt_api_error
#endif  /* PX5_INTERNAL_ERRNO_INTERRUPT_DESTINATION  */


/* Remap references to "errno" to the function that retrieves the error from thread storage.  */

#ifdef  PX5_MISRA_ENABLE
#ifndef PX5_SPECIFIC_ERRNO
#define PX5_SPECIFIC_ERRNO
#endif  /* PX5_SPECIFIC_ERRNO  */
#endif  /* PX5_MISRA_ENABLE  */  
  
#ifdef PX5_SPECIFIC_ERRNO
#define px5_errno                                           px5_errno_get()
#else
#define errno                                               px5_errno_get()
#define errno_get                                           px5_errno_get
#define errno_set(e)                                        px5_errno_set(e)
#endif


/******************************************************************************
 *********************** Section II: Errno constants **************************
 *****************************************************************************/

int             px5_errno_get(void);
int             px5_errno_set(int error);


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_ERRNO_HEADER */
