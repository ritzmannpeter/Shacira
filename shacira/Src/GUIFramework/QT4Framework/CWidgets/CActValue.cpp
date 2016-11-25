
/// PR 05.12.06 - definitely removed restriction to 24 pixel height
///               in CCSSetContext

#include "CActValue.h"
#include "CAppFrame.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(DisplayWidget, \
                   CActValue, \
                   ICON_SET("label"), \
                   "widget to display values of variable references")
#endif

#define NL_TOKEN "\n"

CActValue::CActValue(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QLabel(parent, f),
#else
   : QLabel(parent, name),
#endif
     CWidgetBase(this), _Text("")
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _FormatValue = Native;
   _TranslationValue = NoTranslation;
   _IgnoreNullMappingValue = false;
   _IsNumericInput = false;
#ifdef QT4
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
#else
   setFrameStyle(QFrame::Panel | QFrame::Sunken);
#endif
#else
   setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
#endif
   setLineWidth(1);
   setMinimumHeight(getScaledHeight(this, 24));
   setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
}

CActValue::~CActValue ( ) 
{
}

void CActValue::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QLabel::mousePressEvent(e);
   }
}

void CActValue::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QLabel::mouseReleaseEvent(e);
   }
}


// GUI related virtual methods

void CActValue::View()
{
}

// CCS related virtual methods

void CActValue::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
   if (InitializeVarRef()) {
      CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);

#ifndef QT_PLUGIN
      if ((_VarRef != NULL) && IS_NUMBER(_VarRef->DataType())) {
         _IsNumericInput = true;
      }
#endif
   }
}

void CActValue::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString qValue = value;
   if (_FormatValue == HexaDecimal) {
      ULONG_T lval = qValue.toULong();
      if (size == 1) {
         qValue = QString("%1").arg(lval, 2, 16, QChar('0')).toUpper();
      } else if (size == 2) {
         qValue = QString("%1").arg(lval, 4, 16, QChar('0')).toUpper();
      } else if (size == 4) {
         qValue = QString("%1").arg(lval, 8, 16, QChar('0')).toUpper();
      } else {
         qValue = QString("%1").arg(lval, 10, 16, QChar('0')).toUpper();
      }
      setText(qValue);
   } else if (_FormatValue == Binary) {
      ULONG_T lval = qValue.toULong();
      ULONG_T flt_val = 0x80000000;
      if (size == 1) {
          flt_val = 0x80;
      } else if (size == 2) {
          flt_val = 0x8000;
      } else if (size == 4) {
          flt_val = 0x80000000;
      }
      for(ULONG_T bit=0; bit < (size*8); bit++) {
          CHAR_T bit_val[2] = "0";
          if (lval & (flt_val >> bit)) {
              bit_val[0] = '1';
          } else {
              bit_val[0] = '0';
          }
          qValue.append(bit_val);
      }
      setText(qValue);
   } else {
      if (CWidgetBase::Flag(UTF8_ENCODED_INPUT)) {
         if (!_IsNumericInput) {
            qValue = FromUtf8(qValue);
            //qValue = QString::fromUtf8(CONST_STRING(qValue));
         }
      }
      _Text = qValue;

      if (_TranslationValue != NoTranslation) {
         DelayedLanguageChange();
      } else {
         setText(_Text);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CActValue::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CActValue::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CActValue::DelayedLanguageChange()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_TranslationValue == NormalTranslation) {
      setText(GetTranslation(_Text));
   } else if (_TranslationValue == LineTranslation) {
      USHORT_T textLength = _Text.length();
      if (textLength) {
         setText(ParseText(_Text, textLength));
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

QString CActValue::ParseText(const QString & parseText, USHORT_T textLength)
{
   QString qstransText = "";
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString qsText = parseText;
#ifdef QT4
   int LinesWithToken = qsText.count(NL_TOKEN);
   int maxLine = LinesWithToken;
#ifdef QT4
   if (qsText.lastIndexOf(NL_TOKEN) < textLength) {
#else
   if (qsText.findRev(NL_TOKEN) < textLength) {
#endif
      maxLine++;
   }
   if (maxLine) {
      SHORT_T lineNo = 0;
      QString lineText("");
      QString translineText("");
      while (lineNo < maxLine) {
          QString qsTstText(qsText);
          int TstLength = qsTstText.length();
#ifdef QT4
          int pos = qsTstText.indexOf(NL_TOKEN);
#else
          int pos = qsTstText.find(NL_TOKEN);
#endif
          int offset = (pos == 0) ? 0 : 1;
          if (pos == 0) { // only token newline
              pos++;
          }

          if (pos != -1) {
             lineText = qsTstText.remove(pos, TstLength - pos);
             qsText = qsText.remove(0,pos+offset);
          }
          else {
             lineText = qsTstText;
          }
          translineText = GetTranslation(lineText);
          qstransText += translineText;
          if ((offset == 1) && (lineNo < LinesWithToken)) {
              qstransText += NL_TOKEN;
          }
          lineNo++;
      }
   } else {
      qstransText = GetTranslation(parseText);
   }
#else
   SHORT_T LinesWithToken = qsText.contains(NL_TOKEN);
   SHORT_T maxLine = LinesWithToken;
   if (qsText.findRev(NL_TOKEN) < textLength) {
      maxLine++;
   }
   if (maxLine) {
      SHORT_T lineNo = 0;
      QString lineText("");
      QString translineText("");
      while (lineNo < maxLine) {
          QString qsTstText(qsText);
          USHORT_T TstLength = qsTstText.length();
          SHORT_T pos = qsTstText.find(NL_TOKEN);
          SHORT_T offset = (pos == 0) ? 0 : 1;
          if (pos == 0) { // only token newline
              pos++;
          }

          if (pos != -1) {
             lineText = qsTstText.remove(pos, TstLength - pos);
             qsText = qsText.remove(0,pos+offset);
          }
          else {
             lineText = qsTstText;
          }
          translineText = GetTranslation(lineText);
          qstransText += translineText;
          if ((offset == 1) && (lineNo < LinesWithToken)) {
              qstransText += NL_TOKEN;
          }
          lineNo++;
      }
   } else {
      qstransText = GetTranslation(parseText);
   }
#endif
WMETHOD_RC_EPILOG(qstransText)
#endif
   return qstransText;
}

QString CActValue::GetTranslation(const QString & text)
{
    QString translated_text = "";
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CAppFrame * app_frame = CWidgetBase::_AppFrame;
   if ((app_frame != NULL) && (_VarRef != NULL)) {
      LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
      _VarRef->GetIndices(i1, i2, i3, i4);
      cVarDef * var_def = _VarRef->VarDef();
      ULONG_T system_flags = var_def->_SystemFlags;
      QString i1_Text = QString::number(i1 + ((system_flags & DIM1_OFFSET) != 0));
      QString i2_Text = QString::number(i2 + ((system_flags & DIM2_OFFSET) != 0));
      QString i3_Text = QString::number(i3 + ((system_flags & DIM3_OFFSET) != 0));
      QString i4_Text = QString::number(i4 + ((system_flags & DIM4_OFFSET) != 0));
      if (!app_frame->GetTranslation(translated_text, _VarRef->_Name.c_str(), 0, text, i1_Text, i2_Text, i3_Text, i4_Text)) {
         translated_text = Translate(text, "custom", i1_Text, i2_Text, i3_Text, i4_Text);
      }
   }
WMETHOD_RC_EPILOG(translated_text)
#endif
    return translated_text;
}

BOOL_T CActValue::InitializeVarRef()
{
   BOOL_T initialize = true;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_IgnoreNullMappingValue && strlen(_VarSpec) > 0) {
      if (_Context != NULL) {
         cVarRef * var_ref = _Context->VarRef(_VarSpec, 0);
         if (var_ref != NULL) {
            cVarDef * var_def = var_ref->VarDef();
            if (var_def != NULL) {
               cMapping * mapping = var_def->_Mapping;
               if ((mapping != NULL) &&
                   ((strcmp("register", mapping->_PhysSpec.c_str()) == 0) || (strcmp("bit", mapping->_PhysSpec.c_str()) == 0))) {
                  LONG_T VarSpec_i1 = -1;
                  LONG_T VarSpec_i2 = -1;
                  LONG_T VarSpec_i3 = -1;
                  LONG_T VarSpec_i4 = -1;
                  int elements = var_def->Elements();
                  int pos = 0;
                  SHORT_T  param = 0;
                  QString qcsDimension;
#ifdef QT4
                  QString varSpec = _VarSpec;
                  qcsDimension = varSpec.right(varSpec.length() - varSpec.indexOf('['));
#else
                  qcsDimension = _VarSpec.right(_VarSpec.length() - _VarSpec.find('['));
#endif
                  if (!qcsDimension.isEmpty()) {
                     param = sscanf(CONST_STRING(qcsDimension), "[%d][%d][%d][%d]", &VarSpec_i1, &VarSpec_i2, &VarSpec_i3, &VarSpec_i4);
                  }
                  for (pos=0; pos<elements; pos++) {
                     MAP_ITEM_T * map_item = mapping->MapItem(pos);
                     if (map_item != NULL) {
                        LONG_T i1 = -1;
                        LONG_T i2 = -1;
                        LONG_T i3 = -1;
                        LONG_T i4 = -1;
                        var_def->GetIndices(pos, i1, i2, i3, i4);

                        if ((i1 == VarSpec_i1) && (i2 == VarSpec_i2) && 
                            (i3 == VarSpec_i3) && (i4 == VarSpec_i4) && 
                            (map_item->address == (ULONG_T)UNDEFINED_SYMBOL_VALUE)) {
                           initialize = false;
                           break;
                        }
                     }
                  }
               }
            }
         }
      }
   }
WMETHOD_RC_EPILOG(initialize)
#endif
   return initialize;
}
