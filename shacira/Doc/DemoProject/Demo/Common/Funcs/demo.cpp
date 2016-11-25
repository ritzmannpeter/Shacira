
#include "FirstHeader.h"
#include "System/Database/cContext.h"
#include "System/Database/cVariable.h"
#include "System/cTimeObject.h"
#include "System/Database/cUnitDef.h"
#include "demo.h"

#define RDIV(A,B) ((A)+((B)>>1)) / (B)  /* Division, gerundet */ 

/*.Sf.***********************************************************************
*
*  FUNKTION:
*     way - Liefert die Wegdarstellung eines Wertes in Volumendarstellung
*
*  BESCHREIBUNG:
*
*                volume [0.01cm3]    4 volume [10 mm3]   4000 volume
*         way =  ---------------- = ------------------ = ----------- [0.01mm]
*                  ãDý/4 [mmý]          ãDý [mmý]            ãDý
*
*  AUFRUF:
*     result = way( volume, D );
*
*  PARAMETER:
*     result RESULT [long] - Wert in Wegdarstellung
*     volume IN [long] - Wert in Volumendarstellung
*     D IN [long] - Schneckendurchmesser in mm
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     ...
*
**.Ef.***********************************************************************/
static FLOAT_T way (FLOAT_T volume, long diameter)
{
   DOUBLE_T Q = 0;
   DOUBLE_T D = diameter;
   DOUBLE_T W = volume;
   D *= D*355;
//   Q = RDIV(D,452L);
Q = D / 452;
   W *= 100;
   FLOAT_T ret = (Q == 0L) ? 0 : (FLOAT_T)(W / Q);
   return ret;
}
 
static FLOAT_T vol (FLOAT_T way, long diameter)
{
   DOUBLE_T Q = 0;
   DOUBLE_T D = diameter;
   DOUBLE_T V = way;
   D *= D*355;
//   Q = RDIV(D,452L);
Q = D / 452;
   V /= 100;
   FLOAT_T ret = (Q == 0L) ? 0 : (FLOAT_T)(V * Q);
   return ret;
}
 

#include "System/Database/cUnitDef.h"

FLOAT_T Unit1(cContext * _context, FLOAT_T _value, ULONG_T _flags, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4,
    LONG_T fact)
{
   UCHAR_T source = GET_SOURCE(_flags);
   UCHAR_T destination = GET_DESTINATION(_flags);
   if (source == 0) {
      if (destination == 1) {
         if (fact != 0) {
            return _value / fact;
         }
      }
   } else if (source == 1) {
      if (destination == 0) {
         if (fact != 0) {
           return _value * fact;
         }
      }
   }
   return _value;
}

FLOAT_T ConvertWayVol(cContext * _context, FLOAT_T _value, ULONG_T _flags, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4,
    ULONG_T diameter)
{
   UCHAR_T source = GET_SOURCE(_flags);
   UCHAR_T destination = GET_DESTINATION(_flags);
   if (source == 0) {
      if (destination == 1) {
         if (diameter != 0) {
            return way(_value, diameter);
         }
      } else if (destination == 2) {
         // inches
         FLOAT_T mm = way(_value, diameter);
         return (FLOAT_T)(mm / 25.4);
      } else if (destination == 3) {
         // miles
         return (FLOAT_T)0.099;
      }
   } else if (source == 1) {
      if (destination == 0) {
         if (diameter != 0) {
            return vol(_value, diameter);
         }
      } else if (destination == 2) {
         // inches
         return (FLOAT_T)(_value / 25.4);
      } else if (destination == 3) {
         // miles
         return (FLOAT_T)0.099;
      }
   } else if (source == 2) {
      // inches
      if (destination == 0) {
         if (diameter != 0) {
            FLOAT_T way = (FLOAT_T)(_value * 25.4);
            return vol(way, diameter);
         }
      } else if (destination == 1) {
         // inches
         return (FLOAT_T)(_value * 25.4);
      } else if (destination == 2) {
         // inches
         return _value;
      } else if (destination == 3) {
         // miles
         return (FLOAT_T)0.099;
      }
   }
   return _value;
}

// implementation of max function MaxIndex
LONG_T MaxIndex(cContext * _context, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4, 
	LONG_T which)
{
   cVariable * variable = _context->Variable("matrix1");
   if (variable != NULL) {
      LONG_T dim_size = 0;
      if (which == 0) {
         dim_size = variable->DimSize(0);
      } else if (which == 1) {
         dim_size = variable->DimSize(1);
      } else {
         throw cError("invalid dimension", 0);
      }
      return dim_size - 1;
   }
   return 0;
}

// implementation of filter function filter1
LONG_T filter1(cContext * _context, LONG_T _value, ULONG_T _flags, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4, 
	LONG_T arg1)
{
   return 0;
}

LONG_T LangMax(cContext * _context, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4)
{
   return 3;
}

LONG_T LangMin(cContext * _context, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4)
{
   return 1;
}

FLOAT_T MMInchConversion(cContext * _context, FLOAT_T _value, ULONG_T _flags, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4)
{
   UCHAR_T source = (UCHAR_T)GET_SOURCE(_flags);
   UCHAR_T destination = (UCHAR_T)GET_DESTINATION(_flags);
   if (source != destination) {
      if (source == 0 ) {
         // mm
         if (destination == 1) {
            // inch
            return _value / (FLOAT_T)25.4;
         }
      } else if (source == 1) {
         // inch
         if (destination == 0) {
            // mm
            return _value * (FLOAT_T)25.4;
         }
      }
   }
   return _value;
}

LONG_T object_func(cContext * _context, LONG_T _value, ULONG_T _flags, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4, 
	LONG_T obj)
{
   return 0;
}



