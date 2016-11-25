
/// PR 12.05.05 - changed alarm table handling to minor resource consuming version
/// PR 19.10.05 - calling CAppFrame::GetTranslatedText to handle user translated alarm texts
///             - switched OLD_ALARM_HANDLING off
/// PR 19.10.05 - removed OLD_ALARM_HANDLING and added utf8-sensitivity
/// PR 18.03.11 - added missing designer plugin registration

#include "CAlarmWidget.h"
#include "CAppFrame.h"
#include <qheader.h>
#include <qdir.h>

#ifndef QT_PLUGIN
#include "qscrollbar.h"
#endif

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
SH_PLUGIN_REGISTER(DisplayWidget, \
                   CAlarmWidget, \
                   ICON_SET("listview"), \
                   "widget to display currently active alarms")
#endif

static const char* const info_icon_data[] = { 
"32 32 5 1",
"a c None",
"b c #000000",
"# c #808000",
"c c #808080",
". c #c0c0c0",
".............###................",
"............#aa.b...............",
"...........#aaaa.bc.............",
"...........#aaaaabcc............",
"..........#aaaaaa.bcc...........",
"..........#aaaaaaabcc...........",
".........#aaaaaaaa.bcc..........",
".........#aaaaaaaaabcc..........",
"........#aaaaaaaaaa.bcc.........",
"........#aaa.bbb.aaabcc.........",
".......#aaaabbbbbaaa.bcc........",
".......#aaaabbbbbaaaabcc........",
"......#aaaaabbbbbaaaa.bcc.......",
"......#aaaaabbbbbaaaaabcc.......",
".....#aaaaaabbbbbaaaaa.bcc......",
".....#aaaaaa#bbb#aaaaaabcc......",
"....#aaaaaaa.bbb.aaaaaa.bcc.....",
"....#aaaaaaaabbbaaaaaaaabcc.....",
"...#aaaaaaaaa#b#aaaaaaaa.bcc....",
"...#aaaaaaaaa.b.aaaaaaaaabcc....",
"..#aaaaaaaaaaabaaaaaaaaaa.bcc...",
"..#aaaaaaaaaaaaaaaaaaaaaaabcc...",
".#aaaaaaaaaaa.bb.aaaaaaaaa.bcc..",
".#aaaaaaaaaaabbbbaaaaaaaaaabcc..",
"#aaaaaaaaaaaabbbbaaaaaaaaaa.bcc.",
"#aaaaaaaaaaaa.bb.aaaaaaaaaaabcc.",
"#aaaaaaaaaaaaaaaaaaaaaaaaaaabccc",
"#aaaaaaaaaaaaaaaaaaaaaaaaaa.bccc",
".#aaaaaaaaaaaaaaaaaaaaaaaa.bcccc",
"..#bbbbbbbbbbbbbbbbbbbbbbbbccccc",
"....ccccccccccccccccccccccccccc.",
".....ccccccccccccccccccccccccc.."};

static const char* const warning_icon_data[] = { 
"32 32 5 1",
"a c None",
"b c #000000",
"# c #808000",
"c c #808080",
". c #c0c0c0",
".............###................",
"............#aa.b...............",
"...........#aaaa.bc.............",
"...........#aaaaabcc............",
"..........#aaaaaa.bcc...........",
"..........#aaaaaaabcc...........",
".........#aaaaaaaa.bcc..........",
".........#aaaaaaaaabcc..........",
"........#aaaaaaaaaa.bcc.........",
"........#aaa.bbb.aaabcc.........",
".......#aaaabbbbbaaa.bcc........",
".......#aaaabbbbbaaaabcc........",
"......#aaaaabbbbbaaaa.bcc.......",
"......#aaaaabbbbbaaaaabcc.......",
".....#aaaaaabbbbbaaaaa.bcc......",
".....#aaaaaa#bbb#aaaaaabcc......",
"....#aaaaaaa.bbb.aaaaaa.bcc.....",
"....#aaaaaaaabbbaaaaaaaabcc.....",
"...#aaaaaaaaa#b#aaaaaaaa.bcc....",
"...#aaaaaaaaa.b.aaaaaaaaabcc....",
"..#aaaaaaaaaaabaaaaaaaaaa.bcc...",
"..#aaaaaaaaaaaaaaaaaaaaaaabcc...",
".#aaaaaaaaaaa.bb.aaaaaaaaa.bcc..",
".#aaaaaaaaaaabbbbaaaaaaaaaabcc..",
"#aaaaaaaaaaaabbbbaaaaaaaaaa.bcc.",
"#aaaaaaaaaaaa.bb.aaaaaaaaaaabcc.",
"#aaaaaaaaaaaaaaaaaaaaaaaaaaabccc",
"#aaaaaaaaaaaaaaaaaaaaaaaaaa.bccc",
".#aaaaaaaaaaaaaaaaaaaaaaaa.bcccc",
"..#bbbbbbbbbbbbbbbbbbbbbbbbccccc",
"....ccccccccccccccccccccccccccc.",
".....ccccccccccccccccccccccccc.."};

static const char* const error_icon_data[] = { 
"31 32 5 1",
". c None",
"# c #800000",
"b c #808080",
"a c #ff0000",
"c c #ffffff",
"...........########............",
"........###aaaaaaaa###.........",
".......#aaaaaaaaaaaaaa#........",
".....##aaaaaaaaaaaaaaaa##......",
"....#aaaaaaaaaaaaaaaaaaaa#.....",
"...#aaaaaaaaaaaaaaaaaaaaaa#....",
"...#aaaaaaaaaaaaaaaaaaaaaa#b...",
"..#aaaaaacaaaaaaaaaacaaaaaa#b..",
".#aaaaaacccaaaaaaaacccaaaaaa#..",
".#aaaaacccccaaaaaacccccaaaaa#b.",
".#aaaaaacccccaaaacccccaaaaaa#bb",
"#aaaaaaaacccccaacccccaaaaaaaa#b",
"#aaaaaaaaaccccccccccaaaaaaaaa#b",
"#aaaaaaaaaaccccccccaaaaaaaaaa#b",
"#aaaaaaaaaaaccccccaaaaaaaaaaa#b",
"#aaaaaaaaaaaccccccaaaaaaaaaaa#b",
"#aaaaaaaaaaccccccccaaaaaaaaaa#b",
"#aaaaaaaaaccccccccccaaaaaaaaa#b",
"#aaaaaaaacccccaacccccaaaaaaaa#b",
".#aaaaaacccccaaaacccccaaaaaa#bb",
".#aaaaacccccaaaaaacccccaaaaa#bb",
".#aaaaaacccaaaaaaaacccaaaaaa#bb",
"..#aaaaaacaaaaaaaaaacaaaaaa#bbb",
"...#aaaaaaaaaaaaaaaaaaaaaa#bbbb",
"...#aaaaaaaaaaaaaaaaaaaaaa#bbb.",
"....#aaaaaaaaaaaaaaaaaaaa#bbb..",
".....##aaaaaaaaaaaaaaaa##bbbb..",
"......b#aaaaaaaaaaaaaa#bbbbb...",
".......b###aaaaaaaa###bbbbb....",
".........bb########bbbbbb......",
"..........bbbbbbbbbbbbbb.......",
".............bbbbbbbb.........."};

static const char* const serious_error_icon_data[] = { 
"31 32 5 1",
". c None",
"# c #800000",
"b c #808080",
"a c #ff0000",
"c c #ffffff",
"...........########............",
"........###aaaaaaaa###.........",
".......#aaaaaaaaaaaaaa#........",
".....##aaaaaaaaaaaaaaaa##......",
"....#aaaaaaaaaaaaaaaaaaaa#.....",
"...#aaaaaaaaaaaaaaaaaaaaaa#....",
"...#aaaaaaaaaaaaaaaaaaaaaa#b...",
"..#aaaaaacaaaaaaaaaacaaaaaa#b..",
".#aaaaaacccaaaaaaaacccaaaaaa#..",
".#aaaaacccccaaaaaacccccaaaaa#b.",
".#aaaaaacccccaaaacccccaaaaaa#bb",
"#aaaaaaaacccccaacccccaaaaaaaa#b",
"#aaaaaaaaaccccccccccaaaaaaaaa#b",
"#aaaaaaaaaaccccccccaaaaaaaaaa#b",
"#aaaaaaaaaaaccccccaaaaaaaaaaa#b",
"#aaaaaaaaaaaccccccaaaaaaaaaaa#b",
"#aaaaaaaaaaccccccccaaaaaaaaaa#b",
"#aaaaaaaaaccccccccccaaaaaaaaa#b",
"#aaaaaaaacccccaacccccaaaaaaaa#b",
".#aaaaaacccccaaaacccccaaaaaa#bb",
".#aaaaacccccaaaaaacccccaaaaa#bb",
".#aaaaaacccaaaaaaaacccaaaaaa#bb",
"..#aaaaaacaaaaaaaaaacaaaaaa#bbb",
"...#aaaaaaaaaaaaaaaaaaaaaa#bbbb",
"...#aaaaaaaaaaaaaaaaaaaaaa#bbb.",
"....#aaaaaaaaaaaaaaaaaaaa#bbb..",
".....##aaaaaaaaaaaaaaaa##bbbb..",
"......b#aaaaaaaaaaaaaa#bbbbb...",
".......b###aaaaaaaa###bbbbb....",
".........bb########bbbbbb......",
"..........bbbbbbbbbbbbbb.......",
".............bbbbbbbb.........."};

#ifndef QT_PLUGIN

typedef STRING_T ALARM_TEXT_TYPE_T;

#define MAX_ALARMS      512
#define MAX_TEXT_SIZE   256

typedef struct alarm_entry {
   ULONG_T timestamp;
   ULONG_T ident;
   CONST_STRING_T context;
   SeverityTypes severity;
   cAlarm * _Alarm;
}  ALARM_ENTRY_T;   

class AlarmTable {
public:
   AlarmTable();
   virtual ~AlarmTable();
   void AddAlarm(cAlarm * alarm);
   void RemoveAlarm(cAlarm * alarm);
   ULONG_T Alarms();
   ULONG_T Ident(int index);
   SeverityTypes Severity(int index);
   ULONG_T Timestamp(int index);
   ALARM_TEXT_TYPE_T Context(int index);
   QString Text1(int index, BOOL_T &translated);
   ALARM_TEXT_TYPE_T Text2(int index);
   ALARM_TEXT_TYPE_T Text3(int index);
   ALARM_TEXT_TYPE_T Text4(int index);
   ALARM_TEXT_TYPE_T Param1(int index);
   ALARM_TEXT_TYPE_T Param2(int index);
   ALARM_TEXT_TYPE_T Param3(int index);
   ALARM_TEXT_TYPE_T Param4(int index);
   ALARM_TEXT_TYPE_T HelpId(int index);
private:
   ALARM_ENTRY_T _Entries[MAX_ALARMS];
private:
   int FreeIndex();
   int FindIndex(ULONG_T ident);
};

AlarmTable::AlarmTable()
{
   memset(_Entries, 0, sizeof(_Entries));
}

AlarmTable::~AlarmTable()
{
}

void AlarmTable::AddAlarm(cAlarm * alarm)
{
   ULONG_T ident = alarm->get_Ident();
   int index = FindIndex(ident);
   if (index >= 0) return;
   index = FreeIndex();
   if (index >= 0) {
      ULONG_T text_id1 = alarm->get_TextId1();
      alarm->AddRef();
      _Entries[index].timestamp = alarm->get_TimeStamp();;
      _Entries[index].severity = alarm->get_Severity();;
      _Entries[index].ident = ident;
      if (cResources::FlagSet(PF_NONSTANDARD_CONTEXT) && (text_id1 == 0)) {
         if((_Entries[index].severity == SevSeriousError) || (_Entries[index].severity == SevError))
            _Entries[index].context = "AlarmText";
         else
            _Entries[index].context = "FaultText";
      }
      else {
         _Entries[index].context = cText::Context(text_id1);
      }
      _Entries[index]._Alarm = alarm;
   } else {
   }
}

void AlarmTable::RemoveAlarm(cAlarm * alarm)
{
   ULONG_T ident = alarm->get_Ident();
   int index = FindIndex(ident);
   if (index >= 0) {
      _Entries[index].ident = 0;
      _Entries[index]._Alarm->Release();
      _Entries[index]._Alarm = NULL;
   }
}

ULONG_T AlarmTable::Alarms()
{
   ULONG_T alarms = 0;
   for (ULONG_T i=0; i<MAX_ALARMS; i++) {
      if (_Entries[i].ident != 0) alarms++; 
   }
   return alarms;
}

ULONG_T AlarmTable::Ident(int index)
{
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      return _Entries[index].ident;
   }
   return 0;
}

SeverityTypes AlarmTable::Severity(int index)
{
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      return _Entries[index].severity;
   }
   return SevSeriousError;
}

ULONG_T AlarmTable::Timestamp(int index)
{
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      return _Entries[index].timestamp;
   }
   return 0;
}

ALARM_TEXT_TYPE_T AlarmTable::Context(int index)
{
   ALARM_TEXT_TYPE_T context = "custom";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      context = _Entries[index].context;
   }
   return context;
}

QString AlarmTable::Text1(int index, BOOL_T &translated)
{
   QString text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      CAppFrame * app_frame = CWidgetBase::_AppFrame;
      if (app_frame != NULL) {
         QString translated_text;
         ULONG_T id = _Entries[index]._Alarm->get_Ident();

         text = cText::GetText(_Entries[index]._Alarm->get_TextId1(),
                               _Entries[index]._Alarm->get_Text1().c_str()).c_str();

         if (app_frame->GetTranslation(translated_text, app_frame->GetLanguage(),
                                       id, text,
                                       _Entries[index]._Alarm->get_Param1().c_str(), _Entries[index]._Alarm->get_Param2().c_str(),
                                       _Entries[index]._Alarm->get_Param3().c_str(), _Entries[index]._Alarm->get_Param4().c_str())) {
            text = translated_text;
            translated = true;
         } else {
            /// standard translation
            translated = false;
         } 
      }
   }
   return text;
}

ALARM_TEXT_TYPE_T AlarmTable::Text2(int index)
{
   ALARM_TEXT_TYPE_T text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      text = cText::GetText(_Entries[index]._Alarm->get_TextId2(),
                            _Entries[index]._Alarm->get_Text2().c_str());
   }
   return text;
}

ALARM_TEXT_TYPE_T AlarmTable::Text3(int index)
{
   ALARM_TEXT_TYPE_T text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      text = _Entries[index]._Alarm->get_Text3().c_str();
   }
   return text;
}

ALARM_TEXT_TYPE_T AlarmTable::Text4(int index)
{
   ALARM_TEXT_TYPE_T text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      text = _Entries[index]._Alarm->get_Text4().c_str();
   }
   return text;
}

ALARM_TEXT_TYPE_T AlarmTable::Param1(int index)
{
   ALARM_TEXT_TYPE_T text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      text = _Entries[index]._Alarm->get_Param1();
   }
   return text;
}

ALARM_TEXT_TYPE_T AlarmTable::Param2(int index)
{
   ALARM_TEXT_TYPE_T text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      text = _Entries[index]._Alarm->get_Param2();
   }
   return text;
}

ALARM_TEXT_TYPE_T AlarmTable::Param3(int index)
{
   ALARM_TEXT_TYPE_T text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      text = _Entries[index]._Alarm->get_Param3();
   }
   return text;
}

ALARM_TEXT_TYPE_T AlarmTable::Param4(int index)
{
   ALARM_TEXT_TYPE_T text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      text = _Entries[index]._Alarm->get_Param4();
   }
   return text;
}

ALARM_TEXT_TYPE_T AlarmTable::HelpId(int index)
{
   ALARM_TEXT_TYPE_T text = "?";
   if (index < MAX_ALARMS && _Entries[index].ident != 0) {
      text = _Entries[index]._Alarm->get_HelpId();
   }
   return text;
}


int AlarmTable::FreeIndex()
{
   for (ULONG_T i=0; i<MAX_ALARMS; i++) {
      if (_Entries[i].ident == 0) return i; 
   }
   return -1;
}

int AlarmTable::FindIndex(ULONG_T ident)
{
   for (ULONG_T i=0; i<MAX_ALARMS; i++) {
      if (_Entries[i].ident == ident) return i; 
   }
   return -1;
}

#endif


// CAlarmWidgetItem
CAlarmWidgetItem::CAlarmWidgetItem(ListView * parent, const QString & help_id)
   : ListViewItem(parent), _help_id(help_id)
{
};

CAlarmWidgetItem::~CAlarmWidgetItem()
{
};

QString CAlarmWidgetItem::get_HelpId()
{
   return _help_id;
};

CAlarmWidget::CAlarmWidget(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
   : ListView(parent, name, f),
     CWidgetBase(this),
     _InfoImage(info_icon_data),
     _WarningImage(warning_icon_data),
     _ErrorImage(error_icon_data),
     _SeriousErrorImage(serious_error_icon_data)
{
   CONSTRUCT_WIDGET

#ifdef QT4
   _InfoImage = _InfoImage.scaled(20, 20);
   _WarningImage = _WarningImage.scaled(20, 20);
   _ErrorImage = _ErrorImage.scaled(20, 20);
   _SeriousErrorImage = _SeriousErrorImage.scaled(20, 20);
#else
   _InfoImage = _InfoImage.scale(20, 20);
   _WarningImage = _WarningImage.scale(20, 20);
   _ErrorImage = _ErrorImage.scale(20, 20);
   _SeriousErrorImage = _SeriousErrorImage.scale(20, 20);
#endif
   _IconWidthValue = 0;
   _IconHeightValue = 0;
   _IconColWidthValue = 30;
   _TimeColWidthValue = 150;
   _MessageColWidthValue = 400;
   _ColSpacingValue = 10;
   _ItemSelectionTypeValue = Standard;

#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _AlarmTable = new AlarmTable;
WMETHOD_VOID_EPILOG
#endif

   connect(this, SIGNAL(selectionChanged(ListViewItem*)), this, SLOT(SelectionChanged(ListViewItem*)));

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   header()->setSectionsMovable(false);
#else
   header()->setMovable(false);
#endif

#if QT_VERSION >= QT_VERSION_CHECK(4,0,0)
   setUniformRowHeights(true);
#endif
}

CAlarmWidget::~CAlarmWidget ( ) 
{
#ifndef QT_PLUGIN
#endif
}

void CAlarmWidget::SelectionChanged(ListViewItem * item)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (item != NULL) {
      if (_ItemSelectionTypeValue == ChangeHelpId1) {
         CAlarmWidgetItem * alarmItem = static_cast<CAlarmWidgetItem*>(item);
         QString help_id = alarmItem->get_HelpId();

         if (!help_id.isEmpty()) {
             QString qAdditionalPath = "alarms";
#ifdef QT4
             SHORT_T sepPos = help_id.lastIndexOf(QDir::separator());
#else
             SHORT_T sepPos = help_id.findRev(QDir::separator());
#endif
             if (sepPos != -1) {
                 qAdditionalPath = help_id.left(sepPos);
                 help_id = help_id.right(help_id.length() - (sepPos+1));
             }
             _ActHelpId1 = help_id;
             _AppFrame->SetHelpAdditionalPath(qAdditionalPath);
         } else {
             SetHelpIds((QWidget*)_QWidget->parent());
         }
        
         if (_AppFrame->HelpActive()) {
             _AppFrame->ShowHelp(_ActHelpId1, _ActHelpId2);
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

// GUI related virtual methods

void CAlarmWidget::View()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   UpdateWidget();
WMETHOD_VOID_EPILOG
#endif
}

void CAlarmWidget::DelayedLanguageChange()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ShowAlarms();
WMETHOD_VOID_EPILOG
#endif
}

// CCS related virtual methods

void CAlarmWidget::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifdef QT4
   if (_InfoPixmapValue.width() > 0) {
      _InfoImage = _InfoPixmapValue.toImage();
      if (_IconWidthValue > 0 &&
          _IconHeightValue > 0) {
         _InfoImage = _InfoImage.scaled(_IconWidthValue, _IconHeightValue);
      }
   }
   if (_WarningPixmapValue.width() > 0) {
      _WarningImage = _WarningPixmapValue.toImage();
      if (_IconWidthValue > 0 &&
          _IconHeightValue > 0) {
         _WarningImage = _WarningImage.scaled(_IconWidthValue, _IconHeightValue);
      }
   }
   if (_ErrorPixmapValue.width() > 0) {
      _ErrorImage = _ErrorPixmapValue.toImage();
      if (_IconWidthValue > 0 &&
          _IconHeightValue > 0) {
         _ErrorImage = _ErrorImage.scaled(_IconWidthValue, _IconHeightValue);
      }
   }
   if (_SeriousErrorPixmapValue.width() > 0) {
      _SeriousErrorImage = _SeriousErrorPixmapValue.toImage();
      if (_IconWidthValue > 0 &&
          _IconHeightValue > 0) {
         _SeriousErrorImage = _SeriousErrorImage.scaled(_IconWidthValue, _IconHeightValue);
      }
   }

#ifndef QT_PLUGIN
   if (TOUCH_SCREEN_ACTIVE()) {
      QScrollBar * hScrollBar = horizontalScrollBar();
      QScrollBar * vScrollbar = verticalScrollBar();
      if (hScrollBar) hScrollBar->setContextMenuPolicy(Qt::PreventContextMenu);
      if (vScrollbar) vScrollbar->setContextMenuPolicy(Qt::PreventContextMenu);
   }
#endif
#else
   if (_InfoPixmapValue.width() > 0) {
      _InfoImage = _InfoPixmapValue;
      if (_IconWidthValue > 0 &&
          _IconHeightValue > 0) {
         _InfoImage = _InfoImage.scale(_IconWidthValue, _IconHeightValue);
      }
   }
   if (_WarningPixmapValue.width() > 0) {
      _WarningImage = _WarningPixmapValue;
      if (_IconWidthValue > 0 &&
          _IconHeightValue > 0) {
         _WarningImage = _WarningImage.scale(_IconWidthValue, _IconHeightValue);
      }
   }
   if (_ErrorPixmapValue.width() > 0) {
      _ErrorImage = _ErrorPixmapValue;
      if (_IconWidthValue > 0 &&
          _IconHeightValue > 0) {
         _ErrorImage = _ErrorImage.scale(_IconWidthValue, _IconHeightValue);
      }
   }
   if (_SeriousErrorPixmapValue.width() > 0) {
      _SeriousErrorImage = _SeriousErrorPixmapValue;
      if (_IconWidthValue > 0 &&
          _IconHeightValue > 0) {
         _SeriousErrorImage = _SeriousErrorImage.scale(_IconWidthValue, _IconHeightValue);
      }
   }
#endif

   addColumn(_IconColTextValue);
   addColumn(_TimeColTextValue);
   addColumn(_MessageColTextValue);
   header()->setFont(font());
}

void CAlarmWidget::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
}

void CAlarmWidget::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
}

void CAlarmWidget::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   UCHAR_T object_type = object->get_Type();
   if (object_type == OT_ALARM) {
      cAlarm * alarm = (cAlarm*)object;
      BOOL_T state = alarm->get_State();
      if (state) {
         _AlarmTable->AddAlarm(alarm);
      } else {
         _AlarmTable->RemoveAlarm(alarm);
      }
      _Invalidated = true;
      Notify(VIEW_DATA);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAlarmWidget::ShowAlarms()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   clear();
#ifdef QT4
   setColumnText(0, _IconColTextValue);
   setColumnText(1, _TimeColTextValue);
   setColumnText(2, _MessageColTextValue);
   setColumnWidth(0, _IconColWidthValue + _ColSpacingValue);
   setColumnWidth(1, _TimeColWidthValue + _ColSpacingValue);
   setColumnWidth(2, _MessageColWidthValue + _ColSpacingValue);
   setSorting(-1, false);
#else
   setColumnText(0, _IconColTextValue);
   setColumnText(1, _TimeColTextValue);
   setColumnText(2, _MessageColTextValue);
   setColumnWidth(0, _IconColWidthValue + _ColSpacingValue);
   setColumnWidth(1, _TimeColWidthValue + _ColSpacingValue);
   setColumnWidth(2, _MessageColWidthValue + _ColSpacingValue);
   setSorting(-1, false);
#endif
   ULONG_T alarms = _AlarmTable->Alarms();
   if (alarms > 0) {
      for (ULONG_T i=0; i<MAX_ALARMS; i++) {
         ULONG_T ident = _AlarmTable->Ident(i);
         if (ident > 0) {
            CAlarmWidgetItem * item = new CAlarmWidgetItem(this, _AlarmTable->HelpId(i).c_str());
            cTimeObject timestamp(_AlarmTable->Timestamp(i));
            item->setText(1, (const char *)timestamp);
            BOOL_T  translated = false;
            QString text = _AlarmTable->Text1(i, translated);
            if (translated == false)
            {
                text = Translate(text, _AlarmTable->Context(i).c_str(),
                                 _AlarmTable->Param1(i).c_str(), _AlarmTable->Param2(i).c_str(),
                                 _AlarmTable->Param3(i).c_str(), _AlarmTable->Param4(i).c_str());
            }

            if (strlen(_AlarmTable->Text2(i).c_str())) {
               QString text2 = Translate(_AlarmTable->Text2(i).c_str(), _AlarmTable->Context(i).c_str(),
                                         _AlarmTable->Param1(i).c_str(), _AlarmTable->Param2(i).c_str(),
                                         _AlarmTable->Param3(i).c_str(), _AlarmTable->Param4(i).c_str());
               text += " : ";
               text += text2;
            }
            SeverityTypes severity = _AlarmTable->Severity(i);
            switch (severity) {
            case SevInfo:
               item->setImage(0, _InfoImage);
               break;
            case SevWarning:
               item->setImage(0, _WarningImage);
               break;
            case SevError:
               item->setImage(0, _ErrorImage);
               break;
            case SevSeriousError:
               item->setImage(0, _SeriousErrorImage);
               break;
            }
            QString utf8_text = text;
            if (CWidgetBase::Flag(UTF8_ENCODED_INPUT)) {
               utf8_text = FromUtf8(text);
               //utf8_text = QString::fromUtf8(CONST_STRING(text));
            }
            item->setText(2, utf8_text);
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAlarmWidget::UpdateWidget()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Invalidated) {
      ShowAlarms();
      update();
      _Invalidated = false;
   }
WMETHOD_VOID_EPILOG
#endif
}

ULONG_T CAlarmWidget::ItemPos(ListViewItem * item)
{
#ifndef QT_PLUGIN
   if (item != NULL) {
      ULONG_T children = childCount();
      if (children == 0) return 0;
      ULONG_T i = 0;
      ListViewItemIterator it(this);
      ListViewItem * search_item = it.current();
      while (search_item != NULL) {
         if (item == search_item) {
            break;
         }
         i++;
         it++;
         search_item = it.current();
      }
      return (search_item == item) ? i : 0;
   }
#endif
   return 0;
}

