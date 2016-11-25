
#ifndef __suniconv__
#define __suniconv__

#include <stdio.h>
#include <sunichar.h>

int  UNICONV_GetLanguageHandle (char *language);
void UNICONV_ListLanguages (void (*func)(char *), void (*ufunc)(UNICHAR *));
UNICHAR UNICONV_Iqt2UnicodeChar (int hnd, char *str, int *num_chars, int *converted);
int  UNICONV_Iqt2UnicodeString (int hnd, UNICHAR *dest, char *src, int max);
char UNICONV_Iqt2Latin1Char (int hnd, char *str, int *num_chars, int *converted);
int  UNICONV_Iqt2Latin1String (int hnd, char *dest, char *src, int max);
char UNICONV_Unicode2Latin1Char (UNICHAR uchar);
int  UNICONV_Unicode2Latin1String (char *dest, UNICHAR *src, int max);

#endif /* __suniconv__ */
