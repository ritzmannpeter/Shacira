
#ifndef _XMLHandler_h_
#define _XMLHandler_h_

#include "xercesc/sax/HandlerBase.hpp"
#include <string>

XERCES_CPP_NAMESPACE_USE

XERCES_CPP_NAMESPACE_BEGIN

class XMLHandler : public HandlerBase
{
public:
   // -----------------------------------------------------------------------
   //  Constructors and Destructor
   // -----------------------------------------------------------------------
   XMLHandler();
   ~XMLHandler();

   // -----------------------------------------------------------------------
   //  Handlers for the SAX DocumentHandler interface
   // -----------------------------------------------------------------------
   void startElement(const XMLCh* const name, AttributeList& attributes);
   void characters (const XMLCh* const chars, const XMLSize_t length);
   void endElement(const XMLCh* const name);
   void resetDocument();

   // -----------------------------------------------------------------------
   //  Handlers for the SAX ErrorHandler interface
   // -----------------------------------------------------------------------
	void warning(const SAXParseException& exc);
   void error(const SAXParseException& exc);
   void fatalError(const SAXParseException& exc);
   void resetErrors();
protected:
   void Trim(char * data);
private:
   static int _depth;
   char _currentTag[0x200];
};

class XMLErrorHandler : public ErrorHandler
{
public:
   // -----------------------------------------------------------------------
   //  Constructors and Destructor
   // -----------------------------------------------------------------------
   XMLErrorHandler() : _errorsOccured(false)
   {
   }

   virtual ~XMLErrorHandler()
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
   bool errorsOccured() const {return _errorsOccured;};
   std::string errorMessage() const {return _errorMessage;}
private:
   bool _errorsOccured;
   std::string _errorMessage;
};

XERCES_CPP_NAMESPACE_END

#endif
