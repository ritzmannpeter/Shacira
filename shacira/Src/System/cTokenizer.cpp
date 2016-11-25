//## begin module%3A55D27901F5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A55D27901F5.cm

//## begin module%3A55D27901F5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A55D27901F5.cp

//## Module: cTokenizer%3A55D27901F5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\cTokenizer.cpp

//## begin module%3A55D27901F5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A55D27901F5.additionalIncludes

//## begin module%3A55D27901F5.includes preserve=yes
//## end module%3A55D27901F5.includes

// cTokenizer
#include "System/cTokenizer.h"
//## begin module%3A55D27901F5.additionalDeclarations preserve=yes
//## end module%3A55D27901F5.additionalDeclarations


// Class cTokenizer 





cTokenizer::cTokenizer()
  //## begin cTokenizer::cTokenizer%.hasinit preserve=no
      : _Buf(NULL), _BufSize(0), _BufPos(0)
  //## end cTokenizer::cTokenizer%.hasinit
  //## begin cTokenizer::cTokenizer%.initialization preserve=yes
  //## end cTokenizer::cTokenizer%.initialization
{
  //## begin cTokenizer::cTokenizer%.body preserve=yes
  //## end cTokenizer::cTokenizer%.body
}

cTokenizer::cTokenizer(const cTokenizer &right)
  //## begin cTokenizer::cTokenizer%copy.hasinit preserve=no
      : _Buf(NULL), _BufSize(0), _BufPos(0)
  //## end cTokenizer::cTokenizer%copy.hasinit
  //## begin cTokenizer::cTokenizer%copy.initialization preserve=yes
  //## end cTokenizer::cTokenizer%copy.initialization
{
  //## begin cTokenizer::cTokenizer%copy.body preserve=yes
   _Buf = right._Buf;
   _BufSize = right._BufSize;
   _BufPos = right._BufPos;
  //## end cTokenizer::cTokenizer%copy.body
}

cTokenizer::cTokenizer (CONST_STRING_T buf, ULONG_T bufsize)
  //## begin cTokenizer::cTokenizer%978694295.hasinit preserve=no
      : _Buf(NULL), _BufSize(0), _BufPos(0)
  //## end cTokenizer::cTokenizer%978694295.hasinit
  //## begin cTokenizer::cTokenizer%978694295.initialization preserve=yes
  //## end cTokenizer::cTokenizer%978694295.initialization
{
  //## begin cTokenizer::cTokenizer%978694295.body preserve=yes
   _Buf = buf;
   _BufSize = bufsize;
  //## end cTokenizer::cTokenizer%978694295.body
}


cTokenizer::~cTokenizer()
{
  //## begin cTokenizer::~cTokenizer%.body preserve=yes
  //## end cTokenizer::~cTokenizer%.body
}



//## Other Operations (implementation)
void cTokenizer::Reset ()
{
  //## begin cTokenizer::Reset%1002702339.body preserve=yes
   _BufPos = 0;
  //## end cTokenizer::Reset%1002702339.body
}

CONST_STRING_T cTokenizer::GetToken ()
{
  //## begin cTokenizer::GetToken%978694296.body preserve=yes
#define IsNull(c) (c == 0)
   _Token = "";
   while (_BufPos < _BufSize) {
      if (IsNull(_Buf[_BufPos])) {
         _BufPos++;
         if (_Token.size() > 0) {
            return _Token.c_str();
         }
      } else {
         _Token = _Token + _Buf[_BufPos];
         _BufPos++;
      }
   }
   if (_Token.size() > 0) {
      return _Token.c_str();
   } else {
      return NULL;
   }
  //## end cTokenizer::GetToken%978694296.body
}

CONST_STRING_T cTokenizer::GetToken (CONST_STRING_T whitespace)
{
  //## begin cTokenizer::GetToken%978694297.body preserve=yes
   _Token = "";
   while (_BufPos < _BufSize) {
      if (IsWhiteSpace(_Buf[_BufPos], whitespace)) {
         _BufPos++;
#ifdef NO_EMPTY_TOKENS
         if (_Token.size() > 0) {
#endif
            return _Token.c_str();
#ifdef NO_EMPTY_TOKENS
         }
#endif
      } else {
         _Token = _Token + _Buf[_BufPos];
         _BufPos++;
      }
   }
   if (_Token.size() > 0) {
      return _Token.c_str();
   } else {
      return NULL;
   }
  //## end cTokenizer::GetToken%978694297.body
}

BOOL_T cTokenizer::IsWhiteSpace (INT_T c, CONST_STRING_T whitespace)
{
  //## begin cTokenizer::IsWhiteSpace%978694298.body preserve=yes
   int len = strlen(whitespace);
   for (int i=0; i<len; i++) {
      if (c == whitespace[i]) return true;
   }
   return false;
  //## end cTokenizer::IsWhiteSpace%978694298.body
}

// Additional Declarations
  //## begin cTokenizer%3A55D27901F5.declarations preserve=yes
  //## end cTokenizer%3A55D27901F5.declarations

//## begin module%3A55D27901F5.epilog preserve=yes
//## end module%3A55D27901F5.epilog
