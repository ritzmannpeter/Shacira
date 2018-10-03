
#include "uitrans.h"
#include "options.h"
#include <qdatastream.h>
#include <qtextstream.h>
#include <iostream>
#include "portingfile.h"
#include "portingapplication.h"

REPLACEMENT_LIST_T UiTrans::_replacementList;
DERIVED_FORM_MAP_T UiTrans::_derivedFormMap;

UiTrans::UiTrans() : _currentFile(NULL)
{
   addDerivedForms();
   addReplacements();
}

UiTrans::~UiTrans()
{
}

bool UiTrans::transform(PortingFile * file)
{
#define test_itx
#ifdef test_it
Replacement r0(0, "insertItem(%0)" , "insertItem(428,%0)");
Replacement r1(0, "insertItem(%0,%1)" , "insertItem(%1,%0)");
Replacement r2(0, "id(%0)" , "indexOf(%0)");
Replacement r4(WORD_ONLY, "QObjectListIterator" , "QObjectList::const_iterator", Qt::CaseSensitive);
//Replacement r5(WORD_ONLY, "find" , "indexOf", Qt::CaseSensitive);
Replacement r5(WORD_ONLY, "setLength" , "resize", Qt::CaseSensitive);
Replacement r6(WORD_ONLY, "Qt::WStyle_Customize" , "WStyle_Customize", Qt::CaseSensitive);
Replacement r7(WORD_ONLY, "QWidgetStack" , "QStackedWidget", Qt::CaseSensitive);
QString test0 = "insertItem( tr( \"Off\") );";
QString test1 = "insertItem( tr( \"Off\") , 555);";
QString test2 = "      QWidget* page0 = Clp_StackTurnParamWizard->page(0);    ";
QString test3 = "        if(DoubleStackTurn && (stack->id(stack->visibleWidget()) != 1))";
QString test4 = "                QObjectListIterator iter(*pObjectList);";
QString test5 = "         data.find(END_OF_LINE);   x.setLength(22)";
QString test6 = "    this->SetWFlags(Qt::WStyle_Customize|Qt::WStyle_NormalBorder|Qt::WStyle_Title); ";
QString test7 = "            QWidgetStack* qWStack = static_cast<QWidgetStack*>(_AppFrame->child(\"MosaicFrameDateTimeWidgetStack\"));       bool changed = false;   ";
bool changed = false;
//QString test0_ = r0.replace(test0, changed);
//QString test1_ = r1.replace(test1, changed);
//QString test2_ = r2.replace(test2, changed);
//QString test3_ = r2.replace(test3, changed);
//QString test4_ = r4.replace(test4, changed);
//QString test5_ = r5.replace(test5, changed);
//QString test6_ = test6;
//REPLACEMENT_LIST_T::const_iterator i = _cppReplacementList.constBegin();
//while (i != _cppReplacementList.constEnd()) {
//   Replacement * replacement = (*i);
//   test6_ = replacement->replace(test6_, changed);
//   i++;
//}
QString test7_ = r7.replace(test7, changed);
return true;
#endif
   _currentFile = file;
   QString inputFile = file->sourcePath();
   QString outputFile = file->destinationPath();
   cout << file->name().toStdString() << "." << file->extension().toStdString() << " ..." << endl;
   LogPrintf(logFileName(), "porting from %s to %s\n", inputFile.toStdString().c_str(), outputFile.toStdString().c_str());
   QFile qInputFile(inputFile);
   qInputFile.open(QIODevice::ReadOnly);
   if (qInputFile.isOpen()) {
      bool changed = false;
      QString content;
      QTextStream inputStream(&qInputFile);
      QFile qOutputFile(outputFile);
      QTextStream tempStream(&content);
      while (!inputStream.atEnd()) {
         QString line = inputStream.readLine();
         QStringList commentList;
         QString newLine = replaceLine(changed, line, commentList);
         if (inputStream.atEnd()) {
            tempStream << newLine << "\r\n";
         } else {
            tempStream << newLine << "\r\n";
         }
         if (!commentList.isEmpty()) {
            QStringList::const_iterator i = commentList.constBegin();
            while (i != commentList.constEnd()) {
               tempStream << (*i) << "\r\n";
               i++;
            }
         }
      }
      qInputFile.close();
      if (changed) {
         QFileInfo fileInfo(outputFile);
         QDir directory = fileInfo.absoluteDir();
         QString directoryPath = directory.absolutePath();
         directory.mkpath(directoryPath);
         QFile qOutputFile(outputFile);
         qOutputFile.open(QIODevice::WriteOnly);
         if (qOutputFile.isOpen()) {
            QTextStream outputStream(&qOutputFile);
            outputStream << content;
            qOutputFile.close();
         }
      }
   }
   return postReplacement(file);
}

#ifdef doku
  <PropertyGroup Label="Globals">
    <ProjectGuid>{7F570B2A-0402-40FE-85F1-D138E77079CE}</ProjectGuid>
    <RootNamespace>MosaicCommon</RootNamespace>
    <Keyword>Qt4VSv1.0</Keyword>
  </PropertyGroup>

  <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="PropertySheets">
    <Import Project="..\..\Shacira\Targ\vc10\q4_lib_release.props" />
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform">
    </Import>
  </ImportGroup>
 
#endif

bool UiTrans::adjustProject(PortingFile * file)
{
   _currentFile = file;
   QString inputFile = file->sourcePath();
   QString outputFile = file->destinationPath();
   cout << file->name().toStdString() << "." << file->extension().toStdString() << " ..." << endl;
   LogPrintf(logFileName(), "adjusting %s to %s\n", inputFile.toStdString().c_str(), outputFile.toStdString().c_str());
   QFile qInputFile(inputFile);
   qInputFile.open(QIODevice::ReadOnly);
   if (qInputFile.isOpen()) {
      bool changed = false;
      bool alreadyProcessed = false;
      QString content;
      QTextStream inputStream(&qInputFile);
      QFile qOutputFile(outputFile);
      QTextStream tempStream(&content);
      bool inGlobalsSection = false;
      while (!inputStream.atEnd()) {
         int pos = 0;
         QString line = inputStream.readLine();
         if (line.indexOf("Qt4VSv1.0") >= 0) {
            alreadyProcessed = true;
         }
         if (!alreadyProcessed && inGlobalsSection) {
            pos = line.indexOf("</PropertyGroup>");
            if (pos >= 0) {
               inGlobalsSection = false;
               tempStream << "    <Keyword>Qt4VSv1.0</Keyword>" << "\r\n";
               changed = true;
            }
         }
         pos = line.indexOf("<PropertyGroup Label=\"Globals\">");
         if (pos >= 0) {
            inGlobalsSection = true;
         }
         QStringList commentList;
         QString newLine = replaceLine(changed, line, commentList);
         if (inputStream.atEnd()) {
            tempStream << newLine << "\r\n";
         } else {
            tempStream << newLine << "\r\n";
         }
      }
      qInputFile.close();
      if (changed) {
         QFileInfo fileInfo(outputFile);
         QDir directory = fileInfo.absoluteDir();
         QString directoryPath = directory.absolutePath();
         directory.mkpath(directoryPath);
         QFile qOutputFile(outputFile);
         qOutputFile.open(QIODevice::WriteOnly);
         if (qOutputFile.isOpen()) {
            QTextStream outputStream(&qOutputFile);
            outputStream << content;
            qOutputFile.close();
         }
      }
   }
   return false;
}

QString UiTrans::replaceAll(const QString & s, const QString &s1, const QString & s2, Qt::CaseSensitivity sensitivity) const
{
   QString newValue = s;
   int position = newValue.indexOf(s1, 0, sensitivity);
   while (position >= 0) {
      newValue.replace(position, s1.length(), s2);
      position = newValue.indexOf(s1, 0, sensitivity);
   }
   return newValue;
}

QString UiTrans::replaceLine(bool & changed, const QString line, QStringList & commentList) const
{
   QString newLine = line;
   if (_currentFile->isCppCode()) {
      REPLACEMENT_LIST_T::const_iterator i = _replacementList.cbegin();
      while (i != _replacementList.cend()) {
         Replacement * replacement = (*i);
         if (replacement->applicable(CPP)) {
            newLine = replacement->replace(newLine, changed);
         }
         i++;
      }
      if (hasSuspiciousConstStringMacro(newLine)) {
         commentList << "#pragma message(__LOC__ \"this is a suspicious usage of macro CONST_STRING()\")";
         changed = true;
      }
   }
   if (_currentFile->isWidgetImplementation()) {
      REPLACEMENT_LIST_T::const_iterator i = _replacementList.begin();
      while (i != _replacementList.cend()) {
         Replacement * replacement = (*i);
         if (replacement->applicable(WIDGET_IMPL)) {
            newLine = replacement->replace(newLine, changed);
         }
         i++;
      }
   }
   if (_currentFile->isProjectFile() ||
       _currentFile->isProjectFilter()) {
      REPLACEMENT_LIST_T::const_iterator i = _replacementList.begin();
      while (i != _replacementList.cend()) {
         Replacement * replacement = (*i);
         if (replacement->applicable(PROJECT|FILTER)) {
            newLine = replacement->replace(newLine, changed);
         }
         i++;
      }
   }
   return newLine;
}

QString UiTrans::replace(bool & changed, const QString & line, const QString & word, const QString & substitution, Qt::CaseSensitivity sensitivity) const
{
   int pos = line.indexOf(word, 0, sensitivity);
   if (pos >= 0) {
      changed = true;
      QString newLine = replaceAll(line, word, substitution, sensitivity);
      return newLine;
   } else {
      return line;
   }
}

QString UiTrans::removeLine(bool & changed, const QString & line, const QString & word, Qt::CaseSensitivity sensitivity) const
{
   int pos = line.indexOf(word, 0, sensitivity);
   if (pos >= 0) {
      changed = true;
      return QString();
   } else {
      return line;
   }
}


bool UiTrans::hasSuspiciousConstStringMacro(const QString & line) const
{
   int pos = line.indexOf("CONST_STRING(");
   if (pos > 0) {
      int i = 0;
      for (i=pos-1; i>0; i--) {
         char c1 = line[i].toLatin1();
         char c0 = 0;
         if (c1 != ' ' &&
             c1 != '\t') {
            if (c1 == '=') {
               if (i > 0) {
                  c0 = line[i-1].toLatin1();
               }
               if (c0 != '=') {
                  return true;
               } else {
                  return false;
               }
            } else {
               return false;
            }
         }
      }
   }
   return false;
}

bool UiTrans::postReplacement(PortingFile * file)
{
   // handles reimplemented form classes
   QString baseName = file->baseName().toLower();
   QString extension = file->extension();
   QString fileName = baseName + "." + extension;
   DerivedForm * derivedForm = this->derivedForm(baseName);
   if (derivedForm != NULL) {
      QString className = derivedForm->_className;
      QString baseClassName = derivedForm->_baseClassName;
      QString uiClassName = derivedForm->_uiClassName;
      QString legacyClassName = uiClassName.right(uiClassName.length() - 3);
      QString inputFile = file->destinationPath();
      if (!QFile(inputFile).exists()) {
         inputFile = file->sourcePath();
      }
      QString outputFile = file->destinationPath();
      cout << file->name().toStdString() << "." << file->extension().toStdString() << " ..." << endl;
      LogPrintf(logFileName(), "adjusting %s to %s\n", inputFile.toStdString().c_str(), outputFile.toStdString().c_str());
      QFile qInputFile(inputFile);
      qInputFile.open(QIODevice::ReadOnly);
      if (qInputFile.isOpen()) {
         bool changed = false;
         QString content;
         QTextStream inputStream(&qInputFile);
         QFile qOutputFile(outputFile);
         QTextStream tempStream(&content);
         while (!inputStream.atEnd()) {
            bool lineChanged = false;
            int pos = 0;
            QString line = inputStream.readLine();
            if (extension == "h") {
               QString legacyIncludeFile = legacyClassName.toLower() + ".h";;
               QString includeFile = uiClassName.toLower() + ".h";
               pos = line.indexOf("#include");
               if (pos >= 0) {
                  int start = line.indexOf("\"");
                  int end = line.lastIndexOf("\"");
                  if (end > 0 && start > 0 && end > start) {
                     start++;
                     QString cmpIncludeFile = line. mid(start, end - start);
                     if (cmpIncludeFile == legacyIncludeFile) {
                        tempStream << "#include \"" << baseClassName.toLower() << ".h\"" << "\r\n";
                        tempStream << "#include " << "\"" << includeFile << "\"" << "\r\n";
                        lineChanged = true;
                     }
                  }
               }
               int pos1 = line.indexOf("class");
               int pos2 = line.indexOf("public");
               if (pos1 >= 0 && pos2 >= 0) {
                  int pos3 = line.indexOf(":");
                  if (pos3 >= 0) {
                     int nameStart = pos1 + 6;
                     int nameLength = pos3 - nameStart;
                     QString cmpClassName = line.mid(nameStart, nameLength);
                     cmpClassName = cmpClassName.trimmed();
                     if (cmpClassName == className) {
                        tempStream << "class " << className << " : public " << baseClassName << "<" << uiClassName  << ">" << "\r\n";
                        lineChanged = true;
                     }
                  }
               }
               QString searchString = legacyClassName + '(';
               pos = line.indexOf(searchString);
               if (pos >= 0) {
                  if (pos > 1 && !isalnum(line[pos-1].toLatin1())) {
                     QString replacement = baseClassName + "<" + uiClassName + ">(";
                     QString newLine = replace(lineChanged, line, searchString, replacement, Qt::CaseSensitive);
                     tempStream << newLine << "\r\n";
                  }
               }
            } else if (extension == "cpp") {
               QString searchString = legacyClassName + '(';
               pos = line.indexOf(searchString);
               if (pos >= 0) {
                  if (pos >= 0 && !isalnum(line[pos-1].toLatin1())) {
                     QString replacement = baseClassName + "<" + uiClassName + ">(";
                     QString newLine = replace(lineChanged, line, searchString, replacement, Qt::CaseSensitive);
                     tempStream << newLine << "\r\n";
                  }
               }
            }
            if (lineChanged) {
               changed = true;
            } else {
               tempStream << line << "\r\n";
            }
         }
         qInputFile.close();
         if (changed) {
            QFileInfo fileInfo(outputFile);
            QDir directory = fileInfo.absoluteDir();
            QString directoryPath = directory.absolutePath();
            directory.mkpath(directoryPath);
            QFile qOutputFile(outputFile);
            qOutputFile.open(QIODevice::WriteOnly);
            if (qOutputFile.isOpen()) {
               QTextStream outputStream(&qOutputFile);
               outputStream << content;
               qOutputFile.close();
            }
         }
      }
   }
adjustProject(file);   
   return true;
}

void UiTrans::addReplacement(unsigned int categories, unsigned int flags, const QString & expression, const QString & replacement)
{
   Replacement * rep = new Replacement(categories, flags, expression, replacement);
   _replacementList.push_back(rep);
}

void UiTrans::addReplacement(unsigned int categories, unsigned int flags, const QString & text, const QString & replacement, Qt::CaseSensitivity sensitivity)
{
   Replacement * rep = new Replacement(categories, flags, text, replacement, sensitivity);
   _replacementList.push_back(rep);
}

void UiTrans::addReplacement(unsigned int categories, unsigned int flags, const QString & text, Qt::CaseSensitivity sensitivity)
{
   Replacement * rep = new Replacement(categories, flags, text, sensitivity);
   _replacementList.push_back(rep);
}

void UiTrans::addReplacements()
{
   // list of textual replacements
   addReplacement(CPP, 0, "qpopupmenu.h", "qmenu.h", Qt::CaseInsensitive);
   addReplacement(CPP, WORD_ONLY, "QPopupMenu", "QMenu", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "simplifyWhiteSpace", "simplified", Qt::CaseSensitive);



   addReplacement(CPP, 0, "Qt::WFlags", "Qt::WindowFlags", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "WFlags", "Qt::WindowFlags", Qt::CaseSensitive);
//   addReplacement(CPP, 0, ".ascii()", ".toAscii()", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".latin1()", ".toLatin1()", Qt::CaseSensitive);
   addReplacement(CPP, 0, "#include <qsimplerichtext.h>", "#include <qimagewriter.h>\r\n#include <qtextdocument.h>\r\n#include <qabstracttextdocumentlayout.h>", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "qbutton.h", "qabstractbutton.h", Qt::CaseInsensitive);
   addReplacement(CPP, WORD_ONLY, "QButton", "QAbstractButton", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".upper()", ".toUpper()", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".lower()", ".toLower()", Qt::CaseSensitive);
   addReplacement(CPP, 0, "PROPERTY_2i(QCString", "PROPERTY_2i(QByteArray", Qt::CaseSensitive);
   addReplacement(CPP, 0, "QCString", "QString", Qt::CaseSensitive);
   addReplacement(CPP, 0, "qlistview.h", "listview.h", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "QListView", "ListView", Qt::CaseSensitive);
   addReplacement(CPP, 0, "QListViewItem", "ListViewItem", Qt::CaseSensitive);
   addReplacement(CPP, 0, "QListViewItemIterator", "ListViewItemIterator", Qt::CaseSensitive);
   addReplacement(CPP, 0, "qvaluevector.h", "qvector.h", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "QValueVector", "QVector", Qt::CaseSensitive);
   addReplacement(CPP, 0, "qptrlist.h", "qlist.h", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "qstrlist.h", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "QPtrListIterator<%0>" , "QList<%0*>::const_iterator");
   addReplacement(CPP, 0, "QPtrList<%0>" , "QList<%0*>");
   addReplacement(CPP, 0, "QIconSet(qembed_findImage(%0))" , "ICON_SET(%0)");
   addReplacement(CPP, 0, "insertItem(%0,%1)" , "insertItem(%1,%0)");
   addReplacement(CPP, 0, "insertItem(%0)" , "insertItem(INT_MAX,%0)");
   addReplacement(CPP, 0, "cqtpluginregistry.h", "pluginfactory.h", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "plugin_icons.h", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "<private/qrichtext_p.h>", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "<private/qinternal_p.h>", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "default_icon.h", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "embedded_images.h", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "painter.begin(%0,%1)" , "painter.begin(%0)");
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "white" , "Qt::white", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "red" , "Qt::red", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "blue" , "Qt::blue", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "green" , "Qt::green", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "yellow" , "Qt::yellow", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "black" , "Qt::black", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "gray" , "Qt::gray", Qt::CaseSensitive);
   addReplacement(CPP, 0, "Qt::AlignmentFlags" , "Qt::Alignment", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "AlignmentFlags" , "Qt::Alignment", Qt::CaseSensitive);
   addReplacement(CPP, 0, "qscrollview.h", "qscrollarea.h", Qt::CaseInsensitive);
   addReplacement(CPP, WORD_ONLY, "QScrollView" , "QScrollArea", Qt::CaseSensitive);
   addReplacement(CPP, 0, "qwidgetstack.h", "qstackedwidget.h", Qt::CaseInsensitive);
   addReplacement(CPP, WORD_ONLY, "QWidgetStack" , "QStackedWidget", Qt::CaseSensitive);
   addReplacement(CPP, 0, "<qheader.h>", "\"headerview.h\"", Qt::CaseInsensitive);
   addReplacement(CPP, WORD_ONLY, "QHeader" , "HeaderView", Qt::CaseSensitive);
   addReplacement(CPP, 0, "<qrangecontrol.h>", "\"cslider.h\"", Qt::CaseInsensitive);
   addReplacement(CPP, WORD_ONLY, "QRangeControl" , "CSlider", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".stripWhiteSpace()" , ".trimmed()", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".fromUcs2" , ".fromUtf16", Qt::CaseSensitive);
   addReplacement(CPP, 0, "::fromUcs2" , "::fromUtf16", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "findRev" , "lastIndexOf", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "find" , "indexOf", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".utf8()" , ".toUtf8()", Qt::CaseSensitive);
   addReplacement(PROJECT|FILTER, WORD_ONLY, "QT3Framework" , "QT4Framework", Qt::CaseInsensitive);
   addReplacement(CPP, 0, ".utf8()" , ".toUtf8()", Qt::CaseSensitive);
   addReplacement(CPP, 0, "ListViewItem::paintCell(%0,%1,%2,%3,%4)", "ListViewItem::paintCell(painter, option, index)");
   addReplacement(CPP, 0, "paintCell(%0,%1,%2,%3,%4)", "paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)");
   addReplacement(CPP, 0, "setCaption" , "setWindowTitle", Qt::CaseSensitive);
   addReplacement(CPP, 0, "public CFrame, public CSlider" , "public CSlider", Qt::CaseSensitive);
   addReplacement(CPP, 0, "const QObjectList *" , "const QObjectList ", Qt::CaseSensitive);
   addReplacement(CPP, 0, "const QObjectList*" , "const QObjectList ", Qt::CaseSensitive);
   addReplacement(CPP, 0, "QObjectList *" , "QObjectList ", Qt::CaseSensitive);
   addReplacement(CPP, 0, "QObjectList*" , "QObjectList ", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "QObjectListIterator" , "QObjectList::const_iterator", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "QObjectListIt" , "QObjectList::const_iterator", Qt::CaseSensitive);
   addReplacement(CPP, 0, "QPointArray" , "QPolygon", Qt::CaseSensitive);
   addReplacement(CPP, 0, "scale(%0,%1)" , "scaled(%0,%1)");
   addReplacement(CPP, 0, "smoothScale" , "scaled", Qt::CaseSensitive);
   addReplacement(CPP, 0, "moveBy(%0,%1)" , "translate(%0,%1)");
   addReplacement(CPP, 0, "bitBlt(%0,%1,%2,%3)" , "QPainter painter(this);\r\n   painter.drawImage(%1,%2, _DoubleBuffer.toImage())");
// stack adaptions
   addReplacement(CPP, 0, "raiseWidget(%0)" , "setCurrentIndex(%0)");
//   addReplacement(CPP, 0, "id(%0)" , "indexOf(%0)");
   addReplacement(CPP, 0, "visibleWidget()" , "currentWidget()", Qt::CaseSensitive);
   addReplacement(CPP, 0, "QWMatrix" , "QMatrix", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "QMAX" , "qMax", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "QMIN" , "qMin", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "QABS" , "qAbs", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "FALSE" , "false", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "TRUE" , "true", Qt::CaseSensitive);
   addReplacement(CPP, 0, "<qvbox.h>", Qt::CaseInsensitive);
   addReplacement(CPP, 0, "<qhbox.h>", Qt::CaseInsensitive);
   addReplacement(CPP, WORD_ONLY, "setToggleButton" , "setCheckable", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "setOn" , "setChecked", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "minValue" , "minimum", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "maxValue" , "maximum", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "setMinValue" , "setMinimum", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "setMaxValue" , "setMaximum", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "setNameFilter" , "setNameFilters", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "IO_ReadOnly" , "QIODevice::ReadOnly", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "IO_WriteOnly" , "QIODevice::WriteOnly", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "IO_Append" , "QIODevice::Append", Qt::CaseSensitive);
//   addReplacement(CPP, 0, "setEncoding(%0)" , "setAutoDetectUnicode(true)");
   addReplacement(CPP, 0, ".grep" , ".filter", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".setLength" , ".resize", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".writeBlock" , ".write", Qt::CaseSensitive);
   addReplacement(CPP, 0, ".readBlock" , ".read", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "setIconSet" , "setIcon", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "QIconSet" , "QIcon", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_Customize" , "WStyle_Customize", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_NormalBorder" , "WStyle_NormalBorder", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_Title" , "WStyle_Title", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_DialogBorder" , "WStyle_DialogBorder", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_NoBorder" , "WStyle_NoBorder", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_NoBorderEx" , "WStyle_NoBorderEx", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_SysMenu" , "WStyle_SysMenu", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_Minimize" , "WStyle_Minimize", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_Maximize" , "WStyle_Maximize", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_MinMax" , "WStyle_MinMax", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_ContextHelp" , "WStyle_ContextHelp", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WStyle_Tool" , "WStyle_Tool", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WType_TopLevel" , "WType_TopLevel", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WType_Dialog" , "WType_Dialog", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WType_Popup" , "WType_Popup", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Qt::WType_Desktop" , "WType_Desktop", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "LeftButton" , "Qt::LeftButton", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "MidButton" , "Qt::MidButton", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY|SKIP_NAMESPACE, "RightButton" , "Qt::RightButton", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "QWizard" , "Wizard", Qt::CaseSensitive);
   // Korrektur
   addReplacement(CPP, WORD_ONLY, "Wizard *" , "QWizard *", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "Wizard*" , "QWizard *", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "convertToImage" , "toImage", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "redirect" , "redirected", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "isShown" , "isVisible", Qt::CaseSensitive);
   addReplacement(CPP, WORD_ONLY, "absPath" , "absolutePath", Qt::CaseSensitive);
#ifdef todo
#endif
}

void UiTrans::addDerivedForm(const QString & baseName, const QString & baseClass, const QString & className, const QString & uiClassName)
{
   DerivedForm * derivedClass = new DerivedForm(baseName, baseClass, className, uiClassName);
   _derivedFormMap[baseName] = derivedClass;
}

DerivedForm * UiTrans::derivedForm(const QString & baseName) const
{
   DERIVED_FORM_MAP_T::const_iterator i = _derivedFormMap.find(baseName);
   if (i == _derivedFormMap.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void UiTrans::addDerivedForms()
{
return;
   // list reimplemented formulars class definitions substitute class definitions and constructors
   addDerivedForm("clp_minmoldheightwizard_sub", "Clp_MinmMoldHeightWizard_Sub", "Wizard", "Ui_Clp_MinMoldHeightWizard");
   addDerivedForm("clp_ejectorwizard_sub", "Clp_EjectorWizard_Sub", "Wizard", "Ui_Clp_EjectorWizard");
   addDerivedForm("cor_prgwizard_sub", "Cor_PrgWizard_Sub", "Wizard", "Ui_Cor_PrgWizard");
   addDerivedForm("inj_setunitmodewizard_sub", "Inj_SetUnitModeWizard_Sub", "Wizard", "Ui_Inj_SetUnitModeWizard");
   addDerivedForm("inj_sledwithstroketranswizard_sub", "Inj_SledWithStrokeTransWizard_Sub", "Wizard", "Ui_Inj_SledWithStrokeTransWizard");
   addDerivedForm("inj_velocitymoldcavitywizard_sub", "Inj_VelocityMoldCavityWizard_Sub", "Wizard", "Ui_Inj_VelocityMoldCavityWizard");
   addDerivedForm("mdat_changefgbgdialog_sub", "MDat_ChangeFgBgDialog_Sub", "ActionDialog", "Ui_MDat_ChangeFgBgDialog");
   addDerivedForm("mdat_copyfgtobgdialog_sub", "MDat_CopyFgToBgDialog_Sub", "ActionDialog", "Ui_MDat_CopyFgToBgDialog");
   addDerivedForm("mdat_readdatadialog_sub", "MDat_ReadDataDialog_Sub", "ActionDialog", "Ui_MDat_ReadDataDialog");
   addDerivedForm("ovw_configbarrelwizard_sub", "Ovw_ConfigBarrelWizard_Sub", "Wizard", "Ui_Ovw_ConfigBarrelWizard");
   addDerivedForm("sys_cardwizard_sub", "Sys_CardWizard_Sub", "Wizard", "Ui_Sys_CardWizard");
   addDerivedForm("sys_dirdialog_sub", "Sys_DirDialogSub", "Dialog", "Ui_Sys_DirDialog");
   addDerivedForm("sys_filehandlingdialog_sub", "Sys_FileHandlingDialog_Sub", "ActionDialog", "Ui_Sys_FileHandlingDialog");
   addDerivedForm("sys_filehandlingwizard_sub", "Sys_FileHandlingWizard_Sub", "Wizard", "Ui_Sys_FileHandlingWizard");
   addDerivedForm("sys_filesavedialog_sub", "Sys_FileSaveDialog_Sub", "Dialog", "Ui_Sys_FileSaveDialog");
   addDerivedForm("sys_filesavereadwizard_sub", "Sys_FileSaveReadWizard_Sub", "Wizard", "Ui_Sys_FileSaveReadWizard");
   addDerivedForm("tmp_interfacewizard_sub", "Tmp_InterfaceWizard_Sub", "Wizard", "Ui_Tmp_InterfaceWizard");
   addDerivedForm("aut_remoterobot_sub", "Aut_RemoteRobotSub", "Page", "Ui_Aut_RemoteRobot");
   addDerivedForm("mosaicstartupformimpl", "MosaicStartupFormImpl", "StartupForm", "Ui_MosaicStartupForm");
   addDerivedForm("mosaicframeimpl", "MosaicFrameImpl", "AppFrame", "Ui_MosaicFrame");
   addDerivedForm("ovw_posting_sub", "Ovw_PostingSub", "Page", "Ui_Ovw_Posting");
   addDerivedForm("sys_datetime_sub", "Sys_DateTimeSub", "Page", "Ui_Sys_DateTime");
   addDerivedForm("sys_language_sub", "Sys_LanguageSub", "Page", "Ui_Sys_Language");
   addDerivedForm("ovw_lubcartridgewizard_sub", "Ovw_LubCartridgeWizard_Sub", "Wizard", "Ui_Ovw_LubCartridgeWizard");
   addDerivedForm("clp_minmoldheightwizard_sub", "Clp_MinMoldHeightWizard_Sub", "Wizard", "Ui_Clp_MinMoldHeightWizard");
   addDerivedForm("clp_stackturnfeedzeroadjustwizard_sub", "Clp_StackTurnFeedZeroAdjustWizard_Sub", "Wizard", "Ui_Clp_StackTurnFeedZeroAdjustWizard");
   addDerivedForm("clp_stackturnparamwizard_sub", "Clp_StackTurnParamWizard_Sub", "Wizard", "Ui_Clp_StackTurnParamWizard");
   addDerivedForm("proc_powersavewizard_sub", "Proc_PowersaveWizard_Sub", "Wizard", "Ui_Proc_PowersaveWizard");
}

