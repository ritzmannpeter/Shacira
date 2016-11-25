
#include "FirstHeader.h"
#include "csubfilelist.h"
#include "Conversion/cFMFatFile.h"
#include "Conversion/cSubfile.h"
#include "Conversion/cHeader.h"
#include "Conversion/cHeatGroup.h"
#include "Conversion/cHeatZone.h"
#include "Conversion/cHeatText.h"
#include "Conversion/cProcessGraphic.h"
#include "Conversion/cRegister.h"
#include "Conversion/cTextVar.h"
#include "Conversion/cFMTestHandler.h"
#include <qapplication.h>
#include <qdatetime.h>
#include <qlabel.h>
#include <qfiledialog.h>
#include "Control/LocalDatabase/cLocalContext.h"
#include "Control/LocalDatabase/cLocalVariable.h"
#include "System/Sys/cFileSystemUtils.h"

#include "cRegDescription.h"
/// global object that holds register descriptions (additional informations like text and precision)
static cRegDescriptions _RegDescriptions;

extern void Out(const char * text);
extern void ClearOutput();
extern void ClearList();

#define HEADER    1
#define SUBFILE   2


#define INIT_FILE_OBJECT() \
   _Type = 0; \
   _Header = NULL; \
   _Subfile = NULL;

#define SHOW_INT_PG(name) \
      sprintf(text, "%s = %d", #name, (int)process_graphic->name); \
      file_object = new CFileObject(root, text, prev_object); \
      prev_object = file_object;
#define SHOW_INT_PG_ARRAY(name,i) \
      sprintf(text, "%s = %d", #name, (int)process_graphic->name[i]); \
      file_object = new CFileObject(root, text, prev_object); \
      prev_object = file_object;
#define SHOW_INT(name) \
      sprintf(text, "%s = %d", #name, (int)header->name); \
      file_object = new CFileObject(root, text, prev_object); \
      prev_object = file_object;
#define SHOW_INT_ARRAY(name,i) \
      sprintf(text, "%s = %d", #name, (int)header->name[i]); \
      file_object = new CFileObject(root, text, prev_object); \
      prev_object = file_object;
#define SHOW_STRING(name) \
      sprintf(text, "%s = \"%s\"", #name, (const char*)header->name.c_str()); \
      file_object = new CFileObject(root, text, prev_object); \
      prev_object = file_object;

class CFileObject;
typedef std::map<STRING_T, CFileObject*> ITEM_MAP_T;
class CFileObject : public QListViewItem
{
public:
   CFileObject(CFileObject * parent, const char * text, CFileObject * after = NULL)
      : QListViewItem(parent, after)
   {
INIT_FILE_OBJECT();
      setText(0, text);
   };
   CFileObject(QListView * parent, cHeader * header)
      : QListViewItem(parent)
   {
INIT_FILE_OBJECT();
      _Type = HEADER;
      _Header = header;
      CFileObject * root = NULL;
      CFileObject * file_object = NULL;
      CFileObject * prev_object = NULL;
      setText(0, "0: Datei Header");
      char text[0x200] = {0};
      int i = 0;
      for (i=0; i<header->_MaxAgg; i++) {
         sprintf(text, "Aggregat %d", i+1); \
         root = new CFileObject(this, text); \
         SHOW_INT_ARRAY(_MouldInPres,i);
         SHOW_INT_ARRAY(_MaxSpritzDruck,i);
         SHOW_INT_ARRAY(_Diameter,i);
         SHOW_INT_ARRAY(_PresConst,i);
         SHOW_INT_ARRAY(_Aggregat,i);
         SHOW_INT_ARRAY(_HeatZoneCount,i);
         SHOW_INT_ARRAY(_ScrewSuckBack,i);
         SHOW_INT_ARRAY(_PlastWay,i);
      }
      root = new CFileObject(this, "Maschine"); \
      SHOW_INT(_Version);
      SHOW_INT(_HeaderSize);
      SHOW_INT(_FileType);
//   cTimeObject _Date;              /* Datum und Uhrzeit */
      SHOW_INT(_RegType);
      SHOW_STRING(_InfoText);
      SHOW_STRING(_MashType);
      SHOW_STRING(_MatNr);
      SHOW_STRING(_ToolNr);
      SHOW_INT(_ProgNr);
      SHOW_INT(_MashSize);
      SHOW_INT(_MouldOpWay);
      SHOW_INT(_VersMash);
      SHOW_INT(_VersStruct);
      SHOW_INT(_VersExtra);
      SHOW_INT(_MaxAgg);
      setOpen(TRUE);
   };
   CFileObject(QListView * parent, cSubfile * subfile)
      : QListViewItem(parent)
   {
INIT_FILE_OBJECT();
      _Type = SUBFILE;
      _Subfile = subfile;
      char text[0x200] = {0};
      sprintf(text, "%s (%d,%d)", _Subfile->_Description.c_str(),
                                  _Subfile->_Offset,
                                  _Subfile->_Size);
//      setText(0, _Subfile->_Description.c_str());
      setText(0, text);
      CFileObject * root = NULL;
      CFileObject * file_object = NULL;
      CFileObject * prev_object = NULL;
      HEATGROUP_MAP_T heatgroup_map;
      _Subfile->HeatGroupMap(heatgroup_map);
      if (heatgroup_map.size() > 0) {
         root = new CFileObject(this, "Heizung");
      }
      CFileObject * heating = root;
      HEATGROUP_MAP_T::const_iterator k = heatgroup_map.begin();
      while (k != heatgroup_map.end()) {
         cHeatGroup * heat_group = (*k).second;
         if (heat_group != NULL) {
            root = new CFileObject(heating, heat_group->GroupName(heat_group->_RegNo));
            ZONE_MAP_T zone_map;
            heat_group->ZoneMap(zone_map);
            ZONE_MAP_T::const_iterator z = zone_map.begin();
            while (z != zone_map.end()) {
               cHeatZone * heat_zone = (*z).second;
               if (heat_zone != NULL) {
                  char text[0x200] = {0};
                  STRING_T zone_name = heat_zone->_ZoneName;
                  if (zone_name.size() > 0) {
                     sprintf(text, "%s: Set = %d,  TolUpNarrow = %d,  TolUpWide = %d,  TolDownNarrow = %d,  TolDownWide = %d",
                             zone_name.c_str(),
                             heat_zone->Set(),
                             heat_zone->TolUpNarrow(),
                             heat_zone->TolUpWide(),
                             heat_zone->TolDownNarrow(),
                             heat_zone->TolDownWide());
                  } else {
                     sprintf(text, "Zone %d: Set = %d,  TolUpNarrow = %d,  TolUpWide = %d,  TolDownNarrow = %d,  TolDownWide = %d",
                             heat_zone->_ZoneId,
                             heat_zone->Set(),
                             heat_zone->TolUpNarrow(),
                             heat_zone->TolUpWide(),
                             heat_zone->TolDownNarrow(),
                             heat_zone->TolDownWide());
                  }
                  file_object = new CFileObject(root, text, prev_object);
                  prev_object = file_object;
               }
               z++;
            }
         }
         k++;
      }
      REGISTER_MAP_T reg_map;
      _Subfile->RegisterMap(reg_map);
      if (reg_map.size() > 0) {
         root = new CFileObject(this, "Register");
      }
      REGISTER_MAP_T::const_iterator i = reg_map.begin();
      while (i != reg_map.end()) {
         cRegister * reg = (*i).second;
         if (reg != NULL &&
             reg->_HasDescription) {
            char text[0x200] = {0};
            int elements = reg->_Elements;
            if (elements == 1) {
               sprintf(text, "%d = %s   (%s)", reg->_RegNo, reg->StringValue().c_str(), reg->_Text.c_str());
            } else {
               STRING_T value_list;
               int i = 0;
               for (i=0; i<elements; i++) {
                  if (i != 0) {
                     value_list += ", ";
                  }
                  char value[0x40] = {0};
                  sprintf(value, "%d", reg->LongValue(i));
                  value_list += value;
               }
               sprintf(text, "%d = {%s}   (%s)", reg->_RegNo, value_list.c_str(), reg->_Text.c_str());
            }
            file_object = new CFileObject(root, text, prev_object);
            prev_object = file_object;
         }
         i++;
      }
      TEXTVAR_MAP_T textvar_map;
      _Subfile->TextVarMap(textvar_map);
      if (textvar_map.size() > 0) {
         root = new CFileObject(this, "Texte");
      }
      TEXTVAR_MAP_T::const_iterator j = textvar_map.begin();
      while (j != textvar_map.end()) {
         cTextVar * text_var = (*j).second;
         if (text_var != NULL) {
            char text[0x100] = {0};
            STRING_T var_text = text_var->Text();
            if (var_text.size() > 100) {
               char _var_text[51] = {0};
               memcpy(_var_text, var_text.c_str(), 50);
               sprintf(text, "%d = \"%s\" (%d)", text_var->_TextId, _var_text, var_text.size());
            } else {
               sprintf(text, "%d = \"%s\"", text_var->_TextId, var_text.c_str());
            }
            file_object = new CFileObject(root, text, prev_object);
            prev_object = file_object;
         }
         j++;
      }
      HEATTEXT_MAP_T heattext_map;
      _Subfile->HeatTextMap(heattext_map);
      if (heattext_map.size() > 0) {
         root = new CFileObject(this, "Heizungstexte");
      }
      HEATTEXT_MAP_T::const_iterator l = heattext_map.begin();
      while (l != heattext_map.end()) {
         cHeatText * heat_text = (*l).second;
         if (heat_text != NULL) {
         }
         l++;
      }
      cProcessGraphic * process_graphic = subfile->ProcessGraphic();
      if (process_graphic != NULL) {
         char text[0x200] = {0};
         root = new CFileObject(this, "Kanal 2");
         SHOW_INT_PG_ARRAY(_Soll_chan,1);
         SHOW_INT_PG_ARRAY(_Soll_max,1);
         SHOW_INT_PG_ARRAY(_Tol,1);
         root = new CFileObject(this, "Kanal 1");
         SHOW_INT_PG_ARRAY(_Soll_chan,0);
         SHOW_INT_PG_ARRAY(_Soll_max,0);
         SHOW_INT_PG_ARRAY(_Tol,0);
         root = new CFileObject(this, "Betriebsmodus");
         SHOW_INT_PG(_Mode);
         SHOW_INT_PG(_Delay);
         SHOW_INT_PG(_Time);
         SHOW_INT_PG(_Mint);
         SHOW_INT_PG(_Vinter);
      }
      setOpen(TRUE);
   };
   CFileObject(CFileObject * parent, cRegister * reg)
      : QListViewItem(parent)
   {
INIT_FILE_OBJECT();
   };
   CFileObject(CFileObject * parent, cTextVar * text_var)
      : QListViewItem(parent)
   {
   };
   CFileObject(CFileObject * parent, cHeatZone * heat_zone)
      : QListViewItem(parent)
   {
INIT_FILE_OBJECT();
   };
   CFileObject(CFileObject * parent, cHeatText * heat_text)
      : QListViewItem(parent)
   {
INIT_FILE_OBJECT();
   };
   CFileObject(CFileObject * parent, cProcessGraphic * process_graphic)
      : QListViewItem(parent)
   {
INIT_FILE_OBJECT();
   };

   ~CFileObject()
   {
   };
   cSubfile * Subfile()
   {
   };
   STRING_T SubfileName()
   {
   };
   static CFileObject * Item()
   {
      return NULL;
   };
private:
   int _Type;
   cHeader * _Header;
   cSubfile * _Subfile;
public:
};

CSubfileList::CSubfileList(QWidget * parent, DatasetViewerForm * viewer)
 : QListView(parent)
{
   _Viewer = viewer;
   STRING_T default_template = cFileSystemUtils::FullPath("default.tpl");
   STRING_T default_regtext = cFileSystemUtils::FullPath("default.txt");
   if (cFileSystemUtils::FileExists(default_template.c_str())) {
      BOOL_T success = false;
      _Context = new cLocalContext;
      try {
         _Context->ParseDatabaseFromFile(default_template.c_str());
         success = true;
      } catch (cError & e) {
         Out((const char*)e);
      } catch (...) {
         Out("unhandled exception when loading template");
      }
      if (success) {
         _Context->Create();
         _Viewer->tpl_file->setText(default_template.c_str());
         _Viewer->regtext_file->setText(default_regtext.c_str());
      }
   }
   addColumn("Teildateien");
   setSorting(-1);
}

CSubfileList::~CSubfileList()
{
}

void CSubfileList::Clear()
{
   clear();
}

void CSubfileList::SelectFile()
{
   ClearOutput();
   ClearList();
   _Viewer->legacy_file->setText("");
   char text[0x200] = {0};
   QFileDialog dialog("", "material.*", this,
                      "Werkzeugdatensatz wählen",
                      TRUE);
   int rc = dialog.exec();
   if (rc != 0) {
      QCString sel_file = dialog.selectedFile();
      sprintf(text, "loading %s ...", (const char *)sel_file);
      Out(text);
      cFMFatFile fat_file((const char*)sel_file);
      if (fat_file.Parse()) {
         _RegDescriptions.Load((const char *)_Viewer->regtext_file->text());
         REGISTER_LIST_T reg_list;
         fat_file.Registers(reg_list);
         REGISTER_LIST_T::const_iterator r = reg_list.begin();
         while (r != reg_list.end()) {
            cRegister * reg = (*r);
            /// Get register description
            /// next line should be activated when the displayed
            /// registers should be filtered
            /// if (_RegDescriptions.Present(reg->_RegNo)) {
            if (true) {
               STRING_T text = _RegDescriptions.Text(reg->_RegNo);
               UCHAR_T precision = _RegDescriptions.Precision(reg->_RegNo);
               reg->_Text = text;
               reg->_Precision = precision;
               reg->_HasDescription = true;
            }
            r++;
         }
         sprintf(text, "file %s is valid\n", (const char*)sel_file);
         cHeader * header = fat_file.Header();
         SUBFILE_LIST_T subfiles;
         SUBFILE_LIST_T subfiles_reverse;
         fat_file.Subfiles(subfiles);
         SUBFILE_LIST_T::const_iterator i = subfiles.begin();
         while (i != subfiles.end()) {
            cSubfile * subfile = (*i);
            subfiles_reverse.push_front(subfile);
            i++;
         }
         i = subfiles_reverse.begin();
         while (i != subfiles_reverse.end()) {
            cSubfile * subfile = (*i);
            CFileObject * file_obj = new CFileObject(this, subfile);
            i++;
         }
         CFileObject * file_obj = new CFileObject(this, header);
         _Viewer->legacy_file->setText((const char *)sel_file);
         if (_Context != NULL) {
            cTransformationHandler * handler = new cFMTestHandler(&fat_file, _Context);
            if (handler->Process()) {
               STRING_T output;
               _Context->ReadFile("", "", output);
               FILE * stream = fopen("dataset.mld", "w");
               if (stream != NULL) {
                  fprintf(stream, "%s", output.c_str());
                  fclose(stream);
               }
            }
         }
      } else {
         sprintf(text, "file %s is no valid file\n", (const char*)sel_file);
      }
      Out(text);
   }
}

void CSubfileList::SelectTemplate()
{
   ClearOutput();
   char text[0x200] = {0};
   _Viewer->tpl_file->setText("");
   QFileDialog dialog("", "*.tpl", this,
                      "Template-Datei wählen",
                      TRUE);
   int rc = dialog.exec();
   if (rc != 0) {
      BOOL_T success = false;
      QCString sel_file = dialog.selectedFile();
      _Context = new cLocalContext;
      try {
         _Context->ParseDatabaseFromFile((const char *)sel_file);
         success = true;
      } catch (cError & e) {
         Out((const char*)e);
      } catch (...) {
         Out("unhandled exception when loading template");
      }
      if (success) {
         _Context->Create();
         _Viewer->tpl_file->setText((const char *)sel_file);
      } else {
         _Viewer->tpl_file->setText("failed to parse template");
      }
   }
}

void CSubfileList::SelectRegtext()
{
   ClearOutput();
   char text[0x200] = {0};
   _Viewer->regtext_file->setText("");
   QFileDialog dialog("", "*.txt", this,
                      "Register-Text-Datei wählen",
                      TRUE);
   int rc = dialog.exec();
   if (rc != 0) {
      BOOL_T success = false;
      QCString sel_file = dialog.selectedFile();
      _Viewer->regtext_file->setText((const char *)sel_file);
   }
}

