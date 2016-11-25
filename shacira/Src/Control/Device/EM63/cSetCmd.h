//## begin module%43808080026C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43808080026C.cm

//## begin module%43808080026C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43808080026C.cp

//## Module: cSetCmd%43808080026C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cSetCmd.h

#ifndef cSetCmd_h
#define cSetCmd_h 1

//## begin module%43808080026C.includes preserve=yes
//## end module%43808080026C.includes

// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class __DLL_EXPORT__ cEM63Interface;

//## begin module%43808080026C.additionalDeclarations preserve=yes
//## end module%43808080026C.additionalDeclarations


//## begin cSetCmd%43808080026C.preface preserve=yes
//## end cSetCmd%43808080026C.preface

//## Class: cSetCmd%43808080026C
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43B286F400F1;cEM63Interface { -> F}

class __DLL_EXPORT__ cSetCmd : public cPresentationCmd  //## Inherits: <unnamed>%438081F402F7
{
  //## begin cSetCmd%43808080026C.initialDeclarations preserve=yes
public:
  //## end cSetCmd%43808080026C.initialDeclarations

    //## Constructors (generated)
      cSetCmd();

      cSetCmd(const cSetCmd &right);

    //## Constructors (specified)
      //## Operation: cSetCmd%1136548771
      cSetCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cSetCmd();


    //## Other Operations (specified)
      //## Operation: Process%1135093199
      virtual BOOL_T Process (cContext *context);

      //## Operation: Start%1135093200
      virtual BOOL_T Start ();

      //## Operation: Stop%1135093201
      virtual void Stop ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ParamId%43B2872400F1
      STRING_T get_ParamId () const;
      void set_ParamId (STRING_T value);

      //## Attribute: ParamValue%43B287420016
      STRING_T get_ParamValue () const;
      void set_ParamValue (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cSetCmd%43808080026C.public preserve=yes
      //## end cSetCmd%43808080026C.public

  protected:
    // Data Members for Class Attributes

      //## begin cSetCmd::ParamId%43B2872400F1.attr preserve=no  public: STRING_T {U} 
      STRING_T _ParamId;
      //## end cSetCmd::ParamId%43B2872400F1.attr

      //## begin cSetCmd::ParamValue%43B287420016.attr preserve=no  public: STRING_T {U} 
      STRING_T _ParamValue;
      //## end cSetCmd::ParamValue%43B287420016.attr

    // Additional Protected Declarations
      //## begin cSetCmd%43808080026C.protected preserve=yes
      //## end cSetCmd%43808080026C.protected

  private:
    // Additional Private Declarations
      //## begin cSetCmd%43808080026C.private preserve=yes
      //## end cSetCmd%43808080026C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSetCmd%43808080026C.implementation preserve=yes
      //## end cSetCmd%43808080026C.implementation

};

//## begin cSetCmd%43808080026C.postscript preserve=yes
//## end cSetCmd%43808080026C.postscript

// Class cSetCmd 

//## begin module%43808080026C.epilog preserve=yes
//## end module%43808080026C.epilog


#endif
