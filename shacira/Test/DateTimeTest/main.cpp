
#include "FirstHeader.h"
#include "System/cTimeObject.h"
#include <qdatetime.h>
#include <time.h>

static void toLocalTime(time_t t, int & second, int & minute, int & hour, int & day, int & month, int & year)
{
   struct tm * ts = localtime(&t);
   second = ts->tm_sec;
   minute = ts->tm_min;
   hour = ts->tm_hour;
   day = ts->tm_mday;
   month = ts->tm_mon + 1;
   year = ts->tm_year + 1900;
}

static bool dateTest(int second, int minute, int hour, int day, int month, int year, time_t & t, std::string & dateString)
{
   bool success = true;
   return success;
}

static bool cDateTest(int second, int minute, int hour, int day, int month, int year, time_t & t, std::string & dateString)
{
   bool success = true;
   cTimeObject to;
#define USE_SERIALIZED_API
#ifdef USE_SERIALIZED_API
   to.Set(cTimeObject::YEAR, year);
   to.Set(cTimeObject::MONTH, month);
   to.Set(cTimeObject::DAY, day);
   to.Set(cTimeObject::HOUR, hour);
   to.Set(cTimeObject::MINUTE, minute);
   to.Set(cTimeObject::SECOND, second);
#else
   to.Set(second, minute, hour, day, month, year);
#endif
   t = to;
   int _second = to.Get(cTimeObject::SECOND);
   int _minute = to.Get(cTimeObject::MINUTE);
   int _hour = to.Get(cTimeObject::HOUR);
   int _day = to.Get(cTimeObject::DAY);
   int _month = to.Get(cTimeObject::MONTH);
   int _year = to.Get(cTimeObject::YEAR);
   if (_second != second) {
      success = false;
   }
   if (_minute != minute) {
      success = false;
   }
   if (_hour != hour) {
      success = false;
   }
   if (_day != day) {
      success = false;
   }
   if (_month != month) {
      success = false;
   }
   if (_year != year) {
      success = false;
   }
   char ds[0x500] ={0};
   sprintf(ds, "%02.02d.%02.02d.%04.04d %02.02d:%02.02d:%02.02d", _day, _month, _year, _hour, _minute, _second);
   dateString = ds;
   return success;
}

static bool qDateTest(int second, int minute, int hour, int day, int month, int year, time_t & t, std::string & dateString)
{
   bool success = true;
   QDateTime qdt;
   QDate date;
   date.setYMD(year, month, day);
   QTime time;
   time.setHMS(hour, minute, second, 0);
   qdt.setDate(date);
   qdt.setTime(time);
   t = qdt.toTime_t();
   int _second = qdt.time().second();
   int _minute = qdt.time().minute();
   int _hour = qdt.time().hour();
   int _day = qdt.date().day();
   int _month = qdt.date().month();
   int _year = qdt.date().year();
   if (_second != second) {
      success = false;
   }
   if (_minute != minute) {
      success = false;
   }
   if (_hour != hour) {
      success = false;
   }
   if (_day != day) {
      success = false;
   }
   if (_month != month) {
      success = false;
   }
   if (_year != year) {
      success = false;
   }
   char ds[0x500] ={0};
   sprintf(ds, "%02.02d.%02.02d.%04.04d %02.02d:%02.02d:%02.02d", _day, _month, _year, _hour, _minute, _second);
   dateString = ds;
   return success;
}

void testTime(int second, int minute, int hour, int day, int month, int year, int & errors0, int & errors1, int & errors2, int & errors3)
{
   std::string dateString1;
   std::string dateString2;
   std::string dateString3;
   bool ok = false;
   time_t t1 = 0;
   time_t t2 = 0;
   time_t t3 = 0;
   ok = dateTest(second, minute, hour, day, month, year, t1, dateString1);
   if (!ok) {
      errors1++;
   }
   ok = cDateTest(second, minute, hour, day, month, year, t2, dateString2);
   if (!ok) {
      errors2++;
   }
   ok = qDateTest(second, minute, hour, day, month, year, t3, dateString3);
   if (!ok) {
      errors3++;
   }
   if (dateString2 != dateString3) {
      errors0++;
      FILE * stream = fopen("dateerrors.txt", "a");
      if (stream != NULL) {
         fprintf(stream, "%s != %s %08.08x %08.08x\n", dateString2.c_str(), dateString3.c_str(), &t2, &t3);
         fclose(stream);
      }
      printf("%s != %s %08.08x %08.08x\n", dateString2.c_str(), dateString3.c_str(), &t2, &t3);
   }
   if (t2 != t3) {
      int dummy = 0;
   }
}

static bool timeTest(int stepSize)
{
   remove("dateerrors.txt");
   int errors0 = 0;
   int errors1 = 0;
   int errors2 = 0;
   int errors3 = 0;
   bool ok = false;
   int second = 0;
   int minute = 0;
   int hour = 0;
   int day = 0;
   int month = 0;
   int year = 0;
   int currentYear = 0;
   for (year=2012; year<2020; year++) {
//   for (year=1971; year<2031; year++) {
      if (year != currentYear) {
         printf("%d\n", year);
         currentYear = year;
      }
      for (month=1; month<13; month++) {
         for (day=1; day<29; day++) {
            for (hour=0; hour<24; hour++) {
//               for (minute=0; minute<60; minute++) {
               for (minute=0; minute<1; minute++) {
//                  for (second=0; second<60; second++) {
                  for (second=0; second<1; second++) {
                     testTime(second, minute, hour, day, month, year, errors0, errors1, errors2, errors3);
                  }
               }
            }
         }
      }
   }
   if (errors0 > 0) {
      printf("%d comparison errors\n", errors0);
   }
   if (errors1 > 0) {
      printf("%d general errors\n", errors1);
   }
   if (errors2 > 0) {
      printf("%d time object errors\n", errors2);
   }
   if (errors3 > 0) {
      printf("%d QDateTime errors\n", errors3);
   }
   printf("step2: step size is %d seconds\n", stepSize);
   int tests = 1000000;
   errors0 = errors1 = errors2 = errors3 = 0;
   currentYear = 0;
   time_t t = time(NULL);
   while (true) {
      second = 0;
      minute = 0;
      hour = 0;
      day = 0;
      month = 0;
      year = 0;
      toLocalTime(t, second, minute, hour, day, month, year);
      if (year != currentYear) {
         if (errors0 > 0) {
            printf("%d comparison errors\n", errors0);
         }
         if (errors1 > 0) {
            printf("%d general errors\n", errors1);
         }
         if (errors2 > 0) {
            printf("%d time object errors\n", errors2);
         }
         if (errors3 > 0) {
            printf("%d QDateTime errors\n", errors3);
         }
         printf("%d\n", year);
         currentYear = year;
      }
      testTime(second, minute, hour, day, month, year, errors0, errors1, errors2, errors3);
      t += stepSize;
   }
   return true;
}

int main(int argc, char* argv[])
{
   int stepSize = 3600;
   if (argc > 1) {
      stepSize = atoi(argv[1]);
   }
   timeTest(stepSize);
   return 0;
}

// some resources from Qt 4

static cTimeObject DateTime(CONST_STRING_T time_value)
{
   char _year[5] = {0};
   char _month[3] = {0};
   char _day[3] = {0};
   char _hour[3] = {0};
   char _minute[3] = {0};
   char _second[3] = {0};
   memcpy(_year, time_value, 4);
   memcpy(_month, &(time_value[4]), 2);
   memcpy(_day, &(time_value[6]), 2);
   memcpy(_hour, &(time_value[8]), 2);
   memcpy(_minute, &(time_value[10]), 2);
   if (strlen(time_value) > 12) {
      memcpy(_second, &(time_value[12]), 2);
   } else {
      memcpy(_second, "00", 2);
   }
   int year = atoi(_year);
   int month = atoi(_month);
   int day = atoi(_day);
   int hour = atoi(_hour);
   int minute = atoi(_minute);
   int second = atoi(_second);
//   cTimeObject t(0);
   cTimeObject t;
   t.Set(cTimeObject::SECOND, second);
   t.Set(cTimeObject::MINUTE, minute);
   t.Set(cTimeObject::HOUR, hour);
   t.Set(cTimeObject::DAY, day);
   t.Set(cTimeObject::MONTH, month);
   t.Set(cTimeObject::YEAR, year);
   return t;
}

#define SECS_PER_HOUR   3600
#define SECS_PER_MIN    60
#define MSECS_PER_HOUR  (SECS_PER_HOUR * 1000)
#define MSECS_PER_MIN   (SECS_PER_MIN * 1000)
static uint setHMS(int h, int m, int s, int ms)
{
   uint mds = (h*SECS_PER_HOUR + m*SECS_PER_MIN + s)*1000 + ms;
   return mds;
}

static int hour(uint mds)
{
    return mds / MSECS_PER_HOUR;
}

static int minute(uint mds)
{
    return (mds % MSECS_PER_HOUR) / MSECS_PER_MIN;
}

static int second(uint mds)
{
    return (mds / 1000)%SECS_PER_MIN;
}

static int msec(uint mds)
{
    return mds % 1000;
}

static uint julianDayFromGregorianDate(int year, int month, int day)
{
    // Gregorian calendar starting from October 15, 1582
    // Algorithm from Henry F. Fliegel and Thomas C. Van Flandern
    return (1461 * (year + 4800 + (month - 14) / 12)) / 4
           + (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12
           - (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4
           + day - 32075;
}

static void getDateFromJulianDay(uint julianDay, int *year, int *month, int *day)
{
    int y, m, d;

    if (julianDay >= 2299161) {
        // Gregorian calendar starting from October 15, 1582
        // This algorithm is from Henry F. Fliegel and Thomas C. Van Flandern
        qulonglong ell, n, i, j;
        ell = qulonglong(julianDay) + 68569;
        n = (4 * ell) / 146097;
        ell = ell - (146097 * n + 3) / 4;
        i = (4000 * (ell + 1)) / 1461001;
        ell = ell - (1461 * i) / 4 + 31;
        j = (80 * ell) / 2447;
        d = ell - (2447 * j) / 80;
        ell = j / 11;
        m = j + 2 - (12 * ell);
        y = 100 * (n - 49) + i + ell;
    } else {
        // Julian calendar until October 4, 1582
        // Algorithm from Frequently Asked Questions about Calendars by Claus Toendering
        julianDay += 32082;
        int dd = (4 * julianDay + 3) / 1461;
        int ee = julianDay - (1461 * dd) / 4;
        int mm = ((5 * ee) + 2) / 153;
        d = ee - (153 * mm + 2) / 5 + 1;
        m = mm + 3 - 12 * (mm / 10);
        y = dd - 4800 + (mm / 10);
        if (y <= 0)
            --y;
    }
    if (year)
        *year = y;
    if (month)
        *month = m;
    if (day)
        *day = d;
}

