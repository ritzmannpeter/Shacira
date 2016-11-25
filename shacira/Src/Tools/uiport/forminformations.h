
#ifndef _forminformations_h_
#define _forminformations_h_

#include <qstring.h>
#include <map>
using namespace std;

class FormInformation
{
public:
   FormInformation()
   {
   };
   FormInformation(const FormInformation & right)
      : _path(right._path),
        _formClass(right._formClass),
        _baseClass(right._baseClass),
        _uiClassName(right._uiClassName),
        _classCode(right._classCode)
   {
   };
   FormInformation(const QString & path, const QString & formClass, const QString & baseClass, const QString & uiClassName, const QString & classCode)
      : _path(path),
        _formClass(formClass),
        _baseClass(baseClass),
        _uiClassName(uiClassName),
        _classCode(classCode)
   {
   };
   virtual ~FormInformation()
   {
   };
   QString _path;
   QString _formClass;
   QString _baseClass;
   QString _uiClassName;
   QString _classCode;
};

typedef map<QString,FormInformation> FORM_INFORMATION_MAP_T;

class FormInformations
{
public:
   FormInformations();
   virtual ~FormInformations();
   void addFormInfo(const QString & path, const QString & formClass, const QString & baseClass, const QString & uiClassName, const QString & classCode);
   void printHeaderInformations(const QString & destinationPath);
private:
   void printSingleHeaders(const QString & destinationPath);
   void printCode(const QString & directory, const QString & fileName, const QString & code);
   void printCode(const QString & path, const QString & code);
   FORM_INFORMATION_MAP_T _formInformationMap;
};

#endif // _imageinformation_h_
