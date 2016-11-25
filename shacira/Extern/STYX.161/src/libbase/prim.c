/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [prim.c]         Instance functions for simple data types                */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

/* Diese Routinen versuchen moeglichst implementationsunabhaengig zu sein. */

#define PRIME_A 987659
#define PRIME_B 123457

/*I----------- Pre-defined functions for various data types --------------- */

long bytesHash(byte x[], long len)
/* hash function for byte sequences */
{ register long crc = 0L;
  long i;
  for (i = 0; i < len; i++)
    crc = (((crc << 1) | (crc < 0)) + *x++) * PRIME_A + PRIME_B;
  return crc;
}

long strHash(string s)
/* hash function for type "string" */
{
  return bytesHash( (byte *) s, (long)strlen(s) );
}

bool strEqual(string a, string b)
/* whether 'a' and 'b' are equal */
{
  return !strcmp(a,b);
}

long combineOrderedHash(long a, long b)
/* combination of two non-commuative hash values */
{
  register long crc = 0L;
  crc = (((crc << 1) | (crc < 0)) + a) * PRIME_A + PRIME_B;
  crc = (((crc << 1) | (crc < 0)) + b) * PRIME_A + PRIME_B;
  return crc;
}

long combineCommutativeHash(long a, long b)
/* combination of two permutable hash values */
{
  return a ^ b;
}

/*I----------- Pre-defined functions for primitive data types --------------- */

long primHash(StdCPtr x)
/* hash function for primitive types like "char","int","pointer" */
{
  return bytesHash( (byte *) &x, sizeof(x) );
}

bool primEqual(StdCPtr a, StdCPtr b)
/* whether 'a' and 'b' are equal */
{
  return a == b;
}

bool primGreatEqual(StdCPtr a, StdCPtr b)
/* whether 'a' is greater equal than 'b' */
{
  return a >= b;
}

bool primLessEqual(StdCPtr a, StdCPtr b)
/* whether 'a' is less equal than 'b' */
{
  return a <= b;
}

int primCompare(StdCPtr a, StdCPtr b)
/* order of 'a' and 'b' */
{
  return a == b ? 0 : a < b ? -1 : 1;
}

StdCPtr primCopy(StdCPtr a)
/* identity */
{
  return a;
}

void primFree(StdCPtr a)
/* frees a primitive value; i.e. does nothing */
{
}
