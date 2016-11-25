/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     HOSTSRV.H
*
*  BESCHREIBUNG:
*     ...
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    1.0                       DATUM:   14.10.92
*     AUTOR(EN):  -MBa-  M.Bauernfeind      TELEFON: (07644) 78381
*
*  HISTORY:
*     14.10.92 -MBa-   Modulerstellung
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*
*  DATENTYPEN:
*
*.EH.***********************************************************************/


/*.SH.*/

/*.SI.***********************************************************************/
#include <syntax.h>
/*.EI.***********************************************************************/

/* Leitrechner Kommunikations Steuerzeichen */

#define         STX     0x02            /* Start of Text */
#define         ETX     0x03            /* End of Text */
#define         EOT     0x04            /* End of Transmission */
#define         ENQ     0x05            /* Enquiry */
#define         CR      0x0d            /* Carriage Return */
#define         LF      0x0a            /* Line Feed */
#define         ACK     0x06            /* Acknowledge */
#define         NAK     0x15            /* No Acknowledge */
#define         ETB     0x17            /* End of Transmission Block */

#define MAX_RETRYS      3

/* Name der Server Task */
#define HstSrv_SERVER_NAME "HOSTSRV"

/**.ST.***********************************************************************
*
*  TYPNAME:
*     HstSrv_MESSAGE
*
*  BESCHREIBUNG:
*     Auftragsstruktur fuer Task-Synchronisation.
*
*  TYPDEFINITION:
*
**.ET.***********************************************************************/

#define HstSrv_WRITE            1
#define HstSrv_READ             2
#define HstSrv_CHARWRITE        3

struct HstSrv_MWRITE {
        char * buffer;
        int buflen;
        TIME timeout;
};

struct HstSrv_MREAD {
        char * buffer;
        int buflen;
        int aktlen;
        TIME timeout;
};

struct HstSrv_MESSAGE {
        int mode;
        IQT_HANDLE ComHnd;
        int Status;
        union {
                struct HstSrv_MWRITE mwrite;
                struct HstSrv_MREAD  mread;
        }m;
        int ret;
};

/*.EH.*/

