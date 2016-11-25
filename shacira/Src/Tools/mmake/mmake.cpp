

#include "cBuildEntry.h"
#include "cMakeConfig.h"

cMakeConfig * _MakeConfig = NULL;

static char _Text[0x10000] = {0};
static void Printf(const char * fmt_str, ...)
{
   va_list ap;
   va_start(ap, fmt_str);
   vsprintf(_Text, fmt_str, ap);
   printf("%s", _Text);
   FILE * stream = fopen("temp.txt", "a");
   if (stream != NULL) {
      fprintf(stream, "%s", _Text);
      fclose(stream);
   }
   va_end(ap);
}

static void AddFile(const char * file_name, const char * path)
{
   if (!_MakeConfig->FileExcluded(file_name)) {
      char buf[0x400] = {0};
      sprintf(buf, "%s/%s", path, file_name);
      cBuildEntry * entry = new cBuildEntry(_MakeConfig, buf);
   } else {
      int dummy = 0;
   }
}

int Find(const char * path)
{
   WIN32_FIND_DATA find_data;
   HANDLE hFind;
   char spec[0x400] = {0};
   if (strlen(path) > 0) {
      sprintf(spec, "%s/*", path);
   } else {
      sprintf(spec, "*");
   }
   hFind = FindFirstFile(spec, &find_data);
   if (hFind != INVALID_HANDLE_VALUE) {
      int found = 1;
      while (found) {
         if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            STRING_T file_name = find_data.cFileName;
            AddFile(file_name.c_str(), path);
         }
         found = FindNextFile(hFind, &find_data);
      }
      FindClose(hFind);
   }
   hFind = FindFirstFile(spec, &find_data);
   if (hFind != INVALID_HANDLE_VALUE) {
      int found = 1;
      while (found) {
         if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (find_data.cFileName[0] != '.') {
               if (!_MakeConfig->DirExcluded(find_data.cFileName)) {
                  if (strlen(path) > 0) {
                     sprintf(spec, "%s/%s", path, (const char*)find_data.cFileName);
                  } else {
                     sprintf(spec, "%s", path, (const char*)find_data.cFileName);
                  }
                  Find(spec);
               }
            }
         }
         found = FindNextFile(hFind, &find_data);
      }
      FindClose(hFind);
   }
   return 0;
}

int mmake(int argc, char* argv[])
{
   const char * build_name = "debug";
   if (argc > 1) {
      build_name = argv[1];
   }
   _MakeConfig = new cMakeConfig(build_name, "build.cfg");
   _MakeConfig->Analyse();
   _MakeConfig->BuildMakeFile();
   return 0;
}

int main(int argc, char* argv[])
{
   return mmake(argc, argv);
}
