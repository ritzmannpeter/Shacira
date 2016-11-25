
#include "FirstHeader.h"
#include "cXMLService.h"
#include "cProcessWrapper.h"
#include "XML/XMLUtils.h"
#include "cAlloc.h"

cXMLService::cXMLService()
{
   XMLPlatformUtils::Initialize();
}


cXMLService::~cXMLService()
{
}

int cXMLService::Request(const unsigned char * request, int request_len, unsigned char * & response, int & response_len)
{
   if (strncmp((const char *)request, "memory", 6) == 0) {
      if (PWrapper()->GetImage((const char *)request, response, response_len)) {
         return response_len;
      }
   }
   if (strncmp((const char *)request, "image:", 6) == 0) {
      if (PWrapper()->GetImage((const char *)&request[6], response, response_len)) {
         return response_len;
      }
   }
   STRING_T value = "syntax error";
   if (PWrapper()->Eval((const char*)request, value)) {
   } else {
   }
   STRING_T xml = WrapXML(value.c_str());
   response_len = xml.size();
   response = (unsigned char*)cAlloc::Alloc(response_len + 1);
   memcpy(response, xml.c_str(), response_len);
   return response_len;
}

STRING_T cXMLService::WrapXML(const char * data)
{
   DOMDocument * doc = XMLUtils::CreateDocument("Response");
   DOMNode * command_node = XMLUtils::AddNode(doc, "Command");
   DOMNode * data_node = XMLUtils::AddNode(doc, command_node, "Data");
   if (XMLUtils::SetNodeCData(doc, data_node, data)) {
      STRING_T xml_data = XMLUtils::GetDocumentText(doc).c_str();
      delete doc;
      return xml_data;
   } else {
      delete doc;
      return data;
   }
}
