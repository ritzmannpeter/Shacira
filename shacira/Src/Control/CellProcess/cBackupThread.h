//## begin module%3AE85FA80391.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AE85FA80391.cm

//## begin module%3AE85FA80391.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AE85FA80391.cp

//## Module: cBackupThread%3AE85FA80391; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\CellProcess\cBackupThread.h

#ifndef cBackupThread_h
#define cBackupThread_h 1

//## begin module%3AE85FA80391.includes preserve=yes
//## end module%3AE85FA80391.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cSysProcess;
class __DLL_EXPORT__ cCellProcess;

//## begin module%3AE85FA80391.additionalDeclarations preserve=yes
//## end module%3AE85FA80391.additionalDeclarations


//## begin cBackupThread%3AE85FA80391.preface preserve=yes
//## end cBackupThread%3AE85FA80391.preface

//## Class: cBackupThread%3AE85FA80391
//## Category: Control::CellProcess%3A791D71001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AE861CE01B1;cConfigurationObject { -> F}
//## Uses: <unnamed>%3AE8649900FB;cSysProcess { -> F}

class __DLL_EXPORT__ cBackupThread : public cControlThread  //## Inherits: <unnamed>%3AE85FCA01D7
{
  //## begin cBackupThread%3AE85FA80391.initialDeclarations preserve=yes
public:
  //## end cBackupThread%3AE85FA80391.initialDeclarations

    //## Constructors (generated)
      cBackupThread();

      cBackupThread(const cBackupThread &right);

    //## Constructors (specified)
      //## Operation: cBackupThread%988306474
      cBackupThread (cCellProcess *process, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cBackupThread();


    //## Other Operations (specified)
      //## Operation: ControlFunc%988306475
      virtual INT_T ControlFunc ();

  public:
    // Additional Public Declarations
      //## begin cBackupThread%3AE85FA80391.public preserve=yes
      //## end cBackupThread%3AE85FA80391.public

  protected:
    // Data Members for Associations

      //## Association: Control::CellProcess::<unnamed>%3AE92B530184
      //## Role: cBackupThread::Process%3AE92B550278
      //## begin cBackupThread::Process%3AE92B550278.role preserve=no  public: cCellProcess {1 -> 1RFHN}
      cCellProcess *_Process;
      //## end cBackupThread::Process%3AE92B550278.role

    // Additional Protected Declarations
      //## begin cBackupThread%3AE85FA80391.protected preserve=yes
      //## end cBackupThread%3AE85FA80391.protected

  private:
    // Additional Private Declarations
      //## begin cBackupThread%3AE85FA80391.private preserve=yes
      //## end cBackupThread%3AE85FA80391.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Backup%988306476
      void Backup ();

      //## Operation: Copy%988306477
      void Copy (CONST_STRING_T source, CONST_STRING_T destination);

      //## Operation: ResetTicker%988356820
      void ResetTicker ();

      //## Operation: Tick%988356821
      void Tick ();

    // Data Members for Class Attributes

      //## Attribute: Hours%3AE8606C02CA
      //## begin cBackupThread::Hours%3AE8606C02CA.attr preserve=no  implementation: ULONG_T {U} 1
      ULONG_T _Hours;
      //## end cBackupThread::Hours%3AE8606C02CA.attr

      //## Attribute: Minutes%3AE860CA026B
      //## begin cBackupThread::Minutes%3AE860CA026B.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _Minutes;
      //## end cBackupThread::Minutes%3AE860CA026B.attr

      //## Attribute: Source%3AE860F7016C
      //## begin cBackupThread::Source%3AE860F7016C.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Source;
      //## end cBackupThread::Source%3AE860F7016C.attr

      //## Attribute: DestinationList%3AE8611000BD
      //## begin cBackupThread::DestinationList%3AE8611000BD.attr preserve=no  implementation: STRING_LIST_T {U} 
      STRING_LIST_T _DestinationList;
      //## end cBackupThread::DestinationList%3AE8611000BD.attr

      //## Attribute: HoursLeft%3AE86B9A0370
      //## begin cBackupThread::HoursLeft%3AE86B9A0370.attr preserve=no  implementation: ULONG_T {U} 
      ULONG_T _HoursLeft;
      //## end cBackupThread::HoursLeft%3AE86B9A0370.attr

      //## Attribute: MinutesLeft%3AE86BBC0026
      //## begin cBackupThread::MinutesLeft%3AE86BBC0026.attr preserve=no  implementation: ULONG_T {U} 
      ULONG_T _MinutesLeft;
      //## end cBackupThread::MinutesLeft%3AE86BBC0026.attr

      //## Attribute: SecondsLeft%3AE86BCB0136
      //## begin cBackupThread::SecondsLeft%3AE86BCB0136.attr preserve=no  implementation: ULONG_T {U} 
      ULONG_T _SecondsLeft;
      //## end cBackupThread::SecondsLeft%3AE86BCB0136.attr

    // Additional Implementation Declarations
      //## begin cBackupThread%3AE85FA80391.implementation preserve=yes
      //## end cBackupThread%3AE85FA80391.implementation

};

//## begin cBackupThread%3AE85FA80391.postscript preserve=yes
//## end cBackupThread%3AE85FA80391.postscript

// Class cBackupThread 

//## begin module%3AE85FA80391.epilog preserve=yes
//## end module%3AE85FA80391.epilog


#endif
