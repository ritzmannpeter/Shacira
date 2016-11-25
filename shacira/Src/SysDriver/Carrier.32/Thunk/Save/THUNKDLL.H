/***************************************************************************/

#ifndef __thunkdll__
#define __thunkdll__

#include <windows.h>
#include <wownt16.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Message(const char * fmt, ... );
void ErrMessage(const char * fmt, ...);

extern DWORD _Module;

#define PARAM_01		0x1
#define PARAM_02		0x2
#define PARAM_03		0x4
#define PARAM_04		0x8

int extern __export FAR PASCAL _export CARRIER_FileInfo(char * path, void * file_info);
int extern __export FAR PASCAL _export CARRIER_FileRepair(char * path);
int extern __export FAR PASCAL _export CARRIER_SetTime(char * path);
int extern __export FAR PASCAL _export CARRIER_SetRegVal(char * path, long regid, int index, long value);
int extern __export FAR PASCAL _export CARRIER_GetRegVal(char * path, long regid, int index, long * value);
int extern __export FAR PASCAL _export CARRIER_SetData(char * path, char * artno, char * matno, char * toolno);
int extern __export FAR PASCAL Carrier(char * input, char * output);

#endif

