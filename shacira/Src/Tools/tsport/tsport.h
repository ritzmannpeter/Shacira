
#ifndef _tsport_h_
#define _tsport_h_

#include <qstring.h>
#include <qdom.h>
#include <QDomImplementation>
#include <qfile.h>
#include <vector>
using namespace std;

class Message
{
public:
   Message(const QString & source, const QString & translation, bool utf8utf8Encoding = false);
   QString & source() {return _source;};
   QString & translation() {return _translation;};
   bool utf8Encoding() const {return _utf8Encoding;};
protected:
   QString _source;
   QString _translation;
   bool _utf8Encoding;
};
typedef vector<Message*> MESSAGE_VECTOR_T;

class Context
{
public:
   Context(const QString & name);
   void addMessage(Message * message);
   inline const MESSAGE_VECTOR_T & messageVector() const {return _messageVector;};
   inline const QString & name() const {return _name;};
protected:
   MESSAGE_VECTOR_T _messageVector;
   QString _name;
};
typedef vector<Context*> CONTEXT_VECTOR_T;

class TSPort
{
public:
   TSPort();
   virtual ~TSPort();
   void analyze(const QString & inputFile);
   void generate(const QString & outputFile = QString());
   inline const CONTEXT_VECTOR_T & contextVector() const {return _contextVector;};
protected:
   CONTEXT_VECTOR_T _contextVector;
protected:
   void addContext(Context * context);
   void generateContext(QDomDocument & document, QDomElement & parent, Context * context);
   void generateMessage(QDomDocument & document, QDomElement & parent, Message * message);
   void addMessages(const QDomNode & node, Context * context);
   QString getContextName(const QDomNode & node) const;
   QString getSource(const QDomNode & node) const;
   QString getTranslation(const QDomNode & node) const;
   QString getNodeValue(const QDomNode node) const;
   void setNodeValue(QDomDocument & document, QDomNode & node, QString value);
};

#endif // _tsport_h_
