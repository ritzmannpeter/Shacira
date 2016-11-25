
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "string"
#include "liba.h"
typedef std::string STRING_T;

extern void hello();

int main3(int argc, char* argv[])
{
   printf("\n\n");
   liba a;
   a.print();
   a.print();
   hello();
   printf("said hello\n");
   return 0;
}

