
#include "forminformations.h"
#include <qfile.h>

FormInformations::FormInformations()
{
}

FormInformations::~FormInformations()
{
}

void FormInformations::addFormInfo(const QString & path, const QString & formClass, const QString & baseClass, const QString & uiClassName, const QString & classCode)
{
   FormInformation formInformation(path, formClass, baseClass, uiClassName, classCode);
   _formInformationMap[path] = formInformation;
}

void FormInformations::printHeaderInformations(const QString & destinationPath)
{
   printSingleHeaders(destinationPath);
}

void FormInformations::printSingleHeaders(const QString & destinationPath)
{
   FORM_INFORMATION_MAP_T::const_iterator i = _formInformationMap.cbegin();
   while (i != _formInformationMap.cend()) {
      FormInformation formInfo = (*i).second;
      QString outputFile = formInfo._path.replace("ui", "h");
      QString code;
      code += "#ifndef _" + formInfo._formClass.toLower() + "_h_\r\n";
      code += "#define _" + formInfo._formClass.toLower() + "_h_\r\n";
      code += "#include \"" + formInfo._baseClass.toLower() + ".h\"\r\n";
      code += formInfo._classCode;
      code += "#endif\r\n";
      printCode(outputFile, code);
      i++;
   }
}

void FormInformations::printCode(const QString & directory, const QString & fileName, const QString & code)
{
   QString path = directory + "/" + fileName + ".h";
   printCode(path, code);
}

void FormInformations::printCode(const QString & path, const QString & code)
{
   QFile file(path);
   file.open(QIODevice::WriteOnly);
   if (file.isOpen()) {
      file.write(code.toStdString().c_str());
      file.close();
   }
}


