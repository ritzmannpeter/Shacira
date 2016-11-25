/*********************
EnumProc.h
*********************/ 
#include <windows.h>

typedef BOOL (CALLBACK *PROCENUMPROC)( DWORD, WORD, LPSTR,
  LPARAM ) ;

BOOL WINAPI EnumProcs( PROCENUMPROC lpProc, LPARAM lParam ) ;

