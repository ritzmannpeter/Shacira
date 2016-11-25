//## begin module%3C59098602B7.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C59098602B7.cm

//## begin module%3C59098602B7.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3C59098602B7.cp

//## Module: cShutDownControl%3C59098602B7; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cShutDownControl.cpp

//## begin module%3C59098602B7.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C59098602B7.additionalIncludes

//## begin module%3C59098602B7.includes preserve=yes
//## end module%3C59098602B7.includes

// cShutDownControl
#include "System/Process/cShutDownControl.h"
//## begin module%3C59098602B7.additionalDeclarations preserve=yes
//## end module%3C59098602B7.additionalDeclarations


// Class cShutDownControl 



cShutDownControl::cShutDownControl()
  //## begin cShutDownControl::cShutDownControl%.hasinit preserve=no
      : _ShutDownControlTime(10000)
  //## end cShutDownControl::cShutDownControl%.hasinit
  //## begin cShutDownControl::cShutDownControl%.initialization preserve=yes
  //## end cShutDownControl::cShutDownControl%.initialization
{
  //## begin cShutDownControl::cShutDownControl%.body preserve=yes
  //## end cShutDownControl::cShutDownControl%.body
}

cShutDownControl::cShutDownControl(const cShutDownControl &right)
  //## begin cShutDownControl::cShutDownControl%copy.hasinit preserve=no
      : _ShutDownControlTime(10000)
  //## end cShutDownControl::cShutDownControl%copy.hasinit
  //## begin cShutDownControl::cShutDownControl%copy.initialization preserve=yes
  //## end cShutDownControl::cShutDownControl%copy.initialization
{
  //## begin cShutDownControl::cShutDownControl%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cShutDownControl::cShutDownControl%copy.body
}

cShutDownControl::cShutDownControl (ULONG_T control_time)
  //## begin cShutDownControl::cShutDownControl%1012464114.hasinit preserve=no
      : _ShutDownControlTime(10000)
  //## end cShutDownControl::cShutDownControl%1012464114.hasinit
  //## begin cShutDownControl::cShutDownControl%1012464114.initialization preserve=yes
  //## end cShutDownControl::cShutDownControl%1012464114.initialization
{
  //## begin cShutDownControl::cShutDownControl%1012464114.body preserve=yes
   _ShutDownControlTime = control_time;
   _Name = "ShutDownControl";
  //## end cShutDownControl::cShutDownControl%1012464114.body
}


cShutDownControl::~cShutDownControl()
{
  //## begin cShutDownControl::~cShutDownControl%.body preserve=yes
  //## end cShutDownControl::~cShutDownControl%.body
}



//## Other Operations (implementation)
INT_T cShutDownControl::MainFunc (void *extra)
{
  //## begin cShutDownControl::MainFunc%1012464115.body preserve=yes
#ifdef __GNUC__
#else
   __try {
      cSystemUtils::Suspend(_ShutDownControlTime);
      ErrorPrintf("ShutDown timeout %d expired stopping ...\n", _ShutDownControlTime);
      _exit(-7);
   } __except(EXCEPTION_EXECUTE_HANDLER) {
      InfoPrintf("Structured exception while stopping\n");
      exit(-7);
   }
#endif
   return 0;
  //## end cShutDownControl::MainFunc%1012464115.body
}

// Additional Declarations
  //## begin cShutDownControl%3C59098602B7.declarations preserve=yes
  //## end cShutDownControl%3C59098602B7.declarations

//## begin module%3C59098602B7.epilog preserve=yes
//## end module%3C59098602B7.epilog
