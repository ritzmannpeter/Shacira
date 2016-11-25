
#include "FirstHeader.h"
#include "cHeatZone.h"
#include "cHeatGroup.h"

cHeatGroup::cHeatGroup(cFMFatFile * file, cSubfile * subfile, HEATGROUP_T * heat_group)
{
   _File = file;
   _Subfile = subfile;
   _RegNo = heat_group->heatgroup;
   _GroupId = GroupId(_RegNo);
   _SubfileId = heat_group->subfile_id;
   _GroupName = GroupName(_RegNo);
   _RegCount = heat_group->reg_count;
   subfile->AddHeatGroup(this);
}

cHeatGroup::~cHeatGroup()
{
}

void cHeatGroup::Print(STRING_T & doc)
{
}

#define ZONE_IDENT(unit, zone)   ((unit*1000) + zone)
void cHeatGroup::AddZone(cHeatZone * heat_zone)
{
   int unit = heat_zone->_UnitId;
   int zone = heat_zone->_ZoneId;
   int zone_ident = ZONE_IDENT(unit,zone);
   _ZoneMap[zone_ident] = heat_zone;
}

cHeatZone * cHeatGroup::Zone(int unit, int zone)
{
   int zone_ident = ZONE_IDENT(unit,zone);
   ZONE_MAP_T::const_iterator i = _ZoneMap.find(zone_ident);
   if (i == _ZoneMap.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

ULONG_T cHeatGroup::GroupId(ULONG_T reg_no)
{
   switch (reg_no) {
   case 19000: return BARREL_GROUP;
   case 19100: return TOOL_GROUP;
   case 19200: return TEMP_GROUP;
   case 19300: return OIL_GROUP;
   case 19400: return RES_GROUP;
   }
   return 0;
}

CONST_STRING_T cHeatGroup::GroupName(ULONG_T reg_no)
{
   switch (reg_no) {
   case 19000: return "Zylinderheizung";
   case 19100: return "Werkzeugheizung";
   case 19200: return "Temperiergeräte";
   case 19300: return "Ölheizung";
   case 19400: return "Reserveheizung";
   }
   return "keine Ahnung";
}

BOOL_T cHeatGroup::Has(int unit)
{
   ZONE_MAP_T::const_iterator i = _ZoneMap.begin();
   while (i != _ZoneMap.end()) {
      cHeatZone * heat_zone = (*i).second;
      if ((int)heat_zone->_UnitId == unit) {
         return true;
      }
      i++;
   }
   return false;
}

BOOL_T cHeatGroup::Has(int unit, int zone)
{
   cHeatZone * heat_zone = Zone(unit, zone);
   if (heat_zone != NULL) {
      return true;
   } else {
      return false;
   }
}

LONG_T cHeatGroup::Set(int unit, int zone)
{
   cHeatZone * heat_zone = Zone(unit, zone);
   if (heat_zone != NULL) {
      return heat_zone->Set();
   } else {
      return 0;
   }
}

LONG_T cHeatGroup::TolUpNarrow(int unit, int zone)
{
   cHeatZone * heat_zone = Zone(unit, zone);
   if (heat_zone != NULL) {
      return heat_zone->TolUpNarrow();
   } else {
      return 0;
   }
}

LONG_T cHeatGroup::TolDownNarrow(int unit, int zone)
{
   cHeatZone * heat_zone = Zone(unit, zone);
   if (heat_zone != NULL) {
      return heat_zone->TolDownNarrow();
   } else {
      return 0;
   }
}

LONG_T cHeatGroup::TolUpWide(int unit, int zone)
{
   cHeatZone * heat_zone = Zone(unit, zone);
   if (heat_zone != NULL) {
      return heat_zone->TolUpWide();
   } else {
      return 0;
   }
}

LONG_T cHeatGroup::TolDownWide(int unit, int zone)
{
   cHeatZone * heat_zone = Zone(unit, zone);
   if (heat_zone != NULL) {
      return heat_zone->TolDownWide();
   } else {
      return 0;
   }
}

void cHeatGroup::ZoneMap(ZONE_MAP_T & zone_map)
{
   zone_map = _ZoneMap;
}





