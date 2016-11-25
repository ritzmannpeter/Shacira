#ifndef _cstdio
#define _cstdio

/*.SI.***********************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __stdio__
#include <stdio.h>
#define __stdio__
#endif
#ifndef __direct__
#include <direct.h>
#define __direct__
#endif
#ifndef __sys_stat__
#include <sys\stat.h>
#define __sys_stat__
#endif
/*.EI.***********************************************************************/

#define NAME_MAX	255		/* maximum filename for HPFS or NTFS */
typedef struct dirent {
    char	d_dta[ 21 ];		/* disk transfer area */
    char	d_attr; 		/* file's attribute */
    unsigned short int d_time;		/* file's time */
    unsigned short int d_date;		/* file's date */
    long	d_size; 		/* file's size */
    char	d_name[ NAME_MAX + 1 ]; /* file's name */
    unsigned short d_ino;		/* serial number (not used) */
    char	d_first;		/* flag for 1st time */
} DIR;
/* values for _flag field in FILE struct and _iomode array */

#define _READ	0x0001	/* file opened for reading */
#define _WRITE	0x0002	/* file opened for writing */
#define _UNGET	0x0004	/* ungetc has been done */
#define _BIGBUF 0x0008	/* big buffer allocated */
#define _EOF	0x0010	/* EOF has occurred */
#define _SFERR	0x0020	/* error has occurred on this file */
#define _APPEND 0x0080	/* file opened for append */
#define _BINARY 0x0040	/* file is binary, skip CRLF processing */
#define _TMPFIL 0x0800	/* this is a temporary file */
#define _DIRTY	0x1000	/* buffer has been modified */
#define _ISTTY	0x2000	/* is console device */
#define _DYNAMIC 0x4000 /*  FILE is dynamically allocated   */

//#define _flag		_flag
#define _handle 	_file

typedef struct drive_module
{  int (*open_file)(USR_WORD flags, char * filename);
   int (*close_file)(int hnd);
   int (*read_file)(int hnd, void * buffer, int size);
   int (*write_file)(int hnd, void * buffer, int size);
   long (*get_size)(int hnd);
   long (*get_pos)(int hnd);
   int (*set_pos)(int hnd, long pos);
   int (*remove_file)(char * filename);
   int (*directory)(DIR ** dir);
   int (*format)(int param);
   int (*init)();
   int (*drive_info)(void * driveinfo);
   int (*file_info)(char * path, void * fileinfo);
}  DRIVE_MODULE;

typedef struct drive_info
{  short format;
   short version;
   long size;
   long free_space;
   const DRIVE_MODULE * module;
}  DRIVE_INFO;

#define ARTNO_SIZE      20
#define TOOLNO_SIZE     20
#define MATNO_SIZE      20
#define MACHTYPE_SIZE   10
#define MACHNO_SIZE     20

typedef struct file_info
{  short format;
   short version;
   long size;
   short day;
   short month;
   short year;
   short sec;
   short min;
   short hour;
   char artno[ARTNO_SIZE];
   char toolno[TOOLNO_SIZE];
   char matno[MATNO_SIZE];
   char machtype[MACHTYPE_SIZE];
   char machno[MACHNO_SIZE];
}  FILE_INFO;

#define MAX_OPEN_CFILES    3
#define MAX_OPEN_CDIRS     3

extern FILE * Cfopen(const char * __filename, const char * __mode);
extern size_t Cfread(void * __ptr, size_t __size, size_t __n, FILE * __fp);
extern size_t Cfwrite(const void *__ptr, size_t __size, size_t __n, FILE *__fp);
extern int Cfseek(FILE *__fp, long int __offset, int __whence);
extern int Cfclose(FILE *__fp);
extern int Cremove(const char *__filename);
extern int Cfeof(FILE *__fp);
extern int Cfileno(FILE * __fp);
extern int Cfstat(int handle, struct stat * buffer);

/* Funktionen aus direct.h
 */
extern int Cclosedir(DIR * dir);
extern DIR * Copendir(const char * path);
extern struct dirent * Creaddir(DIR * dir);

/* zusaetzliche Funktionen
 */
extern int Cformat(int format, int param);
extern int Cfinit(void);
extern int Cdriveinfo(DRIVE_INFO * driveinfo, int refresh);
extern int Cfileinfo(char * path, FILE_INFO * fileinfo);

typedef struct file_module
{  int (*settime)(char * path);
   int (*setregval)(char * path, long regid, int index, long value);
   int (*getregval)(char * path, long regid, int index, long * value);
   int (*setdata)(char * path, char * artno, char * matno, char * toolno);
}  FILE_MODULE;

extern int Csettime(char * path);
extern int Csetregval(char * path, long regid, int index, long value);
extern int Cgetregval(char * path, long regid, int index, long * value);
extern int Csetdata(char * path, char * artno, char * matno, char * toolno);


#endif /* ifndef _cstdio */

