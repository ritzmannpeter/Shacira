//## begin module%3AB6258802B5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AB6258802B5.cm

//## begin module%3AB6258802B5.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3AB6258802B5.cp

//## Module: cAirbagProgram%3AB6258802B5; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cAirbagProgram.cpp

//## begin module%3AB6258802B5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AB6258802B5.additionalIncludes

//## begin module%3AB6258802B5.includes preserve=yes
//## end module%3AB6258802B5.includes

// cIO
#include "System/Objects/cIO.h"
// cState
#include "System/Objects/cState.h"
// cObjectBuffer
#include "System/Objects/cObjectBuffer.h"
// cInfo
#include "System/Objects/cInfo.h"
// cDriver
#include "Control/Driver/cDriver.h"
// cCell
#include "Control/Cell/cCell.h"
// cAirbagProgram
#include "Control/Cell/Programs/cAirbagProgram.h"
// cIOSignal
#include "Control/DigitalChannel/cIOSignal.h"
// cDigitalIO
#include "Control/DigitalChannel/cDigitalIO.h"
//## begin module%3AB6258802B5.additionalDeclarations preserve=yes

#define CB_PENDING(cb) (cb != NULL)
#define STATE(state) ((state == _ProgramState) ? true : false)

typedef std::map<STRING_T, BOOL_T> SIGNAL_MAP_T;
static SIGNAL_MAP_T _ISignals;
static SIGNAL_MAP_T _OSignals;

#undef USE_TIMED_SYNC

#define SET_OUTPUT(signal) \
SetOutput(signal); \
LogSignal(signal, true);

#define RESET_OUTPUT(signal) \
ResetOutput(signal); \
LogSignal(signal, false);

#define NEW
#ifdef NEW

#define __LOCK__ \
   cObjectLock __lock__(this);
#include "System\cIniFile.h"
static void SaveBarcode(CONST_STRING_T barcode)
{
   cIniFile ini_file("Barcode.dat");
   ini_file.WriteValue("Barcode", "Barcode", barcode);
}

#endif

//## end module%3AB6258802B5.additionalDeclarations


// Class cAirbagProgram 






































cAirbagProgram::cAirbagProgram()
  //## begin cAirbagProgram::cAirbagProgram%.hasinit preserve=no
      : _Retries(2), _ActRetries(0), _PartCount(0), _Day(-1), _IgnoreApplication(false), _IgnoreApplicator(false), _IgnoreHandling(false), _SyncTime(5000), _I2OF5WorkAround(false), _PrintmarkWorkAround(false), _Ventus610(false), _ControlDanglingParts(false), _RefuseTime(500), _PartOffset(0), _ApplicationDelay(0), _PartToPrinter(NULL), _MountLabel(NULL), _PartToScanner(NULL), _RefusePart(NULL), _AcceptPart(NULL), _PartAtPrinter(NULL), _LabelMounted(NULL), _PartAtScanner(NULL), _MountFailure(NULL), _ApplicatorReady(NULL), _Resync(NULL), _MediaLow(NULL), _SplitLine(NULL), _Printer(NULL), _Scanner(NULL), _CellData(NULL), _MachineState(NULL), _ObjectBuffer(NULL)
  //## end cAirbagProgram::cAirbagProgram%.hasinit
  //## begin cAirbagProgram::cAirbagProgram%.initialization preserve=yes
  //## end cAirbagProgram::cAirbagProgram%.initialization
{
  //## begin cAirbagProgram::cAirbagProgram%.body preserve=yes
  //## end cAirbagProgram::cAirbagProgram%.body
}

cAirbagProgram::cAirbagProgram(const cAirbagProgram &right)
  //## begin cAirbagProgram::cAirbagProgram%copy.hasinit preserve=no
      : _Retries(2), _ActRetries(0), _PartCount(0), _Day(-1), _IgnoreApplication(false), _IgnoreApplicator(false), _IgnoreHandling(false), _SyncTime(5000), _I2OF5WorkAround(false), _PrintmarkWorkAround(false), _Ventus610(false), _ControlDanglingParts(false), _RefuseTime(500), _PartOffset(0), _ApplicationDelay(0), _PartToPrinter(NULL), _MountLabel(NULL), _PartToScanner(NULL), _RefusePart(NULL), _AcceptPart(NULL), _PartAtPrinter(NULL), _LabelMounted(NULL), _PartAtScanner(NULL), _MountFailure(NULL), _ApplicatorReady(NULL), _Resync(NULL), _MediaLow(NULL), _SplitLine(NULL), _Printer(NULL), _Scanner(NULL), _CellData(NULL), _MachineState(NULL), _ObjectBuffer(NULL)
  //## end cAirbagProgram::cAirbagProgram%copy.hasinit
  //## begin cAirbagProgram::cAirbagProgram%copy.initialization preserve=yes
  //## end cAirbagProgram::cAirbagProgram%copy.initialization
{
  //## begin cAirbagProgram::cAirbagProgram%copy.body preserve=yes
  //## end cAirbagProgram::cAirbagProgram%copy.body
}

cAirbagProgram::cAirbagProgram (cCell *cell, cConfigurationObject *config_obj)
  //## begin cAirbagProgram::cAirbagProgram%985080212.hasinit preserve=no
      : _Retries(2), _ActRetries(0), _PartCount(0), _Day(-1), _IgnoreApplication(false), _IgnoreApplicator(false), _IgnoreHandling(false), _SyncTime(5000), _I2OF5WorkAround(false), _PrintmarkWorkAround(false), _Ventus610(false), _ControlDanglingParts(false), _RefuseTime(500), _PartOffset(0), _ApplicationDelay(0), _PartToPrinter(NULL), _MountLabel(NULL), _PartToScanner(NULL), _RefusePart(NULL), _AcceptPart(NULL), _PartAtPrinter(NULL), _LabelMounted(NULL), _PartAtScanner(NULL), _MountFailure(NULL), _ApplicatorReady(NULL), _Resync(NULL), _MediaLow(NULL), _SplitLine(NULL), _Printer(NULL), _Scanner(NULL), _CellData(NULL), _MachineState(NULL), _ObjectBuffer(NULL)
  //## end cAirbagProgram::cAirbagProgram%985080212.hasinit
  //## begin cAirbagProgram::cAirbagProgram%985080212.initialization preserve=yes
   , cProgram(cell, config_obj)
  //## end cAirbagProgram::cAirbagProgram%985080212.initialization
{
  //## begin cAirbagProgram::cAirbagProgram%985080212.body preserve=yes
_ASSERT_COND(cell != NULL)
_ASSERT_COND(config_obj != NULL)
_ASSERT_COND(_DigitalIO != NULL)
   _ThreadName = config_obj->get_Name();
   _ObjectBuffer = new cObjectBuffer(1);
   _Retries = config_obj->PropertyValue("Retries", _Retries);
   _SyncTime = config_obj->PropertyValue("SyncTime", _SyncTime);
   _RefuseTime = config_obj->PropertyValue("RefuseTime", _RefuseTime);
   _IgnoreApplication = config_obj->PropertyValue("IgnoreApplication", _IgnoreApplication);
   _IgnoreApplicator = config_obj->PropertyValue("IgnoreApplicator", _IgnoreApplicator);
   _IgnoreHandling = config_obj->PropertyValue("IgnoreHandling", _IgnoreHandling);
   _BarcodeProlog = config_obj->PropertyValue("BarcodeProlog", "");
   _I2OF5WorkAround = config_obj->PropertyValue("I2OF5WorkAround", _I2OF5WorkAround);
   _PrintmarkWorkAround = config_obj->PropertyValue("PrintmarkWorkAround", _PrintmarkWorkAround);
   _ControlDanglingParts = config_obj->PropertyValue("ControlDanglingParts", _ControlDanglingParts);
   _PartOffset = config_obj->PropertyValue("PartOffset", _PartOffset);
   _Ventus610 = config_obj->PropertyValue("Ventus610", _Ventus610);
   _ApplicationDelay = config_obj->PropertyValue("ApplicationDelay", _ApplicationDelay);
   STRING_T driver_name;
   driver_name = config_obj->PropertyValue("SplitLine", "");
   _SplitLine = Driver(driver_name.c_str());
_ASSERT_COND(_SplitLine != NULL)
   driver_name = config_obj->PropertyValue("BarcodePrinter", "");
   _Printer = Driver(driver_name.c_str());
_ASSERT_COND(_Printer != NULL)
   driver_name = config_obj->PropertyValue("BarcodeScanner", "");
   _Scanner = Driver(driver_name.c_str());
_ASSERT_COND(_Scanner != NULL)
   driver_name = config_obj->PropertyValue("Cell", "");
   _CellData = Driver(driver_name.c_str());
_ASSERT_COND(_CellData != NULL)
   STRING_T signal_name;

   // Output Signals
   signal_name = config_obj->PropertyValue("PartToPrinter", "");
   _PartToPrinter = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_PartToPrinter != NULL)
   signal_name = config_obj->PropertyValue("MountLabel", "");
   _MountLabel = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_MountLabel != NULL)
   signal_name = config_obj->PropertyValue("PartToScanner", "");
   _PartToScanner = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_PartToScanner != NULL)
   signal_name = config_obj->PropertyValue("RefusePart", "");
   _RefusePart = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_RefusePart != NULL)
   signal_name = config_obj->PropertyValue("AcceptPart", "");
   _AcceptPart = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_AcceptPart != NULL)

   // Input Signals
   signal_name = config_obj->PropertyValue("PartAtPrinter", "");
   _PartAtPrinter = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_PartAtPrinter != NULL)
   signal_name = config_obj->PropertyValue("LabelMounted", "");
   _LabelMounted = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_LabelMounted != NULL)
   signal_name = config_obj->PropertyValue("PartAtScanner", "");
   _PartAtScanner = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_PartAtScanner != NULL)
   signal_name = config_obj->PropertyValue("MountFailure", "");
   _MountFailure = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_MountFailure != NULL)
   signal_name = config_obj->PropertyValue("ApplicatorReady", "");
   _ApplicatorReady = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_ApplicatorReady != NULL)
   signal_name = config_obj->PropertyValue("MediaLow", "");
   _MediaLow = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_MediaLow != NULL)
   signal_name = config_obj->PropertyValue("Resync", "");
   _Resync = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_Resync != NULL)
  //## end cAirbagProgram::cAirbagProgram%985080212.body
}


cAirbagProgram::~cAirbagProgram()
{
  //## begin cAirbagProgram::~cAirbagProgram%.body preserve=yes
   DELETE_OBJECT(cObjectBuffer, _ObjectBuffer)
  //## end cAirbagProgram::~cAirbagProgram%.body
}



//## Other Operations (implementation)
BOOL_T cAirbagProgram::Start ()
{
  //## begin cAirbagProgram::Start%1047387657.body preserve=yes
	return true;
  //## end cAirbagProgram::Start%1047387657.body
}

BOOL_T cAirbagProgram::Stop ()
{
  //## begin cAirbagProgram::Stop%1047387658.body preserve=yes
	return true;
  //## end cAirbagProgram::Stop%1047387658.body
}

void cAirbagProgram::ProcessEvent (cTransientObject *object)
{
  //## begin cAirbagProgram::ProcessEvent%1047387659.body preserve=yes
  //## end cAirbagProgram::ProcessEvent%1047387659.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cAirbagProgram::get_IgnoreApplication () const
{
  //## begin cAirbagProgram::get_IgnoreApplication%3ACDC2E6036F.get preserve=no
  return _IgnoreApplication;
  //## end cAirbagProgram::get_IgnoreApplication%3ACDC2E6036F.get
}

BOOL_T cAirbagProgram::get_IgnoreApplicator () const
{
  //## begin cAirbagProgram::get_IgnoreApplicator%3B0267DD0312.get preserve=no
  return _IgnoreApplicator;
  //## end cAirbagProgram::get_IgnoreApplicator%3B0267DD0312.get
}

BOOL_T cAirbagProgram::get_IgnoreHandling () const
{
  //## begin cAirbagProgram::get_IgnoreHandling%3B0293BB01A7.get preserve=no
  return _IgnoreHandling;
  //## end cAirbagProgram::get_IgnoreHandling%3B0293BB01A7.get
}

STRING_T cAirbagProgram::get_BarcodeProlog () const
{
  //## begin cAirbagProgram::get_BarcodeProlog%3B0267AB0279.get preserve=no
  return _BarcodeProlog;
  //## end cAirbagProgram::get_BarcodeProlog%3B0267AB0279.get
}

ULONG_T cAirbagProgram::get_SyncTime () const
{
  //## begin cAirbagProgram::get_SyncTime%3ADD59270192.get preserve=no
  return _SyncTime;
  //## end cAirbagProgram::get_SyncTime%3ADD59270192.get
}

BOOL_T cAirbagProgram::get_I2OF5WorkAround () const
{
  //## begin cAirbagProgram::get_I2OF5WorkAround%3B038BEA01FB.get preserve=no
  return _I2OF5WorkAround;
  //## end cAirbagProgram::get_I2OF5WorkAround%3B038BEA01FB.get
}

BOOL_T cAirbagProgram::get_PrintmarkWorkAround () const
{
  //## begin cAirbagProgram::get_PrintmarkWorkAround%3E6E0E1F01A5.get preserve=no
  return _PrintmarkWorkAround;
  //## end cAirbagProgram::get_PrintmarkWorkAround%3E6E0E1F01A5.get
}

BOOL_T cAirbagProgram::get_Ventus610 () const
{
  //## begin cAirbagProgram::get_Ventus610%3E6E0E6E0177.get preserve=no
  return _Ventus610;
  //## end cAirbagProgram::get_Ventus610%3E6E0E6E0177.get
}

BOOL_T cAirbagProgram::get_ControlDanglingParts () const
{
  //## begin cAirbagProgram::get_ControlDanglingParts%3B77C07A02BC.get preserve=no
  return _ControlDanglingParts;
  //## end cAirbagProgram::get_ControlDanglingParts%3B77C07A02BC.get
}

ULONG_T cAirbagProgram::get_RefuseTime () const
{
  //## begin cAirbagProgram::get_RefuseTime%3B7B9EA90150.get preserve=no
  return _RefuseTime;
  //## end cAirbagProgram::get_RefuseTime%3B7B9EA90150.get
}

ULONG_T cAirbagProgram::get_PartOffset () const
{
  //## begin cAirbagProgram::get_PartOffset%3E6E0E4903D8.get preserve=no
  return _PartOffset;
  //## end cAirbagProgram::get_PartOffset%3E6E0E4903D8.get
}

ULONG_T cAirbagProgram::get_ApplicationDelay () const
{
  //## begin cAirbagProgram::get_ApplicationDelay%3E6E0E9700AB.get preserve=no
  return _ApplicationDelay;
  //## end cAirbagProgram::get_ApplicationDelay%3E6E0E9700AB.get
}

// Additional Declarations
  //## begin cAirbagProgram%3AB6258802B5.declarations preserve=yes
  //## end cAirbagProgram%3AB6258802B5.declarations

//## begin module%3AB6258802B5.epilog preserve=yes
//## end module%3AB6258802B5.epilog
