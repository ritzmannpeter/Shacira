
#ifndef __cstreamtokenizer_h__
#define __cstreamtokenizer_h__

#include "global_defs.h"
#include <string.h>

#define EMPTY_TOKEN     0

typedef struct _token {
   int token;
   const char * token_value;
}  TOKEN_T;

class cStreamTokenizer
{
public:
   cStreamTokenizer(const char * file, int line, unsigned long chunk_size = 20)
   {
      _File = file;
      _Line = line;
      _StackPointer = 0;
      _Fill = 0;
      _Tokens = (TOKEN_T*)calloc(1, (sizeof(TOKEN_T) * chunk_size));
      _Size = _ChunkSize = chunk_size;
      memset(_Tail, 0, sizeof(_Tail));
   };
   virtual ~cStreamTokenizer()
   {
      int i = 0;
      for (i=0; i<_Fill; i++) {
         char * token_buf = (char*)_Tokens[i].token_value;
         if (token_buf != NULL) {
            free(token_buf);
         }
      }
      free(_Tokens);
   };
   inline void ReAlloc()
   {
      int old_size = _Fill * sizeof(TOKEN_T);
      int new_size = old_size + (_ChunkSize * sizeof(TOKEN_T));
      TOKEN_T * old_mem = _Tokens;
      TOKEN_T * new_mem = (TOKEN_T*)calloc(1, (new_size));
      memcpy(new_mem, old_mem, old_size);
      _Tokens = new_mem;
      _Size = new_size / sizeof(TOKEN_T);
      free(old_mem);
   }
   inline const char * AllocTokenValue(const char * token_value)
   {
      int len = strlen(token_value);
      char * token_buf = (char*)calloc(1, (len + 1));
      memcpy(token_buf, token_value, len);
      return token_buf;
   }
   inline void AddToken(int token, const char * token_value)
   {
      if (_Fill == _Size) {
         ReAlloc();
      }
      _Tokens[_Fill].token = token;
      _Tokens[_Fill].token_value = token_value;
      _Fill++;
   };
   inline int GetNextToken()
   {
      int token = EMPTY_TOKEN;
      if (_StackPointer < _Fill && _StackPointer >= 0) {
         token = _Tokens[_StackPointer].token;
         _StackPointer++;
      }
      return token;
   };
   inline int GetNextToken(const char * & token_value)
   {
      int token = EMPTY_TOKEN;
      if (_StackPointer < _Fill && _StackPointer >= 0) {
         token = _Tokens[_StackPointer].token;
         token_value = _Tokens[_StackPointer].token_value;
         _StackPointer++;
      } else {
         token_value = "";
      }
      return token;
   };
   inline int Token(int pos)
   {
      int token = EMPTY_TOKEN;
      if (pos < _Fill && pos >= 0) {
         token = _Tokens[pos].token;
      }
      return token;
   };
   inline bool Empty()
   {
      return (_StackPointer == _Fill);
   };
   inline const char * GetTokenValue()
   {
      const char * token_value = "";
      if (_StackPointer < _Fill && _StackPointer >= 0) {
         token_value = _Tokens[_StackPointer].token_value;
      }
      return token_value;
   };
   inline int Lookup(int rel_pos = 0)
   {
      int pos = _StackPointer + rel_pos;
      if (pos >= _Fill || pos < 0) {
         return EMPTY_TOKEN;
      } else {
         return _Tokens[pos].token;
      }
   };
   inline const char * TokenValue(int pos)
   {
      if (pos >= _Fill || pos < 0) {
         return "empty";
      } else {
         return _Tokens[pos].token_value;
      }
   };
   inline void Back(int steps = 1)
   {
      if (_StackPointer >= 0) {
         _StackPointer = _StackPointer - steps;
      }
   };
   inline int Pos()
   {
      return _StackPointer;
   };
   inline int Fill()
   {
      return _Fill;
   };
   inline void SetPos(int pos)
   {
      if (pos >= _Fill) {
         _StackPointer = _Fill;
      } else if (pos < 0) {
         _StackPointer = -1;
      } else {
         _StackPointer = pos;
      }
   };
   inline void Reset()
   {
      SetPos(0);
   };
   inline const char * Tail()
   {
      memset(_Tail, 0, sizeof(_Tail));
      char * tail_ptr = _Tail;
      int i = 0;
      for (i=_StackPointer; i<_Fill; i++) {
         if (i != _StackPointer+1) {
         }
         int len = strlen(_Tokens[i].token_value);
         memcpy(tail_ptr, _Tokens[i].token_value, len);
         tail_ptr += len;
      }
      return _Tail;
   };
   inline const char * File()
   {
      return _File;
   }
   inline int Line()
   {
      return _Line;
   }
   virtual void Scan(const char * text) = 0;
   virtual int GetToken(const char * text, const char * & token_value, const char * & tail) = 0;
   virtual const char * TokenText(int token) = 0;
protected:
   const char * _File;
   int _Line;
   long _ChunkSize;
   long _Size;
   long _Fill;
   long _StackPointer;
   TOKEN_T * _Tokens;
   char _Tail[0x2000];
};

#endif

