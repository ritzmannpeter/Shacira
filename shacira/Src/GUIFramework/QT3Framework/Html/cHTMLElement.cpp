//////////////////////////////////////////////////////////////////////
//
// cHTMLElement.cpp: implementation pf class cHTMLElement
//                   and derived classes
//
//////////////////////////////////////////////////////////////////////
#include "cHTMLElement.h"

//////////////////////////////////////////////////////////////////////
// HTMLElement
//////////////////////////////////////////////////////////////////////
cHTMLElement::cHTMLElement(cHTMLDocument* doc, QString tag_name)
: _Document(doc),_Node(),  _TagName(tag_name), _ClassName("cHTMLElement")
{
	Init(tag_name);
}

cHTMLElement::~cHTMLElement()
{
}

void cHTMLElement::Add(cHTMLElement child)
{
#ifdef DOM_INTERFACE_ENABLED
	_Node.appendChild(child.Node());
#endif
}

void cHTMLElement::Add(QString text)
{
#ifdef DOM_INTERFACE_ENABLED
	_Node.appendChild(_Document->CreateTextNode(text));
#endif
}

void cHTMLElement::Init(QString name)
{
#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( name );
#endif
}

void cHTMLElement::SetAttribute(QString name, QString value)
{
#ifdef DOM_INTERFACE_ENABLED
	if(_Node.hasAttribute(name)) {
		_Node.removeAttribute(name);
	}
	_Node.setAttribute(name, value);
#endif
}

void cHTMLElement::RemoveAttribute(QString name)
{
#ifdef DOM_INTERFACE_ENABLED
	if(_Node.hasAttribute(name)) {
		_Node.removeAttribute(name);
	}
#endif
}

void cHTMLElement::SetClassName(QString name)
{
#ifdef DOM_INTERFACE_ENABLED
   SetAttribute("CLASS", name);
#endif
}

//////////////////////////////////////////////////////////////////////
// Root
//////////////////////////////////////////////////////////////////////
cHTMLRoot::cHTMLRoot(cHTMLDocument* doc)
: cHTMLElement(doc, "HTML")
{
    _ClassName = "cHTMLRoot";
}

cHTMLRoot::~cHTMLRoot()
{
}

void cHTMLRoot::Init()
{
	cHTMLElement::Init("HTML");
}
//////////////////////////////////////////////////////////////////////
// Head
//////////////////////////////////////////////////////////////////////
cHTMLHead::cHTMLHead(cHTMLDocument* doc)
: cHTMLElement(doc, "HEAD")
{
   _ClassName = "cHTMLHead";
}

cHTMLHead::~cHTMLHead()
{
}

void cHTMLHead::Init()
{
	cHTMLElement::Init("HEAD");
}

//////////////////////////////////////////////////////////////////////
// Meta
//////////////////////////////////////////////////////////////////////
cHTMLMeta::cHTMLMeta(cHTMLDocument* doc, QString http_equiv, QString content, PropertyType property_type)
: cHTMLElement(doc, "META"), _HttpEquiv(http_equiv), _Content(content)
{
    _ClassName = "cHTMLMeta";
    Init(http_equiv, content, property_type);
}

cHTMLMeta::~cHTMLMeta()
{
}

void cHTMLMeta::Init(QString http_equiv, QString content, PropertyType property_type)
{
#ifdef DOM_INTERFACE_ENABLED
    QString qPropertyType;
    qPropertyType = (property_type == Server) ? "HTTP-EQUIV" : "NAME";


	_HttpEquiv = http_equiv;
	_Content = content;

	_Node = _Document->CreateElement( "META" );
	_Node.setAttribute(qPropertyType, _HttpEquiv);
	_Node.setAttribute("CONTENT", _Content);
#endif
}
//////////////////////////////////////////////////////////////////////
// Stylesheet
//////////////////////////////////////////////////////////////////////
cHTMLStyleSheet::cHTMLStyleSheet(cHTMLDocument* doc, QString link)
: cHTMLElement(doc, "LINK"), _Link(link)
{
    _ClassName = "cHTMLStyleSheet";
	Init(link);
}

cHTMLStyleSheet::~cHTMLStyleSheet()
{
}

void cHTMLStyleSheet::Init(QString link)
{
#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( "LINK" );
	_Link = link;
	_Node.setAttribute("REL", "stylesheet");
	_Node.setAttribute("TYPE", "text/css" );
	_Node.setAttribute("HREF", _Link );
#endif
}

//////////////////////////////////////////////////////////////////////
// Title
//////////////////////////////////////////////////////////////////////
cHTMLTitle::cHTMLTitle(cHTMLDocument* doc, QString title)
: cHTMLElement(doc, "TITLE"), _Title(title)
{
    _ClassName = "cHTMLTitle";
	Init(title);
}

cHTMLTitle::~cHTMLTitle()
{
		
}

void cHTMLTitle::Init(QString title)
{
#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( "TITLE" );
	_Title = title;
	QDomText t = _Document->CreateTextNode(_Title);
	_Node.appendChild(t);
#endif
}

//////////////////////////////////////////////////////////////////////
// Body
//////////////////////////////////////////////////////////////////////
cHTMLBody::cHTMLBody(cHTMLDocument* doc)
: cHTMLElement(doc, "BODY")
{
    _ClassName = "cHTMLBody";
}

cHTMLBody::~cHTMLBody()
{
}
void cHTMLBody::Init()
{
	cHTMLElement::Init("BODY");
}
//////////////////////////////////////////////////////////////////////
// Form
//////////////////////////////////////////////////////////////////////
cHTMLForm::cHTMLForm(cHTMLDocument* doc, QString action, QString method, QString enctype)
: cHTMLElement(doc, "FORM"), _Action(action), _Method(method), _EncType(enctype)
{
    _ClassName = "cHTMLForm";

	Init(action, method, enctype);
}

cHTMLForm::~cHTMLForm()
{
}

void cHTMLForm::Init(QString action, QString method, QString enctype)
{
	_Action = action;
	_Method = method;
	_EncType = enctype;

	cHTMLElement::Init("FORM");
#ifdef DOM_INTERFACE_ENABLED
	_Node.setAttribute("ACTION", _Action);
	_Node.setAttribute("METHOD", _Method);
	_Node.setAttribute("ENC-TYPE", _EncType);
#endif
}
//////////////////////////////////////////////////////////////////////
// Paragraph
//////////////////////////////////////////////////////////////////////
cHTMLParagraph::cHTMLParagraph(cHTMLDocument* doc)
: cHTMLElement(doc, "P")
{
// PR 29.09.05 initialize when constructing
   _ClassName = "cHTMLParagraph";

   Init();
}

cHTMLParagraph::~cHTMLParagraph()
{
}

void cHTMLParagraph::Init()
{
	cHTMLElement::Init("P");
}

//////////////////////////////////////////////////////////////////////
// Block group
//////////////////////////////////////////////////////////////////////
cHTMLBlockGroup::cHTMLBlockGroup(cHTMLDocument* doc)
: cHTMLElement(doc, "SPAN")
{
   _ClassName = "cHTMLBlockGroup";
   Init();
}

cHTMLBlockGroup::~cHTMLBlockGroup()
{
}

void cHTMLBlockGroup::Init()
{
	cHTMLElement::Init("SPAN");
}

//////////////////////////////////////////////////////////////////////
// New line
//////////////////////////////////////////////////////////////////////
cHTMLNewLine::cHTMLNewLine(cHTMLDocument* doc)
: cHTMLElement(doc, "BR")
{
   _ClassName = "cHTMLNewLine";

   Init();
}

cHTMLNewLine::~cHTMLNewLine()
{
}

void cHTMLNewLine::Init()
{
	cHTMLElement::Init("BR");
}

//////////////////////////////////////////////////////////////////////
// Horizontal line
//////////////////////////////////////////////////////////////////////
cHTMLHorizontalLine::cHTMLHorizontalLine(cHTMLDocument* doc)
: cHTMLElement(doc, "HR")
{
   _ClassName = "cHTMLHorizontalLine";

   Init();
}

cHTMLHorizontalLine::~cHTMLHorizontalLine()
{
}

void cHTMLHorizontalLine::Init()
{
	cHTMLElement::Init("HR");
}

//////////////////////////////////////////////////////////////////////
// Font
//////////////////////////////////////////////////////////////////////
cHTMLFont::cHTMLFont(cHTMLDocument* doc, QString face_value)
: cHTMLElement(doc, "FONT"), _FaceValue(face_value)
{
   _ClassName = "cHTMLFont";

   Init(face_value);
}

cHTMLFont::~cHTMLFont()
{
}

void cHTMLFont::Init(QString face_value)
{
    _FaceValue = face_value;

#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement("FONT");
    _Node.setAttribute("FACE", face_value);
#endif
}

//////////////////////////////////////////////////////////////////////
// TextField
//////////////////////////////////////////////////////////////////////
cHTMLTextField::cHTMLTextField(cHTMLDocument* doc, QString field_name, QString value, int len,  bool readonly)
: cHTMLElement(doc, "INPUT"), _FieldName(field_name), _Value(value), _ReadOnly(readonly), _Len(len)
{
    _ClassName = "cHTMLTextField";

	Init(field_name, value, readonly, len);
}

cHTMLTextField::~cHTMLTextField()
{
		
}

void cHTMLTextField::Init(QString field_name, QString value, int len, bool readonly)
{
	_FieldName = field_name;
	_Value = value;
	_ReadOnly = readonly;
	_Len = len;

#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( "INPUT" );
	_Node.setAttribute("TYPE", "text");
	_Node.setAttribute("NAME", _FieldName );
	_Node.setAttribute("VALUE", _Value );
	_Node.setAttribute("SIZE", QString::number(_Len));
	_Node.setAttribute("MAXLENGTH", QString::number(_Len));
	if(_ReadOnly) _Node.setAttribute("READONLY", "true");
#endif
}
//////////////////////////////////////////////////////////////////////
// Image
//////////////////////////////////////////////////////////////////////
cHTMLImage::cHTMLImage(cHTMLDocument* doc, QString file, QString alt)
: cHTMLElement(doc, "IMG"), _File(file)
{
    _ClassName = "cHTMLImage";

	Init(file, alt);
}

cHTMLImage::~cHTMLImage()
{
}

void cHTMLImage::Init(QString file, QString alt)
{
	_File = file;
#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( "IMG" );
	if(alt != "") _Node.setAttribute("ALT", alt);
	_Node.setAttribute("SRC", _File);
#endif
}
//////////////////////////////////////////////////////////////////////
// Table
//////////////////////////////////////////////////////////////////////
cHTMLTable::cHTMLTable(cHTMLDocument* doc)
: cHTMLElement(doc, "TABLE")
{
// PR 29.09.05 initialize when constructing
   _ClassName = "cHTMLTable";

   Init();
}

cHTMLTable::~cHTMLTable()
{
		
}

void cHTMLTable::Init()
{
	cHTMLElement::Init("TABLE");
}

//////////////////////////////////////////////////////////////////////
// cHTMLRow
//////////////////////////////////////////////////////////////////////
cHTMLRow::cHTMLRow(cHTMLDocument* doc, bool isHeadline)
: cHTMLElement(doc, "TR"), _IsHeadline(isHeadline)
{
    _ClassName = "cHTMLRow";

	Init(isHeadline);
}

cHTMLRow::~cHTMLRow()
{	
}

void cHTMLRow::Init(bool isHeadline)		
{ 
	_IsHeadline = isHeadline;
	_Node = _Document->CreateElement( "TR" );
}

void cHTMLRow::Add(QString text)
{
#ifdef DOM_INTERFACE_ENABLED
	QDomElement td = _Document->CreateElement( _IsHeadline ? "TH" : "TD" );
	_Node.appendChild(td);
	td.appendChild(_Document->CreateTextNode(text));
#endif
}

void cHTMLRow::Add(cHTMLElement element)
{
#ifdef DOM_INTERFACE_ENABLED
	QDomElement td = _Document->CreateElement( _IsHeadline ? "TH" : "TD" );
	_Node.appendChild(td);
	td.appendChild(element.Node());
#endif
}

void cHTMLRow::Add(QString text, QString alignment, QString class_name, QString colspan)
{
#ifdef DOM_INTERFACE_ENABLED
	QDomElement td = _Document->CreateElement( _IsHeadline ? "TH" : "TD" );
	if( alignment != "") td.setAttribute("ALIGN", alignment);
	if( class_name != "") td.setAttribute("CLASS", class_name);
	if( colspan != "") td.setAttribute("COLSPAN", colspan);
	_Node.appendChild(td);
	td.appendChild(_Document->CreateTextNode(text));
#endif
}

void cHTMLRow::Add(cHTMLElement element, QString alignment, QString class_name, QString colspan)
{
#ifdef DOM_INTERFACE_ENABLED
	QDomElement td = _Document->CreateElement( _IsHeadline ? "TH" : "TD" );
	if( alignment != "") td.setAttribute("ALIGN", alignment);
	if( class_name != "") td.setAttribute("CLASS", class_name);
	if( colspan != "") td.setAttribute("COLSPAN", colspan);
	_Node.appendChild(td);
	td.appendChild(element.Node());
#endif
}

//////////////////////////////////////////////////////////////////////
// StrRow
//////////////////////////////////////////////////////////////////////
/*cHTMLStrRow::cHTMLStrRow(cHTMLDocument* doc, QStringList data_list, bool isHeadline)
: cHTMLElement(doc, "TR")
{
	Init(data_list, isHeadline);
}

cHTMLStrRow::~cHTMLStrRow()
{
		
}

void cHTMLStrRow::Init(QStringList data_list, bool isHeadline)		
{ 
	_Node = _Document->CreateElement( "TR" );
	QStringList::iterator it = data_list.begin();
	while(it != data_list.end()){
		QString name;
		isHeadline ? name = "TH" : name = "TD";
		QDomElement td = _Document->CreateElement(name);
		_Node.appendChild(td);
		QDomText t = _Document->CreateTextNode((*it));
		td.appendChild(t);
		it++;
	}
 }
*/

//////////////////////////////////////////////////////////////////////
// HeadLine
//////////////////////////////////////////////////////////////////////
cHTMLHeadLine::cHTMLHeadLine(cHTMLDocument* doc, QString text,int order)
: cHTMLElement(doc, "H1"), _Text(text)
{
   _ClassName = "cHTMLHeadLine";

	Init(text, order);
}

cHTMLHeadLine::~cHTMLHeadLine()
{
}

void cHTMLHeadLine::Init(QString text, int order)
{
	QString tag = "H";
	tag += QString::number(order);

#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( tag );
	_Text = text;
	QDomText t = _Document->CreateTextNode(_Text);
	_Node.appendChild(t);
#endif
}

//////////////////////////////////////////////////////////////////////
// TableData
//////////////////////////////////////////////////////////////////////
/*cHTMLTableData::cHTMLTableData(cHTMLDocument* doc, bool isHeadline, QString align )
: cHTMLElement(doc, isHeadline ? "TH" : "TD")
{
// PR 29.09.05 right justified by default
//   Init(isHeadline);
	Init(isHeadline, "right");
}
cHTMLTableData::~cHTMLTableData()
{
}

void cHTMLTableData::Init(bool isHeadline, QString align)
{
	_Node = _Document->CreateElement( isHeadline ? "TH" : "TD" );
	_Node.setAttribute("ALIGN", align);
}
*/


//////////////////////////////////////////////////////////////////////
// Link
//////////////////////////////////////////////////////////////////////
cHTMLLink::cHTMLLink(cHTMLDocument* doc, QString target, QString text)
: cHTMLElement(doc, "A"), _Target(target), _Text(text)
{
    _ClassName = "cHTMLLink";

	Init(target, text);
}

cHTMLLink::~cHTMLLink()
{
}

void cHTMLLink::Init(QString target, QString text)
{
	_Target = target;
	_Text = text;

#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( "A" );
	_Node.setAttribute("HREF", _Target);
	QDomText t = _Document->CreateTextNode(_Text);
	_Node.appendChild(t);
#endif
}

//////////////////////////////////////////////////////////////////////
// Button
//////////////////////////////////////////////////////////////////////
cHTMLButton::cHTMLButton(cHTMLDocument* doc, QString caption)
: cHTMLElement(doc, "INPUT"), _Caption(caption)
{
   _ClassName = "cHTMLButton";
}

cHTMLButton::~cHTMLButton()
{
}

//////////////////////////////////////////////////////////////////////
// SubmitButton
//////////////////////////////////////////////////////////////////////
cHTMLSubmitButton::cHTMLSubmitButton(cHTMLDocument* doc, QString caption)
: cHTMLButton(doc, caption)
{
   _ClassName = "cHTMLSubmitButton";

	Init(caption);
}

cHTMLSubmitButton::~cHTMLSubmitButton()
{
}

void cHTMLSubmitButton::Init(QString caption)
{
	_Caption = caption;
#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( "INPUT" );
	_Node.setAttribute("TYPE", "submit");
	_Node.setAttribute("VALUE", _Caption);
#endif
}

//////////////////////////////////////////////////////////////////////
// ResetButton
//////////////////////////////////////////////////////////////////////
cHTMLResetButton::cHTMLResetButton(cHTMLDocument* doc, QString caption)
: cHTMLButton(doc, caption)
{
   _ClassName = "cHTMLResetButton";

	Init(caption);
}

cHTMLResetButton::~cHTMLResetButton()
{
}

void cHTMLResetButton::Init(QString caption)
{
	_Caption = caption;
#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( "INPUT" );
	_Node.setAttribute("TYPE", "reset");
	_Node.setAttribute("VALUE", _Caption);
#endif
}

//////////////////////////////////////////////////////////////////////
// cHTMLList
//////////////////////////////////////////////////////////////////////
cHTMLList::cHTMLList(cHTMLDocument* doc, bool ordered)
: cHTMLElement(doc, ordered ? "OL" : "UL"), _IsOrdered(ordered)
{
   _ClassName = "cHTMLList";

	Init(_IsOrdered);
}

cHTMLList::~cHTMLList()
{
}

void cHTMLList::Init(bool ordered)
{
	_IsOrdered = ordered;
#ifdef DOM_INTERFACE_ENABLED
	if(_IsOrdered) _Node = _Document->CreateElement( "OL" );
	else _Node = _Document->CreateElement( "UL" );
#endif
}

void cHTMLList::Add(QString text)
{
#ifdef DOM_INTERFACE_ENABLED
	QDomElement td = _Document->CreateElement("LI" );
	_Node.appendChild(td);
	td.appendChild(_Document->CreateTextNode(text));
#endif
}

void cHTMLList::Add(cHTMLElement element)
{
#ifdef DOM_INTERFACE_ENABLED
	QDomElement td = _Document->CreateElement( "LI");
	_Node.appendChild(td);
	td.appendChild(element.Node());
#endif

}

void cHTMLList::Add(cHTMLList element)
{
#ifdef DOM_INTERFACE_ENABLED
	cHTMLElement::Add(element);
#endif

}

//////////////////////////////////////////////////////////////////////
// cHTMLDiv
//////////////////////////////////////////////////////////////////////
cHTMLDiv::cHTMLDiv(cHTMLDocument* doc, QString className)
: cHTMLElement(doc, "DIV")
{
   _ClassName = "cHTMLDiv";

	Init(className);
}

cHTMLDiv::~cHTMLDiv()
{
}

void cHTMLDiv::Init(QString className)
{

#ifdef DOM_INTERFACE_ENABLED
	_Node = _Document->CreateElement( "DIV" );
	if(className != "") SetClassName(className);
#endif
}