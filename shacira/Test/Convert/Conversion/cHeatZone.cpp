
#include "FirstHeader.h"
#include "cHeatGroup.h"
#include "cHeatZone.h"
#include "cFMFatFile.h"

cHeatZone::cHeatZone(cFMFatFile * file, ZONE_T * zone, cHeatGroup * heat_group)
{
   _File = file;
   memset(_Values, 0, sizeof(_Values));
   _HeatGroup = heat_group;
   _UnitId = zone->unit_id;
   _ZoneId = zone->zone_id;
   short * short_ptr = (short*)zone->buffer;
   for (ULONG_T i=0; i<_HeatGroup->_RegCount; i++) {
      _Values[i] = *short_ptr;
      short_ptr++;
   }
}

cHeatZone::~cHeatZone()
{
}

void cHeatZone::Print(STRING_T & doc)
{
}

LONG_T cHeatZone::Set()
{
   return _Values[0];
}

LONG_T cHeatZone::TolUpNarrow()
{
   return _Values[2];
}

LONG_T cHeatZone::TolDownNarrow()
{
   return _Values[4];
}

LONG_T cHeatZone::TolUpWide()
{
   return _Values[1];
}

LONG_T cHeatZone::TolDownWide()
{
   return _Values[3];
}


