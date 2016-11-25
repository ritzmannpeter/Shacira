
#include "cstringlist.h"
#include "utilities.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

cStringList::cStringList(unsigned long size) :
   _StringBuffer(NULL), _BufferSize(0), _Fill(0), _Pos(0)
{
   Expand(size);
}

cStringList::~cStringList()
{
   ClearStringList();
}

void cStringList::AddString(const char * str)
{
   char * new_string = CreateString(str);
   if (!Exists(new_string)) {
      unsigned long pos = _Fill;
      if (_Fill == _BufferSize) {
         Expand(0x1000);
      }
      _StringBuffer[pos] = new_string;
      _Fill++;
   } else {
      FreeString(new_string);
   }
}

void cStringList::Reset()
{
   _Pos = 0;
}

const char * cStringList::GetString()
{
   if (_Pos < _Fill) {
      const char * str = _StringBuffer[_Pos];
      _Pos++;
      return str;
   } else {
      return NULL;
   }
}

bool cStringList::Exists(const char * str)
{
   if (_Fill > 0) {
      for (unsigned long i=0; i<_Fill; i++) {
         if (strcmp(str, _StringBuffer[i]) == 0) {
            return true;
         }
      }
   }
   return false;
}

void cStringList::ClearStringList()
{
   if (_Fill > 0) {
      for (unsigned long i=0; i<_Fill; i++) {
         FreeString(_StringBuffer[i]);
      }
   }
}

void cStringList::Expand(unsigned long size)
{
   unsigned long old_size = _BufferSize;
   unsigned long new_size = old_size + size;
   const char ** buf = (const char **)calloc(1, sizeof(const char*) * new_size);
   if ((_Fill > 0) && (buf != NULL)) {
      for (unsigned long i=0; i<_Fill; i++) {
         buf[i] = _StringBuffer[i];
      }
      free(_StringBuffer);
   }
   _StringBuffer = buf;
   _BufferSize = new_size;
}

char * cStringList::CreateString(const char * str)
{
   unsigned long str_len = strlen(str);
   char * new_string = (char *)calloc(1, str_len + 1);
   if (new_string != NULL){
      memcpy((void*)new_string, (void*)str, str_len);
      ReplaceChar(new_string, '"', '\'');
   }
   return new_string;
}

void cStringList::FreeString(const char * str)
{
   free((void*)str);
}


