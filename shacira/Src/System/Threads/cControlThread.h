//## begin module%3AA342FA00A3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AA342FA00A3.cm

//## begin module%3AA342FA00A3.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AA342FA00A3.cp

//## Module: cControlThread%3AA342FA00A3; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Threads\cControlThread.h

#ifndef cControlThread_h
#define cControlThread_h 1

//## begin module%3AA342FA00A3.includes preserve=yes
//## end module%3AA342FA00A3.includes

// eb_thread
#include "base/eb_thread.hpp"
// cStaticObject
#include "System/Objects/cStaticObject.h"

class __DLL_EXPORT__ cObjectLock;

//## begin module%3AA342FA00A3.additionalDeclarations preserve=yes

class cControlThread;
typedef std::map<unsigned long, cControlThread*> THREAD_MAP_T;

//## end module%3AA342FA00A3.additionalDeclarations


//## begin cControlThread%3AA342FA00A3.preface preserve=yes
//## end cControlThread%3AA342FA00A3.preface

//## Class: cControlThread%3AA342FA00A3
//## Category: System::Threads%3DC7FCF00004
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C68EC78000C;cObjectLock { -> F}

class __DLL_EXPORT__ cControlThread : public cThread, //## Inherits: <unnamed>%3AA343220303
                            	public cStaticObject  //## Inherits: <unnamed>%3FF01D44009C
{
  //## begin cControlThread%3AA342FA00A3.initialDeclarations preserve=yes
public:
  //## end cControlThread%3AA342FA00A3.initialDeclarations

    //## Constructors (generated)
      cControlThread();

      cControlThread(const cControlThread &right);

    //## Destructor (generated)
      virtual ~cControlThread();


    //## Other Operations (specified)
      //## Operation: Start%987504143
      virtual void Start ();

      //## Operation: Stop%987504144
      virtual void Stop ();

      virtual bool kill(bool wait = false);

      //## Operation: onEnter%983778320
      virtual BOOL_T onEnter (void *extra);

      //## Operation: onMain%983778321
      virtual INT_T onMain (void *extra);

      //## Operation: onLeave%983778322
      virtual void onLeave (INT_T rc);

      //## Operation: MainFunc%1012414868
      virtual INT_T MainFunc (void *extra);

      //## Operation: ControlFunc%983778325
      virtual INT_T ControlFunc ();

      //## Operation: Terminated%983778353
      BOOL_T Terminated ();

      //## Operation: Active%1072782023
      BOOL_T Active ();

      //## Operation: GetThreadById%997883622
      static cControlThread * GetThreadById (ULONG_T thread_id);

      //## Operation: GetThreadByName%1036575935
      static cControlThread * GetThreadByName (CONST_STRING_T thread_name);

      //## Operation: GetCurrentThreadID%1036575936
      static ULONG_T GetCurrentThreadID ();

      //## Operation: GetCurrentThread%1036575937
      static cControlThread * GetCurrentThread ();

      //## Operation: Started%1097160585
      BOOL_T Started ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ThreadId%3B7AAA810118
      ULONG_T get_ThreadId () const;

      //## Attribute: IdleTime%3AA3436D03E7
      ULONG_T get_IdleTime () const;
      void set_IdleTime (ULONG_T value);

      //## Attribute: TimeControl%45AB521403A9
      BOOL_T get_TimeControl () const;
      void set_TimeControl (BOOL_T value);

      //## Attribute: CycleTimeSet%45AB51EE0167
      ULONG_T get_CycleTimeSet () const;
      void set_CycleTimeSet (ULONG_T value);

      //## Attribute: CycleTime%45AB534400AB
      ULONG_T get_CycleTime () const;

      //## Attribute: CycleTimeMin%45AB523D0157
      ULONG_T get_CycleTimeMin () const;

      //## Attribute: CycleTimeMax%45AB525F02EE
      ULONG_T get_CycleTimeMax () const;

      //## Attribute: CycleTimeAverage%45AB5270009C
      DOUBLE_T get_CycleTimeAverage () const;

      ULONG_T get_CycleCount() const;

  public:
    // Additional Public Declarations
      //## begin cControlThread%3AA342FA00A3.public preserve=yes
      //## end cControlThread%3AA342FA00A3.public

  protected:
    // Data Members for Class Attributes

      //## begin cControlThread::ThreadId%3B7AAA810118.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ThreadId;
      //## end cControlThread::ThreadId%3B7AAA810118.attr

      //## begin cControlThread::IdleTime%3AA3436D03E7.attr preserve=no  public: ULONG_T {U} 1000
      ULONG_T _IdleTime;
      //## end cControlThread::IdleTime%3AA3436D03E7.attr

      //## begin cControlThread::TimeControl%45AB521403A9.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _TimeControl;
      //## end cControlThread::TimeControl%45AB521403A9.attr

      //## begin cControlThread::CycleTimeSet%45AB51EE0167.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _CycleTimeSet;
      //## end cControlThread::CycleTimeSet%45AB51EE0167.attr

      //## begin cControlThread::CycleTime%45AB534400AB.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _CycleTime;
      //## end cControlThread::CycleTime%45AB534400AB.attr

      //## begin cControlThread::CycleTimeMin%45AB523D0157.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _CycleTimeMin;
      //## end cControlThread::CycleTimeMin%45AB523D0157.attr

      //## begin cControlThread::CycleTimeMax%45AB525F02EE.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _CycleTimeMax;
      //## end cControlThread::CycleTimeMax%45AB525F02EE.attr

      //## begin cControlThread::CycleTimeAverage%45AB5270009C.attr preserve=no  public: DOUBLE_T {U} 0
      DOUBLE_T _CycleTimeAverage;
      //## end cControlThread::CycleTimeAverage%45AB5270009C.attr

      //## Attribute: CycleCount%45AB51A400BB
      //## begin cControlThread::CycleCount%45AB51A400BB.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _CycleCount;
      //## end cControlThread::CycleCount%45AB51A400BB.attr

      //## Attribute: Terminating%3FF15E2100CB
      //## begin cControlThread::Terminating%3FF15E2100CB.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Terminating;
      //## end cControlThread::Terminating%3FF15E2100CB.attr

      //## Attribute: Terminated%3AA344490357
      //## begin cControlThread::Terminated%3AA344490357.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Terminated;
      //## end cControlThread::Terminated%3AA344490357.attr

      //## Attribute: Started%3AC1B433030C
      //## begin cControlThread::Started%3AC1B433030C.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Started;
      //## end cControlThread::Started%3AC1B433030C.attr

      //## begin cControlThread::Threads%3FF0237B031C.attr preserve=no  implementation: static THREAD_MAP_T {U} 
      static THREAD_MAP_T _Threads;
      //## end cControlThread::Threads%3FF0237B031C.attr

    // Additional Protected Declarations
      //## begin cControlThread%3AA342FA00A3.protected preserve=yes
      //## end cControlThread%3AA342FA00A3.protected

  private:
    // Additional Private Declarations
      //## begin cControlThread%3AA342FA00A3.private preserve=yes
      //## end cControlThread%3AA342FA00A3.private

  private: //## implementation
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Threads%3FF0237B031C
      static THREAD_MAP_T get_Threads ();

    // Data Members for Class Attributes

      //## Attribute: ThreadMutex%3C68EC8C01A6
      //## begin cControlThread::ThreadMutex%3C68EC8C01A6.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _ThreadMutex;
      //## end cControlThread::ThreadMutex%3C68EC8C01A6.attr

      //## Attribute: StatReference%45AB528802DE
      //## begin cControlThread::StatReference%45AB528802DE.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _StatReference;
      //## end cControlThread::StatReference%45AB528802DE.attr

    // Additional Implementation Declarations
      //## begin cControlThread%3AA342FA00A3.implementation preserve=yes
      //## end cControlThread%3AA342FA00A3.implementation

};

//## begin cControlThread%3AA342FA00A3.postscript preserve=yes
//## end cControlThread%3AA342FA00A3.postscript

// Class cControlThread 

//## begin module%3AA342FA00A3.epilog preserve=yes
//## end module%3AA342FA00A3.epilog


#endif
