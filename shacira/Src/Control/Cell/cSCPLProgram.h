//## begin module%40F919FC035B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40F919FC035B.cm

//## begin module%40F919FC035B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40F919FC035B.cp

//## Module: cSCPLProgram%40F919FC035B; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cSCPLProgram.h

#ifndef cSCPLProgram_h
#define cSCPLProgram_h 1

//## begin module%40F919FC035B.includes preserve=yes
//## end module%40F919FC035B.includes

// cProgram
#include "Control/Cell/cProgram.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cControlProcedure;

//## begin module%40F919FC035B.additionalDeclarations preserve=yes

extern BOOL_T _SCPLLog;
extern void SCPLLog(const char * fmt_str, ...);
extern void SCPLLogClear();

//## end module%40F919FC035B.additionalDeclarations


//## begin cSCPLProgram%40F919FC035B.preface preserve=yes
//## end cSCPLProgram%40F919FC035B.preface

//## Class: cSCPLProgram%40F919FC035B
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%42E6325B00BB;cControlProcedure { -> F}
//## Uses: <unnamed>%42E632B1006D;cContext { -> F}

class __DLL_EXPORT__ cSCPLProgram : public cProgram  //## Inherits: <unnamed>%40F91A2100FA
{
  //## begin cSCPLProgram%40F919FC035B.initialDeclarations preserve=yes
public:
  //## end cSCPLProgram%40F919FC035B.initialDeclarations

    //## Constructors (generated)
      cSCPLProgram();

      cSCPLProgram(const cSCPLProgram &right);

    //## Constructors (specified)
      //## Operation: cSCPLProgram%1090067122
      cSCPLProgram (cConfigurationObject *config_obj, cContext *context);

    //## Destructor (generated)
      virtual ~cSCPLProgram();

  public:
    // Additional Public Declarations
      //## begin cSCPLProgram%40F919FC035B.public preserve=yes
      //## end cSCPLProgram%40F919FC035B.public

  protected:

    //## Other Operations (specified)
      //## Operation: LoadProgram%1090067123
      void LoadProgram (CONST_STRING_T source);

      //## Operation: Procedure%1090067638
      cControlProcedure * Procedure (CONST_STRING_T name);

    // Additional Protected Declarations
      //## begin cSCPLProgram%40F919FC035B.protected preserve=yes
      //## end cSCPLProgram%40F919FC035B.protected

  private:
    // Additional Private Declarations
      //## begin cSCPLProgram%40F919FC035B.private preserve=yes
      //## end cSCPLProgram%40F919FC035B.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSCPLProgram%40F919FC035B.implementation preserve=yes
      //## end cSCPLProgram%40F919FC035B.implementation

};

//## begin cSCPLProgram%40F919FC035B.postscript preserve=yes
//## end cSCPLProgram%40F919FC035B.postscript

// Class cSCPLProgram 

//## begin module%40F919FC035B.epilog preserve=yes
//## end module%40F919FC035B.epilog


#endif
