/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     FMT2
*
*  BESCHREIBUNG:
*     Ferromatik FMT2-Zugriffsfunktionen.
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
*     01.07.98 -PR- Unterstuetzung fuer Mehraggregatmaschinen eingebaut.
*                   Das ganze wurde mit einem Hoechstmass an zusaetzlichem
*                   Code realisiert, um Fluechtigkeitsfehler für die schon
*                   unterstuetzten Datentraeger zu vermeiden.
*     12.03.99  -PR- Auf Jahr 2000-Faehigkeit ueberprueft und angepasst.
*     09.08.99  -PR- ToolNr und MatNr richtig umgerechnet.
*
*
*  BEMERKUNGEN:
*
*     Die Checksumme im Haupt-Header wird nur fuer Grafikdatentraeger verwendet
*     Grafikdatentraeger koennen aktuell noch nicht eingelesen werden,
*
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  FUNKTIONEN:
*
*      FMT2_Module
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
#ifndef __fmt2__
#include <fmt2.h>
#define __fmt2__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __srvice__
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

#define MAX_FMT2_FILES  3

#define _OPEN     0x1000

typedef struct fmt2_cb
{  USR_WORD flags;
   long filepos;
   long filesize;
   char * buffer;
}  FMT2CB;

LOCAL FMT2CB Cariobuffer[MAX_FMT2_FILES + 1] = {{0}};
LOCAL USR_BYTE TempBuf[4096];

LOCAL int FileNo(char * filename)
{  int fileno;
   If (sscanf(filename, "OLDCAR.%d", &fileno) == 1) Then
      If (fileno > 0 && fileno < MAX_FMT2_FILES + 1) Then
         return fileno;
      Else
         return FMT2_INVALID_FILENO;
      Endif
   Else
      return FMT2_INVALID_FILENAME;
   Endif
}

LOCAL FMT2CB * Iobuffer(int fileno)
{
   If (fileno > 0 && fileno < MAX_FMT2_FILES + 1) Then
      return &Cariobuffer[fileno];
   Else
      return NULL;
   Endif
}

/* Implementierung der Zugriffsfunktionen
 */

LOCAL long FileSize(int fileno)
{  int err;
   OLD_DISK_HEADER header;
   long size = sizeof(OLD_DISK_HEADER) +
               sizeof(OLD_DISK_SUB_HEADER) +
               DATA_SIZE;
   if ((err = BASIC_Read((long)ADR_HEADER, sizeof(header),
                           (char*)&header)) != USR_NO_ERROR) return err;
   size += header.TextLength;
   return size;
}

LOCAL long FileSize_2F()
{  int err;
   OLD_DISK_HEADER header;
   long size = sizeof(OLD_DISK_HEADER) +
               sizeof(SUB_HEADER_2F) +
               DATA_SIZE_2F;
   if ((err = BASIC_Read((long)ADR_HEADER, sizeof(header),
                           (char*)&header)) != USR_NO_ERROR) return err;
   size += header.TextLength;
   return size;
}

LOCAL long FileSize_3F()
{  int err;
   OLD_DISK_HEADER header;
   long size = sizeof(OLD_DISK_HEADER) +
               sizeof(SUB_HEADER_3F) +
               DATA_SIZE_3F;
   if ((err = BASIC_Read((long)ADR_HEADER, sizeof(header),
                           (char*)&header)) != USR_NO_ERROR) return err;
   size += header.TextLength;
   return size;
}

LOCAL long CarrierPos(int fileno, int object)
{
   Switch (object)
   Case ID_SUBHEADER:
      Switch (fileno)
      Case 1: return ADR_SUBHEADER_1;
      Case 2: return ADR_SUBHEADER_2;
      Case 3: return ADR_SUBHEADER_3;
      Endswitch
   Case ID_LIST:
      Switch (fileno)
      Case 1: return ADR_LIST_1;
      Case 2: return ADR_LIST_2;
      Case 3: return ADR_LIST_3;
      Endswitch
   Endswitch
   return -42L;
}

LOCAL long DINT2Long (long value)
{
   return (value >> 16) * 10000L + (value & 0x0000ffffL);
}

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

LOCAL int MakeFileChecksum(int fileno)
{  USR_BYTE checksum;
   int err;
   
   Switch (fileno)
   Case 1:
      if ((err = BASIC_Read(ADR_LIST_1, DATA_SIZE, TempBuf)) != USR_NO_ERROR) return err;
      checksum = Checksum(TempBuf, 0, DATA_SIZE);
      if ((err = BASIC_Write(0x27, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   Case 2:
      if ((err = BASIC_Read(ADR_LIST_2, DATA_SIZE, TempBuf)) != USR_NO_ERROR) return err;
      checksum = Checksum(TempBuf, 0, DATA_SIZE);
      if ((err = BASIC_Write(0x3f, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   Case 3:
      if ((err = BASIC_Read(ADR_LIST_3, DATA_SIZE, TempBuf)) != USR_NO_ERROR) return err;
      checksum = Checksum(TempBuf, 0, DATA_SIZE);
      if ((err = BASIC_Write(0x57, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   Endswitch
   return USR_NO_ERROR;
}

LOCAL int MakeFileChecksum_2F()
{  USR_BYTE checksum;
   int err;
   
   if ((err = BASIC_Read(ADR_LIST_2F, DATA_SIZE_2F, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, DATA_SIZE_2F);
   if ((err = BASIC_Write(0x27, 1, &checksum)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
}

LOCAL int MakeFileChecksum_3F()
{  USR_BYTE checksum;
   int err;
   
   if ((err = BASIC_Read(ADR_LIST_3F, DATA_SIZE_3F, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, DATA_SIZE_3F);
   if ((err = BASIC_Write(0x27, 1, &checksum)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
}

LOCAL int LoadFile(int fileno, char * buffer)
{  int err;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER subheader;
   long carrierpos;
   long size;
   char * buffer_ptr = buffer;

   carrierpos = (long)ADR_HEADER;
   size = sizeof(header);
   if ((err = BASIC_Read(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &header, size);
   buffer_ptr += size;

   carrierpos = CarrierPos(fileno, ID_SUBHEADER);
   size = sizeof(subheader);
   if ((err = BASIC_Read(carrierpos, size, (char*)&subheader)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &subheader, size);
   buffer_ptr += size;

   carrierpos = CarrierPos(fileno, ID_LIST);
   size = DATA_SIZE;
   if ((err = BASIC_Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = BASIC_Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   return USR_NO_ERROR;
}

LOCAL int LoadFile_2F(int fileno, char * buffer)
{  int err;
   OLD_DISK_HEADER header;
   SUB_HEADER_2F subheader;
   long carrierpos;
   long size;
   char * buffer_ptr = buffer;

   carrierpos = (long)ADR_HEADER;
   size = sizeof(header);
   if ((err = BASIC_Read(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &header, size);
   buffer_ptr += size;

   carrierpos = ADR_SUBHEADER_2F;
   size = sizeof(subheader);
   if ((err = BASIC_Read(carrierpos, size, (char*)&subheader)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &subheader, size);
   buffer_ptr += size;

   carrierpos = ADR_LIST_2F;
   size = DATA_SIZE_2F;
   if ((err = BASIC_Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = BASIC_Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   return USR_NO_ERROR;
}

LOCAL int LoadFile_3F(int fileno, char * buffer)
{  int err;
   OLD_DISK_HEADER header;
   SUB_HEADER_3F subheader;
   long carrierpos;
   long size;
   char * buffer_ptr = buffer;

   carrierpos = (long)ADR_HEADER;
   size = sizeof(header);
   if ((err = BASIC_Read(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &header, size);
   buffer_ptr += size;

   carrierpos = ADR_SUBHEADER_3F;
   size = sizeof(subheader);
   if ((err = BASIC_Read(carrierpos, size, (char*)&subheader)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &subheader, size);
   buffer_ptr += size;

   carrierpos = ADR_LIST_3F;
   size = DATA_SIZE_3F;
   if ((err = BASIC_Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = BASIC_Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   return USR_NO_ERROR;
}

LOCAL int FlushFile(int fileno, char * buffer)
{  int err;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER subheader;
   long  carrierpos;
   long  size;
   char * buffer_ptr = buffer;

   carrierpos = (long)ADR_HEADER;
   size = sizeof(header);
   memcpy(&header, buffer_ptr, size);
   if (header.TextLength > MAX_TEXT_LEN) header.TextLength = MAX_TEXT_LEN;
   if ((err = BASIC_Write(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = CarrierPos(fileno, ID_SUBHEADER);
   size = sizeof(subheader);
   memcpy(&subheader, buffer_ptr, size);
   if ((err = BASIC_Write(carrierpos, size, (char*)&subheader)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = CarrierPos(fileno, ID_LIST);
   size = DATA_SIZE;
   if ((err = BASIC_Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = BASIC_Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   
   If ((err = MakeFileChecksum(fileno)) != USR_NO_ERROR) Then
      return err;
   Else
      return USR_NO_ERROR;
   Endif
}

LOCAL int FlushFile_2F(int fileno, char * buffer)
{  int err;
   OLD_DISK_HEADER header;
   SUB_HEADER_2F subheader;
   long  carrierpos;
   long  size;
   char * buffer_ptr = buffer;

   carrierpos = (long)ADR_HEADER;
   size = sizeof(header);
   memcpy(&header, buffer_ptr, size);
   if (header.TextLength > MAX_TEXT_LEN) header.TextLength = MAX_TEXT_LEN;
   if ((err = BASIC_Write(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = ADR_SUBHEADER_2F;
   size = sizeof(subheader);
   memcpy(&subheader, buffer_ptr, size);
   if ((err = BASIC_Write(carrierpos, size, (char*)&subheader)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = ADR_LIST_2F;
   size = DATA_SIZE_2F;
   if ((err = BASIC_Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = BASIC_Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   
   If ((err = MakeFileChecksum_2F()) != USR_NO_ERROR) Then
      return err;
   Else
      return USR_NO_ERROR;
   Endif
}

LOCAL int FlushFile_3F(int fileno, char * buffer)
{  int err;
   OLD_DISK_HEADER header;
   SUB_HEADER_3F subheader;
   long  carrierpos;
   long  size;
   char * buffer_ptr = buffer;

   carrierpos = (long)ADR_HEADER;
   size = sizeof(header);
   memcpy(&header, buffer_ptr, size);
   if (header.TextLength > MAX_TEXT_LEN) header.TextLength = MAX_TEXT_LEN;
   if ((err = BASIC_Write(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = ADR_SUBHEADER_3F;
   size = sizeof(subheader);
   memcpy(&subheader, buffer_ptr, size);
   if ((err = BASIC_Write(carrierpos, size, (char*)&subheader)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = ADR_LIST_3F;
   size = DATA_SIZE_3F;
   if ((err = BASIC_Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;

   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = BASIC_Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   
   If ((err = MakeFileChecksum_3F()) != USR_NO_ERROR) Then
      return err;
   Else
      return USR_NO_ERROR;
   Endif
}

LOCAL int FMT2_OpenFile(USR_WORD flags, char * filename)
{  int err;
   FMT2CB * iobuffer;
   int fileno = FileNo(filename);
   If ((iobuffer = Iobuffer(fileno)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      If (iobuffer->flags & _OPEN) Then
         return FMT2_FILE_ALROP;
      Else
         char * buffer;
         int size = MAX_FILE_SIZE;
         If ((buffer = HeapAlloc((int)size)) == NULL) Then
            return FMT2_NO_MEMORY;
         Else
            If (flags & _READ) Then
               If ((err = LoadFile(fileno, buffer)) == USR_NO_ERROR) Then
                  iobuffer->flags = flags | _OPEN;
                  iobuffer->filepos = 0L;
                  iobuffer->filesize = (long)FileSize(fileno);
                  iobuffer->buffer = buffer;
                  return fileno;
               Else
                  HeapFree(buffer);
                  return err;
               Endif
            Elseif (flags & _WRITE) Then
               iobuffer->flags = flags | _OPEN;
               iobuffer->filepos = 0L;
               iobuffer->filesize = 0L;
               iobuffer->buffer = buffer;
               return fileno;
            Else
               HeapFree(buffer);
               return FMT2_INVALID_MODE;
            Endif               
         Endif
      Endif
   Endif
}

LOCAL int FMT2_2F_OpenFile(USR_WORD flags, char * filename)
{  int err;
   FMT2CB * iobuffer;
   int fileno = FileNo(filename);
   If ((iobuffer = Iobuffer(fileno)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      If (iobuffer->flags & _OPEN) Then
         return FMT2_FILE_ALROP;
      Else
         char * buffer;
         int size = MAX_FILE_SIZE;
         If ((buffer = HeapAlloc((int)size)) == NULL) Then
            return FMT2_NO_MEMORY;
         Else
            If (flags & _READ) Then
               If ((err = LoadFile_2F(fileno, buffer)) == USR_NO_ERROR) Then
                  iobuffer->flags = flags | _OPEN;
                  iobuffer->filepos = 0L;
                  iobuffer->filesize = (long)FileSize_2F();
                  iobuffer->buffer = buffer;
                  return fileno;
               Else
                  HeapFree(buffer);
                  return err;
               Endif
            Elseif (flags & _WRITE) Then
               iobuffer->flags = flags | _OPEN;
               iobuffer->filepos = 0L;
               iobuffer->filesize = 0L;
               iobuffer->buffer = buffer;
               return fileno;
            Else
               HeapFree(buffer);
               return FMT2_INVALID_MODE;
            Endif               
         Endif
      Endif
   Endif
}

LOCAL int FMT2_3F_OpenFile(USR_WORD flags, char * filename)
{  int err;
   FMT2CB * iobuffer;
   int fileno = FileNo(filename);
   If ((iobuffer = Iobuffer(fileno)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      If (iobuffer->flags & _OPEN) Then
         return FMT2_FILE_ALROP;
      Else
         char * buffer;
         int size = MAX_FILE_SIZE;
         If ((buffer = HeapAlloc((int)size)) == NULL) Then
            return FMT2_NO_MEMORY;
         Else
            If (flags & _READ) Then
               If ((err = LoadFile_3F(fileno, buffer)) == USR_NO_ERROR) Then
                  iobuffer->flags = flags | _OPEN;
                  iobuffer->filepos = 0L;
                  iobuffer->filesize = (long)FileSize_3F();
                  iobuffer->buffer = buffer;
                  return fileno;
               Else
                  HeapFree(buffer);
                  return err;
               Endif
            Elseif (flags & _WRITE) Then
               iobuffer->flags = flags | _OPEN;
               iobuffer->filepos = 0L;
               iobuffer->filesize = 0L;
               iobuffer->buffer = buffer;
               return fileno;
            Else
               HeapFree(buffer);
               return FMT2_INVALID_MODE;
            Endif               
         Endif
      Endif
   Endif
}

LOCAL int FMT2_CloseFile(int hnd)
{  FMT2CB * iobuffer;
   If ((iobuffer = Iobuffer(hnd)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      if (iobuffer->flags & _WRITE) FlushFile(hnd, iobuffer->buffer);
      HeapFree(iobuffer->buffer);
      memset(iobuffer, 0, sizeof(FMT2CB));
      return USR_NO_ERROR;
   Endif
}

LOCAL int FMT2_2F_CloseFile(int hnd)
{  FMT2CB * iobuffer;
   If ((iobuffer = Iobuffer(hnd)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      if (iobuffer->flags & _WRITE) FlushFile_2F(hnd, iobuffer->buffer);
      HeapFree(iobuffer->buffer);
      memset(iobuffer, 0, sizeof(FMT2CB));
      return USR_NO_ERROR;
   Endif
}

LOCAL int FMT2_3F_CloseFile(int hnd)
{  FMT2CB * iobuffer;
   If ((iobuffer = Iobuffer(hnd)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      if (iobuffer->flags & _WRITE) FlushFile_3F(hnd, iobuffer->buffer);
      HeapFree(iobuffer->buffer);
      memset(iobuffer, 0, sizeof(FMT2CB));
      return USR_NO_ERROR;
   Endif
}

LOCAL int FMT2_ReadFile(int hnd, void * buffer, int size)
{  FMT2CB * iobuffer;
   If ((iobuffer = Iobuffer(hnd)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      If (iobuffer->flags & _OPEN) Then
         long chars_to_read;
         long max_read_size = iobuffer->filesize - iobuffer->filepos;
         if (max_read_size <= 0L) return ERR_PAST_END;
         If ((long)size > max_read_size) Then
            chars_to_read = max_read_size;
         Else
            chars_to_read = size;
         Endif
         memcpy(buffer, &(iobuffer->buffer[iobuffer->filepos]), (int)chars_to_read);
         iobuffer->filepos += chars_to_read;
         If (chars_to_read < (long)size) Then
            return ERR_PAST_END;
         Else
            return USR_NO_ERROR;
         Endif
      Else
         return FMT2_FILE_NOTOP;
      Endif
   Endif
}

LOCAL int FMT2_WriteFile(int hnd, void * buffer, int size)
{  FMT2CB * iobuffer;
   If ((iobuffer = Iobuffer(hnd)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      If (iobuffer->flags & _OPEN) Then
         long chars_to_write;
         long max_write_size = MAX_FILE_SIZE - iobuffer->filepos;
         if (max_write_size <= 0L) return ERR_PAST_END;
         If ((long)size > max_write_size) Then
            chars_to_write = max_write_size;
         Else
            chars_to_write = size;
         Endif
         memcpy(&(iobuffer->buffer[iobuffer->filepos]), (char*)buffer, (int)chars_to_write);
         iobuffer->filepos += chars_to_write;
         iobuffer->filesize = iobuffer->filepos;
         If (chars_to_write < (long)size) Then
            return ERR_PAST_END;
         Else
            return USR_NO_ERROR;
         Endif
      Else
         return FMT2_FILE_NOTOP;
      Endif
   Endif
}

LOCAL long FMT2_GetSize(int hnd)
{  FMT2CB * iobuffer;
   If ((iobuffer = Iobuffer(hnd)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      If (iobuffer->flags & _OPEN) Then
         return iobuffer->filesize;
      Else
         return FMT2_FILE_NOTOP;
      Endif
   Endif
}

LOCAL long FMT2_GetPos(int hnd)
{  FMT2CB * iobuffer;
   If ((iobuffer = Iobuffer(hnd)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      If (iobuffer->flags & _OPEN) Then
         return iobuffer->filepos;
      Else
         return FMT2_FILE_NOTOP;
      Endif
   Endif
}

LOCAL int FMT2_SetPos(int hnd, long pos)
{  FMT2CB * iobuffer;
   If ((iobuffer = Iobuffer(hnd)) == NULL) Then
      return FMT2_INVALID_HANDLE;
   Else
      If (iobuffer->flags & _OPEN) Then
         If (pos < 0 || pos > iobuffer->filesize) Then
            return FMT2_INVALID_SEEKPOS;
         Else
            iobuffer->filepos = pos;
            return USR_NO_ERROR;
         Endif
      Else
         return FMT2_FILE_NOTOP;
      Endif
   Endif
}

LOCAL int FMT2_RemoveFile(char * filename)
{  int fileno, err;
   OLD_DISK_SUB_HEADER subheader;
   long carrierpos;
   
   If ((fileno = FileNo(filename)) > 0) Then
      memset(&subheader, 0, sizeof(subheader));
      carrierpos = CarrierPos(fileno, ID_SUBHEADER);
      if ((err = BASIC_Write(carrierpos, sizeof(subheader),
                           (char*)&subheader)) != USR_NO_ERROR) return err;
      if ((err = MakeFileChecksum(fileno)) != USR_NO_ERROR) return err;
      return USR_NO_ERROR;
   Else
      return fileno;
   Endif
}

LOCAL int FMT2_2F_RemoveFile(char * filename)
{  int fileno, err;
   SUB_HEADER_2F subheader;
   long carrierpos;
   
   If ((fileno = FileNo(filename)) > 0) Then
      memset(&subheader, 0, sizeof(subheader));
      carrierpos = ADR_SUBHEADER_2F;
      if ((err = BASIC_Write(carrierpos, sizeof(subheader),
                           (char*)&subheader)) != USR_NO_ERROR) return err;
      if ((err = MakeFileChecksum_2F()) != USR_NO_ERROR) return err;
      return USR_NO_ERROR;
   Else
      return fileno;
   Endif
}

LOCAL int FMT2_3F_RemoveFile(char * filename)
{  int fileno, err;
   SUB_HEADER_3F subheader;
   long carrierpos;
   
   If ((fileno = FileNo(filename)) > 0) Then
      memset(&subheader, 0, sizeof(subheader));
      carrierpos = ADR_SUBHEADER_3F;
      if ((err = BASIC_Write(carrierpos, sizeof(subheader),
                           (char*)&subheader)) != USR_NO_ERROR) return err;
      if ((err = MakeFileChecksum_3F()) != USR_NO_ERROR) return err;
      return USR_NO_ERROR;
   Else
      return fileno;
   Endif
}

LOCAL int FMT2_Directory(DIR ** dir)
{  int i, err;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER subheader;
   long carrierpos;
   
   if ((err = BASIC_Read((long)ADR_HEADER, sizeof(header),
                           (char*)&header)) != USR_NO_ERROR) return err;
   DebugPrintf(VERBOSE, "TextLength %d ProcNr %d CarrierNr %d CarrierLength %d Id %d CheckSum %02x\n",
               header.TextLength,
               header.ProcNr,
               header.CarrierNr,
               header.CarrierLength,
               (int)header.Id,
               (int)header.CheckSum);
   *dir = HeapAlloc(sizeof(DIR) * MAX_FMT2_FILES);
   For (i=0; i<MAX_FMT2_FILES; i++) Do
      carrierpos = CarrierPos(i + 1, ID_SUBHEADER);
      if ((err = BASIC_Read(carrierpos, sizeof(subheader),
                              (char*)&subheader)) != USR_NO_ERROR) return err;
      DebugPrintf(VERBOSE, "MashCode %d ProgNr %d Diameter %d PresConst %d\n",
                  subheader.MashCode,
                  subheader.ProgNr,
                  (int)subheader.Diameter,
                  (int)subheader.PresConst);
      DebugPrintf(VERBOSE, "MashSize %d Aggregat %d HeatZoneCount %d\n",
                  subheader.MashSize,
                  (int)subheader.Aggregat,
                  (int)subheader.HeatZoneCount);
      DebugPrintf(VERBOSE, "MatNr %ld ToolNr %ld Date %02x %02x %02x %02x %02x\n",
                  DINT2Long(subheader.MatNr),
                  DINT2Long(subheader.ToolNr),
                  (int)subheader.Date[0],
                  (int)subheader.Date[1],
                  (int)subheader.Date[2],
                  (int)subheader.Date[3],
                  (int)subheader.Date[4]);
      If (subheader.Date[1] != 0) Then
         sprintf((*dir)[i].d_name, "OLDCAR.%03d", i + 1);
         (*dir)[i].d_size = FileSize(i + 1);
      Else
         sprintf((*dir)[i].d_name, "OLDCAR.%03d", i + 1);
         (*dir)[i].d_size = 0L;
      Endif
   Endfor
   return MAX_FMT2_FILES;
}

LOCAL int FMT2_2F_Directory(DIR ** dir)
{  int err;
   OLD_DISK_HEADER header;
   SUB_HEADER_2F subheader;
   long carrierpos;
   
   if ((err = BASIC_Read((long)ADR_HEADER, sizeof(header),
                           (char*)&header)) != USR_NO_ERROR) return err;
      DebugPrintf(VERBOSE, "TextLength %d ProcNr %d CarrierNr %d CarrierLength %d Id %d CheckSum %02x\n",
                  header.TextLength,
                  header.ProcNr,
                  header.CarrierNr,
                  header.CarrierLength,
                  (int)header.Id,
                  (int)header.CheckSum);
   *dir = HeapAlloc(sizeof(DIR));
   carrierpos = ADR_SUBHEADER_2F;
   if ((err = BASIC_Read(carrierpos, sizeof(subheader),
                         (char*)&subheader)) != USR_NO_ERROR) return err;
   DebugPrintf(VERBOSE, "MashCode %d ProgNr %d Diameter %d PresConst %d\n",
               subheader.MashCode,
               subheader.ProgNr,
               (int)subheader.Diameter,
               (int)subheader.PresConst);
   DebugPrintf(VERBOSE, "MashSize %d Aggregat %d HeatZoneCount %d\n",
               subheader.MashSize,
               (int)subheader.Aggregat,
               (int)subheader.HeatZoneCount);
   DebugPrintf(VERBOSE, "MatNr %ld ToolNr %ld Date %02x %02x %02x %02x %02x\n",
               DINT2Long(subheader.MatNr),
               DINT2Long(subheader.ToolNr),
               (int)subheader.Date[0],
               (int)subheader.Date[1],
               (int)subheader.Date[2],
               (int)subheader.Date[3],
               (int)subheader.Date[4]);
   If (subheader.Date[1] != 0) Then
      sprintf((*dir)->d_name, "OLDCAR.%03d", 1);
      (*dir)->d_size = FileSize_2F();
   Else
      sprintf((*dir)->d_name, "OLDCAR.%03d", 1);
      (*dir)->d_size = 0L;
   Endif
   return 1;
}

LOCAL int FMT2_3F_Directory(DIR ** dir)
{  int err;
   OLD_DISK_HEADER header;
   SUB_HEADER_3F subheader;
   long carrierpos;
   
   if ((err = BASIC_Read((long)ADR_HEADER, sizeof(header),
                           (char*)&header)) != USR_NO_ERROR) return err;
      DebugPrintf(VERBOSE, "TextLength %d ProcNr %d CarrierNr %d CarrierLength %d Id %d CheckSum %02x\n",
                  header.TextLength,
                  header.ProcNr,
                  header.CarrierNr,
                  header.CarrierLength,
                  (int)header.Id,
                  (int)header.CheckSum);
   *dir = HeapAlloc(sizeof(DIR));
   carrierpos = ADR_SUBHEADER_3F;
   if ((err = BASIC_Read(carrierpos, sizeof(subheader),
                         (char*)&subheader)) != USR_NO_ERROR) return err;
   DebugPrintf(VERBOSE, "MashCode %d ProgNr %d Diameter %d PresConst %d\n",
               subheader.MashCode,
               subheader.ProgNr,
               (int)subheader.Diameter,
               (int)subheader.PresConst);
   DebugPrintf(VERBOSE, "MashSize %d Aggregat %d HeatZoneCount %d\n",
               subheader.MashSize,
               (int)subheader.Aggregat,
               (int)subheader.HeatZoneCount);
   DebugPrintf(VERBOSE, "MatNr %ld ToolNr %ld Date %02x %02x %02x %02x %02x\n",
               DINT2Long(subheader.MatNr),
               DINT2Long(subheader.ToolNr),
               (int)subheader.Date[0],
               (int)subheader.Date[1],
               (int)subheader.Date[2],
               (int)subheader.Date[3],
               (int)subheader.Date[4]);
   If (subheader.Date[1] != 0) Then
      sprintf((*dir)->d_name, "OLDCAR.%03d", 1);
      (*dir)->d_size = FileSize_3F();
   Else
      sprintf((*dir)->d_name, "OLDCAR.%03d", 1);
      (*dir)->d_size = 0L;
   Endif
   return 1;
}

LOCAL int FMT2_Format(int param)
{  int i, err;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER subheader;
   long carrierpos;
   
   memset(&header, 0, sizeof(header));
   header.TextLength = 8;
   header.ProcNr = 1001;
   header.CarrierNr = 0;
   header.CarrierLength = 0;
   header.Id = 1;
   header.CheckSum = 0;
   memset(&subheader, 0, sizeof(subheader));
   
   if ((err = BASIC_Write((long)ADR_HEADER, sizeof(header),
                        (char*)&header)) != USR_NO_ERROR) return err;
   For (i=0; i<MAX_FMT2_FILES; i++) Do
      carrierpos = CarrierPos(i + 1, ID_SUBHEADER);
      if ((err = BASIC_Write(carrierpos, sizeof(subheader),
                           (char*)&subheader)) != USR_NO_ERROR) return err;
      if ((err = MakeFileChecksum(i + 1)) != USR_NO_ERROR) return err;
   Endfor
   return USR_NO_ERROR;
}

LOCAL int FMT2_2F_Format(int param)
{
   return FMT2_FORMAT_NOT_SUPPORTED;
}

LOCAL int FMT2_3F_Format(int param)
{
   return FMT2_FORMAT_NOT_SUPPORTED;
}

LOCAL int FMT2_Init()
{
   return USR_NO_ERROR;
}

LOCAL int FMT2_Version(OLD_DISK_HEADER header, DRIVE_INFO * driveinfo)
{  int version;

   If ((version = Fmt2Version(&header, NULL)) < 0) Then
      DebugPrintf(DEBUG_DEVICES, "FMT2: version invalid %d\n", version);
      return version;
   Else
      driveinfo->format = FMT2;
      driveinfo->version = version;
      Switch (version)
      Case FMT2_FM:
      Case FMT2_FXA:
      Case FMT2_FXP: driveinfo->module = FMT2_Module(); break;
      Case FMT2_FM_2F:
      Case FMT2_FXA_2F:
      Case FMT2_FXP_2F: driveinfo->module = FMT2_2F_Module(); break;
      Case FMT2_FM_3F:
      Case FMT2_FXA_3F:
      Case FMT2_FXP_3F: driveinfo->module = FMT2_3F_Module(); break;
      Endswitch
      return USR_NO_ERROR;
   Endif
}

LOCAL int FMT2_TestChecksum()
{  int err;
   USR_BYTE checksum1 = 0, checksum2 = 0, checksum3 = 0,
            checksum = 0;
   
#ifdef TEST_CHECKSUM
   if ((err = BASIC_Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_1, DATA_SIZE, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, DATA_SIZE);
   If (checksum1 != checksum) Then
      DebugPrintf(DEBUG_DEVICES, "FMT2: checksum 1 invalid\n", err);
      return FMT2_CHECKSUM1;
   Endif

   if ((err = BASIC_Read(0x3f, 1, &checksum2)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_2, DATA_SIZE, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, DATA_SIZE);
   If (checksum2 != checksum) Then
      DebugPrintf(DEBUG_DEVICES, "FMT2: checksum 2 invalid\n", err);
      return FMT2_CHECKSUM2;
   Endif

   if ((err = BASIC_Read(0x57, 1, &checksum3)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_3, DATA_SIZE, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, DATA_SIZE);
   If (checksum3 != checksum) Then
      DebugPrintf(DEBUG_DEVICES, "FMT2: checksum 3 invalid\n", err);
      return FMT2_CHECKSUM3;
   Endif
   return USR_NO_ERROR;
#endif
}

LOCAL int FMT2_2F_TestChecksum()
{  int err;
   USR_BYTE checksum1 = 0, checksum = 0;
   
#ifdef TEST_CHECKSUM
   if ((err = BASIC_Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_2F, DATA_SIZE_2F, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, DATA_SIZE_2F);
   If (checksum1 != checksum) Then
      DebugPrintf(DEBUG_DEVICES, "FMT2: checksum 2 aggregat machine invalid\n", err);
      return FMT2_2F_CHECKSUM;
   Endif
   return USR_NO_ERROR;
#endif
}

LOCAL int FMT2_3F_TestChecksum()
{  int err;
   USR_BYTE checksum1 = 0, checksum = 0;
   
#ifdef TEST_CHECKSUM
   if ((err = BASIC_Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return err;
   if ((err = BASIC_Read(ADR_LIST_3F, DATA_SIZE_3F, TempBuf)) != USR_NO_ERROR) return err;
   checksum = Checksum(TempBuf, 0, DATA_SIZE_3F);
   If (checksum1 != checksum) Then
      DebugPrintf(DEBUG_DEVICES, "FMT2: checksum 3 aggregat machine invalid\n", err);
      return FMT2_3F_CHECKSUM;
   Endif
   return USR_NO_ERROR;
#endif
}

LOCAL int FMT2_DriveInfo(DRIVE_INFO * driveinfo)
{  int err;
   OLD_DISK_HEADER header;
   
   if ((err = BASIC_Read((long)ADR_HEADER, sizeof(header), (char*)&header)) != USR_NO_ERROR)
      return err;
   If (header.Id == 0x01) Then
      If ((err = FMT2_TestChecksum()) == USR_NO_ERROR) Then
         return FMT2_Version(header, driveinfo);
      Else
         return err;
      Endif
   Elseif (header.Id == 0x81) Then
      If ((err = FMT2_2F_TestChecksum()) == USR_NO_ERROR) Then
         return FMT2_Version(header, driveinfo);
      Else
         return err;
      Endif
   Elseif (header.Id == 0x82) Then
      If ((err = FMT2_3F_TestChecksum()) == USR_NO_ERROR) Then
         return FMT2_Version(header, driveinfo);
      Else
         return err;
      Endif
   Elseif (header.Id == 0x02) Then
      DebugPrintf(DEBUG_DEVICES, "FMT2: graphic data carrier detected\n");
      return FMT2_GRAPHIC_NOT_SUPPORTED;
   Else
      DebugPrintf(DEBUG_DEVICES, "FMT2: header id invalid %d\n", header.Id);
      return FMT2_INVALID_VERSION;
   Endif
}

extern int FMT2_FileInfo(char * path, FILE_INFO * fileinfo);

LOCAL const DRIVE_MODULE FMT2_DriveModule =
{  FMT2_OpenFile,
   FMT2_CloseFile,
   FMT2_ReadFile,
   FMT2_WriteFile,
   FMT2_GetSize,
   FMT2_GetPos,
   FMT2_SetPos,
   FMT2_RemoveFile,
   FMT2_Directory,
   FMT2_Format,
   FMT2_Init,
   FMT2_DriveInfo, 
   FMT2_FileInfo
};

GLOBAL const DRIVE_MODULE * FMT2_Module()
{
   return &FMT2_DriveModule;
}


extern int FMT2_2F_FileInfo(char * path, FILE_INFO * fileinfo);

LOCAL const DRIVE_MODULE FMT2_2F_DriveModule =
{  FMT2_2F_OpenFile,
   FMT2_2F_CloseFile,
   FMT2_ReadFile,
   FMT2_WriteFile,
   FMT2_GetSize,
   FMT2_GetPos,
   FMT2_SetPos,
   FMT2_2F_RemoveFile,
   FMT2_2F_Directory,
   FMT2_2F_Format,
   FMT2_Init,
   FMT2_DriveInfo, 
   FMT2_FileInfo
};

GLOBAL const DRIVE_MODULE * FMT2_2F_Module()
{
   return &FMT2_2F_DriveModule;
}


extern int FMT2_3F_FileInfo(char * path, FILE_INFO * fileinfo);

LOCAL const DRIVE_MODULE FMT2_3F_DriveModule =
{  FMT2_3F_OpenFile,
   FMT2_3F_CloseFile,
   FMT2_ReadFile,
   FMT2_WriteFile,
   FMT2_GetSize,
   FMT2_GetPos,
   FMT2_SetPos,
   FMT2_3F_RemoveFile,
   FMT2_3F_Directory,
   FMT2_3F_Format,
   FMT2_Init,
   FMT2_DriveInfo, 
   FMT2_FileInfo
};

GLOBAL const DRIVE_MODULE * FMT2_3F_Module()
{
   return &FMT2_3F_DriveModule;
}

typedef struct
{  int procno;
   int version;
}  FMT2_VERSION;

LOCAL const FMT2_VERSION FMT2Versions[] =
{  {1001, FMT2_FM},
   {1020, FMT2_FXP},
   {1030, FMT2_FXA},
   {2001, FMT2_FM_2F},
   {2020, FMT2_FXP_2F},
   {2030, FMT2_FXA_2F},
   {3001, FMT2_FM_3F},
   {3020, FMT2_FXP_3F},
   {3030, FMT2_FXA_3F}
};

#define FMT2_VERSION_ENTRIES    (sizeof(FMT2Versions) / sizeof(FMT2_VERSION))

LOCAL int Fmt2Version(OLD_DISK_HEADER * header, FILE * stream)
{  int i;
   FMT2_VERSION * fmtvers;

   DebugPrintf(DEBUG_DEVICES, "FMT2: procedure no %d\n", header->ProcNr);
   For (i=0, fmtvers = FMT2Versions; i<FMT2_VERSION_ENTRIES; i++, fmtvers++) Do
      if (fmtvers->procno == header->ProcNr) return fmtvers->version;
   Endfor
   return FMT2_INVALID_PROCNO;
}

#define FMT2_GET_DAY(date) ((USR_BYTE)date[2])
#define FMT2_GET_MONTH(date) ((USR_BYTE)date[1])
#define FMT2_GET_YEAR(date) \
	(((USR_BYTE)date[0] < 70) ? \
	((USR_BYTE)date[0] + 100) : (USR_BYTE)date[0])
#define FMT2_GET_SEC(date) (0)
#define FMT2_GET_HOUR(date) ((USR_BYTE)date[3])
#define FMT2_GET_MIN(date) ((USR_BYTE)date[4])

#define FMT2_SET_YEAR(year)	((year < 100) ? year : year - 100)

LOCAL void SetTime(char * date)
{  struct tm * act_time = NULL;
	time_t now;

	time(&now);
	act_time = localtime(&now);
	date[0] = FMT2_SET_YEAR(act_time->tm_year);
	date[1] = act_time->tm_mon + 1;
	date[2] = act_time->tm_mday;
	date[3] = act_time->tm_hour;
	date[4] = act_time->tm_min;
}


LOCAL int AllocFile(char * path, char * mode, OLD_DISK_HEADER ** header_ptr, 
                    OLD_DISK_SUB_HEADER ** subheader_ptr, FILE ** stream_ptr)
{  OLD_DISK_HEADER * header;
   OLD_DISK_SUB_HEADER * subheader;
   FILE * stream;
   int version;
   
   *header_ptr = *stream_ptr = NULL;
   header = (OLD_DISK_HEADER *)HeapAlloc(sizeof(OLD_DISK_HEADER));
   if (header == NULL) return ERR_DRAM_ALLOC;
   subheader = (OLD_DISK_SUB_HEADER *)HeapAlloc(sizeof(OLD_DISK_SUB_HEADER));
   If (subheader == NULL) Then
      HeapFree(header);
      return ERR_DRAM_ALLOC;
   Endif
   If ((stream = fopen(path, mode)) != NULL) Then
      int nread = fread(header, sizeof(OLD_DISK_HEADER), 1, stream);
      If (nread != 1) Then
         fclose(stream);
         HeapFree(subheader);
         HeapFree(header);
         return FMT2_FILE_READ_FAILURE;
      Else
         int nread = fread(subheader, sizeof(OLD_DISK_SUB_HEADER), 1, stream);
         If (nread != 1) Then
            fclose(stream);
            HeapFree(subheader);
            HeapFree(header);
            return FMT2_FILE_READ_FAILURE;
         Else
            If (header->Id == 0x01 || header->Id == 0x81 || header->Id == 0x82) Then
               If ((version = Fmt2Version(header, stream)) < 0) Then
                  fclose(stream);
                  HeapFree(subheader);
                  HeapFree(header);
               Else
                  *header_ptr = header;
                  *subheader_ptr = subheader;
                  *stream_ptr = stream;
               Endif
               return version;
            Elseif (header->Id == 0x02) Then
               *header_ptr = header;
               *subheader_ptr = subheader;
               *stream_ptr = stream;
               return FMT2_GRAPHIC;
            Else
               fclose(stream);
               HeapFree(subheader);
               HeapFree(header);
               return FMT2_INVALID_CARRIER_ID;
            Endif
         Endif
      Endif
   Else
      return FMT2_FILE_OPEN_FAILURE;
   Endif
}

LOCAL int FreeFile(OLD_DISK_HEADER * header, OLD_DISK_SUB_HEADER * subheader,
                   FILE * stream, USR_BOOL touch)
{  int err;
    
   If (touch) Then
      SetTime(&subheader->Date);
      If (fseek(stream, 0L, SEEK_SET) == 0) Then
         If (fwrite(header, sizeof(OLD_DISK_HEADER), 1, stream) == 1) Then
            If (fseek(stream, sizeof(OLD_DISK_HEADER), SEEK_SET) == 0) Then
               If (fwrite(subheader, sizeof(OLD_DISK_SUB_HEADER), 1, stream) == 1) Then
                  err = USR_NO_ERROR;
               Else
                  err = FMT2_FILE_WRITE_FAILURE;
               Endif
            Else
               err = FMT2_FILE_SEEK_ERROR;
            Endif
         Else
            err = FMT2_FILE_WRITE_FAILURE;
         Endif
      Else
         err = FMT2_FILE_SEEK_ERROR;
      Endif
   Else
      err = USR_NO_ERROR;
   Endif
   fclose(stream);
   HeapFree(subheader);
   HeapFree(header);
   return err;
}

LOCAL int FMT2_FileInfo(char * path, FILE_INFO * fileinfo)
{  int version;
   OLD_DISK_HEADER * header;
   OLD_DISK_SUB_HEADER * subheader;
   FILE * stream;

   memset(fileinfo, 0, sizeof(FILE_INFO)); 
   If ((version = AllocFile(path, "rb", &header, &subheader, &stream)) > 0) Then
      fileinfo->day = FMT2_GET_DAY(subheader->Date);
      fileinfo->month = FMT2_GET_MONTH(subheader->Date);
      fileinfo->year = FMT2_GET_YEAR(subheader->Date) + 1900;
      fileinfo->sec = FMT2_GET_SEC(subheader->Date);
      fileinfo->min = FMT2_GET_MIN(subheader->Date);
      fileinfo->hour = FMT2_GET_HOUR(subheader->Date);
      sprintf(fileinfo->matno, "%ld", DINT2Long(subheader->MatNr));
      sprintf(fileinfo->toolno, "%ld", DINT2Long(subheader->ToolNr));
      sprintf(fileinfo->machtype, "FM%d", subheader->MashSize);
      sprintf(fileinfo->artno, "");
      fileinfo->format = FMT2;
      fileinfo->version = version;
      return FreeFile(header, subheader, stream, FALSE);
   Else
      return version;
   Endif
}

LOCAL int FMT2_SetTime(char * path)
{  OLD_DISK_HEADER * header;
   OLD_DISK_SUB_HEADER * subheader;
   FILE * stream;
   int version;

   If ((version = AllocFile(path, "rb+", &header, &subheader, &stream)) > 0) Then
      return FreeFile(header, subheader, stream, TRUE);
   Else
      return version;
   Endif
}

LOCAL const long AllowedRegs[] =
{  40, 41, 42, 43, 44, 45, 46, 47, 48, 49
};
#define ALLOWED_REGS    (sizeof(AllowedRegs) / sizeof(AllowedRegs[0]))

LOCAL USR_BOOL RegAllowed(long regid)
{  int i;

   For (i=0; i<ALLOWED_REGS; i++) Do
      if (regid == AllowedRegs[i]) return TRUE;
   Endfor
   return FALSE;
}

LOCAL int FMT2_SetRegVal(char * path, long regid, int index, long value)
{  OLD_DISK_HEADER * header;
   OLD_DISK_SUB_HEADER * subheader;
   FILE * stream;
   int version, err;
   signed_16 * buf = TempBuf;

   if (!RegAllowed(regid)) return FMT2_REG_NOT_ALLOWED;
   If (regid >= 0 && regid < FMT2_REGS) Then
      If ((version = AllocFile(path, "rb+", &header, &subheader, &stream)) > 0) Then
         If (fseek(stream, sizeof(OLD_DISK_HEADER) + sizeof(OLD_DISK_SUB_HEADER), SEEK_SET) == 0) Then
            If (fread(buf, DATA_SIZE, 1, stream) == 1) Then
               buf[regid] = value;
               If (fseek(stream, sizeof(OLD_DISK_HEADER) + sizeof(OLD_DISK_SUB_HEADER), SEEK_SET) == 0) Then
                  If (fwrite(buf, DATA_SIZE, 1, stream) == 1) Then
                     err = USR_NO_ERROR;
                  Else
                     err = FMT2_FILE_WRITE_FAILURE;
                  Endif
               Else
                  err = FMT2_FILE_SEEK_ERROR;
               Endif
            Else
               err = FMT2_FILE_READ_FAILURE;
            Endif
         Else
            err = FMT2_FILE_SEEK_ERROR;
         Endif
         FreeFile(header, subheader, stream, TRUE);
         return err;
      Else
         return version;
      Endif
   Else
      return FMT2_INVALID_REGID;
   Endif
}

LOCAL int FMT2_GetRegVal(char * path, long regid, int index, long * value)
{  OLD_DISK_HEADER * header;
   OLD_DISK_SUB_HEADER * subheader;
   FILE * stream;
   int version, err;
   signed_16 * buf = TempBuf;

   If (regid >= 0 && regid < FMT2_REGS) Then
      If ((version = AllocFile(path, "rb", &header, &subheader, &stream)) > 0) Then
         If (fseek(stream, sizeof(OLD_DISK_HEADER) + sizeof(OLD_DISK_SUB_HEADER), SEEK_SET) == 0) Then
            If (fread(buf, DATA_SIZE, 1, stream) == 1) Then
               *value = buf[regid];
               err = USR_NO_ERROR;
            Else
               err = FMT2_FILE_READ_FAILURE;
            Endif
         Else
            err = FMT2_FILE_SEEK_ERROR;
         Endif
         FreeFile(header, subheader, stream, FALSE);
         return err;
      Else
         return version;
      Endif
   Else
      return FMT2_INVALID_REGID;
   Endif
}

LOCAL int FMT2_SetData(char * path, char * matno, char * artno, char * toolno)
{
   return USR_NO_ERROR;
}


LOCAL const FILE_MODULE FMT2_FModule =
{  FMT2_SetTime,
   FMT2_SetRegVal,
   FMT2_GetRegVal,
   FMT2_SetData
};

GLOBAL const FILE_MODULE * FMT2_FileModule()
{
   return &FMT2_FModule;
}

