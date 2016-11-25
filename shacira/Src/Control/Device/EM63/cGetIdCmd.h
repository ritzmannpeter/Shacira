//## begin module%4380804702CB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380804702CB.cm

//## begin module%4380804702CB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380804702CB.cp

//## Module: cGetIdCmd%4380804702CB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cGetIdCmd.h

#ifndef cGetIdCmd_h
#define cGetIdCmd_h 1

//## begin module%4380804702CB.includes preserve=yes
//## end module%4380804702CB.includes

// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class __DLL_EXPORT__ cEM63Interface;

//## begin module%4380804702CB.additionalDeclarations preserve=yes
//## end module%4380804702CB.additionalDeclarations


//## begin cGetIdCmd%4380804702CB.preface preserve=yes
//## end cGetIdCmd%4380804702CB.preface

//## Class: cGetIdCmd%4380804702CB
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43B260750317;cEM63Interface { -> F}

class __DLL_EXPORT__ cGetIdCmd : public cPresentationCmd  //## Inherits: <unnamed>%4380820500D4
{
  //## begin cGetIdCmd%4380804702CB.initialDeclarations preserve=yes
public:
  //## end cGetIdCmd%4380804702CB.initialDeclarations

    //## Constructors (generated)
      cGetIdCmd();

      cGetIdCmd(const cGetIdCmd &right);

    //## Constructors (specified)
      //## Operation: cGetIdCmd%1136548773
      cGetIdCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cGetIdCmd();


    //## Other Operations (specified)
      //## Operation: Process%1135761101
      virtual BOOL_T Process (cContext *context);

      //## Operation: Start%1135761102
      virtual BOOL_T Start ();

      //## Operation: Stop%1135761103
      virtual void Stop ();

  public:
    // Additional Public Declarations
      //## begin cGetIdCmd%4380804702CB.public preserve=yes
      //## end cGetIdCmd%4380804702CB.public

  protected:
    // Additional Protected Declarations
      //## begin cGetIdCmd%4380804702CB.protected preserve=yes
      //## end cGetIdCmd%4380804702CB.protected

  private:
    // Additional Private Declarations
      //## begin cGetIdCmd%4380804702CB.private preserve=yes
      //## end cGetIdCmd%4380804702CB.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cGetIdCmd%4380804702CB.implementation preserve=yes
      //## end cGetIdCmd%4380804702CB.implementation

};

//## begin cGetIdCmd%4380804702CB.postscript preserve=yes
//## end cGetIdCmd%4380804702CB.postscript

// Class cGetIdCmd 

//## begin module%4380804702CB.epilog preserve=yes
//## end module%4380804702CB.epilog


#endif
