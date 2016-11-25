
#ifndef __sunichar__
#define __sunichar__

#include <stdio.h>

typedef short int UNICHAR;

#define CHAR2UNICHAR(c) ((UNICHAR)(unsigned char)c)

int           UNI_strlen  (UNICHAR *str);
int           UNI_bytelen (UNICHAR *str);
UNICHAR *     UNI_AsciiToUnistr (UNICHAR *dst, char *src);
UNICHAR *     UNI_AsciiToUnistrMax (UNICHAR *dst, char *src, int max);
char *        UNI_UniToAsciistr (char *dst, UNICHAR *src);
char *        UNI_UniToAsciistrMax (char *dst, UNICHAR *src, int max);
UNICHAR *     UNI_strchr  (UNICHAR *s, UNICHAR c);
UNICHAR *     UNI_strrchr (UNICHAR *s, UNICHAR c);
int           UNI_isspace (UNICHAR c);
long          UNI_strtol  (UNICHAR *str, UNICHAR **ptr, int base);
unsigned long UNI_strtoul (UNICHAR *str, UNICHAR **ptr, int base);
long          UNI_atol    (UNICHAR *str);
int           UNI_atoi    (UNICHAR *str);
UNICHAR *     UNI_strstr  (UNICHAR *src, UNICHAR *sub);
UNICHAR *     UNI_strcpy  (UNICHAR *s1, UNICHAR *s2);
UNICHAR *     UNI_strncpy (UNICHAR *s1, UNICHAR *s2, int n);
UNICHAR *     UNI_fgets   (UNICHAR *s, int n, FILE *stream);
int           UNI_fputs   (UNICHAR *s, FILE *stream);
int           UNI_fgetc   (FILE *stream);
int           UNI_fputc   (UNICHAR c, FILE *stream);
UNICHAR *     UNI_memset  (UNICHAR *buf, UNICHAR c, int len);
int           UNI_sprintf (UNICHAR *s, const char *format, ...);
int           UNI_sprintf_uniformat (UNICHAR *s, UNICHAR *format, ...);
int           UNI_strcmp  (UNICHAR *s1, UNICHAR *s2);
int           UNI_strncmp (UNICHAR *s1, UNICHAR *s2, int n);
UNICHAR *     UNI_strcat  (UNICHAR *s1, UNICHAR *s2);
UNICHAR *     UNI_strncat (UNICHAR *s1, UNICHAR *s2, int n);
UNICHAR *     UNI_strpbrk (UNICHAR *s, char *set);

#endif /* __sunichar__ */
