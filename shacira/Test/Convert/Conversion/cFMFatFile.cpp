
#include "FirstHeader.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Sys/cSHFile.h"
#include "cFMFatFile.h"

extern void Out(const char * text);

static const SUBFILE_TAB FullFile[] =
{
   { DISK_ID_SETUP,        TAB_IQTREG,   "Einricht-Register" },
   { DISK_ID_SETUP_TEXT,   TAB_TEXT,     "Einricht-Texte" },
   { DISK_ID_FOT,          TAB_IQTREG,   "frei zusammenst. Seiten" },
   { DISK_ID_IQTREG,       TAB_IQTREG,   "IQT-Register" },
   { DISK_ID_ISCOSREG,     TAB_ISCOSREG, "SPS-Register" },
   { DISK_ID_ISCOSBIT,     TAB_ISCOSBIT, "SPS-Bits" },
   { DISK_ID_TEXT,         TAB_TEXT,     "freie Texte" },
   { DISK_ID_HEATTEXT,     TAB_HEATTEXT, "Heizungstexte" },
   { DISK_ID_PG,           TAB_PG,       "Prozeßgrafik kompatible Version" },
   { DISK_ID_PG_IQTREG,    TAB_IQTREG,   "Prozeßgrafik IQT-Register" },
   { DISK_ID_PG_ISCOSREG,  TAB_ISCOSREG, "Prozeßgrafik SPS-Register" },
   { DISK_ID_PG_NEW,       TAB_PG_NEW,   "Prozeßgrafik neue Version" },
   { DISK_ID_ROB_REG,      TAB_IQTREG, "Roboter-Register" },
   { DISK_ID_ROB_TEXT,     TAB_TEXT,   "Roboter-Texte" },
   { DISK_ID_ABGL,         TAB_IQTREG, "Maschinenabgleich-Register" },
   { DISK_ID_CORE_IQTREG,    TAB_IQTREG,   "frei programmierbare Kernzüge IQT-Register" },
   { DISK_ID_CORE_ISCOSREG,  TAB_ISCOSREG, "frei programmierbare Kernzüge SPS-Register" },
   { DISK_ID_EM17_ROB,  TAB_EM17, "Euromap 17 Roboterdaten" }
};
#define CONFIG_ENTRIES  (sizeof(FullFile)/sizeof(SUBFILE_TAB))

static const char * FileName(int id)
{
   int i;
   for (i=0; i<CONFIG_ENTRIES; i++) {
      if (id == FullFile[i].Id) {
         return FullFile[i].Text;
      }
   }
   return "unknown";
}

static STRING_T FileSpec(int id)
{
   char spec[0x200] = {0};
   sprintf(spec, "%d: %s", id, FileName(id));
   return spec;
}

static int FileType(int id)
{
   int i;
   for (i=0; i<CONFIG_ENTRIES; i++) {
      if (id == FullFile[i].Id) {
         return FullFile[i].Tab;
      }
   }
   return -1;
}

#define TEXT_BUF_SIZE   0x400

static int DeCompressText(unsigned_8 * text, unsigned_8 * comp_text, int len)
{
   int i = 0, j = 0;
   unsigned_8 count;
   while (i < len) {
      if ((comp_text[i] & 0x80) == 0x80) {
         for (count=comp_text[i+1]; count>0; count-- ) {
            text[j++] = comp_text[i] & 0x7f;     /* - 128 */
         }
         i += 2;
      } else {
         text[j++] = comp_text[i++];
      }
   }
   return j;
}

static int Compresstext(unsigned_8 * comp_text, unsigned_8 * text, int length)
{
   int i = 0, j = 0, count;
   while (i < length) {
      if (i+1<length && text[i]<128 && text[i] == text[i+1]) {
         // at least 2 characters are equal
         for (count=2;
              i+count<length && text[i]==text[i+count] && count<255;
              count++) {
         }
         comp_text[j++] = text[i] | 0x80;     /* Zeichen + 128 */
         comp_text[j++] = count;              /* Anzahl Zeichen */
         i += count;
      } else {
         comp_text[j++] = text[i++] & 0x7F;   /* hoechstes Bit ausmaskieren */
      }
   }
   return j;
}

static int RegSize(unsigned_8 reg_type)
{
   reg_type = (int)GET_REG_TYPE(reg_type);
   switch (reg_type) {
   case REG_INT: return 2;
   case REG_DINT: return 4;
   case REG_LONG: return 4;
   case REG_INT10: return 20;
   case REG_INT20: return 40;
   case REG_LONG10: return 40;
   case REG_LONG20: return 80;
   default: return 0;
   }
}

static int ValueSize(unsigned_8 reg_type)
{
   reg_type = (int)GET_REG_TYPE(reg_type);
   switch(reg_type) {
   case REG_INT: return 2;
   case REG_DINT: return 4;
   case REG_LONG: return 4;
   case REG_INT10: return 2;
   case REG_INT20: return 2;
   case REG_LONG10: return 4;
   case REG_LONG20: return 4;
   default: return 0;
   }
}

#define BUFFER_SIZE     0x1000000

cFMFatFile::cFMFatFile(CONST_STRING_T file)
{
   _File = cFileSystemUtils::FullPath(file);
   _Header = NULL;
   _FileBuffer = NULL;
   _ProcessGraphic = NULL;
   _NewProcessGraphic = NULL;
   _EM17Data = NULL;
   cPositionedBuffer * _FileBuffer;
   Load();
}

cFMFatFile::~cFMFatFile()
{
}

BOOL_T cFMFatFile::Parse()
{
   if (_FileBuffer == NULL) {
      Error(__LINE__, "no file buffer");
      return false;
   }
   if (ReadHeader()) {
      if (ReadSubfiles()) {
         return true;
      }
   }
   Error(__LINE__, "parse failed");
   return false;
}

cHeader * cFMFatFile::Header()
{
   return _Header;
}

cSubfile * cFMFatFile::Subfile(int id)
{
   SUBFILE_MAP_T::const_iterator i = _Subfiles.find(id);
   if (i == _Subfiles.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cFMFatFile::Subfiles(SUBFILE_LIST_T & subfiles)
{
   SUBFILE_MAP_T::const_iterator i = _Subfiles.begin();
   while (i != _Subfiles.end()) {
      subfiles.push_back((*i).second);
      i++;
   }
}

cRegister * cFMFatFile::Register(int id)
{
   REGISTER_MAP_T::const_iterator i = _Registers.find(id);
   if (i == _Registers.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cFMFatFile::Registers(REGISTER_LIST_T & registers)
{
   REGISTER_MAP_T::const_iterator i = _Registers.begin();
   while (i != _Registers.end()) {
      registers.push_back((*i).second);
      i++;
   }
}

cTextVar * cFMFatFile::TextVar(int id)
{
   TEXTVAR_MAP_T::const_iterator i = _TextVars.find(id);
   if (i == _TextVars.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cFMFatFile::TextVars(TEXTVAR_LIST_T & text_vars)
{
   TEXTVAR_MAP_T::const_iterator i = _TextVars.begin();
   while (i != _TextVars.end()) {
      text_vars.push_back((*i).second);
      i++;
   }
}

cHeatGroup * cFMFatFile::HeatGroup(int id)
{
   HEATGROUP_MAP_T::const_iterator i = _HeatGroups.find(id);
   if (i == _HeatGroups.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cFMFatFile::HeatGroups(HEATGROUP_LIST_T & heat_groups)
{
   HEATGROUP_MAP_T::const_iterator i = _HeatGroups.begin();
   while (i != _HeatGroups.end()) {
      heat_groups.push_back((*i).second);
      i++;
   }
}

cProcessGraphic * cFMFatFile::ProcessGraphic()
{
   return _ProcessGraphic;
}

cNewProcessGraphic * cFMFatFile::NewProcessGraphic()
{
   return _NewProcessGraphic;
}

cEM17Data * cFMFatFile::EM17Data()
{
   return _EM17Data;
}

void cFMFatFile::Print(STRING_T & doc)
{
   _Header->Print(doc);
   SUBFILE_MAP_T::const_iterator sfi = _Subfiles.begin();
   while (sfi != _Subfiles.end()) {
      (*sfi).second->Print(doc);
      sfi++;
   }
   REGISTER_MAP_T::const_iterator ri = _Registers.begin();
   while (ri != _Registers.end()) {
      (*ri).second->Print(doc);
      ri++;
   }
   TEXTVAR_MAP_T::const_iterator tvi = _TextVars.begin();
   while (tvi != _TextVars.end()) {
      (*tvi).second->Print(doc);
      tvi++;
   }
   HEATGROUP_MAP_T::const_iterator hgi = _HeatGroups.begin();
   while (hgi != _HeatGroups.end()) {
      (*hgi).second->Print(doc);
      hgi++;
   }
   _ProcessGraphic->Print(doc);
   _NewProcessGraphic->Print(doc);
   _EM17Data->Print(doc);
}

static char _Text[0x2000] = {0};
static char _OutText[0x2000] = {0};
void cFMFatFile::Error(int line, const char * fmt_str, ...)
{
   va_list args;
   va_start(args, fmt_str);
   vsprintf(_Text, fmt_str, args);
   va_end(args);
   sprintf(_OutText, "error: %s in line %d", _Text, line);
   Out(_OutText);
}

void cFMFatFile::Info(const char * fmt_str, ...)
{
   va_list args;
   va_start(args, fmt_str);
   vsprintf(_Text, fmt_str, args);
   va_end(args);
   Out(_Text);
}

/// private methods

BOOL_T cFMFatFile::Load()
{
   if (_File.size() == 0) {
      Error(__LINE__, "file size is 0");
      return false;
   }
   if (!cFileSystemUtils::FileExists(_File.c_str())) {
      Error(__LINE__, "file %s not found", _File.c_str());
      return false;
   }
   UCHAR_T * temp_buf = (UCHAR_T*)cSystemUtils::Alloc(BUFFER_SIZE);
   UCHAR_T * dst_ptr = temp_buf;
   cSHFile file(_File.c_str());
   if (file.Open(FILE_ACCESS_READ_ONLY|FILE_MODE_BINARY)) {
      UCHAR_T buf[0x200] = {0};
      ULONG_T file_size = 0;
      ULONG_T nread = file.Read(buf, sizeof(buf), sizeof(buf));
      while (nread > 0) {
         memcpy(dst_ptr, buf, nread);
         file_size += nread;
         dst_ptr += nread;
         nread = file.Read(buf, sizeof(buf), sizeof(buf));
      }
      file.Close();
      _FileBuffer = new cPositionedBuffer(file_size);
      _FileBuffer->Set(temp_buf, file_size);
      cSystemUtils::Free(temp_buf);
      return true;
   } else {
      cSystemUtils::Free(temp_buf);
      Error(__LINE__, "failed to open %s", _File.c_str());
      return false;
   }
}

BOOL_T cFMFatFile::ReadHeader()
{
   FILE_HEADER_T header = {0};
   if (_FileBuffer->Get(&header, sizeof(header))) {
      ULONG_T header_size = header.HeaderSize;
      cHeader * _header = new cHeader(this, &header);
      SetHeader(_header);
      _FileBuffer->Seek(header_size);
      return CheckHeader();
   }
   return false;
}

BOOL_T cFMFatFile::CheckHeader()
{
   return true;
}

BOOL_T cFMFatFile::ReadSubfiles()
{
   unsigned_16 subfile_tab_id = 0;
   unsigned_16 subfile_id = 0;
   signed_16 subfiles = 0;
   cPositionedBuffer * subfile_buf = NULL;
   SUBFILE_TAB_T * subfile_tab = NULL;
   SUBFILE_T _subfile = {0};

   if (!_FileBuffer->Get(&subfile_tab_id, sizeof(subfile_tab_id))) {
      return false;
   }
   if (subfile_tab_id != DISK_ID_PTRTAB) {
      Error(__LINE__, "missing pointer table");
//      return _E_SUBFILE_ID_MATCH;
      return false;
   }
   if (!_FileBuffer->Get(&subfiles, sizeof(subfiles))) {
      return false;
   }
   if (subfiles < 0 || subfiles > MAX_SUBFILES) {
      Error(__LINE__, "invalid number of subfiles %d", subfiles);
//      return _E_SUBFILE_COUNT;
      return false;
   }
   subfile_buf = new cPositionedBuffer(subfiles * sizeof(FILE_SUBFILE_T));
   if (!_FileBuffer->Get(subfile_buf->Buffer(), subfiles * sizeof(FILE_SUBFILE_T))) {
      return false;
   }
   subfile_tab = (SUBFILE_TAB_T*)cSystemUtils::Alloc(sizeof(*subfile_tab));
   subfile_tab->id = subfile_tab_id;
   subfile_tab->subfiles = subfiles;
   subfile_tab->buf_size = subfiles * sizeof(FILE_SUBFILE_T);
   subfile_tab->subfile_buf = (FILE_SUBFILE_T*)subfile_buf->Buffer();
   int i = 0;
   FILE_SUBFILE_T * subfile_ptr = (FILE_SUBFILE_T*)subfile_buf->Buffer();
   for (;
        i < subfiles;
        i++, subfile_ptr++) {
      _FileBuffer->Seek(subfile_ptr->offset);
      if (!_FileBuffer->Get(&subfile_id, sizeof(subfile_id))) {
         return false;
      }
      _subfile.subfile_id = subfile_id;
      if (subfile_id != subfile_ptr->id) {
         Error(__LINE__, "id of pointer table invalid (%d != %d)", subfile_id, subfile_ptr->id);
//         return _E_SUBFILE_ID_MATCH;
         return false;
      }
      _subfile.offset = subfile_ptr->offset;
      if (i == subfiles - 1) {
         _subfile.size = _FileBuffer->Size() - subfile_ptr->offset - 2;
      } else {
         _subfile.size = (subfile_ptr+1)->offset - subfile_ptr->offset;
      }
      if (_subfile.size <= 0) {
         Error(__LINE__, "size of subfile %s is 0", FileSpec(subfile_id).c_str());
//         return _E_SUBFILE_SIZE;
         return false;
      }
      _FileBuffer->Seek(subfile_ptr->offset);
      void * buf = cSystemUtils::Alloc(_subfile.size);
      if (!_FileBuffer->Get(buf, _subfile.size)) {
         return false;
      }
      _subfile.buffer = buf;
//      _subfile.description = FileName(_subfile.subfile_id);
      strcpy(_subfile.description, FileSpec(_subfile.subfile_id).c_str());
      cSubfile * subfile = new cSubfile(this, &_subfile);
      AddSubfile(subfile);
      if (!ReadSubfileContent(subfile)) {
         return false;
      }
   }
   return true;
}

BOOL_T cFMFatFile::ReadSubfileContent(cSubfile * subfile)
{
   int subfile_id = subfile->_Id;
   int subfile_type = FileType(subfile_id);
   switch (subfile_type) {
   case TAB_IQTREG:
      if (!ReadIqtRegs(subfile, subfile_id)) {
         Error(__LINE__, "failed to read IQT registers of %s", subfile->_Description.c_str());
         return false;
      }
      break;
   case TAB_ISCOSREG:
      if (!ReadIscosRegs(subfile, subfile_id)) {
         Error(__LINE__, "failed to read ISCOS registers of %s", subfile->_Description.c_str());
         return false;
      }
      break;
   case TAB_ISCOSBIT:
      if (!ReadIscosBits(subfile, subfile_id)) {
         Error(__LINE__, "failed to read ISCOS Bits of %s", subfile->_Description.c_str());
         return false;
      }
      break;
   case TAB_TEXT:
      if (!ReadTexts(subfile, subfile_id)) {
         Error(__LINE__, "failed to read texts of %s", subfile->_Description.c_str());
         return false;
      }
      break;
   case TAB_HEATTEXT:
      if (!ReadHeatTexts(subfile, subfile_id)) {
         Error(__LINE__, "failed to read heating texts of %s", subfile->_Description.c_str());
         return false;
      }
      break;
   case TAB_PG:
      if (!ReadPG(subfile, subfile_id)) {
         Error(__LINE__, "failed to read process graphic data of %s", subfile->_Description.c_str());
         return  true;
      }
      break;
   case TAB_PG_NEW:
      if (!ReadPGNew(subfile, subfile_id)) {
         Error(__LINE__, "failed to read new process graphic data of %s", subfile->_Description.c_str());
         return true;
      }
      break;
   case TAB_EM17:
      if (!ReadEM17(subfile, subfile_id)) {
         Error(__LINE__, "failed to read euromap 17 robot data %s", subfile->_Description.c_str());
         return true;
      }
      break;
   default:
      Error(__LINE__, "unknown subfile type %d of %s", subfile_type, subfile->_Description.c_str());
      return false;
   }
   return true;
}

BOOL_T cFMFatFile::ReadIqtRegs(cSubfile * subfile, int subfile_id)
{
   return ReadRegs(subfile, subfile_id);
}

BOOL_T cFMFatFile::ReadIscosRegs(cSubfile * subfile, int subfile_id)
{
   return ReadRegs(subfile, subfile_id);
}

BOOL_T cFMFatFile::ReadIscosBits(cSubfile * subfile, int subfile_id)
{
   return ReadRegs(subfile, subfile_id);
}

BOOL_T cFMFatFile::ReadTexts(cSubfile * subfile, int subfile_id)
{
   unsigned_16 text_len = 0;
   UCHAR_T comp_text_buf[TEXT_BUF_SIZE] = {0};
   TEXT_IDENT text_ident = {0};
   signed_16 id = {0};
   cPositionedBuffer * subfile_buf = subfile->Buffer();
   subfile_buf->Seek(0);
   if (!subfile_buf->Get(&id, sizeof(id))) {
      return false;
   }
   if (id != subfile_id) {
      Error(__LINE__, "invalid subfile id %d in subfile expected %d", id, subfile_id);
//      return _E_SUBFILE_ID_MATCH;
      return false;
   }
   if (!subfile_buf->Get(&text_ident, sizeof(text_ident))) {
      unsigned_16 text_id = 0;
      if (!subfile_buf->Get(&text_id, sizeof(text_id))) {
         return false;
      } else {
         if (text_id == DISK_ID_END) {
            return true;
         } else {
            return false;
         }
      }
   }
   while (text_ident.id != DISK_ID_END) {
      TEXT_T * _text = (TEXT_T*)cSystemUtils::Alloc(sizeof(*_text));
      _text->subfile_id = subfile_id;
      _text->id = text_ident.id;
      _text->cols = text_ident.cols;
      _text->rows = text_ident.rows;
      _text->length = text_ident.length;
      _text->size = text_ident.cols * text_ident.rows;
      if (_text->size <= 0) {
//            return _E_TEXT_SIZE;
         return false;
      }
      if (!subfile_buf->Get(comp_text_buf, _text->length)) {
         return false;
      }
      UCHAR_T * buffer = (UCHAR_T*)cSystemUtils::Alloc(_text->size + 1);
      text_len = DeCompressText(buffer, comp_text_buf, _text->length);
      if (text_len < 0 || text_len > _text->size) {
//            return _E_TEXT_DECOMPRESS;
         return false;
      }
      _text->buffer = (char*)buffer;
      cTextVar * text_var = new cTextVar(this, subfile, _text);
      AddTextVar(text_var);
      if (!subfile_buf->Get(&text_ident, sizeof(text_ident))) {
         unsigned_16 text_id = 0;
         if (!subfile_buf->Get(&text_id, sizeof(text_id))) {
            return false;
         } else {
            if (text_id == DISK_ID_END) {
               return true;
            } else {
               return false;
            }
         }
      }
   }
   return true;
}

BOOL_T cFMFatFile::ReadRegs(cSubfile * subfile, int subfile_id)
{
   int nregs = 0;
   unsigned_16 id = 0;
   unsigned_16 act_reg_no = 0;
   unsigned_8 reg_type = 0;
   int value_size = 0;
   cPositionedBuffer * buffer = subfile->Buffer();
   buffer->Seek(0);
   if (!buffer->Get(&id, sizeof(id))) {
      return false;
   }
   if (id != subfile_id) {
      Error(__LINE__, "invalid subfile id %d in subfile expected %d", id, subfile_id);
//      return _E_SUBFILE_ID_MATCH;
      return false;
   }
   if (!buffer->Get(&act_reg_no, sizeof(act_reg_no))) {
      return false;
   }
   while (act_reg_no != DISK_ID_END) {
      reg_type = 0;
      if (act_reg_no >= REGMAX_ISCOS_REG && act_reg_no < REGMAX_OILHEAT_REG) {
         if (!buffer->Get(&reg_type, sizeof(reg_type))) {
            return false;
         }
         if (!ReadHeatGroups(subfile, subfile_id, act_reg_no, reg_type)) {
            return false;
         }
      } else {
         ULONG_T size = 0;
         REGISTER_T * _reg = NULL;;
         if (act_reg_no >= START_ISCOS_REGS) {
            if (!buffer->Get(&reg_type, sizeof(reg_type))) {
               return false;
            }
            size = RegSize(reg_type);
            value_size = ValueSize(reg_type);
         } else {
            size = 1;
            value_size = 1;
         }
         if (size == 0) {
//            return _E_REG_SIZE;
            return false;
         }
         _reg = (REGISTER_T*)cSystemUtils::Alloc(sizeof(*_reg));
         _reg->subfile_id = subfile_id;
         _reg->reg_no = act_reg_no;
         _reg->reg_type = reg_type;
         _reg->size = (unsigned_8)size;
         _reg->value_size = value_size;
         _reg->buffer = cSystemUtils::Alloc(_reg->size);
         if (!buffer->Get(_reg->buffer, size)) {
            return false;
         }
         cRegister * reg = new cRegister(this, subfile, _reg);
         AddRegister(reg);
      }
      if (!buffer->Get(&act_reg_no, sizeof(act_reg_no))) {
         return false;
      }
      nregs++;
   }
   return true;
}

BOOL_T cFMFatFile::ReadHeatGroups(cSubfile * subfile, int subfile_id, unsigned_16 reg_no, unsigned_8 reg_type)
{
   unsigned_16 reg_count = 0;
   unsigned_16 zone_count = 0, unit_count = 0;
   signed_16 stored_zones = 0, zone_id = 0, unit_id = 0;
   cPositionedBuffer * buffer = subfile->Buffer();
   if (!buffer->Get(&reg_count, sizeof(reg_count))) {
      return false;
   }
   if (!buffer->Get(&zone_count, sizeof(zone_count))) {
      return false;
   }
   if (!buffer->Get(&unit_count, sizeof(unit_count))) {
      return false;
   }
   if (!buffer->Get(&stored_zones, sizeof(stored_zones))) {
      return false;
   }
   HEATGROUP_T * _heatgroup = (HEATGROUP_T*)cSystemUtils::Alloc(sizeof(*_heatgroup));
   _heatgroup->subfile_id = subfile_id;
   _heatgroup->heatgroup = reg_no;
   _heatgroup->reg_type = reg_type;
   _heatgroup->reg_count = reg_count;
   _heatgroup->zone_count = zone_count;
   _heatgroup->unit_count = unit_count;
   _heatgroup->stored_zones = stored_zones;
   cHeatGroup * heatgroup = new cHeatGroup(this, subfile, _heatgroup);
   AddHeatGroup(heatgroup);
   for (int i=0; i<stored_zones; i++) {
      if (!buffer->Get(&zone_id, sizeof(zone_id))) {
         return false;
      }
      if (!buffer->Get(&unit_id, sizeof(unit_id))) {
         return false;
      }
      ZONE_T * _heatzone = (ZONE_T*)cSystemUtils::Alloc(sizeof(*_heatzone));
      _heatzone->zone_id = zone_id;
      _heatzone->unit_id = unit_id;
      void * buf = cSystemUtils::Alloc(_heatgroup->reg_count * sizeof(signed_16));
      _heatzone->buffer = buf;
      if (!buffer->Get(buf, _heatgroup->reg_count * sizeof(signed_16))) {
         return false;
      }
      cHeatZone * heatzone = new cHeatZone(this, _heatzone, heatgroup);
      heatgroup->AddZone(heatzone);
   }
   return true;
}

BOOL_T cFMFatFile::ReadHeatTexts(cSubfile * subfile, int subfile_id)
{
   cPositionedBuffer * buffer = subfile->Buffer();
   unsigned_16 id = 0;
   unsigned_16 len = 0;
   if (!buffer->Get(&id, sizeof(id))) {
      return false;
   }
   if (id != subfile_id) {
      Error(__LINE__, "invalid subfile id %d in subfile expected %d", id, subfile_id);
//      return _E_SUBFILE_ID_MATCH;
      return false;
   }
   if (!buffer->Get(&len, sizeof(len))) {
      return false;
   }
   if (len == 0) {
      unsigned_16 text_id = 0;
      if (!buffer->Get(&text_id, sizeof(text_id))) {
         return false;
      } else {
         if (text_id == DISK_ID_END) {
            return true;
         } else {
            return false;
         }
      }
   } else {
      while (42) {
         unsigned_16 reg_no = 0;
         unsigned_16 ind1 = 0;
         unsigned_16 ind2 = 0;
         char buf[0x200] = {0};
         if (!buffer->Get(&reg_no, sizeof(reg_no))) {
            return false;
         } else {
            if (reg_no == DISK_ID_END) {
               return true;
            } else {
               if (!buffer->Get(&ind1, sizeof(ind1))) {
                  return false;
               }
               if (!buffer->Get(&ind2, sizeof(ind2))) {
                  return false;
               }
               if (!buffer->Get(buf, len)) {
                  return false;
               }
               cHeatText * heat_text = new cHeatText(this, subfile, reg_no, ind1, ind2, buf);
               AddHeatText(heat_text);
            }
         }
      }
   }
   return false;
}

BOOL_T cFMFatFile::ReadPG(cSubfile * subfile, int subfile_id)
{
   cPositionedBuffer * buffer = subfile->Buffer();
   unsigned_16 id = 0;
   if (!buffer->Get(&id, sizeof(id))) {
      return false;
   }
   if (id != subfile_id) {
      Error(__LINE__, "invalid subfile id %d in subfile expected %d", id, subfile_id);
      return false;
   }
   UCHAR_T * buf = (UCHAR_T*)cSystemUtils::Alloc(PG_BUFFER_SIZE);
   if (!buffer->Get(buf, PG_BUFFER_SIZE)) {
      return false;
   }
   SOLL_INFO * si = (SOLL_INFO*)buf;
   unsigned_8 * curve_buffer = (unsigned_8*)buf + sizeof(*si);
   _ProcessGraphic = new cProcessGraphic(this, subfile, si, curve_buffer);
   cSystemUtils::Free(buf);
   if (!buffer->Get(&id, sizeof(id))) {
      return false;
   }
   if (id == DISK_ID_END) {
      return true;
   } else {
      return false;
   }
}

BOOL_T cFMFatFile::ReadPGNew(cSubfile * subfile, int subfile_id)
{
   cPositionedBuffer * buffer = subfile->Buffer();
   unsigned_16 id = 0;
   if (!buffer->Get(&id, sizeof(id))) {
      return false;
   }
   if (id != subfile_id) {
      Error(__LINE__, "invalid subfile id %d in subfile expected %d", id, subfile_id);
      return false;
   }
   void * buf = cSystemUtils::Alloc(0x4000);
   _NewProcessGraphic = new cNewProcessGraphic(this, subfile);
   while (42) {
      unsigned_16 size = 0;
      if (!buffer->Get(&size, sizeof(size))) {
         cSystemUtils::Free(buf);
         return false;
      }
      if (size == DISK_ID_END) {
         cSystemUtils::Free(buf);
         return true;
      } else if (size < 5) {
         cSystemUtils::Free(buf);
         return false;
      } else {
         if (!buffer->Get(buf, size)) {
            cSystemUtils::Free(buf);
            return false;
         }
         SOLL_CURVE_HEADER * curve_header = (SOLL_CURVE_HEADER*)buf;
         void * curve_buffer = (unsigned_8*)buf + sizeof(*curve_header);
         _NewProcessGraphic->AddCurve(curve_header, curve_buffer);
      }
   }
   cSystemUtils::Free(buf);
   return false;
}

BOOL_T cFMFatFile::ReadEM17(cSubfile * subfile, int subfile_id)
{
   unsigned_16 id = 0;
   cPositionedBuffer * buffer = subfile->Buffer();
   buffer->Seek(0);
   if (!buffer->Get(&id, sizeof(id))) {
      return false;
   }
   if (id != subfile_id) {
      Error(__LINE__, "invalid subfile id %d in subfile expected %d", id, subfile_id);
      return false;
   }
   ULONG_T data_size = subfile->_Size - sizeof(id);
   void * data = cSystemUtils::Alloc(data_size);
   if (!buffer->Get(data, data_size)) {
      return false;
   }
   _EM17Data = new cEM17Data(this, subfile, data, data_size);
   cSystemUtils::Free(data);
   return true;
}

void cFMFatFile::SetHeader(cHeader * header)
{
   _Header = header;
}

void cFMFatFile::AddRegister(cRegister * reg)
{
   int id = reg->_RegNo;
   _Registers[id] = reg;
}

void cFMFatFile::AddTextVar(cTextVar * text_var)
{
   int id = text_var->_TextId;
   _TextVars[id] = text_var;
}

void cFMFatFile::AddHeatGroup(cHeatGroup * heat_group)
{
   int id = heat_group->_GroupId;
   _HeatGroups[id] = heat_group;
}

void cFMFatFile::AddHeatText(cHeatText * heat_text)
{
   // ??
}

void cFMFatFile::AddSubfile(cSubfile * subfile)
{
   int id = subfile->_Id;
   _Subfiles[id] = subfile;
}


