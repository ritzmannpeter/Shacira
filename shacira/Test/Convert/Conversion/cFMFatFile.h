
#ifndef _cFMFatFile_h_
#define _cFMFatFile_h_

#include "FileDefinitions.h"
#include "FileObjects.h"
#include "cHeader.h"
#include "cHeatGroup.h"
#include "cHeatZone.h"
#include "cHeatText.h"
#include "cRegister.h"
#include "cSubfile.h"
#include "cTextVar.h"
#include "cProcessGraphic.h"
#include "cNewProcessGraphic.h"
#include "cEM17Data.h"

class cFMFatFile {
public:
   cFMFatFile(CONST_STRING_T file);
   virtual ~cFMFatFile();
   BOOL_T Parse();
   cHeader * Header();
   cSubfile * Subfile(int id);
   void Subfiles(SUBFILE_LIST_T & subfiles);
   cRegister * Register(int id);
   void Registers(REGISTER_LIST_T & registers);
   cTextVar * TextVar(int id);
   void TextVars(TEXTVAR_LIST_T & text_vars);
   cHeatGroup * HeatGroup(int id);
   void HeatGroups(HEATGROUP_LIST_T & heat_groups);
   cProcessGraphic * ProcessGraphic();
   cNewProcessGraphic * NewProcessGraphic();
   cEM17Data * EM17Data();
   void Print(STRING_T & doc);
   static void Error(int line, const char * fmt_str, ...);
   static void Info(const char * fmt_str, ...);
private:
   STRING_T _File;
   cHeader * _Header;
   SUBFILE_MAP_T _Subfiles;
   REGISTER_MAP_T _Registers;
   TEXTVAR_MAP_T _TextVars;
   HEATGROUP_MAP_T _HeatGroups;
   HEATTEXT_MAP_T _HeatTexts;
   cProcessGraphic * _ProcessGraphic;
   cNewProcessGraphic * _NewProcessGraphic;
   cEM17Data * _EM17Data;
   cPositionedBuffer * _FileBuffer;
private:
   BOOL_T Load();
   BOOL_T ReadHeader();
   BOOL_T CheckHeader();
   BOOL_T ReadSubfiles();
   BOOL_T ReadSubfileContent(cSubfile * subfile);
   BOOL_T ReadIqtRegs(cSubfile * subfile, int subfile_id);
   BOOL_T ReadIscosRegs(cSubfile * subfile, int subfile_id);
   BOOL_T ReadIscosBits(cSubfile * subfile, int subfile_id);
   BOOL_T ReadTexts(cSubfile * subfile, int subfile_id);
   BOOL_T ReadRegs(cSubfile * subfile, int subfile_id);
   BOOL_T ReadHeatGroups(cSubfile * subfile, int subfile_id, unsigned_16 reg_no, unsigned_8 reg_type);
   BOOL_T ReadHeatTexts(cSubfile * subfile, int subfile_id);
   BOOL_T ReadPG(cSubfile * subfile, int subfile_id);
   BOOL_T ReadPGNew(cSubfile * subfile, int subfile_id);
   BOOL_T ReadEM17(cSubfile * subfile, int subfile_id);
   void SetHeader(cHeader * header);
   void AddRegister(cRegister * reg);
   void AddTextVar(cTextVar * text_var);
   void AddHeatGroup(cHeatGroup * heat_group);
   void AddHeatText(cHeatText * heat_text);
   void AddSubfile(cSubfile * subfile);
};


#endif




