
#include "Tools/utilities/fsysutils.h"

static int mkdir(const char * directory)
{
   CreateDir(directory);
   return 0;
}

static int shmkdir(int argc, char* argv[])
{
   if (argc < 2) {
      printf("no file specified\n");
      return -1;
   } else if (argc == 2) {
      const char * dir_name = argv[1];
      return mkdir(dir_name);
   } else {
      printf("too much params specified\n");
      return -1;
   }
}

int main(int argc, char* argv[])
{
   return shmkdir(argc, argv);
}
