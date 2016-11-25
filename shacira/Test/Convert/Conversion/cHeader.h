
#ifndef _cHeader_h_
#define _cHeader_h_

#include "FileDefinitions.h"
#include "System/cTimeObject.h"
class cFMFatFile;

class cHeader {
public:
   cHeader(cFMFatFile * file, FILE_HEADER_T * header);
   virtual ~cHeader();
   void Print(STRING_T & doc);
public:
   int _Version;                   /* Versions-Nr. */
   int _HeaderSize;                /* Groesse des Dateiheaders */
   int _FileType;                  /* Dateityp */
   cTimeObject _Date;              /* Datum und Uhrzeit */
   int _RegType;                   /* Typ der Register-Nr. */
   STRING_T _InfoText;             /* freier Text */
   STRING_T _MashType;             /* Maschinentyp */
   STRING_T _MatNr;                /* Material-Nummer */
   STRING_T _ToolNr;               /* Werkzeug-Nummer */
   int _ProgNr;                    /* Sonderprogramm-Nr */
   int _MashSize;                  /* Maschinen-Groesse */
   int _MouldOpWay;                /* Werkzeugoeffnungsweg */
   int _VersMash;                  /* Maschinen-Version */
   int _VersStruct;                /* Datenstruktur-Version */
   int _VersExtra;                 /* spezielle Versions-Nr. */

   int _MaxAgg;                    /* Anzahl der Aggregate (1, 2 etc.)*/

   int _MouldInPres[8];            /* Stufe fuer Wkz-Innendruck. Agg2 */
   int _MaxSpritzDruck[8];         /* Maximaler Einspritzdruck   Agg2 */
   int _Diameter[8];               /* Schneckendurchmesser */
   int _PresConst[8];              /* Umrechnungskonstante fuer Druck */
   int _Aggregat[8];               /* Aggregat Ausfuehrung */
   int _HeatZoneCount[8];          /* Anzahl Heizzonen */
   int _ScrewSuckBack[8];          /* Auswahl Schneckenrueckzug */
   int _PlastWay[8];               /* Plastifizierweg */
private:
   cFMFatFile * _File;
};

#endif





 