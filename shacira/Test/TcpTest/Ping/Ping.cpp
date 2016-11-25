
#include "cSocketApi.h"
#include <stdio.h>

static bool _HostReached = false;
static void HostReached(const char * ip_address, int c1, int c2, int c3, int c4, unsigned long time)
{
   printf("host %s ip %d.%d.%d.%d msecs %d\n", ip_address, c1, c2, c3, c4, time);
   _HostReached = true;
}

extern void f();
int main(int argc, char **argv)
{
#ifdef TEST_TEMPLATE
f();
return 0;
#endif
   if (argc != 2) {
      printf("usage: Ping <spec>\n");
   } else {
      for (int i=0; i<5; i++) {
         printf("Ping %s\n", argv[1]);
         _HostReached = false;
         cSocketApi::Ping(argv[1], HostReached, 200);
         if (!_HostReached) {
            printf("no host reached\n");
         }
      }
   }
   return 0;
}

