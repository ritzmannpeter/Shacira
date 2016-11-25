//## begin module%3F85177902CE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F85177902CE.cm

//## begin module%3F85177902CE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F85177902CE.cp

//## Module: cConnector%3F85177902CE; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cConnector.cpp

//## begin module%3F85177902CE.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F85177902CE.additionalIncludes

//## begin module%3F85177902CE.includes preserve=yes
//## end module%3F85177902CE.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cConnector
#include "System/Channel/cConnector.h"
//## begin module%3F85177902CE.additionalDeclarations preserve=yes
//## end module%3F85177902CE.additionalDeclarations


// Class cConnector 


cConnector::cConnector()
  //## begin cConnector::cConnector%.hasinit preserve=no
  //## end cConnector::cConnector%.hasinit
  //## begin cConnector::cConnector%.initialization preserve=yes
  //## end cConnector::cConnector%.initialization
{
  //## begin cConnector::cConnector%.body preserve=yes
   char adapter_name[128] = {0};
   SafePrintf(adapter_name, sizeof(adapter_name), "connector:%p", this);
   _Name = adapter_name;
  //## end cConnector::cConnector%.body
}

cConnector::cConnector(const cConnector &right)
  //## begin cConnector::cConnector%copy.hasinit preserve=no
  //## end cConnector::cConnector%copy.hasinit
  //## begin cConnector::cConnector%copy.initialization preserve=yes
  //## end cConnector::cConnector%copy.initialization
{
  //## begin cConnector::cConnector%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cConnector::cConnector%copy.body
}


cConnector::~cConnector()
{
  //## begin cConnector::~cConnector%.body preserve=yes
  //## end cConnector::~cConnector%.body
}



//## Other Operations (implementation)
BOOL_T cConnector::ObjectGetParam (CONST_STRING_T name, STRING_T &value)
{
  //## begin cConnector::ObjectGetParam%1075904921.body preserve=yes
   return false;
  //## end cConnector::ObjectGetParam%1075904921.body
}

BOOL_T cConnector::ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value)
{
  //## begin cConnector::ObjectSetParam%1075904922.body preserve=yes
   return false;
  //## end cConnector::ObjectSetParam%1075904922.body
}

void cConnector::Connect (cChannel *channel)
{
  //## begin cConnector::Connect%1073642253.body preserve=yes
   _Channels.Add(channel);
   InfoPrintf("%s -> %s\n",
              get_Name().c_str(),
              channel->get_Name().c_str());
  //## end cConnector::Connect%1073642253.body
}

void cConnector::Disconnect (cChannel *channel)
{
  //## begin cConnector::Disconnect%1073642254.body preserve=yes
   _Channels.Remove(channel);
  //## end cConnector::Disconnect%1073642254.body
}

void cConnector::Object (cTransientObject *object)
{
  //## begin cConnector::Object%1065687231.body preserve=yes
   Emit(object);
  //## end cConnector::Object%1065687231.body
}

void cConnector::Emit (cTransientObject *object)
{
  //## begin cConnector::Emit%1073642242.body preserve=yes
   cPtrList::cConstIterator i = _Channels.Begin();
   if (i.First()) {
      do {
         cChannel * channel = (cChannel*)i.Ptr();
         if (channel != NULL) {
            channel->Send(object);
         }
      } while (i.Next());
   }
  //## end cConnector::Emit%1073642242.body
}

// Additional Declarations
  //## begin cConnector%3F85177902CE.declarations preserve=yes
  //## end cConnector%3F85177902CE.declarations

//## begin module%3F85177902CE.epilog preserve=yes
//## end module%3F85177902CE.epilog
