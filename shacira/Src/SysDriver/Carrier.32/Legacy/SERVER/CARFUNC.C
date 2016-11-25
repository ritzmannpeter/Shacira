/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     CARFUNC
*
*  BESCHREIBUNG:
*     Wurzelfunktionalitaet fuer DOS-Programm, 16- und 32-Bit DLL.#
*
*  UMGEBUNG:
*     ZIELRECHNER:           PC-AT
*     ENTWICKLUNGSRECHNER:   PC-AT
*     UEBERSETZER:
*     OPTIONEN:
*
*  VERSION:
*     VERSION:    1.00                      DATUM:   28.02.00
*     AUTOR(EN):                            TELEFON: (0761) 45205-0
*
*  HISTORY:
*     28.02.00 -PR- Implementiert aus cardll.c.
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
#ifndef __stdarg__
#include <stdarg.h>
#define __stdarg__
#endif
#ifndef __files__
#include <files.h>
#define __files__
#endif
#ifndef __errcode__
#include <errcode.h>
#define __errcode__
#endif
#ifndef __errno__
#include <errno.h>
#define __errno__
#endif
#ifndef __debug__
#include <debug.h>
#define __debug__
#endif
#ifndef __service__
#include <service.h>
#define __service__
#endif
#ifndef __basicio__
#include <basicio.h>
#define __basicio__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __carfunc__
#include <carfunc.h>
#define __carfunc__
#endif
/***************************************************************************/

LOCAL char Output[OUTPUT_SIZE];
LOCAL char * OutPtr = NULL;

LOCAL char Args[10][128] = {0};
LOCAL char * Argv[10] =
{
  Args[0],
  Args[1],
  Args[2],
  Args[3],
  Args[4],
  Args[5],
  Args[6],
  Args[7],
  Args[8],
  Args[9]
};

LOCAL int OutPrintf(char * format,...)
{  char text[256];

   va_list ap;
   va_start(ap, format);
   vsprintf(text, format, ap);
	OutPtr += sprintf(OutPtr,"%s", text);
	va_end(ap);

   return USR_NO_ERROR;
}

LOCAL char ErrcodeString[128];
LOCAL char * ErrString(int err)
{  
   Switch(err)
   Case EAGAIN:
//   Case DCAR_BAD_TYP:
//   Case DCAR_VERIFY_ERROR:
//   Case DCAR_NO_EEPROM:
   Case DCAR_NOT_READY:
      sprintf(ErrcodeString, "DISK_VERS_UNDEF");
      break;
   Case ENODEV:
   Case DCAR_NOT_FOUND:
      sprintf(ErrcodeString, "DCAR_NOT_FOUND");
      break;
   Case ERR_CAR_WRONG_FORMAT:
   Case ERR_INVALID_DISKID:
	Case ERR_INVALID_SPINFO:
   Case FMT2_INVALID_PROGLEN:
   Case FMT2_CHECKSUM:
   Case FMT2_CHECKSUM1:
   Case FMT2_CHECKSUM2:
	Case FMT2_CHECKSUM3:
	Case FMT2_INVALID_PROCNO:
   Case FMT2_INVALID_VERSION:
   Case FX25_INVALID_PROGLEN:
   Case FX25_CHECKSUM:
   Case FX25_CHECKSUM1:
   Case FX25_CHECKSUM2:
   Case FX25_CHECKSUM3:
   Case FX25_INVALID_HEADERLEN:
   Case FMT1_INVALID_PROGLEN:
   Case FMT1_CHECKSUM:
   Case FMT1_CHECKSUM1:
   Case FMT1_CHECKSUM2:
   Case FMT1_CHECKSUM3:
   Case FMT1_INVALID_HEADERLEN:
   Case FMFAT_INVALID_HEADERLEN:
      sprintf(ErrcodeString, "DISK_VERS_UNKNOWN");
      break;
   Case ENOSPC:
      sprintf(ErrcodeString, "DISK_ERR_DISK_FULL");
      break;
   Default:
      if (err > 0) err = -err;
		sprintf(ErrcodeString, "Error: %d", err);
      break;
   Endswitch
   return ErrcodeString;
}

LOCAL void PrintFormat(int format)
{
   Switch(format)
   Case FMFAT: OutPrintf("DISK_VERS_STD\n"); return;
   Case FMT2: OutPrintf("DISK_VERS_OLD\n"); return;
   Case FX25: OutPrintf("DISK_VERS_OLD_FX\n"); return;
   Case FMT1: OutPrintf("DISK_VERS_OLD_FMT1\n"); return;
   Default: OutPrintf("UNKNOWN_FORMAT\n"); return;
   Endswitch
}

LOCAL void PrintVersion(int version)
{
   Switch(version)
   Case  UNKNOWN_VERSION: OutPrintf("UNKNOWN_VERSION\n"); return;
   Case  FMFAT_KS: OutPrintf("FMFAT_KS\n"); return;
   Case  FMFAT_KE: OutPrintf("FMFAT_KE\n"); return;
   Case  FMFAT_KDS: OutPrintf("FMFAT_KDS\n"); return;
   Case  FMFAT_KDE: OutPrintf("FMFAT_KDE\n"); return;
   Case  FMFAT_ELEKTRA: OutPrintf("FMFAT_ELEKTRA\n"); return;
   Case  FMFAT_FM: OutPrintf("FMFAT_FM\n"); return;
   Case  FMFAT_FXR: OutPrintf("FMFAT_FXR\n"); return;
	Case  FMFAT_FXA: OutPrintf("FMFAT_FXA\n"); return;
   Case  FMFAT_K0: OutPrintf("FMFAT_K0\n"); return;
   Case  FMFAT_K1: OutPrintf("FMFAT_K1\n"); return;
   Case  FMFAT_K2: OutPrintf("FMFAT_K2\n"); return;
   Case  FMT2_FM: OutPrintf("FMT2_FM\n"); return;
	Case  FMT2_FXP: OutPrintf("FMT2_FXP\n"); return;
	Case  FMT2_FXA: OutPrintf("FMT2_FXA\n"); return;
   Case  FMT2_FM_2F: OutPrintf("FMT2_FM_2F\n"); return;
   Case  FMT2_FM_3F: OutPrintf("FMT2_FM_3F\n"); return;
   Case  FMT2_FXP_2F: OutPrintf("FMT2_FXP_2F\n"); return;
   Case  FMT2_FXA_2F: OutPrintf("FMT2_FXA_2F\n"); return;
   Case  FMT2_GRAPHIC: OutPrintf("FMT2_GRAPHIC\n"); return;
   Case  FX25_FX: OutPrintf("FX25_FX\n"); return;
   Case  FMT1_FM: OutPrintf("FMT1_FM\n"); return;
   Case  ARBURG_C: OutPrintf("ARBURG_C\n"); return;
   Default: OutPrintf("UNKNOWN_VERSION %d\n", version); return;
	Endswitch
}

LOCAL int MainFunc(int argc, char **argv)
{  int err = USR_NO_ERROR, return_value = USR_NO_ERROR;
	DRIVE_INFO driveinfo;
	FILE_INFO fileinfo;
	int param = 0;

	memset(&driveinfo, 0, sizeof(DRIVE_INFO));
	memset(&fileinfo, 0, sizeof(FILE_INFO));
	If (argc < 3 || '?' == argv[1][0]) Then
		return 0;
	Endif
	setbuf(stdout, NULL);
	If (0 == strcmp("DEBUG", argv[1])) Then
		SetDebugMode(DEBUG_DEVICES|VERBOSE|FAILURES, NULL);
		BASIC_Init(CARRIER_IO, 15, NULL);
	Elseif (0 == strcmp("DEVICE", argv[1])) Then
		SetDebugMode(0, NULL);
		BASIC_Init(CARRIER_IO, 15, NULL);
	Else
		BASIC_Init(DUMP_IO, 0, argv[1]);
		SetDebugMode(VERBOSE|FAILURES, NULL);
   Endif
   CAR_InitCarrier();

   If (0 == strcmp("-format", argv[2])) Then
		int format = 0;
      If (argc <= 3) Then
         format = 0;
      Else
         If (strcmp(argv[3],"grau")==0) Then
            format = FMFAT;
         Elseif (strcmp(argv[3],"FMT2")==0) Then
            format = FMT2;
         Elseif (strcmp(argv[3],"FX25")==0) Then
				format = FX25;
         Elseif (strcmp(argv[3],"FMT1")==0) Then
            format = FMT1;
			Endif
      Endif
      err = CAR_FormatCarrier(format,param);
      Cdriveinfo(&driveinfo, 1);
      If (err != USR_NO_ERROR) Then
			OutPrintf("%s\n", ErrString(err));
		Else
			PrintFormat(driveinfo.format);
      Endif
   Elseif (0 == strcmp("-dir", argv[2])) Then
      err = CAR_DirCarrier();
		Cdriveinfo(&driveinfo, 0);
      If (err < USR_NO_ERROR) Then
         OutPrintf("%s\n", ErrString(err));
      Else
         PrintFormat(driveinfo.format);
		Endif
   Elseif (0 == strcmp("-add", argv[2])) Then
      If ((err = Cdriveinfo(&driveinfo, 1)) == 0) Then
         If ((err = CAR_FileInfo(argv[3], &fileinfo)) == USR_NO_ERROR) Then
            If (fileinfo.format == driveinfo.format) Then
					If (driveinfo.format == FMT2 && fileinfo.version != driveinfo.version) Then
						OutPrintf("FORMAT_MISMATCH\n");
					Else
						If ((err = CAR_SaveFile(argv[3], driveinfo.format)) == USR_NO_ERROR) Then
							PrintFormat(driveinfo.format);
						Else
							OutPrintf("%s\n", ErrString(err));
						Endif
					Endif
				Else
					OutPrintf("FORMAT_MISMATCH\n");
				Endif
			Else
				OutPrintf("%s\n", ErrString(err));
			Endif
		Else
			OutPrintf("%s\n", ErrString(errno));
		Endif
	Elseif (0 == strncmp("-extract", argv[2], 4)) Then
		err = CAR_RestoreFile(argv[3]);
		Cdriveinfo(&driveinfo, 0);
		If (err != USR_NO_ERROR) Then
			OutPrintf("%s\n", ErrString(err));
		Else
			PrintFormat(driveinfo.format);
		Endif
	Elseif (0 == strncmp("-exall", argv[2], 4)) Then
		If (argc == 4) Then
			err = CAR_RestoreAllFiles(argv[3]);
		Elseif (argc == 3) Then
			err = CAR_RestoreAllFiles(NULL);
		Endif
		Cdriveinfo(&driveinfo, 0);
		If (err != USR_NO_ERROR) Then
			OutPrintf("%s\n", ErrString(err));
		Else
			PrintFormat(driveinfo.format);
		Endif
	Elseif (0 == strncmp("-check", argv[2], 4)) Then
		memset(&driveinfo, 0, sizeof(DRIVE_INFO));
		If ((err = Cdriveinfo(&driveinfo, 1)) == 0) Then
			PrintFormat(driveinfo.format);
		Else
			If (driveinfo.format > 0) Then
				PrintFormat(driveinfo.format);
			Else
				If (driveinfo.size == 32 || driveinfo.size == 64) Then
					PrintFormat(FMFAT);
				Else
					OutPrintf("%s\n", ErrString(errno));
				Endif
			Endif
		Endif
	Elseif (0 == strncmp("-delall", argv[2], 5)) Then
		err = CAR_RemoveAllFiles();
		Cdriveinfo(&driveinfo, 1);
		If (err != USR_NO_ERROR) Then
			OutPrintf("%s\n", ErrString(err));
		Else
			PrintFormat(driveinfo.format);
		Endif
	Elseif (0 == strcmp("-delete", argv[2])) Then
		err = CAR_RemoveFile(argv[3]);
		Cdriveinfo(&driveinfo, 1);
		If (err != USR_NO_ERROR) Then
			OutPrintf("%s\n", ErrString(err));
		Else
			PrintFormat(driveinfo.format);
		Endif
	Elseif (0 == strcmp("-info", argv[2])) Then
		err = CAR_FileInfo(argv[3], &fileinfo);
		If (err != USR_NO_ERROR) Then
			OutPrintf("%s\n", ErrString(err));
		Else
			PrintFormat(fileinfo.format);
			PrintVersion(fileinfo.version);
		Endif
	Else
		return_value = -1;
	Endif
	BASIC_Exit();
	OutPrintf("Size: %d\n", driveinfo.size);
	return return_value;
}

GLOBAL int _Carrier(char * input, char * output)
{  int err;
	int argc;

	memset(Output, 0, sizeof(Output));
	OutPtr = Output;
	argc = sscanf(input, "%s %s %s %s %s %s %s %s %s %s",
					  Argv[0],
					  Argv[1],
					  Argv[2],
					  Argv[3],
					  Argv[4],
					  Argv[5],
					  Argv[6],
					  Argv[7],
					  Argv[8],
					  Argv[9]);
	err = MainFunc(argc, Argv);
	memcpy(output, Output, strlen(Output) + 1);
	return err;
}

GLOBAL int _CARRIER_FileInfo(char * path, FILE_INFO * file_info)
{
	return CAR_FileInfo(path, file_info);
}

GLOBAL int _CARRIER_SetTime(char * path)
{
   return CAR_SetTime(path);
}

GLOBAL int _CARRIER_SetRegVal(char * path, long regid, int index, long value)
{
   return CAR_SetRegVal(path, regid, index, value);
}

GLOBAL int _CARRIER_GetRegVal(char * path, long regid, int index, long * value)
{
   return CAR_GetRegVal(path, regid, index, value);
}

GLOBAL int _CARRIER_SetData(char * path, char * artno, char * matno, char * toolno)
{
   return CAR_SetData(path, artno, matno, toolno);
}

GLOBAL TransformInput(char * input, int argc, char ** argv)
{

}
