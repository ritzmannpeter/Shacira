
#include "FirstHeader.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/cTokenizer.h"
#include "System/Sys/cSHFile.h"

static STRING_T _BaseName;
static STRING_T _VariantName;

static STRING_T _BaseFile;
static STRING_T _VariantFile;

static char _SrcLineBuf[0x4000] = {0};
static char _DstLineBuf[0x4000] = {0};

static void Transform(char * src, char * dst, size_t dst_size)
{
   int params = 0;
   char path[0x1000] = {0};
   if ((params = sscanf(src, "SOURCE=.\\%s", path)) == 1) {
      SafePrintf(dst, dst_size, "SOURCE=..\\%s", path);
   } else if ((params = sscanf(src, "SOURCE=..\\%s", path)) == 1) {
      SafePrintf(dst, dst_size, "SOURCE=..\\..\\%s", path);
   } else {
      STRING_T str = src;
      STRING_T new_str = cStringUtils::Replace(str, _BaseName.c_str(), _VariantName.c_str());
      SafePrintf(dst, dst_size, "%s", new_str.c_str());
   }
}

int main(int argc, char* argv[])
{
   cResources(argc, argv);
   cResources::GetOption("bname", _BaseName);
   cResources::GetOption("vname", _VariantName);

   _BaseFile = "../";
   _BaseFile += _BaseName.c_str();
   _BaseFile += ".dsp";

   _VariantFile += _VariantName.c_str();
   _VariantFile += ".dsp";

   if (!cFileSystemUtils::FileExists(_BaseFile.c_str())) {
      fprintf(stderr, "base project file %s not found\n", _BaseFile.c_str());
      return 1;
   }
   if (cFileSystemUtils::FileExists(_VariantFile.c_str())) {
      fprintf(stderr, "variant project file %s already existing\n", _VariantFile.c_str());
      return 1;
   }
   cSHFile input_file(_BaseFile.c_str());
   cSHFile output_file(_VariantFile.c_str());
   if (input_file.Open(FILE_ACCESS_READ_ONLY) &&
       output_file.Open(FILE_ACCESS_APPEND)){
      while (input_file.ReadLine(_SrcLineBuf, sizeof(_SrcLineBuf))) {
         Transform(_SrcLineBuf, _DstLineBuf, sizeof(_DstLineBuf));
         printf("%s\n", _DstLineBuf);
         output_file.Write(_DstLineBuf, strlen(_DstLineBuf));
         output_file.Write("\n", 1);
         memset(_SrcLineBuf, 0, sizeof(_SrcLineBuf));
         memset(_DstLineBuf, 0, sizeof(_DstLineBuf));
      }
   }
   return 0;
}

