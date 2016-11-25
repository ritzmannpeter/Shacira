/*.sm.***********************************************************************
*
*  MODULE-NAME:
*     FMFAT
*
*  BESCHREIBUNG:
*     Ferromatik FAT-Zugriffsfunktionen.
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
*     18.03.96  -PR- Implementierung.
*     12.12.96  -PR- FileInfo-Funktion ueber Datenanalyse verfeinert.
*     17.12.97  -PR- Logging zur Suche des Alloc-Problems bei Widia eingebaut.
*     01.07.98  -PR- Logging inaktiviert.
*     12.03.99  -PR- Auf Jahr 2000-Faehigkeit ueberprueft und angepasst.
*     07.06.99  -PR- Zwei ELEKTRA-Versionen E1 (bis 1.08) und E2 (ab 1.08)
*                    eingebaut.
*     26.10.00  -PR- Maximale Header-Groesse auf 252 Byte erweitert.
*                    Repairfunktionalitaet entfernt.
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
*      FMFAT_Module
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
#ifndef __iqtdev__
#include <iqtdev.h>
#define __iqtdev__
#endif
#ifndef __devdisk__
#include <devdisk.h>
#define __devdisk__
#endif
#ifndef __fmfat__
#include <fmfat.h>
#define __fmfat__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __service__
#include <service.h>
#define __service__
#endif
/***************************************************************************/

#define DRIVE_NO     DISK_DRV_EEP1

#define MIN_HEADER_LEN	78
#define MAX_HEADER_LEN	252

USR_LONG DiskGetTimeDate ( )
{  struct tm * act_time = NULL;
	time_t now;
	int year, day, month, hour, sec, min;

	time(&now);
	act_time = localtime(&now);
	year = act_time->tm_year;
	month = act_time->tm_mon + 1;
	day = act_time->tm_mday;
	hour = act_time->tm_hour;
	min = act_time->tm_min;
	sec = act_time->tm_sec;
   return DISK_MAKE_DATE(day, month, year, hour, min, sec);
}  /* DiskGetTimeDate */

LOCAL int DeviceError(int hnd)
{  PARAMETER device_error;
   DevGetParam(hnd, DEV_ID_ERROR, &device_error);
   return (int)device_error;
}

LOCAL USR_HANDLE FMFAT_OpenFile(USR_WORD flags, char * filename)
{  USR_HANDLE hnd;
   int err;
   PARAMETER dev_mode = 0L;
   DISK_PARAM_BLOCK  param;

   if (flags & _WRITE) dev_mode |= (PARAMETER)DISK_OP_WRITE | (PARAMETER)DISK_OP_CREATE;
   if (flags & _READ) dev_mode |= (PARAMETER)DISK_OP_READ;
   param.Date = (PARAMETER) DiskGetTimeDate();
   param.Drive = (PARAMETER) DRIVE_NO;
   param.Mode = dev_mode;
   param.FileName = filename;
   If ((err = DevOpen(&hnd, DEV_DISK, &param)) == DEV_ERROR) Then
      return DeviceError(hnd);
   Else
      return hnd;
   Endif
}

LOCAL int FMFAT_CloseFile(int hnd)
{  int err;
   If ((err = DevClose(hnd)) == USR_NO_ERROR) Then
      return USR_NO_ERROR;
	Else
      return DeviceError(hnd);
   Endif
}

LOCAL int FMFAT_ReadFile(int hnd, void * buf, int size)
{  int err = DevRead(hnd, buf, size, NULL, 0);
   If (err == USR_NO_ERROR) Then
      return USR_NO_ERROR;
   Else
      return DeviceError(hnd);
   Endif
}

LOCAL int FMFAT_WriteFile(int hnd, void * buf, int size)
{  int err;
   If ((err = DevWrite(hnd, buf, size, NULL, 0)) != USR_NO_ERROR) Then
      return DeviceError(hnd);
   Else
      return USR_NO_ERROR;
   Endif
}

LOCAL long FMFAT_GetSize(int hnd)
{  int err;
   PARAMETER file_size;
   If ((err = DevGetParam(hnd, DISK_ID_SIZE, (PARAMETER*)&file_size)) != USR_NO_ERROR) Then
      return (long)DeviceError(hnd);
	Else
      return (long)file_size;
   Endif
}

LOCAL long FMFAT_GetPos(int hnd)
{  int err;
   PARAMETER file_pos;
   If ((err = DevGetParam(hnd, DISK_ID_FILEPOS, (PARAMETER*)&file_pos)) != USR_NO_ERROR) Then
      return (long)DeviceError(hnd);
   Else
      return (long)file_pos;
   Endif
}

LOCAL int FMFAT_SetPos(int hnd, long pos)
{  int err;
   If ((err = DevSetParam(hnd, DISK_ID_FILEPOS, (PARAMETER)pos)) != USR_NO_ERROR) Then
      return DeviceError(hnd);
   Else
      return USR_NO_ERROR;
   Endif
}

LOCAL int FMFAT_RemoveFile(char *__filename)
{  int err;
   USR_HANDLE hnd;
   DISK_PARAM_BLOCK  param;
	param.Drive = (PARAMETER) DRIVE_NO;
   param.Mode = DISK_OP_DELETE;
   param.FileName = __filename;
   If ((err = DevOpen(&hnd, DEV_DISK, &param)) != USR_NO_ERROR) Then
		return DeviceError(hnd);
   Else
      DevClose(hnd);
      return USR_NO_ERROR;
   Endif
}

LOCAL int FMFAT_Directory(DIR ** dir)
{  int err, i;
   int dir_entries;
   DISK_PARAM_BLOCK param;
   USR_HANDLE hnd = 0;
   PARAMETER size = 0L;
   DISK_DIR_STRUCT * dev_dir;
   param.Drive    = (PARAMETER)DRIVE_NO;
   param.Mode     = DISK_OP_READ;
   param.FileName = NULL;
   If ((err = DevOpen(&hnd, DEV_DISK, &param)) != USR_NO_ERROR) Then
      return DeviceError(hnd);
   Endif
   If ((err = DevGetParam(hnd, DISK_ID_SIZE, &size)) != USR_NO_ERROR) Then
      err = DeviceError(hnd);
      DevClose(hnd);
      return err;
	Endif
   If (size == 0L) Then
      DevClose(hnd);
      return 0;
	Endif
      
   dir_entries = (USR_WORD)(size / sizeof(DISK_DIR_STRUCT));

   dev_dir = malloc((USR_WORD)size);
   If (dev_dir == NULL) Then
      DevClose(hnd);
      return ERR_DRAM_ALLOC;
   Else
      memset(dev_dir, 0, size);
   Endif

   If ((err = DevSetParam(hnd, DISK_ID_FILEPOS , 0L)) != USR_NO_ERROR) Then
      err = DeviceError(hnd);
      free(dev_dir);
      return err;
   Endif
   If ((err = DevRead(hnd, (char*)dev_dir, (int)size, NULL, (TIME)0)) != USR_NO_ERROR) Then
      err = DeviceError(hnd);
      free(dev_dir);
      return err;
   Else
      DevClose(hnd);
   Endif

   *dir = (DIR*)malloc(dir_entries * sizeof(DIR));
   If (*dir == NULL) Then
      free(dev_dir);
		return ERR_DRAM_ALLOC;
   Else
      memset(*dir, 0, dir_entries * sizeof(DIR));
   Endif

   For (i=0; i<dir_entries; i++) Do
      sprintf((*dir)[i].d_name, "%s", dev_dir[i].FileName);
      (*dir)[i].d_size = dev_dir[i].Size;
   Endfor
   free(dev_dir);
   return dir_entries;
}

LOCAL int FMFAT_Format(int param)
{  USR_HANDLE hnd;
   DISK_PARAM_BLOCK param_block;
   int err;
   
   param_block.Drive = (PARAMETER)DRIVE_NO;
   param_block.Mode = DISK_OP_DELETE;
   param_block.FileName = NULL;
   If ((err = DevOpen(&hnd, DEV_DISK, &param_block)) != USR_NO_ERROR) Then
      return DeviceError(hnd);
   Else
		If ((err = DevClose(hnd)) != USR_NO_ERROR) Then
         return DeviceError(hnd);
      Else
         return USR_NO_ERROR;
		Endif
   Endif
}

LOCAL int FMFAT_Init()
{  DISK_INIT_BLOCK disk_init_block;
   disk_init_block.DebugMask = 0;

   DevInit(DEV_MAIN, NULL);
   DevInit(DEV_DISK, &disk_init_block);
   return USR_NO_ERROR;
}

LOCAL int FMFAT_DriveInfo(DRIVE_INFO * driveinfo)
{  DIR * dir = NULL;
   int dir_entries;

   dir_entries = FMFAT_Directory(&dir);
   If (dir_entries < 0) Then
      if (dir != NULL) free(dir);
      return dir_entries;
   Else
      if (dir != NULL) free(dir);
      driveinfo->format = FMFAT;
		driveinfo->version = 0;
      driveinfo->module = FMFAT_Module();
      return USR_NO_ERROR;
   Endif
}

extern int FMFAT_FileInfo(char * path, FILE_INFO * fileinfo);

LOCAL const DRIVE_MODULE FMFAT_DriveModule =
{  FMFAT_OpenFile,
   FMFAT_CloseFile,
   FMFAT_ReadFile,
   FMFAT_WriteFile,
   FMFAT_GetSize,
   FMFAT_GetPos,
   FMFAT_SetPos,
   FMFAT_RemoveFile,
   FMFAT_Directory,
   FMFAT_Format,
   FMFAT_Init,
   FMFAT_DriveInfo, 
   FMFAT_FileInfo
};

GLOBAL const DRIVE_MODULE * FMFAT_Module()
{
   return &FMFAT_DriveModule;
}

#include <stdio.h>
#include <stdarg.h>

char _Text[4096];
static int AdHocPrintf(char * fmtstr, ...)
{
	va_list args;
	FILE * stream;

	va_start(args, fmtstr);
	vsprintf(_Text, fmtstr, args);
	va_end(args);
	stream = fopen("fmfat.dbg", "a");
	if (stream != NULL) {
		fprintf(stream, "%s", _Text);
		fclose(stream);
	}
	return 0;
}

LOCAL int AllocFile(char * path, char * mode, FILE_HEADER ** header_ptr, FILE ** stream_ptr)
{  FILE_HEADER * header;
	FILE * stream;
	int version;

	*header_ptr = *stream_ptr = NULL;
	header = (FILE_HEADER*)malloc(sizeof(FILE_HEADER));
	If (header == NULL) Then
		return ERR_DRAM_ALLOC;
	Endif
	If ((stream = fopen(path, mode)) != NULL) Then
		If (fread(header, sizeof(FILE_HEADER), 1, stream) != 1) Then
			fclose(stream);
			free(header);
			return FMFAT_FILE_READ_FAILURE;
		Else
			If (header->HeaderSize < MIN_HEADER_LEN ||
				 header->HeaderSize > MAX_HEADER_LEN) Then
				fclose(stream);
				free(header);
				return FMFAT_INVALID_HEADERLEN;
			Else
				If (CheckSubfileTab(stream, header->HeaderSize) != USR_NO_ERROR) Then
					fclose(stream);
					free(header);
					return FMFAT_SUBFILETAB_CORRUPTED;
				Else
					If ((version = FmfatVersion(header, stream)) < 0) Then
						fclose(stream);
						free(header);
					Else
						*header_ptr = header;
						*stream_ptr = stream;
					Endif
					return version;
				Endif
			Endif
		Endif
	Else
		return FMFAT_FILE_OPEN_FAILURE;
	Endif
}

LOCAL int FreeFile(FILE_HEADER * header, FILE * stream, USR_BOOL touch)
{  int err;

	If (touch) Then
		header->Date = DiskGetTimeDate();
		If (fseek(stream, 0L, SEEK_SET) == 0) Then
         If (fwrite(header, header->HeaderSize, 1, stream) == 1) Then
            err = USR_NO_ERROR;
         Else
            err = FMFAT_FILE_WRITE_FAILURE;
         Endif
      Else
         err = FMFAT_FILE_SEEK_ERROR;
      Endif
	Else
      err = USR_NO_ERROR;
   Endif
   fclose(stream);
	free(header);
	return err;
}

typedef struct
{  unsigned_16 id;
   signed_32 offset;
}  SUBFILE_TYPE;
#define MAX_SUBFILES   20

LOCAL long SubFilePos(FILE_HEADER * header, FILE * stream, unsigned_8 id)
{  unsigned_16 subfile_tab_id;
   signed_16 subfiles;
   SUBFILE_TYPE * subfile_tab, * sft_ptr;
   long subfile_pos = FMFAT_SUBFILETAB_MISSING;
   int i;

   If (fseek(stream, header->HeaderSize, SEEK_SET) == 0) Then
      if (fread(&subfile_tab_id, sizeof(subfile_tab_id), 1, stream) != 1)
         return FMFAT_FILE_READ_ERROR;
      if (subfile_tab_id != DISK_ID_PTRTAB) return FMFAT_SUBFILETAB_MISSING;
      if (fread(&subfiles, sizeof(subfiles), 1, stream) != 1)
         return FMFAT_FILE_READ_ERROR;
      if (subfiles < 0 || subfiles > MAX_SUBFILES) return FMFAT_SUBFILETAB_MISSING;
		If ((subfile_tab = malloc(subfiles * sizeof(SUBFILE_TYPE))) == NULL) Then
         return ERR_DRAM_ALLOC;
      Endif
      If (fread(subfile_tab, subfiles * sizeof(SUBFILE_TYPE), 1, stream) == 1) Then
			For (i=0, sft_ptr = subfile_tab;
              i<subfiles && sft_ptr->id != id;
              i++, sft_ptr++) Do
         Endfor
         if (sft_ptr->id == id) subfile_pos = sft_ptr->offset;
		Endif
      free(subfile_tab);
      return subfile_pos;
	Else
      return FMFAT_FILE_SEEK_ERROR;
   Endif
}

LOCAL int CheckSubfileTab(FILE * stream, int header_size)
{  unsigned_16 subfile_tab_id;
	unsigned_16 subfile_id;
	signed_16 subfiles;
   SUBFILE_TYPE * subfile_tab, * sft_ptr;
   int i;

   If (fseek(stream, header_size, SEEK_SET) == 0) Then
      If (fread(&subfile_tab_id, sizeof(subfile_tab_id), 1, stream) != 1) Then
         return FMFAT_SUBFILETAB_READ_FAILED;
      Endif
		If (subfile_tab_id != DISK_ID_PTRTAB) Then
         return FMFAT_SUBFILETAB_MISSING;
      Endif
      If (fread(&subfiles, sizeof(subfiles), 1, stream) != 1) Then
			return FMFAT_SUBFILETAB_READ_FAILED;
      Endif
      if (subfiles < 0 || subfiles > MAX_SUBFILES) return FMFAT_SUBFILETAB_MISSING;
      If ((subfile_tab = malloc(subfiles * sizeof(SUBFILE_TYPE))) == NULL) Then
         return ERR_DRAM_ALLOC;
		Endif
      If (fread(subfile_tab, subfiles * sizeof(SUBFILE_TYPE), 1, stream) == 1) Then
         For (i=0, sft_ptr = subfile_tab;
				  i<subfiles;
              i++, sft_ptr++) Do
            If (fseek(stream, sft_ptr->offset, SEEK_SET) == 0) Then
               If (fread(&subfile_id, sizeof(subfile_id), 1, stream) != 1) Then
                   return FMFAT_SUBFILETAB_READ_FAILED;
               Else
                  If (subfile_id != sft_ptr->id) Then
                      return FMFAT_INCONSISTENT_SUBFILE_ID;
                  Endif
               Endif
            Else
               return FMFAT_FILE_SEEK_ERROR;
            Endif
         Endfor
      Endif
      free(subfile_tab);
		return USR_NO_ERROR;
   Else
      return FMFAT_FILE_SEEK_ERROR;
   Endif
}

/*********************************************************************
*  FUNKTION: DeCompressText
*     Einen Text wiederherstellen.
*********************************************************************/

LOCAL int DeCompressText(USR_BYTE * Text, USR_BYTE * CompText, int Length)
{  int  i=0,j=0;
   USR_BYTE Count;

   While ( i<Length ) Do
      If ( (CompText[i] & 0x80) == 0x80 ) Then
         /* Zeichen kommt mehrmals vor */
         For ( Count=CompText[i+1] ; Count > 0 ; Count-- ) Do
            Text[j++] = CompText[i] & 0x7f;     /* - 128 */
         Endfor
         i += 2;
      Else
         Text[j++] = CompText[i++];
		Endif
	Endwhile
	return j;
}  /* DeCompressText */

#define MAX_TEXT_BUF_SIZE 2000

typedef struct
{  unsigned_16 id;
	unsigned_8 cols;
	unsigned_8 rows;
	unsigned_16 length;
}  TEXT_IDENT;

LOCAL int ReadTextVar(FILE_HEADER * header, FILE * stream, int text_id,
							 char * buffer, int len)
{  long subfile_pos = SubFilePos(header, stream, DISK_ID_SETUP_TEXT);
	unsigned_16 subfile_id;
	signed_16 text_len;
	char * text_buf, * comp_text_buf;
	TEXT_IDENT text_ident;
	int text_size;

	If (subfile_pos < header->HeaderSize) Then
		sprintf(buffer, "$E%d", FMFAT_INVALID_SUBFILE_POSITION);
		return FMFAT_INVALID_SUBFILE_POSITION;
	Endif
	If (fseek(stream, subfile_pos, SEEK_SET) == 0) Then
		If (fread(&subfile_id, sizeof(subfile_id), 1, stream) != 1) Then
			sprintf(buffer, "$E%d", FMFAT_FILE_READ_ERROR);
			return FMFAT_FILE_READ_ERROR;
		Endif
		If (subfile_id != DISK_ID_SETUP_TEXT) Then
			sprintf(buffer, "$E%d", FMFAT_INCONSISTENT_SUBFILE_ID);
			return FMFAT_INCONSISTENT_SUBFILE_ID;
		Endif
		If ((text_buf = malloc(MAX_TEXT_BUF_SIZE)) == NULL) Then
			sprintf(buffer, "$E%d", ERR_DRAM_ALLOC);
			return ERR_DRAM_ALLOC;
		Endif
		If ((comp_text_buf = malloc(MAX_TEXT_BUF_SIZE)) == NULL) Then
			free(text_buf);
			sprintf(buffer, "$E%d", ERR_DRAM_ALLOC);
			return ERR_DRAM_ALLOC;
		Endif
		Repeat
			If (fread(&text_ident, sizeof(text_ident), 1, stream) != 1) Then
				free(text_buf);
				free(comp_text_buf);
				sprintf(buffer, "$E%d", FMFAT_FILE_READ_ERROR);
				return FMFAT_FILE_READ_ERROR;
			Else
				If (text_ident.id != DISK_ID_END) Then
					If (text_ident.id == text_id) Then
						text_size = text_ident.cols * text_ident.rows;
						If (text_size <= 0 || text_size > MAX_TEXT_BUF_SIZE) Then
							free(text_buf);
							free(comp_text_buf);
							sprintf(buffer, "$E%d", FMFAT_INVALID_TEXT_SIZE);
							return FMFAT_INVALID_TEXT_SIZE;
						Endif
						If (fread(comp_text_buf, text_ident.length, 1, stream) != 1) Then
							free(text_buf);
							free(comp_text_buf);
							sprintf(buffer, "$E%d", FMFAT_FILE_READ_ERROR);
							return FMFAT_FILE_READ_ERROR;
						Endif
						text_len = DeCompressText(text_buf, comp_text_buf, text_ident.length);
						If (text_len > len) Then
							memcpy(buffer, text_buf, len);
							buffer[len-1] = '\0';
						Else
							memcpy(buffer, text_buf, text_len);
							buffer[text_len] = '\0';
						Endif
						free(text_buf);
						free(comp_text_buf);
						return USR_NO_ERROR;
					Else
						If (fseek(stream, text_ident.length, SEEK_CUR) != 0) Then
							sprintf(buffer, "$E%d", FMFAT_FILE_SEEK_ERROR);
							return FMFAT_FILE_SEEK_ERROR;
						Endif
					Endif
				Endif
			Endif
		Until (text_ident.id == DISK_ID_END);
		free(text_buf);
		free(comp_text_buf);
		return FMFAT_TEXTVAR_NOT_FOUND;
	Else
		sprintf(buffer, "$E%d", FMFAT_FILE_SEEK_ERROR);
		return FMFAT_FILE_SEEK_ERROR;
	Endif
}

LOCAL int WriteTextVar(FILE_HEADER * header, FILE * stream, int text_id,
							  char * buffer, int len)
{  long subfile_pos = SubFilePos(header, stream, DISK_ID_SETUP_TEXT);
   int err;
	unsigned_16 subfile_id;
   char * text_buf;
   TEXT_IDENT text_ident;
   int text_size;

   if (subfile_pos < header->HeaderSize) return FMFAT_INVALID_SUBFILE_POSITION;
   If (fseek(stream, subfile_pos, SEEK_SET) == 0) Then
      if (fread(&subfile_id, sizeof(subfile_id), 1, stream) != 1)
         return FMFAT_FILE_READ_ERROR;
      if (subfile_id != DISK_ID_SETUP_TEXT)
         return FMFAT_INCONSISTENT_SUBFILE_ID;
      Repeat 
         If (fread(&text_ident, sizeof(text_ident), 1, stream) != 1) Then
            return FMFAT_FILE_READ_ERROR;
         Else
            If (text_ident.id != DISK_ID_END) Then
					If (text_ident.id == text_id) Then
                  text_size = text_ident.cols * text_ident.rows;
                  if (text_size <= 0 || text_size > MAX_TEXT_BUF_SIZE)
                     return FMFAT_INVALID_TEXT_SIZE;
                  if (text_ident.length < text_size) text_size = text_ident.length;
                  If ((text_buf = malloc(text_size + 1)) == NULL) Then
                     return ERR_DRAM_ALLOC;
                  Endif
                  memset(text_buf, ' ', text_size);
						if (len > text_size) len = text_size;
                  memcpy(text_buf, buffer, len);
                  If (fseek(stream, ftell(stream), SEEK_SET) == 0) Then
							If (fwrite(text_buf, text_size, 1, stream) == 1) Then
                        err = USR_NO_ERROR;
                     Else
                        err = FMFAT_FILE_WRITE_FAILURE;
                     Endif
                  Else
                     err = FMFAT_FILE_SEEK_ERROR;
                  Endif
                  free(text_buf); 
                  return err;
               Else
                  If (fseek(stream, text_ident.length, SEEK_CUR) != 0) Then
                     return FMFAT_FILE_SEEK_ERROR;
                  Endif
               Endif
            Endif
			Endif
      Until (text_ident.id == DISK_ID_END);
      return USR_NO_ERROR;
   Else
      return FMFAT_FILE_SEEK_ERROR;
   Endif
}

typedef struct
{  char * vstring;
   int reg_no;
   int version;
}  FMFAT_VERSION;

#define XSTKULM                 3422
#define XSRSSVOR_1              5224
#define XSRSVVOR_1              5226
#define TEXTVAR_ART             6

LOCAL const FMFAT_VERSION FMFATVersions[] =
{  {"FM", 0, FMFAT_FM},
   {"FXR", 0, FMFAT_FXR},
   {"FXA", 0, FMFAT_FXA},
   {"K", XSTKULM, FMFAT_K0},
   {"K", XSRSSVOR_1, FMFAT_K2},
   {"K", -XSTKULM, FMFAT_K1},
   {"E", XSTKULM, FMFAT_E0},
   {"E", XSRSVVOR_1, FMFAT_E1},
	{"E", -XSRSVVOR_1, FMFAT_E2},
   {"E", 0, FMFAT_E2}
};

#define FMFAT_VERSION_ENTRIES    (sizeof(FMFATVersions) / sizeof(FMFAT_VERSION))

LOCAL int SubFileId(int reg_no)
{  
   If (reg_no < START_ISCOS_REGS) Then
		return DISK_ID_ISCOSBIT;
   Elseif ( reg_no < START_IQT_REGS ) Then
      return DISK_ID_ISCOSREG;
	Else
      return DISK_ID_IQTREG;
   Endif
}

LOCAL int RegSize(unsigned_8 reg_type, int * value_size)
{  reg_type = (int)GET_REG_TYPE(reg_type);
   Switch(reg_type)
   Case REG_INT: *value_size = 2; return 2;
   Case REG_DINT: *value_size = 4; return 4;
   Case REG_LONG: *value_size = 4; return 4;
   Case REG_INT10: *value_size = 2; return 20;
   Case REG_INT20: *value_size = 2; return 40;
   Case REG_LONG10: *value_size = 4; return 40;
   Case REG_LONG20: *value_size = 4; return 80;
   Default: *value_size = 0; return 0;
	Endswitch
}

#define MAX_REG_BUF_SIZE        80
LOCAL USR_BOOL RegExist(FILE_HEADER * header, FILE * stream, int reg_no)
{  unsigned_16 subfile_id = SubFileId(reg_no), id;
	long subfile_pos = SubFilePos(header, stream, subfile_id);
	unsigned_16 act_reg_no;
	unsigned_8 reg_type;
	int value_size, size;
	char * buffer;

	if (subfile_pos < header->HeaderSize) return FALSE;
	If (fseek(stream, subfile_pos, SEEK_SET) == 0) Then
		if (fread(&id, sizeof(id), 1, stream) != 1) return FALSE;
		if (id != subfile_id) return FALSE;
		if (fread(&act_reg_no, sizeof(act_reg_no), 1, stream) != 1) return FALSE;
		If ((buffer = malloc(MAX_REG_BUF_SIZE)) == NULL) Then
			return FALSE;
		Endif
		While (act_reg_no != DISK_ID_END && act_reg_no != reg_no) Do
         If (act_reg_no >= START_ISCOS_REGS) Then
            if (fread(&reg_type, sizeof(reg_type), 1, stream) != 1) return FALSE;
            size = RegSize(reg_type, &value_size);
         Else
            size = 1;
            value_size = 1;
         Endif
			If (size == 0 ||
             size > MAX_REG_BUF_SIZE ||
             fread(buffer, size, 1, stream) != 1) Then
            free(buffer);
            return FALSE;
         Endif
         If (fread(&act_reg_no, sizeof(act_reg_no), 1, stream) != 1) Then
            free(buffer);
            return FALSE;
			Endif
      Endwhile
      free(buffer);
		If (act_reg_no == reg_no) Then
         return TRUE;
      Else
         return FALSE;
      Endif
   Else
      return FALSE;
   Endif
}

typedef struct
{  long id;
   int dim;
   int value_size;
   long value_pos;
}  REG_INFO;

LOCAL USR_BOOL RegInfo(FILE_HEADER * header, FILE * stream, int reg_no, REG_INFO * reg_info)
{  unsigned_16 subfile_id = SubFileId(reg_no), id;
   long subfile_pos = SubFilePos(header, stream, subfile_id);
   unsigned_16 act_reg_no;
	unsigned_8 reg_type;
	int value_size, size;
	char * buffer;

	reg_info->id = -1;
	if (subfile_pos < header->HeaderSize) return FALSE;
	If (fseek(stream, subfile_pos, SEEK_SET) == 0) Then
		if (fread(&id, sizeof(id), 1, stream) != 1) return FALSE;
		if (id != subfile_id) return FALSE;
		If ((buffer = malloc(MAX_REG_BUF_SIZE)) == NULL) Then
			return FALSE;
		Endif
		if (fread(&act_reg_no, sizeof(act_reg_no), 1, stream) != 1) return FALSE;
		While (act_reg_no != DISK_ID_END && act_reg_no != reg_no) Do
         If (act_reg_no >= START_ISCOS_REGS) Then
            if (fread(&reg_type, sizeof(reg_type), 1, stream) != 1) return FALSE;
            size = RegSize(reg_type, &value_size);
         Else
            size = 1;
            value_size = 1;
         Endif
         If (size == 0 ||
             size > MAX_REG_BUF_SIZE ||
				 fread(buffer, size, 1, stream) != 1) Then
            free(buffer);
            return FALSE;
         Endif
         If (fread(&act_reg_no, sizeof(act_reg_no), 1, stream) != 1) Then
            free(buffer);
            return FALSE;
         Endif
      Endwhile
		free(buffer);
      If (act_reg_no == reg_no) Then
         If (act_reg_no >= START_ISCOS_REGS) Then
				if (fread(&reg_type, sizeof(reg_type), 1, stream) != 1) return FALSE;
            size = RegSize(reg_type, &value_size);
         Else
            size = 1;
            value_size = 1;
         Endif
         reg_info->id = reg_no;
         reg_info->dim = size / value_size;
         reg_info->value_size = value_size;
         reg_info->value_pos = ftell(stream);
         return TRUE;
      Else
         return FALSE;
      Endif
   Else
		return FALSE;
	Endif
}

LOCAL USR_BOOL RegSubfileOkay(FILE_HEADER * header, FILE * stream, unsigned_16 subfile_id)
{  unsigned_16 id;
	long subfile_pos = SubFilePos(header, stream, subfile_id);
	unsigned_16 act_reg_no = 0, last_reg_no = 0;
	unsigned_8 reg_type;
	int value_size, size;
	char * buffer;

	if (subfile_pos < header->HeaderSize) return FALSE;
	If (fseek(stream, subfile_pos, SEEK_SET) == 0) Then
		if (fread(&id, sizeof(id), 1, stream) != 1) return FALSE;
		if (id != subfile_id) return FALSE;
		If ((buffer = malloc(MAX_REG_BUF_SIZE)) == NULL) Then
			return FALSE;
		Endif

		if (fread(&act_reg_no, sizeof(act_reg_no), 1, stream) != 1) return FALSE;
		While (act_reg_no != DISK_ID_END) Do
			If (act_reg_no >= START_ISCOS_REGS) Then
				if (fread(&reg_type, sizeof(reg_type), 1, stream) != 1)return FALSE;
				size = RegSize(reg_type, &value_size);
			Else
				size = 1;
				value_size = 1;
					  Endif
			If (size == 0 ||
				 size > MAX_REG_BUF_SIZE ||
				 fread(buffer, size, 1, stream) != 1) Then
				free(buffer);
				return FALSE;
			Endif
			If (fread(&act_reg_no, sizeof(act_reg_no), 1, stream) != 1) Then
				free(buffer);
				return FALSE;
			Endif
			If (id == DISK_ID_ISCOSREG && act_reg_no == 19000) Then
				act_reg_no = DISK_ID_END;
			Endif
			last_reg_no = act_reg_no;
		Endwhile
		free(buffer);
		return TRUE;
	Else
		return FALSE;
	Endif
}

LOCAL int FmfatVersion(FILE_HEADER * header, FILE * stream)
{  int i;
	FMFAT_VERSION * fatvers;
	char * versstring;
	char * mashtype;

	For (i=0, fatvers = FMFATVersions; i<FMFAT_VERSION_ENTRIES; i++, fatvers++) Do
		versstring = fatvers->vstring;
		mashtype = header->MashType;
		If (strncmp(fatvers->vstring,
						header->MashType,
						strlen(fatvers->vstring)) == 0) Then
			If (fatvers->reg_no > 0) Then
				if (RegExist(header, stream, fatvers->reg_no)) return fatvers->version;
			Elseif (fatvers->reg_no < 0) Then
				if (!RegExist(header, stream, -(fatvers->reg_no))) return fatvers->version;
			Else
				return fatvers->version;
			Endif
		Endif
	Endfor
	return FMFAT_KS;
}

LOCAL int FMFAT_FileInfo(char * path, FILE_INFO * fileinfo)
{  FILE_HEADER * header;
	int version;
	FILE * stream;

	memset(fileinfo, 0, sizeof(FILE_INFO));
	If ((version = AllocFile(path, "rb", &header, &stream)) > 0) Then
		If (RegSubfileOkay(header, stream, DISK_ID_ISCOSBIT) &&
			 RegSubfileOkay(header, stream, DISK_ID_ISCOSREG) &&
			 RegSubfileOkay(header, stream, DISK_ID_IQTREG)) Then
			fileinfo->day = DISK_GET_DAY(header->Date);
			fileinfo->month = DISK_GET_MONTH(header->Date);
			fileinfo->year = DISK_GET_YEAR(header->Date) + 1900;
			fileinfo->sec = DISK_GET_SEC(header->Date);
			fileinfo->min = DISK_GET_MIN(header->Date);
			fileinfo->hour = DISK_GET_HOUR(header->Date);
			strncpy(fileinfo->matno, header->MatNr, sizeof(header->MatNr));
			strncpy(fileinfo->toolno, header->ToolNr, sizeof(header->ToolNr));
			strncpy(fileinfo->machtype, header->MashType, sizeof(header->MashType));
			ReadTextVar(header, stream, TEXTVAR_ART, fileinfo->artno, ARTNO_SIZE);
			ReadTextVar(header, stream, TEXTVAR_MASHINE, fileinfo->machno, MACHNO_SIZE);
			fileinfo->version = version;
			fileinfo->format = FMFAT;
			return FreeFile(header, stream, FALSE);
		Else
			return FMFAT_CORRUPTED_REG_SUBFILE;
		Endif
	Else
		return version;
	Endif
}

LOCAL int FMFAT_SetTime(char * path)
{  FILE_HEADER * header;
   FILE * stream;
   int version;
   
   If ((version = AllocFile(path, "rb+", &header, &stream)) > 0) Then
      return FreeFile(header, stream, TRUE);
   Else
      return version;
   Endif
}

LOCAL const long AllowedRegs[] =
{  21260, 21261, 21262, 21263, 21264, 21265, 21266, 21267, 21268, 21269,
	21270, 21271
};
#define ALLOWED_REGS    (sizeof(AllowedRegs) / sizeof(AllowedRegs[0]))

LOCAL USR_BOOL RegAllowed(long regid)
{  int i;

   For (i=0; i<ALLOWED_REGS; i++) Do
      if (regid == AllowedRegs[i]) return TRUE;
   Endfor
   return FALSE;
}

LOCAL int FMFAT_SetRegVal(char * path, long regid, int index, long value)
{  FILE_HEADER * header;
   FILE * stream;
   REG_INFO reg_info;
   int version, err;
   
   if (!RegAllowed(regid)) return FMFAT_REG_NOT_ALLOWED;
   If ((version = AllocFile(path, "rb+", &header, &stream)) > 0) Then
      If (RegInfo(header, stream, regid, &reg_info)) Then
         long pos;
         signed_32 l_value = value;
         signed_16 i_value = value;
         signed_8 c_value = value;
         void * buf;
         If (index >= reg_info.dim) Then
            FreeFile(header, stream, TRUE);
            return FMFAT_INVALID_INDEX;
         Endif          
         Switch(reg_info.value_size)
         Case 1:
            pos = reg_info.value_pos + index;
            buf = &c_value;
            break;
         Case 2:
            pos = reg_info.value_pos + (index * 2);
            buf = &i_value;
            break;
         Case 4:
            pos = reg_info.value_pos + (index * 4);
            buf = &l_value;
            break;
         Default:
            FreeFile(header, stream, TRUE);
            return FMFAT_INVALID_REG_VALUESIZE;
         Endswitch
         If (fseek(stream, pos, SEEK_SET) == 0) Then
             If (fwrite(buf, reg_info.value_size, 1, stream) == 1) Then
                err = USR_NO_ERROR;
             Else
                err = FMFAT_FILE_READ_FAILURE;
             Endif
         Else
             err = FMFAT_FILE_SEEK_ERROR;
         Endif
         FreeFile(header, stream, TRUE);
         return err;
      Else
         FreeFile(header, stream, TRUE);
         return FMFAT_REG_NOT_FOUND;
      Endif
   Else
      return version;
   Endif
}

LOCAL int FMFAT_GetRegVal(char * path, long regid, int index, long * value)
{  FILE_HEADER * header;
   FILE * stream;
   REG_INFO reg_info;
   int version, err;
   
   If ((version = AllocFile(path, "rb", &header, &stream)) > 0) Then
      If (RegInfo(header, stream, regid, &reg_info)) Then
         long pos;
         signed_32 l_value;
         signed_16 i_value;
         signed_8 c_value;
         void * buf;
         If (index >= reg_info.dim) Then
            FreeFile(header, stream, FALSE);
            return FMFAT_INVALID_INDEX;
         Endif          
         Switch(reg_info.value_size)
         Case 1:
            pos = reg_info.value_pos + index;
            buf = &c_value;
            break;
         Case 2:
            pos = reg_info.value_pos + (index * 2);
            buf = &i_value;
            break;
         Case 4:
            pos = reg_info.value_pos + (index * 4);
            buf = &l_value;
            break;
         Default:
            FreeFile(header, stream, FALSE);
            return FMFAT_INVALID_REG_VALUESIZE;
         Endswitch
         If (fseek(stream, pos, SEEK_SET) == 0) Then
             If (fread(buf, reg_info.value_size, 1, stream) == 1) Then
                Switch(reg_info.value_size)
                Case 1: *value = (long)c_value; break;
                Case 2: *value = (long)i_value; break;
                Case 4: *value = (long)l_value; break;
                Endswitch
                err = USR_NO_ERROR;
             Else
                err = FMFAT_FILE_READ_FAILURE;
             Endif
         Else
             err = FMFAT_FILE_SEEK_ERROR;
         Endif
         FreeFile(header, stream, FALSE);
         return err;
      Else
         FreeFile(header, stream, FALSE);
         return FMFAT_REG_NOT_FOUND;
      Endif
   Else
      return version;
   Endif
}

LOCAL int FMFAT_GetText(char * path, long textid, int index, char * text)
{  FILE_HEADER * header;
   FILE * stream;
   int version, err;
   
   If ((version = AllocFile(path, "rb", &header, &stream)) > 0) Then
      err = ReadTextVar(header, stream, textid, text, 50);
      FreeFile(header, stream, FALSE);
      return err;
   Else
      return version;
   Endif
}

LOCAL int FMFAT_SetData(char * path, char * matno, char * artno, char * toolno)
{  FILE_HEADER * header;
   FILE * stream;
   int version, err;
   
   If ((version = AllocFile(path, "rb+", &header, &stream)) > 0) Then
      memset(&header->MatNr, ' ', sizeof(header->MatNr));
      memcpy(&header->MatNr, matno, min(strlen(matno), sizeof(header->MatNr)));
      header->MatNr[sizeof(header->MatNr)-1] = '\0';
      memset(&header->ToolNr, ' ', sizeof(header->ToolNr));
      memcpy(&header->ToolNr, toolno, min(strlen(toolno), sizeof(header->ToolNr)));
      header->ToolNr[sizeof(header->ToolNr)-1] = '\0';
      If ((err = WriteTextVar(header, stream, TEXTVAR_MATERIAL, matno, strlen(matno))) != USR_NO_ERROR) Then
         FreeFile(header, stream, TRUE);
         return err;
      Endif      
      If ((err = WriteTextVar(header, stream, TEXTVAR_TOOL, toolno, strlen(toolno))) != USR_NO_ERROR) Then
         FreeFile(header, stream, TRUE);
         return err;
      Endif      
      If ((err = WriteTextVar(header, stream, TEXTVAR_ART, artno, strlen(artno))) != USR_NO_ERROR) Then
         FreeFile(header, stream, TRUE);
         return err;
      Endif      
      return FreeFile(header, stream, TRUE);
   Else
      return version;
   Endif
}

LOCAL const FILE_MODULE FMFAT_FModule =
{  FMFAT_SetTime,
   FMFAT_SetRegVal,
   FMFAT_GetRegVal,
	FMFAT_SetData
};

GLOBAL const FILE_MODULE * FMFAT_FileModule()
{
   return &FMFAT_FModule;
}

