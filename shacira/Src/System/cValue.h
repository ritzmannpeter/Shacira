
#ifndef _cvalue_h
#define _cvalue_h 	1

typedef short wide_char;
typedef struct _buffer {
   unsigned long ref_count;
   unsigned long size;
   void * buffer;
}  BUFFER_T;

#define INLINE_METHOD

class cValue {
public:
   enum ValueType {nil, boolean, integer, real, string, wide_string, byte};
public:
   INLINE_METHOD cValue() {Initialize(); _Type = integer; _IntegerValue = 0;};
   INLINE_METHOD cValue(bool v) {Initialize(); _Type = boolean; _IntegerValue = v;};
   INLINE_METHOD cValue(char v) {Initialize(); _Type = integer; _IntegerValue = v;};
   INLINE_METHOD cValue(short v) {Initialize(); _Type = integer; _IntegerValue = v;};
   INLINE_METHOD cValue(int v) {Initialize(); _Type = integer; _IntegerValue = v;};
   INLINE_METHOD cValue(long v) {Initialize(); _Type = integer; _IntegerValue = v;};
   INLINE_METHOD cValue(unsigned char v) {Initialize(); _Type = integer; _IntegerValue = (long)v;};
   INLINE_METHOD cValue(unsigned short v) {Initialize(); _Type = integer; _IntegerValue = (long)v;};
   INLINE_METHOD cValue(unsigned int v) {Initialize(); _Type = integer; _IntegerValue = (long)v;};
   INLINE_METHOD cValue(unsigned long v) {Initialize(); _Type = integer; _IntegerValue = (long)v;};
   INLINE_METHOD cValue(float v) {Initialize(); _Type = real; _RealValue = v;};
   INLINE_METHOD cValue(double v) {Initialize(); _Type = real; _RealValue = v;};
   INLINE_METHOD cValue(const cValue & right);
   INLINE_METHOD cValue(const char * v);
   INLINE_METHOD cValue(const wide_char * v);
   INLINE_METHOD cValue(const void * v, unsigned long size);
   INLINE_METHOD cValue operator =(const cValue & right);
   INLINE_METHOD operator bool();
   INLINE_METHOD operator char();
   INLINE_METHOD operator short();
   INLINE_METHOD operator int();
   INLINE_METHOD operator long();
   INLINE_METHOD operator unsigned char();
   INLINE_METHOD operator unsigned short();
   INLINE_METHOD operator unsigned int();
   INLINE_METHOD operator unsigned long();
   INLINE_METHOD operator float();
   INLINE_METHOD operator double();
   INLINE_METHOD operator const char *();
   INLINE_METHOD operator const wide_char *();
   INLINE_METHOD operator const void *();
   INLINE_METHOD const char * String();
   INLINE_METHOD const wide_char * WideString();
   INLINE_METHOD unsigned long Size() {return _Size;};
   virtual ~cValue();
   static INLINE_METHOD unsigned long Allocations() { return _Allocations;};
protected:
   static unsigned long _Allocations;
   ValueType _Type;
   unsigned long _Size;
   long _IntegerValue;
   double _RealValue;
   BUFFER_T * _Buffer;
protected:
   INLINE_METHOD void Initialize();
   INLINE_METHOD void Copy(void * destination, const void * source, unsigned long size);
   INLINE_METHOD void Clone(const cValue & right);
   INLINE_METHOD void FreeResources();
   static INLINE_METHOD BUFFER_T * AllocBuffer(unsigned long size);
   static INLINE_METHOD void FreeBuffer(BUFFER_T * buffer);
};

#endif

