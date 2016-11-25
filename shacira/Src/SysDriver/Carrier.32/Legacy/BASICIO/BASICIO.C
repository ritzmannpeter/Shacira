/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     CARIO
*
*  BESchREIBUNG:
*     Zugriffsfunktionen fuer EEPROM-Datentraeger.
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
*     BASIC_Init
*     CASIC_check
*     BASIC_Read
*     BASIC_Write
*     BASIC_Exit
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
#ifndef __conio__
#include <conio.h>
#define __conio__
#endif
#ifndef __errcode__
#include <errcode.h>
#define __errcode__
#endif
#ifndef __cario__
#include <cario.h>
#define __cario__
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


LOCAL IO_MODULE * IoModule = NULL;

GLOBAL int BASIC_Init(int io, int delay_size, char * path)
{
   If (io == CARRIER_IO) Then
      return CAR_Module()->init(&IoModule, NULL);
   Elseif (io == DUMP_IO) Then
      return DMP_Module()->init(&IoModule, path);
   Else
      return BASIC_INVALID_IO_TYPE;
   Endif
}

GLOBAL int BASIC_Check()
{
   return IoModule->check();
}

GLOBAL int BASIC_Read(USR_LONG address, USR_LONG size, void * buffer)
{
   return IoModule->read(address, size, buffer);
}     

GLOBAL int BASIC_Write(USR_LONG address, USR_LONG size, void * buffer)
{
   return IoModule->write(address, size, buffer);
}     

GLOBAL int BASIC_Exit()
{
	return IoModule->exit();
}

