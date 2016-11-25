//## begin module%3DDDF56602D1.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DDDF56602D1.cm

//## begin module%3DDDF56602D1.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DDDF56602D1.cp

//## Module: cSerialChannelFactory%3DDDF56602D1; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSerialChannelFactory.cpp

//## begin module%3DDDF56602D1.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DDDF56602D1.additionalIncludes

//## begin module%3DDDF56602D1.includes preserve=yes
//## end module%3DDDF56602D1.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
// cSerialChannelFactory
#include "Control/SerialChannel/cSerialChannelFactory.h"
//## begin module%3DDDF56602D1.additionalDeclarations preserve=yes
//## end module%3DDDF56602D1.additionalDeclarations


// Class cSerialChannelFactory 

//## begin cSerialChannelFactory::Channels%3E2C3E950293.role preserve=no  public: static cSerialChannel { -> 0..nRFHN}
std::map<STRING_T, cSerialChannel*> cSerialChannelFactory::_Channels;
//## end cSerialChannelFactory::Channels%3E2C3E950293.role

cSerialChannelFactory::cSerialChannelFactory()
  //## begin cSerialChannelFactory::cSerialChannelFactory%.hasinit preserve=no
  //## end cSerialChannelFactory::cSerialChannelFactory%.hasinit
  //## begin cSerialChannelFactory::cSerialChannelFactory%.initialization preserve=yes
  //## end cSerialChannelFactory::cSerialChannelFactory%.initialization
{
  //## begin cSerialChannelFactory::cSerialChannelFactory%.body preserve=yes
_ASSERT_UNCOND
  //## end cSerialChannelFactory::cSerialChannelFactory%.body
}

cSerialChannelFactory::cSerialChannelFactory(const cSerialChannelFactory &right)
  //## begin cSerialChannelFactory::cSerialChannelFactory%copy.hasinit preserve=no
  //## end cSerialChannelFactory::cSerialChannelFactory%copy.hasinit
  //## begin cSerialChannelFactory::cSerialChannelFactory%copy.initialization preserve=yes
  //## end cSerialChannelFactory::cSerialChannelFactory%copy.initialization
{
  //## begin cSerialChannelFactory::cSerialChannelFactory%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSerialChannelFactory::cSerialChannelFactory%copy.body
}


cSerialChannelFactory::~cSerialChannelFactory()
{
  //## begin cSerialChannelFactory::~cSerialChannelFactory%.body preserve=yes
_ASSERT_UNCOND
  //## end cSerialChannelFactory::~cSerialChannelFactory%.body
}



//## Other Operations (implementation)
cSerialChannel * cSerialChannelFactory::CreateSerialChannel (cConfigurationObject *config_obj)
{
  //## begin cSerialChannelFactory::CreateSerialChannel%1037956852.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   cSerialChannel * channel = NULL;
   BOOL_T is_bus = false;
   is_bus = config_obj->PropertyValue("IsBus", false); 
   STRING_T channel_name = config_obj->get_Name();
   if (is_bus) {
      std::map<STRING_T,cSerialChannel*>::const_iterator i = _Channels.find(channel_name.c_str());
      if (i != _Channels.end()) {
         channel = (*i).second;
         return channel;
      }
   }   
   STRING_T type_name = config_obj->PropertyValue("ChannelType", "", true);
   if (IDENTIFIER_EQUAL(type_name.c_str(), "CHANNEL_STANDARD")) {
      channel = new cStandardChannel(config_obj);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "CHANNEL_SOCKET")) {
      channel = new cSocketChannel(config_obj);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "CHANNEL_VSOCKET")) {
       channel = new cVirtualSocketChannel(config_obj);
   } else {
      channel = CreateCustomChannel(type_name.c_str(), config_obj, NULL);
      if (channel == NULL) {
         channel = CreateDLLChannel(type_name.c_str(), config_obj, NULL);
      }
   }
   if (channel != NULL && is_bus) {
      _Channels[channel_name.c_str()] = channel;
   }
   return channel;
  //## end cSerialChannelFactory::CreateSerialChannel%1037956852.body
}

cSerialChannel * cSerialChannelFactory::CreateSerialChannel (INT_T type)
{
  //## begin cSerialChannelFactory::CreateSerialChannel%1037956853.body preserve=yes
   cSerialChannel * channel = NULL;
   switch (type) {
   case CHANNEL_STANDARD:
      channel = new cStandardChannel;
      break;
   case CHANNEL_SOCKET:
      channel = new cSocketChannel;
      break;
   case CHANNEL_VSOCKET:
      channel = new cVirtualSocketChannel;
      break;
   default:
      throw cError(FACTORY_INVALID_VALUE, 0, cConvUtils::StringValue(type).c_str(), "cSerialChannel");
   }
   return channel;
  //## end cSerialChannelFactory::CreateSerialChannel%1037956853.body
}

cSerialChannel * cSerialChannelFactory::CreateCustomChannel (CONST_STRING_T object_type, cConfigurationObject *config_obj, cStaticObject *related_object)
{
  //## begin cSerialChannelFactory::CreateCustomChannel%1079341315.body preserve=yes
return NULL;
  //## end cSerialChannelFactory::CreateCustomChannel%1079341315.body
}

cSerialChannel * cSerialChannelFactory::CreateDLLChannel (CONST_STRING_T object_type, cConfigurationObject *config_obj, cStaticObject *related_object)
{
  //## begin cSerialChannelFactory::CreateDLLChannel%1079341316.body preserve=yes
return NULL;
  //## end cSerialChannelFactory::CreateDLLChannel%1079341316.body
}

// Additional Declarations
  //## begin cSerialChannelFactory%3DDDF56602D1.declarations preserve=yes
  //## end cSerialChannelFactory%3DDDF56602D1.declarations

//## begin module%3DDDF56602D1.epilog preserve=yes
//## end module%3DDDF56602D1.epilog
