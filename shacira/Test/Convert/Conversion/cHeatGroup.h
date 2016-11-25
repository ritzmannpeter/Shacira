
#ifndef _cHeatGroup_h_
#define _cHeatGroup_h_

#include "FileDefinitions.h"
#include "cSubfile.h"
#include "cFMFatFile.h"

#define BARREL_GROUP    1
#define TOOL_GROUP      2  
#define TEMP_GROUP      3
#define OIL_GROUP       4
#define RES_GROUP       5

#define REGSTART_CYLHEAT_REG 19000
#define REGMAX_CYLHEAT_REG   19100
#define REGMAX_TOOLHEAT_REG  19200
#define REGMAX_TEMPHEAT_REG  19300
#define REGMAX_OILHEAT_REG   19400
#define REGMAX_GENHEAT_REG   19500
#define REGMAX_RESHEAT_REG   19600

class cHeatZone;
typedef std::map<int,cHeatZone*> ZONE_MAP_T;

class cHeatGroup {
public:
   cHeatGroup(cFMFatFile * file, cSubfile * subfile, HEATGROUP_T * heat_group);
   virtual ~cHeatGroup();
   void Print(STRING_T & doc);
   void AddZone(cHeatZone * heat_zone);
   cHeatZone * Zone(int unit, int zone);
   static ULONG_T GroupId(ULONG_T reg_no);
   static CONST_STRING_T GroupName(ULONG_T reg_no);
   BOOL_T Has(int unit);
   BOOL_T Has(int unit, int zone);
   LONG_T Set(int unit, int zone);
   LONG_T TolUpNarrow(int unit, int zone);
   LONG_T TolDownNarrow(int unit, int zone);
   LONG_T TolUpWide(int unit, int zone);
   LONG_T TolDownWide(int unit, int zone);
   void ZoneMap(ZONE_MAP_T & zone_map);
public:
   ULONG_T _GroupId;
   ULONG_T _RegNo;
   ULONG_T _SubfileId;
   ULONG_T _RegCount;
private:
   cFMFatFile * _File;
   cSubfile * _Subfile;
   STRING_T _GroupName;
   ZONE_MAP_T _ZoneMap;
};

#endif





