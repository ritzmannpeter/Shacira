//## begin module%438080AF024D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%438080AF024D.cm

//## begin module%438080AF024D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%438080AF024D.cp

//## Module: cDownloadCmd%438080AF024D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cDownloadCmd.h

#ifndef cDownloadCmd_h
#define cDownloadCmd_h 1

//## begin module%438080AF024D.includes preserve=yes
//## end module%438080AF024D.includes

// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class __DLL_EXPORT__ cCondition;
class __DLL_EXPORT__ cEM63Interface;

//## begin module%438080AF024D.additionalDeclarations preserve=yes
//## end module%438080AF024D.additionalDeclarations


//## begin cDownloadCmd%438080AF024D.preface preserve=yes
//## end cDownloadCmd%438080AF024D.preface

//## Class: cDownloadCmd%438080AF024D
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43B54CA8001E;cCondition { -> F}
//## Uses: <unnamed>%43B5554C01DB;cEM63Interface { -> F}

class __DLL_EXPORT__ cDownloadCmd : public cPresentationCmd  //## Inherits: <unnamed>%438081EF0345
{
  //## begin cDownloadCmd%438080AF024D.initialDeclarations preserve=yes
public:
  //## end cDownloadCmd%438080AF024D.initialDeclarations

    //## Constructors (generated)
      cDownloadCmd();

      cDownloadCmd(const cDownloadCmd &right);

    //## Constructors (specified)
      //## Operation: cDownloadCmd%1136548769
      cDownloadCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cDownloadCmd();


    //## Other Operations (specified)
      //## Operation: SetStartCondition%1135947268
      void SetStartCondition (cCondition *condition);

      //## Operation: Start%1135947270
      virtual BOOL_T Start ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ActiveSource%43B54BD50252
      BOOL_T get_ActiveSource () const;
      void set_ActiveSource (BOOL_T value);

      //## Attribute: AvSource%43B54C020167
      STRING_T get_AvSource () const;
      void set_AvSource (STRING_T value);

      //## Attribute: Keyword%43B54C19009C
      STRING_T get_Keyword () const;
      void set_Keyword (STRING_T value);

      //## Attribute: StartCondition%43B54C760176
      cCondition * get_StartCondition () const;
      void set_StartCondition (cCondition * value);

  public:
    // Additional Public Declarations
      //## begin cDownloadCmd%438080AF024D.public preserve=yes
      //## end cDownloadCmd%438080AF024D.public

  protected:
    // Data Members for Class Attributes

      //## begin cDownloadCmd::ActiveSource%43B54BD50252.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _ActiveSource;
      //## end cDownloadCmd::ActiveSource%43B54BD50252.attr

      //## begin cDownloadCmd::AvSource%43B54C020167.attr preserve=no  public: STRING_T {U} 
      STRING_T _AvSource;
      //## end cDownloadCmd::AvSource%43B54C020167.attr

      //## begin cDownloadCmd::Keyword%43B54C19009C.attr preserve=no  public: STRING_T {U} 
      STRING_T _Keyword;
      //## end cDownloadCmd::Keyword%43B54C19009C.attr

      //## begin cDownloadCmd::StartCondition%43B54C760176.attr preserve=no  public: cCondition * {U} NULL
      cCondition *_StartCondition;
      //## end cDownloadCmd::StartCondition%43B54C760176.attr

    // Additional Protected Declarations
      //## begin cDownloadCmd%438080AF024D.protected preserve=yes
      //## end cDownloadCmd%438080AF024D.protected

  private:
    // Additional Private Declarations
      //## begin cDownloadCmd%438080AF024D.private preserve=yes
      //## end cDownloadCmd%438080AF024D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Download%1135947272
      BOOL_T Download ();

    // Additional Implementation Declarations
      //## begin cDownloadCmd%438080AF024D.implementation preserve=yes
      //## end cDownloadCmd%438080AF024D.implementation

};

//## begin cDownloadCmd%438080AF024D.postscript preserve=yes
//## end cDownloadCmd%438080AF024D.postscript

// Class cDownloadCmd 

//## begin module%438080AF024D.epilog preserve=yes
//## end module%438080AF024D.epilog


#endif
