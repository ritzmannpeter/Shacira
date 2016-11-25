/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [com_get.c]            Comment Line Extraction                           */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

#if !defined( MSDOS ) && !defined( _WIN32 )
#define O_BINARY 0
#endif

#define MaxComLen 80
static char Com[MaxComLen+1];

#define ScanChars 2000
static char Blk[ScanChars];

static long BlockLoad(string toBlock, long MaxLen, string fromPathName)
{ int Dset; long length;
  Dset = open(fromPathName,O_RDONLY | O_BINARY);
  if (Dset <= 0)
  { fprintf(STDERR,"File %s couldn't be opened",fromPathName); return 0; }
  assert0(MaxLen < 0x10000L,"block too long");
  length = read(Dset,toBlock,(unsigned int)MaxLen);
  close(Dset);
  return length;
}

static bool strnupeq(string A, string B, int Len)
{ int i;
  for (i = 0; i < Len; i++)
    if (toupper(A[i]) != toupper(B[i]))
      return False;
  return True;
}

string Com_GetEx(string FileName)
/* [basename]#title of source 'FileName' 
   format: ['FileName'] ...
         | ['FileName'(basename)] ...
   ( doesn't allocs memory )
*/
{ int blklen, fidlen, i,j, c;
  strcpy(Com,"");
  blklen = BlockLoad(Blk,ScanChars,FileName);
  blklen = MAX(0, MIN(ScanChars,blklen));
  fidlen = strlen(FileName);
  for (i = fidlen-1; i >= 0; i--)
    if (FileName[i] == '\\' || FileName[i] == '/')
    { fidlen -= i+1; FileName += i+1; break; }
  for (i = 0; i + fidlen + 1 < blklen; i++)
    if (Blk[i] == '['
     && ( Blk[i+fidlen+1] == ']' || Blk[i+fidlen+1] == '(' )
     && strnupeq(Blk+i+1,FileName,fidlen))
      goto Found;
  goto Done;
Found:
  j = i+fidlen+1;
  c = 0;
  if (Blk[j] == '(') 
    for( ++j; j < blklen && c < MaxComLen && Blk[j] != ']'; j++)
    {
      if( Blk[j] != ')' )
      {
        Com[c] = Blk[j]; ++c;
      }
    }
  if( c < MaxComLen )
  {
    Com[c] = '#'; ++c;
  }
  for(j++; j < blklen && Blk[j] == ' '; j++);
  for (; j < blklen && c < MaxComLen &&
        (Blk[j] > ' ' || (Blk[j] == ' ' && j+1 < blklen && Blk[j+1] > ' '));
        j++, c++)
    Com[c] = Blk[j];
  Com[c] = '\0';
Done:
  return Com;
}

string Com_Get(string FileName)
/* title of source 'FileName' 
   format: ['FileName'] ...
   ( doesn't allocs memory )
*/
{ int blklen, fidlen, i,j, c;
  strcpy(Com,"");
  blklen = BlockLoad(Blk,ScanChars,FileName);
  blklen = MAX(0, MIN(ScanChars,blklen));
  fidlen = strlen(FileName);
  for (i = fidlen-1; i >= 0; i--)
    if (FileName[i] == '\\' || FileName[i] == '/')
    { fidlen -= i+1; FileName += i+1; break; }
  for (i = 0; i + fidlen + 1 < blklen; i++)
    if (Blk[i] == '['
     && ( Blk[i+fidlen+1] == ']' || Blk[i+fidlen+1] == '(' )
     && strnupeq(Blk+i+1,FileName,fidlen))
      goto Found;
  goto Done;
Found:
  j = i+fidlen+1;
  if (Blk[j] == '(') 
    for(; j < blklen && Blk[j] != ']'; j++);
  for(j++; j < blklen && Blk[j] == ' '; j++);
  c = 0;
  for (; j < blklen && c < MaxComLen &&
        (Blk[j] > ' ' || (Blk[j] == ' ' && j+1 < blklen && Blk[j+1] > ' '));
        j++, c++)
    Com[c] = Blk[j];
  Com[c] = '\0';
Done:
  return Com;
}
