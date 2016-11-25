
#ifndef _uitrans_h_
#define _uitrans_h_

#include <qfile.h>
#include <qstring.h>
#include <qvariant.h>
#include "replacement.h"
#include <list>
using namespace std;

class DerivedForm
{
public:
   DerivedForm(const QString & baseName, const QString & className, const QString & baseClassName, const QString & uiClassName)
      : _baseName(baseName),
        _className(className),
        _baseClassName(baseClassName),
        _uiClassName(uiClassName)
   {
   };
   QString _baseName;
   QString _className;
   QString _baseClassName;
   QString _uiClassName;
};
typedef map<QString,DerivedForm*> DERIVED_FORM_MAP_T;

class PortingFile;

#define CPP                     0x00000001
#define PROJECT                 0x00000002
#define FILTER                  0x00000004
#define WIDGET_IMPL             0x00000008
#define WIDGET_HEADER           0x00000010
#define PP                      0x00000020

typedef list<Replacement*> REPLACEMENT_LIST_T;

class UiTrans
{
public:
   UiTrans();
   virtual ~UiTrans();
   bool transform(PortingFile * file);
   bool adjustProject(PortingFile * file);
protected:
   QString replaceAll(const QString & s, const QString &s1, const QString & s2, Qt::CaseSensitivity sensitivity = Qt::CaseSensitive) const;
   QString replaceLine(bool & changed, const QString line, QStringList & commentList) const;
   QString replace(bool & changed, const QString & line, const QString & word, const QString & substitution, Qt::CaseSensitivity sensitivity = Qt::CaseSensitive) const;
   QString removeLine(bool & changed, const QString & line, const QString & word, Qt::CaseSensitivity sensitivity) const;
   bool hasSuspiciousConstStringMacro(const QString & line) const;
   bool postReplacement(PortingFile * file);
   static void addReplacement(unsigned int categories, unsigned int flags, const QString & expression, const QString & replacement);
   static void addReplacement(unsigned int categories, unsigned int flags, const QString & text, const QString & replacement, Qt::CaseSensitivity sensitivity);
   static void addReplacement(unsigned int categories, unsigned int flags, const QString & text, Qt::CaseSensitivity sensitivity);
   static void addReplacements();
   static void addDerivedForm(const QString & baseName, const QString & baseClass, const QString & className, const QString & uiClassName);
   DerivedForm * derivedForm(const QString & baseName) const;
   static void addDerivedForms();
protected:
   PortingFile * _currentFile;
   static REPLACEMENT_LIST_T _replacementList;
   static DERIVED_FORM_MAP_T _derivedFormMap;
};

#include <string>
using namespace std;

string logFileName();
string errorFileName();
void LogPrintf(const string & logFile, const char * fmt_str, ...);

#endif // _uitrans_h_
