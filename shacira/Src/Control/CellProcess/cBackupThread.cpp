//## begin module%3AE85FA80391.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AE85FA80391.cm

//## begin module%3AE85FA80391.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AE85FA80391.cp

//## Module: cBackupThread%3AE85FA80391; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\CellProcess\cBackupThread.cpp

//## begin module%3AE85FA80391.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AE85FA80391.additionalIncludes

//## begin module%3AE85FA80391.includes preserve=yes
//## end module%3AE85FA80391.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cSysProcess
#include "System/Sys/cSysProcess.h"
// cBackupThread
#include "Control/CellProcess/cBackupThread.h"
// cCellProcess
#include "Control/CellProcess/cCellProcess.h"
//## begin module%3AE85FA80391.additionalDeclarations preserve=yes

#define MINUTES_PER_HOUR   59
#define SECONDS_PER_MINUTE 59

//## end module%3AE85FA80391.additionalDeclarations


// Class cBackupThread 









cBackupThread::cBackupThread()
  //## begin cBackupThread::cBackupThread%.hasinit preserve=no
      : _Hours(1), _Minutes(0), _HoursLeft(0), _MinutesLeft(0), _SecondsLeft(0), _Process(NULL)
  //## end cBackupThread::cBackupThread%.hasinit
  //## begin cBackupThread::cBackupThread%.initialization preserve=yes
  //## end cBackupThread::cBackupThread%.initialization
{
  //## begin cBackupThread::cBackupThread%.body preserve=yes
  //## end cBackupThread::cBackupThread%.body
}

cBackupThread::cBackupThread(const cBackupThread &right)
  //## begin cBackupThread::cBackupThread%copy.hasinit preserve=no
      : _Hours(1), _Minutes(0), _HoursLeft(0), _MinutesLeft(0), _SecondsLeft(0), _Process(NULL)
  //## end cBackupThread::cBackupThread%copy.hasinit
  //## begin cBackupThread::cBackupThread%copy.initialization preserve=yes
  //## end cBackupThread::cBackupThread%copy.initialization
{
  //## begin cBackupThread::cBackupThread%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cBackupThread::cBackupThread%copy.body
}

cBackupThread::cBackupThread (cCellProcess *process, cConfigurationObject *config_obj)
  //## begin cBackupThread::cBackupThread%988306474.hasinit preserve=no
      : _Hours(1), _Minutes(0), _HoursLeft(0), _MinutesLeft(0), _SecondsLeft(0), _Process(NULL)
  //## end cBackupThread::cBackupThread%988306474.hasinit
  //## begin cBackupThread::cBackupThread%988306474.initialization preserve=yes
  //## end cBackupThread::cBackupThread%988306474.initialization
{
  //## begin cBackupThread::cBackupThread%988306474.body preserve=yes
_ASSERT_COND(process != NULL)
_ASSERT_COND(config_obj != NULL)
   _Name = config_obj->get_Name();
   _Process = process;
   _Source = _Process->get_BaseDir();
   _Minutes = config_obj->PropertyValue("Minutes", _Minutes);
   _Hours = config_obj->PropertyValue("Hours", _Hours);
   STRING_VECTOR_T string_vec;
   config_obj->PropertyValue("BackupDirs", string_vec);
   int list_len = string_vec.size();
   if (list_len > 0) {
      for (int i=0; i<list_len; i++) {
         _DestinationList.push_back(string_vec[i].c_str());
      }
   }
   ResetTicker();
  //## end cBackupThread::cBackupThread%988306474.body
}


cBackupThread::~cBackupThread()
{
  //## begin cBackupThread::~cBackupThread%.body preserve=yes
  //## end cBackupThread::~cBackupThread%.body
}



//## Other Operations (implementation)
INT_T cBackupThread::ControlFunc ()
{
  //## begin cBackupThread::ControlFunc%988306475.body preserve=yes
CONTROLFUNC_PROLOG(_Name.c_str())
   Tick();
   if (_SecondsLeft == 0 &&
       _MinutesLeft == 0 &&
       _HoursLeft == 0) {
      Backup();
      ResetTicker();
   }
   return 0;
CONTROLFUNC_EPILOG
  //## end cBackupThread::ControlFunc%988306475.body
}

void cBackupThread::Backup ()
{
  //## begin cBackupThread::Backup%988306476.body preserve=yes
   STRING_LIST_T::const_iterator destination = _DestinationList.cbegin();
   while (destination != _DestinationList.cend()) {
      Copy(_Source.c_str(), (*destination).c_str());
      destination++;
   }
  //## end cBackupThread::Backup%988306476.body
}

void cBackupThread::Copy (CONST_STRING_T source, CONST_STRING_T destination)
{
  //## begin cBackupThread::Copy%988306477.body preserve=yes
   const char * cmd = "XCOPY";
   STRING_T args = source;
   args += " ";
   args += destination;
   args += " /S /D /C /I";
   cSysProcess proc;
   if (!proc.Spawn(cmd, args.c_str())) {
      InfoPrintf("%s %s failed\n", cmd, args.c_str());
   } else {
//      InfoPrintf("%s %s\n", cmd, args.c_str());
   }
  //## end cBackupThread::Copy%988306477.body
}

void cBackupThread::ResetTicker ()
{
  //## begin cBackupThread::ResetTicker%988356820.body preserve=yes
   _HoursLeft = _Hours;
   _MinutesLeft = _Minutes;
   _SecondsLeft = 1;
  //## end cBackupThread::ResetTicker%988356820.body
}

void cBackupThread::Tick ()
{
  //## begin cBackupThread::Tick%988356821.body preserve=yes
   _SecondsLeft--;
   if (_SecondsLeft == 0) {
      if (_MinutesLeft > 0) {
         _SecondsLeft = SECONDS_PER_MINUTE;
         _MinutesLeft--;
      } else {
         if (_HoursLeft > 0) {
            _SecondsLeft = SECONDS_PER_MINUTE;
            _MinutesLeft = MINUTES_PER_HOUR;
            _HoursLeft--;
         }
      }
   }
//cout << "Time " << _HoursLeft << "/" << _MinutesLeft << "/" << _SecondsLeft << endl;
  //## end cBackupThread::Tick%988356821.body
}

// Additional Declarations
  //## begin cBackupThread%3AE85FA80391.declarations preserve=yes
  //## end cBackupThread%3AE85FA80391.declarations

//## begin module%3AE85FA80391.epilog preserve=yes
//## end module%3AE85FA80391.epilog
