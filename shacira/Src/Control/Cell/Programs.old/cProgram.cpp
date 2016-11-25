//## begin module%3AA36AF4035B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AA36AF4035B.cm

//## begin module%3AA36AF4035B.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3AA36AF4035B.cp

//## Module: cProgram%3AA36AF4035B; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cProgram.cpp

//## begin module%3AA36AF4035B.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AA36AF4035B.additionalIncludes

//## begin module%3AA36AF4035B.includes preserve=yes
//## end module%3AA36AF4035B.includes

// cLogFile
#include "System/cLogFile.h"
// cIO
#include "System/Objects/cIO.h"
// cInfo
#include "System/Objects/cInfo.h"
// cAlarm
#include "System/Objects/cAlarm.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cDriver
#include "Control/Driver/cDriver.h"
// cCellLogger
#include "Control/Cell/cCellLogger.h"
// cCell
#include "Control/Cell/cCell.h"
// cCellDispatcher
#include "Control/Cell/cCellDispatcher.h"
// cProgram
#include "Control/Cell/Programs/cProgram.h"
// cIOSignal
#include "Control/DigitalChannel/cIOSignal.h"
// cDigitalIO
#include "Control/DigitalChannel/cDigitalIO.h"
//## begin module%3AA36AF4035B.additionalDeclarations preserve=yes
//## end module%3AA36AF4035B.additionalDeclarations


// Class cProgram 








cProgram::cProgram()
  //## begin cProgram::cProgram%.hasinit preserve=no
      : _ProgramState(0), _TestMode(0), _LogFile(NULL), _DigitalIO(NULL), _Cell(NULL)
  //## end cProgram::cProgram%.hasinit
  //## begin cProgram::cProgram%.initialization preserve=yes
  //## end cProgram::cProgram%.initialization
{
  //## begin cProgram::cProgram%.body preserve=yes
   _ThreadName = "cProgram";
  //## end cProgram::cProgram%.body
}

cProgram::cProgram(const cProgram &right)
  //## begin cProgram::cProgram%copy.hasinit preserve=no
      : _ProgramState(0), _TestMode(0), _LogFile(NULL), _DigitalIO(NULL), _Cell(NULL)
  //## end cProgram::cProgram%copy.hasinit
  //## begin cProgram::cProgram%copy.initialization preserve=yes
  //## end cProgram::cProgram%copy.initialization
{
  //## begin cProgram::cProgram%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProgram::cProgram%copy.body
}

cProgram::cProgram (cCell *cell, cConfigurationObject *config_obj)
  //## begin cProgram::cProgram%985080211.hasinit preserve=no
      : _ProgramState(0), _TestMode(0), _LogFile(NULL), _DigitalIO(NULL), _Cell(NULL)
  //## end cProgram::cProgram%985080211.hasinit
  //## begin cProgram::cProgram%985080211.initialization preserve=yes
  //## end cProgram::cProgram%985080211.initialization
{
  //## begin cProgram::cProgram%985080211.body preserve=yes
_ASSERT_COND(cell != NULL)
_ASSERT_COND(config_obj != NULL)
   _ThreadName = config_obj->get_Name().c_str();
   _Cell = cell;
   _DigitalIO = _Cell->_DigitalIO;
   _LogFileName = config_obj->PropertyValue("LogFileName", "");
   _TestMode = config_obj->PropertyValue("TestMode", _TestMode);
   if (_LogFileName.length() > 0) _LogFile = new cLogFile(_LogFileName.c_str());
  //## end cProgram::cProgram%985080211.body
}


cProgram::~cProgram()
{
  //## begin cProgram::~cProgram%.body preserve=yes
   DELETE_OBJECT(cLogFile, _LogFile)
  //## end cProgram::~cProgram%.body
}



//## Other Operations (implementation)
void cProgram::UseSignal (cIOSignal *signal)
{
  //## begin cProgram::UseSignal%984992067.body preserve=yes
   _DigitalIO->UseSignal(signal->get_Name().c_str(), _Cell);
  //## end cProgram::UseSignal%984992067.body
}

BOOL_T cProgram::Input (CONST_STRING_T name)
{
  //## begin cProgram::Input%984992068.body preserve=yes
   cIOSignal * io_signal = IOSignal(name);
   if (io_signal != NULL) {
      return io_signal->GetState();
   } else {
      throw cError(PROGRAM_UNKNOWN_IOSIGNAL, 0, name, _ThreadName.c_str());
   }
  //## end cProgram::Input%984992068.body
}

BOOL_T cProgram::Input (cIOSignal *io_signal)
{
  //## begin cProgram::Input%988620494.body preserve=yes
   if (io_signal != NULL) {
      return io_signal->GetState();
   } else {
      throw cError(PROGRAM_UNKNOWN_IOSIGNAL, 0, "?", _ThreadName.c_str());
   }
  //## end cProgram::Input%988620494.body
}

void cProgram::SetOutput (CONST_STRING_T name)
{
  //## begin cProgram::SetOutput%984992069.body preserve=yes
   cIOSignal * io_signal = IOSignal(name);
   if (io_signal != NULL) {
      io_signal->Set();
   } else {
      throw cError(PROGRAM_UNKNOWN_IOSIGNAL, 0, name, _ThreadName.c_str());
   }
  //## end cProgram::SetOutput%984992069.body
}

void cProgram::SetOutput (cIOSignal *io_signal)
{
  //## begin cProgram::SetOutput%988620495.body preserve=yes
   if (io_signal != NULL) {
      io_signal->Set();
   } else {
      throw cError(PROGRAM_UNKNOWN_IOSIGNAL, 0, "?", _ThreadName.c_str());
   }
  //## end cProgram::SetOutput%988620495.body
}

void cProgram::ResetOutput (CONST_STRING_T name)
{
  //## begin cProgram::ResetOutput%984992070.body preserve=yes
   cIOSignal * io_signal = IOSignal(name);
   if (io_signal != NULL) {
      io_signal->Reset();
   } else {
      throw cError(PROGRAM_UNKNOWN_IOSIGNAL, 0, name, _ThreadName.c_str());
   }
  //## end cProgram::ResetOutput%984992070.body
}

void cProgram::ResetOutput (cIOSignal *io_signal)
{
  //## begin cProgram::ResetOutput%988620496.body preserve=yes
   if (io_signal != NULL) {
      io_signal->Reset();
   } else {
      throw cError(PROGRAM_UNKNOWN_IOSIGNAL, 0, "?", _ThreadName.c_str());
   }
  //## end cProgram::ResetOutput%988620496.body
}

void cProgram::SetState (INT_T state)
{
  //## begin cProgram::SetState%985080207.body preserve=yes
   _ProgramState = state;
  //## end cProgram::SetState%985080207.body
}

cDriver * cProgram::Driver (CONST_STRING_T name)
{
  //## begin cProgram::Driver%985080214.body preserve=yes
return NULL;
//   return _Cell->DriverByName(name);
  //## end cProgram::Driver%985080214.body
}

cIOSignal * cProgram::IOSignal (CONST_STRING_T name)
{
  //## begin cProgram::IOSignal%984992074.body preserve=yes
   return _DigitalIO->SignalByName(name);
  //## end cProgram::IOSignal%984992074.body
}

void cProgram::SetAlarm (BOOL_T state, CONST_STRING_T ident)
{
  //## begin cProgram::SetAlarm%985267667.body preserve=yes
   cAlarm * alarm = new cAlarm(this, state, ident);
   _Cell->SendObjectTo(_Cell->_Dispatcher, alarm);
   RELEASE_OBJECT(alarm)
  //## end cProgram::SetAlarm%985267667.body
}

BOOL_T cProgram::LogPrintf (CONST_STRING_T fmt_str, ... )
{
  //## begin cProgram::LogPrintf%997694796.body preserve=yes
#define VA_BUF_SIZE      4096
   try {
      if (_LogFile) {
         va_list args;
         char text[VA_BUF_SIZE] = {0};
         va_start(args, fmt_str);
         vsprintf(text, fmt_str, args);
         va_end(args);
         return _LogFile->LogPrintf("%s\n", text);
      }
      return true;
   } catch (...) {
      return false;
   }
  //## end cProgram::LogPrintf%997694796.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cProgram::get_LogFileName () const
{
  //## begin cProgram::get_LogFileName%3B779C3C010C.get preserve=no
  return _LogFileName;
  //## end cProgram::get_LogFileName%3B779C3C010C.get
}

ULONG_T cProgram::get_TestMode () const
{
  //## begin cProgram::get_TestMode%3C35841E00E6.get preserve=no
  return _TestMode;
  //## end cProgram::get_TestMode%3C35841E00E6.get
}

// Additional Declarations
  //## begin cProgram%3AA36AF4035B.declarations preserve=yes
  //## end cProgram%3AA36AF4035B.declarations

//## begin module%3AA36AF4035B.epilog preserve=yes
//## end module%3AA36AF4035B.epilog
