
#include "XMLUtils.h"
#include <stdio.h>

static void SplitPath(const char * path, std::string & tag, std::string & tail)
{
   int len = strlen(path);
   bool is_tail = false;
   int i = 0;
   for (i=0; i<len; i++) {
      char c = path[i];
      if (is_tail) {
         tail += c;
      } else {
         if (c == '/') {
            is_tail = true;
         } else {
            tag += c;
         }
      }
   }
}

std::string XMLUtils::GetNodeValue(DOMDocument * doc, DOMNode * node, const char * path)
{
   std::string value;
   if (doc == NULL || node == NULL) {
      return value;
   }
   int len = strlen(path);
   if (len > 0) {
      DOMNode * new_node = Node(doc, node, path);
      if (new_node != NULL) {
         return GetNodeValue(doc, new_node);
      }
   } else {
      return GetNodeValue(doc, node);
   }
   return value;
}

std::string XMLUtils::GetNodeValue(DOMDocument * doc, DOMNode * node)
{
   std::string value;
   if (doc == NULL || node == NULL) {
      return value;
   }
   DOMNodeList * children = node->getChildNodes();
   int child_count = children->getLength();
   if (child_count == 0) {
      return value;
   } else {
      int i = 0;
      for (i=0; i<child_count; i++) {
         DOMNode * node = children->item(i);
         std::string name = S(node->getNodeName());
         if (strcmp(name.c_str(), "#text") == 0) {
            value = S(node->getNodeValue());
            return value;
         } else if (strcmp(name.c_str(), "#cdata-section") == 0) {
            value = S(node->getNodeValue());
            return value;
         }
      }
   }
   return value;
}

std::string XMLUtils::GetNodeValue(DOMDocument * doc, const char * path)
{
   std::string value;
   if (doc == NULL) {
      return value;
   }
   DOMNode * node = Node(doc, (DOMNode*) doc->getDocumentElement(), path);
   if (node != NULL) {
      return GetNodeValue(doc, node);
   }
   return value;
}

bool XMLUtils::SetNodeValue(DOMDocument * doc, DOMNode * node, const char * path, const char * value, bool add)
{
   if (doc == NULL || node == NULL) {
      return false;
   }
   int len = strlen(path);
   if (len > 0) {
      DOMNode * new_node = Node(doc, node, path, add);
      if (new_node != NULL) {
         return SetNodeValue(doc, new_node, value, add);
      }
   } else {
      return SetNodeValue(doc, node, value, add);
   }
   return false;
}

bool XMLUtils::SetNodeValue(DOMDocument * doc, DOMNode * node, const char * value, bool add)
{
   if (doc == NULL || node == NULL) {
      return false;
   }
   DOMNodeList * children = node->getChildNodes();
   int child_count = children->getLength();
   if (child_count == 0) {
      DOMText * text = doc->createTextNode(X(value));
      node->appendChild(text);
      return true;
   } else {
      int i = 0;
      for (i=0; i<child_count; i++) {
         DOMNode * node = children->item(i);
         std::string name = S(node->getNodeName());
         if (strcmp(name.c_str(), "#text") == 0) {
            node->setNodeValue(X(value));
            return true;
         } else if (strcmp(name.c_str(), "#cdata-section") == 0) {
            node->setNodeValue(X(value));
            return true;
         }
      }
   }
   return false;
}

bool XMLUtils::SetNodeValue(DOMDocument * doc, const char * path, const char * value, bool add)
{
   if (doc == NULL) {
      return false;
   }
   DOMNode * node = Node(doc, (DOMNode*) doc->getDocumentElement(), path, add);
   if (node != NULL) {
      return SetNodeValue(doc, node, value, add);
   }
   return false;
}










bool XMLUtils::SetNodeCData(DOMDocument * doc, DOMNode * node, const char * path, const char * value, bool add)
{
   if (doc == NULL || node == NULL) {
      return false;
   }
   int len = strlen(path);
   if (len > 0) {
      DOMNode * new_node = Node(doc, node, path, add);
      if (new_node != NULL) {
         return SetNodeCData(doc, new_node, value, add);
      }
   } else {
      return SetNodeCData(doc, node, value, add);
   }
   return false;
}

bool XMLUtils::SetNodeCData(DOMDocument * doc, DOMNode * node, const char * value, bool add)
{
   if (doc == NULL || node == NULL) {
      return false;
   }
   DOMNodeList * children = node->getChildNodes();
   int child_count = children->getLength();
   if (child_count == 0) {
      DOMCDATASection * data_section = doc->createCDATASection(X(value));
      node->appendChild(data_section);
      return true;
   } else {
      int i = 0;
      for (i=0; i<child_count; i++) {
         DOMNode * node = children->item(i);
         std::string name = S(node->getNodeName());
         if (strcmp(name.c_str(), "#text") == 0) {
            node->setNodeValue(X(value));
            return true;
         } else if (strcmp(name.c_str(), "#cdata-section") == 0) {
            node->setNodeValue(X(value));
            return true;
         }
      }
   }
   return false;
}

bool XMLUtils::SetNodeCData(DOMDocument * doc, const char * path, const char * value, bool add)
{
   if (doc == NULL) {
      return false;
   }
   DOMNode * node = Node(doc, (DOMNode*) doc->getDocumentElement(), path, add);
   if (node != NULL) {
      return SetNodeCData(doc, node, value, add);
   }
   return false;
}













bool XMLUtils::SetNodeAttribute(DOMDocument * doc, DOMNode * node, const char * path, const char * name, const char * value, bool add)
{
   if (doc == NULL || node == NULL) {
      return false;
   }
   int len = strlen(path);
   if (len > 0) {
      DOMNode * new_node = Node(doc, node, path, add);
      if (new_node != NULL) {
         return SetNodeAttribute(doc, new_node, name, value, add);
      }
   } else {
      return SetNodeAttribute(doc, node, name, value, add);
   }
   return false;
}

bool XMLUtils::SetNodeAttribute(DOMDocument * doc, DOMNode * node, const char * name, const char * value, bool add)
{
   if (doc == NULL || node == NULL) {
      return false;
   }
   DOMNodeList * children = node->getChildNodes();
   int child_count = children->getLength();
   if (child_count == 0) {
      DOMAttr * attribute = doc->createAttribute(X(name));
      attribute->setValue(X(value));
      DOMElement * element = (DOMElement*)node;
      element->setAttributeNode(attribute);
//      node->appendChild(attribute);
      return true;
   } else {
      int i = 0;
      for (i=0; i<child_count; i++) {
         DOMNode * node = children->item(i);
         std::string node_name = S(node->getNodeName());
         if (strcmp(node_name.c_str(), name) == 0) {
            node->setNodeValue(X(value));
            return true;
         }
      }
   }
   return false;
}

bool XMLUtils::SetNodeAttribute(DOMDocument * doc, const char * path, const char * name, const char * value, bool add)
{
   if (doc == NULL) {
      return false;
   }
   DOMNode * node = Node(doc, (DOMNode*) doc->getDocumentElement(), path, add);
   if (node != NULL) {
      return SetNodeValue(doc, node, value, add);
   }
   return false;
}

DOMNode * XMLUtils::AddNode(DOMDocument * doc, const char * path)
{
   DOMNode * node = Node(doc, (DOMNode*) doc->getDocumentElement(), path, true);
   return node;
}

DOMNode * XMLUtils::AddNode(DOMDocument * doc, DOMNode * node, const char * path)
{
   DOMNode * new_node = Node(doc, node, path, true);
   return new_node;
}

DOMNode * XMLUtils::Node(DOMDocument * doc, DOMNode * node, const char * path, bool add)
{
   if (doc == NULL) {
      return NULL;
   }
   if (node == NULL) {
      return NULL;
   }
   std::string tag;
   std::string tail;
   SplitPath(path, tag, tail);
   DOMNodeList * children = node->getChildNodes();
   int child_count = children->getLength();
   if (add && tail.size() == 0) {
      DOMElement * element = doc->createElement(X(tag.c_str()));
      node->appendChild(element);
      return element;
   }
   int i = 0;
   for (i=0; i<child_count; i++) {
      DOMNode * node = children->item(i);
      std::string name = S(node->getNodeName());
      if (strcmp(name.c_str(), tag.c_str()) == 0) {
         if (tail.size() == 0) {
            return node;
         } else {
            return Node(doc, node, tail.c_str(), add);
         }
      }
   }
   DOMElement * element = doc->createElement(X(tag.c_str()));
   node->appendChild(element);
   if (tail.size() == 0) {
      return element;
   } else {
      return Node(doc, element, tail.c_str(), add);
   }
}

DOMNode * XMLUtils::Node(DOMDocument * doc, const char * path, bool add)
{
   return Node(doc, (DOMNode*)doc->getDocumentElement(), path, add);
}

DOMDocument * XMLUtils::CreateDocument(const char * root_node, const char * dtd_file)
{
   XMLCh temp_str[3] = {chLatin_L, chLatin_S, chNull};
   DOMImplementation * impl = DOMImplementationRegistry::getDOMImplementation(temp_str);
   if (impl != NULL) {
      XStr namespace_uri("");
      XStr qualified_name(root_node);
      XStr public_id("");
      XStr system_id(dtd_file);
      DOMDocumentType * doctype = NULL;
      if (dtd_file != NULL) {
         doctype = impl->createDocumentType(qualified_name.unicodeForm(),
                                            public_id.unicodeForm(),
                                            system_id.unicodeForm());
      }
      DOMDocument * doc = impl->createDocument(namespace_uri.unicodeForm(),
                                               qualified_name.unicodeForm(),
                                               doctype);
      if (doc != NULL) {
         return doc;
      }
   }
   return NULL;
}

void XMLUtils::PrintDocument(DOMDocument * doc, const char * file)
{
   try {
      // get a serializer, an instance of DOMLSSerializer
      XMLCh tempStr[3] = {chLatin_L, chLatin_S, chNull};
      DOMImplementation * impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
      DOMLSSerializer * theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();
      DOMLSOutput * theOutputDesc = ((DOMImplementationLS*)impl)->createLSOutput();
      // set user specified output encoding
      theOutputDesc->setEncoding(0);
      // plug in user's own error handler
      DOMConfiguration* serializerConfig=theSerializer->getDomConfig();
      // set feature if the serializer supports the feature/mode
      serializerConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
      //
      // Plug in a format target to receive the resultant
      // XML stream from the serializer.
      //
      XMLFormatTarget * myFormTarget;
      myFormTarget = new LocalFileFormatTarget(file);
      theOutputDesc->setByteStream(myFormTarget);
      //
      // do the serialization through DOMLSSerializer::write();
      //
      theSerializer->write(doc, theOutputDesc);
      theOutputDesc->release();
      theSerializer->release();
      //
      // Filter, formatTarget and error handler
      // are NOT owned by the serializer.
      //
      delete myFormTarget;
   } catch (const OutOfMemoryException&) {
      int dummy = 0;
   } catch (XMLException& e) {
      std::string m = S(e.getMessage());
      int dummy = 0;
   }
}

std::string XMLUtils::GetDocumentText(DOMDocument * doc)
{
   try {
      // get a serializer, an instance of DOMLSSerializer
      XMLCh tempStr[3] = {chLatin_L, chLatin_S, chNull};
      DOMImplementation * impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
      DOMLSSerializer * theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();
      DOMLSOutput * theOutputDesc = ((DOMImplementationLS*)impl)->createLSOutput();
      // set user specified output encoding
      theOutputDesc->setEncoding(0);
      // plug in user's own error handler
      DOMConfiguration* serializerConfig=theSerializer->getDomConfig();
      // set feature if the serializer supports the feature/mode
      serializerConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
      //
      // Plug in a format target to receive the resultant
      // XML stream from the serializer.
      //
      MemBufFormatTarget * format_target = new MemBufFormatTarget;
      theOutputDesc->setByteStream(format_target);
      //
      // do the serialization through DOMLSSerializer::write();
      //
      theSerializer->write(doc, theOutputDesc);
      int size = format_target->getLen();
      const XMLByte * buffer = format_target->getRawBuffer();
      std::string xml_data = (const char*)buffer;
      theOutputDesc->release();
      theSerializer->release();
      //
      // Filter, formatTarget and error handler
      // are NOT owned by the serializer.
      //
      delete format_target;
      return xml_data;
   } catch (const OutOfMemoryException&) {
      return "out of memory";
   } catch (XMLException& e) {
      std::string m = S(e.getMessage());
      return m;
   }
}


void ErrorHandlerWrapper::error(const SAXParseException& toCatch)
{
   _ErrorsOccured = true;
   _ErrorMessage = StrX(toCatch.getMessage()).localForm();
   char pos[0x50] = {0};
   _snprintf(pos, sizeof(pos), " at line %d column %d", toCatch.getLineNumber(), toCatch.getColumnNumber());
   _ErrorMessage += pos;
}

void ErrorHandlerWrapper::fatalError(const SAXParseException& toCatch)
{
   _ErrorsOccured = true;
   _ErrorMessage = StrX(toCatch.getMessage()).localForm();
   char pos[0x50] = {0};
   _snprintf(pos, sizeof(pos), " at line %d column %d", toCatch.getLineNumber(), toCatch.getColumnNumber());
   _ErrorMessage += pos;
}

void ErrorHandlerWrapper::warning(const SAXParseException& e)
{
}

void ErrorHandlerWrapper::resetErrors()
{
   _ErrorsOccured = false;
   _ErrorMessage = "";
}



DOMDocumentWrapper::DOMDocumentWrapper(const char * file)
      : _DOMParser(NULL), _SAXParser(NULL)
{
   if (file != NULL) {
      _File = file;
   } else {
      int dummy = 0;
   }
   _RefCount = (int*)calloc(1, sizeof(int));
   *_RefCount = 0;
};

DOMDocumentWrapper::DOMDocumentWrapper(const DOMDocumentWrapper & right)
{
   _RefCount = right._RefCount;
   _DOMParser = right._DOMParser;
   _SAXParser = right._SAXParser;
   _ErrorMessage = right._ErrorMessage;
   *_RefCount = (*_RefCount) + 1;
};

DOMDocumentWrapper::~DOMDocumentWrapper()
{
   int ref_count = *_RefCount;
   if (ref_count == 0) {
      Release();
   } else {
      ref_count--;
      *_RefCount = ref_count;
   }
}

void DOMDocumentWrapper::Release()
{
   if (_DOMParser != NULL) {
      delete _DOMParser;
      _DOMParser = NULL;
   }
   if (_SAXParser != NULL) {
      delete _SAXParser;
      _SAXParser = NULL;
   }
   int * ref_count = _RefCount;
   _RefCount = NULL;
   free(ref_count);
}

bool DOMDocumentWrapper::Validate(ErrorHandlerWrapper * error_handler)
{
   try {
      if (_DOMParser != NULL) {
         delete _DOMParser;
         _DOMParser = NULL;
      }
      _DOMParser = new XercesDOMParser;
      PIIResolver * r = new PIIResolver;
      _DOMParser->setEntityResolver(r);
      _DOMParser->setValidationScheme(XercesDOMParser::Val_Always);
      _DOMParser->setErrorHandler(error_handler);
      _DOMParser->parse(_File.c_str());
      if (error_handler->ErrorsOccured()) {
         _ErrorMessage = error_handler->ErrorMessage();
         return false;
      } else {
         return true;
      }
   } catch (...) {
   }
   return false;
}

bool DOMDocumentWrapper::Parse(HandlerBase * document_handler, ErrorHandlerWrapper * error_handler)
{
   try {
      if (_SAXParser != NULL) {
         delete _SAXParser;
         _SAXParser = NULL;
      }
      _SAXParser = new SAXParser;
      PIIResolver * r = new PIIResolver;
      _SAXParser->setEntityResolver(r);
      _SAXParser->setDocumentHandler(document_handler);
      _SAXParser->setErrorHandler(error_handler);
      _SAXParser->parse(_File.c_str());
      if (error_handler->ErrorsOccured()) {
         _ErrorMessage = error_handler->ErrorMessage();
         return false;
      } else {
         return true;
      }
   } catch (...) {
   }
   return false;
}


DOMDocument * DOMDocumentWrapper::Document()
{
   if (_DOMParser != NULL) {
      return _DOMParser->getDocument();
   }
   return NULL;
}

InputSource * PIIResolver::resolveEntity (const XMLCh* const publicId, const XMLCh* const systemId)
{
   StrX p(publicId);
   StrX s(systemId);
   const char * _p = p.localForm();
   const char * _s = s.localForm();
   int len = strlen(_s);
   int fpos = 0;
   for (fpos=len-1; fpos>=0; fpos--) {
      if (_s[fpos] == '/') {
         break;
      }
   }
   fpos++;
   const char * file_name = &(_s[fpos]);
   if (_stricmp(file_name, "piianf.dtd") == 0) {
      return new LocalFileInputSource(X("PIF/dtd/piianf.dtd"));
   } else if (_stricmp(file_name, "piiprddat.dtd") == 0) {
      return new LocalFileInputSource(X("PIF/dtd/piiprddat.dtd"));
   } else if (_stricmp(file_name, "piiprdlst.dtd") == 0) {
      return new LocalFileInputSource(X("PIF/dtd/piiprdlst.dtd"));
   } else if (_stricmp(file_name, "piiV7anf.dtd") == 0) {
      return new LocalFileInputSource(X("PIF/dtd/piiV7anf.dtd"));
   } else if (_stricmp(file_name, "piiV7prddat.dtd") == 0) {
      return new LocalFileInputSource(X("PIF/dtd/piiV7prddat.dtd"));
   } else if (_stricmp(file_name, "piiV7prdlst.dtd") == 0) {
      return new LocalFileInputSource(X("PIF/dtd/piiV7prdlst.dtd"));
   } else {
      return NULL;
   }
}

