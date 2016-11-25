//## begin module%429C6DCA00EA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%429C6DCA00EA.cm

//## begin module%429C6DCA00EA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%429C6DCA00EA.cp

//## Module: cGateway%429C6DCA00EA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cGateway.cpp

//## begin module%429C6DCA00EA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%429C6DCA00EA.additionalIncludes

//## begin module%429C6DCA00EA.includes preserve=yes
//## end module%429C6DCA00EA.includes

// cContext
#include "System/Database/cContext.h"
// cGatewayServer
#include "Control/Cell/cGatewayServer.h"
// cGateway
#include "Control/Cell/cGateway.h"
//## begin module%429C6DCA00EA.additionalDeclarations preserve=yes
//## end module%429C6DCA00EA.additionalDeclarations


// Class cGateway 


cGateway::cGateway()
  //## begin cGateway::cGateway%.hasinit preserve=no
      : _Server(NULL)
  //## end cGateway::cGateway%.hasinit
  //## begin cGateway::cGateway%.initialization preserve=yes
  //## end cGateway::cGateway%.initialization
{
  //## begin cGateway::cGateway%.body preserve=yes
_ASSERT_UNCOND
  //## end cGateway::cGateway%.body
}

cGateway::cGateway(const cGateway &right)
  //## begin cGateway::cGateway%copy.hasinit preserve=no
      : _Server(NULL)
  //## end cGateway::cGateway%copy.hasinit
  //## begin cGateway::cGateway%copy.initialization preserve=yes
  //## end cGateway::cGateway%copy.initialization
{
  //## begin cGateway::cGateway%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cGateway::cGateway%copy.body
}

cGateway::cGateway (cConfigurationObject *config_obj, cContext *context)
  //## begin cGateway::cGateway%1117545273.hasinit preserve=no
      : _Server(NULL)
  //## end cGateway::cGateway%1117545273.hasinit
  //## begin cGateway::cGateway%1117545273.initialization preserve=yes
  , cProgram(config_obj, context)
  //## end cGateway::cGateway%1117545273.initialization
{
  //## begin cGateway::cGateway%1117545273.body preserve=yes
   cSHProcess * process = NULL;
   if (context != NULL) {
      process = context->Process();
   }
   _Server = new cGatewayServer(this, 20000, process);
  //## end cGateway::cGateway%1117545273.body
}


cGateway::~cGateway()
{
  //## begin cGateway::~cGateway%.body preserve=yes
   DELETE_OBJECT(cGatewayServer, _Server)
  //## end cGateway::~cGateway%.body
}



//## Other Operations (implementation)
void cGateway::Start ()
{
  //## begin cGateway::Start%1117548692.body preserve=yes
   _Server->start();
   cProgram::Start();
  //## end cGateway::Start%1117548692.body
}

void cGateway::Stop ()
{
  //## begin cGateway::Stop%1117548693.body preserve=yes
   cProgram::Stop();
  //## end cGateway::Stop%1117548693.body
}

void cGateway::ProcessEvent (cTransientObject *object)
{
  //## begin cGateway::ProcessEvent%1117548689.body preserve=yes
  //## end cGateway::ProcessEvent%1117548689.body
}

void cGateway::Cycle ()
{
  //## begin cGateway::Cycle%1117548690.body preserve=yes
  //## end cGateway::Cycle%1117548690.body
}

void cGateway::Initialize ()
{
  //## begin cGateway::Initialize%1117548691.body preserve=yes
  //## end cGateway::Initialize%1117548691.body
}

void cGateway::GetPage (CONST_STRING_T page, STRING_T &page_text)
{
  //## begin cGateway::GetPage%1127152536.body preserve=yes
#define test_only
#ifdef test_only
   char buffer[0x200] = {0};
   FILE * stream = fopen("overview.html", "r");
   if (stream != NULL) {
      memset(buffer, 0, sizeof(buffer));
      int nread = fread(buffer, sizeof(buffer) - 1, 1, stream);
      while (nread > 0) {
         page_text += buffer;
         nread = fread(buffer, sizeof(buffer) - 1, 1, stream);
      }
      fclose(stream);
   } else {
      page_text = "page ";
      page_text += page;
      page_text += " not found";
   }
#else
   page_text = "page ";
   page_text += page;
   page_text += " not available";
#endif
  //## end cGateway::GetPage%1127152536.body
}

void cGateway::Request (CONST_STRING_T request, STRING_T &response)
{
  //## begin cGateway::Request%1135674615.body preserve=yes
  //## end cGateway::Request%1135674615.body
}

// Additional Declarations
  //## begin cGateway%429C6DCA00EA.declarations preserve=yes
  //## end cGateway%429C6DCA00EA.declarations

//## begin module%429C6DCA00EA.epilog preserve=yes
//## end module%429C6DCA00EA.epilog
