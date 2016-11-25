
#include "liba.h"
#include <stdio.h>
#include "libb.h"

liba::liba()
{
}

liba::~liba()
{
}

void liba::print()
{
   libb b;
   b.print();
   printf("liba\n");
}


