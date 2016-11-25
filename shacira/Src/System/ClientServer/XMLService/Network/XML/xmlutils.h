
#ifndef _XMLUtils_h_
#define _XMLUtils_h_

#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/parsers/SAXParser.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/dom/DOMException.hpp"
#include "xercesc/framework/MemBufFormatTarget.hpp"
#include "xercesc/framework/MemBufInputSource.hpp"
#include "xercesc/framework/LocalFileFormatTarget.hpp"
#include "xercesc/framework/LocalFileInputSource.hpp"
#include "xercesc/util/OutOfMemoryException.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/sax/EntityResolver.hpp"
#include "xercesc/sax/InputSource.hpp"
#include <string>
#include <map>

XERCES_CPP_NAMESPACE_USE

XERCES_CPP_NAMESPACE_BEGIN

class XMLErrorHandler;

class XercesInitializer
{
public:
   XercesInitializer();
   ~XercesInitializer();
};

typedef std::map<int,XercesDOMParser*> DOM_PARSER_MAP_T;

class XMLUtils
{
public:
   static XercesInitializer _initializer;
   static DOM_PARSER_MAP_T _domParserMap;
   static int _domParserCount;
   static std::string GetNodeValue(DOMDocument * doc, DOMNode * node, const std::string & path);
   static std::string GetNodeValue(DOMDocument * doc, DOMNode * node);
   static std::string GetNodeValue(DOMDocument * doc, const std::string & path);
   static bool SetNodeValue(DOMDocument * doc, DOMNode * node, const std::string & path, const std::string & value, bool add = false);
   static bool SetNodeValue(DOMDocument * doc, DOMNode * node, const std::string & value, bool add = false);
   static bool SetNodeValue(DOMDocument * doc, const std::string & path, const std::string & value, bool add = false);
   static bool SetNodeAttribute(DOMDocument * doc, DOMNode * node, const std::string & name, const std::string & path, const std::string & value, bool add = false);
   static bool SetNodeAttribute(DOMDocument * doc, DOMNode * node, const std::string & name, const std::string & value, bool add = false);
   static bool SetNodeAttribute(DOMDocument * doc, const std::string & path, const std::string & name, const std::string & value, bool add = false);
   static DOMNode * AddNode(DOMDocument * doc, const std::string & path);
   static DOMNode * AddNode(DOMDocument * doc, DOMNode * node, const std::string & path);
   static DOMNode * Node(DOMDocument * doc, DOMNode * node, const std::string & path, bool add = false);
   static DOMNode * Node(DOMDocument * doc, const std::string & path, bool add = false);
   static DOMDocument * CreateDocument(const std::string & root_node, const std::string & dtd_file = NULL);
   static bool printDocument(DOMDocument * doc, const std::string & file);
   static bool formatDocument(DOMDocument * doc, std::string & buffer);
   static XercesDOMParser * domParser();
   static void setData(DOMDocument * document, DOMElement * element, const std::string & data, bool ignoreEmptyData = false);
   static std::string getData(DOMDocument * document, DOMElement * element);
private:
   static void SplitPath(const std::string & path, std::string & tag, std::string & tail);
};

class ErrorHandlerWrapper : public ErrorHandler
{
public:
   // -----------------------------------------------------------------------
   //  Constructors and Destructor
   // -----------------------------------------------------------------------
   ErrorHandlerWrapper() : _ErrorsOccured(false)
   {
   }

   virtual ~ErrorHandlerWrapper()
   {
   }

   // -----------------------------------------------------------------------
   //  Implementation of the error handler interface
   // -----------------------------------------------------------------------
   void warning(const SAXParseException& toCatch);
   void error(const SAXParseException& toCatch);
   void fatalError(const SAXParseException& toCatch);
   void resetErrors();

   // -----------------------------------------------------------------------
   //  Getter methods
   // -----------------------------------------------------------------------
   bool ErrorsOccured() const {return _ErrorsOccured;};
   std::string ErrorMessage() const {return _ErrorMessage;}
private:
   bool _ErrorsOccured;
   std::string _ErrorMessage;
};

class DOMDocumentWrapper
{
public:
   DOMDocumentWrapper(const std::string & file);
   DOMDocumentWrapper(const DOMDocumentWrapper & right);
public:
   virtual ~DOMDocumentWrapper();
   void Release();
public:
   inline std::string File() {return _File;};
   inline std::string ErrorMessage() {return _ErrorMessage;};
   bool Validate(ErrorHandlerWrapper * error_handler);
   bool Parse(HandlerBase * document_handler, ErrorHandlerWrapper * error_handler);
   DOMDocument * Document();
private:
   std::string _File;
   std::string _ErrorMessage;
   XercesDOMParser * _DOMParser;
   SAXParser * _SAXParser;
   int * _RefCount;
};

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------
class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
    {
        // Call the private transcoding method
        fLocalForm = XMLString::transcode(toTranscode);
    }

    ~StrX()
    {
        XMLString::release(&fLocalForm);
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const char* localForm() const
    {
        return fLocalForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocalForm
    //      This is the local code page form of the string.
    // -----------------------------------------------------------------------
    char*   fLocalForm;
};
#define S(str) string(StrX(str).localForm())

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of char* data to XMLCh data.
// ---------------------------------------------------------------------------
class XStr
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XStr(const char* const toTranscode)
    {
        // Call the private transcoding method
        fUnicodeForm = XMLString::transcode(toTranscode);
    }

    ~XStr()
    {
        XMLString::release(&fUnicodeForm);
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh* unicodeForm() const
    {
        return fUnicodeForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh*   fUnicodeForm;
};
#define X(str) XStr(str).unicodeForm()

class DTDResolver : public EntityResolver {
public:
   InputSource * resolveEntity (const XMLCh* const publicId, const XMLCh* const systemId);
};

XERCES_CPP_NAMESPACE_END

#endif
