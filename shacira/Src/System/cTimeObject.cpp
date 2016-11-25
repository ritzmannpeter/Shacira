//## begin module%3BA21C2A0140.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA21C2A0140.cm

//## begin module%3BA21C2A0140.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3BA21C2A0140.cp

//## Module: cTimeObject%3BA21C2A0140; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\cTimeObject.cpp

//## begin module%3BA21C2A0140.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BA21C2A0140.additionalIncludes

//## begin module%3BA21C2A0140.includes preserve=yes
#include <time.h>

//## end module%3BA21C2A0140.includes

// cTimeObject
#include "System/cTimeObject.h"
//## begin module%3BA21C2A0140.additionalDeclarations preserve=yes
inline int daylightSavings(int localValue)
{
#if defined(_WIN32)
   /// ???
   return -1;
   TIME_ZONE_INFORMATION info = {0};
   DWORD ds = GetTimeZoneInformation(&info);
   if (ds == TIME_ZONE_ID_UNKNOWN) {
      return -1;
   } else if (ds == TIME_ZONE_ID_STANDARD) {
      return 0;
   } else if (ds == TIME_ZONE_ID_DAYLIGHT) {
      return 1;
   } else {
      return -1;
   }
#else
   return localValue;
#endif
}
//## end module%3BA21C2A0140.additionalDeclarations


// Class cTimeObject 



cTimeObject::cTimeObject()
  //## begin cTimeObject::cTimeObject%.hasinit preserve=no
      : _Time(0)
  //## end cTimeObject::cTimeObject%.hasinit
  //## begin cTimeObject::cTimeObject%.initialization preserve=yes
  //## end cTimeObject::cTimeObject%.initialization
{
  //## begin cTimeObject::cTimeObject%.body preserve=yes
   Now();
  //## end cTimeObject::cTimeObject%.body
}

cTimeObject::cTimeObject(const cTimeObject &right)
  //## begin cTimeObject::cTimeObject%copy.hasinit preserve=no
      : _Time(0)
  //## end cTimeObject::cTimeObject%copy.hasinit
  //## begin cTimeObject::cTimeObject%copy.initialization preserve=yes
  //## end cTimeObject::cTimeObject%copy.initialization
{
  //## begin cTimeObject::cTimeObject%copy.body preserve=yes
   _Time = right._Time;
  //## end cTimeObject::cTimeObject%copy.body
}

cTimeObject::cTimeObject (time_t time)
  //## begin cTimeObject::cTimeObject%1000474830.hasinit preserve=no
      : _Time(0)
  //## end cTimeObject::cTimeObject%1000474830.hasinit
  //## begin cTimeObject::cTimeObject%1000474830.initialization preserve=yes
  //## end cTimeObject::cTimeObject%1000474830.initialization
{
  //## begin cTimeObject::cTimeObject%1000474830.body preserve=yes
   _Time = (ULONG_T)time;
  //## end cTimeObject::cTimeObject%1000474830.body
}

cTimeObject::cTimeObject (ULONG_T time)
  //## begin cTimeObject::cTimeObject%1000474831.hasinit preserve=no
      : _Time(0)
  //## end cTimeObject::cTimeObject%1000474831.hasinit
  //## begin cTimeObject::cTimeObject%1000474831.initialization preserve=yes
  //## end cTimeObject::cTimeObject%1000474831.initialization
{
  //## begin cTimeObject::cTimeObject%1000474831.body preserve=yes
   _Time = time;
  //## end cTimeObject::cTimeObject%1000474831.body
}

cTimeObject::cTimeObject (int time)
  //## begin cTimeObject::cTimeObject%1134980236.hasinit preserve=no
      : _Time(0)
  //## end cTimeObject::cTimeObject%1134980236.hasinit
  //## begin cTimeObject::cTimeObject%1134980236.initialization preserve=yes
  //## end cTimeObject::cTimeObject%1134980236.initialization
{
  //## begin cTimeObject::cTimeObject%1134980236.body preserve=yes
   _Time = (ULONG_T)time;
  //## end cTimeObject::cTimeObject%1134980236.body
}


cTimeObject::~cTimeObject()
{
  //## begin cTimeObject::~cTimeObject%.body preserve=yes
  //## end cTimeObject::~cTimeObject%.body
}



//## Other Operations (implementation)
void cTimeObject::Now ()
{
  //## begin cTimeObject::Now%1000474832.body preserve=yes
   _Time = time(NULL);
  //## end cTimeObject::Now%1000474832.body
}

cTimeObject cTimeObject::Elapsed ()
{
  //## begin cTimeObject::Elapsed%1000474833.body preserve=yes
   time_t now = time(NULL);
   time_t diff = now - _Time;
   return cTimeObject(diff);
  //## end cTimeObject::Elapsed%1000474833.body
}

INT_T cTimeObject::Get (Dimensions dimension) const
{
  //## begin cTimeObject::Get%1000474834.body preserve=yes
   struct tm * tstruct = localtime(&_Time);
   switch (dimension) {
   case MSECOND: return 0;
   case SECOND: return tstruct->tm_sec;
   case MINUTE: return tstruct->tm_min;
   case HOUR: return tstruct->tm_hour;
   case DAY: return tstruct->tm_mday;
   case MONTH: return tstruct->tm_mon + 1;
   case YEAR: return tstruct->tm_year + 1900;
   case YDAY: return tstruct->tm_yday + 1;
   case WDAY: return tstruct->tm_wday + 1;
   default: return 0;
   }
  //## end cTimeObject::Get%1000474834.body
}

void cTimeObject::Set (Dimensions dimension, INT_T value)
{
  //## begin cTimeObject::Set%1000474835.body preserve=yes
   struct tm * tstruct = localtime(&_Time);
   switch (dimension) {
   case MSECOND: return;
   case SECOND: tstruct->tm_sec = value; break;
   case MINUTE: tstruct->tm_min = value; break;
   case HOUR: tstruct->tm_hour = value; break;
   case DAY: tstruct->tm_mday = value; break;
   case MONTH: tstruct->tm_mon = value - 1; break;
   case YEAR: tstruct->tm_year = value - 1900; break;
   default: return;
   }
   tstruct->tm_isdst = daylightSavings(tstruct->tm_isdst);
   time_t time = mktime(tstruct);
   if (time != -1) {
      _Time = time;
   }
  //## end cTimeObject::Set%1000474835.body
}

void cTimeObject::Set (CONST_STRING_T value)
{
  //## begin cTimeObject::Set%1053529581.body preserve=yes
   INT_T year = 0;
   INT_T month = 0;
   INT_T day = 0;
   INT_T hour = 0;
   INT_T minute = 0;
   INT_T second = 0;
   int params = sscanf(value, "%d.%d.%d %d:%d:%d",
                       &day, &month, &year, &hour, &minute, &second);
   if (year > 50 && year <= 99) {
      year += 1900;
   } else if (year <= 50) {
      year += 2000;
   }
   if (params == 6) {
      Set(DAY, day);
      Set(MONTH, month);
      Set(YEAR, year);
      Set(HOUR, hour);
      Set(MINUTE, minute);
      Set(SECOND, second);
   } else if (params == 5) {
      Set(DAY, day);
      Set(MONTH, month);
      Set(YEAR, year);
      Set(HOUR, hour);
      Set(MINUTE, minute);
   } else if (params == 4) {
      Set(DAY, day);
      Set(MONTH, month);
      Set(YEAR, year);
      Set(HOUR, hour);
   } else if (params == 3) {
      Set(DAY, day);
      Set(MONTH, month);
      Set(YEAR, year);
   }
  //## end cTimeObject::Set%1053529581.body
}

void cTimeObject::Set (INT_T sec, INT_T min, INT_T hour, INT_T day, INT_T month, INT_T year)
{
  //## begin cTimeObject::Set%1134552276.body preserve=yes
   struct tm * tstruct = localtime(&_Time);
   tstruct->tm_sec  = sec;
   tstruct->tm_min  = min;
   tstruct->tm_hour = hour;
   tstruct->tm_mday = day;
   tstruct->tm_mon  = month - 1;
   tstruct->tm_year = year - 1900;
   tstruct->tm_isdst = daylightSavings(tstruct->tm_isdst);
   time_t time = mktime(tstruct);
   if (time != -1) {
      _Time = time;
   }
  //## end cTimeObject::Set%1134552276.body
}

void cTimeObject::SetSystime ()
{
  //## begin cTimeObject::SetSystime%1092322933.body preserve=yes
#if defined(_WIN32)
#if defined(__MINGW32__)
PORT_LEVEL_3
#else
   struct tm * tstruct = localtime(&_Time);
   unsigned ret = _setsystime(tstruct, 0);
#endif
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
  //## end cTimeObject::SetSystime%1092322933.body
}

cTimeObject::operator time_t () const
{
  //## begin cTimeObject::operator time_t%1000474837.body preserve=yes
   return _Time;
  //## end cTimeObject::operator time_t%1000474837.body
}

cTimeObject::operator ULONG_T () const
{
  //## begin cTimeObject::operator ULONG_T%1000474838.body preserve=yes
   return (ULONG_T)_Time;
  //## end cTimeObject::operator ULONG_T%1000474838.body
}

cTimeObject::operator CONST_STRING_T ()
{
  //## begin cTimeObject::operator CONST_STRING_T%1000474839.body preserve=yes
   char time_text[128] = {0};
   SafePrintf(time_text, sizeof(time_text), "%02.2d.%02.2d.%04.4d %02.2d:%02.2d:%02.2d",
              (int)Get(DAY),
              (int)Get(MONTH),
              (int)Get(YEAR),
              (int)Get(HOUR),
              (int)Get(MINUTE),
              (int)Get(SECOND));
   _Text = time_text;
   return _Text.c_str();
  //## end cTimeObject::operator CONST_STRING_T%1000474839.body
}

cTimeObject cTimeObject::operator - (const cTimeObject &right)
{
  //## begin cTimeObject::operator -%1006258483.body preserve=yes
   unsigned long left_value = *this;
   unsigned long right_value = right;
   unsigned long diff = left_value - right_value;
   return cTimeObject(diff);
  //## end cTimeObject::operator -%1006258483.body
}

cTimeObject cTimeObject::operator + (const cTimeObject &right)
{
  //## begin cTimeObject::operator +%1006258484.body preserve=yes
   unsigned long left_value = *this;
   unsigned long right_value = right;
   unsigned long sum = left_value + right_value;
   return cTimeObject(sum);
  //## end cTimeObject::operator +%1006258484.body
}

STRING_T cTimeObject::Duration ()
{
  //## begin cTimeObject::Duration%1053332827.body preserve=yes
   ULONG_T time = (ULONG_T)_Time;
   ULONG_T days = time / (24 * 60 * 60);
   time = time % (24 * 60 * 60);
   ULONG_T hours = time / (60 * 60);
   time = time % (60 * 60);
   ULONG_T minutes = time / 60;
   time = time % 60;
   ULONG_T seconds = time;
   char buf[128] = {0};
   SafePrintf(buf, sizeof(buf), "%d %02.02d:%02.02d:%02.02d", days, hours, minutes, seconds);
   return buf;
  //## end cTimeObject::Duration%1053332827.body
}

// Additional Declarations
  //## begin cTimeObject%3BA21C2A0140.declarations preserve=yes
  //## end cTimeObject%3BA21C2A0140.declarations

//## begin module%3BA21C2A0140.epilog preserve=yes
//## end module%3BA21C2A0140.epilog
