
#include "XMLHandler.h"
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <windows.h>
#include "XMLUtils.h"
#include "Base/basedef.h"
#include <list>

typedef std::list<std::string> PATH_T;
PATH_T _Path;
static std::string Path()
{
   std::string path;
   PATH_T::const_iterator i = _Path.begin();
   while (i != _Path.end()) {
      path += "/";
      path += (*i);
      i++;
   }
   return path;
}

static void CopyString(char * s, const XMLCh * v)
{
   int i = 0;
   for (i=0; i<0x200; i++) {
      char c = (char)v[i];
      s[i] = c;
      if (c == 0) {
         break;
      }
      if (c == 10) {
         s[i] = 0;
         break;
      }
   }
}

int XMLHandler::_depth = 0;

XMLHandler::XMLHandler()
{
   memset(_currentTag, 0, sizeof(_currentTag));
}

XMLHandler::~XMLHandler()
{
}


// ---------------------------------------------------------------------------
//  XMLHandler: Implementation of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void XMLHandler::startElement(const XMLCh * name, AttributeList&  attributes)
{
   _depth++;
   CopyString(_currentTag, name);
}

void XMLHandler::characters(const XMLCh * chars, const XMLSize_t length)
{
   char data[0x500] = {0};
   CopyString(data, chars);
   Sleep(0);
}

void XMLHandler::endElement(const XMLCh * name)
{
   char ename[0x200] = {0};
   CopyString(ename, name);
   memset(_currentTag, 0, sizeof(_currentTag));
}

void XMLHandler::resetDocument()
{
}

// ---------------------------------------------------------------------------
//  XMLHandler: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void XMLHandler::error(const SAXParseException& e)
{
}

void XMLHandler::fatalError(const SAXParseException& e)
{
}

void XMLHandler::warning(const SAXParseException& e)
{
}

void XMLHandler::resetErrors()
{
}

void XMLHandler::Trim(char * data)
{
   int len = (int)strlen(data);
   int i = 0;
   for (i=len-1; i>=0; i--) {
      if (data[i] == ' ') {
         data[i] = 0;
      } else {
         return;
      }
   }
}

void XMLErrorHandler::error(const SAXParseException& toCatch)
{
   _errorsOccured = true;
   _errorMessage = StrX(toCatch.getMessage()).localForm();
   _errorMessage += " at line ";
   _errorMessage += itos((int)toCatch.getLineNumber());
   _errorMessage += " column ";
   _errorMessage += itos((int)toCatch.getColumnNumber());
}

void XMLErrorHandler::fatalError(const SAXParseException& toCatch)
{
   _errorsOccured = true;
   _errorMessage = StrX(toCatch.getMessage()).localForm();
   _errorMessage += " at line ";
   _errorMessage += itos((int)toCatch.getLineNumber());
   _errorMessage += " column ";
   _errorMessage += itos((int)toCatch.getColumnNumber());
}

void XMLErrorHandler::warning(const SAXParseException& e)
{
}

void XMLErrorHandler::resetErrors()
{
   _errorsOccured = false;
   _errorMessage = "";
}

 