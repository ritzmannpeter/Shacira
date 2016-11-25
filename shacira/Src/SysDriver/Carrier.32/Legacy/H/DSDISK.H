/*********************************************************************
*
*
*         DSDISK.H         - Datentraeger
*
*
*********************************************************************/

/*  *** HISTORY ***
*   12.02.90   -SF-     Implementierung
*   10.08.90   -SF-     typedefs hierher verlagert, da Pruefung in dsutil.c
*   15.08.90   -SF-     FILE_HEADER erweitert
*   17.08.90   -SF-     FILE_HEADER nochmals erweitert
*   11.09.90   -SF-     DO_CONVERT eingebaut
*   11.09.90   -SF-     FILE_HEADER um ScrewSuckBack und PlastWay erweitert
*   12.09.90   -SF-     MAX_MAT_NR von 8 auf 15 erweitert
*   18.09.90   -SF-     ToolNr doch wieder ein String
*    4.04.91   -SF-     Version 2.0 erstellt: Konfiguration des
*                       Lesens/Schreibens ist komplett neu
*   22.10.91   -TSchw-  USE_GREATEST_KEY definiert
*   09.12.91   -SF-     DISK_ID_FOT definiert
*   31.01.92   -TSchw-  FILE_HEADER erweitert fuer Version 57: 2. Aggregat,
*                       Stufe der Werkzeuginnendruckumschaltung
*   13.02.92   -SF-     DISK_ID_ABGL definiert
*   23.11.92   -TSchw-  GENERAL_FILE_TYPE definiert
*
*/

/*********************************************************************
X  Dateikoepfe
*********************************************************************/

/* Typ der Register-Nr. */
#define  DISK_REGNR_WORD      0
#define  DISK_REGNR_LONG      1
#define  DISK_REGNR_STRING    2

