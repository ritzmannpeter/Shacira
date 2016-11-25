

#include <stdarg.h>
#include "abuild.h"
#include "cAutoProject.h"
#include "cDirectoryUtils.h"
#include "cPath.h"
#include "cSource.h"
#include "cVirtualFileSystem.h"
#include "Base/cValue.h"

#define LOG_FILE        "e:/temp/abuild/abuild.log"

STRING_T Compiler()
{
   return "vcpp";
//   return "gcc";
}

STRING_T System()
{
   return "win32";
//   return "linux";
}

static char _IntermediateDirectory[0x200] = {0};
const char * IntermediateDirectory()
{
   if (_IntermediateDirectory[0] == 0) {
      sprintf(_IntermediateDirectory, "%s_%s", System().c_str(), Compiler().c_str());
   }
   return _IntermediateDirectory;
}

void ParseError(const char * fmt_str, ...)
{
}

static char _Text[0x20000] = {0};
void Printf(const char * fmt_str, ...)
{
   va_list args;
   va_start(args, fmt_str);
   try {
      vsprintf(_Text, fmt_str, args);
      printf("%s", _Text);
      FILE * stream = fopen(LOG_FILE, "a");
      if (stream != NULL) {
         fprintf(stream, "%s", _Text);
         fclose(stream);
      }
   } catch (...) {
   }
}

static cVirtualFileSystem _Vfs;

void AddVFS(const char * path)
{
   STRING_T npath = cPath::Normalize(path);
   _Vfs.AddPath(npath.c_str());
}

bool FindVFS(const char * path)
{
   bool success = _Vfs.FindPath(path);
   if (success) {
      return true;
   } else {
      return false;
   }
}

int abuild(int argc, char* argv[])
{
   remove(LOG_FILE);
   const char * build_spec = "build.cfg";
   if (argc > 1) {
      build_spec = argv[1];
   }
   cAutoProject auto_project(build_spec);
   if (auto_project.Parse()) {
      STRING_LIST_T strings;
      auto_project.IncludeDirectories(strings, cDirectoryUtils::CurrentDir().c_str());
      STRING_LIST_T::const_iterator i = strings.begin();
      Printf("\ninclude directories:\n");
      while (i != strings.end()) {
         Printf("%s\n", (*i).c_str());
         cPath p((*i).c_str());
         bool exists = p.Exists();
         if (exists) {
            bool dir = p.IsDirectory();
            if (!dir) {
               Printf("this path is no directory\n");
            }
         } else {
            Printf("this path doesnt exist\n");
         }
         i++;
      }
      strings.clear();
      auto_project.LibraryDirectories(strings, cDirectoryUtils::CurrentDir().c_str());
      i = strings.begin();
      Printf("\nlibrary directories:\n");
      while (i != strings.end()) {
         Printf("%s\n", (*i).c_str());
         cPath p((*i).c_str());
         bool exists = p.Exists();
         if (exists) {
            bool dir = p.IsDirectory();
            if (!dir) {
               Printf("this path is no directory\n");
            }
         } else {
            Printf("this path doesnt exist\n");
         }
         i++;
      }
      strings.clear();
      auto_project.Libraries(strings, cDirectoryUtils::CurrentDir().c_str());
      i = strings.begin();
      Printf("\nlibraries:\n");
      while (i != strings.end()) {
         Printf("%s\n", (*i).c_str());
         i++;
      }
      Printf("\nsources:\n");
      SOURCE_LIST_T sources;
      auto_project.Sources(sources);
      SOURCE_LIST_T::const_iterator so = sources.begin();
      while (so != sources.end()) {
         cSource * source = (*so);
         cPath * p = source->Path();
         bool exists = p->Exists();
         Printf("%s: %s\n", p->AbsolutePath().c_str(), source->TypeName().c_str());
         if (exists) {
//            Printf("%s\n", p->RelativePath(cDirectoryUtils::CurrentDir().c_str()).c_str());
//            Printf("%s: %s\n", p->AbsolutePath().c_str(), source->TypeName().c_str());
         } else {
            Printf("this source file doesnt exist\n");
         }
         so++;
      }
   }
   _Vfs.Print(0);
///   if (auto_project.Build()) {
///      return 0;
///   }
   STRING_T graph_file = cDirectoryUtils::FullPath("project.graph");
   auto_project.Show(graph_file.c_str());
   return 0;
}

int main(int argc, char* argv[])
{

   int rc = abuild(argc, argv);
   return rc;
}
