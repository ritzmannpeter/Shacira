/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     FILES
*
*  BESCHREIBUNG:
*     Funktionen zum extrahieren und ablegen von Dateien auf beliebeigen
*     Datentraegern.
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
*     08.03.96 -PR-   Implementierung.
*     12.12.96 -PR-   Definition der Obergrenzen MAX_HEADER_SIZE und
*                     und MAX_PATH_LEN.
*
*
*
*
*
*
*
*
*
*
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  FUNKTIONEN:
*
*     CAR_InitCarrier
*     CAR_DirCarrier
*     CAR_FormatCarrier
*     CAR_SaveFile
*     CAR_RestoreFile
*     CAR_RestoreAllFiles
*     CAR_RemoveFile
*     CAR_FileInfo
*
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
#ifndef __platform__
#include <platform.h>
#define __platform__
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
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __debug__
#include <debug.h>
#define __debug__
#endif
#ifndef __dsdisk__
#include <dsdisk.h>
#define __dsdisk__
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
#ifndef __fmfat__
#include <fmfat.h>
#define __fmfat__
#endif
#ifndef __files__
#include <files.h>
#define __files__
#endif
#ifndef __errcode__
#include <errcode.h>
#define __errcode__
#endif
#ifndef __service__
#include <service.h>
#define __service__
#endif
/***************************************************************************/

#define MAX_SYS_ERR             42
#define MAX_HEADER_SIZE         256
#define MAX_PATH_LEN            128

#define BLOCK_SIZE      1
#define ITEMS           1000

LOCAL char Buffer[BLOCK_SIZE * ITEMS];

#define BITMAP_BUF_SIZE    256
#define MAX_POS            (BITMAP_BUF_SIZE * 8)

LOCAL USR_BYTE FMFileMap[256];

#define SET_FILE(i)  (FMFileMap[i/8] |= (0x01 << (i%8)))
#define FILE_SET(i)  (FMFileMap[i/8] & (0x01 << (i%8)))

LOCAL void SetFile(char * filename)
{  int number;
   If (sscanf(filename, "MATERIAL.%d", &number) == 1) Then
      SET_FILE(number);
   Endif
   return;
}

LOCAL int ExtractFileName(char * file, char * buffer)
{  int length = strlen(file);
   int i, pos;   

   pos = 0;
   For (i=0; i<length; i++) Do
      if (file[i] == '\\' ||
          file[i] == ':') pos = i;
   Endfor
   If (pos > 0) Then
      sprintf(buffer, "%s", &file[pos + 1]);
   Else
      sprintf(buffer, "%s", file);
   Endif
   return USR_NO_ERROR;
}

LOCAL int MakeFMFileName(char * buffer)
{  DIR * dir;
   struct dirent * dirent_ptr;
   int i;
   
   dirent_ptr = dir = Copendir("");
   If (dir != NULL) Then
      memset(FMFileMap, 0, BITMAP_BUF_SIZE);
      SetFile(dirent_ptr->d_name);
      While (TRUE) Do
         dirent_ptr = Creaddir(dir);
         If (dirent_ptr == NULL) Then
            break;
         Else
            SetFile(dirent_ptr->d_name);
         Endif
      Endwhile
      Cclosedir(dir);
      For (i=0; i<MAX_POS; i++) Do
         If (!(FILE_SET(i))) Then
            sprintf(buffer, "MATERIAL.%03d", i);
            return USR_NO_ERROR;
         Endif
      Endfor      
      return FILES_FILEMAP_FULL;
   Else
      If (errno == ENOF) Then
         DebugPrintf(VERBOSE, "no files found\n");
         sprintf(buffer, "MATERIAL.000");
         return USR_NO_ERROR;
      Else
         DebugPrintf(VERBOSE|FAILURES, "failed to open directory: %d\n", errno);
         return errno;
      Endif
   Endif
}

GLOBAL int CAR_InitCarrier()
{
   return Cfinit();
}

GLOBAL int CAR_FormatCarrier(int format, int param)
{  int ret = Cformat(format,param);
   If (ret != 0) Then
      DebugPrintf(FAILURES|VERBOSE, "failed to format carrier: %d\n", errno);
      return errno;
   Else
      DebugPrintf(VERBOSE, "carrier formatted\n");
      return USR_NO_ERROR;
   Endif
}

GLOBAL int CAR_DirCarrier()
{  DIR * dir;
   struct dirent * dirent_ptr;
   
   dirent_ptr = dir = Copendir("");
   If (dir != NULL) Then
      DebugPrintf(VERBOSE, "%.15s %ld\n", dirent_ptr->d_name, dirent_ptr->d_size);
      While (TRUE) Do
         dirent_ptr = Creaddir(dir);
         If (dirent_ptr == NULL) Then
            break;
         Else
            DebugPrintf(VERBOSE, "%.15s %ld\n", dirent_ptr->d_name, dirent_ptr->d_size);
         Endif
      Endwhile
      Cclosedir(dir);
      return USR_NO_ERROR;
   Else
      If (errno == ENOF) Then
         DebugPrintf(VERBOSE, "no files found\n");
         return USR_NO_ERROR;
      Else
         DebugPrintf(VERBOSE|FAILURES, "failed to open directory: %d\n", errno);
         return errno;
      Endif
   Endif
}  

GLOBAL int CAR_RemoveFile(char * file)
{  int err;
   char dfilename[MAX_PATH_LEN];
   
   err = ExtractFileName(file, dfilename);
   If (err != USR_NO_ERROR) Then
      DebugPrintf(VERBOSE|FAILURES, "error extracting file name %d\n", err);
      return err;
   Endif

   strupr(dfilename);
   DebugPrintf(VERBOSE, "removing %s\n", dfilename);
   err = Cremove(dfilename);
   If (err != USR_NO_ERROR) Then
      DebugPrintf(VERBOSE|FAILURES, "failed to remove %s %d\n", dfilename, errno);
      return errno;
   Else
      DebugPrintf(VERBOSE, "%s removed\n", dfilename);
      return USR_NO_ERROR;
   Endif
}

GLOBAL int CAR_SaveFile(char * file, int format)
{  FILE * istream;
   FILE * ostream;
   char iname[MAX_PATH_LEN];
   char oname[MAX_PATH_LEN];
   int err;

   sprintf(iname, "%s", file);
   If (format == FMFAT) Then
      err = MakeFMFileName(oname);
      If (err != USR_NO_ERROR) Then
         DebugPrintf(VERBOSE|FAILURES, "error making fm file name %d\n", err);
         return err;
      Endif
   Elseif (format == FX25 || format == FMT2 || format == FMT1) Then
      err = ExtractFileName(file, oname);
      If (err != USR_NO_ERROR) Then
         DebugPrintf(VERBOSE|FAILURES, "error extracting file name %d\n", err);
         return err;
      Endif
   Else
      sprintf(oname, "%s", file);
   Endif
   strupr(iname);
   strupr(oname);

   DebugPrintf(VERBOSE, "saving %s to %s\n", iname, oname);

{
   int err;
   FILE_INFO file_info;
   err = CAR_FileInfo(iname, &file_info);
   If (err) Then
      DebugPrintf(VERBOSE, "no file info: %d\n", err);
   Else
      DebugPrintf(VERBOSE, "file format %d version %d\n", file_info.format, file_info.version);
   Endif
}

   istream = fopen(iname, "rb");
   If (istream != NULL) Then
      ostream = Cfopen(oname, "wb");
      If (ostream != NULL) Then
         int nread = ITEMS;
         int nwrite = ITEMS;
         While (nread == ITEMS && nwrite == ITEMS) Do
            nread = fread(Buffer, BLOCK_SIZE, ITEMS, istream);
            If (nread < 0) Then
               int read_errno = errno;
               fclose(istream);
               Cfclose(ostream);
               DebugPrintf(VERBOSE|FAILURES, "failed to read %s %d", iname, errno);
               return read_errno;
            Endif               
            nwrite = Cfwrite(Buffer, BLOCK_SIZE, nread, ostream);
         Endwhile
         If (nwrite != nread) Then
            int write_errno = errno;
            DebugPrintf(VERBOSE|FAILURES, "failed to write to %s %d\n", oname, errno);
            Cfclose(ostream);
            fclose(istream);
            DebugPrintf(VERBOSE, "deleting %s\n", oname);
            Cremove(oname);
            return write_errno;
         Else
            Cfclose(ostream);
            fclose(istream);
            DebugPrintf(VERBOSE, "%s saved to %s\n", iname, oname);
            return USR_NO_ERROR;
         Endif
      Else
         int open_errno = errno;
         DebugPrintf(VERBOSE|FAILURES, "failed to open %s %d\n", oname, errno);
         fclose(istream);
         return open_errno;
      Endif
   Else
      DebugPrintf(VERBOSE|FAILURES, "failed to open %s %d\n", iname, errno);
      return errno;
   Endif
}

GLOBAL int CAR_RestoreFile(char * filename)
{  FILE * istream;
   FILE * ostream;
   char iname[MAX_PATH_LEN];
   char oname[MAX_PATH_LEN];

   sprintf(iname, "%s", filename);
   sprintf(oname, "%s", filename);
   strupr(iname);
   strupr(oname);

   DebugPrintf(VERBOSE, "restoring %s from %s\n", iname, oname);

   istream = Cfopen(iname, "rb");
   If (istream != NULL) Then
      ostream = fopen(oname, "wb");
      If (ostream != NULL) Then
         int nread = ITEMS;
         int nwrite = ITEMS;
         While (nread == ITEMS && nwrite == ITEMS) Do
            nread = Cfread(Buffer, BLOCK_SIZE, ITEMS, istream);
            If (nread < 0) Then
               int read_errno = errno;
               DebugPrintf(VERBOSE|FAILURES, "failed to read %s %d", iname, errno);
               Cfclose(istream);
               fclose(ostream);
               return read_errno;
            Endif               
            nwrite = fwrite(Buffer, BLOCK_SIZE, nread, ostream);
         Endwhile
         If (nwrite != nread) Then
            int write_errno = errno;
            DebugPrintf(VERBOSE|FAILURES, "failed to write to %s %d\n", oname, errno);
            fclose(ostream);
            Cfclose(istream);
            DebugPrintf(VERBOSE, "deleting %s\n", oname);
            remove(oname);
            return write_errno;
         Else
            fclose(ostream);
            Cfclose(istream);
            DebugPrintf(VERBOSE, "%s restored to %s\n", iname, oname);

{
   int err;
   FILE_INFO file_info;
   err = CAR_FileInfo(oname, &file_info);
   If (err) Then
      DebugPrintf(VERBOSE, " no file info: %d\n", err);
   Else
      DebugPrintf(VERBOSE, " file format %d version %d\n", file_info.format, file_info.version);
   Endif
}

            return USR_NO_ERROR;
         Endif
      Else
         int open_errno = errno;
         DebugPrintf(VERBOSE|FAILURES, "failed to open %s %d\n", oname, errno);
         Cfclose(istream);
         return open_errno;
      Endif
   Else
      DebugPrintf(VERBOSE|FAILURES, "failed to open %s %d\n", iname, errno);
      return errno;
   Endif
}

GLOBAL int CAR_RestoreFileTo(char * filename, char * out_filename)
{  FILE * istream;
   FILE * ostream;
   char iname[MAX_PATH_LEN];
   char oname[MAX_PATH_LEN];
   int err;

   sprintf(iname, "%s", filename);
   sprintf(oname, "%s", out_filename);
   strupr(iname);
   strupr(oname);

   DebugPrintf(VERBOSE, "restoring %s from %s\n", iname, oname);

   istream = Cfopen(iname, "rb");
   If (istream != NULL) Then
      ostream = fopen(oname, "wb");
      If (ostream != NULL) Then
         int nread = ITEMS;
         int nwrite = ITEMS;
         While (nread == ITEMS && nwrite == ITEMS) Do
            nread = Cfread(Buffer, BLOCK_SIZE, ITEMS, istream);
            If (nread < 0) Then
               int read_errno = errno;
               DebugPrintf(VERBOSE|FAILURES, "failed to read %s %d", iname, errno);
               err = Cfclose(istream);
               err = fclose(ostream);
               return read_errno;
            Endif               
            nwrite = fwrite(Buffer, BLOCK_SIZE, nread, ostream);
         Endwhile
         If (nwrite != nread) Then
            int write_errno = errno;
            DebugPrintf(VERBOSE|FAILURES, "failed to write to %s %d\n", oname, errno);
            err = Cfclose(istream);
            err = fclose(ostream);
            DebugPrintf(VERBOSE, "deleting %s\n", oname);
            remove(oname);
            return write_errno;
         Else
            err = Cfclose(istream);
            err = fclose(ostream);
            DebugPrintf(VERBOSE, "%s restored to %s\n", iname, oname);

{
   int err;
   FILE_INFO file_info;
   err = CAR_FileInfo(oname, &file_info);
   If (err) Then
      DebugPrintf(VERBOSE, " no file info: %d\n", err);
   Else
      DebugPrintf(VERBOSE, " file format %d version %d\n", file_info.format, file_info.version);
   Endif
}

            return USR_NO_ERROR;
         Endif
      Else
         int open_errno = errno;
         DebugPrintf(VERBOSE|FAILURES, "failed to open %s %d\n", oname, errno);
         err = Cfclose(istream);
         return open_errno;
      Endif
   Else
      DebugPrintf(VERBOSE|FAILURES, "failed to open %s %d\n", iname, errno);
      return errno;
   Endif
}

GLOBAL int CAR_RestoreAllFiles(char * destination_path)
{  DIR * dir;
   int err;
   struct dirent * dirent_ptr;
   char dst_file[MAX_PATH_LEN] = {0};   
   
   dirent_ptr = dir = Copendir("");
   If (dir != NULL) Then
      If (destination_path == NULL ) Then
         sprintf(dst_file, "%s", dirent_ptr->d_name);
      Else
         sprintf(dst_file, "%s\\%s", destination_path, dirent_ptr->d_name);
      Endif
      If ((err = CAR_RestoreFileTo(dirent_ptr->d_name, dst_file)) != USR_NO_ERROR) Then
         Cclosedir(dir);
         return err;
      Endif
      While (TRUE) Do
         dirent_ptr = Creaddir(dir);
         If (dirent_ptr == NULL) Then
            break;
         Else
            If (destination_path == NULL ) Then
               sprintf(dst_file, "%s", dirent_ptr->d_name);
            Else
               sprintf(dst_file, "%s\\%s", destination_path, dirent_ptr->d_name);
            Endif
            If ((err = CAR_RestoreFileTo(dirent_ptr->d_name, dst_file)) != USR_NO_ERROR) Then
               Cclosedir(dir);
               return err;
            Endif
         Endif
      Endwhile
      Cclosedir(dir);
      return USR_NO_ERROR;
   Else
      If (errno == ENOF) Then
         DebugPrintf(VERBOSE, "no files found\n");
         return USR_NO_ERROR;
      Else
         DebugPrintf(VERBOSE|FAILURES, "failed to open directory: %d\n", errno);
         return errno;
      Endif
   Endif
}  

GLOBAL int CAR_RemoveAllFiles()
{  DIR * dir;
   int err;
   struct dirent * dirent_ptr;
   
   dirent_ptr = dir = Copendir("");
   If (dir != NULL) Then
      If ((err = CAR_RemoveFile(dirent_ptr->d_name)) != USR_NO_ERROR) Then
         Cclosedir(dir);
         return err;
      Endif
      While (TRUE) Do
         dirent_ptr = Creaddir(dir);
         If (dirent_ptr == NULL) Then
            break;
         Else
            If ((err = CAR_RemoveFile(dirent_ptr->d_name)) != USR_NO_ERROR) Then
               Cclosedir(dir);
               return err;
            Endif
         Endif
      Endwhile
      Cclosedir(dir);
      return USR_NO_ERROR;
   Else
      If (errno == ENOF) Then
         DebugPrintf(VERBOSE, "no files found\n");
         return USR_NO_ERROR;
      Else
         DebugPrintf(VERBOSE|FAILURES, "failed to open directory: %d\n", errno);
         return errno;
      Endif
   Endif
}  

GLOBAL int CAR_FileInfo(char * path, FILE_INFO * fileinfo)
{
   return Cfileinfo(path, fileinfo);
}

GLOBAL int CAR_SetTime(char * path)
{
   return Csettime(path);
}

GLOBAL int CAR_SetRegVal(char * path, long regid, int index, long value)
{
   return Csetregval(path, regid, index, value);
}

GLOBAL int CAR_GetRegVal(char * path, long regid, int index, long * value)
{
   return Cgetregval(path, regid, index, value);
}

GLOBAL int CAR_SetData(char * path, char * artno, char * matno, char * toolno)
{
   return Csetdata(path, artno, matno, toolno);
}


