
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "FMFatFile.h"
#include "FileBuffer.h"
#include "HAlloc.h"

static int _LastError = 0;
static int _Line = 0;
static unsigned_32 _LastSeekPos = 0;
static unsigned_32 _LastReadPos = 0;
static unsigned_32 _LastWritePos = 0;
static unsigned_32 _LastReadSize = 0;
static unsigned_32 _LastWriteSIze = 0;

static int min(int a, int b)
{
   if (a < b) {
      return a;
   } else {
      return b;
   }
}

static int LastError(int error, int line)
{
   _LastError = error;
   _Line = line;
   return error;
}

int GetLastErr() { return _LastError; }
int GetLine() { return _Line; }

#define TEXT_BUF_SIZE   4096
static char _Text[8192];

static void Subst(char * buf, char c, char subst, int len)
{
   int i;
   for (i=0; i<len; i++) {
      if (buf[i] == c) buf[i] = subst;
   }
}

static int DebugPrintf(char * fmtstr, ...)
{
   va_list args;
   FILE * stream;

   va_start(args, fmtstr);
   vsprintf(_Text, fmtstr, args);
   va_end(args);
   stream = fopen("Debug.txt", "a");
   if (stream != NULL) {
      fprintf(stream, "%s", _Text);
      fclose(stream);
   }
   return 0;
}

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
   { DISK_ID_PG,           TAB_PG,       "Proze~grafik kompatible Version" },
   { DISK_ID_PG_IQTREG,    TAB_IQTREG,   "Proze~grafik IQT-Register" },
   { DISK_ID_PG_ISCOSREG,  TAB_ISCOSREG, "Proze~grafik SPS-Register" },
   { DISK_ID_PG_NEW,       TAB_PG_NEW,   "Proze~grafik neue Version" },
   { DISK_ID_ROB_REG,      TAB_IQTREG, "Roboter-Register" },
   { DISK_ID_ROB_TEXT,     TAB_TEXT,   "Roboter-Texte" },
   { DISK_ID_ABGL,         TAB_IQTREG, "Maschinenabgleich-Register" },
   { DISK_ID_CORE_IQTREG,    TAB_IQTREG,   "Kernz}ge IQT-Register" },
   { DISK_ID_CORE_ISCOSREG,  TAB_ISCOSREG, "Kernz}ge SPS-Register" }
};
#define CONFIG_ENTRIES  (sizeof(FullFile)/sizeof(SUBFILE_TAB))

const char * FileName(int id)
{
   int i;
   for (i=0; i<CONFIG_ENTRIES; i++) {
      if (id == FullFile[i].Id) {
         return FullFile[i].Text;
      }
   }
   return "unknown";
}

int FileType(int id)
{
   int i;
   for (i=0; i<CONFIG_ENTRIES; i++) {
      if (id == FullFile[i].Id) {
         return FullFile[i].Tab;
      }
   }
   return -1;
}

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
         /* mindestens 2 Zeichen sind gleich */
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

static int AddHeader(FMFAT_BUFFER_T * fmfat_buf, FILE_HEADER_T * header)
{
   fmfat_buf->header = header;
   return 0;
}

#define _E_MEMORY_ALLOC          -10000
#define _E_BUF_READ              -10001
#define _E_BUF_WRITE             -10002
#define _E_BUF_SEEK              -10003

#define _E_HEADER_SIZE           -10100
#define _E_SUBFILE_ID_MATCH      -10101
#define _E_REG_SIZE              -10102
#define _E_TEXT_SIZE             -10103
#define _E_SUBFILE_COUNT         -10104
#define _E_SUBFILE_SIZE          -10105
#define _E_SUBFILE_TYPE_MATCH    -10106

#define _E_HEATGROUP_BUF         -10200
#define _E_ZONE_BUF              -10201
#define _E_REG_BUF               -10202
#define _E_TEXT_BUF              -10203
#define _E_SUBFILE_BUF           -10204

#define _E_SUBFILE_NOT_FOUND     -10300
#define _E_REG_NOT_FOUND         -10301
#define _E_TEXT_NOT_FOUND        -10302
#define _E_HEATGROUP_NOT_FOUND   -10303
#define _E_ZONE_NOT_FOUND        -10304
#define _E_HEATGROUP_PARAM       -10305
#define _E_REG_VALUE_SIZE        -10306
#define _E_REG_INDEX             -10307
#define _E_REG_DIM               -10308
#define _E_TEXT_ROW              -10309
#define _E_TEXT_DECOMPRESS       -10310

#define _E_BUFFER_SIZE           -10400
#define _E_STRING_LENGTH         -10401
#define _E_OUT_OF_RANGE          -10402

#define ALLOC_OBJECT(obj,size) \
   if ((obj = HAlloc(size)) == NULL) return LastError(_E_MEMORY_ALLOC, __LINE__);

#define LAST_ERROR(err) return LastError(_E_MEMORY_ALLOC,__LINE__);

#define ERROR_RETURN(func) \
   { \
      int __ret; \
      if ((__ret = func) != 0) return LastError(__ret,__LINE__); \
   }

#define CHECKED_READ(fbuf,buf,size) \
   if (fbuf->Read(fbuf, buf, size) != size) return LastError(_E_BUF_READ,__LINE__);

#define CHECKED_WRITE(fbuf,buf,size) \
   if (fbuf->Write(fbuf, buf, size) != size) return LastError(_E_BUF_WRITE,__LINE__);

#define SEEK(fbuf,pos) \
   { \
      long __pos; \
      if ((__pos = fbuf->Seek(fbuf, pos)) != pos) return LastError(__pos,__LINE__); \
   }

static int ReadHeader(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf)
{
   FILE_HEADER_T * header;
   unsigned_32 size = sizeof(*header);
   ALLOC_OBJECT(header, size)
   ERROR_RETURN(AddHeader(fmfat_buf, header))
   SEEK(fbuf,0)
   CHECKED_READ(fbuf,header,size)
   if (header->HeaderSize > size) return _E_HEADER_SIZE;
   _CALLBACK_(fmfat_buf,Header,header)
   return header->HeaderSize;
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

static int AddHeatgroup(FMFAT_BUFFER_T * fmfat_buf, HEATGROUP_T * heatgroup)
{
   int i;
   for (i=0; i<MAX_HEAT_GROUPS; i++) {
      if (fmfat_buf->heatgroup[i] == NULL) {
         fmfat_buf->heatgroup[i] = heatgroup;
         return 0;
      }
   }
   return _E_HEATGROUP_BUF;
}

static int AddZone(HEATGROUP_T * heatgroup, ZONE_T * zone)
{
   int i;
   for (i=0; i<MAX_ZONES; i++) {
      if (heatgroup->zone[i] == NULL) {
         heatgroup->zone[i] = zone;
         return 0;
      }
   }
   return _E_ZONE_BUF;
}

static int ReadHeatgroups(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf,
                        unsigned_16 subfile_id, unsigned_16 reg_no, unsigned_16 reg_type)
{
   int i;
   unsigned_16 reg_count;
   unsigned_16 zone_count, unit_count;
   signed_16 stored_zones, zone_id, unit_id;
   HEATGROUP_T * heatgroup;

   CHECKED_READ(fbuf,&reg_count,sizeof(reg_count))
   CHECKED_READ(fbuf,&zone_count, sizeof(zone_count))
   CHECKED_READ(fbuf,&unit_count, sizeof(unit_count))
   CHECKED_READ(fbuf,&stored_zones,sizeof(stored_zones))
   ALLOC_OBJECT(heatgroup,sizeof(*heatgroup))
   ERROR_RETURN(AddHeatgroup(fmfat_buf, heatgroup))
   heatgroup->subfile_id = subfile_id;
   heatgroup->heatgroup = reg_no;
   heatgroup->reg_type = reg_type;
   heatgroup->reg_count = reg_count;
   heatgroup->zone_count = zone_count;
   heatgroup->unit_count = unit_count;
   heatgroup->stored_zones = stored_zones;
   _CALLBACK_(fmfat_buf,Heatgroup,heatgroup)
   for (i=0; i<stored_zones; i++) {
      int bufsize;
      ZONE_T * zone;
      void * buffer;
      CHECKED_READ(fbuf,&zone_id,sizeof(zone_id))
      CHECKED_READ(fbuf,&unit_id,sizeof(unit_id))
      ALLOC_OBJECT(zone,sizeof(*zone))
      ERROR_RETURN(AddZone(heatgroup, zone))
      zone->zone_id = zone_id;
      zone->unit_id = unit_id;
      bufsize = heatgroup->reg_count * sizeof(signed_16);
      ALLOC_OBJECT(buffer,bufsize)
      zone->buffer = buffer;
      CHECKED_READ(fbuf,buffer,bufsize)
      _CALLBACK_(fmfat_buf,Zone,zone)
   }
   return 0;
}

static int AddRegister(FMFAT_BUFFER_T * fmfat_buf, REGISTER_T * reg)
{
   int i;
   for (i=0; i<MAX_REGS; i++) {
      if (fmfat_buf->reg[i] == NULL) {
         fmfat_buf->reg[i] = reg;
         return 0;
      }
   }
   return _E_REG_BUF;
}

static int ReadRegs(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf,
                    unsigned_32 pos, unsigned_16 subfile_id)
{
   int nregs = 0, ret;
   unsigned_16 id;
   unsigned_16 act_reg_no;
   unsigned_8 reg_type;
   int value_size, size;

   SEEK(fbuf, pos)
   CHECKED_READ(fbuf,&id,sizeof(id))
   if (id != subfile_id) return _E_SUBFILE_ID_MATCH;
   CHECKED_READ(fbuf,&act_reg_no,sizeof(act_reg_no))
   while (act_reg_no != DISK_ID_END) {
      reg_type = 0;
      if (act_reg_no >= REGMAX_ISCOS_REG && act_reg_no < REGMAX_OILHEAT_REG) {
         CHECKED_READ(fbuf,&reg_type,sizeof(reg_type))
         ERROR_RETURN(ReadHeatgroups(fbuf, fmfat_buf, subfile_id, act_reg_no, reg_type))
      } else {
         REGISTER_T * reg;
         void * buffer;
         if (act_reg_no >= START_ISCOS_REGS) {
            CHECKED_READ(fbuf,&reg_type,sizeof(reg_type))
            size = RegSize(reg_type);
            value_size = ValueSize(reg_type);
         } else {
            size = 1;
            value_size = 1;
         }
         if (size == 0) return _E_REG_SIZE;
         ALLOC_OBJECT(reg,sizeof(*reg))
         ERROR_RETURN(AddRegister(fmfat_buf, reg))
         reg->subfile_id = subfile_id;
         reg->reg_no = act_reg_no;
         reg->reg_type = reg_type;
         reg->size = size;
         reg->value_size = value_size;
         ALLOC_OBJECT(buffer,reg->size)
         reg->buffer = buffer;
         _CALLBACK_(fmfat_buf,Register,reg)
         CHECKED_READ(fbuf,buffer,reg->size)
      }
      CHECKED_READ(fbuf,&act_reg_no,sizeof(act_reg_no))
      nregs++;
   }
   return 0;
}

static int ReadIqtRegs(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf,
                       unsigned_32 pos, unsigned_16 subfile_id)
{
   return ReadRegs(fbuf, fmfat_buf, pos, subfile_id);
}

static int ReadIscosRegs(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf,
                         unsigned_32 pos, unsigned_16 subfile_id)
{
   return ReadRegs(fbuf, fmfat_buf, pos, subfile_id);
}

static int ReadIscosBits(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf,
                         unsigned_32 pos, unsigned_16 subfile_id)
{
   return ReadRegs(fbuf, fmfat_buf, pos, subfile_id);
}

static int AddText(FMFAT_BUFFER_T * fmfat_buf, TEXT_T * text)
{
   int i;
   for (i=0; i<MAX_TEXTS; i++) {
      if (fmfat_buf->text[i] == NULL) {
         fmfat_buf->text[i] = text;
         return 0;
      }
   }
   return _E_TEXT_BUF;
}

static int ReadTexts(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf,
                     unsigned_32 pos, unsigned_16 subfile_id)
{
   unsigned_16 text_len;
   char comp_text_buf[TEXT_BUF_SIZE];
   TEXT_IDENT text_ident;
   signed_16 id;

   SEEK(fbuf, pos)
   CHECKED_READ(fbuf,&id,sizeof(id))
   if (id != subfile_id) return _E_SUBFILE_ID_MATCH;
   do {
      //-JH- 12.01.2001
      //CHECKED_READ(fbuf,&text_ident,sizeof(text_ident))
      CHECKED_READ(fbuf,&text_ident.id,sizeof(text_ident.id))
      if (text_ident.id != DISK_ID_END) {
         TEXT_T * text;
         char * buffer;
         
         //-JH- 12.01.2001
         CHECKED_READ(fbuf,&text_ident.cols,sizeof(text_ident.cols))
         CHECKED_READ(fbuf,&text_ident.rows,sizeof(text_ident.rows))
         CHECKED_READ(fbuf,&text_ident.length,sizeof(text_ident.length))
         
         ALLOC_OBJECT(text,sizeof(*text))
         ERROR_RETURN(AddText(fmfat_buf, text))
         text->subfile_id = subfile_id;
         text->id = text_ident.id;
         text->cols = text_ident.cols;
         text->rows = text_ident.rows;
         text->length = text_ident.length;
         text->size = text_ident.cols * text_ident.rows;
         if (text->size <= 0) return _E_TEXT_SIZE;
         ALLOC_OBJECT(buffer,text->size)
         text->buffer = buffer;
         CHECKED_READ(fbuf,comp_text_buf,text->length)
         text_len = DeCompressText(buffer, comp_text_buf, text->length);
//         if (text_len != text->size) return _E_TEXT_DECOMPRESS;
         if (text_len < 0 || text_len > text->size) return _E_TEXT_DECOMPRESS;
         _CALLBACK_(fmfat_buf,Text,text)
      }
   } while (text_ident.id != DISK_ID_END);
   return 0;
}

static int ReadSubfileContents(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf,
                               unsigned_32 pos, unsigned_16 subfile_id)
{
   int subfile_type = FileType(subfile_id);
   switch (subfile_type) {
   case TAB_IQTREG:
      ERROR_RETURN(ReadIqtRegs(fbuf, fmfat_buf, pos, subfile_id))
      break;
   case TAB_ISCOSREG:
      ERROR_RETURN(ReadIscosRegs(fbuf, fmfat_buf, pos, subfile_id))
      break;
   case TAB_ISCOSBIT:
      ERROR_RETURN(ReadIscosBits(fbuf, fmfat_buf, pos, subfile_id))
      break;
   case TAB_TEXT:
      ERROR_RETURN(ReadTexts(fbuf, fmfat_buf, pos, subfile_id))
      break;
   }
   return 0;
}

static int AddSubfile(SUBFILE_T * subfile, FMFAT_BUFFER_T * fmfat_buf)
{
   int i;
   for (i=0; i<MAX_SUBFILES; i++) {
      if (fmfat_buf->subfile[i] == NULL) {
         fmfat_buf->subfile[i] = subfile;
         return 0;
      }
   }
   return _E_SUBFILE_BUF;
}

static int AddSubfileTab(FMFAT_BUFFER_T * fmfat_buf, SUBFILE_TAB_T * subfile_tab)
{
   fmfat_buf->subfile_tab = subfile_tab;
   return 0;
}

static int ReadSubfiles(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf, unsigned_32 pos)
{
   int i;
   unsigned_32 size = 0;
   unsigned_16 subfile_tab_id;
   unsigned_16 subfile_id;
   signed_16 subfiles;
   FILE_SUBFILE_T * subfile_buf, * sft_ptr;
   SUBFILE_TAB_T * subfile_tab;

   SEEK(fbuf, pos)
   size = sizeof(subfile_tab_id);
   CHECKED_READ(fbuf,&subfile_tab_id,size)
   if (subfile_tab_id != DISK_ID_PTRTAB) return _E_SUBFILE_ID_MATCH;
   size = sizeof(subfiles);
   CHECKED_READ(fbuf,&subfiles,size)
   if (subfiles < 0 || subfiles > MAX_SUBFILES) return _E_SUBFILE_COUNT;
   size = subfiles * sizeof(FILE_SUBFILE_T);
   ALLOC_OBJECT(subfile_buf,size)
   ALLOC_OBJECT(subfile_tab,sizeof(*subfile_tab))
   ERROR_RETURN(AddSubfileTab(fmfat_buf, subfile_tab))
   CHECKED_READ(fbuf,subfile_buf,size)
   subfile_tab->id = subfile_tab_id;
   subfile_tab->subfiles = subfiles;
   subfile_tab->buf_size = size;
   subfile_tab->subfile_buf = subfile_buf;
   _CALLBACK_(fmfat_buf,SubfileTab,subfile_tab)
   for (i=0, sft_ptr = subfile_buf;
        i<subfiles;
        i++, sft_ptr++) {
      SUBFILE_T * subfile;
      void * buf;
      SEEK(fbuf,sft_ptr->offset)
      size = sizeof(subfile_id);
      CHECKED_READ(fbuf,&subfile_id,size)
      if (subfile_id != sft_ptr->id) return _E_SUBFILE_ID_MATCH;
      ALLOC_OBJECT(subfile,sizeof(SUBFILE_T))
      ERROR_RETURN(AddSubfile(subfile, fmfat_buf))
      subfile->subfile_id = subfile_id;
      subfile->description = FileName(subfile_id);
      subfile->offset = sft_ptr->offset;
      if (i == subfiles - 1) {
         subfile->size = fbuf->file_size - sft_ptr->offset - 2;
      } else {
         subfile->size = (sft_ptr+1)->offset - sft_ptr->offset;
      }
      if (subfile->size <= 0) return _E_SUBFILE_SIZE;
      ALLOC_OBJECT(buf,subfile->size)
      SEEK(fbuf,subfile->offset)
      CHECKED_READ(fbuf,buf,subfile->size)
      subfile->buffer = buf;
      subfile->changes = 0;
      _CALLBACK_(fmfat_buf,Subfile,subfile)
      ERROR_RETURN(ReadSubfileContents(fbuf, fmfat_buf, subfile->offset, subfile->subfile_id))
   }
   return 0;
}

int WriteSubfileTab(FMFAT_BUFFER_T * fmfat_buf, FILE_BUFFER_T * fbuf)
{
   unsigned_32 size;
   unsigned_16 end = DISK_ID_END;
   SEEK(fbuf,fmfat_buf->header->HeaderSize)
   size = sizeof(fmfat_buf->subfile_tab->id);
   CHECKED_WRITE(fbuf,&(fmfat_buf->subfile_tab->id),size)
   size = sizeof(fmfat_buf->subfile_tab->subfiles);
   CHECKED_WRITE(fbuf,&(fmfat_buf->subfile_tab->subfiles),size)
   size = fmfat_buf->subfile_tab->subfiles * sizeof(FILE_SUBFILE_T);
   CHECKED_WRITE(fbuf,fmfat_buf->subfile_tab->subfile_buf,size)
   CHECKED_WRITE(fbuf,&end,sizeof(end))
   return 0;
}


static int WriteHeatgroups(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf, unsigned_16 subfile_id)
{
   int i, j, bufsize;

   for (i=0; i<MAX_HEAT_GROUPS; i++) {
      if (fmfat_buf->heatgroup[i] != NULL) {
         HEATGROUP_T * heatgroup = fmfat_buf->heatgroup[i];
         if (heatgroup->subfile_id != subfile_id) continue;
         bufsize = heatgroup->reg_count * sizeof(signed_16);
         CHECKED_WRITE(fbuf,&heatgroup->heatgroup,sizeof(heatgroup->heatgroup))
         CHECKED_WRITE(fbuf,&heatgroup->reg_type,sizeof(heatgroup->reg_type))
         CHECKED_WRITE(fbuf,&heatgroup->reg_count,sizeof(heatgroup->reg_count))
         CHECKED_WRITE(fbuf,&heatgroup->zone_count,sizeof(heatgroup->zone_count))
         CHECKED_WRITE(fbuf,&heatgroup->unit_count,sizeof(heatgroup->unit_count))
         CHECKED_WRITE(fbuf,&heatgroup->stored_zones,sizeof(heatgroup->stored_zones))
         for (j=0; j<MAX_ZONES; j++) {
            if (heatgroup->zone[j] != NULL) {
               ZONE_T * zone = heatgroup->zone[j];
               CHECKED_WRITE(fbuf,&zone->zone_id,sizeof(zone->zone_id))
               CHECKED_WRITE(fbuf,&zone->unit_id,sizeof(zone->unit_id))
               if (zone->buffer != NULL) {
                  CHECKED_WRITE(fbuf, zone->buffer, bufsize)
               }
            }
         }
      }
   }
   return 0;
}

static int WriteRegs(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf, unsigned_16 subfile_id)
{
   int i;

   for (i=0; i<MAX_REGS; i++) {
      if (fmfat_buf->reg[i] != NULL) {
         REGISTER_T * reg = fmfat_buf->reg[i];
         if (reg->subfile_id != subfile_id) continue;
         CHECKED_WRITE(fbuf,&reg->reg_no,sizeof(reg->reg_no))
         if (reg->size > 1) {
            CHECKED_WRITE(fbuf,&reg->reg_type,sizeof(reg->reg_type))
         }
         CHECKED_WRITE(fbuf,reg->buffer,reg->size)
      }
   }
   return 0;
}

static int WriteTexts(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf, unsigned_16 subfile_id)
{
   int i;
   TEXT_IDENT text_ident;
   char text_buf[TEXT_BUF_SIZE];
   int text_len;

   for (i=0; i<MAX_TEXTS; i++) {
      if (fmfat_buf->text[i] != NULL) {
         TEXT_T * text = fmfat_buf->text[i];
         if (text->subfile_id != subfile_id) continue;
         if (text->buffer == NULL) return -260;
         memset(&text_ident, 0, sizeof(text_ident));
         text_ident.id = text->id;
         text_ident.cols = text->cols;
         text_ident.rows = text->rows;
         memset(text_buf, 0, sizeof(text_buf));
         text_len = Compresstext(text_buf, text->buffer, text->size);
         text_ident.length = text_len;
         CHECKED_WRITE(fbuf,&text_ident,sizeof(text_ident))
         CHECKED_WRITE(fbuf,&text_buf,text_ident.length)
      }
   }
   return 0;
}

static int WriteSubfileContents(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_T * fmfat_buf,
                                unsigned_32 pos, unsigned_16 subfile_id)
{
   int ret = _E_SUBFILE_TYPE_MATCH;
   int subfile_type;
   unsigned_16 end = DISK_ID_END;

   CHECKED_WRITE(fbuf, &subfile_id, sizeof(subfile_id))
   subfile_type = FileType(subfile_id);
   switch (subfile_type) {
   case TAB_IQTREG:
      ret = WriteRegs(fbuf, fmfat_buf, subfile_id);
      break;
   case TAB_ISCOSREG:
      if ((ret = WriteRegs(fbuf, fmfat_buf, subfile_id)) == 0) {
         if (subfile_id == DISK_ID_ISCOSREG) {
            ret = WriteHeatgroups(fbuf, fmfat_buf, subfile_id);
         }
      }
      break;
   case TAB_ISCOSBIT:
      ret = WriteRegs(fbuf, fmfat_buf, subfile_id);
      break;
   case TAB_TEXT:
      ret = WriteTexts(fbuf, fmfat_buf, subfile_id);
      break;
   }
   CHECKED_WRITE(fbuf, &end, sizeof(end))
   return ret;
}

int WriteFatBuffer(FMFAT_BUFFER_T * fmfat_buf, FILE_BUFFER_T * fbuf)
{
   int header_len, i;
   unsigned_16 end = DISK_ID_END;

   SEEK(fbuf,0)
   header_len = fmfat_buf->header->HeaderSize;
   CHECKED_WRITE(fbuf,fmfat_buf->header,header_len)
   ERROR_RETURN(WriteSubfileTab(fmfat_buf, fbuf))
   for (i=0; i<MAX_SUBFILES; i++) {
      SUBFILE_T * subfile = fmfat_buf->subfile[i];
      if (subfile != 0) {
         unsigned_32 size = subfile->size;
         if (size > 0) {
            unsigned_32 offset = fbuf->SeekPos(fbuf);
            int file_type = FileType(subfile->subfile_id);
            fmfat_buf->subfile_tab->subfile_buf[i].offset = offset;
            if ((file_type == TAB_IQTREG ||
                 file_type == TAB_ISCOSREG ||
                 file_type == TAB_ISCOSBIT ||
                 file_type == TAB_TEXT) &&
                subfile->changes > 0) {
               ERROR_RETURN(WriteSubfileContents(fbuf, fmfat_buf, offset, subfile->subfile_id))
            } else {
               void * buf = subfile->buffer;
               CHECKED_WRITE(fbuf,buf,size)
            }
         }
      }
   }
   CHECKED_WRITE(fbuf,&end,sizeof(end))
   ERROR_RETURN(WriteSubfileTab(fmfat_buf, fbuf))
   return 0;
}

static REGISTER_T * FindReg(FMFAT_BUFFER_T * fmfat_buf, unsigned_16 reg_no)
{
   int i;

   for (i=0; i<MAX_REGS; i++) {
      if (fmfat_buf->reg[i] != NULL) {
         REGISTER_T * reg = fmfat_buf->reg[i];
         if (reg->reg_no == reg_no) return reg;
      }
   }
   return NULL;
}

static SUBFILE_T * FindSubfile(FMFAT_BUFFER_T * fmfat_buf, unsigned_16 subfile_id)
{
   int i;
   for (i=0; i<MAX_SUBFILES; i++) {
      if (fmfat_buf->subfile[i] != NULL) {
         SUBFILE_T * subfile = fmfat_buf->subfile[i];
         if (subfile->subfile_id == subfile_id) return subfile;
      }
   }
   return NULL;
}

static int SubfileChange(FMFAT_BUFFER_T * fmfat_buf, unsigned_16 subfile_id)
{
   SUBFILE_T * subfile = FindSubfile(fmfat_buf, subfile_id);
   if (subfile == NULL) return _E_SUBFILE_NOT_FOUND;
   subfile->changes++;
   return 0;
}

static int GetRegVal(void * buf, unsigned_16 reg_no, long * val)
{
   int dim;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   REGISTER_T * reg = FindReg(fmfat_buf, reg_no);
   if (reg == NULL) return _E_REG_NOT_FOUND;
   dim = DIM(reg);
   if (dim > 1) return _E_REG_DIM;
   switch (reg->value_size) {
   case 1: *val = *((signed_8*)reg->buffer); return 0;
   case 2: *val = *((signed_16*)reg->buffer); return 0;
   case 4: *val = *((signed_32*)reg->buffer); return 0;
   default: return _E_REG_VALUE_SIZE;
   }
}

static int SetRegVal(void * buf, unsigned_16 reg_no, long val)
{
   int dim, ret = 0;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   REGISTER_T * reg = FindReg(fmfat_buf, reg_no);
   if (reg == NULL) return _E_REG_NOT_FOUND;
   dim = DIM(reg);
   if (dim > 1) return _E_REG_DIM;
   switch (reg->value_size) {
   case 1: *((signed_8*)reg->buffer) = (signed_8)val; ret = 0; break;
   case 2: *((signed_16*)reg->buffer) = (signed_16)val; ret = 0; break;
   case 4: *((signed_32*)reg->buffer) = (signed_32)val; ret = 0; break;
   default: ret = _E_REG_VALUE_SIZE;
   }
   if (ret == 0) {
      ret = SubfileChange(fmfat_buf, reg->subfile_id);
   }
   return ret;
}

static int GetRegValI(void * buf, unsigned_16 reg_no, unsigned_16 index, long * val)
{
   int dim;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   REGISTER_T * reg = FindReg(fmfat_buf, reg_no);
   if (reg == NULL) return _E_REG_NOT_FOUND;
   dim = DIM(reg);
   if (dim <= 1) return _E_REG_DIM;
   if (index >= dim) return _E_REG_INDEX;
   switch (reg->value_size) {
   case 1: *val = ((signed_8*)reg->buffer)[index]; return 0;
   case 2: *val = ((signed_16*)reg->buffer)[index]; return 0;
   case 4: *val = ((signed_32*)reg->buffer)[index]; return 0;
   default: return _E_REG_VALUE_SIZE;
   }
   return 0;
}

static int SetRegValI(void * buf, unsigned_16 reg_no, unsigned_16 index, long val)
{
   int dim, ret = 0;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   REGISTER_T * reg = FindReg(fmfat_buf, reg_no);
   if (reg == NULL) return _E_REG_NOT_FOUND;
   dim = DIM(reg);
   if (dim <= 1) return _E_REG_DIM;
   if (index >= dim) return _E_REG_INDEX;
   switch (reg->value_size) {
   case 1: ((signed_8*)reg->buffer)[index] = (signed_8)val; ret = 0; break;
   case 2: ((signed_16*)reg->buffer)[index] = (signed_16)val; ret = 0; break;
   case 4: ((signed_32*)reg->buffer)[index] = (signed_32)val; ret = 0; break;
   default: ret = _E_REG_VALUE_SIZE;
   }
   if (ret == 0) {
      ret = SubfileChange(fmfat_buf, reg->subfile_id);
   }
   return ret;
}

static TEXT_T * FindText(FMFAT_BUFFER_T * fmfat_buf, unsigned_16 text_id)
{
   int i;

   for (i=0; i<MAX_TEXTS; i++) {
      if (fmfat_buf->text[i] != NULL) {
         TEXT_T * text = fmfat_buf->text[i];
         if (text->id == text_id) return text;
      }
   }
   return NULL;
}

static int GetTextRow(void * buf, unsigned_16 text_id, unsigned_16 row,
                      void * buffer, unsigned_32 buf_size)
{
   char * start;
   unsigned_16 row_width, size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   TEXT_T * text = FindText(fmfat_buf, text_id);
   if (text == NULL) return _E_TEXT_NOT_FOUND;
   if (row >= text->rows) return _E_TEXT_ROW;
   start = STARTPOS(text,row);
   row_width = ROW_WIDTH(text);
   size = min(buf_size, row_width);
   memcpy(buffer, start, size);
   return size;
}

static int SetTextRow(void * buf, unsigned_16 text_id, unsigned_16 row,
                      void * buffer, unsigned_32 buf_size)
{
   char * start;
   unsigned_16 row_width, size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   TEXT_T * text = FindText(fmfat_buf, text_id);
   if (text == NULL) return _E_TEXT_NOT_FOUND;
   if (row >= text->rows) return _E_TEXT_ROW;
   start = STARTPOS(text,row);
   row_width = ROW_WIDTH(text);
   size = min(buf_size, row_width);
   memcpy(start, buffer, size);
   SubfileChange(fmfat_buf, text->subfile_id);
   return size;
}

static int GetText(void * buf, unsigned_16 text_id, void * buffer, unsigned_32 buf_size)
{
   unsigned_16 size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   TEXT_T * text = FindText(fmfat_buf, text_id);
   if (text == NULL) return _E_TEXT_NOT_FOUND;
   size = min(buf_size, text->size);
   memcpy(buffer, text->buffer, size);
   return size;
}

static int SetText(void * buf, unsigned_16 text_id, void * buffer, unsigned_32 buf_size)
{
   unsigned_16 size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   TEXT_T * text = FindText(fmfat_buf, text_id);
   if (text == NULL) return _E_TEXT_NOT_FOUND;
   size = min(buf_size, text->size);
   memcpy(buffer, text->buffer, size);
   SubfileChange(fmfat_buf, text->subfile_id);
   return size;
}

static HEATGROUP_T * FindHeatgroup(FMFAT_BUFFER_T * fmfat_buf, unsigned_16 group_id)
{
   int i;

   for (i=0; i<MAX_HEAT_GROUPS; i++) {
      if (fmfat_buf->heatgroup[i] != NULL) {
         HEATGROUP_T * heatgroup = fmfat_buf->heatgroup[i];
         if (heatgroup->heatgroup == group_id) return heatgroup;
      }
   }
   return NULL;
}

static ZONE_T * FindZone(HEATGROUP_T * heatgroup, unsigned_16 zone_id, unsigned_16 unit_id)
{
   int i;

   for (i=0; i<MAX_ZONES; i++) {
      if (heatgroup->zone[i] != NULL) {
         ZONE_T * zone = heatgroup->zone[i];
         if (zone->zone_id == zone_id &&
             zone->unit_id == unit_id) return zone;
      }
   }
   return NULL;
}

static int GetHeatParam(void * buf, unsigned_16 group_id, unsigned_16 zone_id,
                        unsigned_16 unit_id, unsigned_16 param, long * val)
{
   unsigned_16 size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   HEATGROUP_T * heatgroup = FindHeatgroup(fmfat_buf, group_id);
   ZONE_T * zone;
   signed_16 * values;
   if (heatgroup == NULL) return _E_HEATGROUP_NOT_FOUND;
   if (param >= heatgroup->reg_count) return _E_HEATGROUP_PARAM;
   zone = FindZone(heatgroup, zone_id, unit_id);
   if (zone == NULL) return _E_ZONE_NOT_FOUND;
   values = zone->buffer;
   *val = values[param];
   return 0;
}

static int SetHeatParam(void * buf, unsigned_16 group_id, unsigned_16 zone_id,
                        unsigned_16 unit_id, unsigned_16 param, long val)
{
   unsigned_16 size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   HEATGROUP_T * heatgroup = FindHeatgroup(fmfat_buf, group_id);
   ZONE_T * zone;
   signed_16 * values;
   if (heatgroup == NULL) return _E_HEATGROUP_NOT_FOUND;
   if (param >= heatgroup->reg_count) return _E_HEATGROUP_PARAM;
   zone = FindZone(heatgroup, zone_id, unit_id);
   if (zone == NULL) return _E_ZONE_NOT_FOUND;
   values = zone->buffer;
   values[param] = val;
   SubfileChange(fmfat_buf, heatgroup->subfile_id);
   return 0;
}

int GetRegCount(void * buf, unsigned_16 group_id, int * val)
{
   unsigned_16 size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   HEATGROUP_T * heatgroup = FindHeatgroup(fmfat_buf, group_id);
   ZONE_T * zone;
   signed_16 * values;
   if (heatgroup == NULL) return _E_HEATGROUP_NOT_FOUND;
   *val = heatgroup->reg_count;
   return 0;
}

int GetZoneCount(void * buf, unsigned_16 group_id, int * val)
{
   unsigned_16 size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   HEATGROUP_T * heatgroup = FindHeatgroup(fmfat_buf, group_id);
   ZONE_T * zone;
   signed_16 * values;
   if (heatgroup == NULL) return _E_HEATGROUP_NOT_FOUND;
   *val = heatgroup->zone_count;
   return 0;
}

int GetUnitCount(void * buf, unsigned_16 group_id, int * val)
{
   unsigned_16 size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   HEATGROUP_T * heatgroup = FindHeatgroup(fmfat_buf, group_id);
   ZONE_T * zone;
   signed_16 * values;
   if (heatgroup == NULL) return _E_HEATGROUP_NOT_FOUND;
   *val = heatgroup->unit_count;
   return 0;
}

int GetStoredZones(void * buf, unsigned_16 group_id, int * val)
{
   unsigned_16 size;
   FMFAT_BUFFER_T * fmfat_buf = buf;
   HEATGROUP_T * heatgroup = FindHeatgroup(fmfat_buf, group_id);
   ZONE_T * zone;
   signed_16 * values;
   if (heatgroup == NULL) return _E_HEATGROUP_NOT_FOUND;
   *val = heatgroup->stored_zones;
   return 0;
}

int Get_MashType(void * buf, void * buffer, signed_16 buf_size)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   if (buf_size <= MAX_MASCH_TYPE) return _E_BUFFER_SIZE;
   memset(buffer, '\0', MAX_MASCH_TYPE+1);
   memcpy(buffer, header->MashType, MAX_MASCH_TYPE);
   return 0;
}

int Set_MashType(void * buf, void * mash_type)
{
   long len = strlen(mash_type);
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   memset(header->MashType, 0, MAX_MASCH_TYPE);
   if (len > MAX_MASCH_TYPE) return _E_STRING_LENGTH;
   memcpy(header->MashType, mash_type, len);
   return 0;
}

int Get_MatNr(void * buf, void * buffer, signed_16 buf_size)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   if (buf_size <= MAX_MAT_NR) return _E_BUFFER_SIZE;
   memset(buffer, '\0', MAX_MAT_NR+1);
   memcpy(buffer, header->MatNr, MAX_MAT_NR);
   return 0;
}

int Set_MatNr(void * buf, void * mat_nr)
{
   long len = strlen(mat_nr);
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   memset(header->MatNr, 0, MAX_MAT_NR);
   if (len > MAX_MAT_NR) return _E_STRING_LENGTH;
   memcpy(header->MatNr, mat_nr, len);
   return 0;
}

int Get_ToolNr(void * buf, void * buffer, signed_16 buf_size)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   if (buf_size <= MAX_TOOL_NR) return _E_BUFFER_SIZE;
   memset(buffer, '\0', MAX_TOOL_NR+1);
   memcpy(buffer, header->ToolNr, MAX_TOOL_NR);
   return 0;
}

int Set_ToolNr(void * buf, void * tool_nr)
{
   long len = strlen(tool_nr);
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   memset(header->ToolNr, 0, MAX_TOOL_NR);
   if (len > MAX_TOOL_NR) return _E_STRING_LENGTH;
   memcpy(header->ToolNr, tool_nr, len);
   return 0;
}

int Get_InfoText(void * buf, void * buffer, signed_16 buf_size)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   if (buf_size <= MAX_INFO_TEXT) return _E_BUFFER_SIZE;
   memset(buffer, '\0', MAX_INFO_TEXT+1);
   memcpy(buffer, header->InfoText, MAX_INFO_TEXT);
   return 0;
}

int Set_InfoText(void * buf, void * info_text)
{
   long len = strlen(info_text);
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   memset(header->InfoText, 0, MAX_INFO_TEXT);
   if (len > MAX_INFO_TEXT) return _E_STRING_LENGTH;
   memcpy(header->InfoText, info_text, len);
   return 0;
}

int Get_Date(void * buf, unsigned_32 * date)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *date = header->Date;
   return 0;
}

int Set_Date(void * buf, unsigned_32 date)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->Date = date;
   return 0;
}

int Get_MaxAgg(void * buf, signed_16 * max_agg)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *max_agg = header->MaxAgg;
   return 0;
}

int Set_MaxAgg(void * buf, signed_16 max_agg)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->MaxAgg = max_agg;
   return 0;
}

int Get_MashSize(void * buf, signed_16 * mash_size)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *mash_size = header->MashSize;
   return 0;
}

int Set_MashSize(void * buf, signed_16 mash_size)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->MashSize = mash_size;
   return 0;
}

int Get_MouldOpWay(void * buf, signed_16 * mould_op_way)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *mould_op_way = header->MouldOpWay;
   return 0;
}

int Set_MouldOpWay(void * buf, signed_16 mould_op_way)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->MouldOpWay = mould_op_way;
   return 0;
}

int Get_Version(void * buf, unsigned_8 * version)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *version = header->Version;
   return 0;
}

int Set_Version(void * buf, unsigned_8 version)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->Version = version;
   return 0;
}

int Get_HeaderSize(void * buf, unsigned_8 * header_size)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *header_size = header->HeaderSize;
   return 0;
}

int Set_HeaderSize(void * buf, unsigned_8 header_size)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->HeaderSize = header_size;
   return 0;
}

int Get_FileType(void * buf, unsigned_8 * file_type)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *file_type = header->FileType;
   return 0;
}

int Set_FileType(void * buf, unsigned_8 file_type)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->FileType = file_type;
   return 0;
}

int Get_RegType(void * buf, unsigned_8 * reg_type)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *reg_type = header->RegType;
   return 0;
}

int Set_RegType(void * buf, unsigned_8 reg_type)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->RegType = reg_type;
   return 0;
}

int Get_ProgNr(void * buf, signed_16 * prog_nr)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *prog_nr = header->ProgNr;
   return 0;
}

int Set_ProgNr(void * buf, signed_16 prog_nr)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->ProgNr = prog_nr;
   return 0;
}

int Get_VersMash(void * buf, unsigned_8 * vers_mash)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *vers_mash = header->VersMash;
   return 0;
}

int Set_VersMash(void * buf, unsigned_8 vers_mash)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->VersMash = vers_mash;
   return 0;
}

int Get_VersStruct(void * buf, unsigned_8 * vers_struct)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *vers_struct = header->VersStruct;
   return 0;
}

int Set_VersStruct(void * buf, unsigned_8 vers_struct)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->VersStruct = vers_struct;
   return 0;
}

int Get_VersExtra(void * buf, unsigned_8 * vers_extra)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *vers_extra = header->VersExtra;
   return 0;
}

int Set_VersExtra(void * buf, unsigned_8 vers_extra)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->VersExtra = vers_extra;
   return 0;
}

int Get_Reserved1(void * buf, signed_16 * reserved1)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *reserved1 = header->Reserved1;
   return 0;
}

int Set_Reserved1(void * buf, signed_16 reserved1)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->Reserved1 = reserved1;
   return 0;
}

int Get_Reserved2(void * buf, signed_16 * reserved2)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   *reserved2 = header->Reserved2;
   return 0;
}

int Set_Reserved2(void * buf, signed_16 reserved2)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   header->Reserved2 = reserved2;
   return 0;
}

int Get_PlastWay(void * buf, signed_16 index, signed_16 * plast_way)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: *plast_way = header->PlastWay; break;
      case 2: *plast_way = header->PlastWay2; break;
      case 3: *plast_way = header->PlastWay3; break;
      case 4: *plast_way = header->PlastWay4; break;
      case 5: *plast_way = header->PlastWay5; break;
      case 6: *plast_way = header->PlastWay6; break;
      case 7: *plast_way = header->PlastWay7; break;
      case 8: *plast_way = header->PlastWay8; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Set_PlastWay(void * buf, signed_16 index, signed_16 plast_way)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: header->PlastWay = plast_way; break;
      case 2: header->PlastWay2 = plast_way; break;
      case 3: header->PlastWay3 = plast_way; break;
      case 4: header->PlastWay4 = plast_way; break;
      case 5: header->PlastWay5 = plast_way; break;
      case 6: header->PlastWay6 = plast_way; break;
      case 7: header->PlastWay7 = plast_way; break;
      case 8: header->PlastWay8 = plast_way; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Get_HeatZoneCount(void * buf, signed_16 index, unsigned_8 * heat_zone_count)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: *heat_zone_count = header->HeatZoneCount; break;
      case 2: *heat_zone_count = header->HeatZoneCount2; break;
      case 3: *heat_zone_count = header->HeatZoneCount3; break;
      case 4: *heat_zone_count = header->HeatZoneCount4; break;
      case 5: *heat_zone_count = header->HeatZoneCount5; break;
      case 6: *heat_zone_count = header->HeatZoneCount6; break;
      case 7: *heat_zone_count = header->HeatZoneCount7; break;
      case 8: *heat_zone_count = header->HeatZoneCount8; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Set_HeatZoneCount(void * buf, signed_16 index, unsigned_8 heat_zone_count)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: header->HeatZoneCount = heat_zone_count; break;
      case 2: header->HeatZoneCount2 = heat_zone_count; break;
      case 3: header->HeatZoneCount3 = heat_zone_count; break;
      case 4: header->HeatZoneCount4 = heat_zone_count; break;
      case 5: header->HeatZoneCount5 = heat_zone_count; break;
      case 6: header->HeatZoneCount6 = heat_zone_count; break;
      case 7: header->HeatZoneCount7 = heat_zone_count; break;
      case 8: header->HeatZoneCount8 = heat_zone_count; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Get_MaxSpritzDruck(void * buf, signed_16 index, signed_16 * max_spritz_druck)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: *max_spritz_druck = header->MaxSpritzDruck; break;
      case 2: *max_spritz_druck = header->MaxSpritzDruck2; break;
      case 3: *max_spritz_druck = header->MaxSpritzDruck3; break;
      case 4: *max_spritz_druck = header->MaxSpritzDruck4; break;
      case 5: *max_spritz_druck = header->MaxSpritzDruck5; break;
      case 6: *max_spritz_druck = header->MaxSpritzDruck6; break;
      case 7: *max_spritz_druck = header->MaxSpritzDruck7; break;
      case 8: *max_spritz_druck = header->MaxSpritzDruck8; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Set_MaxSpritzDruck(void * buf, signed_16 index, signed_16 max_spritz_druck)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: header->MaxSpritzDruck = max_spritz_druck; break;
      case 2: header->MaxSpritzDruck2 = max_spritz_druck; break;
      case 3: header->MaxSpritzDruck3 = max_spritz_druck; break;
      case 4: header->MaxSpritzDruck4 = max_spritz_druck; break;
      case 5: header->MaxSpritzDruck5 = max_spritz_druck; break;
      case 6: header->MaxSpritzDruck6 = max_spritz_druck; break;
      case 7: header->MaxSpritzDruck7 = max_spritz_druck; break;
      case 8: header->MaxSpritzDruck8 = max_spritz_druck; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Get_MouldInPres(void * buf, signed_16 index, signed_16 * mould_in_press)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: *mould_in_press = header->MouldInPres; break;
      case 2: *mould_in_press = header->MouldInPres2; break;
      case 3: *mould_in_press = header->MouldInPres3; break;
      case 4: *mould_in_press = header->MouldInPres4; break;
      case 5: *mould_in_press = header->MouldInPres5; break;
      case 6: *mould_in_press = header->MouldInPres6; break;
      case 7: *mould_in_press = header->MouldInPres7; break;
      case 8: *mould_in_press = header->MouldInPres8; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Set_MouldInPres(void * buf, signed_16 index, signed_16 mould_in_press)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: header->MouldInPres = mould_in_press; break;
      case 2: header->MouldInPres2 = mould_in_press; break;
      case 3: header->MouldInPres3 = mould_in_press; break;
      case 4: header->MouldInPres4 = mould_in_press; break;
      case 5: header->MouldInPres5 = mould_in_press; break;
      case 6: header->MouldInPres6 = mould_in_press; break;
      case 7: header->MouldInPres7 = mould_in_press; break;
      case 8: header->MouldInPres8 = mould_in_press; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Get_Diameter(void * buf, signed_16 index, signed_16 * diameter)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: *diameter = header->Diameter; break;
      case 2: *diameter = header->Diameter2; break;
      case 3: *diameter = header->Diameter3; break;
      case 4: *diameter = header->Diameter4; break;
      case 5: *diameter = header->Diameter5; break;
      case 6: *diameter = header->Diameter6; break;
      case 7: *diameter = header->Diameter7; break;
      case 8: *diameter = header->Diameter8; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Set_Diameter(void * buf, signed_16 index, signed_16 diameter)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: header->Diameter = diameter; break;
      case 2: header->Diameter2 = diameter; break;
      case 3: header->Diameter3 = diameter; break;
      case 4: header->Diameter4 = diameter; break;
      case 5: header->Diameter5 = diameter; break;
      case 6: header->Diameter6 = diameter; break;
      case 7: header->Diameter7 = diameter; break;
      case 8: header->Diameter8 = diameter; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Get_PresConst(void * buf, signed_16 index, signed_16 * pres_const)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: *pres_const = header->PresConst; break;
      case 2: *pres_const = header->PresConst2; break;
      case 3: *pres_const = header->PresConst3; break;
      case 4: *pres_const = header->PresConst4; break;
      case 5: *pres_const = header->PresConst5; break;
      case 6: *pres_const = header->PresConst6; break;
      case 7: *pres_const = header->PresConst7; break;
      case 8: *pres_const = header->PresConst8; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Set_PresConst(void * buf, signed_16 index, signed_16 pres_const)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: header->PresConst = pres_const; break;
      case 2: header->PresConst2 = pres_const; break;
      case 3: header->PresConst3 = pres_const; break;
      case 4: header->PresConst4 = pres_const; break;
      case 5: header->PresConst5 = pres_const; break;
      case 6: header->PresConst6 = pres_const; break;
      case 7: header->PresConst7 = pres_const; break;
      case 8: header->PresConst8 = pres_const; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Get_Aggregat(void * buf, signed_16 index, unsigned_8 * aggregat)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: *aggregat = header->Aggregat; break;
      case 2: *aggregat = header->Aggregat2; break;
      case 3: *aggregat = header->Aggregat3; break;
      case 4: *aggregat = header->Aggregat4; break;
      case 5: *aggregat = header->Aggregat5; break;
      case 6: *aggregat = header->Aggregat6; break;
      case 7: *aggregat = header->Aggregat7; break;
      case 8: *aggregat = header->Aggregat8; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Set_Aggregat(void * buf, signed_16 index, unsigned_8 aggregat)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: header->Aggregat = aggregat; break;
      case 2: header->Aggregat2 = aggregat; break;
      case 3: header->Aggregat3 = aggregat; break;
      case 4: header->Aggregat4 = aggregat; break;
      case 5: header->Aggregat5 = aggregat; break;
      case 6: header->Aggregat6 = aggregat; break;
      case 7: header->Aggregat7 = aggregat; break;
      case 8: header->Aggregat8 = aggregat; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Get_ScrewSuckBack(void * buf, signed_16 index, signed_16 * screw_suck_back)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: *screw_suck_back = header->ScrewSuckBack; break;
      case 2: *screw_suck_back = header->ScrewSuckBack2; break;
      case 3: *screw_suck_back = header->ScrewSuckBack3; break;
      case 4: *screw_suck_back = header->ScrewSuckBack4; break;
      case 5: *screw_suck_back = header->ScrewSuckBack5; break;
      case 6: *screw_suck_back = header->ScrewSuckBack6; break;
      case 7: *screw_suck_back = header->ScrewSuckBack7; break;
      case 8: *screw_suck_back = header->ScrewSuckBack8; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

int Set_ScrewSuckBack(void * buf, signed_16 index, signed_16 screw_suck_back)
{
   FMFAT_BUFFER_T * fmfat_buf = buf;
   FILE_HEADER * header = fmfat_buf->header;
   switch (index) {
      case 1: header->ScrewSuckBack = screw_suck_back; break;
      case 2: header->ScrewSuckBack2 = screw_suck_back; break;
      case 3: header->ScrewSuckBack3 = screw_suck_back; break;
      case 4: header->ScrewSuckBack4 = screw_suck_back; break;
      case 5: header->ScrewSuckBack5 = screw_suck_back; break;
      case 6: header->ScrewSuckBack6 = screw_suck_back; break;
      case 7: header->ScrewSuckBack7 = screw_suck_back; break;
      case 8: header->ScrewSuckBack8 = screw_suck_back; break;
      default: return _E_OUT_OF_RANGE;
   }   
   return 0;
}

FMFAT_BUFFER_T * NewFatBuffer(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_CALLBACK_MODULE_T * module)
{
   int ret, header_len;
   FMFAT_BUFFER_T * fmfat_buf;

   if ((fmfat_buf = HAlloc(sizeof(*fmfat_buf))) != NULL) {
      fmfat_buf->Module = module;
      if ((header_len = ReadHeader(fbuf, fmfat_buf)) > 0) {
         if ((ret = ReadSubfiles(fbuf, fmfat_buf, header_len)) == 0) {
            fmfat_buf->GetRegVal = GetRegVal;
            fmfat_buf->SetRegVal = SetRegVal;
            fmfat_buf->GetRegValI = GetRegValI;
            fmfat_buf->SetRegValI = SetRegValI;
            fmfat_buf->GetText = GetText;
            fmfat_buf->SetText = SetText;
            fmfat_buf->GetTextRow = GetTextRow;
            fmfat_buf->SetTextRow = SetTextRow;
            fmfat_buf->GetHeatParam = GetHeatParam;
            fmfat_buf->SetHeatParam = SetHeatParam;
            fmfat_buf->GetRegCount = GetRegCount;
            fmfat_buf->GetZoneCount = GetZoneCount;
            fmfat_buf->GetUnitCount = GetUnitCount;
            fmfat_buf->GetStoredZones = GetStoredZones;
            // header general values
            fmfat_buf->Get_Date = Get_Date;
            fmfat_buf->Set_Date = Set_Date;
            fmfat_buf->Get_MaxAgg = Get_MaxAgg;
            fmfat_buf->Set_MaxAgg = Set_MaxAgg;
            fmfat_buf->Get_MashSize = Get_MashSize;
            fmfat_buf->Set_MashSize = Set_MashSize;
            fmfat_buf->Get_Version = Get_Version;
            fmfat_buf->Set_Version = Set_Version;
            fmfat_buf->Get_HeaderSize = Get_HeaderSize;
            fmfat_buf->Set_HeaderSize = Set_HeaderSize;
            fmfat_buf->Get_FileType = Get_FileType;
            fmfat_buf->Set_FileType = Set_FileType;
            fmfat_buf->Get_RegType = Get_RegType;
            fmfat_buf->Set_RegType = Set_RegType;
            fmfat_buf->Get_ProgNr = Get_ProgNr;
            fmfat_buf->Set_ProgNr = Set_ProgNr;
            fmfat_buf->Get_VersMash = Get_VersMash;
            fmfat_buf->Set_VersMash = Set_VersMash;
            fmfat_buf->Get_VersStruct = Get_VersStruct;
            fmfat_buf->Set_VersStruct = Set_VersStruct;
            fmfat_buf->Get_VersExtra = Get_VersExtra;
            fmfat_buf->Set_VersExtra = Set_VersExtra;
            fmfat_buf->Get_Reserved1 = Get_Reserved1;
            fmfat_buf->Set_Reserved1 = Set_Reserved1;
            fmfat_buf->Get_Reserved2 = Get_Reserved2;
            fmfat_buf->Set_Reserved2 = Set_Reserved2;
            // header specific values
            fmfat_buf->Get_MouldOpWay = Get_MouldOpWay;
            fmfat_buf->Set_MouldOpWay = Set_MouldOpWay;
            fmfat_buf->Get_PlastWay = Get_PlastWay;
            fmfat_buf->Set_PlastWay = Set_PlastWay;
            fmfat_buf->Get_HeatZoneCount = Get_HeatZoneCount;
            fmfat_buf->Set_HeatZoneCount = Set_HeatZoneCount;
            fmfat_buf->Get_MaxSpritzDruck = Get_MaxSpritzDruck;
            fmfat_buf->Set_MaxSpritzDruck = Set_MaxSpritzDruck;
            fmfat_buf->Get_MouldInPres = Get_MouldInPres;
            fmfat_buf->Set_MouldInPres = Set_MouldInPres;
            fmfat_buf->Get_Diameter = Get_Diameter;
            fmfat_buf->Set_Diameter = Set_Diameter;
            fmfat_buf->Get_PresConst = Get_PresConst;
            fmfat_buf->Set_PresConst = Set_PresConst;
            fmfat_buf->Get_Aggregat = Get_Aggregat;
            fmfat_buf->Set_Aggregat = Set_Aggregat;
            fmfat_buf->Get_ScrewSuckBack = Get_ScrewSuckBack;
            fmfat_buf->Set_ScrewSuckBack = Set_ScrewSuckBack;
            // header texts
            fmfat_buf->Get_MashType = Get_MashType;
            fmfat_buf->Set_MashType = Set_MashType;
            fmfat_buf->Get_MatNr = Get_MatNr;
            fmfat_buf->Set_MatNr = Set_MatNr;
            fmfat_buf->Get_ToolNr = Get_ToolNr;
            fmfat_buf->Set_ToolNr = Set_ToolNr;
            fmfat_buf->Get_InfoText = Get_InfoText;
            fmfat_buf->Set_InfoText = Set_InfoText;
            return fmfat_buf;
         } else {
            _LastError = ret;
            _Line = __LINE__;
            DeleteFatBuffer(fmfat_buf);
            return NULL;
         }
      } else {
         _LastError = header_len;
         _Line = __LINE__;
         DeleteFatBuffer(fmfat_buf);
         return NULL;
      }
   } else {
      _LastError = _E_MEMORY_ALLOC;
      _Line = __LINE__;
      return NULL;
   }
}

int DeleteFatBuffer(FMFAT_BUFFER_T * fmfat_buf)
{
   int i, j;
   if (fmfat_buf->header != NULL) {
      HFree(fmfat_buf->header);
      fmfat_buf->header = NULL;
   }
   if (fmfat_buf->subfile_tab != NULL) {
      if (fmfat_buf->subfile_tab->subfile_buf != NULL) {
         HFree(fmfat_buf->subfile_tab->subfile_buf);
         fmfat_buf->subfile_tab->subfile_buf = NULL;
      }
      HFree(fmfat_buf->subfile_tab);
      fmfat_buf->subfile_tab = NULL;
   }
   for (i=0; i<MAX_SUBFILES; i++) {
      if (fmfat_buf->subfile[i] != NULL) {
         SUBFILE_T * subfile = fmfat_buf->subfile[i];
         if (subfile->buffer != NULL) {
            HFree(subfile->buffer);
            subfile->buffer = NULL;
         }
         HFree(fmfat_buf->subfile[i]);
         fmfat_buf->subfile[i] = NULL;
      }
   }
   for (i=0; i<MAX_TEXTS; i++) {
      if (fmfat_buf->text[i] != NULL) {
         TEXT_T * text = fmfat_buf->text[i];
         if (text->buffer != NULL) {
            HFree(text->buffer);
            text->buffer = NULL;
         }
         HFree(fmfat_buf->text[i]);
         fmfat_buf->text[i] = NULL;
      }
   }
   for (i=0; i<MAX_REGS; i++) {
      if (fmfat_buf->reg[i] != NULL) {
         REGISTER_T * reg = fmfat_buf->reg[i];
         if (reg->buffer != NULL) {
            HFree(reg->buffer);
            reg->buffer = NULL;
         }
         HFree(fmfat_buf->reg[i]);
         fmfat_buf->reg[i] = NULL;
      }
   }
   for (i=0; i<MAX_HEAT_GROUPS; i++) {
      if (fmfat_buf->heatgroup[i] != NULL) {
         HEATGROUP_T * heatgroup = fmfat_buf->heatgroup[i];
         for (j=0; j<MAX_ZONES; j++) {
            if (heatgroup->zone[j] != NULL) {
               ZONE_T * zone = heatgroup->zone[j];
               if (zone->buffer != NULL) {
                  HFree(zone->buffer);
                  zone->buffer = NULL;
               }
               HFree(heatgroup->zone[j]);
               heatgroup->zone[j] = NULL;
            }
         }
         HFree(fmfat_buf->heatgroup[i]);
         fmfat_buf->heatgroup[i] = NULL;
      }
   }
   HFree(fmfat_buf);
   return 0;
}


