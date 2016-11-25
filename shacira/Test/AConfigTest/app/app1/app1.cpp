
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "string"
#include "liba.h"
typedef std::string STRING_T;

void hello()
{
   printf("hello app1\n");
}

int main1(int argc, char* argv[])
{
   printf("\n\n");
   liba a;
   a.print();
   a.print();
   hello();
   return 0;
}

