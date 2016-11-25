//## begin module%4380805F01D0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380805F01D0.cm

//## begin module%4380805F01D0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380805F01D0.cp

//## Module: cGetInfoCmd%4380805F01D0; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cGetInfoCmd.h

#ifndef cGetInfoCmd_h
#define cGetInfoCmd_h 1

//## begin module%4380805F01D0.includes preserve=yes
//## end module%4380805F01D0.includes

// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class __DLL_EXPORT__ cEM63Interface;

//## begin module%4380805F01D0.additionalDeclarations preserve=yes
//## end module%4380805F01D0.additionalDeclarations


//## begin cGetInfoCmd%4380805F01D0.preface preserve=yes
//## end cGetInfoCmd%4380805F01D0.preface

//## Class: cGetInfoCmd%4380805F01D0
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43B260A102AF;cEM63Interface { -> F}

class __DLL_EXPORT__ cGetInfoCmd : public cPresentationCmd  //## Inherits: <unnamed>%4380820D03D1
{
  //## begin cGetInfoCmd%4380805F01D0.initialDeclarations preserve=yes
public:
  //## end cGetInfoCmd%4380805F01D0.initialDeclarations

    //## Constructors (generated)
      cGetInfoCmd();

      cGetInfoCmd(const cGetInfoCmd &right);

    //## Constructors (specified)
      //## Operation: cGetInfoCmd%1136548772
      cGetInfoCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cGetInfoCmd();


    //## Other Operations (specified)
      //## Operation: Process%1135093202
      virtual BOOL_T Process (cContext *context);

      //## Operation: Start%1135093203
      virtual BOOL_T Start ();

      //## Operation: Stop%1135093204
      virtual void Stop ();

  public:
    // Additional Public Declarations
      //## begin cGetInfoCmd%4380805F01D0.public preserve=yes
      //## end cGetInfoCmd%4380805F01D0.public

  protected:
    // Additional Protected Declarations
      //## begin cGetInfoCmd%4380805F01D0.protected preserve=yes
      //## end cGetInfoCmd%4380805F01D0.protected

  private:
    // Additional Private Declarations
      //## begin cGetInfoCmd%4380805F01D0.private preserve=yes
      //## end cGetInfoCmd%4380805F01D0.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: AddString%1135098391
      void AddString (STRING_T &info, CONST_STRING_T name, CONST_STRING_T value, CONST_STRING_T delimiter);

      //## Operation: AddInteger%1135098392
      void AddInteger (STRING_T &info, CONST_STRING_T name, LONG_T value, CONST_STRING_T delimiter);

      //## Operation: AddActiveJobs%1135162374
      void AddActiveJobs (cEM63Interface *itf, STRING_T &info, CONST_STRING_T delimiter);

      //## Operation: AddActiveReports%1135162375
      void AddActiveReports (cEM63Interface *itf, STRING_T &info, CONST_STRING_T delimiter);

      //## Operation: AddActiveEvents%1135162376
      void AddActiveEvents (cEM63Interface *itf, STRING_T &info, CONST_STRING_T delimiter);

      //## Operation: AddEventTypes%1135177951
      void AddEventTypes (cEM63Interface *itf, STRING_T &info, CONST_STRING_T delimiter);

      //## Operation: AddRefString%1136199178
      void AddRefString (STRING_T &info, CONST_STRING_T name, CONST_STRING_T var_spec, CONST_STRING_T delimiter);

      //## Operation: AddRefInteger%1136199179
      void AddRefInteger (STRING_T &info, CONST_STRING_T name, CONST_STRING_T var_spec, CONST_STRING_T delimiter);

    // Additional Implementation Declarations
      //## begin cGetInfoCmd%4380805F01D0.implementation preserve=yes
      //## end cGetInfoCmd%4380805F01D0.implementation

};

//## begin cGetInfoCmd%4380805F01D0.postscript preserve=yes
//## end cGetInfoCmd%4380805F01D0.postscript

// Class cGetInfoCmd 

//## begin module%4380805F01D0.epilog preserve=yes
//## end module%4380805F01D0.epilog


#endif
