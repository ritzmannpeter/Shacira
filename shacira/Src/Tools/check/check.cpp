
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
   fprintf(stderr, "checkqt 1.0 Copyright 2013 2i Industrial Informatics GmbH \n");
   if (argc == 2) {
      int requestedVersion = atoi(argv[1]);
      if (requestedVersion < 3 || requestedVersion > 5 ) {
         fprintf(stderr, "requesting qt version %d is impossible\n", requestedVersion);
         return -1;
      }
      string qtDir = getenv("QTDIR");
      if (qtDir.empty()) {
         fprintf(stderr, "no QTDIR environment variable set\n");
         return -1;
      } 
      fprintf(stderr, "QTDIR is %s\n", qtDir.c_str());
      int foundVersion = 0;
      int pos = qtDir.find("3");
      if (pos >= 0) {
         foundVersion = 3;
      }
      pos = qtDir.find("4");
      if (pos >= 0) {
         foundVersion = 4;
      }
      pos = qtDir.find("5");
      if (pos >= 0) {
         foundVersion = 5;
      }
      if (foundVersion == 0) {
         fprintf(stderr, "cannot detect version in %s\n", qtDir.c_str());
         return -1;
      }
      if (foundVersion != requestedVersion) {
         fprintf(stderr, "version %d requested\n", requestedVersion);
         fprintf(stderr, "version %d active\n", foundVersion);
         fprintf(stderr, "this is not the requested version\n");
         return -1;
      }
      fprintf(stderr, "version %d requested\n", requestedVersion);
      fprintf(stderr, "version %d active\n", foundVersion);
   } else {
      fprintf(stderr, "please specify a the requested Qt version\n");
   }
   return 0;
}

