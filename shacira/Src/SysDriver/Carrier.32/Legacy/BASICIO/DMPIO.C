/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     DMPIO
*
*  BESchREIBUNG:
*     Zugriffsfunktionen fuer EEPROM-Dumps oder sonstige Speicherabzuege.
*
*  UMGEBUNG:
*     ZIELREchNER:           PC-AT
*     ENTWICKLUNGSREchNER:   PC-AT
*     UEBERSETZER:
*     OPTIONEN:
*
*  VERSION:
*     VERSION:    1.00                      DATUM:   25.03.96
*     AUTOR(EN):                            TELEFON: (0761) 4520520
*
*  HISTORY:
*
*
*
*  BEMERKUNGEN:
*
*
*---------------------------------------------------------------------------
*
*  EXPORTSchNITTSTELLE:
*
*  FUNKTIONEN:
*
*     DMP_Module
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
#ifndef __errcode__
#include <errcode.h>
#define __errcode__
#endif
#ifndef __errno__
#include <errno.h>
#define __errno__
#endif
#ifndef __dmpio__
#include <dmpio.h>
#define __dmpio__
#endif
#ifndef __debug__
#include <debug.h>
#define __debug__
#endif
/***************************************************************************/

LOCAL char DmpFile[128] = {0};
#define TEMP_BUF_SIZE      256
LOCAL char TempBuf[TEMP_BUF_SIZE] = {0};

LOCAL long CarrierSize(char * path)
{  int path_len = strlen(path);
   char extension[4] = {0};
   int ext = FALSE;
   int ext_ind = 0;
   int i;
   int size;
   
   For (i=0; i<path_len; i++) Do
      if (ext & ext_ind < 3) extension[ext_ind++] = path[i];
      if (path[i] == '.') ext = TRUE;
   Endfor
   If (ext) Then
      size = atoi(extension);
      If (size > 0 && size < 513) Then
         return (long)size * 1024L;
      Else
         return 32L * 1024L;
      Endif
   Else
         return 32L * 1024L;
   Endif
}

LOCAL int DMP_Init(IO_MODULE_ ** module, const char * path)
{  FILE * stream;
   long size = 1024L * 32L;
   int nwrite;
   
   size = CarrierSize(path);
   If ((stream = fopen(path, "rb")) != NULL) Then
      fclose(stream);
      sprintf(DmpFile, "%s", path);
      *module = DMP_Module();
      return USR_NO_ERROR;
   Else
      memset(TempBuf, 0, sizeof(TempBuf));
      If ((stream = fopen(path, "wb")) != NULL) Then
         While (size > 0) Do
            nwrite = fwrite(TempBuf, TEMP_BUF_SIZE, 1, stream);
            If (nwrite == 1) Then
               size -= TEMP_BUF_SIZE;
            Else
               fclose(stream);
               return errno;
            Endif
         Endwhile
         fclose(stream);
         sprintf(DmpFile, "%s", path);
         *module = DMP_Module();
         return USR_NO_ERROR;
      Else
         return errno;
      Endif      
   Endif
}

LOCAL int DMP_Check()
{  FILE * stream;
   long file_size = 0;

   If ((stream = fopen(DmpFile, "rb")) != NULL) Then
      While (fread(TempBuf, 1, 1, stream) == 1 && file_size < (128L * 1024L)) Do
         file_size++;
      Endwhile
		fclose(stream);
		return file_size / 1024L;
	Else
		return -errno;
	Endif
}

LOCAL int DMP_Read(USR_LONG address, USR_LONG size, void * buffer)
{  FILE * stream;
	int nread;

	if (size == 0) return USR_NO_ERROR;
	If ((stream = fopen(DmpFile, "rb")) != NULL) Then
		If (fseek(stream, address, SEEK_SET) == 0) Then
			nread = fread(buffer, (int)size, 1, stream);
			If (nread == 1) Then
				fclose(stream);
				return USR_NO_ERROR;
			Else
				fclose(stream);
				return -errno;
			Endif
		Else
			fclose(stream);
			return -errno;
		Endif
	Else
		return -errno;
	Endif
}

LOCAL int DMP_Write(USR_LONG address, USR_LONG size, void * buffer)
{  FILE * stream;
	int nwrite;

	if (size == 0) return USR_NO_ERROR;
	If ((stream = fopen(DmpFile, "rb+")) != NULL) Then
		If (fseek(stream, address, SEEK_SET) == 0) Then
			nwrite = fwrite(buffer, (int)size, 1, stream);
			If (nwrite == 1) Then
				fclose(stream);
				return USR_NO_ERROR;
			Else
				fclose(stream);
				return -errno;
			Endif
		Else
			fclose(stream);
			return -errno;
		Endif
	Else
		return -errno;
	Endif
}

LOCAL int DMP_Exit()
{
	return USR_NO_ERROR;
}

LOCAL const IO_MODULE DmpIoModule =
{  DMP_Init,
	DMP_Check,
	DMP_Read,
	DMP_Write,
	DMP_Exit
};

GLOBAL const IO_MODULE * DMP_Module()
{
	return &DmpIoModule;
}

