#include "stdosx.h"

#include "gstream.h"
#include "scn_imp.h"
#include "symbols.h"

#if defined( _MSDOS ) || defined( _WIN32 )
#define CS_LATIN1 "850"
#else
#define CS_LATIN1 "LATIN1"
#endif

int xfmain(int c, char* argv[])
{
if( SCN_CHAR_SET_SIZE < 0 )
  printf("<%u\n",SCN_CHAR_SET_SIZE);
else
  printf(">=%u\n",SCN_CHAR_SET_SIZE);
return(0);
}

int fmain(int c, char* argv[])
{ FILE* fp = fopen(argv[1],"rb");
  char buf[500];
  char lbuf[500];
  string x;
  wc_char wbuf[500];
  wchar_t* w = L"Das ist ein Test !ÄÜÖ";
  wchar_t* wx;
  c_string s = "Das ist ein Test !ÄÜÖ";
  int rc, rc1, rc2, rc3, rc4, l, ll, i, sl = 22, wsl=22*4, tl = 500, wtl = 500*4;
  CSConv_T conv1 = GS_csconv_new("WCHAR_T"/*CS_ID_WCHAR*/,CS_LATIN1);
  CSConv_T conv2 = GS_csconv_new("WCHAR_T","WCHAR_T"/*CS_ID_WCHAR,CS_ID_WCHAR*/);
  CSConv_T conv3 = GS_csconv_new(CS_ID_MBYTE/*"UTF-8"*/,"WCHAR_T"/*CS_ID_WCHAR*/);
  CSConv_T conv4 = GS_csconv_new(CS_LATIN1/*"UTF-8"*/,CS_ID_MBYTE);
  GStream_T gstream = GS_stream_file_new(fp,CS_LATIN1,False);
  assert1(fp != NULL,"open %s failed",argv[1]);
  assert0(gstream != NULL,"stream create failed");
/**/
  wbuf[0] = L'\0';
  buf[0] = '\0';
  l = wtl;
  rc1 = GS_csconv_string(conv1,s,sl,(c_string)wbuf,&l);
  if( rc1 >= 0 )
  {
    wbuf[l] = L'\0';
    printf("\nSTR-CNV-1=%S\n",wbuf);
  for( i=0; i < 18; ++i )
    printf("\nWBUF[i]=%ld\n",wbuf[i]);
  }
  else
    printf("STR-CNV-1-ERR %d\n",rc1);
  wbuf[0] = L'\0';
  buf[0] = '\0';
  l = wtl;
  rc2 = GS_csconv_string(conv2,(c_string)w,wsl,(c_string)wbuf,&l);
  if( rc2 >= 0 )
  {
    wbuf[l] = L'\0';
    printf("\nSTR-CNV-2=%S\n",wbuf);
  for( i=0; i < 18; ++i )
    printf("\nWBUF[i]=%ld\n",wbuf[i]);
  }
  else
    printf("STR-CNV-2-ERR %d\n",rc2);
  wbuf[0] = L'\0';
  buf[0] = '\0';
  l = tl;
  rc3 = GS_csconv_string(conv3,(c_string)w,wsl,buf,&l);
  if( rc3 >= 0 )
  {
    buf[l] = '\0';
    printf("\nSTR-CNV-3=%s\n",buf);
  }
  else
    printf("STR-CNV-3-ERR %d\n",rc3);
  lbuf[0] = '\0';
  ll = tl;
  rc4 = GS_csconv_string(conv4,(c_string)buf,l,lbuf,&ll);
  if( rc4 >= 0 )
  {
    lbuf[l] = '\0';
    printf("\nSTR-CNV-4=%s\n",lbuf);
  }
  else
    printf("STR-CNV-4-ERR %d\n",rc4);

  for( i=0; i < 18; ++i )
    printf("\nW[i]=%C\n",w[i]);

  x = GS_ucs4_to_utf8(w);
  if( x != NULL )
  {
    for( i=0; i < strlen(x); ++i )
    {
      printf("\nx[i]=%d\n",x[i]);
    }
    printf("\nx=%s\n",buf);
    wx = GS_utf8_to_ucs4(x);
    if( wx != NULL && WCStrLen(w) == (l=WCStrLen(wx)) )
    {
      for( i=0; i < l; ++i )
      {
        if( w[i] != wx[i] )
        {
          printf("Verschieden: %d\n",i);
          break;
        }
      }
      if( i >= l ) printf("OK !\n");
    }
    else printf("Fehler: %s\n",wx != NULL ? "Länge" : "NULL");
    if( wx != NULL ) FreeMem(wx);
    FreeMem(x);
  }
/**/

/*
  rc = GS_stream_get_wcrc(gstream);
  for( i=0; rc > 0; )
  {
    printf("WCHAR %ld=%08x %C\n",++i,rc,rc);
    rc = GS_stream_get_wcrc(gstream);
  }
*/

  GS_csconv_free(conv1);
  GS_csconv_free(conv2);
  GS_csconv_free(conv3);
  GS_csconv_free(conv4);
  GS_stream_file_free(gstream);
  if( fp != NULL ) fclose(fp);
  //printf("\nW=%S\n",w);
  return 0;
}

int lmain(int argc, char* argv[])
{ long long int x = 30560;
  long y = x >> 16;
  short z = x >> 16;
  long yy = x >> 0;
  short zz = x >> 0;
  printf("SIZE=%d\n",sizeof(long long int));
  printf("LONG-HI=%ld\n",y);
  printf("LONG-LO=%ld\n",yy);
  printf("SHORT-HI=%d\n",z);
  printf("SHORT-LO=%d\n",zz);
  return 0;
}

int bmain(int argc, char* argv[])
{ FILE* fp = fopen("udp.src","w");
  unsigned short psrc, pdst, len, crc;
  char* text = "hallo welt !";
  psrc = 25;
  pdst = 33667;
  len = 8 + 13;
  crc = 12345;
  if( fp != NULL )
  {
    if( fwrite(&psrc,1,2,fp) != 2 )
    {
      printf("error\n"); return 1;
    }
    if( fwrite(&pdst,1,2,fp) != 2 )
    {
      printf("error\n"); return 1;
    }
    if( fwrite(&len,1,2,fp) != 2 )
    {
      printf("error\n"); return 1;
    }
    if( fwrite(&crc,1,2,fp) != 2 )
    {
      printf("error\n"); return 1;
    }
    if( fwrite(text,1,13,fp) != 13 )
    {
      printf("error\n"); return 1;
    }
    fclose(fp);
  }
  else
  {
    printf("error\n"); return 1;
  }
  printf("OK\n");
  return 0;
}

int main(int argc, char* argv[])
{ string s = "äöü-Umlaute";
  int l = strlen(s),i;
  symbol sy;
  initSymbols();
  fprint_raw(STDOUT,s,-1);
  NL;
  for(i=0; i<l; ++i)
  {
    if( !iscntrl(s[i]) )
      printf("%c",s[i]);
    else
      printf("%02x",s[i]);
  }
  sy = stringToSymbol("");
  printf("\n>%s<\n",symbolToString(sy));
  fmain(argc,argv);
  freeSymbols();
  BUG_CORE;
  return 0;
}
