
#include "cextprocess.h"
#if defined(_WIN32)
#include <process.h>
#endif

int cExtProcess::Execute(int argc, char* argv[])
{
#if defined(_WIN32)
   int err = spawnlp(P_WAIT, argv[0],
                     argv[0], argv[1], argv[2], argv[3], argv[4],
                     argv[5], argv[6], argv[7], argv[8], argv[9],
                     argv[10], argv[11], argv[12], argv[13], argv[14]);
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
   return err;
}


