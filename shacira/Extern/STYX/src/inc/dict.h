/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [dict.h]                    Type: Dictionary                             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef dict_INCL
#define dict_INCL


#include "standard.h"


#ifdef __cplusplus
extern "C" {
#endif


/*  
   [dict] provides platform-independant access to directories and their entries.
   Supported platforms are Unix and Windows.
*/

/* ---------------------- Types ------------------------------------------- */

AbstractType(Dir);    /* Abstract directory type       */
AbstractType(Dentry); /* Abstract directory entry type */

/* -------------------------- Directory access ---------------------------- */

Dir      Dir_open(c_string PathName);  /* open directory 'PathName'         */
Dentry   Dir_read(Dir Directory);      /* next directory entry              */
c_string Dentry_name(Dentry Entry);    /* name of 'Entry'                   */
Dir      Dentry_open(Dentry Entry);    /* open 'Entry'                      */
c_string Dentry_path(Dentry Entry);  /* full path of 'Entry'; allocs memory */
c_bool   Dentry_isDir(Dentry Entry); /* 'Entry' = directory ?               */
c_bool   Dentry_isFile(Dentry Entry);  /* 'Entry' = regular file ?          */
c_bool   Dentry_isCDev(Dentry Entry);  /* 'Entry' = character device ?      */
c_bool   Dentry_isBDev(Dentry Entry);  /* 'Entry' = block device ?          */
c_bool   Dentry_isFifo(Dentry Entry);  /* 'Entry' = FIFO ?                  */
c_string Dir_name(Dir Directory);      /* name of 'Directory'               */
void     Dir_close(Dir Directory);     /* close 'Directory'                 */


#ifdef __cplusplus
}
#endif

#endif