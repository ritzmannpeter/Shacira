#ifndef _files
#define _files

/*.SI.***********************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
/*.EI.***********************************************************************/

GLOBAL int CAR_InitCarrier();
GLOBAL int CAR_FormatCarrier(int format,int param);
GLOBAL int CAR_DirCarrier();
GLOBAL int CAR_RemoveFile(char * file_name);
GLOBAL int CAR_SaveFile(char * file_name, int format);
GLOBAL int CAR_RestoreFile(char * file_name);
GLOBAL int CAR_RestoreFileTo(char * file_name, char * out_file_name);
GLOBAL int CAR_RestoreAllFiles(char * destination_path);
GLOBAL int CAR_FileInfo(char * path, FILE_INFO * fileinfo);
GLOBAL int CAR_RemoveAllFiles();
GLOBAL int CAR_FileRepair(char * path);
GLOBAL int CAR_SetTime(char * path);
GLOBAL int CAR_SetRegVal(char * path, long regid, int index, long value);
GLOBAL int CAR_GetRegVal(char * path, long regid, int index, long * value);
GLOBAL int CAR_SetData(char * path, char * artno, char * matno, char * toolno);

#endif /* ifndef _files */
