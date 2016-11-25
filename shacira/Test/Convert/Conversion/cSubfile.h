
#ifndef _cSubfile_h_
#define _cSubfile_h_

#include "FileDefinitions.h"
#include "FileObjects.h"
#include "cPositionedBuffer.h"
class cFMFatFile;

class cProcessGraphic;
class cNewProcessGraphic;
class cEM17Data;

class cSubfile {
public:
   cSubfile(cFMFatFile * file, SUBFILE_T * subfile);
   virtual ~cSubfile();
   void Print(STRING_T & doc);
   cPositionedBuffer * Buffer();
   void AddRegister(cRegister * reg);
   void AddTextVar(cTextVar * text_var);
   void AddHeatGroup(cHeatGroup * heat_group);
   void AddHeatText(cHeatText * heat_text);
   void SetProcessGraphic(cProcessGraphic * process_graphic);
   void SetNewProcessGraphic(cNewProcessGraphic * process_graphic);
   void SetEM17Data(cEM17Data * em17_data);
   void RegisterMap(REGISTER_MAP_T & regs);
   void TextVarMap(TEXTVAR_MAP_T & text_vars);
   void HeatGroupMap(HEATGROUP_MAP_T & heat_groups);
   void HeatTextMap(HEATTEXT_MAP_T & heat_texts);
   cProcessGraphic * ProcessGraphic();
   cNewProcessGraphic * NewProcessGraphic();
   cEM17Data * EM17Data();
public:
   ULONG_T _Id;
public:
   ULONG_T _Offset;
   ULONG_T _Size;
   STRING_T _Description;
   cPositionedBuffer * _Buffer;
private:
   cFMFatFile * _File;
   REGISTER_MAP_T _RegisterMap;
   TEXTVAR_MAP_T _TextVarMap;
   HEATGROUP_MAP_T _HeatGroupMap;
   HEATTEXT_MAP_T _HeatTextMap;
   cProcessGraphic * _ProcessGraphic;
   cNewProcessGraphic * _NewProcessGraphic;
   cEM17Data * _EM17Data;
};

#endif





