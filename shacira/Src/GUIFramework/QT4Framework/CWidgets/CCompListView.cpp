
#include "CCompListView.h"
#include <qapplication.h>

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(AdditionalWidget, \
                   CCompListView, \
                   ICON_SET("listview"), \
                   "list view widget for the display of dataset comparisons")
#endif

#include <qimage.h>

#ifndef QT_PLUGIN
#include "System/cTokenizer.h"
#include "System/cStringUtils.h"
#include "System/Database/cVarDef.h"
#include "Control/LocalDatabase/cLocalVariable.h"
#endif

static const char* const image0_data[] = { 
"61 36 28 1",
"# c #000000",
"p c #006d00",
"o c #009200",
"r c #6b6d52",
"q c #6b6dad",
"c c #6b9252",
"m c #6b92ad",
"d c #946d52",
"s c #946dad",
"f c #949252",
"e c #9492ad",
"x c #b5b6ad",
"z c #b5b6ff",
"w c #b5dbad",
"v c #b5dbff",
". c #c6c3c6",
"j c #de0000",
"u c #deb6ad",
"y c #deb6ff",
"k c #dedbad",
"b c #dedbff",
"t c #deffad",
"g c #deffff",
"i c #ff0000",
"l c #ffdbad",
"a c #ffdbff",
"n c #ffffad",
"h c #ffffff",
".............................................................",
".............................................................",
".............................................................",
".............................................................",
".............................................................",
"....................#a.......................................",
"....................b#.......................................",
"...............cdecfff.......................................",
"...............gbbbbbbba.....................................",
"...hhaghghhgiiiiiiiiiiijhhhhbbakbabbblbbbabbakakhghhghh......",
"...hhhhhhhhhiij#dmdmdmdi####dmdmdmdmdmdmdmdmdmbbhhhhh#h......",
"...hhgnhbhghjii#mdmdmdmidopm########qfqfrecscstaredmfmf......",
"...hhhhhhnhhiii#fqfqfqfimpodhhhhhhhhhhcabakglbbatbbakbl......",
"...hhhghhghhjijuqfqfqfqidopmvuwxwywh##sgbtabbbnb##lgabg......",
"...hghahhhhhiiizcscscscimdmdxxy#xxxywzd#a#bfqfq#bbbkbnb......",
"...hhnhgnahgiiixfscscsciscscywxxvuvxu#c#kbhrere#hhlgabbatb...",
"...hhhhhhghhijixmdmdmfqi####x#hhxxuwzxe#bak#####frblbtabba...",
"...hghhghhghiiixerersreicscs##########dglgbhkhbabgagbakbnb...",
"...hhhhhhhhhjiixefmfmfqiecscscsmdmfqrfqabkabbakglbkakgabbl...",
"...##h#####hiii#rqrsrscixh########qfeererererfbabbagbablg....",
"...##hgh###hjiiweefeceqixzk#hhhxxkzxxxer#hbnbgbtat##agkga....",
"...##hiiiiihiiizxxxzxxxikxzxwuxxbxxxbx#e#kbbablbab##kbabl....",
"...hhghhghghijiiiiijiiiirererererererfqfqfqfqfqfqcsrermdm....",
"...hhhhhhhhhiiiiijiiiiiimdmdmdmdmdmdmqecsmdmfqfqedefmsfqf....",
"...gblgkere#cscecfererereredmdmfqfqf#d####yx##mxxwzxxwzfq....",
"...........#s...........ecscscscscsc#hzwuxwxxhdkzuxxh#uqf....",
"...........#m...........fqfqfqfqfscs#hxuzhhzkhqxwxzkhhxcs....",
"...........#f...........qfqfqfqfqfqf#hvxwxuxxxexzkxxhhwsc....",
"...........#q...........fqfqfqfqfqfq#hxyxzwzk#rk#xvuzxycs....",
"...........#f...........cscscscscscs##wxuwxuxxexzuxxuwxsc....",
"...........#e...........re##ecscscscer#ecscscerecerecsc#e....",
"...........#n...........#################################....",
".............................................................",
".............................................................",
".............................................................",
"............................................................."};


#ifndef QT_PLUGIN
static STRING_T ParseVarName(CONST_STRING_T var_spec)
{
   int len = strlen(var_spec);
   int i = 0;
   for (i=0; i<len; i++) {
      if (var_spec[i] == '\0' ||
          var_spec[i] == '[') {
         break;
      }
   }
   if (i == len) {
      return var_spec;
   } else {
      STRING_T var_name = cStringUtils::Left(var_spec, i);
      return var_name;
   }
}

class cCompEntry
{
public:
   cCompEntry(CONST_STRING_T var_spec, CONST_STRING_T fg_value, CONST_STRING_T bg_value)
   {
      _VarSpec = var_spec;
      _FgValue = fg_value;
      _BgValue = bg_value;
   };
   virtual ~cCompEntry() {};
public:
   STRING_T _VarSpec;
   STRING_T _FgValue;
   STRING_T _BgValue;
};
typedef std::list<cCompEntry*> COMP_ENTRY_LIST_T;


class cVarGroup
{
public:
   cVarGroup(const QString & group_name)
   {
      _GroupName = group_name;
   };
   virtual ~cVarGroup()
   {
      COMP_ENTRY_LIST_T::const_iterator i = _CompEntries.begin();
      while (i != _CompEntries.end()) {
         cCompEntry * entry = (*i);
         if (entry != NULL) {
            delete entry;
         }
         i++;
      }
   };
   void Add(CONST_STRING_T var_spec, CONST_STRING_T fg_value, CONST_STRING_T bg_value)
   {
      cCompEntry * entry = new cCompEntry(var_spec, fg_value, bg_value);
      _CompEntries.push_back(entry);
   };
   COMP_ENTRY_LIST_T * Entries()
   {
      return &(_CompEntries);
   };
private:
   QString _GroupName;
   COMP_ENTRY_LIST_T _CompEntries; 
};
typedef std::map<STRING_T,cVarGroup*> VAR_GROUP_MAP_T;


class cVarGroups
{
public:
   cVarGroups() {};
   virtual ~cVarGroups()
   {
      VAR_GROUP_MAP_T::const_iterator i = _VarGroups.begin();
      while (i != _VarGroups.end()) {
         cVarGroup * var_group = (*i).second;
         if (var_group != NULL) {
            delete var_group;
         }
         i++;
      }
   };
   void Add(CONST_STRING_T group_name, CONST_STRING_T var_spec, CONST_STRING_T fg_value, CONST_STRING_T bg_value)
   {
      cVarGroup * var_group = VarGroup(group_name);
      if (var_group == NULL) {
         var_group = new cVarGroup(group_name);
         if (var_group != NULL) {
            var_group->Add(var_spec, fg_value, bg_value);
            _VarGroups[group_name] = var_group;
         }
      } else {
         var_group->Add(var_spec, fg_value, bg_value);
      }
   }
   COMP_ENTRY_LIST_T * Entries(CONST_STRING_T group_name)
   {
      cVarGroup * var_group = VarGroup(group_name);
      if (var_group == NULL) {
         return NULL;
      } else {
         return var_group->Entries();
      }
   };
   void GetGroupNames(STRING_LIST_T & group_names)
   {
      VAR_GROUP_MAP_T::const_iterator i = _VarGroups.begin();
      while (i != _VarGroups.end()) {
         group_names.push_back((*i).first);
         i++;
      }
   }
   void EraseEntries()
   {
      int size = _VarGroups.size();
      if (size) {
         _VarGroups.erase(_VarGroups.begin(), _VarGroups.end());
      }
   }
private:
   VAR_GROUP_MAP_T _VarGroups;
private:
   cVarGroup * VarGroup(CONST_STRING_T group_name)
   {
      VAR_GROUP_MAP_T::const_iterator i = _VarGroups.find(group_name);
      if (i == _VarGroups.end()) {
         return NULL;
      } else {
         return (*i).second;
      }
   };
};
#endif


CCompListView::CCompListView(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f) :
          CListView(parent, name)
{
   CONSTRUCT_WIDGET
#ifndef QT_PLUGIN
   _varGroups = new cVarGroups;
#endif
}

CCompListView::~CCompListView() 
{
}

void CCompListView::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CListView::mousePressEvent(e);
   }
}

void CCompListView::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      CListView::mouseReleaseEvent(e);
   }
}

void CCompListView::RefreshComparison()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Context != NULL) {
      STRING_T result = _Context->Compare();
      _varGroups->EraseEntries();

      char *pVarSpec = (char *)cSystemUtils::Alloc(0x100);
      char *pFgValue = (char *)cSystemUtils::Alloc(0x2200);
      char *pBgValue = (char *)cSystemUtils::Alloc(0x2200);
      const char * token = NULL;
      cTokenizer tokenizer(result.c_str(), result.size());
      token = tokenizer.GetToken("\n");
      while (token != NULL) {
         memset(pVarSpec, 0, sizeof(pVarSpec));
         memset(pFgValue, 0, sizeof(pFgValue));
         memset(pBgValue, 0, sizeof(pBgValue));
         int params = sscanf(token, "%[^(](%[^,],%[^)])", pVarSpec, pFgValue, pBgValue);
         if (params == 3) {
            STRING_T var_name = ParseVarName(pVarSpec);
   	        cVarDef* pVarDef = _Context->VarDef(var_name.c_str());
			if (pVarDef != NULL)
			{
			   if(strcmp(pVarDef->_Text.c_str(), "NO_LOG_TEXT") != 0)
			   { // Don't add if text == "NO_LOG_TEXT"
                  STRING_T database = pVarDef->_DatabaseName;
                  STRING_T trimed_fg_value = cStringUtils::Trim(pFgValue, '\"');
                  STRING_T trimed_bg_value = cStringUtils::Trim(pBgValue, '\"');

                  _varGroups->Add(database.c_str(), pVarSpec, trimed_fg_value.c_str(), trimed_bg_value.c_str());
			   }
            }
         }
         token = tokenizer.GetToken("\n");
      }

      if (pVarSpec != NULL) cSystemUtils::Free(pVarSpec);
      if (pFgValue != NULL) cSystemUtils::Free(pFgValue);
      if (pBgValue != NULL) cSystemUtils::Free(pBgValue);

      FillListView();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CCompListView::RefreshShadowComparison()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Context != NULL) {
      STRING_T result = _Context->Compare(CF_COMPARE_TO_SHADOW);
      _varGroups->EraseEntries();

      char *pVarSpec = (char *)cSystemUtils::Alloc(0x100);
      char *pFgValue = (char *)cSystemUtils::Alloc(0x2200);
      char *pBgValue = (char *)cSystemUtils::Alloc(0x2200);
      const char * token = NULL;
      cTokenizer tokenizer(result.c_str(), result.size());
      token = tokenizer.GetToken("\n");
      while (token != NULL) {
         memset(pVarSpec, 0, sizeof(pVarSpec));
         memset(pFgValue, 0, sizeof(pFgValue));
         memset(pBgValue, 0, sizeof(pBgValue));
         int params = sscanf(token, "%[^(](%[^,],%[^)])", pVarSpec, pFgValue, pBgValue);
         if (params == 3) {
            STRING_T var_name = ParseVarName(pVarSpec);
  		    cVarDef* pVarDef = _Context->VarDef(var_name.c_str());
			if (pVarDef != NULL)
			{
			   if(strcmp(pVarDef->_Text.c_str(), "NO_LOG_TEXT") != 0)
			   { // Don't add if text == "NO_LOG_TEXT"
                  STRING_T database = pVarDef->_DatabaseName;
                  STRING_T trimed_fg_value = cStringUtils::Trim(pFgValue, '\"');
                  STRING_T trimed_bg_value = cStringUtils::Trim(pBgValue, '\"');

                  _varGroups->Add(database.c_str(), pVarSpec, trimed_fg_value.c_str(), trimed_bg_value.c_str());
			   }
            }
         }
         token = tokenizer.GetToken("\n");
      }

      if (pVarSpec != NULL) cSystemUtils::Free(pVarSpec);
      if (pFgValue != NULL) cSystemUtils::Free(pFgValue);
      if (pBgValue != NULL) cSystemUtils::Free(pBgValue);

      FillListView();
   }
WMETHOD_VOID_EPILOG
#endif
}

// GUI related virtual methods

void CCompListView::View()
{
}

void CCompListView::DelayedLanguageChange()
{
}

// CCS related virtual methods

void CCompListView::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);

   // Set Alignment for column 1 and 2
   setColumnAlignment(1, Qt::AlignRight);
   setColumnAlignment(2, Qt::AlignRight);
WMETHOD_VOID_EPILOG
#endif
}

void CCompListView::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
#endif
}

void CCompListView::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
#endif
}

void CCompListView::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
#endif
}

QPixmap CCompListView::GroupPixmap(const QString & group_name)
{
   if (!_GroupName0Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName0Value) == 0) {
      return _Icon0Value;
   } else if (!_GroupName1Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName1Value) == 0) {
      return _Icon1Value;
   } else if (!_GroupName2Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName2Value) == 0) {
      return _Icon2Value;
   } else if (!_GroupName3Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName3Value) == 0) {
      return _Icon3Value;
   } else if (!_GroupName4Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName4Value) == 0) {
      return _Icon4Value;
   } else if (!_GroupName5Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName5Value) == 0) {
      return _Icon5Value;
   } else if (!_GroupName6Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName6Value) == 0) {
      return _Icon6Value;
   } else if (!_GroupName7Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName7Value) == 0) {
      return _Icon7Value;
   } else if (!_GroupName8Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName8Value) == 0) {
      return _Icon8Value;
   } else if (!_GroupName9Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName9Value) == 0) {
      return _Icon9Value;
   } else if (!_GroupName10Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName10Value) == 0) {
      return _Icon10Value;
   } else if (!_GroupName11Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName11Value) == 0) {
      return _Icon11Value;
   } else if (!_GroupName12Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName12Value) == 0) {
      return _Icon12Value;
   } else if (!_GroupName13Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName13Value) == 0) {
      return _Icon13Value;
   } else if (!_GroupName14Value.isNull() && _stricmp(CONST_STRING(group_name), (CONST_STRING_T)_GroupName14Value) == 0) {
      return _Icon14Value;
   } else {
      return _DefaultIconValue;
   }
   return _DefaultIconValue;
}

QString CCompListView::VarRefText(const QString & varRefSpec)
{
    QString description = "???";
#ifndef QT_PLUGIN
    cVarRef * var_ref = _Context->VarRef(CONST_STRING(varRefSpec));
    if (var_ref == NULL) {
        description = QApplication::translate("custom", CONST_STRING(varRefSpec));
    } else {
        description = RefText(_Context, var_ref);
    }
#endif

    return description;
}

void CCompListView::FillListView()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
    clear();
    STRING_LIST_T group_names;
    _varGroups->GetGroupNames(group_names);
    STRING_LIST_T::const_iterator g = group_names.begin();
    while (g != group_names.end()) {
       ListViewItem * node = new ListViewItem(this);
       node->setOpen(TRUE);
       COMP_ENTRY_LIST_T * entries = _varGroups->Entries((*g).c_str());
       COMP_ENTRY_LIST_T::const_iterator e = entries->begin();
       while (e != entries->end()) {
          cCompEntry * entry = *e;
          if (entry != NULL) {
             ListViewItem * item = new ListViewItem(node);
             item->setText(0, VarRefText(entry->_VarSpec.c_str()));
             item->setText(1, entry->_FgValue.c_str());
             item->setText(2, entry->_BgValue.c_str());
          }
          e++;
       }
       node->setPixmap(0, GroupPixmap((*g).c_str()));
       g++;
    }

    UCHAR_T index;
    for (index = 0; index < 3; ++index)
    { // Adjust columns
        setColumnWidthMode(index, ListView::Manual);
        resizeColumnToContents(index);
    }

    if (getAutoAdjustColumnSize() == false)
    {
        adjustColumnWidths();
    }

WMETHOD_VOID_EPILOG
#endif
}

//////////////////////////////////////////////////////////////////////
// slots
//////////////////////////////////////////////////////////////////////
void CCompListView::languageChange()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
    FillListView();
WMETHOD_VOID_EPILOG
#endif 

}
