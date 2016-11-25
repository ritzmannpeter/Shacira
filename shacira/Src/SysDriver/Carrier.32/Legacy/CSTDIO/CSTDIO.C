/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     CSTDIO
*
*  BESCHREIBUNG:
*     Realisierung der Standard-I/O-Funktionen fuer Datentraegerzugriff.
*
*  UMGEBUNG:
*     ZIELRECHNER:           PC-AT
*     ENTWICKLUNGSRECHNER:   PC-AT
*     UEBERSETZER:
*     OPTIONEN:
*
*  VERSION:
*     VERSION:    1.00                      DATUM:   08.03.96
*     AUTOR(EN):                            TELEFON: (0761) 4520520
*
*  HISTORY:
*     08.03.96 -PR-  Implementierung.
*     17.02.00 -PR-  Aufruf von BasicFormat entfernt.
*
*
*
*  BEMERKUNGEN:
*
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  FUNKTIONEN:
*
*     Cfopen
*     Cfclose
*     Cfread
*     Cfwrite
*     Cfseek
*     Cremove
*
*     Cfstat
*
*     Copendir
*     Creaddir
*     Cclosedir
*
*     Cformat
*     Cfinit
*     Cdriveinfo
*     Cfileinfo
*
*  DATENTYPEN:
*
*  VARIABLEN:
*
*.EM.***********************************************************************/
/***************************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __stddef__
#include <stddef.h>
#define __stddef__
#endif
#ifndef __stdlib__
#include <stdlib.h>
#define __stdlib__
#endif
#ifndef __stdio__
#include <stdio.h>
#define __stdio__
#endif
#ifndef __string__
#include <string.h>
#define __string__
#endif
#ifndef __errno__
#include <errno.h>
#define __errno__
#endif
#ifndef __errcode__
#include <errcode.h>
#define __errcode__
#endif
#ifndef __basicio__
#include <basicio.h>
#define __basicio__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __fmfat__
#include <fmfat.h>
#define __fmfat__
#endif
#ifndef __fmt2__
#include <fmt2.h>
#define __fmt2__
#endif
#ifndef __fx25__
#include <fx25.h>
#define __fx25__
#endif
#ifndef __fmt1__
#include <fmt1.h>
#define __fmt1__
#endif
#ifndef __service__
#include <service.h>
#define __service__
#endif
/***************************************************************************/

/***************************************************************************/
/* Verwaltungsfunktionen fuer die Datentraegerschicht                      */
/***************************************************************************/

LOCAL DRIVE_INFO DriveInfo = {0};


LOCAL DRIVE_MODULE * DriveModule(int format)
{
   Switch(format)
   Case FMFAT: return FMFAT_Module();
   Case FMT2: return FMT2_Module();
   Case FX25: return FX25_Module();
   Case FMT1: return FMT1_Module();
   Default: return NULL;
   Endswitch
}

LOCAL FILE_MODULE * FileModule(char * path)
{  int err = 0;
   FILE_INFO fileinfo;

   memset(&fileinfo, 0, sizeof(FILE_INFO));
   If ((err = FMFAT_Module()->file_info(path, &fileinfo)) == USR_NO_ERROR) Then
      return FMFAT_FileModule();
   Elseif ((err = FMT2_Module()->file_info(path, &fileinfo)) == USR_NO_ERROR) Then
      return FMT2_FileModule();
   Elseif ((err = FX25_Module()->file_info(path, &fileinfo)) == USR_NO_ERROR) Then
      return FX25_FileModule();
   Elseif ((err = FMT1_Module()->file_info(path, &fileinfo)) == USR_NO_ERROR) Then
      return FMT1_FileModule();
   Else
      return NULL;
   Endif
}

LOCAL int GetDriveInfo(DRIVE_INFO * driveinfo)
{  int err;
   int size;

   memset(driveinfo, 0, sizeof(DRIVE_INFO));
   size = BASIC_Check();
   If (size < 0) Then
      return size;
   Else
      driveinfo->size = size;
      If (size == 64 || size == 32) Then
         err = FMFAT_Module()->drive_info(driveinfo);
         return err;
      Elseif (size == 8 || size == 4) Then
         err = FMT2_Module()->drive_info(driveinfo);
         If (err == USR_NO_ERROR) Then
            return USR_NO_ERROR;
         Else
            err = FX25_Module()->drive_info(driveinfo);
            If (err == USR_NO_ERROR) Then
               return USR_NO_ERROR;
            Else
               err = FMT1_Module()->drive_info(driveinfo);
               return err;
            Endif
         Endif
      Else
         return CSTDIO_SIZE_NOT_SUPPORTED;
      Endif
   Endif
}

/***************************************************************************/
/* Verwaltungsfunktionen und -strukturen cstdio                            */
/***************************************************************************/

#define _OPEN    0x0001
#define _CREATE  0x0002

typedef struct cfile
{  USR_WORD cflags;
   int handle;
   FILE iobuf;
}  CFILE;

LOCAL CFILE Ciobuf[MAX_OPEN_CFILES] = {0};

LOCAL int FreeFileDescriptor()
{  int i;
   For (i=0; i<MAX_OPEN_CFILES; i++) Do
      If (!(Ciobuf[i].cflags & _OPEN)) Then
         return i;
      Endif
   Endfor
   return -1;
}

CFILE * FileDescriptor(FILE * stream)
{  int buf_ind;
   CFILE * cstream;
   
   If (stream == NULL) Then
      return NULL;
   Else
      buf_ind = stream->_handle;
      If (buf_ind < 0 || buf_ind >= MAX_OPEN_CFILES) Then
         errno = EBADF;
         return NULL;
      Else
         cstream = &(Ciobuf[buf_ind]);
         If (cstream->cflags & _OPEN) Then
            return cstream;
         Else
            errno = ENOTOP;
            return NULL;
         Endif
      Endif
   Endif
}

typedef struct cdir
{  USR_WORD dflags;
   int act_entry;
   int max_entries;
   DIR * dir_buf;
}  CDIR;

LOCAL CDIR Dirbuf[MAX_OPEN_CDIRS] = {0};

LOCAL int FreeDirDescriptor()
{  int i;
   For (i=0; i<MAX_OPEN_CDIRS; i++) Do
      If (!(Dirbuf[i].dflags & _OPEN)) Then
         return i;
      Endif
   Endfor
   return -1;
}

CDIR * DirDescriptor(DIR * dir)
{  int buf_ind;
   CDIR * cdir;
   
   If (dir == NULL) Then
      return NULL;
   Else
      buf_ind = dir->d_ino;
      If (buf_ind < 0 || buf_ind >= MAX_OPEN_CDIRS) Then
         errno = EBADF;
         return NULL;
      Else
         cdir = &(Dirbuf[buf_ind]);
         If (cdir->dflags & _OPEN) Then
            return cdir;
         Else
            errno = ENOTOP;
            return NULL;
         Endif
      Endif
   Endif
}

LOCAL int ErrTrans(int device_error)
{
   Switch((int)device_error)
   Case ERR_CAR_NOT_READY: return EAGAIN;
   Case ERR_FILE_NOT_FOUND: return ENOENT;
   Case ERR_MULTIPLE_FILE: return EEXIST;
   Case ERR_NO_DEVICE: return ENODEV;
   Case ERR_DEVICE_FULL: return ENOSPC;
   Case ERR_CAR_WRONG_FORMAT: return device_error;
   Case ERR_CAR_NO_DIR_ENTRY: return device_error;
   Case ERR_CAR_FILE_EXISTS: return device_error;
   Case ERR_CAR_NO_EEPROM: return device_error;
   Case ERR_CAR_ADDRESS: return device_error;
   Case ERR_INVALID_DISKID: return device_error;
   Case ERR_INVALID_SPINFO: return device_error;
   Case ERR_PAST_END: return device_error;
   Case ERR_DIR_FULL: return device_error;
   Case ERR_UNKNOWN: return device_error;
   Case ERR_HARDWARE: return device_error;
   Case ERR_BAD_MODE: return device_error;
   Case ERR_READ: return device_error;
   Case ERR_WRITE: return device_error;
   Case ERR_NO_FILESYSTEM: return device_error;
   Default: return device_error;
   Endswitch
}

/***************************************************************************/
/* Implementierung der cstdio-Funktionen                                   */
/***************************************************************************/

FILE * Cfopen(const char * __filename, const char * __mode)
{  int file_descriptor, err;
   FILE * stream;
   CFILE * cstream;
   USR_WORD flags = 0;
   USR_WORD cflags = 0;
   char * mode_ptr = __mode;
   char c;
   int hnd;

   If ((err = GetDriveInfo(&DriveInfo)) != USR_NO_ERROR) Then
      errno = ErrTrans(err);
      return NULL;
   Endif
   
   file_descriptor = FreeFileDescriptor();
   If (file_descriptor < 0) Then
      errno = ENFILE;
      return NULL;
   Else
      cstream = &(Ciobuf[file_descriptor]);
   Endif
   stream = &(cstream->iobuf);
   While ((c = *(mode_ptr++)) != '\0') Do
      Switch(c)
      Case 'w': flags |= _WRITE; cflags |= _CREATE; break;
      Case 'r': flags |= _READ; break;
      Case 'b': flags |= _BINARY; break;
      Case '+': flags |= _WRITE | _READ; break;
      Case 'a': flags |= _APPEND; break;
      Default: errno = EINVAL; return NULL;
      Endswitch
   Endwhile

   If ((hnd = DriveInfo.module->open_file(flags, __filename)) < 0) Then
      errno = ErrTrans(hnd);
      return NULL;
   Else
      cstream->cflags = _OPEN;
      cstream->handle = hnd;
      stream->_flag = flags;
      stream->_handle = file_descriptor;
      return stream;
   Endif
}

int Cfclose(FILE *__fp)
{  int err;
   int hnd;
   CFILE * cstream;

   cstream = FileDescriptor(__fp);
   if (cstream == NULL) return -1;
   hnd = cstream->handle;
   If ((err = DriveInfo.module->close_file(hnd)) != USR_NO_ERROR) Then
      errno = ErrTrans(err);
      return -1;
   Else
      memset(cstream, 0, sizeof(CFILE));
      return 0;
   Endif
}

size_t Cfread(void * __ptr, size_t __size, size_t __n, FILE * __fp)
{  int i, err;
   int hnd;
   char * buf_ptr = __ptr;
   CFILE * cstream;

   cstream = FileDescriptor(__fp);
   if (cstream == NULL) return -1;
   if (__size == 0 || __n == 0) return 0;
   hnd = cstream->handle;
   For (i=0; i<__n; i++) Do
      err = DriveInfo.module->read_file(hnd, buf_ptr, __size);
      If (err != USR_NO_ERROR) Then
         err = ErrTrans(err);
         If (err == ERR_PAST_END) Then
            __fp->_flag |= _EOF;
            return i;
         Else
            errno = err;
            return -1;
         Endif
      Endif
      buf_ptr += __size;
   Endfor
   return __n;
}

size_t Cfwrite( const void *__ptr, size_t __size, size_t __n, FILE *__fp)
{  int i, err;
   int hnd;
   char * buf_ptr = __ptr;
   CFILE * cstream;

   cstream = FileDescriptor(__fp);
   if (cstream == NULL) return -1;
   __fp->_flag &= (~_EOF);
   if (__size == 0 || __n == 0) return 0;
   hnd = cstream->handle;
   For (i=0; i<__n; i++) Do
      err = DriveInfo.module->write_file(hnd, buf_ptr, __size);
      If (err != USR_NO_ERROR) Then
         errno = ErrTrans(err);
         return i;
      Endif
      buf_ptr += __size;
   Endfor
   return __n;
}

int Cfseek(FILE *__fp, long int __offset, int __whence)
{  int err;
   int hnd;
   CFILE * cstream;
   long cur_pos, pos, file_size;

   cstream = FileDescriptor(__fp);
   if (cstream == NULL) return -1;
   hnd = cstream->handle;
   If ((file_size = DriveInfo.module->get_size(hnd)) < 0) Then
      errno = ErrTrans((int)file_size);
      return -1;
   Endif
   If ((cur_pos = DriveInfo.module->get_pos(hnd)) < 0) Then
      errno = ErrTrans((int)cur_pos);
      return -1;
   Endif

   Switch(__whence)
   Case SEEK_SET: pos = __offset; break;
   Case SEEK_CUR: pos = cur_pos + __offset; break;
   Case SEEK_END: pos = file_size; break;
   Default: errno = EINVAL; return -1;
   Endswitch
   If (pos < 0 || pos > file_size) Then
      errno = ESPIPE;
      return -1;
   Endif
   __fp->_flag &= (~_EOF);
   err = DriveInfo.module->set_pos(hnd, pos);
   If (err == USR_NO_ERROR) Then
      return 0;
   Else
      errno = ErrTrans(err);
      return -1;
   Endif
}

int Cremove(const char *__filename)
{  int err;
   If ((err = GetDriveInfo(&DriveInfo)) != USR_NO_ERROR) Then
      errno = ErrTrans(err);
      return -1;
   Endif
   err = DriveInfo.module->remove_file(__filename);
   If (err == USR_NO_ERROR) Then
      return 0;
   Else
      errno = ErrTrans(err);
      return -1;
   Endif
}

int Cfeof(FILE *__fp)
{
   If (__fp->_flag & _EOF) Then
      return 1;
   Else
      return 0;
   Endif   
}

int Cfileno(FILE * __fp)
{  CFILE * cstream;
   cstream = FileDescriptor(__fp);
   if (cstream == NULL) return -1;
   return cstream->handle;
}

int Cfstat(int handle, struct stat * buffer)
{

#ifdef NOCH_NICHT

   CFILE * cstream;
   FILE * stream;

   If (handle< 0 || handle >= MAX_OPEN_CFILES) Then
      errno = EBADF;
      return -1;
   Endif

   cstream = FileDescriptor(stream);
   if (cstream == NULL) return -1;
   stream = &(cstream->iobuf);

   buffer->st_dev = 0;   /* disk drive file resides on */
   buffer->st_ino = 0;   /* this inode's #, not used for DOS */
   buffer->st_mode = 0; /* file mode */
   buffer->st_nlink = 0;   /* # of hard links */
   buffer->st_uid = 0;  /* user-id, always 'root' */
   buffer->st_gid = 0;  /* group-id, always 'root' */
   buffer->st_rdev = 0; /* should be device type */
            /* but same as st_dev for the time being */
   buffer->st_size = 0; /* total file size */
   buffer->st_atime = 0;   /* should be file last access time */
   buffer->st_mtime = 0;   /* file last modify time */
   buffer->st_ctime = 0;   /* should be file last status change time */
   buffer->st_btime = 0; /* last archived date and time */
   buffer->st_attr = 0;  /* file attributes */
                      /* next 4 fields Netware only */
   buffer->st_archivedID = 0; /* user/object ID that last archived file*/
   buffer->st_updatedID = 0;  /* user/object ID that last updated file*/
   buffer->st_inheritedRightsMask = 0;
   buffer->st_originatingNameSpace = 0;
   sprintf(st_name, "%s", ""); /* ASCIIZ filename */
#endif
   return 0;
}

DIR * Copendir(const char * path)
{  int dir_descriptor, err;
   int dir_entries = 0;
   CDIR * cdir;
   DIR * dir;

   If ((err = GetDriveInfo(&DriveInfo)) != USR_NO_ERROR) Then
      errno = ErrTrans(err);
      return NULL;
   Endif
   
   dir_descriptor = FreeDirDescriptor();
   If (dir_descriptor < 0) Then
      errno = ENFILE;
      return NULL;
   Else
      cdir = &(Dirbuf[dir_descriptor]);
   Endif

   dir_entries = DriveInfo.module->directory(&dir);
   If (dir_entries < 0) Then
      errno = ErrTrans(dir_entries);
      return NULL;
   Elseif (dir_entries == 0) Then
      errno = ENOF;
      return NULL;
   Endif
   
   cdir->dflags = _OPEN;
   cdir->act_entry = 0;
   cdir->max_entries = dir_entries;
   cdir->dir_buf = dir;
   dir->d_ino = dir_descriptor;
   return dir;
}

int Cclosedir(DIR * dir)
{  CDIR * cdir;
   cdir = DirDescriptor(dir);
   if (cdir == NULL) return -1;
   free(cdir->dir_buf);
   memset(cdir, 0, sizeof(CDIR));
   return 0;
}

struct dirent * Creaddir(DIR * dir)
{  CDIR * cdir;
   cdir = DirDescriptor(dir);
   if (cdir == NULL) return NULL;
   cdir->act_entry++;
   If (cdir->act_entry >= cdir->max_entries) Then
      return NULL;
   Else
      dir = &(cdir->dir_buf[cdir->act_entry]);
      return dir;
   Endif
}

#define PAGE_SIZE       64L
static unsigned char FormatPattern[PAGE_SIZE] = {0};
LOCAL int BasicFormat(long carrier_size)
{  int err;
   long i, size;
   If (carrier_size > 0 && carrier_size < 128) Then
      size = carrier_size * 1024L;
      For (i=0; i<size; i+=PAGE_SIZE) Do
        if ((err = BASIC_Write(i, PAGE_SIZE, FormatPattern)) != USR_NO_ERROR) return err;
      Endfor
   Endif
   return USR_NO_ERROR;
}


int Cformat(int format, int param)
{  int err;
   DRIVE_MODULE * module;
   
   err = GetDriveInfo(&DriveInfo);
   If (format != 0) Then
      module = DriveModule(format);
      If (module == NULL) Then
         errno = EINVAL;
         return -1;
      Endif
   Else
      If (err == USR_NO_ERROR) Then
         module = DriveInfo.module;
      Else
         errno = CSTDIO_NO_FORMAT_INFO;
         return -1;
      Endif
   Endif
/* PR 17.02.2000
 *
   If ((err = BasicFormat(DriveInfo.size)) != USR_NO_ERROR) Then
      errno = err;
      return -1;
   Endif
*/
   If ((err = module->format(param)) != USR_NO_ERROR) Then
      errno = ErrTrans(err);
      return -1;
   Else
      return 0;
   Endif
}

int Cfinit()
{  int err;
   If ((err = FMFAT_Module()->init()) == USR_NO_ERROR) Then
      If ((err = FMT2_Module()->init()) == USR_NO_ERROR) Then
         If ((err = FX25_Module()->init()) == USR_NO_ERROR) Then
            If ((err = FMT1_Module()->init()) == USR_NO_ERROR) Then
               return USR_NO_ERROR;
            Endif
         Endif
      Endif
   Endif
   errno = ErrTrans(err);
   return -1;
}

int Cdriveinfo(DRIVE_INFO * driveinfo, int refresh)
{  int err = 0;
   If (refresh != 0) Then
      If ((err = GetDriveInfo(&DriveInfo)) != USR_NO_ERROR) Then
         errno = ErrTrans(err);
         err = -1;
      Endif
   Endif
   memcpy(driveinfo, &DriveInfo, sizeof(DRIVE_INFO));
   return err;
}

int Cfileinfo(char * path, FILE_INFO * fileinfo)
{  int err = 0;

   memset(fileinfo, 0, sizeof(FILE_INFO));
   If ((err = FMFAT_Module()->file_info(path, fileinfo)) == USR_NO_ERROR) Then
      return USR_NO_ERROR;
   Elseif ((err = FMT2_Module()->file_info(path, fileinfo)) == USR_NO_ERROR) Then
      return USR_NO_ERROR;
   Elseif ((err = FX25_Module()->file_info(path, fileinfo)) == USR_NO_ERROR) Then
      return USR_NO_ERROR;
   Elseif ((err = FMT1_Module()->file_info(path, fileinfo)) == USR_NO_ERROR) Then
      return USR_NO_ERROR;
   Else
      return CSTDIO_NO_FILE_FORMAT_DETECTED;
   Endif
}

int Csettime(char * path)
{  FILE_MODULE * file_module = FileModule(path);

   If (file_module) Then
      return file_module->settime(path);
   Else
      return CSTDIO_NO_FILE_FORMAT_DETECTED;
   Endif
}

int Csetregval(char * path, long regid, int index, long value)
{  FILE_MODULE * file_module = FileModule(path);

   If (file_module) Then
      return file_module->setregval(path, regid, index, value);
   Else
      return CSTDIO_NO_FILE_FORMAT_DETECTED;
   Endif
}

int Cgetregval(char * path, long regid, int index, long * value)
{  FILE_MODULE * file_module = FileModule(path);

   If (file_module) Then
      return file_module->getregval(path, regid, index, value);
   Else
      return CSTDIO_NO_FILE_FORMAT_DETECTED;
   Endif
}

int Csetdata(char * path, char * artno, char * matno, char * toolno)
{  FILE_MODULE * file_module = FileModule(path);

   If (file_module) Then
      return file_module->setdata(path, artno, matno, toolno);
   Else
      return CSTDIO_NO_FILE_FORMAT_DETECTED;
   Endif
}

