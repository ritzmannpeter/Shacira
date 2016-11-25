
#include "global_defs.h"
#include "cextprocess.h"
#include "cdirectoryutils.h"

static void Usage()
{
   printf("usage:\n");
   printf("   styxw <input file> options\n");
   printf("       options:\n");
   printf("         -o <output file>\n");
   printf("         styx options\n");
   printf("\n");
   printf("\n");
}

int main(int argc, char* argv[])
{
   STRING_LIST_T arg_list;
   STRING_T path;
   STRING_T file;
   STRING_T destination;
   STRING_T destination_file;
   STRING_T language = "unknown";
   const char * name = "styx";
   const char * input_file = NULL;
   const char * output_file = NULL;
   const char * args[20] = {0};
   args[0] = name;
   int i = 0;
   for (i=1; i<argc; i++) {
      if (strnicmp(argv[i], "-o ", 3) == 0) {
         output_file = argv[i];
      } else if (strnicmp(argv[i], "-o", 2) == 0) {
         output_file = &(argv[i][2]);
      } else if (strnicmp(argv[i], "-", 1) == 0) {
//         args[i] = argv[i];
         arg_list.push_back(argv[i]);
      } else {
         input_file = argv[i];
         cDirectoryUtils::RightSplit(input_file, path, file);
         char lang[0x40] = {0};
         char ext[0x40] = {0};
         int params = sscanf(file.c_str(), "%[^.].%s", lang, ext);
         if (params == 2) {
            language = lang;
         }
      }
   }
   args[1] = language.c_str();
   int arg_index = 2;
   STRING_LIST_T::const_iterator s = arg_list.begin();
   while (s != arg_list.end()) {
      args[arg_index] = (*s).c_str();
      arg_index++;
      s++;
   }
   if (input_file == NULL) {
      if (output_file == NULL) {
         printf("no input file and no output file specified\n");
         Usage();
         return -1;
      } else {
         printf("no input file specified\n");
         Usage();
         return -1;
      }
   }
   if (output_file == NULL) {
      printf("no output file specified\n");
      Usage();
      return -1;
   }
   cDirectoryUtils::RightSplit(output_file, destination, destination_file);
   destination_file = cDirectoryUtils::AppendPath(destination.c_str(), file.c_str());
   cDirectoryUtils::CopyFile(input_file, destination_file.c_str());
   printf("wstyx input = %s output = %s path = %s file = %s language = %s destination = %s\n",
          input_file, output_file,
          path.c_str(), file.c_str(), language.c_str(),
          destination_file.c_str());
   i = 0;
   const char * arg = args[i];
   printf("command:");
   while (arg != NULL) {
      printf(" %s", arg);
      i++;
      arg = args[i];
   }
   STRING_T current_dir = cDirectoryUtils::CurrentDir();
   int rc = 0;
   if (cDirectoryUtils::SetCurrentDir(destination.c_str())) {
      try {
         rc = cExtProcess::Execute(argc, (char**) args);
         if (rc == 0) {
            memset(args, 0, sizeof(args));
            args[0] = "ctoh";
            rc = cExtProcess::Execute(1, (char**) args);
         }
      } catch (...) {
      }
      if (!cDirectoryUtils::SetCurrentDir(current_dir.c_str())) {
         return -1;
      }
   }
   return rc;
}

