// ===========================================================================
// eb_time.cpp                                                  ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cDateTime - Verwaltung von Datum und Uhrzeit
//     |
//     +--cDate     - Datum/Woche (Tag, Monat, Jahr oder Woche, Jahr)
//     |
//     +--cTime     - Uhrzeit (Stunde, Minute, Sekunde)
//
// ===========================================================================

#include "base/eb_time.hpp"

#include <math.h>
#include <ctype.h>


// Lokale Daten
// ===========================================================================
// ### Wofuer ist das? Kannste gelegentlich dokumentieren!

#if defined __ECL_VCPP__
   class __ECL_cSetupTimezoneInfo__ {
   public: __ECL_cSetupTimezoneInfo__() { _tzset(); }
   } __ECL_SetupTimezoneInfo__;
#endif




#ifdef __INTERFACE__

// Headerdateien
// ===========================================================================

#include <time.h> /* wg. time_t */

#include "base/eb_base.hpp"
#include "base/eb_str.hpp"

class cDateTime;

// ===========================================================================
// Declaration cDate
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDate - Datum (an Tagen orientiert)
//
// ===========================================================================

class __ECL_DLLEXPORT__ cDate : public cBase {

public:
   // Datum ueber aktuelles Datum erzeugen
   cDate();
   // Datum ueber julianisches Datum erzeugen
   cDate(long jd);
   // Datum ueber Tag, Monat und Jahr erzeugen (Jahreszahl 2- oder 4-stellig)
   cDate(int year, int month, int day);
   // Datum ueber KW und Jahr erzeugen
   cDate(int year, int week);
   // Datum ueber Textform erzeugen (bei weekyr=true wird KW/JJJJ angenommen)
   cDate(const char *str, bool weekyr = false);

   // Datum ueber cDateTime erzeugen
   cDate(const cDateTime &other);
   // Zuweisungsoperator (cDateTime)
   cDate &operator=(const cDateTime &other);

   // Tag ermitteln (1..31)
   int getDay() const;
   // Monat ermitteln (1..12)
   int getMonth() const;
   // Jahr ermitteln (nur 4-stellig)
   int getYear() const;
   // Liefert das Standard-Textformat (TT.MM.JJJJ)
   cString getStr() const;


   // Woche
   // =====

   // Wochentag ermitteln (0..6, 0 = Montag)
   int getWeekday() const
      { return jd % 7; }
   // Aufzaehlung aller Wochentage
   enum WEEKDAY {
      wdayMonday    = 0,
      wdayTuesday   = 1,
      wdayWednesday = 2,
      wdayThursday  = 3,
      wdayFriday    = 4,
      wdaySaturday  = 5,
      wdaySunday    = 6,
   };

   // Kalenderwoche
   int getWeek() const;
   // Liefert das Standard-Textformat der Kalenderwoche (KW WW/JJJJ)
   cString getWeekStr() const
      { return cStringf("KW %02d/%04d", getWeek(), getYear()); }


   // Vergleichsoperatoren
   // ====================

   // Vergleichsoperatoren (Direktvergleich des Julianischen Datums)
   int operator==(const cDate& other) const
      { return jd == other.jd; }
   int operator!=(const cDate& other) const
      { return jd != other.jd; }
   int operator<(const cDate& other) const
      { return jd < other.jd; }
   int operator<=(const cDate& other) const
      { return jd < other.jd; }
   int operator>(const cDate& other) const
      { return jd < other.jd; }
   int operator>=(const cDate& other) const
      { return jd < other.jd; }


   // Abstaende zwischen Daten
   // ========================

   // Tage zwischen zwei Daten
   int operator-(const cDate& other) const
      { return (jd - other.jd); }
   // Tage zwischen zwei Daten
   int getDaysTo(const cDate& other) const
      { return (jd - other.jd); }
   // Wochen zwischen zwei Daten
   int getWeeksTo(const cDate& other) const
      { return (jd - other.jd) / 7; }
   // Monate zwischen zwei Daten
   int getMonthsTo(const cDate& other) const
      { return getYearsTo(other)*12 + (getMonth()-other.getMonth()); }
   // Jahre zwischen zwei Daten
   int getYearsTo(const cDate& other) const
      { return getYear()-other.getYear(); }


   // Datumsarithmetik
   // ================

   // Tage von Datum subtrahieren
   cDate operator-(int days) const
      { return cDate(jd - days); }
   // Tage zu Datum addieren
   cDate operator+(int days) const
      { return cDate(jd + days); }
   // Tage zu Datum addieren
   cDate addDays(int days) const
      { return cDate(jd + days); }
   // Wochen zu Datum addieren
   cDate addWeeks(int weeks) const
      { return cDate(jd + weeks * 7); }
   // Monate zu Datum addieren
   cDate addMonths(int months) const;
   // Jahre zu Datum addieren
   cDate addYears(int years) const
      { return addMonths(years * 12); }


   // Julianisches Datum
   // ==================

   // julianisches Datum (fuer 12:00h)
   long getJulianDate() const
      { return jd; }
   // Umrechnung Kalender -> Julianisches Datum
   static long getJulianDate(int year, int month, int day);
   // Umrechnung Julianisches Datum -> Kalender
   static void getCalendar(long jd, int &year, int &month, int &day);


   // Maskieren
   // =========

   enum MASKS {
      mskYear  = 0x0020,
      mskMonth = 0x0010,
      mskDay   = 0x0008,
   };

   // Liefert das maskierte Datum (Komponenten mit 'false' haben Defaultwerte)
   cDate getMasked(bool year, bool month, bool day) const;
   // Liefert das maskierte Datum (Bitmaske, Bits 5..3 = YMD)
   cDate getMasked(int mask) const;


   // Umwandlung
   // ==========

   // Umwandlung cDate <- time_t
   static cDate conv(const time_t& tstamp);
   // Umwandlung time_t <- cDate
   static time_t conv(const cDate& date);


   // Sonstiges
   // =========

   // Tag im Jahr ermitteln (0..364/365)
   int getYearDay() const;
   // Laenge des Monats (28..31)
   int getMonthLength() const;
   static int getMonthLength(int year, int month);
   // Laenge des Jahres (365..366)
   int getYearLength() const;
   static int getYearLength(int year);

   // Monat als String
   cString getMonthStr() const
      { return getMonthStr(getMonth()); }
   static cString getMonthStr(int month);

   // Wochentag als String
   cString getWeekdayStr() const
      { return getWeekdayStr(getWeekday()); }
   static cString getWeekdayStr(int weekday);


private:
   // interne Darstellung: "Julianisches Datum", am 01.01.4713 v.Chr., 12:00h
   // beginnt die Zaehlung mit 0. (Der 01.01.2000, 12:00h ist 2451545.0 JD)
	long jd;
};

#endif /*__INTERFACE__*/




// Implementierung cDate
// ===========================================================================
// interne Darstellung: "Julianisches Datum", am 01.01.4713 v.Chr., 12:00h
// beginnt die Zaehlung mit 0. (Der 01.01.2000, 12:00h ist 2451545.0 JD,
// beginnend mit diesem Datum gibt es auch das "Julianische Datum 2000")
//
// Die verwendeten Algorithmen erheben keinen Anspruch auf astronomische
// Genauigkeit. Insbesondere wird die Gregorianische Kalenderreform ausser
// Acht gelassen: es gibt Fehlberechnungen vor dem 15.10.1582 = 2299161 JD.
// Die Gueltigkeit in der Zukunft koennte man bis zum 31.12.9999 = 5373484 JD
// annehmen, aber vorher wird es wohl wieder eine Kalenderreform geben (NGZ?)
//
// Moegliche Erweiterungen:
// Operatoren +=, -=

// (statische) Basisfunktionen fuer das Julianische Datum
// ---------------------------------------------------------------------------

long cDate::getJulianDate(int y, int m, int d)
{
   // zweistellige Jahreszahlen -> 1950..2049
   if (y < 50) {
      y += 2000;
   } else if (y < 100) {
      y += 1900;
   }

   int y1 = y;
   int m1 = m+1;

   if (m <=2) {
      y1 -= 1;
      m1 += 12;
   };

   int leap = (int)(2 - floor(y1/100) + floor(y1/400));
   return (long)(floor(365.25*y1) + floor(30.6001*m1) + d + leap + 1720995);
}

void cDate::getCalendar(long jd, int &y, int &m, int &d)
{
   // I = (long)floor(jd + 0.5) --> I = jd
   // F = jd + 0,5 - I          --> F = 0.5
   long A = jd;

   if (jd >= 2299161) {
      long X = (long)floor((jd-1867216.25) / 36524.25);
      A += 1 + X - (long)floor(X/4);
   }

   long B = A + 1524;
   long C = (int)floor((B-122.1) / 365.25);
   long D = (int)floor(365.25 * C);
   long E = (int)floor((B-D) / 30.6001);

   // dd = B-D-floor(30.6001*E) + F;
   d = B - D - (long)floor(30.6001*E);
   m = (E <= 13) ? E-1 : E-13;
   y = (m >= 3) ? C-4716 : C-4715;
}


// Konstruktion
// ---------------------------------------------------------------------------

cDate::cDate()
{
   time_t now = time(0);
   struct tm * local = localtime(&now);
   jd = getJulianDate(local->tm_year+1900, local->tm_mon+1, local->tm_mday);
}

cDate::cDate(long jd)
{
   cDate::jd = jd;
}

cDate::cDate(int year, int month, int day)
{
   jd = getJulianDate(year, month, day);
}

cDate::cDate(const cDateTime &datetime)
{
   *this = datetime.getDate();
}

cDate::cDate(int year, int week)
{
   int jd_jan1 = getJulianDate(year,1,1);
   jd = jd_jan1 - (jd_jan1 % 7) + (week-1) * 7;
}

// Diesen merkwuerdigen Konstruktor hab ich aus der alten cDate-Klasse
// uebernommen und nur ein wenig angepasst ... ohne Gewaehr!
cDate::cDate(const char *str, bool weekyr)
{
   *this = cDate();

   char *end = NULL;
   static char term[] = ",./";
   int f1 = -1, f2 = -1, f3 = -1;

   if ( str ) {
      if ( strnicmp(str, "KW", 2) == 0 ) {
         weekyr = true;
         str += 2;
         while ( isspace(*str) )
            str++;
      }
      f1 = strtol(str, &end, 10);
      if ( end && strchr(term, *end) != NULL ) {
         str = end + 1;
         if ( *str != '\0' ) {
            f2 = strtol(str, &end, 10);
            if ( end && strchr(term, *end) != NULL ) {
               str = end + 1;
               if ( *str != '\0' )
                  f3 = strtol(str, &end, 10);
            }
         }
      }
   }

   if ( weekyr ) {
      if ( f1 < 1 || f1 > 52 ) f1 = getWeek();
      if ( f2 < 0 ) f2 = getYear();
      jd = cDate(f2, f1).getJulianDate();
   } else {
      if ( f1 < 1 || f1 > 31 ) f1 = getDay();
      if ( f2 < 1 || f2 > 12 ) f2 = getMonth();
      if ( f3 < 0 ) f3 = getYear();
      jd = getJulianDate(f3,f2,f1);
   }
}


// get & set
// ---------------------------------------------------------------------------

int cDate::getDay() const
{
   int d, m, y;
   getCalendar(jd, y,m,d);
   return d;
}

int cDate::getMonth() const
{
   int d, m, y;
   getCalendar(jd, y,m,d);
   return m;
}

int cDate::getYear() const
{
   int d, m, y;
   getCalendar(jd, y,m,d);
   return y;
}

cString cDate::getStr() const
{
   int d, m, y;
   getCalendar(jd, y,m,d);
   return cStringf("%02d.%02d.%04d",d,m,y);
}


int cDate::getYearDay() const
{
   int d,m,y;
   getCalendar(jd, y,m,d);
   int jd_jan1 = getJulianDate(y,1,1);
   return jd - jd_jan1;
}


int cDate::getMonthLength(int year, int month)
{
   return getJulianDate(year,month+1,1) - getJulianDate(year,month,1);
}

int cDate::getMonthLength() const
{
   int d,m,y;
   getCalendar(jd, y,m,d);
   return getMonthLength(y,m);
}


int cDate::getYearLength(int year)
{
   return getJulianDate(year+1,1,1) - getJulianDate(year,1,1);
}

int cDate::getYearLength() const
{
   int d,m,y;
   getCalendar(jd, y,m,d);
   return getYearLength(y);
}

int cDate::getWeek() const
{
   int d,m,y;
   getCalendar(jd, y,m,d);
   int jd_jan1 = getJulianDate(y,1,1);
   return (jd - jd_jan1 + (jd_jan1 % 7)) / 7 + 1;
}

cDate cDate::getMasked(bool year, bool month, bool day) const
{
   int d,m,y;
   getCalendar(jd, y,m,d);

   if ( !year )  y = 2000;
   if ( !month ) m = 1;
   if ( !day )   d = 1;

   return cDate(y,m,d);
}

cDate cDate::getMasked(int mask) const
{
   int d,m,y;
   getCalendar(jd, y,m,d);

   if ( !(mask & mskYear) )  y = 2000;
   if ( !(mask & mskMonth) ) m = 1;
   if ( !(mask & mskDay) )   d = 1;

   return cDate(y,m,d);
}

cString cDate::getWeekdayStr(int weekday)
{
   static char *names[7] = {
      "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag", "Sonntag"
   };
   return names[(unsigned)weekday % 7];
}

cString cDate::getMonthStr(int month)
{
   static char *names[12] = {
      "Januar", "Februar", "März", "April", "Mai", "Juni",
      "Juli", "August", "September", "Oktober", "November", "Dezember"
   };

   return names[(unsigned)(month-1) % 12];
}


// Umwandlungen
// ---------------------------------------------------------------------------

cDate cDate::conv(const time_t& tstamp)
{
   struct tm *ts = localtime(&tstamp);
   return cDate(ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday);
}

time_t cDate::conv(const cDate& date)
{
   struct tm ts;
   ts.tm_sec = ts.tm_min = ts.tm_hour = 0;
   ts.tm_isdst = -1;
   ts.tm_mday = date.getDay();
   ts.tm_mon  = date.getMonth() - 1;
   ts.tm_year = date.getYear() - 1900;
   return mktime(&ts);
}


// Sonstiges
// ---------------------------------------------------------------------------

cDate &cDate::operator=(const cDateTime &other)
{
   *this = other.getDate(); return *this;
}

cDate cDate::addMonths(int months) const
{
   int d,m,y;
   getCalendar(jd, y,m,d);

   if (months >= 0) {
      y += months / 12;
      m += months % 12;
      if (m > 12) {
         y++; m -= 12;
      }
   } else {
      y -= -months / 12;
      m -= -months % 12;
      if (m < 1) {
         y--; m += 12;
      }
   }
   return cDate(y,m,d);
}




#ifdef __INTERFACE__

// ===========================================================================
// Declaration cTime
// ---------------------------------------------------------------------------
//
// cBase
//  +--cTime - Uhrzeit (an Sekunden orientiert)
//
// ===========================================================================

class __ECL_DLLEXPORT__ cTime : public cBase {

public:
   // Uhrzeit ueber aktuelle Uhrzeit erzeugen
   cTime();
   // Uhrzeit ueber Sekunden seit Mitternacht erzeugen
   cTime(int daysec);
   // Uhrzeit ueber Stunde, Minute und Sekunde erzeugen
   cTime(int hour, int min, int sec = 0);
   // Uhrzeit ueber Textform erzeugen
   cTime(const char *str);

   // Uhrzeit ueber cDateTime erzeugen
   cTime(const cDateTime &other);
   // Zuweisungsoperatoren
   cTime &operator=(const cDateTime &other);

   // Stunde ermitteln (0..23)
   int getHour() const
      { return (ts % TIC_DAY) / TIC_HOUR; }
   // Minute ermitteln (0..59)
   int getMin() const
      { return (ts % TIC_HOUR) / TIC_MIN; }
   // Sekunde ermitteln (0..59)
   int getSec() const
      { return (ts % TIC_MIN) / TIC_SEC; }
   // Liefert das Standard-Textformat (HH:MM:SS)
   cString getStr() const
      { return cStringf("%02d:%02d:%02d", getHour(), getMin(), getSec()); }


   // Vergleichsoperatoren
   // ====================

   // Vergleichsoperatoren (Direktvergleich der internen Darstellung)
   int operator==(const cTime& other) const
      { return ts == other.ts; }
   int operator!=(const cTime& other) const
      { return ts != other.ts; }
   int operator<(const cTime& other) const
      { return ts < other.ts; }
   int operator<=(const cTime& other) const
      { return ts < other.ts; }
   int operator>(const cTime& other) const
      { return ts < other.ts; }
   int operator>=(const cTime& other) const
      { return ts < other.ts; }


   // Abstaende zwischen Uhrzeiten
   // ============================

   // Sekunden zwischen zwei Uhrzeiten
   int operator-(const cTime& other) const
      { return (ts - other.ts); }
   // Sekunden zwischen zwei Uhrzeiten
   int getSecsTo(const cTime& other) const
      { return (ts - other.ts); }
   // Minuten zwischen zwei Uhrzeiten
   int getMinsTo(const cTime& other) const
      { return (ts - other.ts) / 60; }
   // Stunden zwischen zwei Uhrzeiten
   int getHoursTo(const cTime& other) const
      { return (ts - other.ts) / 3600; }


   // Uhrzeitarithmetik
   // =================

   // Sekunden von Uhrzeit subtrahieren
   cTime operator-(int secs) const
      { return cTime(ts - secs); }
   // Sekunden zu Uhrzeit addieren
   cTime operator+(int secs) const
      { return cTime(ts + secs); }
   // Sekunden zu Uhrzeit addieren
   cTime addSecs(int secs) const
      { return cTime(ts + secs); }
   // Minuten zu Uhrzeit addieren
   cTime addMins(int mins) const
      { return cTime(ts + mins * 60); }
   // Stunden zu Uhrzeit addieren
   cTime addHours(int hours) const
      { return cTime(ts + hours * 3600); }


   // Maskieren
   // =========

   enum MASKS {
      mskHour  = 0x0004,
      mskMin   = 0x0002,
      mskSec   = 0x0001
   };

   // Liefert die maskierte Uhrzeit (Komponenten mit 'false' haben Defaultwerte)
   cTime getMasked(bool hour, bool min, bool sec) const;
   // Liefert die maskierte Uhrzeit (Bitmaske, Bits 2..0 = HMS)
   cTime getMasked(int mask) const;


   // Umwandlung
   // ==========

   // Umwandlung cTime <- time_t
   static cTime conv(const time_t& tstamp);
   // Umwandlung time_t <- cTime
   static time_t conv(const cTime& time);


   // Sonstiges
   // =========

   // Sekunde am Tag ermitteln (0..86399)
   int getDaySec() const
      { return ts; }

private:
   enum {
      TIC_SEC = 1,
      TIC_MIN = TIC_SEC * 60,
      TIC_HOUR = TIC_MIN * 60,
      TIC_DAY = TIC_HOUR *24
   };
   int ts;
};

#endif /*__INTERFACE__*/




// Implementierung cTime
// ===========================================================================
// Interne Darstellung: Sekunden seit 00:00:00
//
// Die Kodierung basiert auf Konstanten und sollte bei Notwendigkeit z.B.
// auch auf 1/100 sec seit Mitternacht umgestellt werden koennen. In dem Fall
// wuerde es sich anbieten, z.B. die Arithmetik durch Varianten mit double fuer
// die Sekunden zu ergaenzen.

#define MAKE_TIME(h,m,s) ((h)*TIC_HOUR + (m)*TIC_MIN + (s)*TIC_SEC)


// Konstruktion
// ---------------------------------------------------------------------------

cTime::cTime()
{
   time_t now = time(0);
   struct tm * local = localtime(&now);
   ts = (unsigned)MAKE_TIME(local->tm_hour, local->tm_min, local->tm_sec) % TIC_DAY;
}

cTime::cTime(int daysec)
{
   ts = (unsigned)daysec % TIC_DAY;
}

cTime::cTime(int hour, int min, int sec)
{
   ts = (unsigned)MAKE_TIME(hour, min, sec) % TIC_DAY;
}

cTime::cTime(const cDateTime &datetime)
{
   *this = datetime.getTime();
}

// Diesen merkwuerdigen Konstruktor hab ich aus der alten cTime-Klasse
// uebernommen und nur ein wenig angepasst ... ohne Gewaehr!
cTime::cTime(const char *str)
{
   *this = cTime();

   char *end = NULL;
   static char term[] = ",.:/";
   int f1 = -1, f2 = -1, f3 = -1;

   if ( str ) {
      f1 = strtol(str, &end, 10);
      if ( end && strchr(term, *end) != NULL ) {
         str = end + 1;
         f2 = strtol(str, &end, 10);
         if ( end && strchr(term, *end) != NULL ) {
            str = end + 1;
            f3 = strtol(str, &end, 10);
         }
      }
   }

   if ( f1 < 0 || f1 > 23 ) f1 = getHour();
   if ( f2 < 0 || f2 > 59 ) f2 = getMin();
   if ( f3 < 0 || f3 > 59 ) f3 = getSec();
   ts = MAKE_TIME(f1, f2, f3);
}


// get & set
// ---------------------------------------------------------------------------

cTime cTime::getMasked(bool hour, bool min, bool sec) const
{
   int h = hour ? getHour() : 0;
   int m = min  ? getMin()  : 0;
   int s = sec  ? getSec()  : 0;

   return cTime(h,m,s);
}

cTime cTime::getMasked(int mask) const
{
   int h = mask & mskHour ? getHour() : 0;
   int m = mask & mskMin  ? getMin()  : 0;
   int s = mask & mskSec  ? getSec()  : 0;

   return cTime(h,m,s);
}


// Umwandlungen
// ---------------------------------------------------------------------------

cTime cTime::conv(const time_t& tstamp)
{
   struct tm *ts = localtime(&tstamp);
   return cTime(ts->tm_hour, ts->tm_min, ts->tm_sec);
}

time_t cTime::conv(const cTime& time)
{
   struct tm ts;
   ts.tm_mday = ts.tm_mon = ts.tm_year = 0;
   ts.tm_isdst = -1;
   ts.tm_hour = time.getHour();
   ts.tm_min  = time.getMin();
   ts.tm_sec  = time.getSec();
   return mktime(&ts);
}


// Sonstiges
// ---------------------------------------------------------------------------

cTime &cTime::operator=(const cDateTime &other)
{
   *this = other.getTime(); return *this;
}




#ifdef __INTERFACE__

// ===========================================================================
// Declaration cDateTime
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDateTime - Zeitstempel (Datum und Uhrzeit)
//
// ===========================================================================

class __ECL_DLLEXPORT__ cDateTime : public cBase {

public:
   // Initialisierung ueber aktuelles Datum/Uhrzeit
   cDateTime() :
      date(),time() {}
   // Initialisierung ueber direkte Angabe (Jahreszahl 2- oder 4-stellig)
   cDateTime(int year, int month, int day, int hour, int min, int sec=0) :
      date(year,month,day),time(hour,min,sec) {}
   // Initialisierung ueber cDate und cTime
   cDateTime(const cDate &d, const cTime &t) :
      date(d),time(t) {}
   // Initialisierung ueber time_t
   cDateTime(time_t time);
   // Initialisierung ueber Julianisches Datum
   cDateTime(double jd);

   // Initialisierung ueber cDate & 00:00:00h
   cDateTime(const cDate &d) :
      date(d),time((int)0) {}
   // Zuweisungsoperator cDate & 00:00:00h
   cDateTime &operator=(const cDate &other)
      { *this = cDateTime(other); return *this; }

   // Initialisierung ueber cTime & aktuelles Datum
   cDateTime(const cTime &t) :
      date(),time(t) {}
   // Zuweisungsoperator cTime & aktuelles Datum
   cDateTime &operator=(const cTime &other)
      { *this = cDateTime(other); return *this; }

   // Zeitstempel ueber Textform erzeugen
   cDateTime(const char *str);
   // Liefert das Standard-Textformat (TT.MM.JJJJ HH:MM:SS)
   cString getStr() const
      { return date.getStr() + " " + time.getStr(); }


   // Datum
   // =====

   // Datumskomponente ermitteln
   const cDate &getDate() const
      { return date; }
   // Tag ermitteln (1..31)
   int getDay() const
      { return date.getDay(); }
   // Monat ermitteln (1..12)
   int getMonth() const
      { return date.getMonth(); }
   // Jahr ermitteln (nur 4-stellig)
   int getYear() const
      { return date.getYear(); }
   // Liefert das Standard-Textformat des Datums (TT.MM.JJJJ)
   cString getDateStr() const
      { return date.getStr(); }


   // Zeit
   // ====

   const cTime &getTime() const
      { return time; }
   // Stunde ermitteln (0..24)
   int getHour() const
      { return time.getHour(); }
   // Minute ermitteln (0..59)
   int getMin() const
      { return time.getMin(); }
   // Sekunde ermitteln (0..59)
   int getSec() const
      { return time.getSec(); }
   // Liefert das Standard-Textformat der Uhrzeit (HH:MM:SS)
   cString getTimeStr() const
      { return time.getSec(); }


   // Vergleichsoperatoren
   // ====================

   int operator==(const cDateTime& other) const
      { return (*this - other) == 0; }
   int operator!=(const cDateTime& other) const
      { return (*this - other) != 0; }
   int operator<(const cDateTime& other) const
      { return (*this - other) < 0; }
   int operator<=(const cDateTime& other) const
      { return (*this - other) <= 0; }
   int operator>(const cDateTime& other) const
      { return (*this - other) > 0; }
   int operator>=(const cDateTime& other) const
      { return (*this - other) >= 0; }


   // Abstaende zwischen Zeitstempeln
   // ===============================

   // Sekunden zwischen zwei Zeitstempeln
   long operator-(const cDateTime& other) const
      { return (date - other.date) * 86400 + (time - other.time); }
   // Sekunden zwischen zwei Zeitstempeln
   long getSecsTo(const cDateTime& other) const
      { return (*this - other); }
   // Minuten zwischen zwei Zeitstempeln
   long getMinsTo(const cDateTime& other) const
      { return (*this - other) / 60; }
   // Stunden zwischen zwei Zeitstempeln
   long getHoursTo(const cDateTime& other) const
      { return (*this - other) / 3600; }
   // Tage zwischen zwei Zeitstempeln
   int getDaysTo(const cDateTime& other) const
      { return date - other.date; }
   // Wochen zwischen zwei Zeitstempeln
   int getWeeksTo(const cDateTime& other) const
      { return (date - other.date) / 7; }
   // Monate zwischen zwei Zeitstempeln
   int getMonthsTo(const cDateTime& other) const
      { return date.getMonthsTo(other.date); }
   // Jahre zwischen zwei Zeitstempeln
   int getYearsTo(const cDateTime& other) const
      { return date.getYearsTo(other.date); }


   // Zeitstempelarithmetik
   // =====================

   // Sekunden zum Zeitstempel addieren
   cDateTime addSecs(long secs) const;
   // Minuten zum Zeitstempel addieren
   cDateTime addMins(long mins) const
      { return addSecs(mins * 60); }
   // Stunden zum Zeitstempel addieren
   cDateTime addHours(long hours) const
      { return addSecs(hours * 3600); }
   // Tage zum Zeitstempel addieren
   cDateTime addDays(int days) const
      { return cDateTime(date + days, time); }
   // Wochen zum Zeitstempel addieren
   cDateTime addWeeks(int weeks) const
      { return addDays(weeks * 7); }
   // Monate zum Zeitstempel addieren
   cDateTime addMonths(int months) const
      { return cDateTime(date.addMonths(months),time); }
   // Jahre zum Zeitstempel addieren
   cDateTime addYears(int years) const
      { return addMonths(years * 12); }


   // Julianisches Datum (incl. Uhrzeit)
   // ==================================

   // Julianisches Datum
   double getJulianDate() const
      { return (double)time.getDaySec()/86400 + date.getJulianDate() - 0.5; }


   // Maskieren
   // =========

   enum MASKS {
      mskYear  = 0x0020,
      mskMonth = 0x0010,
      mskDay   = 0x0008,
      mskHour  = 0x0004,
      mskMin   = 0x0002,
      mskSec   = 0x0001
   };

   // Liefert den maskierten Zeitstempel (Komponenten mit 'false' haben Defaultwerte)
   cDateTime getMasked(bool year, bool month, bool day, bool hour, bool min, bool sec) const
      { return cDateTime( getDate().getMasked(year, month, day),
                          getTime().getMasked(hour, min, sec) ); }
   // Liefert den maskierten Zeitstempel (Bitmaske, Bits 5..0 = YMDHMS)
   cDateTime getMasked(int mask) const
      { return cDateTime( getDate().getMasked(mask),
                          getTime().getMasked(mask) ); }


   // Umwandlung
   // ==========

   // Umwandlung cDateTime <- time_t
   static cDateTime conv(const time_t& tstamp);
   // Umwandlung time_t <- cDateTime
   static time_t conv(const cDateTime& datetime);


private:
   cDate date;
   cTime time;
};

#endif /*__INTERFACE__*/




// Implementierung cDateTime
// ===========================================================================
// Interne Darstellung: Komponenten cDate und cTime
//
// ### Anmerkungen zur Umstellung:
// -  Die Funktionalitaeten der alten Basisklasse wurde auf cDate & cTime
//    verteilt. Wo es sinnvoll erschien, gibt es ein doppeltes Interface.
// -  z.B. bei wochenbasierten schien es nicht notwendig.


cDateTime::cDateTime(time_t tstamp)
{
   date = cDate::conv(tstamp);
   time = cTime::conv(tstamp);
}

cDateTime::cDateTime(double jd)
{
   jd += 0.5;
   date = cDate((long)jd);
   time = cTime((int)((jd-floor(jd))*86400));
}

cDateTime::cDateTime(const char *str) :
   date(str), time(strchr(str, ' '))
{
   // Hey! Q&D programming @ its best!
}

cDateTime cDateTime::addSecs(long secs) const
{
   secs += time.getDaySec();
   int day_diff = (int)floor((double)(secs)/86400);
   int time_rest = secs - day_diff*86400;

   return cDateTime(date + day_diff, cTime(time_rest));
}


// Umwandlungen
// ---------------------------------------------------------------------------

cDateTime cDateTime::conv(const time_t& tstamp)
{
   struct tm *ts = localtime(&tstamp);
   return cDateTime(ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday,
                    ts->tm_hour, ts->tm_min, ts->tm_sec);
}

time_t cDateTime::conv(const cDateTime& datetime)
{
   struct tm ts;
   ts.tm_isdst = -1;
   ts.tm_mday = datetime.getDay();
   ts.tm_mon  = datetime.getMonth() - 1;
   ts.tm_year = datetime.getYear() - 1900;
   ts.tm_hour = datetime.getHour();
   ts.tm_min  = datetime.getMin();
   ts.tm_sec  = datetime.getSec();
   return mktime(&ts);
}




// ===========================================================================
// Declaration cCalendar
// ---------------------------------------------------------------------------
//
// cBase
// +--cDate
//    +--cCalendar
//
// - Ableitung von cDate
// - Markiert zusaetzlich Feiertage (Ostern, Weihnachten, Tashas Geburtstag)
// - Der standard "Feiertagsdatenbase" koennen neue Termine angelernt werden
// - Lokalisierung? Ohoh! Feiertagsnamen sollten erfragbar sein ...
//
// ===========================================================================



