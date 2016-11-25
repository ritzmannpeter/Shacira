
#ifndef _cBinaryObject_h
#define _cBinaryObject_h 	1

typedef unsigned char * BINARY_OBJECT_T;
typedef unsigned long OBJECT_SIZE_T;
typedef struct _object_data {
   int ref_count;
   BINARY_OBJECT_T object_data;
}  OBJECT_DATA_T;

class cBinaryObject {
public:
   enum ObjectType{Unspecified = 0};
public:
   /*! constructors
    */
   cBinaryObject();
   cBinaryObject(OBJECT_SIZE_T object_size);
   cBinaryObject(const cBinaryObject & right);
   cBinaryObject(BINARY_OBJECT_T object, OBJECT_SIZE_T object_size, ObjectType object_type = Unspecified);
   virtual ~cBinaryObject();
   cBinaryObject & operator= (const cBinaryObject & right);
   BINARY_OBJECT_T Data();
   inline OBJECT_SIZE_T Size() {return _ObjectSize;};
   inline ObjectType Type() {return _ObjectType;};
   void Set(BINARY_OBJECT_T object, OBJECT_SIZE_T object_size, ObjectType object_type = Unspecified);
   void Set(OBJECT_SIZE_T object_size, ObjectType object_type = Unspecified);
private:
   void Release(OBJECT_DATA_T * data);
private:
   OBJECT_DATA_T * _ObjectData;
   OBJECT_SIZE_T _ObjectSize;
   ObjectType _ObjectType;
};

extern unsigned long _BinaryObjects;

#endif

