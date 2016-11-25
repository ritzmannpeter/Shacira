/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [reformat.c]               Reformats Sources                             */
/*                                                                          */
/* Copyright (c) 1994 by Lars D\olle, Heike Manns                           */
/* ------------------------------------------------------------------------ */

#ifdef DOCUMENT
Zusammenfassung

  "reformat" fuegt '\f'-Zeichen an geeigneten Stellen ein.

Parameter

| reformat Filename

#endif

#include "stdosx.h"
#include "pathes.h"
#include "line_scn.h"
#include "otab.h"

#include "refo_cim.h"

FILE *SysIn;
FILE *SysOut;

long srclin;
long pagenr;

#define PageLength CTX_EVAL(int,"PageLength")

ROW(ROW(string)) blocks;

bool is_section(ROW(string) blk)
/* whether a block starts a section  */
/* rule: first line contains "-----" */
{ string s; int i,len;
  if (OT_CNT(blk) < 1) return False;
  s=OT_GET(string,blk,0);
  len = strlen(s);
  if (*s != 0 && *s != ' ')
    for (i = 0; i < len-5; i++)
      if (!strncmp(s+i,"-----",5))
        return True;
  return False;
}

ROW(string) getBlock(void)
/* read a block */
{ string lin; long len;
  ROW(string) tab = OT_CREATE(string,primCopy,FreeMem,primEqual);
Skip:
  lin = Line_get(SysIn);
  if (lin == NULL)
    goto Done;
  len = strlen(lin);
  if (len == 0)
  {
    FreeMem(lin);
    goto Skip;
  }
Line:
  OT_T_INS(tab,lin);
  lin = Line_get(SysIn);
  if (lin == NULL)
    goto Done;
  len = strlen(lin);
  if (len == 0)
  {
    FreeMem(lin);
    goto Done;
  }
  goto Line;
Done:
  return tab;
}

void printPage(int nr_of_blocks)
{ int i;
  printf("%4ld | ",srclin);
  if (pagenr > 1)
  {
    fprintf(SysOut,"\f\n");
    printf(" "); srclin += 1;
  }
  for (i = 0; i < nr_of_blocks; i++)
  { ROW(string) r = OT_GET(ROW(string),blocks,i);
    long j,cnt = OT_CNT(r);
    if (i > 0)
    {
      fprintf(SysOut,"\n");
      printf(" "); srclin+=1;
    }
    for (j = 0; j < cnt; j++)
    {
      fprintf(SysOut,"%s\n",OT_GET(string,r,j));
      printf("*"); srclin+=1;
    }
    OT_DEL_T(r);
  }
  OT_DEL_ES(blocks,0,nr_of_blocks);
  pagenr += 1;
  printf("\n");
}

void addBlock(ROW(string) block)
{ int i; long sum = OT_CNT(blocks), cnt = sum+1, pos = 0;
  bool posfound = False;
  OT_PUSH(block,blocks);
  for (i = 0; i < cnt; i++)
  {
    sum += OT_CNT(OT_GET(ROW(string),blocks,i));
    if (i > 0 && !posfound && is_section(OT_GET(ROW(string),blocks,i)))
    {
      posfound = OT_CNT(OT_GET(ROW(string),blocks,i)) > 1;
      pos = i;
    }
  }
  if (posfound || sum >= PageLength)
    printPage((int)(pos ? pos : cnt-1));
}

void reformat(void)
{ ROW(string) tmp;
  blocks = OT_CREATE_ADT(ROW(string));
  for(tmp = getBlock(); OT_CNT(tmp) > 0; tmp = getBlock())
    addBlock(tmp);
  OT_DEL_T(tmp);
  if (OT_CNT(blocks)>0) printPage((int)OT_CNT(blocks));
  OT_DEL_T(blocks);
}

#define tnam "reformat.$$$"
#define fnam CTX_EVAL(string,"FileName")

int main(int argc, string argv[])
{
  CTX_init_reformat(argc,argv);
  SysIn  = OpnFile(fnam,"rt");
  SysOut = OpnFile(tnam,"wt");
  srclin = 1;
  pagenr = 1;
/**/printf("File : '%s'\n",fnam);
/**/printf("Line | ---------+---------+---------+---------");
/**/printf("+---------+---------+---------+--\n");
  reformat();
  printf("%4ld pages\n",pagenr-1);
  fclose(SysOut);
  fclose(SysIn);
  remove(fnam); rename(tnam,fnam);
  CTX_quit();
  BUG_CORE;
  return(0);
}
