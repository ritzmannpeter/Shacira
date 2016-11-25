
#ifndef _cNewProcessGraphic_h_
#define _cNewProcessGraphic_h_

#include "FileDefinitions.h"
#include "cSubfile.h"
class cFMFatFile;

class cSetCurve {
public:
   cSetCurve(SOLL_CURVE_HEADER * curve_header, void * curve_buffer);
   virtual ~cSetCurve();
public:
   short int _Version;         /* z.Zt. immer 1; falls spaeter die Struktur */
                               /* aufgebohrt werden muss.                   */
   short int _CurveId;         /* Kurven-Id (PG_CID_PH_T etc.)              */
   short int _GroupId;         /* Gruppen-ID (FU_AGGREGAT etc.)             */
   short int _FunctionUnit;    /* Aggregatnummer (1-4)                      */
   short int _ValueType;       /* PG_SINGLE/PG_PAIR; fuer Sicherheitscheck, */
                               /* falls sich der Typ aendern sollte.        */
   short int _DimensionId;     /* Dimension (IQT_DIM_TENTH_OF_BAR etc.),    */
                               /* falls sich mal die Dimensionen aendern.   */
   short int _CompressionType; /* z.Zt. immer 0; falls mal eine Kompression */
                               /* der Kurven implementiert wird.            */
   short int _CurveBufferSize; /* Groesse des Kurvenpuffers in BYTE         */
   long  int _Tolerance;       /* Toleranz in % fuer Toleranzkurven         */
   long  int _YScale;          /* Y-Skalierung fuer Tolerankurvenberechnung */
   long  int _YMax;            /* Max. Y-Wert fuer Tolerankurvenberechnung  */
   void * _CurveBuffer;
};

typedef std::list<cSetCurve*> SET_CURVE_LIST_T;

class cNewProcessGraphic {
public:
   cNewProcessGraphic(cFMFatFile * file, cSubfile * subfile);
   virtual ~cNewProcessGraphic();
   void AddCurve(SOLL_CURVE_HEADER * curve_header, void * curve_buffer);
   void SetCurves(SET_CURVE_LIST_T & curves);
   void Print(STRING_T & doc);
private:
   cFMFatFile * _File;
   cSubfile * _Subfile;
   SET_CURVE_LIST_T _Curves;
};

#endif





