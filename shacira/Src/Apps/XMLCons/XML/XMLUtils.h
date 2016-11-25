
#ifndef _XMLUtils_h_
#define _XMLUtils_h_

#include "xercesc/util/PlatformUtils.hpp"
#include <xercesc/dom/DOM.hpp>
#include "xercesc/parsers/SAXParser.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/dom/DOMException.hpp"
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include "xercesc/sax/HandlerBase.hpp"
#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <string>

XERCES_CPP_NAMESPACE_USE

class XMLUtils
{
public:
   static std::string GetNodeValue(DOMDocument * doc, DOMNode * node, const char * path);
   static std::string GetNodeValue(DOMDocument * doc, DOMNode * node);
   static std::string GetNodeValue(DOMDocument * doc, const char * path);
   static bool SetNodeValue(DOMDocument * doc, DOMNode * node, const char * path, const char * value, bool add = false);
   static bool SetNodeValue(DOMDocument * doc, DOMNode * node, const char * value, bool add = false);
   static bool SetNodeValue(DOMDocument * doc, const char * path, const char * value, bool add = false);
   static bool SetNodeCData(DOMDocument * doc, DOMNode * node, const char * path, const char * value, bool add = false);
   static bool SetNodeCData(DOMDocument * doc, DOMNode * node, const char * value, bool add = false);
   static bool SetNodeCData(DOMDocument * doc, const char * path, const char * value, bool add = false);
   static bool SetNodeAttribute(DOMDocument * doc, DOMNode * node, const char * name, const char * path, const char * value, bool add = false);
   static bool SetNodeAttribute(DOMDocument * doc, DOMNode * node, const char * name, const char * value, bool add = false);
   static bool SetNodeAttribute(DOMDocument * doc, const char * path, const char * name, const char * value, bool add = false);
   static DOMNode * AddNode(DOMDocument * doc, const char * path);
   static DOMNode * AddNode(DOMDocument * doc, DOMNode * node, const char * path);
   static DOMNode * Node(DOMDocument * doc, DOMNode * node, const char * path, bool add = false);
   static DOMNode * Node(DOMDocument * doc, const char * path, bool add = false);
   static DOMDocument * CreateDocument(const char * root_node, const char * dtd_file = NULL);
   static void PrintDocument(DOMDocument * doc, const char * file);
   static std::string GetDocumentText(DOMDocument * doc);
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
   DOMDocumentWrapper(const char * file);
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
#define S(str) StrX(str).localForm()

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

class PIIResolver : public EntityResolver {
public:
   InputSource * resolveEntity (const XMLCh* const publicId, const XMLCh* const systemId);
};

#endif
