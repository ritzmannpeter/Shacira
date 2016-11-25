//## begin module%43A694AB0122.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A694AB0122.cm

//## begin module%43A694AB0122.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A694AB0122.cp

//## Module: cInterval%43A694AB0122; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cInterval.cpp

//## begin module%43A694AB0122.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43A694AB0122.additionalIncludes

//## begin module%43A694AB0122.includes preserve=yes
//## end module%43A694AB0122.includes

// cInterval
#include "Control/Device/EM63/cInterval.h"
//## begin module%43A694AB0122.additionalDeclarations preserve=yes
#include "Control/Device/EM63/cEM63Interface.h"
//## end module%43A694AB0122.additionalDeclarations


// Class cInterval 




cInterval::cInterval()
  //## begin cInterval::cInterval%.hasinit preserve=no
      : _Interval(0), _Remaining(0), _LastCheck(0)
  //## end cInterval::cInterval%.hasinit
  //## begin cInterval::cInterval%.initialization preserve=yes
  //## end cInterval::cInterval%.initialization
{
  //## begin cInterval::cInterval%.body preserve=yes
   INCREMENT_OBJECT_COUNT()
   //## end cInterval::cInterval%.body
}

cInterval::cInterval(const cInterval &right)
  //## begin cInterval::cInterval%copy.hasinit preserve=no
      : _Interval(0), _Remaining(0), _LastCheck(0)
  //## end cInterval::cInterval%copy.hasinit
  //## begin cInterval::cInterval%copy.initialization preserve=yes
  //## end cInterval::cInterval%copy.initialization
{
  //## begin cInterval::cInterval%copy.body preserve=yes
   INCREMENT_OBJECT_COUNT()
   //## end cInterval::cInterval%copy.body
}

cInterval::cInterval (int interval)
  //## begin cInterval::cInterval%1134980245.hasinit preserve=no
      : _Interval(0), _Remaining(0), _LastCheck(0)
  //## end cInterval::cInterval%1134980245.hasinit
  //## begin cInterval::cInterval%1134980245.initialization preserve=yes
  //## end cInterval::cInterval%1134980245.initialization
{
  //## begin cInterval::cInterval%1134980245.body preserve=yes
   _Remaining = _Interval = interval;
   INCREMENT_OBJECT_COUNT()
   //## end cInterval::cInterval%1134980245.body
}

cInterval::cInterval (int hours, int minutes, int seconds)
  //## begin cInterval::cInterval%1134980248.hasinit preserve=no
      : _Interval(0), _Remaining(0), _LastCheck(0)
  //## end cInterval::cInterval%1134980248.hasinit
  //## begin cInterval::cInterval%1134980248.initialization preserve=yes
  //## end cInterval::cInterval%1134980248.initialization
{
  //## begin cInterval::cInterval%1134980248.body preserve=yes
   INCREMENT_OBJECT_COUNT()
   //## end cInterval::cInterval%1134980248.body
}


cInterval::~cInterval()
{
  //## begin cInterval::~cInterval%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cInterval::~cInterval%.body
}



//## Other Operations (implementation)
BOOL_T cInterval::Condition ()
{
  //## begin cInterval::Condition%1134980243.body preserve=yes
   cTimeObject t;
   ULONG_T now = t;
   ULONG_T diff = (now - _LastCheck);
   _Remaining -= diff;
   if (_Remaining <= 0) {
      _Remaining = _Interval;
      _LastCheck = now;
      return true;
   } else {
      _LastCheck = now;
      return false;
   }
  //## end cInterval::Condition%1134980243.body
}

// Additional Declarations
  //## begin cInterval%43A694AB0122.declarations preserve=yes
  //## end cInterval%43A694AB0122.declarations

//## begin module%43A694AB0122.epilog preserve=yes
//## end module%43A694AB0122.epilog
