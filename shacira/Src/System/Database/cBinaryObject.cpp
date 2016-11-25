
#include "cBinaryObject.h"
#include <stddef.h>
#include <string.h>
#include <malloc.h>

#define Alloc(s) calloc(1, s)
#define Free(p) free(p)

unsigned long _BinaryObjects = 0;

cBinaryObject::cBinaryObject()
   : _ObjectData(NULL), _ObjectSize(0), _ObjectType(Unspecified)
{
}

cBinaryObject::cBinaryObject(OBJECT_SIZE_T object_size)
   : _ObjectData(NULL), _ObjectSize(0), _ObjectType(Unspecified)
{
   if (object_size > 0) {
      _BinaryObjects++;
      _ObjectData = (OBJECT_DATA_T*)Alloc(sizeof(*_ObjectData));
      _ObjectData->object_data = (BINARY_OBJECT_T)Alloc(object_size);
      _ObjectData->ref_count = 1;
      _ObjectSize = object_size;
   }
}

cBinaryObject::cBinaryObject(const cBinaryObject & right)
   : _ObjectData(NULL), _ObjectSize(0), _ObjectType(Unspecified)
{
   _ObjectData = right._ObjectData;
   _ObjectSize = right._ObjectSize;
   _ObjectType = right._ObjectType;
   if (_ObjectData != NULL) {
      _ObjectData->ref_count++;
   }
}

cBinaryObject::cBinaryObject(BINARY_OBJECT_T object, OBJECT_SIZE_T object_size, ObjectType object_type)
   : _ObjectData(NULL), _ObjectSize(0), _ObjectType(Unspecified)
{
   Set(object, object_size, object_type);
}

cBinaryObject::~cBinaryObject()
{
   if (_ObjectData != NULL) {
      _ObjectData->ref_count--;
      if (_ObjectData->ref_count == 0) {
         Release(_ObjectData);
      }
   }
}

cBinaryObject & cBinaryObject::operator= (const cBinaryObject & right)
{
   if (_ObjectData != right._ObjectData) {
      if (_ObjectData != NULL) {
         _ObjectData->ref_count--;
         if (_ObjectData->ref_count == 0) {
            Release(_ObjectData);
         }
         _ObjectData = NULL;
      }
      _ObjectData = right._ObjectData;
      if (_ObjectData != NULL) {
         _ObjectData->ref_count++;
      }
      _ObjectSize = right._ObjectSize;
      _ObjectType = right._ObjectType;
   }
   return *this;
}
  
BINARY_OBJECT_T cBinaryObject::Data()
{
   if (_ObjectData != NULL) {
      return _ObjectData->object_data;
   }
   return NULL;
}

void cBinaryObject::Set(BINARY_OBJECT_T object, OBJECT_SIZE_T object_size, ObjectType object_type)
{
   if (_ObjectData != NULL) {
      _ObjectData->ref_count--;
      if (_ObjectData->ref_count == 0) {
         Release(_ObjectData);
      }
      _ObjectData = NULL;
   }
   if (object_size > 0 && object != NULL) {
      _BinaryObjects++;
      _ObjectData = (OBJECT_DATA_T*)Alloc(sizeof(*_ObjectData));
      _ObjectData->object_data = (BINARY_OBJECT_T)Alloc(object_size);
      memcpy(_ObjectData->object_data, object, object_size);
      _ObjectData->ref_count = 1;
      _ObjectSize = object_size;
      _ObjectType = object_type;
   }
}

void cBinaryObject::Set(OBJECT_SIZE_T object_size, ObjectType object_type)
{
   if (_ObjectData != NULL) {
      _ObjectData->ref_count--;
      if (_ObjectData->ref_count == 0) {
         Release(_ObjectData);
      }
      _ObjectData = NULL;
   }
   if (object_size > 0) {
      _BinaryObjects++;
      _ObjectData = (OBJECT_DATA_T*)Alloc(sizeof(*_ObjectData));
      _ObjectData->object_data = (BINARY_OBJECT_T)Alloc(object_size);
      _ObjectData->ref_count = 1;
      _ObjectSize = object_size;
      _ObjectType = object_type;
   }
}

void cBinaryObject::Release(OBJECT_DATA_T * data)
{
   if (data != NULL) {
      if (data->object_data != NULL) {
         Free(data->object_data);
      }
      Free(data);
      _BinaryObjects--;
   }
}

