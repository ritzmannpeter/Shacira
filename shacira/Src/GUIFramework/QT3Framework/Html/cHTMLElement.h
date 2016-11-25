//////////////////////////////////////////////////////////////////////
//
// cHTMLElement.h: class interfaces of cHTMLElement
//                 and derived classes
//
//////////////////////////////////////////////////////////////////////

#ifndef CHMTLELEMENT
#define CHMTLELEMENT

#include <qdom.h>
#if defined(QT_MODULE_XML)
#define DOM_INTERFACE_ENABLED
#endif

#ifdef QT_NO_DOM
class QDomDocument{};
class QDomNode{};
class QDomText{};
class QDomElement : public QDomNode {};
#endif

class DOMDisabledException {};

#include "cHTMLDocument.h"
#include <qstring.h>
#include <qstringlist.h> 

class cHTMLDocument;

class cHTMLElement
{
	protected:
		cHTMLDocument* _Document;
		QDomElement _Node;
		QString _TagName;
        QString _ClassName;
	public:
		cHTMLElement(cHTMLDocument* doc, QString tag_name);
		virtual ~cHTMLElement();

		void Init(QString name);
		void Add(cHTMLElement child);
		void Add(QString text);
		cHTMLDocument* Document()	{ return _Document; };
		QDomNode Node()	{ return _Node; };

		virtual void SetClassName(QString name);
		virtual void SetAttribute(QString name, QString value);
		virtual void RemoveAttribute(QString name);
};

class cHTMLRoot: public cHTMLElement
{
	public:
		cHTMLRoot(cHTMLDocument* doc);
		virtual ~cHTMLRoot();
		void Init();
	private:
		
};

class cHTMLHead: public cHTMLElement
{
	public:
		cHTMLHead(cHTMLDocument* doc);
		virtual ~cHTMLHead();
		void Init();
	private:
		
};

class cHTMLMeta: public cHTMLElement
{
	private:
		QString _HttpEquiv;
		QString _Content;
	public:
        enum PropertyType { Client, Server };

		cHTMLMeta(cHTMLDocument* doc, QString http_eqiv="", QString content="", PropertyType property_type = Server);
		virtual ~cHTMLMeta();

		void Init(QString http_eqiv, QString content, PropertyType property_type);
};

class cHTMLStyleSheet : public cHTMLElement
{
	private:
		QString _Link;
	public:
		cHTMLStyleSheet(cHTMLDocument* doc,QString link = "");
		virtual ~cHTMLStyleSheet();
		void Init(QString link);
};

class cHTMLTitle: public cHTMLElement
{
	private:
		QString _Title;
	public:
		cHTMLTitle(cHTMLDocument* doc, QString title = "");
		virtual ~cHTMLTitle();
		void Init(QString title);
};

class cHTMLBody: public cHTMLElement
{
	public:
		cHTMLBody(cHTMLDocument* doc);
		virtual ~cHTMLBody();
		void Init();
	private:
		
};

class cHTMLForm: public cHTMLElement
{
	private:
		QString _Action;
		QString _Method;
		QString _EncType;
	public:
		cHTMLForm(cHTMLDocument* doc, QString action ="", QString method = "POST", QString enctype = "text/plain");
		virtual ~cHTMLForm();
		void Init(QString action, QString method = "POST", QString enctype = "text/plain");
};

class cHTMLParagraph: public cHTMLElement
{
	public:
		cHTMLParagraph(cHTMLDocument* doc);
		virtual ~cHTMLParagraph();
		void Init();
	private:
		
};

class cHTMLBlockGroup: public cHTMLElement
{
	public:
		cHTMLBlockGroup(cHTMLDocument* doc);
		virtual ~cHTMLBlockGroup();
		void Init();
	private:
		
};

class cHTMLNewLine: public cHTMLElement
{
	public:
		cHTMLNewLine(cHTMLDocument* doc);
		virtual ~cHTMLNewLine();
		void Init();
	private:
		
};

class cHTMLHorizontalLine: public cHTMLElement
{
	public:
		cHTMLHorizontalLine(cHTMLDocument* doc);
		virtual ~cHTMLHorizontalLine();
		void Init();
	private:
		
};

class cHTMLFont: public cHTMLElement
{
	public:
		cHTMLFont(cHTMLDocument* doc, QString face_value);
		virtual ~cHTMLFont();
		void Init(QString face_value);

	private:
		QString _FaceValue;
};

class cHTMLTextField: public cHTMLElement
{
	private:
		QString _FieldName;
		QString _Value;
		bool _ReadOnly;
		int _Len;
	public:
		cHTMLTextField(	cHTMLDocument* doc, 
						QString field_name ="", 
						QString value = "", 
						int len = 10,
						bool readonly = true
						);
		virtual ~cHTMLTextField();
		void Init(QString field_name, QString value, int len = 10, bool readonly = true);
};

class cHTMLImage : public cHTMLElement
{
	private:
		QString _File;
	public:
		cHTMLImage(cHTMLDocument* doc,QString file = "", QString alt = "");
		virtual ~cHTMLImage();
		void Init(QString file, QString alt = "");
};

class cHTMLTable: public cHTMLElement
{
	private:
	public:
		cHTMLTable(cHTMLDocument* doc);
		virtual ~cHTMLTable();
		void Init();
};

class cHTMLRow: public cHTMLElement
{
	private:
		bool _IsHeadline;
	public:
		cHTMLRow(cHTMLDocument* doc, bool isHeadline = false);
		virtual ~cHTMLRow();
		void Init(bool isHeadline = false);
		void Add(QString text);
		void Add(cHTMLElement element);
		void Add(QString text, QString alignment, QString class_name = "", QString colspan = "");
		void Add(cHTMLElement element, QString alignment, QString class_name = "", QString colspan = "");
};


/*class cHTMLStrRow: public cHTMLElement
{
	public:
		cHTMLStrRow(cHTMLDocument* doc, QStringList data_list, bool isHeadline = false);
		virtual ~cHTMLStrRow();
		void Init(QStringList data_list, bool isHeadline = false);
};
*/

class cHTMLHeadLine : public cHTMLElement
{
	private:
		QString _Text;
	public:
		cHTMLHeadLine(cHTMLDocument* doc,QString text = "", int order = 1);
		virtual ~cHTMLHeadLine();
		void Init(QString text,int order = 1);
};

//replaced by cHTMLRow::Add(...)
/*class cHTMLTableData: public cHTMLElement
{
	private:
	public:
		cHTMLTableData(cHTMLDocument* doc, bool isHeadline = false,  QString align = "RIGHT");

		virtual ~cHTMLTableData();
		void Init(bool isHeadline = false,  QString align = "RIGHT");
};
*/


class cHTMLLink : public cHTMLElement
{
	private:
		QString _Target;
		QString _Text;
	public:
		cHTMLLink(cHTMLDocument* doc, QString target = "", QString text = "");
		virtual ~cHTMLLink();
		void Init(QString target, QString text);
};


class cHTMLButton : public cHTMLElement
{
	protected:
		QString _Caption;
	public:
		cHTMLButton(cHTMLDocument* doc, QString caption = "");
		virtual ~cHTMLButton() = 0;
};

class cHTMLSubmitButton : public cHTMLButton
{
	public:
		cHTMLSubmitButton(cHTMLDocument* doc, QString caption = "");
		virtual ~cHTMLSubmitButton();
		virtual void Init(QString caption);
};

class cHTMLResetButton : public cHTMLButton
{
	public:
		cHTMLResetButton(cHTMLDocument* doc, QString caption = "");
		virtual ~cHTMLResetButton();
		virtual void Init(QString caption);
};

class cHTMLList : public cHTMLElement
{
	private:
		bool _IsOrdered;
	public:
		cHTMLList(cHTMLDocument* doc, bool ordered = false);
		virtual ~cHTMLList();
		void Init(bool ordered = false);
		void Add(QString text);
		void Add(cHTMLElement element);
        void Add(cHTMLList element);
};

class cHTMLDiv : public cHTMLElement
{
	public:
		cHTMLDiv(cHTMLDocument* doc, QString className);
		virtual ~cHTMLDiv();
		void Init(QString className);		

};

#endif 
