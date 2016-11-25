
#ifndef _cValue_h
#define _cValue_h 	1

void TestValues();

typedef short wide_char;

class cValue {
public:
   enum ValueType {nil, integer, uinteger, real, string, wide_string, byte};
public:
   inline cValue(char v) {Initialize(); _Type = integer; _IntegerValue = v;};
   inline cValue(short v) {Initialize(); _Type = integer; _IntegerValue = v;};
   inline cValue(int v) {Initialize(); _Type = integer; _IntegerValue = v;};
   inline cValue(long v) {Initialize(); _Type = integer; _IntegerValue = v;};
   inline cValue(unsigned char v) {Initialize(); _Type = uinteger; _UIntegerValue = v;};
   inline cValue(unsigned short v) {Initialize(); _Type = uinteger; _UIntegerValue = v;};
   inline cValue(unsigned int v) {Initialize(); _Type = uinteger; _UIntegerValue = v;};
   inline cValue(unsigned long v) {Initialize(); _Type = uinteger; _UIntegerValue = v;};
   inline cValue(float v) {Initialize(); _Type = real; _RealValue = v;};
   inline cValue(double v) {Initialize(); _Type = real; _RealValue = v;};
   inline cValue(const cValue & right);
   inline cValue(const char * v);
   inline cValue(const wide_char * v);
   inline cValue(const void * v, unsigned long size);
   inline cValue operator =(const cValue & right);
   inline operator char();
   inline operator short();
   inline operator int();
   inline operator long();
   inline operator unsigned char();
   inline operator unsigned short();
   inline operator unsigned int();
   inline operator unsigned long();
   inline operator float();
   inline operator double();
   inline operator const char *();
   inline operator const wide_char *();
   inline operator const void *();
   inline const char * String();
   inline const wide_char * WideString();
   inline unsigned long Size() {return _Size;};
   virtual ~cValue();
   static inline unsigned long Allocations() { return _Allocations;};
protected:
   static unsigned long _Allocations;
   unsigned long _RefCount;
   ValueType _Type;
   unsigned long _Size;
   long _IntegerValue;
   unsigned long _UIntegerValue;
   double _RealValue;
   const void * _Buffer;
protected:
   inline void Initialize();
   inline void Copy(void * destination, const void * source, unsigned long size);
   inline void * Alloc(unsigned long size);
   inline void Free(void * mem);
   inline void Clone(cValue & left, const cValue & right);
   inline void FreeResources();
};

#endif

