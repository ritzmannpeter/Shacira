//## begin module%3D21E86F000D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D21E86F000D.cm

//## begin module%3D21E86F000D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3D21E86F000D.cp

//## Module: cSPSProgram%3D21E86F000D; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cSPSProgram.cpp

//## begin module%3D21E86F000D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3D21E86F000D.additionalIncludes

//## begin module%3D21E86F000D.includes preserve=yes
//## end module%3D21E86F000D.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cCell
#include "Control/Cell/cCell.h"
// cSPSProgram
#include "Control/Cell/Programs/cSPSProgram.h"
//## begin module%3D21E86F000D.additionalDeclarations preserve=yes

// poor mans union

#define IDLE_TIME          50
#define CYCLE_TIME         10000
#define MAX_TOOL_STROKE    3000
#define BEGIN_CLOSE   500
#define END_CLOSE     3000
#define BEGIN_OPEN    7000
#define END_OPEN      8000
#define CLOSE_STEP   ((MAX_TOOL_STROKE/(END_CLOSE-BEGIN_CLOSE))*IDLE_TIME)
#define OPEN_STEP    ((MAX_TOOL_STROKE/(END_OPEN-BEGIN_OPEN))*IDLE_TIME)
static int _Elapsed = 0;
static BOOL_T _Opening = false;
static BOOL_T _Closing = false;
static long _ToolStroke = MAX_TOOL_STROKE;

static void Open(cPPCComSlave * itf)
{
   if (_Elapsed >= BEGIN_OPEN && _Elapsed <= END_OPEN) {
      _Opening = true;
   } else {
      _Opening = false;
   }
   if (_Opening) {
      _ToolStroke += OPEN_STEP;
      cRegister r(itf, "xsweg2");
      if (_ToolStroke > MAX_TOOL_STROKE) _ToolStroke = MAX_TOOL_STROKE;
      if (_ToolStroke < 0) _ToolStroke = 0;
      r = _ToolStroke;
   }
}

static void Close(cPPCComSlave * itf)
{
   if (_Elapsed >= BEGIN_CLOSE && _Elapsed <= END_CLOSE) {
      _Closing = true;
   } else {
      _Closing = false;
   }
   if (_Closing) {
      _ToolStroke -= CLOSE_STEP;
      cRegister r(itf, "xsweg2");
      if (_ToolStroke > MAX_TOOL_STROKE) _ToolStroke = MAX_TOOL_STROKE;
      if (_ToolStroke < 0) _ToolStroke = 0;
      r = _ToolStroke;
   }
}

static void EndCycle(cPPCComSlave * itf)
{
   cRegister r(itf, "xtzykl");
   long value = _Time.Elapsed();
   _Time.Now();
   r = value;
}

//## end module%3D21E86F000D.additionalDeclarations


// Class cSPSProgram 


cSPSProgram::cSPSProgram()
  //## begin cSPSProgram::cSPSProgram%.hasinit preserve=no
  //## end cSPSProgram::cSPSProgram%.hasinit
  //## begin cSPSProgram::cSPSProgram%.initialization preserve=yes
  //## end cSPSProgram::cSPSProgram%.initialization
{
  //## begin cSPSProgram::cSPSProgram%.body preserve=yes
  //## end cSPSProgram::cSPSProgram%.body
}

cSPSProgram::cSPSProgram(const cSPSProgram &right)
  //## begin cSPSProgram::cSPSProgram%copy.hasinit preserve=no
  //## end cSPSProgram::cSPSProgram%copy.hasinit
  //## begin cSPSProgram::cSPSProgram%copy.initialization preserve=yes
  //## end cSPSProgram::cSPSProgram%copy.initialization
{
  //## begin cSPSProgram::cSPSProgram%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSPSProgram::cSPSProgram%copy.body
}

cSPSProgram::cSPSProgram (cCell *cell, cConfigurationObject *config_obj)
  //## begin cSPSProgram::cSPSProgram%1025618961.hasinit preserve=no
  //## end cSPSProgram::cSPSProgram%1025618961.hasinit
  //## begin cSPSProgram::cSPSProgram%1025618961.initialization preserve=yes
  , cProgram(cell, config_obj)
  //## end cSPSProgram::cSPSProgram%1025618961.initialization
{
  //## begin cSPSProgram::cSPSProgram%1025618961.body preserve=yes
_ASSERT_COND(config_obj != NULL)
_ASSERT_COND(cell != NULL)
   _Name = config_obj->get_Name();
   _Interface = (cPPCComSlave*)_Cell->Interface();
  //## end cSPSProgram::cSPSProgram%1025618961.body
}


cSPSProgram::~cSPSProgram()
{
  //## begin cSPSProgram::~cSPSProgram%.body preserve=yes
  //## end cSPSProgram::~cSPSProgram%.body
}



//## Other Operations (implementation)
BOOL_T cSPSProgram::Start ()
{
  //## begin cSPSProgram::Start%1047387666.body preserve=yes
  //## end cSPSProgram::Start%1047387666.body
}

BOOL_T cSPSProgram::Stop ()
{
  //## begin cSPSProgram::Stop%1047387667.body preserve=yes
  //## end cSPSProgram::Stop%1047387667.body
}

void cSPSProgram::ProcessEvent (cTransientObject *object)
{
  //## begin cSPSProgram::ProcessEvent%1047387668.body preserve=yes
  //## end cSPSProgram::ProcessEvent%1047387668.body
}

// Additional Declarations
  //## begin cSPSProgram%3D21E86F000D.declarations preserve=yes
  //## end cSPSProgram%3D21E86F000D.declarations

//## begin module%3D21E86F000D.epilog preserve=yes
//## end module%3D21E86F000D.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cSPSProgram::TimerEvent%1025618967.body preserve=no
   _Elapsed += IDLE_TIME;
   if (_Elapsed > CYCLE_TIME) {
      EndCycle(_Interface);
      _Elapsed = 0;
   } else {
      _Elapsed++;
   }
   Open(_Interface);
   Close(_Interface);

   cRegister r1(_Interface, "xfzuhk");
   if ((long)r1 < 5000) {
      ++r1;
   } else {
      r1 = 0L;
   }
   cRegister r2(_Interface, "xtest");
   if ((long)r2 < 100) {
      ++r2;
   } else {
      r2 = 0L;
   }
//## end cSPSProgram::TimerEvent%1025618967.body

#endif
