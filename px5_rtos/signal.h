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

#ifndef PX5_SIGNAL_HEADER
#define PX5_SIGNAL_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  Signal Constants
   Section III: Signal Types
   Section IV:  PX5 API Mapping
   Section V:   Actual PX5 API prototypes

******************************************************************************/


/******************************************************************************
 ************************** Section I: Include Files **************************
 *****************************************************************************/

#include "sys/types.h"
#include "px5_time.h"
#include "px5_errno.h"


/******************************************************************************
 ********************** Section II:  Signal Constants *************************
 *****************************************************************************/


/* Define maximum number of signals.  */

#define PX5_MAXIMUM_SIGNALS                                 32
#define PX5_SIGNAL_NUMBER_MASK                              0x1FUL


/* Define default signal mask.  */

#ifndef PX5_DEFAULT_SIGNAL_MASK
#define PX5_DEFAULT_SIGNAL_MASK                             0xFFFFFFFFUL
#endif /* PX5_DEFAULT_SIGNAL_MASK  */


/* Define default valid signal waiting mask, which by default excludes signal 0, since
   it is only used for error checking.  */

#ifndef PX5_DEFAULT_VALID_SIGNAL_WAIT
#define PX5_DEFAULT_VALID_SIGNAL_WAIT                       0xFFFFFFFEUL
#endif


/* Define default fill and empty signal masks.  */

#ifndef PX5_DEFAULT_FILL_MASK
#define PX5_DEFAULT_FILL_MASK                               0xFFFFFFFFUL
#endif  /* PX5_DEFAULT_FILL_MASK */

#ifndef PX5_DEFAULT_EMPTY_MASK
#define PX5_DEFAULT_EMPTY_MASK                              0UL
#endif  /* PX5_DEFAULT_EMPTY_MASK */


/* Default signal info extension macro to whitespace.  */

#ifndef PX5_SIGINFO_T_EXTENSIONS
#define PX5_SIGINFO_T_EXTENSIONS
#endif  /* PX5_SIGINFO_T_EXTENSIONS */


/* Define pthread_sigmask constants.  */

#define SIG_BLOCK                                           0
#define SIG_UNBLOCK                                         1
#define SIG_SETMASK                                         2


/* Define signal numbers.  */

#define SIG_ZERO                                            0
#define SIGABRT                                             6
#define SIGALRM                                             14
#define SIGBUS                                              10
#define SIGCHLD                                             20
#define SIGCONT                                             19
#define SIGFPE                                              8
#define SIGHUP                                              1
#define SIGILL                                              4
#define SIGINT                                              2
#define SIGKILL                                             9
#define SIGPIPE                                             13
#define SIGQUIT                                             3
#define SIGSEGV                                             11
#define SIGSTOP                                             17
#define SIGTERM                                             15
#define SIGTSTP                                             18
#define SIGTTIN                                             21
#define SIGTTOU                                             22
#define SIGUSR1                                             30
#define SIGUSR2                                             31
#define SIGPOLL                                             23
#define SIGPROF                                             27
#define SIGSYS                                              12
#define SIGTRAP                                             5
#define SIGURG                                              16
#define SIGVTALRM                                           26
#define SIGXCPU                                             24
#define SIGXFSZ                                             25


/******************************************************************************
 ************************ Section III:  Signal Types **************************
 *****************************************************************************/

#ifdef  PX5_MISRA_ENABLE
#ifndef PX5_SPECIFIC_SIGACTION
#define PX5_SPECIFIC_SIGACTION
#endif  /* PX5_SPECIFIC_SIGACTION  */
#endif  /* PX5_MISRA_ENABLE  */  
  

/* Determine if we need to remap the sigaction and siginfo.  */

#ifndef PX5_SPECIFIC_SIGACTION
#define sigaction                                           px5_sigaction
#define sigaction_t                                         px5_sigaction_t
#define siginfo_t                                           px5_siginfo_t
#endif  /* PX5_SPECIFIC_SIGACTION  */
  
  
/* Define the signal information structure that is used by some of the APIs.  */

typedef struct px5_siginfo_t_struct 
{

    /* Define signal information.  */
    int                                                     si_signo;
    int                                                     si_errno;
    int                                                     si_code;
    int                                                     si_trapno;  

    /* Define a macro for application to define additional structure members to the signal
       information type.  By default, the macro is set to whitespace (above).  */
    PX5_SIGINFO_T_EXTENSIONS

} px5_siginfo_t;


/* Define signal set type.  */

typedef unsigned long                                       sigset_t;


/* Define the signal action structure, which specifies the signal handler.  */

struct px5_sigaction
{

    /* Define the signal handler.  */
    void                                                    (*signal_handler)(int);
    u_long                                                  signal_handler_verification_code;
    px5_siginfo_t                                           signal_info;
};

typedef struct px5_sigaction                                px5_sigaction_t;


/******************************************************************************
 *********************** Section IV: PX5 API Mapping **************************
 *****************************************************************************/

/* Determine if PX5 source is present. If so, skip remapping.  */

#ifndef PX5_SOURCE_CODE


/* Determine if parameter checking is disabled. If so, skip parameter checking veener.  */

#ifndef PX5_PARAMETER_CHECKING_DISABLE

#define pthread_kill                                        px5_pthread_kill_check_params
#define pthread_sigmask                                     px5_pthread_sigmask_check_params
#define sigaddset                                           px5_sigaddset
#define sigdelset                                           px5_sigdelset
#define sigemptyset                                         px5_sigemptyset
#define sigfillset                                          px5_sigfillset
#define sigismember                                         px5_sigismember
#define sigpending                                          px5_sigpending
#define sigtimedwait                                        px5_sigtimedwait_check_params
#define sigwait                                             px5_sigwait_check_params
#define sigwaitinfo                                         px5_sigwaitinfo_check_params

#else

#define pthread_kill                                        px5_pthread_kill
#define pthread_sigmask                                     px5_pthread_sigmask
#define sigaddset                                           px5_sigaddset
#define sigdelset                                           px5_sigdelset
#define sigemptyset                                         px5_sigemptyset
#define sigfillset                                          px5_sigfillset
#define sigismember                                         px5_sigismember
#define sigpending                                          px5_sigpending
#define sigtimedwait                                        px5_sigtimedwait
#define sigwait                                             px5_sigwait
#define sigwaitinfo                                         px5_sigwaitinfo



#endif /* PX5_PARAMETER_CHECKING_DISABLE */

#endif /* PX5_SOURCE_CODE */


/******************************************************************************
 ******************** Section IV: Actual PX5 API prototypes *******************
 *****************************************************************************/

int             px5_pthread_kill(pthread_t  thread_handle, int  signal_number);
int             px5_pthread_kill_check_params(pthread_t  thread_handle, int  signal_number);
int             px5_pthread_sigmask(int  operation, const sigset_t *  signal_set,  sigset_t *  previous_mask);
int             px5_pthread_sigmask_check_params(int  operation, const sigset_t *  signal_set,  sigset_t *  previous_mask);
int             px5_sigaction(int  signal_number, const px5_sigaction_t *  new_handler,  px5_sigaction_t *  previous_handler);
int             px5_sigaddset(sigset_t *  signal_set, int signal_number);
int             px5_sigdelset(sigset_t *  signal_set, int signal_number);
int             px5_sigemptyset(sigset_t *  signal_set);
int             px5_sigfillset(sigset_t *  signal_set);
int             px5_sigismember(const sigset_t *  signal_set, int signal_number);
int             px5_sigpending(sigset_t *  pending_signals);
int             px5_sigtimedwait(const sigset_t *  signals, px5_siginfo_t *  signal_info, const struct px5_timespec *timeout);
int             px5_sigtimedwait_check_params(const sigset_t *  signals, px5_siginfo_t *  signal_info, const struct px5_timespec *timeout);
int             px5_sigwait(const sigset_t *  signals, int *  return_signal);
int             px5_sigwait_check_params(const sigset_t *  signals, int *  return_signal);
int             px5_sigwaitinfo(const sigset_t *  signals, px5_siginfo_t *  signal_info);
int             px5_sigwaitinfo_check_params(const sigset_t *  signals, px5_siginfo_t *  signal_info);


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_SIGNAL_HEADER */
