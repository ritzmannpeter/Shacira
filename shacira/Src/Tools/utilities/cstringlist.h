

#ifndef _cstringlist_h_
#define _cstringlist_h_

class cStringList
{
public:
   cStringList(unsigned long size = 0x10000);
   virtual ~cStringList();
   void AddString(const char * str);
   void Reset();
   const char * GetString();
private:
   bool Exists(const char * str);
   void ClearStringList();
   void Expand(unsigned long size);
   char * CreateString(const char * string);
   void FreeString(const char * str);
private:
   const char ** _StringBuffer;
   unsigned long _BufferSize;
   unsigned long _Fill;
   unsigned long _Pos;
};

#endif

