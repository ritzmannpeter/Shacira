/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVEM17.H
*
*  BESCHREIBUNG:
*     ...
*
*  UMGEBUNG:
*     ZIELRECHNER:          Provit 2000/2001/5000 - Linux/Windows
*     ENTWICKLUNGSRECHNER   PC Windows NT
*     UEBERSETZER:          VC5 / Gnu C
*                                                                     
*  VERSION:                                                           
*     VERSION:  1.0                     DATUM:       12.03.2001       
*     AUTOR:    -TSchw- T.Schwörer       
*                                                                     
*  HISTORY:                                                           
*     12.03.01 -TSchw-  Implementierung
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     Keine
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _devem17
#define _devem17

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
#include <timefunc.h>
/*.EI.***********************************************************************/

typedef struct EM17ParamBlock {
   IQT_HANDLE ComHnd;
} EM17_PARAM_BLOCK, * EM17_PARAM_PTR;

/* Die Struktur enthält die Daten eines Roboterprogramms. ProgramName,     */
/* ProgramChecksum und Data werden über die Euromap 17 Schnittstelle geholt*/
/* bzw. geschrieben. Data ist das erste Byte des DataLen große Puffers, der*/
/* das eigentliche Roboterprogramm enthält.                                */
/* Die Struktur mit dem daran anschließenden Datenpuffer ist byte-alligned,*/
/* hat also eine definierte Länge und kann somit direkt auf Datenträger    */
/* geschrieben werden.                                                     */
#include <packstart.h>
typedef struct EM17ProgramData {
   char ProgramName [8];         /* 8 Byte */
   char ProgramChecksum[8];      /* 8 Byte */
   unsigned long int DataLen;    /* 4 Byte */
   char Data[1];                 /* DataLen Byte */
} STRUCT_PACKED EM17_PROGRAM_DATA;
#include <packstop.h>

/*********************************************************************
*  EM17-Treiber: KONSTANTEN FUER DIE PARAMETER
*********************************************************************/

#define EM17_ID_COMHND              1
#define EM17_ID_STATUS              2
#define EM17_ID_PROGRAM_DATA        3
#define EM17_ID_ERROR_MSG           4
#define EM17_ID_PROGRAM_NAME        5
#define EM17_ID_STATUS_WORD         6
#define EM17_ID_BASE_COMMAND        7
#define EM17_ID_BASE_PARAMCOM       8
#define EM17_ID_BASE_BLOCKCOM       9



#endif /* ifndef _devem17 */