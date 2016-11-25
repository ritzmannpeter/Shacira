
#include "FirstHeader.h"
#include "System/Database/cContext.h"
#include "System/Database/cVariable.h"
#include "System/cTimeObject.h"
#include "System/Database/cUnitDef.h"

ULONG_T Second(cContext * _context, ULONG_T _value, ULONG_T _flags, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4)
{
   static int second = 0;
   return second++;
}

