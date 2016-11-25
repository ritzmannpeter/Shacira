//## begin module%3ABA3DF202B1.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ABA3DF202B1.cm

//## begin module%3ABA3DF202B1.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3ABA3DF202B1.cp

//## Module: cTimer%3ABA3DF202B1; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cTimer.cpp

//## begin module%3ABA3DF202B1.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3ABA3DF202B1.additionalIncludes

//## begin module%3ABA3DF202B1.includes preserve=yes
//## end module%3ABA3DF202B1.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cTimer
#include "Control/Cell/Programs/cTimer.h"
// cProgram
#include "Control/Cell/Programs/cProgram.h"
//## begin module%3ABA3DF202B1.additionalDeclarations preserve=yes
//## end module%3ABA3DF202B1.additionalDeclarations


// Class cTimer 



cTimer::cTimer()
  //## begin cTimer::cTimer%.hasinit preserve=no
      : _Program(NULL)
  //## end cTimer::cTimer%.hasinit
  //## begin cTimer::cTimer%.initialization preserve=yes
  //## end cTimer::cTimer%.initialization
{
  //## begin cTimer::cTimer%.body preserve=yes
   _Name = "cTimer";
  //## end cTimer::cTimer%.body
}

cTimer::cTimer(const cTimer &right)
  //## begin cTimer::cTimer%copy.hasinit preserve=no
      : _Program(NULL)
  //## end cTimer::cTimer%copy.hasinit
  //## begin cTimer::cTimer%copy.initialization preserve=yes
  //## end cTimer::cTimer%copy.initialization
{
  //## begin cTimer::cTimer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTimer::cTimer%copy.body
}

cTimer::cTimer (cProgram *program, cConfigurationObject *config_obj)
  //## begin cTimer::cTimer%985267674.hasinit preserve=no
      : _Program(NULL)
  //## end cTimer::cTimer%985267674.hasinit
  //## begin cTimer::cTimer%985267674.initialization preserve=yes
  //## end cTimer::cTimer%985267674.initialization
{
  //## begin cTimer::cTimer%985267674.body preserve=yes
_ASSERT_COND(program != NULL)
_ASSERT_COND(config_obj != NULL)
   _Name = "cTimer";
   _Program = program;
   _IdleTime = config_obj->PropertyValue("IdleTime", _IdleTime);
  //## end cTimer::cTimer%985267674.body
}


cTimer::~cTimer()
{
  //## begin cTimer::~cTimer%.body preserve=yes
  //## end cTimer::~cTimer%.body
}



//## Other Operations (implementation)
INT_T cTimer::ControlFunc ()
{
  //## begin cTimer::ControlFunc%985267675.body preserve=yes
CONTROLFUNC_PROLOG(_Name.c_str())
   CheckTimers();
   _Program->TimerEvent();
   return 0;
CONTROLFUNC_EPILOG
  //## end cTimer::ControlFunc%985267675.body
}

BOOL_T cTimer::CreateTimer (CONST_STRING_T name)
{
  //## begin cTimer::CreateTimer%985677026.body preserve=yes
   _TimerMap[name] = -1;
   return true;
  //## end cTimer::CreateTimer%985677026.body
}

void cTimer::SetTimer (CONST_STRING_T name, LONG_T value)
{
  //## begin cTimer::SetTimer%985677027.body preserve=yes
   long timer_value = value / _IdleTime;
   _TimerMap[name] = timer_value;
  //## end cTimer::SetTimer%985677027.body
}

BOOL_T cTimer::TimerExpired (CONST_STRING_T name)
{
  //## begin cTimer::TimerExpired%985677028.body preserve=yes
   long timer_value = _TimerMap[name];
   return (timer_value < 0) ? true : false;
  //## end cTimer::TimerExpired%985677028.body
}

void cTimer::CheckTimers ()
{
  //## begin cTimer::CheckTimers%985677032.body preserve=yes
   TIMER_MAP_T::const_iterator i = _TimerMap.begin();
   while (i != _TimerMap.end()) {
      long timer_value = (*i).second;
      if (timer_value == 0) {
         _Program->TimerEvent((*i).first.c_str());
      }
      i++;
   }
   TIMER_MAP_T::iterator j = _TimerMap.begin();
   while (j != _TimerMap.end()) {
      (*j).second--;
      j++;
   }
  //## end cTimer::CheckTimers%985677032.body
}

// Additional Declarations
  //## begin cTimer%3ABA3DF202B1.declarations preserve=yes
  //## end cTimer%3ABA3DF202B1.declarations

//## begin module%3ABA3DF202B1.epilog preserve=yes
//## end module%3ABA3DF202B1.epilog
