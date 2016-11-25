/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [fsplit.c]         Splitting/Concationation of large files               */
/*                                                                          */
/* Copyright (c) 1994 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"
#include "pathes.h"
#include "sink.h"

#define MAX_FILE_LEN (1400000L)

void splitFile(string src_file, string dst_dict)
{ FILE* SysIn, *SysOut; int cc; long len = 0;
  string dst_name = Str_printf("%s/fsplit.%03ld",dst_dict,(len+1)/MAX_FILE_LEN);
  fprintf(STDERR,"--> %s\n",dst_name);
  SysIn = OpnFile(src_file,"rb");
  SysOut = OpnFile(dst_name,"wb");
  for (cc = fgetc(SysIn); cc != EOF; cc = fgetc(SysIn))
  {
    if (len % MAX_FILE_LEN == 0 && len > 0)
    { 
      FreeMem(dst_name);
      fclose(SysOut);
      dst_name = Str_printf("%s/fsplit.%03ld",dst_dict,(len+1)/MAX_FILE_LEN);
      fprintf(STDERR,"--> %s\n",dst_name);
      SysOut = OpnFile(dst_name,"wb");
    }
    fputc(cc,SysOut);
    len += 1;
  }
  fclose(SysIn);
  FreeMem(dst_name);
  fclose(SysOut);
  dst_name = Str_printf("%s/fsplit.all",dst_dict);
  SysOut = OpnFile(dst_name,"wt");
  fprintf(SysOut,"[fsplit.all] Verzeichnis\n\n");
  fprintf(SysOut,"%ld Parts, %ld Bytes\n", 
                 MAX(1,(len+MAX_FILE_LEN-1)/MAX_FILE_LEN), len);
  FreeMem(dst_name);
  fclose(SysOut);
}

void concatFile(string dst_file, string src_dict)
{ FILE* SysIn, *SysOut; bool dig = False; 
  int cc; long cnt = 0L, parts, len, i;
  string s1 = (string)NULL, s2 = (string)NULL, 
         src_name = Str_printf("%s/fsplit.all",src_dict);
  Sink t1 = Sink_open(), t2 = Sink_open();

  fprintf(STDERR,"<-- %s\n",src_name);
  SysIn = OpnFile(src_name,"rt");
  for (cc = fgetc(SysIn); cc != EOF; cc = fgetc(SysIn))
  {
    if( isdigit(cc) )
    {
      dig = True;
      if( s1 == (string)NULL ) Sink_printf(t1,"%c",cc);
      else                     Sink_printf(t2,"%c",cc);
    }
    else
    {
      if( dig )
      {
        dig = False;
        if( s1 == (string)NULL ) s1 = Sink_close(t1);
        else                     s2 = Sink_close(t2);
      }
    }
  }
  parts = atol(s1); len = atol(s2);
  FreeMem(s1); FreeMem(s2); FreeMem(src_name);
  fclose(SysIn);

  SysOut = OpnFile(dst_file,"wb");
  for( i=0; i < parts; ++i )
  {
    src_name = Str_printf("%s/fsplit.%03ld",src_dict,i);
    fprintf(STDERR,"<-- %s\n",src_name);
    SysIn = OpnFile(src_name,"rb");
    for (cc = fgetc(SysIn); cc != EOF; cc = fgetc(SysIn))
    {
      fputc(cc,SysOut); cnt += 1;
    }
    FreeMem(src_name);
    fclose(SysIn);
  }
  fclose(SysOut);
  assert1(cnt == len,"destination file '%s' corrupted",dst_file);
}

int main(int argc, string argv[])
{
  assert0
  (
    argc == 4 && ( !strcmp(argv[1],"-split") || !strcmp(argv[1],"-concat") ), 
    "usage: fsplit [-split|-concat] FileName DictName"
  );
  if( ! strcmp(argv[1],"-split") ) splitFile(argv[2],argv[3]);
  else                            concatFile(argv[2],argv[3]);
  BUG_CORE;
  return 0;
}
