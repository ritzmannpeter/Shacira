
#include "Tools/utilities/utilities.h"

int Where(int argc, char* argv[])
{
   try {
      char find_buf[512] = {0};
      const char * file_name = argv[1];
      if (file_name != NULL) {
         char path_list[2048] = {0};
         GetWorkingDirectory(path_list, sizeof(path_list));
         path_list[strlen(path_list)] = ';';
         strcpy(&path_list[strlen(path_list)], getenv("path"));
         const char * found_path = SearchFile(file_name,
                                              find_buf,
                                              sizeof(find_buf),
                                              path_list);
         if (found_path != NULL) {
            char file_time[32] = {0};
            FileTime(found_path, file_time, sizeof(file_time));
            printf("found file %s in %s Time is %s\n",
                   file_name, found_path,
                   file_time);
         } else {
            printf("file %s not found\n", file_name);
         }
      } else {
         printf("please specify the name of a binary object\n");
      }
   } catch (...) {
      printf("unhandled exception executing where\n");
      return -1;
   }
   return 0;
}

int main(int argc, char* argv[])
{
   return Where(argc, argv);
}

