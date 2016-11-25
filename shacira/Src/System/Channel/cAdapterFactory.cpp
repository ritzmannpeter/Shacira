//## begin module%3FBA3D9F03A9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBA3D9F03A9.cm

//## begin module%3FBA3D9F03A9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBA3D9F03A9.cp

//## Module: cAdapterFactory%3FBA3D9F03A9; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cAdapterFactory.cpp

//## begin module%3FBA3D9F03A9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FBA3D9F03A9.additionalIncludes

//## begin module%3FBA3D9F03A9.includes preserve=yes
//## end module%3FBA3D9F03A9.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cChannel
#include "System/Channel/cChannel.h"
// cAdapterFactory
#include "System/Channel/cAdapterFactory.h"
// cConnector
#include "System/Channel/cConnector.h"
//## begin module%3FBA3D9F03A9.additionalDeclarations preserve=yes
//## end module%3FBA3D9F03A9.additionalDeclarations


// Class cAdapterFactory 

cAdapterFactory::cAdapterFactory()
  //## begin cAdapterFactory::cAdapterFactory%.hasinit preserve=no
  //## end cAdapterFactory::cAdapterFactory%.hasinit
  //## begin cAdapterFactory::cAdapterFactory%.initialization preserve=yes
  //## end cAdapterFactory::cAdapterFactory%.initialization
{
  //## begin cAdapterFactory::cAdapterFactory%.body preserve=yes
  //## end cAdapterFactory::cAdapterFactory%.body
}

cAdapterFactory::cAdapterFactory(const cAdapterFactory &right)
  //## begin cAdapterFactory::cAdapterFactory%copy.hasinit preserve=no
  //## end cAdapterFactory::cAdapterFactory%copy.hasinit
  //## begin cAdapterFactory::cAdapterFactory%copy.initialization preserve=yes
  //## end cAdapterFactory::cAdapterFactory%copy.initialization
{
  //## begin cAdapterFactory::cAdapterFactory%copy.body preserve=yes
  //## end cAdapterFactory::cAdapterFactory%copy.body
}


cAdapterFactory::~cAdapterFactory()
{
  //## begin cAdapterFactory::~cAdapterFactory%.body preserve=yes
  //## end cAdapterFactory::~cAdapterFactory%.body
}



//## Other Operations (implementation)
cAdapter * cAdapterFactory::CreateAdapter (cConfigurationObject *config_obj, cChannel *front_end)
{
  //## begin cAdapterFactory::CreateAdapter%1069152410.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   STRING_T adapter_name = config_obj->get_Name();
   STRING_T type_name = config_obj->PropertyValue("AdapterType", "", true);
   cAdapter * adapter = NULL;
   if (IDENTIFIER_EQUAL(type_name.c_str(), "Connector")) {
      adapter = new cConnector;
   } else {
      adapter = CreateExternal(type_name.c_str(), config_obj, front_end);
   }
   return adapter;
  //## end cAdapterFactory::CreateAdapter%1069152410.body
}

cAdapter * cAdapterFactory::CreateExternal (CONST_STRING_T source, cConfigurationObject *config_obj, cStaticObject *related_object)
{
  //## begin cAdapterFactory::CreateExternal%1074701776.body preserve=yes
_ASSERT_UNCOND
   return NULL;
#ifdef lassma
   cAdapter * adapter = (cAdapter*)cObjectFactory::CreateObject(source, config_obj, related_object);
   return adapter;
#endif
  //## end cAdapterFactory::CreateExternal%1074701776.body
}

// Additional Declarations
  //## begin cAdapterFactory%3FBA3D9F03A9.declarations preserve=yes
  //## end cAdapterFactory%3FBA3D9F03A9.declarations

//## begin module%3FBA3D9F03A9.epilog preserve=yes
//## end module%3FBA3D9F03A9.epilog
