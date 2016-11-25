//## begin module%3AA36AF4035B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AA36AF4035B.cm

//## begin module%3AA36AF4035B.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3AA36AF4035B.cp

//## Module: cProgram%3AA36AF4035B; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cProgram.h

#ifndef cProgram_h
#define cProgram_h 1

//## begin module%3AA36AF4035B.includes preserve=yes
//## end module%3AA36AF4035B.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cLogFile;
class __DLL_EXPORT__ cIO;
class __DLL_EXPORT__ cInfo;
class __DLL_EXPORT__ cAlarm;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cDriver;
class __DLL_EXPORT__ cCellLogger;
class __DLL_EXPORT__ cCell;
class __DLL_EXPORT__ cCellDispatcher;
class __DLL_EXPORT__ cIOSignal;
class __DLL_EXPORT__ cDigitalIO;

//## begin module%3AA36AF4035B.additionalDeclarations preserve=yes
//## end module%3AA36AF4035B.additionalDeclarations


//## begin cProgram%3AA36AF4035B.preface preserve=yes
//## end cProgram%3AA36AF4035B.preface

//## Class: cProgram%3AA36AF4035B
//## Category: Control::Cell::Programs%3AB6268F0083
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AB6300401D8;cIO { -> F}
//## Uses: <unnamed>%3AB75CB30297;cDriver { -> F}
//## Uses: <unnamed>%3ABA1BA30045;cInfo { -> F}
//## Uses: <unnamed>%3AE45C8C0377;cConfigurationObject { -> F}
//## Uses: <unnamed>%3AED38310327;cIOSignal { -> F}
//## Uses: <unnamed>%3E155CE40009;cAlarm { -> F}
//## Uses: <unnamed>%3E6DEFF10000;cCellDispatcher { -> F}
//## Uses: <unnamed>%3E6DF00C00BB;cCellLogger { -> F}
//## Uses: <unnamed>%3FBF6B690271;cTransientObject { -> }

class __DLL_EXPORT__ cProgram : public cControlThread  //## Inherits: <unnamed>%3E6E009E0186
{
  //## begin cProgram%3AA36AF4035B.initialDeclarations preserve=yes
public:
  //## end cProgram%3AA36AF4035B.initialDeclarations

    //## Constructors (generated)
      cProgram();

      cProgram(const cProgram &right);

    //## Constructors (specified)
      //## Operation: cProgram%985080211
      cProgram (cCell *cell, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cProgram();


    //## Other Operations (specified)
      //## Operation: Start%987504139
      virtual BOOL_T Start () = 0;

      //## Operation: Stop%987504141
      virtual BOOL_T Stop () = 0;

      //## Operation: ProcessEvent%984992072
      virtual void ProcessEvent (cTransientObject *object) = 0;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: LogFileName%3B779C3C010C
      STRING_T get_LogFileName () const;

      //## Attribute: TestMode%3C35841E00E6
      ULONG_T get_TestMode () const;

    // Data Members for Associations

      //## Association: Control::Cell::Programs::<unnamed>%3AED31B901A9
      //## Role: cProgram::DigitalIO%3AED31BA007E
      //## begin cProgram::DigitalIO%3AED31BA007E.role preserve=no  public: cDigitalIO { -> 0..1RFHN}
      cDigitalIO *_DigitalIO;
      //## end cProgram::DigitalIO%3AED31BA007E.role

      //## Association: Control::Cell::<unnamed>%3AB7318B0100
      //## Role: cProgram::Cell%3AB7318C02E2
      //## begin cProgram::Cell%3AB7318C02E2.role preserve=no  public: cCell { -> 1RFHN}
      cCell *_Cell;
      //## end cProgram::Cell%3AB7318C02E2.role

  public:
    // Additional Public Declarations
      //## begin cProgram%3AA36AF4035B.public preserve=yes
      //## end cProgram%3AA36AF4035B.public

  protected:

    //## Other Operations (specified)
      //## Operation: UseSignal%984992067
      void UseSignal (cIOSignal *signal);

      //## Operation: Input%984992068
      BOOL_T Input (CONST_STRING_T name);

      //## Operation: Input%988620494
      BOOL_T Input (cIOSignal *io_signal);

      //## Operation: SetOutput%984992069
      void SetOutput (CONST_STRING_T name);

      //## Operation: SetOutput%988620495
      void SetOutput (cIOSignal *io_signal);

      //## Operation: ResetOutput%984992070
      void ResetOutput (CONST_STRING_T name);

      //## Operation: ResetOutput%988620496
      void ResetOutput (cIOSignal *io_signal);

      //## Operation: SetState%985080207
      virtual void SetState (INT_T state);

      //## Operation: Driver%985080214
      cDriver * Driver (CONST_STRING_T name);

      //## Operation: IOSignal%984992074
      cIOSignal * IOSignal (CONST_STRING_T name);

      //## Operation: SetAlarm%985267667
      void SetAlarm (BOOL_T state, CONST_STRING_T ident);

      //## Operation: LogPrintf%997694796
      BOOL_T LogPrintf (CONST_STRING_T fmt_str, ... );

    // Data Members for Class Attributes

      //## Attribute: ProgramState%3AB723190315
      //## begin cProgram::ProgramState%3AB723190315.attr preserve=no  protected: INT_T {U} 0
      INT_T _ProgramState;
      //## end cProgram::ProgramState%3AB723190315.attr

      //## begin cProgram::LogFileName%3B779C3C010C.attr preserve=no  public: STRING_T {U} 
      STRING_T _LogFileName;
      //## end cProgram::LogFileName%3B779C3C010C.attr

      //## begin cProgram::TestMode%3C35841E00E6.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _TestMode;
      //## end cProgram::TestMode%3C35841E00E6.attr

    // Data Members for Associations

      //## Association: Control::Cell::Programs::<unnamed>%3B779E460384
      //## Role: cProgram::LogFile%3B779E4702E5
      //## begin cProgram::LogFile%3B779E4702E5.role preserve=no  public: cLogFile { -> 0..1RFHN}
      cLogFile *_LogFile;
      //## end cProgram::LogFile%3B779E4702E5.role

    // Additional Protected Declarations
      //## begin cProgram%3AA36AF4035B.protected preserve=yes
      //## end cProgram%3AA36AF4035B.protected

  private:
    // Additional Private Declarations
      //## begin cProgram%3AA36AF4035B.private preserve=yes
      //## end cProgram%3AA36AF4035B.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cProgram%3AA36AF4035B.implementation preserve=yes
      //## end cProgram%3AA36AF4035B.implementation

};

//## begin cProgram%3AA36AF4035B.postscript preserve=yes
//## end cProgram%3AA36AF4035B.postscript

// Class cProgram 

//## begin module%3AA36AF4035B.epilog preserve=yes
//## end module%3AA36AF4035B.epilog


#endif
