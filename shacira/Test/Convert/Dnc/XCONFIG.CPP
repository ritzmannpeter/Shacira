
#pragma hdrstop
#include <condefs.h>
#include "cVariables.h"
#include "FMFATFile.h"

//---------------------------------------------------------------------------
USEUNIT("cVariables.cpp");
USEUNIT("cParse.cpp");
USEUNIT("..\cChapter.cpp");
USEUNIT("..\..\ecl\base\eb_base.cpp");
USEUNIT("..\..\ecl\base\eb_collect.cpp");
USEUNIT("..\..\ecl\base\eb_str.cpp");
USEUNIT("..\..\ecl\base\eb_prof.cpp");
USEUNIT("..\..\ecl\base\eb_err.cpp");
USEUNIT("FMFatFile.c");
USEUNIT("FileBuffer.c");
USEUNIT("HAlloc.c");
//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
   const char * data_file = "material.111";
   const char * config_file = ".\\test.ini";
   FILE_BUFFER_T * fbuf = NewFileBuffer(data_file);
   if (fbuf == NULL) {
      printf("failed to read data file %s\n", data_file);
      return 0;
   }
   FMFAT_BUFFER_T * fmfat_buf = NewFatBuffer(fbuf, NULL);
   if (fmfat_buf == NULL) {
      int err = GetLastErr();
      printf("failed to read data file %s: %d\n", data_file, err);
      return 0;
   }
   cVariables * variables = new cVariables(".\\test.ini", fmfat_buf);
   cVariable * variable = variables->Variable("sepp");
   string value;
   if (variable != NULL) {
      variable->GetValue(value);
      int dummy = 0;
   }
   const char * name = "heinz";
   variables->GetValue(name, value);
   printf("variable %s: value %s\n", name, value.c_str());
   name = "sepp";
   variables->GetValue(name, value);
   printf("variable %s: value %s\n", name, value.c_str());
   name = "juri";
   variables->GetValue(name, value);
   printf("variable %s: value %s\n", name, value.c_str());
   name = "werkzeugnummer";
   variables->GetValue(name, value);
   printf("variable %s: value %s\n", name, value.c_str());
   name = "sollwert_zylinderzone1";
   variables->GetValue(name, value);
   printf("variable %s: value %s\n", name, value.c_str());
   return 0;
}
