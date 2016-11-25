/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     CARIO32
*
*  BESCHREIBUNG:
*     Zugriffsfunktionen fuer über Kernel-Mode-Treiber.
*
*  UMGEBUNG:
*     ZIELRECHNER:           PC-AT
*     ENTWICKLUNGSRECHNER:   PC-AT
*     UEBERSETZER:
*     OPTIONEN:
*
*  VERSION:
*     VERSION:    1.00                      DATUM:   28.02.00
*     AUTOR(EN):  P. Ritzmann               TELEFON: (0761) 45205-0
*
*  HISTORY:
*     28.02.00 -PR- Implementierung.
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
*     CAR_Module
*
*  DATENTYPEN:
*
*  VARIABLEN:
*
*.EM.***********************************************************************/

#include "syntax.h"
#include "basicio.h"
#include "caritf.h"

LOCAL HANDLE Handle = INVALID_HANDLE_VALUE;

GLOBAL const IO_MODULE * CAR_Module();

LOCAL long CAR_NT_Init(IO_MODULE_ ** module, const char * path)
{
	*module = CAR_Module();
   Handle = CARITF_Open();
   return 0;
}

LOCAL long CAR_NT_Exit(void)
{
   CARITF_Close(Handle);
   return 0;
}

LOCAL long CAR_NT_Check(void)
{ 
   return CARITF_Check(Handle);
}

LOCAL long CAR_NT_Write(USR_LONG address, USR_LONG size, void * buffer)
{
   long rc = CARITF_Write(Handle, address, buffer, size);
   return rc < 0 ? rc : 0;
}

LOCAL long CAR_NT_Read(USR_LONG address, USR_LONG size, void * buffer)
{
   long rc = CARITF_Read(Handle, address, buffer, size, size);
   return rc < 0 ? rc : 0;
}

LOCAL const IO_MODULE CarNTIoModule =
{  CAR_NT_Init,
	CAR_NT_Check,
	CAR_NT_Read,
	CAR_NT_Write,
	CAR_NT_Exit
};

GLOBAL const IO_MODULE * CAR_Module()
{
	return &CarNTIoModule;
}




