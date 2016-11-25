//////////////////////////////////////////////////////////////////////
//
// cHTMLDocument.h: interface of class cHTMLDocument
//
//////////////////////////////////////////////////////////////////////

#ifndef CHTMLDOCUMENT
#define CHTMLDOCUMENT

#include <qdom.h>
#if defined(QT_MODULE_XML)
#define DOM_INTERFACE_ENABLED
#endif

#include <qstring.h>
#include "cHTMLElement.h"

class cHTMLElement;

#ifndef DOM_INTERFACE_ENABLED
class cHTMLDisabled {
};
#endif

class cHTMLDocument  
{
private:
	QString _DocType;
    QDomDocument _Document;
    cHTMLElement* _Root;
public:
	cHTMLDocument(QString docType = "");
	virtual ~cHTMLDocument();

	QDomElement CreateElement(QString name);
	QDomText CreateTextNode(QString value);
	cHTMLElement* Root() { return _Root; }
	QString ToHTML(int ident=1);
};

#endif
