/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [bin_dump.c]           Binary Image Dump Utility                         */
/*                                                                          */
/* Copyright (c) 1994 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "binimg.h"
#include "stdosx.h"
#include "literal.h"

#include "bin__cim.h"

static void dumpLine(int loc, string txt)
{ int i;
  printf("%04x : ",loc&0xfff0);
  for (i = 0; i < 16; i++)
  {
    if (i <= (loc&15))
      printf(" %02x",txt[i]&0xff);
    else
      printf("   ");
  }
  printf("  |");
  for (i = 0; i < 16; i++)
  {
    if (i <= (loc&15))
      //printf("%c", 32 <= txt[i] && txt[i] <= 126 ? txt[i] : '.');
      printf("%c", isascii(txt[i]) && isprint(txt[i]) ? txt[i] : '.');
    else
      printf(" ");
  }
  printf("|\n");
}

void PackerReport(void)
/* inactive since interfacing */
{
/*
  BytesIn -= 1; /-* wg. EOF *-/
  printf("\n");
  printf("Packer Quality Report\n");
  printf("\n");
  printf("in  : %8ld : 100.00 %%\n",BytesIn);
  if (BytesIn != 0)
    printf("out : %8ld : %3ld.%02ld %%\n",BytesOut,
                  100*BytesOut/BytesIn,(10000*BytesOut/BytesIn)%100);
  else
    printf("out : %8ld : 100.00 %%\n",BytesOut);
*/
}

void getDump(string FileName)
/* dump utility */
{ string Tit, Mag, tmp; byte Ma, Mi, Bv;
  int i,cc; char txt[16];
  getBgn("",FileName,"");
  getHeaderInfo(&Tit, &Mag, &Ma, &Mi, &Bv);
  tmp = LIT_c_str_lit(Tit); printf("Title: %s\n",tmp); FreeMem(tmp);
  tmp = LIT_c_str_lit(Mag); printf("Magic: %s\n",tmp); FreeMem(tmp);
  printf("Major:  %d\n",Ma);
  printf("Minor:  %d\n",Mi);
  printf("Bvers:  %d\n",Bv);
  FreeMem(Tit); FreeMem(Mag);
  printf("\n");
  for (i=0,cc=getByte_or_EOF(); cc != EOF; i+=1,cc=getByte_or_EOF())
  {
    txt[i&15] = cc;
    if ((i&15) == 15) dumpLine(i,txt);
  }
  if ((i&15) != 0) dumpLine(i-1,txt);
  getEnd();
  PackerReport();
}

int main(int argc, string argv[])
{
  CTX_init_bin_dump(argc,argv);
  getDump(CTX_EVAL(string,"Filename"));
  CTX_quit();
  BUG_CORE;
  return(0);
}
