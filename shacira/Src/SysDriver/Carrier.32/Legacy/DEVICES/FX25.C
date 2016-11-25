/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     FX25
*
*  BESCHREIBUNG:
*     Ferromatik FX25-Zugriffsfunktionen.
*
*  UMGEBUNG:
*     ZIELRECHNER:           PC-AT
*     ENTWICKLUNGSRECHNER:   PC-AT
*     UEBERSETZER:
*     OPTIONEN:
*
*  VERSION:
*     VERSION:    1.00                      DATUM:   18.03.96
*     AUTOR(EN):                            TELEFON: (0761) 4520520
*
*  HISTORY:
*
*     12.03.99  -PR- Auf Jahr 2000-Faehigkeit ueberprueft und angepasst.
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
*      FX25_Module
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
#ifndef __time__
#include <time.h>
#define __time__
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
#ifndef __fx25__
#include <fx25.h>
#define __fx25__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __service__
#include <service.h>
#define __service__
#endif
#ifndef __debug__
#include <debug.h>
#define __debug__
#endif
/***************************************************************************/
/* Verwaltung von Zugriffen
*/

#define FX25_USER_FORMAT_STRING "F25"
#define FX25_USER_FORMAT_POS 28L         

#define MAX_FX25_FILES  3
#define _OPEN     0x1000

typedef struct fx25_cb
{  USR_WORD flags;
   long filepos;
   long filesize;
   char * buffer;
}  FX25_CB;

LOCAL FX25_CB Cariobuf[MAX_FX25_FILES + 1] = {0};
LOCAL USR_BYTE TempBuf[4096];


/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FileNo(char * filename)
{  int fileno;
   If (sscanf(filename, "OLDCAR.%d", &fileno) == 1) Then
      If (fileno > 0 && fileno < MAX_FX25_FILES + 1) Then
         return fileno;
      Else
         return FX25_INVALID_FILENO;
      Endif
   Else
      return FX25_INVALID_FILENAME;
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL FX25_CB * Iobuf(int fileno)
{
   If (fileno > 0 && fileno < MAX_FX25_FILES + 1) Then
      return &Cariobuf[fileno];
   Else
      return NULL;
   Endif
}


/* Implementierung der Zugriffsfunktionen */

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL long FileSize(int fileno)
{
   return (long)OLD_SIZE_FX;
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL long CarrierPos(int fileno)
{
   Switch (fileno)
   Case 1: return 0L;
   Case 2: return 1024L;
   Case 3: return 2048L;
   Endswitch
   return -42L;
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL USR_BYTE Checksum(USR_BYTE * buffer, int src, int offs)
{  USR_BYTE val;
   USR_BYTE checksum;
   long i;

   checksum = 0;
   For (i=src; i<src+offs; i++) Do
      val = buffer[i];
      checksum ^= val;
   Endfor
   return checksum;
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int MakeFileChecksum(int fileno)
{  USR_BYTE checksum;
   int err;
   USR_WORD prog_len;
   Switch (fileno)
   Case 1:
      if ((err = BASIC_Read(64, 960, TempBuf)) != USR_NO_ERROR) return err;
      checksum = Checksum(TempBuf, 0, 960);
      checksum--;
      if ((err = BASIC_Write(0x01d, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = BASIC_Write(0x41d, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = BASIC_Write(0x81d, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   Case 2:
      if ((err = BASIC_Read(64 + 0x400, 960, TempBuf)) != USR_NO_ERROR) return err;
      checksum = Checksum(TempBuf, 0, 960);
      checksum--;
      if ((err = BASIC_Write(0x01c, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = BASIC_Write(0x41c, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = BASIC_Write(0x81c, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   Case 3:
      if ((err = BASIC_Read(64 + 0x800, 960, TempBuf)) != USR_NO_ERROR) return err;
      checksum = Checksum(TempBuf, 0, 960);
      checksum--;
      if ((err = BASIC_Write(0x01e, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = BASIC_Write(0x41e, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = BASIC_Write(0x81e, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   Endswitch
   if ((err = BASIC_Read(14, 2, TempBuf)) != USR_NO_ERROR) return err;
   prog_len = (((unsigned int)TempBuf[1])<<8) | ((unsigned int)TempBuf[0]);
   If ((prog_len > 0) && (prog_len < 32)) Then
      if ((err = BASIC_Read(0, prog_len, TempBuf)) != USR_NO_ERROR) return err;
      checksum = Checksum(TempBuf, 0, prog_len);
      if ((err = BASIC_Write(31, 1, &checksum)) != USR_NO_ERROR) return err;
   Endif
   return USR_NO_ERROR;
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int LoadFile(int fileno, char * buffer)
{  int err;
   long  carrierpos;
   long  size;
   char * buf_ptr = buffer;

   carrierpos = CarrierPos(fileno);
   size = OLD_SIZE_FX;
   if ((err = BASIC_Read(carrierpos, size, buf_ptr)) != USR_NO_ERROR) return err;
   buf_ptr += size;
   return USR_NO_ERROR;
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FlushFile(int fileno, char * buffer)
{  int err;
   long  carrierpos;
   long  size;
   char * buf_ptr = buffer;

   carrierpos = CarrierPos(fileno);
   size = OLD_SIZE_FX;
   if ((err = BASIC_Write(carrierpos, size, buf_ptr)) != USR_NO_ERROR) return err;
   buf_ptr += size;
   
   If ((err = MakeFileChecksum(fileno)) != USR_NO_ERROR) Then
      return err;
   Else
      MakeFileChecksum(1);
      MakeFileChecksum(2);
      MakeFileChecksum(3);
      return USR_NO_ERROR;
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FX25_OpenFile(USR_WORD flags, char * filename)
{  int err;
   FX25_CB * iobuf;
   int fileno = FileNo(filename);
   If ((iobuf = Iobuf(fileno)) == NULL) Then
      return FX25_INVALID_HANDLE;
   Else
      If (iobuf->flags & _OPEN) Then
         return FX25_FILE_ALROP;
      Else
         char * buffer;
         int size = OLD_SIZE_FX;
         If ((buffer = malloc((int)size)) == NULL) Then
            return FX25_NO_MEMORY;
         Else
            If (flags & _READ) Then
               If ((err = LoadFile(fileno, buffer)) == USR_NO_ERROR) Then
                  iobuf->flags = flags | _OPEN;
                  iobuf->filepos = 0L;
                  iobuf->filesize = (long)FileSize(fileno);
                  If ((err = Fx25WriteFormatInFile(buffer)) != USR_NO_ERROR) Then
                     free(buffer);
                     return err;
                  Endif
                  iobuf->buffer = buffer;
                  return fileno;
               Else
                  free(buffer);
                  return err;
               Endif
            Elseif (flags & _WRITE) Then
               iobuf->flags = flags | _OPEN;
               iobuf->filepos = 0L;
               iobuf->filesize = 0L;
               iobuf->buffer = buffer;
               return fileno;
            Else
               free(buffer);
               return FX25_INVALID_MODE;
            Endif               
         Endif
      Endif
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FX25_CloseFile(int hnd)
{  FX25_CB * iobuf;
   If ((iobuf = Iobuf(hnd)) == NULL) Then
      return FX25_INVALID_HANDLE;
   Else
      if (iobuf->flags & _WRITE) FlushFile(hnd, iobuf->buffer);
      free(iobuf->buffer);
      memset(iobuf, 0, sizeof(FX25_CB));
      return USR_NO_ERROR;
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FX25_ReadFile(int hnd, void * buf, int size)
{  FX25_CB * iobuf;
   If ((iobuf = Iobuf(hnd)) == NULL) Then
      return FX25_INVALID_HANDLE;
   Else
      If (iobuf->flags & _OPEN) Then
         long chars_to_read;
         long max_read_size = iobuf->filesize - iobuf->filepos;
         if (max_read_size <= 0L) return ERR_PAST_END;
         If ((long)size > max_read_size) Then
            chars_to_read = max_read_size;
         Else
            chars_to_read = size;
         Endif
         memcpy(buf, &(iobuf->buffer[iobuf->filepos]), (int)chars_to_read);
         iobuf->filepos += chars_to_read;
         If (chars_to_read < (long)size) Then
            return ERR_PAST_END;
         Else
            return USR_NO_ERROR;
         Endif
      Else
         return FX25_FILE_NOTOP;
      Endif
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FX25_WriteFile(int hnd, void * buf, int size)
{  FX25_CB * iobuf;
   If ((iobuf = Iobuf(hnd)) == NULL) Then
      return FX25_INVALID_HANDLE;
   Else
      If (iobuf->flags & _OPEN) Then
         long chars_to_write;
         long max_write_size = OLD_SIZE_FX - iobuf->filepos;
         if (max_write_size <= 0L) return ERR_PAST_END;
         If ((long)size > max_write_size) Then
            chars_to_write = max_write_size;
         Else
            chars_to_write = size;
         Endif
         memcpy(&(iobuf->buffer[iobuf->filepos]), (char*)buf, (int)chars_to_write);
         iobuf->filepos += chars_to_write;
         iobuf->filesize = iobuf->filepos;
         If (chars_to_write < (long)size) Then
            return ERR_PAST_END;
         Else
            return USR_NO_ERROR;
         Endif
      Else
         return FX25_FILE_NOTOP;
      Endif
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL long FX25_GetSize(int hnd)
{  FX25_CB * iobuf;
   If ((iobuf = Iobuf(hnd)) == NULL) Then
      return FX25_INVALID_HANDLE;
   Else
      If (iobuf->flags & _OPEN) Then
         return iobuf->filesize;
      Else
         return FX25_FILE_NOTOP;
      Endif
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL long FX25_GetPos(int hnd)
{  FX25_CB * iobuf;
   If ((iobuf = Iobuf(hnd)) == NULL) Then
      return FX25_INVALID_HANDLE;
   Else
      If (iobuf->flags & _OPEN) Then
         return iobuf->filepos;
      Else
         return FX25_FILE_NOTOP;
      Endif
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FX25_SetPos(int hnd, long pos)
{  FX25_CB * iobuf;
   If ((iobuf = Iobuf(hnd)) == NULL) Then
      return FX25_INVALID_HANDLE;
   Else
      If (iobuf->flags & _OPEN) Then
         If (pos < 0 || pos > iobuf->filesize) Then
            return FX25_INVALID_SEEKPOS;
         Else
            iobuf->filepos = pos;
            return USR_NO_ERROR;
         Endif
      Else
         return FX25_FILE_NOTOP;
      Endif
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FX25_RemoveFile(char * filename)
{  int fileno, err;
   OLD_FX25_DISK_SUB_HEADER subheader;
   long carrierpos;
   long size;
   
   If ((fileno = FileNo(filename)) > 0) Then
      carrierpos = CarrierPos(fileno);
      size = OLD_SIZE_FX;
      size = 100;
      memset(TempBuf, 0, (int)size);
      memset(&subheader, 0, sizeof(subheader));
      subheader.LenHeader = 32;
      memcpy(TempBuf, &subheader, sizeof(subheader));
      if ((err = BASIC_Write(carrierpos, size, TempBuf)) != USR_NO_ERROR) return err;
      if ((err = MakeFileChecksum(fileno)) != USR_NO_ERROR) return err;
      MakeFileChecksum(1);
      MakeFileChecksum(2);
      MakeFileChecksum(3);
      return USR_NO_ERROR;
   Else
      return fileno;
   Endif
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FX25_Directory(DIR ** dir)
{  int i, err;
   OLD_FX25_DISK_SUB_HEADER subheader;
   long carrierpos;
   int file_counter;

   file_counter = 0;
   *dir = malloc(sizeof(DIR) * MAX_FX25_FILES);
   For (i=0; i<MAX_FX25_FILES; i++) Do
      carrierpos = CarrierPos(i + 1);
      if ((err = BASIC_Read(carrierpos, sizeof(subheader),
                              (char*)&subheader)) != USR_NO_ERROR) return err;
      DebugPrintf(VERBOSE, "ToolNr %d MatNr %d ProcNr %d LenHeader %d\n",
       subheader.ToolNr,
       subheader.MatNr,
       subheader.ProcNr,
       subheader.LenHeader);
      DebugPrintf(VERBOSE, "LenData %d LenProgFeld %d Date %02x %02x %02x %02x\n",
       subheader.LenData,
       subheader.LenProgFeld,
       (int)subheader.Date[0],
       (int)subheader.Date[1],
       (int)subheader.Date[2],
       (int)subheader.Date[3]);
#ifdef SHOW_EMPTY_FILE
      If (subheader.Date[0] != 0) Then
         sprintf((*dir)[file_counter].d_name, "OLDCAR.%03d", i + 1);
         (*dir)[file_counter].d_size = FileSize(i + 1);
         file_counter++;
      Else
         sprintf((*dir)[file_counter].d_name, "OLDCAR.%03d", i + 1);
         (*dir)[file_counter].d_size = 0L;
      Endif
#else
      If (subheader.Date[1] != 0) Then
         sprintf((*dir)[i].d_name, "OLDCAR.%03d", i + 1);
         (*dir)[i].d_size = FileSize(i + 1);
      Else
         sprintf((*dir)[i].d_name, "OLDCAR.%03d", i + 1);
         (*dir)[i].d_size = 0L;
      Endif
      file_counter++;
#endif
   Endfor
   return file_counter;
}

/*---------------------------------------------------------------------
| Löscht die Datensätze auf dem Datenträger und initialisiert diese mit
| einer neuen Checksumme für die leeren Datensätze.
| 
|----------------------------------------------------------------------*/
LOCAL int FX25_Format(int param)
{  int err;
   If ((err = FX25_RemoveFile("OLDCAR.001")) != USR_NO_ERROR) return err;
   If ((err = FX25_RemoveFile("OLDCAR.002")) != USR_NO_ERROR) return err;
   If ((err = FX25_RemoveFile("OLDCAR.003")) != USR_NO_ERROR) return err;
   MakeFileChecksum(1);
   MakeFileChecksum(2);
   MakeFileChecksum(3);
   return USR_NO_ERROR;
}

/*-----------------------------------------------------------------------------------
|
------------------------------------------------------------------------------------*/
LOCAL int FX25_Init()
{
   return USR_NO_ERROR;
}

/*----------------------------------------------------------------------
| 
------------------------------------------------------------------------*/
LOCAL int FX25_DriveInfo(DRIVE_INFO * driveinfo)
{  int err;

   USR_BYTE checksum1 = 0, checksum2 = 0, checksum3 = 0, checksum = 0;

#ifdef TEST_CHECKSUM
   if ((err = BASIC_Read(64, 960, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, 960);
   checksum--;
   if ((err = BASIC_Read(0x01d, 1, &checksum1)) != USR_NO_ERROR) return err;
   if (checksum1 != checksum) return FX25_CHECKSUM1;
   if ((err = BASIC_Read(0x41d, 1, &checksum1)) != USR_NO_ERROR) return err;
   if (checksum1 != checksum) return FX25_CHECKSUM1;
   if ((err = BASIC_Read(0x81d, 1, &checksum1)) != USR_NO_ERROR) return err;
   if (checksum1 != checksum) return FX25_CHECKSUM1;

   if ((err = BASIC_Read(64 + 0x400, 960, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, 960);
   checksum--; 
   if ((err = BASIC_Read(0x01c, 1, &checksum2)) != USR_NO_ERROR) return err;
   if (checksum2 != checksum) return FX25_CHECKSUM2; 
   if ((err = BASIC_Read(0x41c, 1, &checksum2)) != USR_NO_ERROR) return err;
   if (checksum2 != checksum) return FX25_CHECKSUM2; 
   if ((err = BASIC_Read(0x81c, 1, &checksum2)) != USR_NO_ERROR) return err;
   if (checksum2 != checksum) return FX25_CHECKSUM2; 

   if ((err = BASIC_Read(64 + 0x800, 960, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, 960);
   checksum--;
   if ((err = BASIC_Read(0x01e, 1, &checksum3)) != USR_NO_ERROR) return err;
   if (checksum3 != checksum) return FX25_CHECKSUM3; 
   if ((err = BASIC_Read(0x41e, 1, &checksum3)) != USR_NO_ERROR) return err;
   if (checksum3 != checksum) return FX25_CHECKSUM3; 
   if ((err = BASIC_Read(0x81e, 1, &checksum3)) != USR_NO_ERROR) return err;
   if (checksum3 != checksum) return FX25_CHECKSUM3; 
#endif
   driveinfo->format = FX25;
   driveinfo->version = FX25_FX;
   driveinfo->module = FX25_Module();
   return USR_NO_ERROR;
}


/*-----------------------------------------------------------------------
|
----------------------------------------------------------------------- */
LOCAL int Fx25TestFormatInFile(FILE *stream)
{
char tempBuf[4];
long int save_pos, size_of_file;
    save_pos = ftell(stream);
    fseek(stream, 0L, SEEK_END );
    size_of_file = ftell(stream);
    If (size_of_file < OLD_SIZE_FX) Then
      fseek(stream,save_pos,SEEK_SET);
      return FX25_USER_CHECK_ERR;
    Else
      fseek(stream,FX25_USER_FORMAT_POS,SEEK_SET);
      If (fread(tempBuf,sizeof(tempBuf),1,stream) != 1) Then
         fseek(stream,save_pos,SEEK_SET);
         return FX25_USER_CHECK_ERR;
      Else
         If (strncmp(tempBuf,FX25_USER_FORMAT_STRING,strlen(FX25_USER_FORMAT_STRING)) != 0) Then
            fseek(stream,save_pos,SEEK_SET);
            return FX25_USER_CHECK_ERR;
         Else
            fseek(stream,save_pos,SEEK_SET);
            return USR_NO_ERROR;
         Endif 
      Endif
   Endif
}

LOCAL int Fx25WriteFormatInFile(char *buffer)
{
      strncpy(&buffer[FX25_USER_FORMAT_POS],FX25_USER_FORMAT_STRING,strlen(FX25_USER_FORMAT_STRING));
      return USR_NO_ERROR;
}

LOCAL int Fx25Version(OLD_FX25_DISK_SUB_HEADER * header, FILE * stream)
{
   int err;
   If (header->LenHeader == 32) Then
      If ((err = Fx25TestFormatInFile(stream)) != USR_NO_ERROR) Then
         return err;
      Else
         return FX25_FX;
      Endif
   Else
      return FX25_INVALID_HEADERLEN;
   Endif
}

#define FX25_GET_DAY(date) ((USR_BYTE)date[2])
#define FX25_GET_MONTH(date) ((USR_BYTE)date[1])
#define FX25_GET_YEAR(date) \
        (((USR_BYTE)date[0] < 70) ? \
        ((USR_BYTE)date[0] + 100) : (USR_BYTE)date[0])
#define FX25_GET_SEC(date) (0)
#define FX25_GET_HOUR(date) (0)
#define FX25_GET_MIN(date) (0)

#define FX25_SET_YEAR(year)     ((year < 100) ? year : year - 100)

LOCAL void SetTime(char * date)
{  struct tm * act_time = NULL;
	time_t now;

	time(&now);
	act_time = localtime(&now);
	date[0] = FX25_SET_YEAR(act_time->tm_year);
	date[1] = act_time->tm_mon + 1;
	date[2] = act_time->tm_mday;
}


LOCAL int FX25_FileInfo(char * path, FILE_INFO * fileinfo)
{  int version;
   OLD_FX25_DISK_SUB_HEADER * header;
   FILE * stream;

   memset(fileinfo, 0, sizeof(FILE_INFO)); 
   header = (OLD_FX25_DISK_SUB_HEADER *)malloc(sizeof(OLD_FX25_DISK_SUB_HEADER));
   if (header == NULL) return ERR_DRAM_ALLOC;
   If ((stream = fopen(path, "rb")) != NULL) Then
      int nread = fread(header, sizeof(OLD_FX25_DISK_SUB_HEADER), 1, stream);
      If (nread != 1) Then
         fclose(stream);
         free(header);
         return FX25_FILE_READ_FAILURE;
      Else
         If (header->LenHeader == 32) Then
            If ((version = Fx25Version(header, stream)) < 0) Then
               fclose(stream);
               free(header);
               return version;
            Else
               fileinfo->format = FX25;
               fileinfo->version = version;
               fileinfo->day = FX25_GET_DAY(header->Date);
               fileinfo->month = FX25_GET_MONTH(header->Date);
               fileinfo->year = FX25_GET_YEAR(header->Date) + 1900;
               fileinfo->sec = FX25_GET_SEC(header->Date);
               fileinfo->min = FX25_GET_MIN(header->Date);
               fileinfo->hour = FX25_GET_HOUR(header->Date);
               sprintf(fileinfo->matno, "%d", header->MatNr);
               sprintf(fileinfo->toolno, "%d", header->ToolNr);
               sprintf(fileinfo->machtype, "FX25");
               sprintf(fileinfo->artno, "");
               fclose(stream);
               free(header);
               return USR_NO_ERROR;
            Endif
         Else
            fclose(stream);
            free(header);
            return FX25_INVALID_HEADERLEN;
         Endif
      Endif
   Else
      free(header);
      return FX25_FILE_OPEN_FAILURE;
   Endif               
}

LOCAL const DRIVE_MODULE FX25_DriveModule =
{  FX25_OpenFile,
   FX25_CloseFile,
   FX25_ReadFile,
   FX25_WriteFile,
   FX25_GetSize,
   FX25_GetPos,
   FX25_SetPos,
   FX25_RemoveFile,
   FX25_Directory,
   FX25_Format,
   FX25_Init,
   FX25_DriveInfo, 
   FX25_FileInfo
};

/*-----------------------------------------------------------------------
|
----------------------------------------------------------------------- */
GLOBAL const DRIVE_MODULE * FX25_Module()
{
   return &FX25_DriveModule;
}

LOCAL int FX25_SetTime(char * path)
{  int err;
   OLD_FX25_DISK_SUB_HEADER * header;
   FILE * stream;

   header = (OLD_FX25_DISK_SUB_HEADER *)malloc(sizeof(OLD_FX25_DISK_SUB_HEADER));
   if (header == NULL) return ERR_DRAM_ALLOC;
   If ((stream = fopen(path, "rb+")) != NULL) Then
      int nread = fread(header, sizeof(OLD_FX25_DISK_SUB_HEADER), 1, stream);
      If (nread != 1) Then
         fclose(stream);
         free(header);
         return FX25_FILE_READ_FAILURE;
      Else
         If (header->LenHeader == 32) Then
            If ((err = Fx25Version(header, stream)) < 0) Then
               fclose(stream);
               free(header);
               return err;
            Else
               SetTime(&header->Date);
               If (fseek(stream, 0L, SEEK_SET) == 0 &&
                   fwrite(header, sizeof(OLD_FX25_DISK_SUB_HEADER), 1, stream) == 1) Then
                  err = USR_NO_ERROR;
               Else
                  err = FX25_FILE_WRITE_FAILURE;
               Endif
               fclose(stream);
               free(header);
               return err;
            Endif
         Else
            fclose(stream);
            free(header);
            return FX25_INVALID_HEADERLEN;
         Endif
      Endif
   Else
      free(header);
      return FX25_FILE_OPEN_FAILURE;
   Endif               
}

LOCAL int FX25_SetRegVal(char * path, long regid, int index, long value)
{
   return USR_NO_ERROR;
}

LOCAL int FX25_GetRegVal(char * path, long regid, int index, long * value)
{
   return USR_NO_ERROR;
}

LOCAL int FX25_SetData(char * path, char * matno, char * artno, char * toolno)
{
   return USR_NO_ERROR;
}


LOCAL const FILE_MODULE FX25_FModule =
{  FX25_SetTime,
   FX25_SetRegVal,
   FX25_GetRegVal,
   FX25_SetData
};

GLOBAL const FILE_MODULE * FX25_FileModule()
{
   return &FX25_FModule;
}

