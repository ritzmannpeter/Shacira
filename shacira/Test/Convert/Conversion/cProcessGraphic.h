
#ifndef _cProcessGraphic_h_
#define _cProcessGraphic_h_

#include "FileDefinitions.h"
#include "cSubfile.h"
#include "cFMFatFile.h"

class cProcessGraphic {
public:
   cProcessGraphic(cFMFatFile * file, cSubfile * subfile, SOLL_INFO * pg_info, unsigned_8 * curve_buffer);
   virtual ~cProcessGraphic();
   void Print(STRING_T & doc);
private:
   cFMFatFile * _File;
   cSubfile * _Subfile;
public:
   int _Mode;           /* Betriebsart */
   int _Delay;          /* Startverzoegerung */
   int _Time;           /* Messzeit */
   int _Mint;           /* Messintervall */
   int _Vinter;         /* Geschw.intervall */
   int _Soll_chan[2];
   int _Soll_max[2];
   int _Tol[2];
   unsigned_16 _Curve1[1000];
   unsigned_16 _Curve2[1000];
};

#endif





