
#include "cLiteString.h"
#include "safefunctions.h"
#include <malloc.h>

static char * StrAlloc(unsigned long size)
{
   return (char*)calloc(1, size);
}

static void StrFree(char * string)
{
   free(string);
}

cLiteString::cLiteString()
{
   _String = NULL;
   _RefCount = 0;
}

cLiteString::cLiteString(const cLiteString & right)
{
   _String = NULL;
   _RefCount = 0;
   const char * string = right.c_str();
   unsigned long len = strlen(string);
   if (len > 0) {
      _String = StrAlloc(len+1);
      SafeStrCpy(_String, string, len+1);
   }
}

cLiteString::cLiteString(const char * string)
{
   _String = NULL;
   _RefCount = 0;
   int len = strlen(string);
   _String = StrAlloc(len+1);
   SafeStrCpy(_String, string, len+1);
}

cLiteString::cLiteString(const char * string, unsigned long len)
{
   _String = NULL;
   _RefCount = 0;
   _String = StrAlloc(len+1);
   strncpy(_String, string, len);
}

cLiteString::~cLiteString()
{
   if (_String != NULL) {
      StrFree(_String);
      _String = NULL;
   }
}

const char * cLiteString::c_str() const
{
   if (_String == NULL) {
      return "";
   } else {
      return _String;
   }
}

const unsigned long cLiteString::size() const
{
   if (_String == NULL) {
      return 0;
   } else {
      return strlen(_String);
   }
}

cLiteString cLiteString::operator +(const cLiteString & right)
{
   const char * str1 = _String;
   const char * str2 = right.c_str();
   const unsigned long size1 = size();
   const unsigned long size2 = right.size();
   unsigned long new_size = size1 + size2;
   char * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   cLiteString new_string = cLiteString(new_buf);
   StrFree(new_buf);
   return new_string;
}

cLiteString cLiteString::operator +(const char * right)
{
   const char * str1 = _String;
   const char * str2 = right;
   const unsigned long size1 = size();
   unsigned long size2 = strlen(right);
   unsigned long new_size = size1 + size2;
   char * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   cLiteString new_string = cLiteString(new_buf);
   StrFree(new_buf);
   return new_string;
}

cLiteString cLiteString::operator +=(const cLiteString & right)
{
   const char * str1 = _String;
   const char * str2 = right.c_str();
   const unsigned long size1 = size();
   const unsigned long size2 = right.size();
   unsigned long new_size = size1 + size2;
   char * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

cLiteString cLiteString::operator +=(const char * right)
{
   const char * str1 = _String;
   const char * str2 = right;
   const unsigned long size1 = size();
   unsigned long size2 = strlen(right);
   unsigned long new_size = size1 + size2;
   char * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

cLiteString cLiteString::operator =(const cLiteString & right)
{
   char * new_buf = NULL;
   const char * string = right.c_str();
   const unsigned long size = right.size();
   if (size > 0) {
      new_buf = StrAlloc(size+1);
      SafeStrCpy(new_buf, string, size+1);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

cLiteString cLiteString::operator =(const char * right)
{
   char * new_buf = NULL;
   const char * string = right;
   unsigned long size = strlen(right);
   if (size > 0) {
      new_buf = StrAlloc(size+1);
      SafeStrCpy(new_buf, string, size+1);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

char cLiteString::operator [](unsigned long index)
{
   if (_String == NULL) {
      return 0;
   } else {   
      if (index < size()) {
         return _String[index];
      } else {
         return 0;
      }
   }
}

void cLiteString::clear()
{
}


