/****************************************************************************
*
*
*        TEXTVAR.H
*
*
*        In diesem H-File sind Konstanten fuer die Textvariablen definiert.
*        In den Seitenbeschreibungen werden Textvariable definiert, denen
*        ein Index zugeordnet ist. Um die Verwaltung dieser Indizes zu
*        erleichtern, werden die hier definierten Konstanten verwendet.
*
*        Die Indizes muessen groesser als 0 sein und sollten ohne Luecke
*        sequentiell aufeinander folgen, da im Kernprogramm so viele
*        Speicherplaetze reserviert werden, wie durch den groessten Index
*        nahegelegt werden.
*
*        Folgende Konstanten werden im Kernprogramm verwendet und duerfen
*        deshalb nicht geaendert werden, ohne das Kernprogramm (Modul BDE)
*        neu zu uebersetzen und zu linken:
*
*        TEXTVAR_MASHINE
*        TEXTVAR_ORDER
*        TEXTVAR_PERSONAL
*        TEXTVAR_MATERIAL
*        TEXTVAR_TOOL
*        TEXTVAR_DISK_INFO
*        TEXTVAR_MTYPE
*
*  HISTORY:
*     08.10.90 -TSchw-  Konstanten 12, 13, 14 eingefuehrt
*     27.11.90 -SF-     Robotertexte (Konstanten 15 - 18) eingefuehrt
*     21.10.91 -SF-     TEXTVAR_VERSION ist neu
*     22.11.91 -TSchw-  TEXTVAR_ART ist neu: Artikelnummer fuer Mangel 171
*     09.12.91 -SF-     TEXTVAR_PASSWORD eingebaut
*     21.02.92 -PR-     TEXTVAR_HEATCHANTYPE eingefuehrt (EWIKON)
*     22.12.92 -TSchw-  TEXTVAR_SPEC_PROG_LINE und TEXTVAR_SPEC_PROG_NAME
*                       eingefuegt
*     04.03.93 -TSchw-  TEXTVAR_SPEC_PROG_LINE und TEXTVAR_SPEC_PROG_NAME
*                       auf Index 33 und 34 verschoben, da die Indizes
*                       21 - 30 fuer Maintal reserviert sind.
*     13-09-96 -PR-     Konstanten fuer Texte Kernbewegungen (TEXTVAR_MOVEMENT).
*     08.12.97 -HAns-   Konstante fuer freiauswaehlbare Diagnoseseite (TEXTVAR_FREEDIAG)
*                       eingefuegt.
*     27.04.00 -TSchw-  TEXTVAR_RUNOFF eingefuegt fuer die Abnahmeprotkollierung
*     13.11.00 -TSchw-  TEXTVAR_NEWPERSNR eingefuegt (siehe MEMCARD).
*     26.03.01 -TSchw-  TEXTVAR_EM17... eingefügt (siehe EM17).
*     05.06.01 -TSchw-  TEXTVAR_STOP_ERRORS eingefügt für variable Stillstandstexte
*     14.01.02 -HA-     TEXTVAR_LV_NAME eingefuegt, fuer variable Luftventiltexte
*     04.04.03 -HA-     TEXTVAR_SPECCORE eingefügt für variable Kernzugtexte der Seite 67.0
*
****************************************************************************/

#ifndef _textvar
#define _textvar

#define  TEXTVAR_MASHINE          1
#define  TEXTVAR_ORDER            2
#define  TEXTVAR_PERSONAL         3
#define  TEXTVAR_MATERIAL         4 
#define  TEXTVAR_TOOL             5 
#define  TEXTVAR_ART              6
#define  TEXTVAR_FREEPAGE1        7
#define  TEXTVAR_FREEPAGE2        8
#define  TEXTVAR_DISK_INFO        9
#define  TEXTVAR_FREEPAGE3       10
#define  TEXTVAR_FREEPAGE4       11
#define  TEXTVAR_COLOR_TYPE      12
#define  TEXTVAR_COLOR           13
#define  TEXTVAR_MTYPE           14
#define  TEXTVAR_ROB_PGM         15
#define  TEXTVAR_ROB_MACRO       16
#define  TEXTVAR_ROB_PAR_TYPE    17
#define  TEXTVAR_ROB_PAR_NAME    18
#define  TEXTVAR_ROB_HEADPOINT   19
#define  TEXTVAR_VERSION         20
/* Die Indizes 21-30 werden z.T. von Maintal benutzt */

#define  TEXTVAR_PASSWORD        31
/*BEGIN_EWIKON*/
#define  TEXTVAR_HEATCHANTYPE    32
/*END_EWIKON*/
#define  TEXTVAR_SPEC_PROG_LINE  33
#define  TEXTVAR_SPEC_PROG_NAME  34
#define  TEXTVAR_FREETEXT        35
#define  TEXTVAR_MOVEMENT        36
#define  TEXTVAR_FREEDIAG        37

#define  TEXTVAR_RUNOFF          38    /* Abnahmeprotokoll Texte: */

#define  TEXTVAR_NEWPERSNR       39    /* MEMCARD */

#define  TEXTVAR_EM17_PROGNAME   40    /* EM17 */
#define  TEXTVAR_EM17_STATUS     41    /* EM17 */
#define  TEXTVAR_EM17_ERRORS     42    /* EM17 */

#define  TEXTVAR_STOP_ERRORS     43    /* Variable Stillstandsmeldungen */
#define  TEXTVAR_LV_NAME         44    /* variable Luftventiltexte */
#define  TEXTVAR_SPECCORE        45    /* variable Kernzugtext, Seite 67.0 */
 
#endif      /* #ifndef _textvar */
