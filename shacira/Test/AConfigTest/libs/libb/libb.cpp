
#include "libb.h"
#include <stdio.h>
#include "libc.h"

libb::libb()
{
}

libb::~libb()
{
}

void libb::print()
{
   libc c;
   c.print();
   printf("libb\n");
}


