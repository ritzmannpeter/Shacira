
#ifndef _cHeatZone_h_
#define _cHeatZone_h_

#include "FileDefinitions.h"
class cFMFatFile;

class cHeatGroup;
class cHeatZone {
public:
   cHeatZone(cFMFatFile * file, ZONE_T * zone, cHeatGroup * heat_group);
   virtual ~cHeatZone();
   void Print(STRING_T & doc);
   LONG_T Set();
   LONG_T TolUpNarrow();
   LONG_T TolDownNarrow();
   LONG_T TolUpWide();
   LONG_T TolDownWide();
public:
   cHeatGroup * _HeatGroup;
   ULONG_T _UnitId;
   ULONG_T _ZoneId;
   ULONG_T _Values[40];
   STRING_T _ZoneName;
private:
   cFMFatFile * _File;
};

#endif
