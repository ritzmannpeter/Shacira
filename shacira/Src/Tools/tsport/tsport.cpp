
#include "tsport.h"
#include <qtextstream.h>
#include <iostream>
#include <fstream>
using namespace std;

Message::Message(const QString & source, const QString & translation, bool utf8Encoding)
   : _source(source), _translation(translation), _utf8Encoding(utf8Encoding)
{
}


Context::Context(const QString & name)
   : _name(name)
{
}

void Context::addMessage(Message * message)
{
   int index = _messageVector.size();
   _messageVector.resize(index + 1);
   _messageVector[index] = message;
}

   
TSPort::TSPort()
{
}

TSPort::~TSPort()
{
}

void TSPort::analyze(const QString & inputFile)
{
   QDomDocument document;
   QString errorMsg;
   int errorLine = 0;
   int errorColumn = 0;
   QFile xmlFile(inputFile);
   bool success = document.setContent(&xmlFile, false, &errorMsg, &errorLine, &errorColumn);
   if (success) {
      Context * currentContext = NULL;
      QDomElement documentElement = document.documentElement();
      QDomNodeList nodeList = documentElement.childNodes();
      int nodeCount = nodeList.count();
      int i = 0;
      for (i=0; i<nodeCount; i++) {
         QDomNode node = nodeList.item(i);
         QDomNode::NodeType nodeType = node.nodeType();
         if (nodeType == QDomNode::ElementNode) {
            QDomElement child = node.toElement();
            QString tagName = child.tagName();
            if (tagName == "context") {
               QString contextName = getContextName(child);
               if (contextName.isEmpty()) {
               } else {
                  currentContext = new Context(contextName);
                  addContext(currentContext);
                  addMessages(child, currentContext);
               }
            }
         }
      }
   }
}

void TSPort::generate(const QString & outputFile)
{
   QDomImplementation domImpl;
   QDomDocumentType docType = domImpl.createDocumentType("TS1", "TS2", "TS3");
//   QDomDocument document(docType);
   QDomDocument document("TS");
   QDomElement documentElement = document.createElement("TS");
   document.appendChild(documentElement);
   // ...
   const CONTEXT_VECTOR_T & v = contextVector();
   CONTEXT_VECTOR_T::const_iterator i = v.begin();
   while (i != v.end()) {
      Context * context = (*i);
static bool done = false;
if (done) {
   break;
}
      generateContext(document, documentElement, context);
//done = true;
      i++;
   }
   QString xmlData = document.toString();
   if (outputFile.isEmpty()) {
      cout << xmlData.toStdString();
   } else {
      QFile f(outputFile);
      if (f.open(QIODevice::WriteOnly|QIODevice::Text)) {
         QTextStream textStream(&f);
         textStream << xmlData;
      }
   }
}

void TSPort::addContext(Context * context)
{
   int index = _contextVector.size();
   _contextVector.resize(index + 1);
   _contextVector[index] = context;
}

void TSPort::generateContext(QDomDocument & document, QDomElement & parent, Context * context)
{
cout << context->name().toStdString() << endl;
   QDomElement contextElement = document.createElement("context");
   parent.appendChild(contextElement);
   QDomElement nameElement = document.createElement("name");
   setNodeValue(document, nameElement, context->name());
   contextElement.appendChild(nameElement);
   const MESSAGE_VECTOR_T & v = context->messageVector();
   MESSAGE_VECTOR_T::const_iterator i = v.begin();
   while (i != v.end()) {
      Message * message = (*i);
      generateMessage(document, contextElement, message);
      i++;
   }
}

void TSPort::generateMessage(QDomDocument & document, QDomElement & parent, Message * message)
{
   QDomElement messageElement = document.createElement("message");
   parent.appendChild(messageElement);
   QDomElement sourceElement = document.createElement("source");
   setNodeValue(document, sourceElement, message->source().toUtf8());
   messageElement.appendChild(sourceElement);
   QDomElement translationElement = document.createElement("translation");
   setNodeValue(document, translationElement, message->translation().toUtf8());
   messageElement.appendChild(translationElement);
   if (message->utf8Encoding()) {
      messageElement.setAttribute("encoding", "UTF-8");
   }
}

void TSPort::addMessages(const QDomNode & node, Context * context)
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "message") {
            QString source = getSource(child);
            QString translation = getTranslation(child);
            bool utf8Encoding = false;
            QString utf8Attribute = child.attribute("utf8");
            if (!utf8Attribute.isEmpty()) {
               utf8Encoding = true;
            }
            Message * message = new Message(source, translation, utf8Encoding);
            context->addMessage(message);
         }
      }
   }
}

QString TSPort::getContextName(const QDomNode & node) const
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "name") {
            QString contextName = getNodeValue(child);
            return contextName;
         }
      }
   }
   return QString();
}

QString TSPort::getSource(const QDomNode & node) const
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "source") {
            QString source = getNodeValue(child);
            return source;
         }
      }
   }
   return QString();
}

QString TSPort::getTranslation(const QDomNode & node) const
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "translation") {
            QString translation = getNodeValue(child);
            return translation;
         }
      }
   }
   return QString();
}

QString TSPort::getNodeValue(const QDomNode node) const
{
   QString value;
   QDomNodeList children = node.childNodes();
   int child_count = children.count();
   if (child_count > 0) {
      int i = 0;
      for (i=0; i<child_count; i++) {
         QDomNode node = children.item(i);
         QString nodeName = node.nodeName();
         if (nodeName == "#text") {
            value = node.nodeValue();
         } else if (nodeName == "#cdata-section") {
            value = node.nodeValue();
         }
      }
   }
   return value;
}

void TSPort::setNodeValue(QDomDocument & document, QDomNode & node, QString value)
{
   QDomNodeList children = node.childNodes();
   int child_count = children.count();
   if (child_count == 0) {
      QDomText textNode = document.createTextNode(value);
//      textNode.setNodeValue(value);
      node.appendChild(textNode);
   } else {
      int i = 0;
      for (i=0; i<child_count; i++) {
         QDomNode node = children.item(i);
         QString nodeName = node.nodeName();
         if (nodeName ==  "#text") {
            node.setNodeValue(value);
         } else if (nodeName ==  "#cdata-section") {
            node.setNodeValue(value);
         }
      }
   }
}


