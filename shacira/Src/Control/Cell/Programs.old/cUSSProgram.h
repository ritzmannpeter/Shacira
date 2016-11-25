//## begin module%3BD6C32703A9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BD6C32703A9.cm

//## begin module%3BD6C32703A9.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BD6C32703A9.cp

//## Module: cUSSProgram%3BD6C32703A9; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cUSSProgram.h

#ifndef cUSSProgram_h
#define cUSSProgram_h 1

//## begin module%3BD6C32703A9.includes preserve=yes
//## end module%3BD6C32703A9.includes

// cProgram
#include "Control/Cell/Programs/cProgram.h"

class __DLL_EXPORT__ cIO;
class __DLL_EXPORT__ cState;
class __DLL_EXPORT__ cInfo;
class __DLL_EXPORT__ cDriver;
class __DLL_EXPORT__ cCell;
class __DLL_EXPORT__ cIOSignal;
class __DLL_EXPORT__ cDigitalIO;

//## begin module%3BD6C32703A9.additionalDeclarations preserve=yes

#define USS_PS_INIT                  0
#define USS_PS_WF_BARCODE1           1
#define USS_PS_WF_COLOR              2
#define USS_PS_WF_USS_READY          3
#define USS_PS_WF_USS_WELD           4
#define USS_PS_WF_CYCLE_DATA         5
#define USS_PS_WF_PRINTING           6
#define USS_PS_WF_SCAN_VALUE         7
#define USS_PS_WF_DATA_LOGGED        8
#define USS_PS_STOP                  9
#define USS_PS_WF_PRINTING_2         10

//## end module%3BD6C32703A9.additionalDeclarations


//## begin cUSSProgram%3BD6C32703A9.preface preserve=yes
//## end cUSSProgram%3BD6C32703A9.preface

//## Class: cUSSProgram%3BD6C32703A9
//## Category: Control::Cell::Programs%3AB6268F0083
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BD6C5A70038;cDigitalIO { -> F}
//## Uses: <unnamed>%3BD6CB3501EB;cState { -> F}
//## Uses: <unnamed>%3BD6E5F700A1;cIO { -> F}
//## Uses: <unnamed>%3BD6EE0700BD;cInfo { -> F}
//## Uses: <unnamed>%3BD6F04602EA;cIOSignal { -> F}
//## Uses: <unnamed>%3BD7EE370014;cCell { -> F}

class __DLL_EXPORT__ cUSSProgram : public cProgram  //## Inherits: <unnamed>%3BD6C344036F
{
  //## begin cUSSProgram%3BD6C32703A9.initialDeclarations preserve=yes
  //## end cUSSProgram%3BD6C32703A9.initialDeclarations

    //## Constructors (generated)
      cUSSProgram();

      cUSSProgram(const cUSSProgram &right);

    //## Constructors (specified)
      //## Operation: cUSSProgram%1003916882
      cUSSProgram (cCell *cell, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cUSSProgram();


    //## Other Operations (specified)
      //## Operation: Start%1047387663
      virtual BOOL_T Start ();

      //## Operation: Stop%1047387664
      virtual BOOL_T Stop ();

      //## Operation: ProcessEvent%1047387665
      virtual void ProcessEvent (cTransientObject *object);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: BarcodeProlog%3BD6DE7D01A3
      STRING_T get_BarcodeProlog () const;

      //## Attribute: I2OF5WorkAround%3BD6DE7D01C1
      BOOL_T get_I2OF5WorkAround () const;

      //## Attribute: ControlPartMovement%3BD83C2B01AA
      BOOL_T get_ControlPartMovement () const;

      //## Attribute: RescanBarcode%3C3B0523024F
      BOOL_T get_RescanBarcode () const;

      //## Attribute: RescanBoth%3E6E115E036B
      BOOL_T get_RescanBoth () const;

      //## Attribute: ExternalUSSControl%3BE93F4401FC
      BOOL_T get_ExternalUSSControl () const;

      //## Attribute: IgnoreOldCode%3E6E106F02FD
      BOOL_T get_IgnoreOldCode () const;

      //## Attribute: PartOffset%3E6E118B000F
      ULONG_T get_PartOffset () const;

      //## Attribute: Programmable%3E6E109B038A
      BOOL_T get_Programmable () const;

      //## Attribute: CycleDelay%3E6E1100030D
      ULONG_T get_CycleDelay () const;

      //## Attribute: StaticBarcode%3E6E10C9030D
      STRING_T get_StaticBarcode () const;

  public:
    // Additional Public Declarations
      //## begin cUSSProgram%3BD6C32703A9.public preserve=yes
      //## end cUSSProgram%3BD6C32703A9.public

  protected:
    // Data Members for Class Attributes

      //## begin cUSSProgram::BarcodeProlog%3BD6DE7D01A3.attr preserve=no  public: STRING_T {U} 
      STRING_T _BarcodeProlog;
      //## end cUSSProgram::BarcodeProlog%3BD6DE7D01A3.attr

      //## begin cUSSProgram::I2OF5WorkAround%3BD6DE7D01C1.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _I2OF5WorkAround;
      //## end cUSSProgram::I2OF5WorkAround%3BD6DE7D01C1.attr

      //## begin cUSSProgram::ControlPartMovement%3BD83C2B01AA.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _ControlPartMovement;
      //## end cUSSProgram::ControlPartMovement%3BD83C2B01AA.attr

      //## begin cUSSProgram::RescanBarcode%3C3B0523024F.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _RescanBarcode;
      //## end cUSSProgram::RescanBarcode%3C3B0523024F.attr

      //## begin cUSSProgram::RescanBoth%3E6E115E036B.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _RescanBoth;
      //## end cUSSProgram::RescanBoth%3E6E115E036B.attr

      //## begin cUSSProgram::ExternalUSSControl%3BE93F4401FC.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _ExternalUSSControl;
      //## end cUSSProgram::ExternalUSSControl%3BE93F4401FC.attr

      //## begin cUSSProgram::IgnoreOldCode%3E6E106F02FD.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IgnoreOldCode;
      //## end cUSSProgram::IgnoreOldCode%3E6E106F02FD.attr

      //## begin cUSSProgram::PartOffset%3E6E118B000F.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _PartOffset;
      //## end cUSSProgram::PartOffset%3E6E118B000F.attr

      //## begin cUSSProgram::Programmable%3E6E109B038A.attr preserve=no  public: BOOL_T {U} true
      BOOL_T _Programmable;
      //## end cUSSProgram::Programmable%3E6E109B038A.attr

      //## begin cUSSProgram::CycleDelay%3E6E1100030D.attr preserve=no  public: ULONG_T {U} 1000
      ULONG_T _CycleDelay;
      //## end cUSSProgram::CycleDelay%3E6E1100030D.attr

      //## begin cUSSProgram::StaticBarcode%3E6E10C9030D.attr preserve=no  public: STRING_T {U} "012345"
      STRING_T _StaticBarcode;
      //## end cUSSProgram::StaticBarcode%3E6E10C9030D.attr

    // Data Members for Associations

      //## Association: Control::Cell::Programs::<unnamed>%3BD6DFBC00C5
      //## Role: cUSSProgram::ColorSensor%3BD6DFBD0012
      //## begin cUSSProgram::ColorSensor%3BD6DFBD0012.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_ColorSensor;
      //## end cUSSProgram::ColorSensor%3BD6DFBD0012.role

      //## Association: Control::Cell::Programs::<unnamed>%3BD6DFFF0357
      //## Role: cUSSProgram::Scanner%3BD6E00003BC
      //## begin cUSSProgram::Scanner%3BD6E00003BC.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_Scanner;
      //## end cUSSProgram::Scanner%3BD6E00003BC.role

      //## Association: Control::Cell::Programs::<unnamed>%3BD6E02E00F1
      //## Role: cUSSProgram::Printer%3BD6E02F0084
      //## begin cUSSProgram::Printer%3BD6E02F0084.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_Printer;
      //## end cUSSProgram::Printer%3BD6E02F0084.role

      //## Association: Control::Cell::Programs::<unnamed>%3BD6E04F01E9
      //## Role: cUSSProgram::CellData%3BD6E05001FE
      //## begin cUSSProgram::CellData%3BD6E05001FE.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_CellData;
      //## end cUSSProgram::CellData%3BD6E05001FE.role

      //## Association: Control::Cell::Programs::<unnamed>%3BD7DFAB022C
      //## Role: cUSSProgram::USS%3BD7DFAC0223
      //## begin cUSSProgram::USS%3BD7DFAC0223.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_USS;
      //## end cUSSProgram::USS%3BD7DFAC0223.role

      //## Association: Control::Cell::Programs::<unnamed>%3E6E11F703B9
      //## Role: cUSSProgram::Scanner2%3E6E11F9034B
      //## begin cUSSProgram::Scanner2%3E6E11F9034B.role preserve=no  public: cDriver { -> 0..1RFHN}
      cDriver *_Scanner2;
      //## end cUSSProgram::Scanner2%3E6E11F9034B.role

    // Additional Protected Declarations
      //## begin cUSSProgram%3BD6C32703A9.protected preserve=yes
      //## end cUSSProgram%3BD6C32703A9.protected

  private:
    // Additional Private Declarations
      //## begin cUSSProgram%3BD6C32703A9.private preserve=yes
      //## end cUSSProgram%3BD6C32703A9.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: USSWeld%3BD6DC480060
      //## begin cUSSProgram::USSWeld%3BD6DC480060.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_USSWeld;
      //## end cUSSProgram::USSWeld%3BD6DC480060.attr

      //## Attribute: USSAlarm%3BD6DC4902A6
      //## begin cUSSProgram::USSAlarm%3BD6DC4902A6.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_USSAlarm;
      //## end cUSSProgram::USSAlarm%3BD6DC4902A6.attr

      //## Attribute: USSParamSet%3BD6DC4B0187
      //## begin cUSSProgram::USSParamSet%3BD6DC4B0187.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_USSParamSet;
      //## end cUSSProgram::USSParamSet%3BD6DC4B0187.attr

      //## Attribute: USSReset%3BD6DC610323
      //## begin cUSSProgram::USSReset%3BD6DC610323.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_USSReset;
      //## end cUSSProgram::USSReset%3BD6DC610323.attr

      //## Attribute: USSLock%3BD6DC710203
      //## begin cUSSProgram::USSLock%3BD6DC710203.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_USSLock;
      //## end cUSSProgram::USSLock%3BD6DC710203.attr

      //## Attribute: USSReady%3BD6DC340378
      //## begin cUSSProgram::USSReady%3BD6DC340378.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_USSReady;
      //## end cUSSProgram::USSReady%3BD6DC340378.attr

      //## Attribute: Alarm%3BD6DC7203D2
      //## begin cUSSProgram::Alarm%3BD6DC7203D2.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_Alarm;
      //## end cUSSProgram::Alarm%3BD6DC7203D2.attr

      //## Attribute: Retries%3BD6DE620385
      //## begin cUSSProgram::Retries%3BD6DE620385.attr preserve=no  implementation: ULONG_T {U} 2
      ULONG_T _Retries;
      //## end cUSSProgram::Retries%3BD6DE620385.attr

      //## Attribute: ActRetries%3BD6DE620399
      //## begin cUSSProgram::ActRetries%3BD6DE620399.attr preserve=no  implementation: INT_T {U} 0
      INT_T _ActRetries;
      //## end cUSSProgram::ActRetries%3BD6DE620399.attr

      //## Attribute: PartCount%3BD6DE6203A3
      //## begin cUSSProgram::PartCount%3BD6DE6203A3.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _PartCount;
      //## end cUSSProgram::PartCount%3BD6DE6203A3.attr

      //## Attribute: Day%3BD6DE6203B7
      //## begin cUSSProgram::Day%3BD6DE6203B7.attr preserve=no  implementation: INT_T {U} -1
      INT_T _Day;
      //## end cUSSProgram::Day%3BD6DE6203B7.attr

      //## Attribute: LogEvent%3BD6F0FF0047
      //## begin cUSSProgram::LogEvent%3BD6F0FF0047.attr preserve=no  implementation: cEventSem {U} 
      cEventSem _LogEvent;
      //## end cUSSProgram::LogEvent%3BD6F0FF0047.attr

      //## Attribute: Barcode1%3BD6FA4900BF
      //## begin cUSSProgram::Barcode1%3BD6FA4900BF.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Barcode1;
      //## end cUSSProgram::Barcode1%3BD6FA4900BF.attr

      //## Attribute: Barcode2%3BD6DE62037B
      //## begin cUSSProgram::Barcode2%3BD6DE62037B.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Barcode2;
      //## end cUSSProgram::Barcode2%3BD6DE62037B.attr

      //## Attribute: ActColor%3BD8315D00B2
      //## begin cUSSProgram::ActColor%3BD8315D00B2.attr preserve=no  implementation: INT_T {U} 0
      INT_T _ActColor;
      //## end cUSSProgram::ActColor%3BD8315D00B2.attr

      //## Attribute: ColorString%3C3B5EA801F4
      //## begin cUSSProgram::ColorString%3C3B5EA801F4.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ColorString;
      //## end cUSSProgram::ColorString%3C3B5EA801F4.attr

      //## Attribute: ColorCode%3C3B627B02F6
      //## begin cUSSProgram::ColorCode%3C3B627B02F6.attr preserve=no  implementation: INT_T {U} 9
      INT_T _ColorCode;
      //## end cUSSProgram::ColorCode%3C3B627B02F6.attr

    // Additional Implementation Declarations
      //## begin cUSSProgram%3BD6C32703A9.implementation preserve=yes
      //## end cUSSProgram%3BD6C32703A9.implementation

};

//## begin cUSSProgram%3BD6C32703A9.postscript preserve=yes
//## end cUSSProgram%3BD6C32703A9.postscript

// Class cUSSProgram 

//## begin module%3BD6C32703A9.epilog preserve=yes
//## end module%3BD6C32703A9.epilog


#endif
