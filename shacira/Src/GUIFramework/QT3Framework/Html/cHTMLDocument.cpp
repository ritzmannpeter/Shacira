//////////////////////////////////////////////////////////////////////
//
// cHTMLDocument.cpp: implementation of class cHTMLDocument.
//
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include "cHTMLDocument.h"
#include "cHTMLElement.h"

//////////////////////////////////////////////////////////////////////
// HTMLDocument
//////////////////////////////////////////////////////////////////////

cHTMLDocument::cHTMLDocument(QString docType)
:	_DocType(docType == "" ? "HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\"" : docType)
#ifdef DOM_INTERFACE_ENABLED
	, _Document(_DocType)
#endif
{
   _Root = new cHTMLRoot(this);
#ifdef DOM_INTERFACE_ENABLED
   _Document.appendChild( _Root->Node() );
#endif
}

cHTMLDocument::~cHTMLDocument()
{
	delete _Root;
}

QDomElement cHTMLDocument::CreateElement(QString name)
{
#ifdef DOM_INTERFACE_ENABLED
	return _Document.createElement(name);
#else
   throw DOMDisabledException();
#endif
}

QDomText cHTMLDocument::CreateTextNode(QString value)
{
#ifdef DOM_INTERFACE_ENABLED
	return _Document.createTextNode(value);
#else
   throw DOMDisabledException();
#endif
}

QString cHTMLDocument::ToHTML(int ident)
{
#ifdef DOM_INTERFACE_ENABLED
	return _Document.toString(ident);
#else
   return "Error: HTML generation interface not enabled";
#endif
}
