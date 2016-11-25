
#ifndef _cRegDescription_h_
#define _cRegDescription_h_

class cRegDescription
{
public:
   cRegDescription(CONST_STRING_T line);
   virtual ~cRegDescription();
public:
   LONG_T _RegNo;
   BOOL_T _IsValid;
   STRING_T _Text;
   UCHAR_T _Precision;
private:
   void Parse(CONST_STRING_T line);
};

typedef std::map<LONG_T,cRegDescription*> REG_DESCRIPTION_MAP_T;

class cRegDescriptions
{
public:
   cRegDescriptions();
   virtual ~cRegDescriptions();
   void Load(CONST_STRING_T file);
   void Clear();
   BOOL_T Present(LONG_T reg_no);
   STRING_T Text(LONG_T reg_no);
   UCHAR_T Precision(LONG_T reg_no);
private:
   REG_DESCRIPTION_MAP_T _RegDescriptions;
};



#endif
