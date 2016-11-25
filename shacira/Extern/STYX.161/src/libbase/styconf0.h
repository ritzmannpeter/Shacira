/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [styconf0.h]               System Dependencies ( C Library )               */
/*                                                                            */
/* Copyright (c) 1999 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

#if defined( _WIN32 ) || defined( _MSDOS ) || defined( MSDOS )
#define STYX_CONFIG_OSMS
#endif


#if defined( _MSDOS ) || defined( _WIN32 )

#pragma warning(disable: 4018 4135 4237 4759)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>
#include <io.h>
#include <malloc.h>
#include <process.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <fcntl.h>
#include <wchar.h>
#include <wctype.h>
#include <windows.h>
#ifdef __MINGW32__
// PR no support for this types when using mingw
///   typedef signed char int8_t;
///   typedef short int16_t;
///   typedef int int32_t;
///   typedef long long int64_t;
   typedef unsigned char u_int8_t;
   typedef unsigned short u_int16_t;
   typedef unsigned int u_int32_t;
   typedef unsigned long long u_int64_t;
   typedef int32_t register_t;
#endif

#define VERSION   "1.6"

#else

#ifndef HAVE_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <wchar.h>
#include <wctype.h>
#include <iconv.h>
#include <semaphore.h>
#include <dlfcn.h>

#define VERSION   "1.6"

#else
#include <config.h>

/* The following is borrowed from w3c-wwwlib. */

/* stdio.h */
#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

/* types.h */
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#else
#ifdef HAVE_TYPES_H
#include <types.h>
#endif
#endif

/* unistd.h */
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#else
#ifdef HAVE_SYS_UNISTD_H
#include <sys/unistd.h>
#endif
#endif

/* fcntl.h */
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#else
#ifdef HAVE_SYS_FCNTL_H
#include <sys/fcntl.h>
#endif
#endif

/* stat.h */
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#else
#ifdef HAVE_STAT_H
#include <stat.h>
#endif
#endif

/* time.h */
#ifdef TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#ifdef HAVE_TIME_H
#include <time.h>
#endif
#endif
#endif

/* string{,s}.h */
#ifdef HAVE_STRING_H
#include <string.h>
#else
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#endif

/* errno.h */
#ifdef HAVE_ERRNO_H
#include <errno.h>
#else
#ifdef HAVE_SYS_ERRNO_H
#include <sys/errno.h>
#else
#ifdef HAVE_NET_ERRNO_H
#include <net/errno.h>
#endif
#endif
#endif

/* libc.h */
#ifdef HAVE_LIBC_H
#include <libc.h>
#endif

/* stdlib.h */
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

/* malloc.h */
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

/* memory.h */
#ifdef HAVE_MEMORY_H
#include <memory.h>
#endif

/* direct.h */
#ifdef HAVE_DIRECT_H
#include <direct.h>
#endif

/* ctype.h */
#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif

/* wchar.h */
#ifdef HAVE_WCHAR_H
#include <wchar.h>
#endif

/* wctype.h */
#ifdef HAVE_WCTYPE_H
#include <wctype.h>
#endif

/* iconv.h */
#ifdef HAVE_ICONV_H
#include <iconv.h>
#endif

/* semaphore.h */
#ifdef HAVE_SEMAPHORE_H
#include <semaphore.h>
#endif

/* dlfcn.h */
#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif

/* dirent.h / ndir.h / dir.h */
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#define NAMLEN(dirent) strlen((dirent)->d_name)
#else
#define dirent direct
#define NAMLEN(dirent) (dirent)->d_namlen
#ifdef HAVE_SYS_NDIR_H
#include <sys/ndir.h>
#endif
#ifdef HAVE_SYS_DIR_H
#include <sys/dir.h>
#endif
#ifdef HAVE_DIR_H
#include <dir.h>
#endif
#ifdef HAVE_NDIR_H
#include <ndir.h>
#endif
#endif

/* Definition of var args */
#if defined(STDC_HEADERS) || defined(__STDC__)
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#ifndef HAVE_STRERROR				  /* Otherwise use the table */
extern char *sys_errlist[];
extern int sys_nerr;
#endif

#if !defined(HAVE_MEMCPY)
#define memcpy(d, s, n) bcopy((s), (d), (n))
#define memmove(d, s, n) bcopy((s), (d), (n))
#endif

#if !defined(HAVE_MEMCMP)
#define memcmp memcmp_aux
#endif

#if !defined(HAVE_STRDUP)
#define strdup StrCopy
#endif

#if !defined(HAVE_STRSTR)
#define strstr strstr_aux
#endif

#if !defined(HAVE_STRCHR)
#if defined(HAVE_INDEX)
#define strchr index
#else
#define strchr strchr_aux
#endif
#endif

#if !defined(HAVE_STRRCHR)
#if defined(HAVE_RINDEX)
#define strchr rindex
#else
#define strrchr strrchr_aux
#endif
#endif

#if !defined(HAVE_STRCSPN)
#define strcspn strcspn_aux
#endif

#if !defined(HAVE_GETCWD)
#define getcwd getcwd_aux
#endif

//TODO additional workarounds for vprintf ...

#if !defined(HAVE_VSNPRINTF)
#define vsnprintf(s,l,f,a) vsprintf(s,f,a)
#endif

#endif

#endif


/* Patch for problems in glibc6 */
#if defined(__GLIBC__)
#undef S_IFMT
#undef S_IFDIR
#define S_IFMT __S_IFMT
#define S_IFDIR __S_IFDIR
#endif


#ifndef NULL
#define NULL ((void *)0)
#endif

