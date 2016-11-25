
#ifndef __sdiskio__
#define __sdiskio__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef __WIN32__
#include <windows.h>
//#include <winbase.h>
#include <direct.h>
#include <io.h>
#else
#include <dirent.h>
#endif


/* ID der einzelnen "Geraete": */
#define SDISKIO_DRV_FLO1            0  /* 1. Floppy, FAT-Filesystem        */
#define SDISKIO_DRV_FLO2            1  /* 2. Floppy, FAT-Filesystem        */
#define SDISKIO_CURRENT_DIRECTORY   2  /* Harddisk, aktuelles Verzeichnis  */
#define SDISKIO_QNX_DRV_FLO1        3  /* 1. Floppy, QNX4-Filesystem       */
#define SDISKIO_QNX_DRV_FLO2        4  /* 2. Floppy, QNX4-Filesystem       */
#define SDISKIO_QNX_DRV_HDISK       5  /* Harddisk, Root                   */

#define SDISKIO_MAX_DRIVENAMELEN   30
#define SDISKIO_MAX_PATHLEN       128

#define SDISKIO_NOERROR             0
#define SDISKIO_ERR_DIRNOTFOUND    -1
#define SDISKIO_ERR_FILENOTFOUND   -2


#if defined (__QNX2__) || defined (__QNXNTO__) || defined(__QNX4__)
#define DIRECTORY_SEPARATOR_CHAR '/'
#elif defined __WIN32__
#define DIRECTORY_SEPARATOR_CHAR '\\'
#endif


typedef struct {
   BOOL handle_ok;
   struct stat statbuf;
   char path[SDISKIO_MAX_PATHLEN];
   char *filename_start;
#if defined (__QNX2__) || defined (__QNXNTO__) || defined(__QNX4__) || defined(__LINUX__)
   DIR * dir;
   struct dirent * direntry;
#elif defined __WIN32__
   HANDLE find_handle;
   WIN32_FIND_DATA find_buffer;
#endif
} SDISKIO_DIR_HANDLE;




GLOBAL int SDISKIO_GetDriveName (int sdiskio_drive, char * drivename);
GLOBAL int SDISKIO_Mount (int sdiskio_drive);
GLOBAL int SDISKIO_UnMount (int sdiskio_drive);
GLOBAL int SDISKIO_IsMounted (int sdiskio_drive);
GLOBAL int SDISKIO_GetDriveSpace (int sdiskio_drive, ULONG * total_space,
                                  ULONG * used_space, ULONG * free_space);
GLOBAL int SDISKIO_DeleteFile (char *file_name);
GLOBAL int SDISKIO_FormatDisk (int sdiskio_drive);

GLOBAL int     SDISKIO_DirFindFirstFile (SDISKIO_DIR_HANDLE *hnd, char *path);
GLOBAL int     SDISKIO_DirFindNextFile  (SDISKIO_DIR_HANDLE *hnd);
GLOBAL void    SDISKIO_DirFindClose     (SDISKIO_DIR_HANDLE *hnd);
GLOBAL char *  SDISKIO_DirGetFileName   (SDISKIO_DIR_HANDLE *hnd);
GLOBAL ULONG   SDISKIO_DirGetFileSize   (SDISKIO_DIR_HANDLE *hnd);
GLOBAL struct tm * SDISKIO_DirGetFileTime (SDISKIO_DIR_HANDLE *hnd);

#endif /* __sdiskio__ */

