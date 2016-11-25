//## begin module%3BD6C32703A9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BD6C32703A9.cm

//## begin module%3BD6C32703A9.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BD6C32703A9.cp

//## Module: cUSSProgram%3BD6C32703A9; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cUSSProgram.cpp

//## begin module%3BD6C32703A9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BD6C32703A9.additionalIncludes

//## begin module%3BD6C32703A9.includes preserve=yes
//## end module%3BD6C32703A9.includes

// cIO
#include "System/Objects/cIO.h"
// cState
#include "System/Objects/cState.h"
// cInfo
#include "System/Objects/cInfo.h"
// cDriver
#include "Control/Driver/cDriver.h"
// cCell
#include "Control/Cell/cCell.h"
// cUSSProgram
#include "Control/Cell/Programs/cUSSProgram.h"
// cIOSignal
#include "Control/DigitalChannel/cIOSignal.h"
// cDigitalIO
#include "Control/DigitalChannel/cDigitalIO.h"
//## begin module%3BD6C32703A9.additionalDeclarations preserve=yes

#define VALID_PARAM_SET       0
#define INVALID_PARAM_SET     15

#define CB_PENDING(cb) (cb != NULL)
#define STATE(state) ((state == _ProgramState) ? true : false)

typedef std::map<STRING_T, BOOL_T> SIGNAL_MAP_T;
static SIGNAL_MAP_T _ISignals;
static SIGNAL_MAP_T _OSignals;

#define SET_OUTPUT(signal) \
SetOutput(signal); \
LogSignal(signal, true);

#define RESET_OUTPUT(signal) \
ResetOutput(signal); \
LogSignal(signal, false);

#define NO_MOVEMENT     0
#define PART_REMOVED    1
#define PART_MOUNTED    2

#define RESET_CHECK_STATE(check_state)    check_state = 0;
#define CHECK(check_state,pos)            check_state |= (1 << pos);
#define CHECKED(check_state,pos)          (check_state & (1 << pos))

//## end module%3BD6C32703A9.additionalDeclarations


// Class cUSSProgram 



































cUSSProgram::cUSSProgram()
  //## begin cUSSProgram::cUSSProgram%.hasinit preserve=no
      : _I2OF5WorkAround(false), _ControlPartMovement(false), _RescanBarcode(false), _RescanBoth(false), _ExternalUSSControl(false), _IgnoreOldCode(false), _PartOffset(0), _Programmable(true), _CycleDelay(1000), _StaticBarcode("012345"), _USSWeld(NULL), _USSAlarm(NULL), _USSParamSet(NULL), _USSReset(NULL), _USSLock(NULL), _USSReady(NULL), _Alarm(NULL), _Retries(2), _ActRetries(0), _PartCount(0), _Day(-1), _ActColor(0), _ColorCode(9), _ColorSensor(NULL), _Scanner(NULL), _Printer(NULL), _CellData(NULL), _USS(NULL), _Scanner2(NULL)
  //## end cUSSProgram::cUSSProgram%.hasinit
  //## begin cUSSProgram::cUSSProgram%.initialization preserve=yes
  //## end cUSSProgram::cUSSProgram%.initialization
{
  //## begin cUSSProgram::cUSSProgram%.body preserve=yes
  //## end cUSSProgram::cUSSProgram%.body
}

cUSSProgram::cUSSProgram(const cUSSProgram &right)
  //## begin cUSSProgram::cUSSProgram%copy.hasinit preserve=no
      : _I2OF5WorkAround(false), _ControlPartMovement(false), _RescanBarcode(false), _RescanBoth(false), _ExternalUSSControl(false), _IgnoreOldCode(false), _PartOffset(0), _Programmable(true), _CycleDelay(1000), _StaticBarcode("012345"), _USSWeld(NULL), _USSAlarm(NULL), _USSParamSet(NULL), _USSReset(NULL), _USSLock(NULL), _USSReady(NULL), _Alarm(NULL), _Retries(2), _ActRetries(0), _PartCount(0), _Day(-1), _ActColor(0), _ColorCode(9), _ColorSensor(NULL), _Scanner(NULL), _Printer(NULL), _CellData(NULL), _USS(NULL), _Scanner2(NULL)
  //## end cUSSProgram::cUSSProgram%copy.hasinit
  //## begin cUSSProgram::cUSSProgram%copy.initialization preserve=yes
  //## end cUSSProgram::cUSSProgram%copy.initialization
{
  //## begin cUSSProgram::cUSSProgram%copy.body preserve=yes
  //## end cUSSProgram::cUSSProgram%copy.body
}

cUSSProgram::cUSSProgram (cCell *cell, cConfigurationObject *config_obj)
  //## begin cUSSProgram::cUSSProgram%1003916882.hasinit preserve=no
      : _I2OF5WorkAround(false), _ControlPartMovement(false), _RescanBarcode(false), _RescanBoth(false), _ExternalUSSControl(false), _IgnoreOldCode(false), _PartOffset(0), _Programmable(true), _CycleDelay(1000), _StaticBarcode("012345"), _USSWeld(NULL), _USSAlarm(NULL), _USSParamSet(NULL), _USSReset(NULL), _USSLock(NULL), _USSReady(NULL), _Alarm(NULL), _Retries(2), _ActRetries(0), _PartCount(0), _Day(-1), _ActColor(0), _ColorCode(9), _ColorSensor(NULL), _Scanner(NULL), _Printer(NULL), _CellData(NULL), _USS(NULL), _Scanner2(NULL)
  //## end cUSSProgram::cUSSProgram%1003916882.hasinit
  //## begin cUSSProgram::cUSSProgram%1003916882.initialization preserve=yes
   , cProgram(cell, config_obj)
  //## end cUSSProgram::cUSSProgram%1003916882.initialization
{
  //## begin cUSSProgram::cUSSProgram%1003916882.body preserve=yes
_ASSERT_COND(cell != NULL)
_ASSERT_COND(config_obj != NULL)
_ASSERT_COND(_DigitalIO != NULL)
   set_Name(config_obj->get_Name());
   _Retries = config_obj->PropertyValue("Retries", _Retries);
   _BarcodeProlog = config_obj->PropertyValue("BarcodeProlog", "");
   _I2OF5WorkAround = config_obj->PropertyValue("I2OF5WorkAround", _I2OF5WorkAround);
   _ControlPartMovement = config_obj->PropertyValue("ControlPartMovement", _ControlPartMovement);
   _RescanBarcode = config_obj->PropertyValue("RescanBarcode", _RescanBarcode);
   _RescanBoth = config_obj->PropertyValue("RescanBoth", _RescanBoth);
   _ExternalUSSControl = config_obj->PropertyValue("ExternalUSSControl", _ExternalUSSControl);
   _IgnoreOldCode = config_obj->PropertyValue("IgnoreOldCode", _IgnoreOldCode);
   _Programmable = config_obj->PropertyValue("Programmable", _Programmable);
   _PartOffset = config_obj->PropertyValue("PartOffset", _PartOffset);
   _CycleDelay = config_obj->PropertyValue("CycleDelay", _CycleDelay);
   _StaticBarcode = config_obj->PropertyValue("StaticBarcode", _StaticBarcode.c_str());
   STRING_T driver_name;
   driver_name = config_obj->PropertyValue("USS", "");
   _USS = Driver(driver_name.c_str());
_ASSERT_COND(_USS != NULL)
   driver_name = config_obj->PropertyValue("ColorSensor", "");
   _ColorSensor = Driver(driver_name.c_str());
_ASSERT_COND(_ColorSensor != NULL)
   driver_name = config_obj->PropertyValue("BarcodePrinter", "");
   _Printer = Driver(driver_name.c_str());
_ASSERT_COND(_Printer != NULL)
   driver_name = config_obj->PropertyValue("BarcodeScanner", "");
   _Scanner = Driver(driver_name.c_str());
_ASSERT_COND(_Scanner != NULL)
   driver_name = config_obj->PropertyValue("BarcodeScanner2", "");
   if (driver_name.size() > 0) {
      _Scanner2 = Driver(driver_name.c_str());
_ASSERT_COND(_Scanner2 != NULL)
   } else {
      _Scanner2 = _Scanner;
   }
   driver_name = config_obj->PropertyValue("Cell", "");
   _CellData = Driver(driver_name.c_str());
_ASSERT_COND(_CellData != NULL)
   STRING_T signal_name;

   // Output Signals
   signal_name = config_obj->PropertyValue("USSParamSet", "");
   _USSParamSet = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_USSParamSet != NULL)
   signal_name = config_obj->PropertyValue("USSReset", "");
   _USSReset = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_USSReset != NULL)
   signal_name = config_obj->PropertyValue("USSLock", "");
   _USSLock = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_USSLock != NULL)
   signal_name = config_obj->PropertyValue("Alarm", "");
   _Alarm = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_Alarm != NULL)

   // Input Signals
   signal_name = config_obj->PropertyValue("USSReady", "");
   _USSReady = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_USSReady != NULL)
   signal_name = config_obj->PropertyValue("USSWeld", "");
   _USSWeld = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_USSWeld != NULL)
   signal_name = config_obj->PropertyValue("USSAlarm", "");
   _USSAlarm = _DigitalIO->SignalByName(signal_name.c_str());
_ASSERT_COND(_USSAlarm != NULL)

  //## end cUSSProgram::cUSSProgram%1003916882.body
}


cUSSProgram::~cUSSProgram()
{
  //## begin cUSSProgram::~cUSSProgram%.body preserve=yes
  //## end cUSSProgram::~cUSSProgram%.body
}



//## Other Operations (implementation)
BOOL_T cUSSProgram::Start ()
{
  //## begin cUSSProgram::Start%1047387663.body preserve=yes
	return true;
  //## end cUSSProgram::Start%1047387663.body
}

BOOL_T cUSSProgram::Stop ()
{
  //## begin cUSSProgram::Stop%1047387664.body preserve=yes
	return true;
  //## end cUSSProgram::Stop%1047387664.body
}

void cUSSProgram::ProcessEvent (cTransientObject *object)
{
  //## begin cUSSProgram::ProcessEvent%1047387665.body preserve=yes
  //## end cUSSProgram::ProcessEvent%1047387665.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cUSSProgram::get_BarcodeProlog () const
{
  //## begin cUSSProgram::get_BarcodeProlog%3BD6DE7D01A3.get preserve=no
  return _BarcodeProlog;
  //## end cUSSProgram::get_BarcodeProlog%3BD6DE7D01A3.get
}

BOOL_T cUSSProgram::get_I2OF5WorkAround () const
{
  //## begin cUSSProgram::get_I2OF5WorkAround%3BD6DE7D01C1.get preserve=no
  return _I2OF5WorkAround;
  //## end cUSSProgram::get_I2OF5WorkAround%3BD6DE7D01C1.get
}

BOOL_T cUSSProgram::get_ControlPartMovement () const
{
  //## begin cUSSProgram::get_ControlPartMovement%3BD83C2B01AA.get preserve=no
  return _ControlPartMovement;
  //## end cUSSProgram::get_ControlPartMovement%3BD83C2B01AA.get
}

BOOL_T cUSSProgram::get_RescanBarcode () const
{
  //## begin cUSSProgram::get_RescanBarcode%3C3B0523024F.get preserve=no
  return _RescanBarcode;
  //## end cUSSProgram::get_RescanBarcode%3C3B0523024F.get
}

BOOL_T cUSSProgram::get_RescanBoth () const
{
  //## begin cUSSProgram::get_RescanBoth%3E6E115E036B.get preserve=no
  return _RescanBoth;
  //## end cUSSProgram::get_RescanBoth%3E6E115E036B.get
}

BOOL_T cUSSProgram::get_ExternalUSSControl () const
{
  //## begin cUSSProgram::get_ExternalUSSControl%3BE93F4401FC.get preserve=no
  return _ExternalUSSControl;
  //## end cUSSProgram::get_ExternalUSSControl%3BE93F4401FC.get
}

BOOL_T cUSSProgram::get_IgnoreOldCode () const
{
  //## begin cUSSProgram::get_IgnoreOldCode%3E6E106F02FD.get preserve=no
  return _IgnoreOldCode;
  //## end cUSSProgram::get_IgnoreOldCode%3E6E106F02FD.get
}

ULONG_T cUSSProgram::get_PartOffset () const
{
  //## begin cUSSProgram::get_PartOffset%3E6E118B000F.get preserve=no
  return _PartOffset;
  //## end cUSSProgram::get_PartOffset%3E6E118B000F.get
}

BOOL_T cUSSProgram::get_Programmable () const
{
  //## begin cUSSProgram::get_Programmable%3E6E109B038A.get preserve=no
  return _Programmable;
  //## end cUSSProgram::get_Programmable%3E6E109B038A.get
}

ULONG_T cUSSProgram::get_CycleDelay () const
{
  //## begin cUSSProgram::get_CycleDelay%3E6E1100030D.get preserve=no
  return _CycleDelay;
  //## end cUSSProgram::get_CycleDelay%3E6E1100030D.get
}

STRING_T cUSSProgram::get_StaticBarcode () const
{
  //## begin cUSSProgram::get_StaticBarcode%3E6E10C9030D.get preserve=no
  return _StaticBarcode;
  //## end cUSSProgram::get_StaticBarcode%3E6E10C9030D.get
}

// Additional Declarations
  //## begin cUSSProgram%3BD6C32703A9.declarations preserve=yes
  //## end cUSSProgram%3BD6C32703A9.declarations

//## begin module%3BD6C32703A9.epilog preserve=yes
//## end module%3BD6C32703A9.epilog
