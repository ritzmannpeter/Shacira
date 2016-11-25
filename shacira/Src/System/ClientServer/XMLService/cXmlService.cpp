//## begin module%4CA9FA0D01C5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4CA9FA0D01C5.cm

//## begin module%4CA9FA0D01C5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4CA9FA0D01C5.cp

//## Module: cXmlService%4CA9FA0D01C5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\XMLService\cXmlService.cpp

//## begin module%4CA9FA0D01C5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4CA9FA0D01C5.additionalIncludes

//## begin module%4CA9FA0D01C5.includes preserve=yes
//## end module%4CA9FA0D01C5.includes

// cContext
#include "System/Database/cContext.h"
// cXmlService
#include "System/ClientServer/XMLService/cXmlService.h"
//## begin module%4CA9FA0D01C5.additionalDeclarations preserve=yes

#include "System/Database/cVarRef.h"
#include "System/Database/cVariable.h"

#include "driverfactory.h"
#include "bytebuffer.h"
#include "service.h"
#include "xmlstruct.h"
#include "binaryframehandler.h"

class cEmbeddedXMLService : public cService
{
public:
   cEmbeddedXMLService(cDriver * driver, cSession * session, cContext * context)
      : cService(driver, session), _Context(context)
   {
   };
   cEmbeddedXMLService(cDriver * driver, cClient * client, cContext * context)
      : cService(driver, client), _Context(context)
   {
   };
   virtual ~cEmbeddedXMLService()
   {
   };
   virtual void handleFrame(const cByteBuffer & buffer)
   {
      buffer.show("<-");
      cByteBuffer response;
      int rc = createResponse(buffer, response);
      if (rc == 0) {
         rc = send(response.data(), response.size());
      } else {
		 char scode[0x50] = {0};
		 SafePrintf(scode, sizeof(scode), "%d", rc);
         string resp = "<W2F>\n";
         resp += "  <Reply>\n";
         resp += "    <Sender>\n";
         resp += "      <Address Ident=\"bridge\"></Address>\n";
         resp += "    </Sender>\n";
         resp += "    <Destination>\n";
         resp += "      <Address Ident=\"client\"></Address>\n";
         resp += "    </Destination>\n";
         resp += "    <Response State=\"error\" ErrorCode=\"";
         resp += scode;
		 resp += "\" ErrorText=\"server error\"></Response>\n";
         resp += "    <Response State=\"error\" ErrorCode=\"2500\" ErrorText=\"not connected\"></Response>\n";
         resp += "  </Reply>\n";
         resp += "</W2F>";
         rc = send((OCTET_T*)resp.c_str(), (LENGTH_T)resp.size());
	  }
   };
   virtual int request(const cByteBuffer & request, cByteBuffer & reply)
   {
      return 0;
   };
private:
   virtual int createResponse(const cByteBuffer & request, cByteBuffer & response)
   {
      cXMLStruct * xmlRequest = cXMLStruct::construct(request.data(), request.size());
      if (xmlRequest != NULL) {
	     if (xmlRequest->dataRequest() != NULL) {
            DataRequest * dataRequest = xmlRequest->dataRequest();
            DataReply * dataReply = new DataReply(new Address(dataRequest->destination()->ident(), dataRequest->destination()->ipAddress()),
                                                  new Address(dataRequest->sender()->ident(), dataRequest->sender()->ipAddress()),
                                                  new Response(Response::Success, 0, "no error"));
            VariableSpecificationList & specs = dataRequest->variableSpecificationList();
            VariableSpecificationList::const_iterator i = specs.begin();
            while (i != specs.end()) {
               VariableSpecification * spec = (*i);
               VariableSpecification::SpecificationType spec_type = spec->type();
               try {
                  if (spec_type == VariableSpecification::Reference) {
                     VariableReference * variableReference = static_cast<VariableReference*>(spec);
                     STRING_T reference = variableReference->reference();
                     if (!reference.empty()) {
                        cVarRef * var_ref = _Context->VarRef(reference.c_str());
                        if (var_ref != NULL) {
                           STRING_T value;
                           try {
                              var_ref->GetValue(value);
                              Data * data = new Data(new VariableReference(reference), new Value(value));
                              dataReply->add(data);
                           } catch (cError & e) {
                              ErrorPrintf("xml service get varref %s: %s\n", reference.c_str(), (const char *)e);
                           } catch (...) {
                              ErrorPrintf("xml service get varref %s: unhandled exception\n", reference.c_str());
                           }
                           int dummy = 0;
                        }
                     }
                     int dummy = 0;
                  } else if (spec_type == VariableSpecification::QualifiedSpecification) {
                     QualifiedVariableSpecification * qualifiedVariableSpecification = static_cast<QualifiedVariableSpecification*>(spec);
                     STRING_T variable_name = qualifiedVariableSpecification->variableName();
                     int i1 = qualifiedVariableSpecification->index1();
                     int i2 = qualifiedVariableSpecification->index2();
                     int i3 = qualifiedVariableSpecification->index3();
                     int i4 = qualifiedVariableSpecification->index4();
                     cVariable * variable = _Context->Variable(variable_name.c_str());
                     if (variable != NULL) {
                        STRING_T value;
                        try {
                           variable->Get(value, i1, i2, i3, i4);
                           Data * data = new Data(new QualifiedVariableSpecification(variable_name, i1, i2, i3, i4), new Value(value));
                           dataReply->add(data);
                        } catch (cError & e) {
                           ErrorPrintf("xml service get variable %s[%d][%d][%d][%d]: %s\n", variable_name.c_str(), i1, i2, i3, i4, (const char *)e);
                        } catch (...) {
                           ErrorPrintf("xml service get variable %s[%d][%d][%d][%d]: unhandled exception\n", variable_name.c_str(), i1, i2, i3, i4);
                        }
                        int dummy = 0;
                     }
                     int dummy = 0;
                  }
               } catch (cError & e) {
                  ErrorPrintf("xml service error: %s\n", (const char *)e);
               } catch (...) {
                  ErrorPrintf("xml service unhandled exception\n");
               }
               i++;
            }
            cXMLStruct * reply = new cXMLStruct(dataReply);
			reply->serialize(response);
			delete reply;
			return 0;
         } else if (xmlRequest->setDataRequest() != NULL) {
            SetDataRequest * setDataRequest = xmlRequest->setDataRequest();
            DataList & dataList = setDataRequest->dataList();
            DataList::const_iterator i = dataList.begin();
            while (i != dataList.end()) {
               Data * data = (*i);
               string specification = data->specification();
               string valueText = data->valueText();
               VariableReference * variableReference = data->variableReference();
               QualifiedVariableSpecification * qualifiedVariableSpecification = data->qualifiedVariableSpecification();
               Value * value = data->value();
               if (variableReference != NULL) {
                  STRING_T reference = variableReference->reference();
                  if (!reference.empty()) {
                     cVarRef * var_ref = _Context->VarRef(reference.c_str());
                     if (var_ref != NULL) {
                        STRING_T value;
                        try {
                           var_ref->SetValue(valueText.c_str());
                        } catch (cError & e) {
                           ErrorPrintf("xml service get varref %s: %s\n", reference.c_str(), (const char *)e);
                        } catch (...) {
                           ErrorPrintf("xml service get varref %s: unhandled exception\n", reference.c_str());
                        }
                     }
                  }
               } else if (qualifiedVariableSpecification != NULL) {
                  STRING_T variable_name = qualifiedVariableSpecification->variableName();
                  int i1 = qualifiedVariableSpecification->index1();
                  int i2 = qualifiedVariableSpecification->index2();
                  int i3 = qualifiedVariableSpecification->index3();
                  int i4 = qualifiedVariableSpecification->index4();
                  cVariable * variable = _Context->Variable(variable_name.c_str());
                  if (variable != NULL) {
                     try {
                        variable->Set(valueText.c_str(), i1, i2, i3, i4);
                     } catch (cError & e) {
                        ErrorPrintf("xml service get variable %s[%d][%d][%d][%d]: %s\n", variable_name.c_str(), i1, i2, i3, i4, (const char *)e);
                     } catch (...) {
                        ErrorPrintf("xml service get variable %s[%d][%d][%d][%d]: unhandled exception\n", variable_name.c_str(), i1, i2, i3, i4);
                     }
                     int dummy = 0;
                  }
               }
               i++;
            }
            SetDataReply * setDataReply = new SetDataReply(new Address(setDataRequest->destination()->ident(), setDataRequest->destination()->ipAddress()),
                                                           new Address(setDataRequest->sender()->ident(), setDataRequest->sender()->ipAddress()),
                                                           new Response(Response::Error, -22, "not yet supported"));
            cXMLStruct * reply = new cXMLStruct(setDataReply);
			reply->serialize(response);
			return 0;
         } else if (xmlRequest->eventRequest() != NULL) {
            EventRequest * eventRequest = xmlRequest->eventRequest();
            EventReply * eventReply = new EventReply(new Address(eventRequest->destination()->ident(), eventRequest->destination()->ipAddress()),
                                                     new Address(eventRequest->sender()->ident(), eventRequest->sender()->ipAddress()),
                                                     new Response(Response::Error, -22, "not yet supported"));
            cXMLStruct * reply = new cXMLStruct(eventReply);
			reply->serialize(response);
			return 0;
         } else {
            return -2;
		 }
      };
      return -1;
  };
private:
   cContext * _Context;
};

class cEmbeddedServiceFactory : public cServiceFactory
{
public:
   cEmbeddedServiceFactory(cContext * context) : _Context(context) {};
   virtual ~cEmbeddedServiceFactory() {};
   virtual cService * createService(cDriver * driver, cSession * session)
   {
      return new cEmbeddedXMLService(driver, session, _Context);
   };
   virtual cService * createService(cDriver * driver, cClient * client)
   {
      return new cEmbeddedXMLService(driver, client, _Context);
   };
   virtual cFrameHandler * createFrameHandler()
   {
      return new cBinaryFrameHandler;
   };
protected:
   cContext * _Context;
};

//## end module%4CA9FA0D01C5.additionalDeclarations


// Class cXmlService 



cXmlService::cXmlService()
  //## begin cXmlService::cXmlService%.hasinit preserve=no
      : _Port(11333), _Context(NULL)
  //## end cXmlService::cXmlService%.hasinit
  //## begin cXmlService::cXmlService%.initialization preserve=yes
  //## end cXmlService::cXmlService%.initialization
{
  //## begin cXmlService::cXmlService%.body preserve=yes
  //## end cXmlService::cXmlService%.body
}

cXmlService::cXmlService(const cXmlService &right)
  //## begin cXmlService::cXmlService%copy.hasinit preserve=no
      : _Port(11333), _Context(NULL)
  //## end cXmlService::cXmlService%copy.hasinit
  //## begin cXmlService::cXmlService%copy.initialization preserve=yes
  //## end cXmlService::cXmlService%copy.initialization
{
  //## begin cXmlService::cXmlService%copy.body preserve=yes
  //## end cXmlService::cXmlService%copy.body
}

cXmlService::cXmlService (cContext *context, USHORT_T listener_port)
  //## begin cXmlService::cXmlService%1286209113.hasinit preserve=no
      : _Port(11333), _Context(NULL)
  //## end cXmlService::cXmlService%1286209113.hasinit
  //## begin cXmlService::cXmlService%1286209113.initialization preserve=yes
  //## end cXmlService::cXmlService%1286209113.initialization
{
  //## begin cXmlService::cXmlService%1286209113.body preserve=yes
   _Context = context;
   _Port = listener_port;
  //## end cXmlService::cXmlService%1286209113.body
}


cXmlService::~cXmlService()
{
  //## begin cXmlService::~cXmlService%.body preserve=yes
  //## end cXmlService::~cXmlService%.body
}



//## Other Operations (implementation)
INT_T cXmlService::onMain (void *extra)
{
  //## begin cXmlService::onMain%1286209114.body preserve=yes
   cByteBuffer::setVerbose(false);
   cServiceFactory * serviceFactory = new cEmbeddedServiceFactory(_Context);
   cDriver * driver = cDriverFactory::create(cDriver::SOCKETIO, _Port, serviceFactory);
   if (driver != NULL) {
      return driver->run();
   } else {
      return -1;
   }
   return 0;
  //## end cXmlService::onMain%1286209114.body
}

//## Get and Set Operations for Class Attributes (implementation)

short cXmlService::get_Port () const
{
  //## begin cXmlService::get_Port%4CAA03C7003E.get preserve=no
  return _Port;
  //## end cXmlService::get_Port%4CAA03C7003E.get
}

void cXmlService::set_Port (short value)
{
  //## begin cXmlService::set_Port%4CAA03C7003E.set preserve=no
  _Port = value;
  //## end cXmlService::set_Port%4CAA03C7003E.set
}

// Additional Declarations
  //## begin cXmlService%4CA9FA0D01C5.declarations preserve=yes
  //## end cXmlService%4CA9FA0D01C5.declarations

//## begin module%4CA9FA0D01C5.epilog preserve=yes
//## end module%4CA9FA0D01C5.epilog
