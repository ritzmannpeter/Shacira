//## begin module%438080340163.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%438080340163.cm

//## begin module%438080340163.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%438080340163.cp

//## Module: cEventlogCmd%438080340163; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cEventlogCmd.h

#ifndef cEventlogCmd_h
#define cEventlogCmd_h 1

//## begin module%438080340163.includes preserve=yes
//## end module%438080340163.includes

// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class cMutexSem;
class __DLL_EXPORT__ cAlarm;
class __DLL_EXPORT__ cDataChange;
class __DLL_EXPORT__ cObjectQueue;
class __DLL_EXPORT__ cEM63Program;
class __DLL_EXPORT__ cEM63Interface;

//## begin module%438080340163.additionalDeclarations preserve=yes
//## end module%438080340163.additionalDeclarations


//## begin cEventlogCmd%438080340163.preface preserve=yes
//## end cEventlogCmd%438080340163.preface

//## Class: cEventlogCmd%438080340163
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43BE4D8B0062;cEM63Interface { -> F}
//## Uses: <unnamed>%43BE86080386;cMutexSem { -> F}
//## Uses: <unnamed>%43BE897D02E4;cAlarm { -> F}
//## Uses: <unnamed>%43BE89850063;cDataChange { -> F}

class __DLL_EXPORT__ cEventlogCmd : public cPresentationCmd  //## Inherits: <unnamed>%4380820A00F3
{
  //## begin cEventlogCmd%438080340163.initialDeclarations preserve=yes
public:
  //## end cEventlogCmd%438080340163.initialDeclarations

    //## Constructors (generated)
      cEventlogCmd();

      cEventlogCmd(const cEventlogCmd &right);

    //## Constructors (specified)
      //## Operation: cEventlogCmd%1136548766
      cEventlogCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cEventlogCmd();


    //## Other Operations (specified)
      //## Operation: SetEvent%1136559696
      void SetEvent (cTransientObject *object);

      //## Operation: HandleEvents%1136559697
      void HandleEvents (BOOL_T clear);

      //## Operation: SetStartCondition%1136281475
      void SetStartCondition (cCondition *condition);

      //## Operation: SetStopCondition%1136281476
      void SetStopCondition (cCondition *condition);

      //## Operation: Process%1136457194
      virtual BOOL_T Process (cContext *context);

      //## Operation: Start%1136457195
      virtual BOOL_T Start ();

      //## Operation: Control%1136457196
      virtual void Control ();

      //## Operation: Stop%1136457197
      virtual void Stop ();

      //## Operation: IsEvent%1136286715
      virtual BOOL_T IsEvent ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: EventType%43BA4D80027E
      STRING_T get_EventType () const;
      void set_EventType (STRING_T value);

      //## Attribute: PresentationType%43BA4C7B02DF
      int get_PresentationType () const;
      void set_PresentationType (int value);

      //## Attribute: StartCondition%43BA4C7B02EF
      cCondition * get_StartCondition () const;
      void set_StartCondition (cCondition * value);

      //## Attribute: StopCondition%43BA4C7B02FE
      cCondition * get_StopCondition () const;
      void set_StopCondition (cCondition * value);

      //## Attribute: Count%43BEA53102D5
      ULONG_T get_Count () const;

  public:
    // Additional Public Declarations
      //## begin cEventlogCmd%438080340163.public preserve=yes
      //## end cEventlogCmd%438080340163.public

  protected:
    // Data Members for Class Attributes

      //## begin cEventlogCmd::EventType%43BA4D80027E.attr preserve=no  public: STRING_T {U} 
      STRING_T _EventType;
      //## end cEventlogCmd::EventType%43BA4D80027E.attr

      //## begin cEventlogCmd::PresentationType%43BA4C7B02DF.attr preserve=no  public: int {U} EM63_APPEND
      int _PresentationType;
      //## end cEventlogCmd::PresentationType%43BA4C7B02DF.attr

      //## begin cEventlogCmd::StartCondition%43BA4C7B02EF.attr preserve=no  public: cCondition * {U} NULL
      cCondition *_StartCondition;
      //## end cEventlogCmd::StartCondition%43BA4C7B02EF.attr

      //## begin cEventlogCmd::StopCondition%43BA4C7B02FE.attr preserve=no  public: cCondition * {U} NULL
      cCondition *_StopCondition;
      //## end cEventlogCmd::StopCondition%43BA4C7B02FE.attr

      //## begin cEventlogCmd::Count%43BEA53102D5.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Count;
      //## end cEventlogCmd::Count%43BEA53102D5.attr

    // Data Members for Associations

      //## Association: Control::Device::EM63::<unnamed>%43BE85AA0386
      //## Role: cEventlogCmd::EventQueue%43BE85AB0357
      //## begin cEventlogCmd::EventQueue%43BE85AB0357.role preserve=no  public: cObjectQueue { -> 0..1RFHN}
      cObjectQueue *_EventQueue;
      //## end cEventlogCmd::EventQueue%43BE85AB0357.role

    // Additional Protected Declarations
      //## begin cEventlogCmd%438080340163.protected preserve=yes
      //## end cEventlogCmd%438080340163.protected

  private:
    // Additional Private Declarations
      //## begin cEventlogCmd%438080340163.private preserve=yes
      //## end cEventlogCmd%438080340163.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: PrintCurrentAlarms%1136567370
      void PrintCurrentAlarms ();

      //## Operation: HandleAlarm%1136559699
      void HandleAlarm (cAlarm *alarm);

      //## Operation: HandleChange%1136559698
      void HandleChange (cDataChange *change);

      //## Operation: PrintAlarm%1136567368
      void PrintAlarm (cBufferedFile *file, cAlarm *alarm, BOOL_T print_state = true);

      //## Operation: PrintChange%1136567369
      void PrintChange (cBufferedFile *file, cDataChange *change);

    // Data Members for Class Attributes

      //## Attribute: QueueMutex%43BE86F00096
      //## begin cEventlogCmd::QueueMutex%43BE86F00096.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _QueueMutex;
      //## end cEventlogCmd::QueueMutex%43BE86F00096.attr

    // Additional Implementation Declarations
      //## begin cEventlogCmd%438080340163.implementation preserve=yes
      //## end cEventlogCmd%438080340163.implementation

};

//## begin cEventlogCmd%438080340163.postscript preserve=yes
//## end cEventlogCmd%438080340163.postscript

// Class cEventlogCmd 

//## begin module%438080340163.epilog preserve=yes
//## end module%438080340163.epilog


#endif
