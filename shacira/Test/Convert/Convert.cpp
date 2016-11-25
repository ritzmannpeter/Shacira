

#include <syntax.h>
#define USE_ALL_ISCOSBIT
#define USE_ALL_IQTREG
#define IMPORT_NOT_GLOBAL
#define IMPORT_FLTFUNC
#include <iqtdstr.h>
#include <symreg.h>
#include <symbit.h>
#include <spsdiag.h>

extern "C" {
extern const IQTREG_TYPE IqtRegTab[];
extern const ISCOSBIT_TYPE IscosBitTab[];
extern const ISCOSREG_TYPE IscosRegTab[];
}

#include <malloc.h>
#include <stdio.h>

enum SymbolType {symbit, symreg, iqtreg};
#define MAX_ENTRIES  0x10000
static const char ** _SymBitTextTable = (const char **)calloc(1, MAX_ENTRIES * sizeof(const char *));
static const char ** _SymRegTextTable = (const char **)calloc(1, MAX_ENTRIES * sizeof(const char *));
static const char ** _IqtRegTextTable = (const char **)calloc(1, MAX_ENTRIES * sizeof(const char *));

static void AddSymBitText(unsigned long symbol, const char * text)
{
   _SymBitTextTable[symbol] = text;
}

static void AddSymRegText(unsigned long symbol, const char * text)
{
   _SymRegTextTable[symbol] = text;
}

static void AddIqtRegText(unsigned long reg_no, const char * text)
{
   _IqtRegTextTable[reg_no] = text;
}

static void AddText(unsigned long id, const char * text, SymbolType type)
{
   if (type == symbit) {
      AddSymBitText(id, text);
   } else if (type == symreg) {
      AddSymRegText(id, text);
   } else if (type == iqtreg) {
      AddIqtRegText(id, text);
   }
}

static const char * SymBitText(unsigned long symbol)
{
   return _SymBitTextTable[symbol];
}

static const char * SymRegText(unsigned long symbol)
{
   return _SymRegTextTable[symbol];
}

static const char * IqtRegText(unsigned long reg_no)
{
   return _IqtRegTextTable[reg_no];
}

static char * AllocText(char * text)
{
   char * text_ptr = text;
   int len = strlen(text);
   while (42) {
      char c = *text_ptr;
      if (c == ' ' ||
          c == '/' ||
          c == '*') {
         text_ptr++;
      } else {
         break;
      }
   }
   int i = 0;
   bool done = false;
   for (i=len; i>=0; i--) {
      char c = text[i];
      if (c == ' ' ||
          c == '/' ||
          c == '*' ||
          c == '\0' ||
          c == '\n') {
      } else if (c == ';') {
         text[i] = ' ';
      } else {
         if (!done) {
            text[i+1] = '\0';
            done = true;
         }
      }
   }
   len = strlen(text_ptr);
   if (len > 0) {
      char * new_text = (char*)calloc(1, len + 1);
      memcpy(new_text, text_ptr, len);
      return new_text;
   } else {
      return "";
   }
}

static void GetComments(const char * file_name, SymbolType type)
{
   FILE * stream = fopen(file_name, "r");
   if (stream != NULL) {
      char line [0x400] = {0};
      char * line_ptr = NULL;
      char symbol[0x200] = {0};
      unsigned long definition = 0;
      while ((line_ptr = fgets(line, sizeof(line), stream)) != NULL) {
         if (strlen(line) > 0) {
            bool success = false;
            memset(symbol, 0, sizeof(symbol));
            int nscan = 0;
            const char * fmt = NULL;
            if (type == symbit) {
               fmt = "#define %s %x %n";
            } else if (type == symreg) {
               fmt = "#define %s %x %n";
            } else if (type == iqtreg) {
               fmt = "#define %s %d %n";
            }
            int params = sscanf(line_ptr, fmt, symbol, &definition, &nscan);
            if (params == 2) {
               char * text_ptr = line_ptr + nscan;
               char * text = AllocText(text_ptr);
               AddText(definition, text, type);
            }
         }
      }
      fclose(stream);
   }
}

static void GetComments()
{
   GetComments("iqtreg.h", iqtreg);
   GetComments("robreg.h", iqtreg);
   GetComments("symbit.h", symbit);
   GetComments("symreg.h", symreg);
   GetComments("symreg2.h", symreg);
}

static void PrintTextTable()
{

   const IQTREG_TYPE * iqtreg_ptr = &IqtRegTab[0];
   while (42) {
      bool disk_reg = false;
      unsigned short reg_no = iqtreg_ptr->RegNr;
      if (reg_no == 0xffff) {
         break;
      }
      unsigned short reg_type = iqtreg_ptr->RegType;
      if (reg_type & REG_DISK_TOOL) {
         disk_reg = true;
      }
      if (reg_type & REG_DISK_PG) {
         disk_reg = true;
      }
      if (reg_type & REG_DISK_CORE) {
         disk_reg = true;
      }
      if (disk_reg) {
         const char * text = IqtRegText(reg_no);
         printf("%d;%s;\n", reg_no, text);
      }
      iqtreg_ptr++;
   }
   const ISCOSREG_TYPE * iscosreg_ptr = &IscosRegTab[0];
   while (42) {
      bool disk_reg = false;
      unsigned short reg_no = iscosreg_ptr->RegNr;
      if (reg_no == 0xffff) {
         break;
      }
      unsigned short reg_type = iscosreg_ptr->RegType;
      if (reg_type & REG_DISK_TOOL) {
         disk_reg = true;
      }
      if (reg_type & REG_DISK_PG) {
         disk_reg = true;
      }
      if (reg_type & REG_DISK_CORE) {
         disk_reg = true;
      }
      if (disk_reg) {
         unsigned long symbol = iscosreg_ptr->IscosAdr;
         const char * text = SymRegText(symbol);
         printf("%d;%s;\n", reg_no, text);
      }
      iscosreg_ptr++;
   }
   const ISCOSBIT_TYPE * iscosbit_ptr = &IscosBitTab[0];
   while (42) {
      bool disk_reg = false;
      unsigned short bit_no = iscosbit_ptr->RegNr;
      if (bit_no == 0xffff) {
         break;
      }
      unsigned short reg_type = iscosbit_ptr->RegType;
      if (reg_type & REG_DISK_TOOL) {
         disk_reg = true;
      }
      if (reg_type & REG_DISK_PG) {
         disk_reg = true;
      }
      if (reg_type & REG_DISK_CORE) {
         disk_reg = true;
      }
      if (disk_reg) {
         unsigned long symbol = (iscosbit_ptr->IscosAdr * 0x10) + iscosbit_ptr->LogAdr;
         const char * text = SymBitText(symbol);
         printf("%d;%s;\n", bit_no, text);
      }
      iscosbit_ptr++;
   }
}

int main(int argc, char* argv[])
{
   GetComments();
   PrintTextTable();
   return 0;
}

