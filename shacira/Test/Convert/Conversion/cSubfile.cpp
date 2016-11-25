
#include "FirstHeader.h"
#include "cSubfile.h"
#include "cHeatGroup.h"
#include "cHeatZone.h"
#include "cHeatText.h"
#include "cRegister.h"
#include "cSubfile.h"
#include "cTextVar.h"
#include "cProcessGraphic.h"
#include "cEM17Data.h"
#include "cFMFatFile.h"

cSubfile::cSubfile(cFMFatFile * file, SUBFILE_T * subfile)
{
   _File = file;
   _ProcessGraphic = NULL;
   _NewProcessGraphic = NULL;
   _EM17Data = NULL;
   _Id = subfile->subfile_id;
   _Offset = subfile->offset;
   _Size = subfile->size;
   _Description = subfile->description;
   _Buffer = new cPositionedBuffer(_Size);
   _Buffer->Set(subfile->buffer, _Size);
}

cSubfile::~cSubfile()
{
   if (_Buffer != NULL) {
      delete _Buffer;
   }
}

void cSubfile::Print(STRING_T & doc)
{
static char temp_buf[0x2000] = {0};
   sprintf(temp_buf, "subfile %d name %s offset %d size %d\n",
           _Id, _Description.c_str(), _Offset, _Size);
   doc += temp_buf;
}

cPositionedBuffer * cSubfile::Buffer()
{
   return _Buffer;
}

void cSubfile::AddRegister(cRegister * reg)
{
   int id = reg->_RegNo;
   _RegisterMap[id] = reg;
}

void cSubfile::AddTextVar(cTextVar * text_var)
{
   int id = text_var->_TextId;
   _TextVarMap[id] = text_var;
}

void cSubfile::AddHeatGroup(cHeatGroup * heat_group)
{
   int id = heat_group->_GroupId;
   _HeatGroupMap[id] = heat_group;
}

void cSubfile::AddHeatText(cHeatText * heat_text)
{
}

void cSubfile::SetProcessGraphic(cProcessGraphic * process_graphic)
{
   _ProcessGraphic = process_graphic;
}

void cSubfile::SetNewProcessGraphic(cNewProcessGraphic * process_graphic)
{
   _NewProcessGraphic = process_graphic;
}

void cSubfile::SetEM17Data(cEM17Data * em17_data)
{
   _EM17Data = em17_data;
}

void cSubfile::RegisterMap(REGISTER_MAP_T & regs)
{
   regs = _RegisterMap;
}

void cSubfile::TextVarMap(TEXTVAR_MAP_T & text_vars)
{
   text_vars = _TextVarMap;
}

void cSubfile::HeatGroupMap(HEATGROUP_MAP_T & heat_groups)
{
   heat_groups = _HeatGroupMap;
}

void cSubfile::HeatTextMap(HEATTEXT_MAP_T & heat_texts)
{
   heat_texts = _HeatTextMap;
}

cProcessGraphic * cSubfile::ProcessGraphic()
{
   return _ProcessGraphic;
}

cNewProcessGraphic * cSubfile::NewProcessGraphic()
{
   return _NewProcessGraphic;
}

cEM17Data * cSubfile::EM17Data()
{
   return _EM17Data;
}

