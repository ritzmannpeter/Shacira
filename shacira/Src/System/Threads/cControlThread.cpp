//## begin module%3AA342FA00A3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AA342FA00A3.cm

//## begin module%3AA342FA00A3.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AA342FA00A3.cp

//## Module: cControlThread%3AA342FA00A3; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Threads\cControlThread.cpp

//## begin module%3AA342FA00A3.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AA342FA00A3.additionalIncludes

//## begin module%3AA342FA00A3.includes preserve=yes

/// PR 12.01.07 - added property TimeControl to strictly control
///               cycle times (duration of ControlFunc is subtracted from
///               suspend value down to a minimum of 50 ms)
/// PR 14.02.11 - clarified thread implementation, added useful log messages

//## end module%3AA342FA00A3.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cControlThread
#include "System/Threads/cControlThread.h"
//## begin module%3AA342FA00A3.additionalDeclarations preserve=yes
//## end module%3AA342FA00A3.additionalDeclarations


// Class cControlThread 













//## begin cControlThread::Threads%3FF0237B031C.attr preserve=no  implementation: static THREAD_MAP_T {U} 
THREAD_MAP_T cControlThread::_Threads;
//## end cControlThread::Threads%3FF0237B031C.attr



cControlThread::cControlThread()
  //## begin cControlThread::cControlThread%.hasinit preserve=no
      : _ThreadId(0), _IdleTime(1000), _TimeControl(false), _CycleTimeSet(0), _CycleTime(0), _CycleTimeMin(0), _CycleTimeMax(0), _CycleTimeAverage(0), _CycleCount(0), _Terminating(false), _Terminated(false), _Started(false), _StatReference(0)
  //## end cControlThread::cControlThread%.hasinit
  //## begin cControlThread::cControlThread%.initialization preserve=yes
  //## end cControlThread::cControlThread%.initialization
{
  //## begin cControlThread::cControlThread%.body preserve=yes
  //## end cControlThread::cControlThread%.body
}

cControlThread::cControlThread(const cControlThread &right)
  //## begin cControlThread::cControlThread%copy.hasinit preserve=no
      : _ThreadId(0), _IdleTime(1000), _TimeControl(false), _CycleTimeSet(0), _CycleTime(0), _CycleTimeMin(0), _CycleTimeMax(0), _CycleTimeAverage(0), _CycleCount(0), _Terminating(false), _Terminated(false), _Started(false), _StatReference(0)
  //## end cControlThread::cControlThread%copy.hasinit
  //## begin cControlThread::cControlThread%copy.initialization preserve=yes
  //## end cControlThread::cControlThread%copy.initialization
{
  //## begin cControlThread::cControlThread%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cControlThread::cControlThread%copy.body
}


cControlThread::~cControlThread()
{
  //## begin cControlThread::~cControlThread%.body preserve=yes
   Stop();
  //## end cControlThread::~cControlThread%.body
}



//## Other Operations (implementation)
void cControlThread::Start ()
{
  //## begin cControlThread::Start%987504143.body preserve=yes
   cObjectLock __Lock__ (&_ThreadMutex);
   if (!_Started) {
      if (_Name.size() == 0) {
         _Name = "anonymous thread";
      }
      _Started = true;
      _Terminated = false;
      _Terminating = false;
      STRING_T starter_name = "Main";
      cControlThread * starter = GetCurrentThread();
      if (starter != NULL) {
         starter_name = starter->get_Name().c_str();
	  }
      InfoPrintf("starting %s by %s\n", _Name.c_str(), starter_name.c_str());
      BOOL_T success = start(teStart);
      if (success) {
         _ThreadId = getThreadId();
         _Threads[_ThreadId] = this;
         InfoPrintf("%s: Thread id %d started\n", _Name.c_str(), _ThreadId);
      } else {
         FatalPrintf("failed to start %s by %s\n", _Name.c_str(), starter_name.c_str());
         ExitProcess(-3, false);
      }
      waitFor(teStart);
   }
  //## end cControlThread::Start%987504143.body
}

void cControlThread::Stop ()
{
  //## begin cControlThread::Stop%987504144.body preserve=yes
   cObjectLock __Lock__ (&_ThreadMutex);
   if (!_Started) {
      return;
   }
   if (_Terminated) {
      return;
   }
   if (_Terminating) {
      waitFor(teEnd);
      return;
   }
   _Terminating = true;
   _Started = false;
   STRING_T stopper_name = "unknown";
   cControlThread * stopper = GetCurrentThread();
   if (stopper != NULL) {
      stopper_name = stopper->get_Name().c_str();
   }
   waitFor(teEnd);
   _Terminated = true;
   _Terminating = false;
   InfoPrintf("%s: Thread id %d stopped by %s\n", _Name.c_str(), _ThreadId, stopper_name.c_str());
   _Threads.erase(_ThreadId);
  //## end cControlThread::Stop%987504144.body
}

BOOL_T cControlThread::onEnter (void *extra)
{
  //## begin cControlThread::onEnter%983778320.body preserve=yes
   return true;
  //## end cControlThread::onEnter%983778320.body
}

INT_T cControlThread::onMain (void *extra)
{
  //## begin cControlThread::onMain%983778321.body preserve=yes
//   __try {
      int rc = 0;
      rc = MainFunc(extra);
      _Terminated = true;
      if (rc != 0) {
         FatalPrintf("thread %s abnormal termination rc=%d\n", _Name.c_str(), rc);
         ExitProcess(-2, false);
      }
      return 0;
//   } __except(ExceptionFilter(GetExceptionInformation())) {
//      FatalPrintf("unhandled structured exception in thread %s\n", _Name.c_str());
//      ExitProcess(-2, false);
//      return -2;
//   }
  //## end cControlThread::onMain%983778321.body
}

void cControlThread::onLeave (INT_T rc)
{
  //## begin cControlThread::onLeave%983778322.body preserve=yes
   if (rc != 0) {
      GenerateConsoleCtrlEvent(CTRL_C_EVENT, NULL);
   }
  //## end cControlThread::onLeave%983778322.body
}

INT_T cControlThread::MainFunc (void *extra)
{
  //## begin cControlThread::MainFunc%1012414868.body preserve=yes
MAINFUNC_PROLOG(_Name.c_str())
#define MIN_IDLE_TIME   50
   ULONG_T t0 = 0, t1 = 0;
   while (!(_Terminated || _Terminating)) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      if (_TimeControl) {
         t0 = cSystemUtils::RealtimeOffset();
      }
      ControlFunc();
      if (_TimeControl) {
         t1 = cSystemUtils::RealtimeOffset();
      }
MAINFUNC_LOOP_EPILOG
      if (!_Terminated) {
         if (_TimeControl) {
            int suspend = MIN_IDLE_TIME;
            ULONG_T duration = (t1 - t0);
            if (_CycleTimeSet > 0 &&
                duration > _CycleTimeSet) {
               if (_Name.size() > 0) {
                  ErrorPrintf("%s: cycle duration exceeded control (%d > %d)\n",
                              _Name.c_str(), duration, _CycleTimeSet);
               } else {
                  ErrorPrintf("unnamed thread %08.08x: cycle duration exceeded control (%d > %d)\n",
                     cSystemUtils::ThreadId(), duration, _CycleTimeSet);
               }
            }
            int rest = (_IdleTime - duration);
            if (rest > MIN_IDLE_TIME) {
               suspend = rest;
            } else {
               suspend = MIN_IDLE_TIME;
            }
            if (_CycleCount > 100) {
               if (duration > 0) {
                  _StatReference++;
                  if (duration > _CycleTimeMax) {
                     _CycleTimeMax = duration;
                  }
                  if (duration < _CycleTimeMin) {
                     _CycleTimeMin = duration;
                  }
                  _CycleTimeAverage = ((DOUBLE_T)(_CycleTimeAverage * (DOUBLE_T)_StatReference) + duration) / (_StatReference + 1);
               }
            } else {
               if (duration > 0) {
                  _CycleTimeAverage = _CycleTimeMin = _CycleTimeMax =  duration;
               }
            }
            _CycleTime = duration;
            cSystemUtils::Suspend(suspend);
         } else {
            cSystemUtils::Suspend(_IdleTime);
         }
         _CycleCount++;
      }
   }
MAINFUNC_EPILOG
   return 0;
  //## end cControlThread::MainFunc%1012414868.body
}

INT_T cControlThread::ControlFunc ()
{
  //## begin cControlThread::ControlFunc%983778325.body preserve=yes
   return 0;
  //## end cControlThread::ControlFunc%983778325.body
}

BOOL_T cControlThread::Terminated ()
{
  //## begin cControlThread::Terminated%983778353.body preserve=yes
   return _Terminated;
  //## end cControlThread::Terminated%983778353.body
}

BOOL_T cControlThread::Active ()
{
  //## begin cControlThread::Active%1072782023.body preserve=yes
   return !(_Terminating || _Terminated);
  //## end cControlThread::Active%1072782023.body
}

cControlThread * cControlThread::GetThreadById (ULONG_T thread_id)
{
  //## begin cControlThread::GetThreadById%997883622.body preserve=yes
   cControlThread * control_thread = NULL;
   THREAD_MAP_T::const_iterator thread = _Threads.find(thread_id);
   if (thread != _Threads.end()) {
      control_thread = (*thread).second;
      return control_thread;
   }
   return NULL;
  //## end cControlThread::GetThreadById%997883622.body
}

cControlThread * cControlThread::GetThreadByName (CONST_STRING_T thread_name)
{
  //## begin cControlThread::GetThreadByName%1036575935.body preserve=yes
   cControlThread * control_thread = NULL;
   THREAD_MAP_T::const_iterator thread = _Threads.begin();
   while (thread != _Threads.end()) {
      if (strcmp((*thread).second->get_Name().c_str(), thread_name) == 0) {
         control_thread = (*thread).second;
         break;
      }
      thread++;
   }
   return control_thread;
  //## end cControlThread::GetThreadByName%1036575935.body
}

ULONG_T cControlThread::GetCurrentThreadID ()
{
  //## begin cControlThread::GetCurrentThreadID%1036575936.body preserve=yes
   // obsolete and no more used
   unsigned long thread_id = cSystemUtils::ThreadId();
   return thread_id;
  //## end cControlThread::GetCurrentThreadID%1036575936.body
}

cControlThread * cControlThread::GetCurrentThread ()
{
  //## begin cControlThread::GetCurrentThread%1036575937.body preserve=yes
   unsigned long thread_id = cSystemUtils::ThreadId();
   return GetThreadById(thread_id);
  //## end cControlThread::GetCurrentThread%1036575937.body
}

BOOL_T cControlThread::Started ()
{
  //## begin cControlThread::Started%1097160585.body preserve=yes
   return _Started;
  //## end cControlThread::Started%1097160585.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cControlThread::get_ThreadId () const
{
  //## begin cControlThread::get_ThreadId%3B7AAA810118.get preserve=no
  return _ThreadId;
  //## end cControlThread::get_ThreadId%3B7AAA810118.get
}

ULONG_T cControlThread::get_IdleTime () const
{
  //## begin cControlThread::get_IdleTime%3AA3436D03E7.get preserve=no
  return _IdleTime;
  //## end cControlThread::get_IdleTime%3AA3436D03E7.get
}

void cControlThread::set_IdleTime (ULONG_T value)
{
  //## begin cControlThread::set_IdleTime%3AA3436D03E7.set preserve=no
  _IdleTime = value;
  //## end cControlThread::set_IdleTime%3AA3436D03E7.set
}

BOOL_T cControlThread::get_TimeControl () const
{
  //## begin cControlThread::get_TimeControl%45AB521403A9.get preserve=no
  return _TimeControl;
  //## end cControlThread::get_TimeControl%45AB521403A9.get
}

void cControlThread::set_TimeControl (BOOL_T value)
{
  //## begin cControlThread::set_TimeControl%45AB521403A9.set preserve=no
  _TimeControl = value;
  //## end cControlThread::set_TimeControl%45AB521403A9.set
}

ULONG_T cControlThread::get_CycleTimeSet () const
{
  //## begin cControlThread::get_CycleTimeSet%45AB51EE0167.get preserve=no
  return _CycleTimeSet;
  //## end cControlThread::get_CycleTimeSet%45AB51EE0167.get
}

void cControlThread::set_CycleTimeSet (ULONG_T value)
{
  //## begin cControlThread::set_CycleTimeSet%45AB51EE0167.set preserve=no
  _CycleTimeSet = value;
  //## end cControlThread::set_CycleTimeSet%45AB51EE0167.set
}

ULONG_T cControlThread::get_CycleTime () const
{
  //## begin cControlThread::get_CycleTime%45AB534400AB.get preserve=no
  return _CycleTime;
  //## end cControlThread::get_CycleTime%45AB534400AB.get
}

ULONG_T cControlThread::get_CycleTimeMin () const
{
  //## begin cControlThread::get_CycleTimeMin%45AB523D0157.get preserve=no
  return _CycleTimeMin;
  //## end cControlThread::get_CycleTimeMin%45AB523D0157.get
}

ULONG_T cControlThread::get_CycleTimeMax () const
{
  //## begin cControlThread::get_CycleTimeMax%45AB525F02EE.get preserve=no
  return _CycleTimeMax;
  //## end cControlThread::get_CycleTimeMax%45AB525F02EE.get
}

DOUBLE_T cControlThread::get_CycleTimeAverage () const
{
  //## begin cControlThread::get_CycleTimeAverage%45AB5270009C.get preserve=no
  return _CycleTimeAverage;
  //## end cControlThread::get_CycleTimeAverage%45AB5270009C.get
}

THREAD_MAP_T cControlThread::get_Threads ()
{
  //## begin cControlThread::get_Threads%3FF0237B031C.get preserve=no
  return _Threads;
  //## end cControlThread::get_Threads%3FF0237B031C.get
}

ULONG_T cControlThread::get_CycleCount () const
{
  return _CycleCount;
}

// Additional Declarations
  //## begin cControlThread%3AA342FA00A3.declarations preserve=yes
  //## end cControlThread%3AA342FA00A3.declarations

//## begin module%3AA342FA00A3.epilog preserve=yes
//## end module%3AA342FA00A3.epilog
