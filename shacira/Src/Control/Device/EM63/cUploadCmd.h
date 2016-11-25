//## begin module%4380809B026C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380809B026C.cm

//## begin module%4380809B026C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380809B026C.cp

//## Module: cUploadCmd%4380809B026C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cUploadCmd.h

#ifndef cUploadCmd_h
#define cUploadCmd_h 1

//## begin module%4380809B026C.includes preserve=yes
//## end module%4380809B026C.includes

// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class __DLL_EXPORT__ cCondition;
class __DLL_EXPORT__ cEM63Interface;

//## begin module%4380809B026C.additionalDeclarations preserve=yes
//## end module%4380809B026C.additionalDeclarations


//## begin cUploadCmd%4380809B026C.preface preserve=yes
//## end cUploadCmd%4380809B026C.preface

//## Class: cUploadCmd%4380809B026C
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43B54CB000BA;cCondition { -> F}
//## Uses: <unnamed>%43B5555900A2;cEM63Interface { -> F}

class __DLL_EXPORT__ cUploadCmd : public cPresentationCmd  //## Inherits: <unnamed>%438082110306
{
  //## begin cUploadCmd%4380809B026C.initialDeclarations preserve=yes
public:
  //## end cUploadCmd%4380809B026C.initialDeclarations

    //## Constructors (generated)
      cUploadCmd();

      cUploadCmd(const cUploadCmd &right);

    //## Constructors (specified)
      //## Operation: cUploadCmd%1136548770
      cUploadCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cUploadCmd();


    //## Other Operations (specified)
      //## Operation: SetStartCondition%1135947269
      void SetStartCondition (cCondition *condition);

      //## Operation: Start%1135947271
      virtual BOOL_T Start ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ActiveSource%43B54C390290
      BOOL_T get_ActiveSource () const;
      void set_ActiveSource (BOOL_T value);

      //## Attribute: AvSource%43B54C39029F
      STRING_T get_AvSource () const;
      void set_AvSource (STRING_T value);

      //## Attribute: Keyword%43B54C3902A0
      STRING_T get_Keyword () const;
      void set_Keyword (STRING_T value);

      //## Attribute: StartCondition%43B54C7C0270
      cCondition * get_StartCondition () const;
      void set_StartCondition (cCondition * value);

  public:
    // Additional Public Declarations
      //## begin cUploadCmd%4380809B026C.public preserve=yes
      //## end cUploadCmd%4380809B026C.public

  protected:
    // Data Members for Class Attributes

      //## begin cUploadCmd::ActiveSource%43B54C390290.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _ActiveSource;
      //## end cUploadCmd::ActiveSource%43B54C390290.attr

      //## begin cUploadCmd::AvSource%43B54C39029F.attr preserve=no  public: STRING_T {U} 
      STRING_T _AvSource;
      //## end cUploadCmd::AvSource%43B54C39029F.attr

      //## begin cUploadCmd::Keyword%43B54C3902A0.attr preserve=no  public: STRING_T {U} 
      STRING_T _Keyword;
      //## end cUploadCmd::Keyword%43B54C3902A0.attr

      //## begin cUploadCmd::StartCondition%43B54C7C0270.attr preserve=no  public: cCondition * {U} NULL
      cCondition *_StartCondition;
      //## end cUploadCmd::StartCondition%43B54C7C0270.attr

    // Additional Protected Declarations
      //## begin cUploadCmd%4380809B026C.protected preserve=yes
      //## end cUploadCmd%4380809B026C.protected

  private:
    // Additional Private Declarations
      //## begin cUploadCmd%4380809B026C.private preserve=yes
      //## end cUploadCmd%4380809B026C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Upload%1135947273
      BOOL_T Upload ();

    // Additional Implementation Declarations
      //## begin cUploadCmd%4380809B026C.implementation preserve=yes
      //## end cUploadCmd%4380809B026C.implementation

};

//## begin cUploadCmd%4380809B026C.postscript preserve=yes
//## end cUploadCmd%4380809B026C.postscript

// Class cUploadCmd 

//## begin module%4380809B026C.epilog preserve=yes
//## end module%4380809B026C.epilog


#endif
