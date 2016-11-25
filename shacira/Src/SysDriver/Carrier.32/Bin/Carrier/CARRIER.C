/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     CARRIER
*
*  BESCHREIBUNG:
*     Programm zum extrahieren und ablegen von Dateien auf beliebeigen
*     Datentraegern.
*
*  UMGEBUNG:
*     ZIELRECHNER:           PC-AT
*     ENTWICKLUNGSRECHNER:   PC-AT
*     UEBERSETZER:
*     OPTIONEN:
*
*  VERSION:
*     VERSION:    1.00                      DATUM:   08.03.96
*     AUTOR(EN):                            TELEFON: (0761) 4520520
*
*  HISTORY:
*     07.07.98 -PR- Ueberpruefung auf Version im add-Kommando fuer
*                   FMT2-Datentraeger eingebaut.
*
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
*  DATENTYPEN:
*
*  VARIABLEN:
*
*.EM.***********************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <cardll32.h>

#define INBUF_SIZE   0x2000
#define OUTBUF_SIZE  0x2000

static char Input[INBUF_SIZE] = {0};
static char Output[OUTBUF_SIZE] = {0};

int main(int argc, char **argv)
{
	int i = 0;
   memset(Input, 0, INPUT_SIZE);
	memset(Output, 0, OUTPUT_SIZE);
   if (argc == 1) {
      sprintf(Input, "carrier");
   } else if (argc == 2) {
      sprintf(Input, "carrier %s", argv[1]);
   } else if (argc == 3) {
      sprintf(Input, "carrier %s %s", argv[1], argv[2]);
   } else if (argc == 4) {
      sprintf(Input, "carrier %s %s %s", argv[1], argv[2], argv[3]);
   } else if (argc == 5) {
      sprintf(Input, "carrier %s %s %s %s", argv[1], argv[2], argv[3],
              argv[4]);
   } else if (argc == 6) {
      sprintf(Input, "carrier %s %s %s %s %s", argv[1], argv[2], argv[3],
              argv[4], argv[5]);
   } else if (argc == 7) {
      sprintf(Input, "carrier %s %s %s %s %s %s", argv[1], argv[2], argv[3],
              argv[4], argv[5], argv[6]);
   }
	Carrier(Input, Output);
	printf(Output);
   return 0;
}


