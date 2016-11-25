/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     DEBUG
*
*  BESCHREIBUNG:
*
*     Modul zur Steuerung der Ausgabe von Debuginformationen.
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
*     18.03.96 -PR-  Implementierung.
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
*     SetDebugMode
*     DebugPrintf
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
#ifndef __stdarg__
#include <stdarg.h>
#define __stdarg__
#endif
#ifndef __time__
#include <time.h>
#define __time__
#endif
/***************************************************************************/

LOCAL long DebugMode = 0L;
LOCAL char DebugFile[128] = "stdout";

GLOBAL int FAR PASCAL _export SetDebugMode (long debug_mode, char * output)
{
   DebugMode = debug_mode;
   If (output != NULL) Then
      sprintf(DebugFile, "%s", output);
   Else
      sprintf(DebugFile, "stdout");
   Endif
   return USR_NO_ERROR;
}

GLOBAL int FAR PASCAL _export DebugPrintf(long mode, char * fmtstr, ...)
{  va_list args;
   char text[256];
   FILE * stream;
   struct tm * newtime;
   time_t long_time;

   if (!(DebugMode & mode)) return USR_NO_ERROR;

   time(&long_time);
   newtime = localtime(&long_time);

   va_start(args, fmtstr);
   vsprintf(text, fmtstr, args);
   va_end(args);
   
   If (strcmp(DebugFile, "stdout") == 0) Then
      fprintf(stdout, "%s", text);
   Elseif (strcmp(DebugFile, "stderr") == 0) Then
      fprintf(stderr, "%s", text);
   Elseif (strcmp(DebugFile, "stdin") == 0) Then
   Elseif (strcmp(DebugFile, "com1") == 0) Then
   Elseif (strcmp(DebugFile, "com2") == 0) Then
   Elseif (strcmp(DebugFile, "com3") == 0) Then
   Elseif (strcmp(DebugFile, "com4") == 0) Then
   Else
      stream = fopen(DebugFile, "a");
      If (stream != NULL) Then
         fprintf(stream, "%s", text);
         fclose(stream);
      Endif
   Endif
   return USR_NO_ERROR;
}


