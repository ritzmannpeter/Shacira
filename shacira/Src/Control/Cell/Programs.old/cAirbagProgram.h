//## begin module%3AB6258802B5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AB6258802B5.cm

//## begin module%3AB6258802B5.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3AB6258802B5.cp

//## Module: cAirbagProgram%3AB6258802B5; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cAirbagProgram.h

#ifndef cAirbagProgram_h
#define cAirbagProgram_h 1

//## begin module%3AB6258802B5.includes preserve=yes
//## end module%3AB6258802B5.includes

// eb_sema
#include "base/eb_sema.hpp"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cProgram
#include "Control/Cell/Programs/cProgram.h"

class __DLL_EXPORT__ cIO;
class __DLL_EXPORT__ cState;
class __DLL_EXPORT__ cObjectBuffer;
class __DLL_EXPORT__ cInfo;
class __DLL_EXPORT__ cDriver;
class __DLL_EXPORT__ cCell;
class __DLL_EXPORT__ cIOSignal;
class __DLL_EXPORT__ cDigitalIO;

//## begin module%3AB6258802B5.additionalDeclarations preserve=yes

#define AB_PS_INIT                0
#define AB_PS_WF_MACHINE_CYCLE    1
#define AB_PS_WF_PART_AT_PRINTER  3
#define AB_PS_WF_APPLICATOR_READY 4
#define AB_PS_WF_LABEL_MOUNTED    5
#define AB_PS_WF_PART_AT_SCANNER  6
#define AB_PS_WF_SCAN_VALUE       7
#define AB_PS_WF_DATA_LOGGED      8
#define AB_PS_WF_RESYNC           9
#define AB_PS_STOP                10

//## end module%3AB6258802B5.additionalDeclarations


//## begin cAirbagProgram%3AB6258802B5.preface preserve=yes
//## end cAirbagProgram%3AB6258802B5.preface

//## Class: cAirbagProgram%3AB6258802B5
//## Category: Control::Cell::Programs%3AB6268F0083
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AB6315A0003;cConfigurationObject { -> }
//## Uses: <unnamed>%3AE45F8E00C2;cIO { -> F}
//## Uses: <unnamed>%3AE45FD0006C;cInfo { -> F}
//## Uses: <unnamed>%3AED2F660280;cIOSignal { -> F}
//## Uses: <unnamed>%3AED2F75001E;cDigitalIO { -> F}
//## Uses: <unnamed>%3B7B97FF011B;cMutexSem { -> }
//## Uses: <unnamed>%3BD7EDF00329;cCell { -> F}

class __DLL_EXPORT__ cAirbagProgram : public cProgram  //## Inherits: <unnamed>%3AB625A302DC
{
  //## begin cAirbagProgram%3AB6258802B5.initialDeclarations preserve=yes
  //## end cAirbagProgram%3AB6258802B5.initialDeclarations

    //## Constructors (generated)
      cAirbagProgram();

      cAirbagProgram(const cAirbagProgram &right);

    //## Constructors (specified)
      //## Operation: cAirbagProgram%985080212
      cAirbagProgram (cCell *cell, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cAirbagProgram();


    //## Other Operations (specified)
      //## Operation: Start%1047387657
      virtual BOOL_T Start ();

      //## Operation: Stop%1047387658
      virtual BOOL_T Stop ();

      //## Operation: ProcessEvent%1047387659
      virtual void ProcessEvent (cTransientObject *object);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IgnoreApplication%3ACDC2E6036F
      BOOL_T get_IgnoreApplication () const;

      //## Attribute: IgnoreApplicator%3B0267DD0312
      BOOL_T get_IgnoreApplicator () const;

      //## Attribute: IgnoreHandling%3B0293BB01A7
      BOOL_T get_IgnoreHandling () const;

      //## Attribute: BarcodeProlog%3B0267AB0279
      STRING_T get_BarcodeProlog () const;

      //## Attribute: SyncTime%3ADD59270192
      ULONG_T get_SyncTime () const;

      //## Attribute: I2OF5WorkAround%3B038BEA01FB
      BOOL_T get_I2OF5WorkAround () const;

      //## Attribute: PrintmarkWorkAround%3E6E0E1F01A5
      BOOL_T get_PrintmarkWorkAround () const;

      //## Attribute: Ventus610%3E6E0E6E0177
      BOOL_T get_Ventus610 () const;

      //## Attribute: ControlDanglingParts%3B77C07A02BC
      BOOL_T get_ControlDanglingParts () const;

      //## Attribute: RefuseTime%3B7B9EA90150
      ULONG_T get_RefuseTime () const;

      //## Attribute: PartOffset%3E6E0E4903D8
      ULONG_T get_PartOffset () const;

      //## Attribute: ApplicationDelay%3E6E0E9700AB
      ULONG_T get_ApplicationDelay () const;

  public:
    // Additional Public Declarations
      //## begin cAirbagProgram%3AB6258802B5.public preserve=yes
      //## end cAirbagProgram%3AB6258802B5.public

  protected:
    // Data Members for Class Attributes

      //## begin cAirbagProgram::IgnoreApplication%3ACDC2E6036F.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IgnoreApplication;
      //## end cAirbagProgram::IgnoreApplication%3ACDC2E6036F.attr

      //## begin cAirbagProgram::IgnoreApplicator%3B0267DD0312.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IgnoreApplicator;
      //## end cAirbagProgram::IgnoreApplicator%3B0267DD0312.attr

      //## begin cAirbagProgram::IgnoreHandling%3B0293BB01A7.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IgnoreHandling;
      //## end cAirbagProgram::IgnoreHandling%3B0293BB01A7.attr

      //## begin cAirbagProgram::BarcodeProlog%3B0267AB0279.attr preserve=no  public: STRING_T {U} 
      STRING_T _BarcodeProlog;
      //## end cAirbagProgram::BarcodeProlog%3B0267AB0279.attr

      //## begin cAirbagProgram::SyncTime%3ADD59270192.attr preserve=no  public: ULONG_T {U} 5000
      ULONG_T _SyncTime;
      //## end cAirbagProgram::SyncTime%3ADD59270192.attr

      //## begin cAirbagProgram::I2OF5WorkAround%3B038BEA01FB.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _I2OF5WorkAround;
      //## end cAirbagProgram::I2OF5WorkAround%3B038BEA01FB.attr

      //## begin cAirbagProgram::PrintmarkWorkAround%3E6E0E1F01A5.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _PrintmarkWorkAround;
      //## end cAirbagProgram::PrintmarkWorkAround%3E6E0E1F01A5.attr

      //## begin cAirbagProgram::Ventus610%3E6E0E6E0177.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Ventus610;
      //## end cAirbagProgram::Ventus610%3E6E0E6E0177.attr

      //## begin cAirbagProgram::ControlDanglingParts%3B77C07A02BC.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _ControlDanglingParts;
      //## end cAirbagProgram::ControlDanglingParts%3B77C07A02BC.attr

      //## begin cAirbagProgram::RefuseTime%3B7B9EA90150.attr preserve=no  public: ULONG_T {U} 500
      ULONG_T _RefuseTime;
      //## end cAirbagProgram::RefuseTime%3B7B9EA90150.attr

      //## begin cAirbagProgram::PartOffset%3E6E0E4903D8.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _PartOffset;
      //## end cAirbagProgram::PartOffset%3E6E0E4903D8.attr

      //## begin cAirbagProgram::ApplicationDelay%3E6E0E9700AB.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ApplicationDelay;
      //## end cAirbagProgram::ApplicationDelay%3E6E0E9700AB.attr

    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%3AB75C7A01C3
      //## Role: cAirbagProgram::SplitLine%3AB75C7B02B4
      //## begin cAirbagProgram::SplitLine%3AB75C7B02B4.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_SplitLine;
      //## end cAirbagProgram::SplitLine%3AB75C7B02B4.role

      //## Association: Control::Cell::<unnamed>%3AB75CC90220
      //## Role: cAirbagProgram::Printer%3AB75CCA02B8
      //## begin cAirbagProgram::Printer%3AB75CCA02B8.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_Printer;
      //## end cAirbagProgram::Printer%3AB75CCA02B8.role

      //## Association: Control::Cell::<unnamed>%3AB75D100381
      //## Role: cAirbagProgram::Scanner%3AB75D120012
      //## begin cAirbagProgram::Scanner%3AB75D120012.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_Scanner;
      //## end cAirbagProgram::Scanner%3AB75D120012.role

      //## Association: Control::Cell::<unnamed>%3ABF29BE030B
      //## Role: cAirbagProgram::CellData%3ABF29C0026E
      //## begin cAirbagProgram::CellData%3ABF29C0026E.role preserve=no  public: cDriver { -> 1RFHN}
      cDriver *_CellData;
      //## end cAirbagProgram::CellData%3ABF29C0026E.role

      //## Association: Control::Cell::<unnamed>%3AB72BCA0260
      //## Role: cAirbagProgram::MachineState%3AB72BCB0384
      //## begin cAirbagProgram::MachineState%3AB72BCB0384.role preserve=no  public: cState { -> 0..1RFHN}
      cState *_MachineState;
      //## end cAirbagProgram::MachineState%3AB72BCB0384.role

      //## Association: Control::Cell::<unnamed>%3ABF3B490309
      //## Role: cAirbagProgram::ObjectBuffer%3ABF3B4A0152
      //## begin cAirbagProgram::ObjectBuffer%3ABF3B4A0152.role preserve=no  public: cObjectBuffer { -> 1RFHN}
      cObjectBuffer *_ObjectBuffer;
      //## end cAirbagProgram::ObjectBuffer%3ABF3B4A0152.role

    // Additional Protected Declarations
      //## begin cAirbagProgram%3AB6258802B5.protected preserve=yes
      //## end cAirbagProgram%3AB6258802B5.protected

  private:
    // Additional Private Declarations
      //## begin cAirbagProgram%3AB6258802B5.private preserve=yes
      //## end cAirbagProgram%3AB6258802B5.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Barcode%3AB765FC00B4
      //## begin cAirbagProgram::Barcode%3AB765FC00B4.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Barcode;
      //## end cAirbagProgram::Barcode%3AB765FC00B4.attr

      //## Attribute: Retries%3AB7746002F6
      //## begin cAirbagProgram::Retries%3AB7746002F6.attr preserve=no  implementation: ULONG_T {U} 2
      ULONG_T _Retries;
      //## end cAirbagProgram::Retries%3AB7746002F6.attr

      //## Attribute: ActRetries%3AB77522011F
      //## begin cAirbagProgram::ActRetries%3AB77522011F.attr preserve=no  implementation: INT_T {U} 0
      INT_T _ActRetries;
      //## end cAirbagProgram::ActRetries%3AB77522011F.attr

      //## Attribute: PartCount%3AB77EEC01EA
      //## begin cAirbagProgram::PartCount%3AB77EEC01EA.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _PartCount;
      //## end cAirbagProgram::PartCount%3AB77EEC01EA.attr

      //## Attribute: Day%3ABF049D0155
      //## begin cAirbagProgram::Day%3ABF049D0155.attr preserve=no  implementation: INT_T {U} -1
      INT_T _Day;
      //## end cAirbagProgram::Day%3ABF049D0155.attr

      //## Attribute: PartToPrinter%3AED2F02038A
      //## begin cAirbagProgram::PartToPrinter%3AED2F02038A.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_PartToPrinter;
      //## end cAirbagProgram::PartToPrinter%3AED2F02038A.attr

      //## Attribute: MountLabel%3AED2F0203E4
      //## begin cAirbagProgram::MountLabel%3AED2F0203E4.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_MountLabel;
      //## end cAirbagProgram::MountLabel%3AED2F0203E4.attr

      //## Attribute: PartToScanner%3AED2F030043
      //## begin cAirbagProgram::PartToScanner%3AED2F030043.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_PartToScanner;
      //## end cAirbagProgram::PartToScanner%3AED2F030043.attr

      //## Attribute: RefusePart%3AED2F3E02F0
      //## begin cAirbagProgram::RefusePart%3AED2F3E02F0.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_RefusePart;
      //## end cAirbagProgram::RefusePart%3AED2F3E02F0.attr

      //## Attribute: AcceptPart%3AED2F5600CE
      //## begin cAirbagProgram::AcceptPart%3AED2F5600CE.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_AcceptPart;
      //## end cAirbagProgram::AcceptPart%3AED2F5600CE.attr

      //## Attribute: PartAtPrinter%3AED3AA5009F
      //## begin cAirbagProgram::PartAtPrinter%3AED3AA5009F.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_PartAtPrinter;
      //## end cAirbagProgram::PartAtPrinter%3AED3AA5009F.attr

      //## Attribute: LabelMounted%3AED3AA500EF
      //## begin cAirbagProgram::LabelMounted%3AED3AA500EF.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_LabelMounted;
      //## end cAirbagProgram::LabelMounted%3AED3AA500EF.attr

      //## Attribute: PartAtScanner%3AED3AA5013F
      //## begin cAirbagProgram::PartAtScanner%3AED3AA5013F.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_PartAtScanner;
      //## end cAirbagProgram::PartAtScanner%3AED3AA5013F.attr

      //## Attribute: MountFailure%3AED3AA5018F
      //## begin cAirbagProgram::MountFailure%3AED3AA5018F.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_MountFailure;
      //## end cAirbagProgram::MountFailure%3AED3AA5018F.attr

      //## Attribute: ApplicatorReady%3AED3AA501E9
      //## begin cAirbagProgram::ApplicatorReady%3AED3AA501E9.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_ApplicatorReady;
      //## end cAirbagProgram::ApplicatorReady%3AED3AA501E9.attr

      //## Attribute: Resync%3AED3AF80315
      //## begin cAirbagProgram::Resync%3AED3AF80315.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_Resync;
      //## end cAirbagProgram::Resync%3AED3AF80315.attr

      //## Attribute: MediaLow%3AED3AFA0372
      //## begin cAirbagProgram::MediaLow%3AED3AFA0372.attr preserve=no  implementation: cIOSignal * {U} NULL
      cIOSignal *_MediaLow;
      //## end cAirbagProgram::MediaLow%3AED3AFA0372.attr

      //## Attribute: LogEvent%3B7B978703D6
      //## begin cAirbagProgram::LogEvent%3B7B978703D6.attr preserve=no  implementation: cEventSem {U} 
      cEventSem _LogEvent;
      //## end cAirbagProgram::LogEvent%3B7B978703D6.attr

      //## Attribute: CycleBufMutex%3B7CC6DC03A3
      //## begin cAirbagProgram::CycleBufMutex%3B7CC6DC03A3.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _CycleBufMutex;
      //## end cAirbagProgram::CycleBufMutex%3B7CC6DC03A3.attr

    // Additional Implementation Declarations
      //## begin cAirbagProgram%3AB6258802B5.implementation preserve=yes
      //## end cAirbagProgram%3AB6258802B5.implementation

};

//## begin cAirbagProgram%3AB6258802B5.postscript preserve=yes
//## end cAirbagProgram%3AB6258802B5.postscript

// Class cAirbagProgram 

//## begin module%3AB6258802B5.epilog preserve=yes
//## end module%3AB6258802B5.epilog


#endif
