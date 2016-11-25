
#include <stdio.h>

int shrm(int argc, char* argv[])
{
   if (argc < 2) {
      printf("no file specified\n");
      return -1;
   } else if (argc == 2) {
      const char * file_name = argv[1];
      int rc = remove(file_name);
      if (rc == 0) {
         return -1;
      } else {
         return 0;
      }
   } else {
      printf("too much params specified\n");
      return -1;
   }
}

int main(int argc, char* argv[])
{
   return shrm(argc, argv);
}
