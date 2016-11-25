/*--------------------------------------------------------------------------*/
/*                                                                          */
/* [date.c]                    Type: Date                                   */
/*                                                                          */
/* Copyright (c) 1994 by Lars D\olle, Heike Manns                           */
/*--------------------------------------------------------------------------*/

#include "standard.h"
#include "sink.h"

/*I---------------------------- The Type --------------------------------- */

/*!!
   The data type DATE is implemented as number of days since 01.01.0000.
   This origin date is represented by the number 0.

   The rules for the conversion of a date
     internal format <-->  external day/month/year-format
   rely on the Gregorian calendar:

   1) A normal year has 365 days, a leap year 366 days.
   2) All years, divisible by 4, are leap years, except
   3) the years, divisible by 100, this except
   4) the years, divisible by 400.
*/   

/*DOC_INTERFACE*/
typedef long Date; /* range DMY(01,01,0000) .. DMY(31,12,9999) */

#define D001 ((long) 365)
#define D004 ((D001) +  3 * ((D001) + 0))
#define D100 ((D004) + 24 * ((D004) + 1))
#define D400 ((D100) +  3 * ((D100) + 0))

#define MonthPerYear 12
static int DaysInMonth[2][MonthPerYear] =
/* Jan Feb M\ar Apr Mai Jun Jul Aug Sep Okt Nov Dez */
{ 
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31  }
};

static int DaysBeforeMonth[2][MonthPerYear];
static int MonthOfDayInYear[2][366];


/*I------------------------ Init ------------------------------------------ */

void date_init(void)
/* init date module */
{ int i,l;
  for (i = 0; i < MonthPerYear; i++)
    DaysInMonth[1][i] = DaysInMonth[0][i] + (i == 1); /* Feb in leap-year */
  for (l = 0; l <2; l++)
  { int j;
    DaysBeforeMonth[l][0] = 0;
    for (i = 1; i < MonthPerYear; i++)
      DaysBeforeMonth[l][i] = DaysBeforeMonth[l][i-1] + DaysInMonth[l][i-1];
    for (i = 0; i < MonthPerYear; i++)
      for (j = 0; j < DaysInMonth[l][i]; j++)
        MonthOfDayInYear[l][DaysBeforeMonth[l][i]+j] = i;
  }
}

/*I------------------------ Date operations ------------------------------- */

bool LeapYear(int Year)
/* whether 'Year' is a leap year */
{
  assert1(0 <= Year && Year <= 9999,"invalid year %d",Year);
  return (Year % 4 == 0) && ((Year % 100 != 0) || (Year % 400 == 0));
}

bool validDMY(int Day, int Month, int Year)
/* whether 'Day'.'Month'.'Year' is a valid date */
{
  return 0 <= Year  && Year  <= 9999
      && 1 <= Month && Month <= MonthPerYear
      && 1 <= Day   && Day   <= DaysInMonth[LeapYear(Year)][Month-1];
}

static int NumberOfLeapYears(int Year)
/* number of leap years between [0 .. 'Year'), exclusive 'Year' */
{
  return 1 + (Year / 4) - (Year / 100) + (Year / 400) - LeapYear(Year);
}

static long DaysBeforeYear(int Year)
/* number of days before 01.01.'Year' */
{
  return (D001) * Year + NumberOfLeapYears(Year);
}

Date DMY(int Day, int Month, int Year)
/* converts 'Day'.'Month'.'Year' into the internal date format */
{
  assert( validDMY(Day,Month,Year),
          "invalid date '%d.%d.%d'",Day,Month,Year );
  return DaysBeforeYear(Year)
       + DaysBeforeMonth[LeapYear(Year)][Month-1]
       + (Day-1);
}

static void splitDays(long *days, int *year, int *p, int px, long d, int y)
/* Zerlegung von Tagen in Jahresperioden. Hilfsfunktion f\ur Year(_). */
{
  if (*days < d + *p) return;
  *year += (*days - d - *p) / (d + px) * y + y;
  *days  = (*days - d - *p) % (d + px);
  *p     = px;
}

int Year(Date days)
/* year of 'days' ( result >= 0 ) */
{ int p = 1; int year = (days / (D400 + p)) * 400; days = (days % (D400 + p));
  splitDays(&days, &year, &p, 0, D100, 100);
  splitDays(&days, &year, &p, 1, D004,   4);
  splitDays(&days, &year, &p, 0, D001,   1);
  return year;
}

int Month(Date date)
/* month of 'date' ( result >= 1 ) */
{ int year = Year(date);
  return MonthOfDayInYear[LeapYear(year)][date-DaysBeforeYear(year)]+1;
}

int Day(Date date)
/* day of 'date' ( result >= 1 ) */
{ int year = Year(date); int month = Month(date)-1;
  return date-DaysBeforeYear(year)-DaysBeforeMonth[LeapYear(year)][month]+1;
}

int WeekDay(Date date)
/* weekday of 'date' ( sunday = 0, saturday = 6 ) */
{
  return (date + 6) % 7;
}

Date Today(void)
/* current date ( system clock ) */
{ time_t t = time(NULL);
  struct tm* today = localtime(&t);
  return DMY(today->tm_mday, today->tm_mon+1, today->tm_year+1900);
}

string CurTime(void)
/* current time ( system clock ); allocs memory */
{ time_t t = time(NULL);
  struct tm* today = localtime(&t);
  return 
    Str_printf("%02d:%02d:%02d",today->tm_hour,today->tm_min,today->tm_sec);
}

static string DayName[7] =
{
  "Sonntag",    "Montag",     "Dienstag",   "Mittwoch",   "Donnerstag",
  "Freitag",    "Samstag"
};

static string MonthName[12] =
{
  "Januar",    "Februar", "Maerz",      "April",
  "Mai",       "Juni",    "Juli",      "August",
  "September", "Oktober", "November",  "Dezember"
};

int MonthLength(int Month, int Year)
/* the number of days in month */
{
  assert( 0 <= Year  && Year  <= 9999 &&
          1 <= Month && Month <= MonthPerYear,
         "invalid month/year '%d.%d'",Month,Year);
  return DaysInMonth[LeapYear(Year)][Month-1];
}

#define DATE_OK(c) assert1((c),"'%s': wrong date format",date)

Date Str_Date(string date)
/* converts 'date' [ "dd.mm.yy" | "dd.mm.yyyy" ] 
   into the internal date format 
*/
{ string ds, ms, ys; Sink dig[3]; 
  int len = strlen(date), i, j, d, m, y;
  dig[0] = Sink_open(); dig[1] = Sink_open(); dig[2] = Sink_open();
  for( i=0, j=0; i < len; ++i )
  {
    DATE_OK(j < 3);
    if( date[i] == '.' ) ++j;
    else                 
    {
      DATE_OK(isdigit(date[i]));
      Sink_printf(dig[j],"%c",date[i]);
    }
  }
  ds = Sink_close(dig[0]); ms = Sink_close(dig[1]); ys = Sink_close(dig[2]);
  DATE_OK(j == 2); 
  DATE_OK(strlen(ds) > 0);
  DATE_OK(strlen(ms) > 0);
  DATE_OK(strlen(ys) > 0);
  y = ( strlen(ys) == 2 ) 
      ? ( Year(Today()) / 100 ) * 100 + atoi(ys) : atoi(ys);
  d = atoi(ds); m = atoi(ms);
  FreeMem(ds); FreeMem(ms); FreeMem(ys);
  return DMY(d,m,y);
}

string Date_Str(Date date)
/* converts 'date' to string type [ "tt.mm.jjjj" ]; allocs memory */
{
  return Str_printf("%02d.%02d.%04d",Day(date),Month(date),Year(date));
}

/*I------------------------ Debug ----------------------------------------- */

void pDate4(Date date)
/* print 'date' [ "tt.mm.jjjj" ] */
{
  fprintf(STDOUT,"%02d.%02d.%04d",Day(date),Month(date),Year(date));
}

void pDate2(Date date)
/* print 'date' [ "tt.mm.jj" ] */
{
  fprintf(STDOUT,"%02d.%02d.%02d",Day(date),Month(date),Year(date)%100);
}

void pDateS(Date date)
/* print 'date' [ "...Anno..." ] */
{
  fprintf(STDOUT,"%7ld. Tag, ein %10s der ",date, DayName[WeekDay(date)]);
  fprintf
  (
    STDOUT,"%2d. %8s Anno %4d",Day(date),MonthName[Month(date)-1],Year(date)
  );
}

/*INTERFACE_OFF*/
/*
tmain()
{
  date_init();
  fprintf(STDOUT,"------------");
  fprintf(STDOUT," Demonstration des Gregorianischen Kalenders ");
  fprintf(STDOUT,"------------");
  fprintf(STDOUT,"\n\n");
  fprintf(STDOUT,"Erster  Tag : "); pDateS(DMY(1,1,0));      NL;
  fprintf(STDOUT,"Dieser  Tag : "); pDateS(Today());         NL;
  fprintf(STDOUT,"Letzter Tag : "); pDateS(DMY(31,12,9999)); NL;
  fprintf(STDOUT,"Referenz 01 : "); pDateS(DMY(1,1,1800));   NL;
  fprintf(STDOUT,"Referenz 02 : "); pDateS(DMY(1,1,1900));   NL;
  fprintf(STDOUT,"Referenz 03 : "); pDateS(DMY(1,1,2000));   NL;
}
*/
/*INTERFACE_ON*/
