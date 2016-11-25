
#include "xmlstruct.h"
#include "XML/xmlutils.h"
#include "XML/xmlhandler.h"
#include "log.h"

void XMLComponent::increment()
{
   cXMLStruct::_componentCount++;
}

void XMLComponent::decrement()
{
   cXMLStruct::_componentCount--;
}

int XMLComponent::componentCount()
{
   return cXMLStruct::_componentCount;
}

int XMLComponent::structCount()
{
   return cXMLStruct::_count;
}

int cXMLStruct::_count = 0;
int cXMLStruct::_componentCount = 0;

cXMLStruct::cXMLStruct()
   : _dataRequest(NULL),
     _setDataRequest(NULL),
     _eventRequest(NULL),
     _dataReply(NULL),
     _setDataReply(NULL),
     _eventReply(NULL)
{
   _count++;
}

cXMLStruct::cXMLStruct(const string & text)
   : _dataRequest(NULL),
     _setDataRequest(NULL),
     _eventRequest(NULL),
     _dataReply(NULL),
     _setDataReply(NULL),
     _eventReply(NULL),
     _text(text)
{
   _count++;
}

cXMLStruct::cXMLStruct(DataRequest * request)
   : _dataRequest(request),
     _setDataRequest(NULL),
     _eventRequest(NULL),
     _dataReply(NULL),
     _setDataReply(NULL),
     _eventReply(NULL)
{
   _count++;
}

cXMLStruct::cXMLStruct(SetDataRequest * request)
   : _dataRequest(NULL),
     _setDataRequest(request),
     _eventRequest(NULL),
     _dataReply(NULL),
     _setDataReply(NULL),
     _eventReply(NULL)
{
   _count++;
}

cXMLStruct::cXMLStruct(EventRequest * request)
   : _dataRequest(NULL),
     _setDataRequest(NULL),
     _eventRequest(request),
     _dataReply(NULL),
     _setDataReply(NULL),
     _eventReply(NULL)
{
   _count++;
}

cXMLStruct::cXMLStruct(DataReply * reply)
   : _dataRequest(NULL),
     _setDataRequest(NULL),
     _eventRequest(NULL),
     _dataReply(reply),
     _setDataReply(NULL),
     _eventReply(NULL)
{
   _count++;
}

cXMLStruct::cXMLStruct(SetDataReply * reply)
   : _dataRequest(NULL),
     _setDataRequest(NULL),
     _eventRequest(NULL),
     _dataReply(NULL),
     _setDataReply(reply),
     _eventReply(NULL)
{
   _count++;
}

cXMLStruct::cXMLStruct(EventReply * reply)
   : _dataRequest(NULL),
     _setDataRequest(NULL),
     _eventRequest(NULL),
     _dataReply(NULL),
     _setDataReply(NULL),
     _eventReply(reply)
{
   _count++;
}

cXMLStruct::~cXMLStruct()
{
   if (_dataRequest != NULL) {
      delete _dataRequest;
   }
   if (_setDataRequest != NULL) {
      delete _setDataRequest;
   }
   if (_eventRequest != NULL) {
      delete _eventRequest;
   }
   if (_dataReply != NULL) {
      delete _dataReply;
   }
   if (_setDataReply != NULL) {
      delete _setDataReply;
   }
   if (_eventReply != NULL) {
      delete _eventReply;
   }
   _count--;
}

cXMLStruct * cXMLStruct::construct(const OCTET_T * data, LENGTH_T dataLength)
{
#undef BUFFER_TEST
#ifdef BUFFER_TEST
   cXMLStruct * object = new cXMLStruct((const char*)data + 4);
   object->setRequestId(data);
   return object;
#else
#ifdef lassma
   cXMLStruct * object = constructFromDocument((const char*)data + 4);
   if (object != NULL) {
      object->setRequestId(data);
cByteBuffer b;
object->serialize(b);
object->_text = (const char*)b.data()+4;
   }
#endif
   cXMLStruct * object = constructFromDocument((const char*)data);
   return object;
#endif
}

int cXMLStruct::serialize(cByteBuffer & buffer)
{
#ifdef lassma
   unsigned char rid[4] = {0};
   toRid(rid, _requestId);
   cByteBuffer newBuffer(rid, 4);
#else
   cByteBuffer newBuffer;
#endif
#ifdef BUFFER_TEST
   newBuffer.append((OCTET_T *)_text.c_str(), _text.size());
   buffer = newBuffer;
   return 0;
#else
   string data;
   if (createDocument(data)) {
      newBuffer.append((const unsigned char*)data.c_str(), data.size());
   }
   buffer = newBuffer;
_text = data.c_str();
   return 0;
#endif
}

DOMElement * addressElement(DOMDocument * document, Address * address)
{
   DOMElement * element = document->createElement(X("Address"));
   element->setAttribute(X("Ident"), X(address->ident().c_str()));
   element->setAttribute(X("IpAddress"), X(address->ipAddress().c_str()));
int sc = address->structCount();
int cc = address->componentCount();
   return element;
}

DOMElement * variableReferenceElement(DOMDocument * document, VariableReference * variableReference)
{
   DOMElement * element = document->createElement(X("VariableReference"));
   element->setAttribute(X("Reference"), X(variableReference->reference().c_str()));
   return element;
}

DOMElement * qualifiedVariableSpecificationElement(DOMDocument * document, QualifiedVariableSpecification * qualifiedVariableSpecification)
{
   DOMElement * element = document->createElement(X("QualifiedVariableSpecification"));
   element->setAttribute(X("VariableName"), X(qualifiedVariableSpecification->variableName().c_str()));
   element->setAttribute(X("Index1"), X(itos(qualifiedVariableSpecification->index1()).c_str()));
   element->setAttribute(X("Index2"), X(itos(qualifiedVariableSpecification->index2()).c_str()));
   element->setAttribute(X("Index3"), X(itos(qualifiedVariableSpecification->index3()).c_str()));
   element->setAttribute(X("Index4"), X(itos(qualifiedVariableSpecification->index4()).c_str()));
   return element;
}

DOMElement * dataRequestElement(DOMDocument * document, DataRequest * dataRequest)
{
   DOMElement * dataRequestElement = document->createElement(X("DataRequest"));
   VariableSpecificationList::const_iterator i = dataRequest->variableSpecificationList().begin();
   while (i != dataRequest->variableSpecificationList().end()) {
      VariableSpecification * spec = (*i);
      VariableSpecification::SpecificationType specificationType = spec->type();
      if (specificationType == VariableReference::Reference) {
         VariableReference * reference = static_cast<VariableReference*>(spec);
         DOMElement * element = variableReferenceElement(document, reference);
         dataRequestElement->appendChild(element);
      } else if (specificationType == VariableReference::QualifiedSpecification) {
         QualifiedVariableSpecification * specification = static_cast<QualifiedVariableSpecification*>(spec);
         DOMElement * element = qualifiedVariableSpecificationElement(document, specification);
         dataRequestElement->appendChild(element);
      }
      i++;
   }
   return dataRequestElement;
}

DOMElement * valueElement(DOMDocument * document, Value * value)
{
   DOMElement * valueElement = document->createElement(X("Value"));
   string data = value->value();
   XMLUtils::setData(document, valueElement, data);
   return valueElement;
}

DOMElement * dataElement(DOMDocument * document, Data * data)
{
   DOMElement * dataElement = document->createElement(X("Data"));
   DOMElement * element = NULL;
   if (data->qualifiedVariableSpecification() != NULL) {
      element = qualifiedVariableSpecificationElement(document, data->qualifiedVariableSpecification());
   }
   if (data->variableReference() != NULL) {
      element = variableReferenceElement(document, data->variableReference());
   }
   if (element != NULL) {
      dataElement->appendChild(element);
   }
   if (data->value() != NULL) {
      element = valueElement(document, data->value());
      dataElement->appendChild(element);
   }
   return dataElement;
}

DOMElement * setDataRequestElement(DOMDocument * document, SetDataRequest * setDataRequest)
{
   DOMElement * setDataRequestElement = document->createElement(X("SetDataRequest"));
   DataList::const_iterator i = setDataRequest->dataList().begin();
   while (i != setDataRequest->dataList().end()) {
      Data * data = (*i);
      DOMElement * element = dataElement(document, data);
      setDataRequestElement->appendChild(element);
      i++;
   }
   return setDataRequestElement;
}

DOMElement * eventRequestElement(DOMDocument * document, EventRequest * eventRequest)
{
   DOMElement * eventRequestElement = document->createElement(X("EventRequest"));
   return eventRequestElement;
}

DOMElement * responseElement(DOMDocument * document, Response * response)
{
   DOMElement * element = document->createElement(X("Response"));
   element->setAttribute(X("State"), X(response->stateText().c_str()));
   element->setAttribute(X("ErrorCode"), X(itos(response->errorCode()).c_str()));
   element->setAttribute(X("ErrorText"), X(response->errorText().c_str()));
   return element;
}

DOMElement * dataReplyElement(DOMDocument * document, DataReply * dataReply)
{
   DOMElement * dataReplyElement = document->createElement(X("DataReply"));
   DataList::const_iterator i = dataReply->dataList().begin();
   while (i != dataReply->dataList().end()) {
      Data * data = (*i);
      DOMElement * element = dataElement(document, data);
      dataReplyElement->appendChild(element);
      i++;
   }
   return dataReplyElement;
}

DOMElement * setDataReplyElement(DOMDocument * document, SetDataReply * setDataReply)
{
   DOMElement * dataReplyElement = document->createElement(X("SetDataReply"));
   return dataReplyElement;
}

DOMElement * eventReplyElement(DOMDocument * document, EventReply * eventReply)
{
   DOMElement * dataReplyElement = document->createElement(X("EventReply"));
   return dataReplyElement;
}

// invert !!

Address * addressComponent(DOMDocument * document, DOMElement * element)
{
   DOMNodeList * nodeList = element->getElementsByTagName(X("Address"));
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            string ident = S(child->getAttribute(X("Ident")));
            string ipAddress = S(child->getAttribute(X("IpAddress")));
            return new Address(ident, ipAddress);
         }
      }
   }
   return NULL;
}

Address * senderComponent(DOMDocument * document, DOMElement * element)
{
   DOMNodeList * nodeList = element->getElementsByTagName(X("Sender"));
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            return addressComponent(document, child);
         }
      }
   }
   return NULL;
}

Address * destinationComponent(DOMDocument * document, DOMElement * element)
{
   DOMNodeList * nodeList = element->getElementsByTagName(X("Destination"));
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            return addressComponent(document, child);
         }
      }
   }
   return NULL;
}

VariableReference * variableReferenceComponent(DOMDocument * document, DOMElement * element)
{
   string reference = S(element->getAttribute(X("Reference")));
   return new VariableReference(reference);
}

QualifiedVariableSpecification * qualifiedVariableSpecificationComponent(DOMDocument * document, DOMElement *  element)
{
   string variableName = S(element->getAttribute(X("VariableName")));
   int index1 = atoi(S(element->getAttribute(X("Index1"))).c_str());
   int index2 = atoi(S(element->getAttribute(X("Index2"))).c_str());
   int index3 = atoi(S(element->getAttribute(X("Index3"))).c_str());
   int index4 = atoi(S(element->getAttribute(X("Index4"))).c_str());
   return new QualifiedVariableSpecification(variableName, index1, index2, index3, index4);
}

DataRequest * dataRequestComponent(DOMDocument * document, DOMElement * element, Address * sender, Address * destination, TimeStamp * timeStamp)
{
   DataRequest * dataRequest = new DataRequest(sender, destination, timeStamp);
   DOMNodeList * nodeList = element->getChildNodes();
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            string tagName = S(child->getTagName());
            if (tagName == "VariableReference") {
               VariableReference * r = variableReferenceComponent(document, child);
               dataRequest->add(r);
            } else if (tagName == "QualifiedVariableSpecification") {
               QualifiedVariableSpecification * s = qualifiedVariableSpecificationComponent(document, child);
               dataRequest->add(s);
            }
         }
      }
   }
   return dataRequest;   
}

Value * valueComponent(DOMDocument * document, DOMElement * element)
{
   string data = XMLUtils::getData(document, element);
   return new Value(data);
}

Data * dataComponent(DOMDocument * document, DOMElement * element)
{
   VariableReference * variableReference = NULL;
   QualifiedVariableSpecification * qualifiedVariableSpecification = NULL;
   Value * value = NULL;
   DOMNodeList * nodeList = element->getChildNodes();
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            string tagName = S(child->getTagName());
            if (tagName == "VariableReference") {
               variableReference = variableReferenceComponent(document, child);
            } else if (tagName == "QualifiedVariableSpecification") {
               qualifiedVariableSpecification = qualifiedVariableSpecificationComponent(document, child);
            } else if (tagName == "Value") {
               value = valueComponent(document, child);
            }
         }
      }
   }
   if (variableReference != NULL) {
      return new Data(variableReference, value);
   }
   if (qualifiedVariableSpecification != NULL) {
      return new Data(qualifiedVariableSpecification, value);
   }
   return NULL;
}

SetDataRequest * setDataRequestComponent(DOMDocument * document, DOMElement * element, Address * sender, Address * destination)
{
   SetDataRequest * setDataRequest = new SetDataRequest(sender, destination);
   DOMNodeList * nodeList = element->getChildNodes();
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            string tagName = S(child->getTagName());
            if (tagName == "Data") {
               Data * data = dataComponent(document, child);
               setDataRequest->add(data);
            }
         }
      }
   }
   return setDataRequest;
}

Response * responseComponent(DOMDocument * document, DOMElement * element)
{
   DOMNodeList * nodeList = element->getElementsByTagName(X("Response"));
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            Response::ResponseState responseState = Response::responseStateFromText(S(child->getAttribute(X("State"))));
#if (_MSC_VER >= 1300)
            int errorCode = std::atoi(S(child->getAttribute(X("ErrorText"))).c_str());
#else
            int errorCode = atoi(S(child->getAttribute(X("ErrorText"))).c_str());
#endif
            string errorText = S(child->getAttribute(X("ErrorText")));
            return new Response(responseState, errorCode, errorText);
         }
      }
   }
   return NULL;
}

TimeStamp * timeStampComponent(DOMDocument * document, DOMElement * element)
{
   DOMNodeList * nodeList = element->getElementsByTagName(X("TimeStamp"));
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            string data = XMLUtils::getData(document, child);
            return new TimeStamp(data);
         }
      }
   }
   return NULL;
}

DataReply * dataReplyComponent(DOMDocument * document, DOMElement * element, Address * sender, Address * destination, Response * response)
{
   DataReply * dataReply = new DataReply(sender, destination, response);
   DOMNodeList * nodeList = element->getChildNodes();
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            string tagName = S(child->getTagName());
            if (tagName == "Data") {
               Data * data = dataComponent(document, child);
               dataReply->add(data);
            }
         }
      }
   }
   return dataReply;
}

DOMElement * requestElement(DOMDocument * document)
{
   DOMElement * element = document->getDocumentElement();
   DOMNodeList * nodeList = element->getChildNodes();
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            string tagName = S(child->getTagName());
            if (tagName == "Request") {
               return child;
            }
         }
      }
   }
   return NULL;
}

DOMElement * replyElement(DOMDocument * document)
{
   DOMElement * element = document->getDocumentElement();
   DOMNodeList * nodeList = element->getChildNodes();
   XMLSize_t nodeCount = nodeList->getLength();
   if (nodeCount > 0) {
      XMLSize_t i = 0;
      for (i=0; i<nodeCount; i++) {
         DOMNode * node = nodeList->item(i);
         DOMNode::NodeType node_type = node->getNodeType();
         if (node_type == DOMNode::ELEMENT_NODE) {
            DOMElement * child = (DOMElement*)node;
            string tagName = S(child->getTagName());
            if (tagName == "Reply") {
               return child;
            }
         }
      }
   }
   return NULL;
}

cXMLStruct * evaluateDocument(DOMDocument * document)
{
   DOMElement * element = requestElement(document);
   if (element != NULL) {
      DOMNodeList * nodeList = element->getChildNodes();
      XMLSize_t nodeCount = nodeList->getLength();
      if (nodeCount > 0) {
         XMLSize_t i = 0;
         for (i=0; i<nodeCount; i++) {
            DOMNode * node = nodeList->item(i);
            DOMNode::NodeType node_type = node->getNodeType();
            if (node_type == DOMNode::ELEMENT_NODE) {
               DOMElement * child = (DOMElement*)node;
               string tagName = S(child->getTagName());
               if (tagName == "DataRequest") {
                  Address * sender = senderComponent(document, element);
                  Address * destination = destinationComponent(document, element);
                  TimeStamp * timeStamp = timeStampComponent(document, child);
                  return new cXMLStruct(dataRequestComponent(document, child, sender, destination, timeStamp));
               } else if (tagName == "SetDataRequest") {
                  Address * sender = senderComponent(document, element);
                  Address * destination = destinationComponent(document, element);
                  return new cXMLStruct(setDataRequestComponent(document, child, sender, destination));
               } else if (tagName == "EventRequest") {
                  Address * sender = senderComponent(document, element);
                  Address * destination = destinationComponent(document, element);
//                  request  eventRequestComponent(document, child, sender, destination);
               }
            }
         }
      }
   } else {
      element = replyElement(document);
      if (element != NULL) {
         DOMNodeList * nodeList = element->getChildNodes();
         XMLSize_t nodeCount = nodeList->getLength();
         if (nodeCount > 0) {
            XMLSize_t i = 0;
            for (i=0; i<nodeCount; i++) {
               DOMNode * node = nodeList->item(i);
               DOMNode::NodeType node_type = node->getNodeType();
               if (node_type == DOMNode::ELEMENT_NODE) {
                  DOMElement * child = (DOMElement*)node;
                  string tagName = S(child->getTagName());
                  if (tagName == "DataReply") {
                     Address * sender = senderComponent(document, element);
                     Address * destination = destinationComponent(document, element);
                     Response * response = responseComponent(document, element);
                     return new cXMLStruct(dataReplyComponent(document, child, sender, destination, response));
                  } else if (tagName == "SetDataReply") {
                     Address * sender = senderComponent(document, element);
                     Address * destination = destinationComponent(document, element);
                     Response * response = responseComponent(document, element);
                     int dummy = 0;
                  } else if (tagName == "EventReply") {
                     Address * sender = senderComponent(document, element);
                     Address * destination = destinationComponent(document, element);
                     Response * response = responseComponent(document, element);
                     int dummy = 0;
                  }
               }
            }
         }
       }
   }
   return NULL;
}

cXMLStruct * cXMLStruct::constructFromDocument(const string & data)
{
   try {
      Log("service.log", "parsing ...n");
      XercesDOMParser * parser = XMLUtils::domParser();
      XMLErrorHandler errorHandler;
      parser->setErrorHandler(&errorHandler);
      MemBufInputSource inputSource((const XMLByte *)data.c_str(), data.size(), "w2f");
      parser->parse(inputSource);
      if (errorHandler.errorsOccured()) {
         string errorMessage = errorHandler.errorMessage();
         Log("service.log", "parse error %s\n", errorMessage.c_str());
         return NULL;
      } else {
         Log("service.log", "parsed\n");
         DOMDocument * document = parser->getDocument();
         cXMLStruct * object = evaluateDocument(document);
         delete document;
         return object;
      }
   } catch (...) {
      return NULL;
   }
}

bool cXMLStruct::createDocument(string & data)
{
   DOMDocument * document = DOMImplementation::getImplementation()->createDocument();
   DOMElement * root_element = document->createElement(X("W2F"));
   document->appendChild(root_element);
   DOMElement * documentElement = document->getDocumentElement();
   if (isRequest()) {
      DOMElement * requestElement = document->createElement(X("Request"));
      documentElement->appendChild(requestElement);
      DOMElement * senderElement = document->createElement(X("Sender"));
      requestElement->appendChild(senderElement);
      DOMElement * destinationElement = document->createElement(X("Destination"));
      requestElement->appendChild(destinationElement);
      if (dataRequest() != NULL) {
         DOMElement * element = addressElement(document, dataRequest()->sender());
         senderElement->appendChild(element);
         element = addressElement(document, dataRequest()->destination());
         destinationElement->appendChild(element);
         element = dataRequestElement(document, dataRequest());
         requestElement->appendChild(element);
      } else if (setDataRequest() != NULL) {
         DOMElement * element = addressElement(document, setDataRequest()->sender());
         senderElement->appendChild(element);
         element = addressElement(document, setDataRequest()->destination());
         destinationElement->appendChild(element);
         element = setDataRequestElement(document, setDataRequest());
         requestElement->appendChild(element);
      } else if (eventRequest()) {
         DOMElement * element = addressElement(document, eventRequest()->sender());
         senderElement->appendChild(element);
         element = addressElement(document, eventRequest()->destination());
         destinationElement->appendChild(element);
         element = eventRequestElement(document, eventRequest());
         requestElement->appendChild(element);
      }
   } else if (isReply()) {
      DOMElement * replyElement = document->createElement(X("Reply"));
      documentElement->appendChild(replyElement);
      DOMElement * senderElement = document->createElement(X("Sender"));
      replyElement->appendChild(senderElement);
      DOMElement * destinationElement = document->createElement(X("Destination"));
      replyElement->appendChild(destinationElement);
      if (dataReply() != NULL) {
         DOMElement * element = addressElement(document, dataReply()->sender());
         senderElement->appendChild(element);
         element = addressElement(document, dataReply()->destination());
         destinationElement->appendChild(element);
         element = dataReplyElement(document, dataReply());
         replyElement->appendChild(element);
      } else if (setDataReply() != NULL) {
         DOMElement * element = addressElement(document, setDataReply()->sender());
         senderElement->appendChild(element);
         element = addressElement(document, setDataReply()->destination());
         destinationElement->appendChild(element);
         element = setDataReplyElement(document, setDataReply());
         replyElement->appendChild(element);
      } else if (eventReply() != NULL) {
         DOMElement * element = addressElement(document, eventReply()->sender());
         senderElement->appendChild(element);
         element = addressElement(document, eventReply()->destination());
         destinationElement->appendChild(element);
         element = eventReplyElement(document, eventReply());
         replyElement->appendChild(element);
      }
   }
   bool success = XMLUtils::formatDocument(document, data);
   delete document;
   return success;
}
