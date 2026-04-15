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

#ifndef PX5_STAT_HEADER
#define PX5_STAT_HEADER


/* Ensure this file can be included and used by C++ programs.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/******************************************************************************
 ******************************** Manifest ************************************
 ******************************************************************************
   
   Section I:   Include Files
   Section II:  Mode Constants
   Section III: Mode Types

******************************************************************************/


/******************************************************************************
 ************************** Section I: Include Files **************************
 *****************************************************************************/

#include "sys/types.h"
#include "px5_time.h"
#include "px5_errno.h"


/******************************************************************************
 ********************** Section II:  Mode Constants ***************************
 *****************************************************************************/

#define S_IFMT                                              0x000000FFUL   
#define S_IFBLK                                             0x00000001UL   
#define S_IFCHR                                             0x00000002UL   
#define S_IFIFO                                             0x00000004UL   
#define S_IFREG                                             0x00000008UL    /* Regular file  */
#define S_IFDIR                                             0x00000010UL    /* Directory     */
#define S_IFLNK                                             0x00000020UL   
#define S_IFSOCK                                            0x00000040UL  
#define S_IRWXU                                             0x00000700UL  
#define S_IRUSR                                             0x00000100UL    /* Read enabled  */
#define S_IWUSR                                             0x00000200UL    /* Write enabled */ 
#define S_IXUSR                                             0x00000400UL 
#define S_IRWXG                                             0x00007000UL 
#define S_IRGRP                                             0x00001000UL 
#define S_IWGRP                                             0x00002000UL 
#define S_IXGRP                                             0x00004000UL 
#define S_IRWXO                                             0x00070000UL 
#define S_IROTH                                             0x00010000UL 
#define S_IWOTH                                             0x00020000UL 
#define S_IXOTH                                             0x00040000UL 
#define S_ISUID                                             0x00100000UL 
#define S_ISGID                                             0x00200000UL 
#define S_ISVTX                                             0x00400000UL 


/******************************************************************************
 ************************ Section III:  Mode Types ****************************
 *****************************************************************************/


/* Define the mode type.  */

typedef unsigned long                                       mode_t;


/* Define the file information structure.  */

struct px5_stat 
{

    u_int                                                   st_dev;
    u_int                                                   st_ino;
    mode_t                                                  st_mode;
    u_int                                                   st_nlink;
    u_int                                                   st_uid;
    u_int                                                   st_gid;
    u_int                                                   st_rdev;
    u_long                                                  st_size;   
    u_long                                                  st_blksize;
    u_long                                                  st_blocks;
    px5_time_t                                              st_atime;
    px5_time_t                                              st_mtime;
    px5_time_t                                              st_ctime;
};


#ifdef __cplusplus
}  /* Closing bracket for extern "C" at the top of file.  */
#endif /* __cplusplus  */


#endif  /* PX5_STAT_HEADER */
