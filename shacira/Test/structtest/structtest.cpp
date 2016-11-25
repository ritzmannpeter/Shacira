

#include "Pack_1"

   struct db80_t {
      int i1;
      char c1;
      float f1;
      double d1;
      float f2;
      double d2;
   };
   struct db81_t {
      int i1;
      char c1;
      float f1;
      double d1;
      int i2;
      char c2;
      float f2;
      double d2;
      char array[100];
   };
   struct _interface {
      int length;
      db80_t db80;
      db81_t db81;
   };
   typedef struct {
      const char * name;
      unsigned long address;
      unsigned long length;
   }  map;
   _interface _ifc = {0};
#define comp(name) {#name, (unsigned long)&(_ifc.name) - (unsigned long)&_ifc, sizeof(_ifc.name)}
#include "Unpack"

int main(int argc, char* argv[])
{
   _interface* ifc_ptr = &_ifc;
   map addrmap[] =
   {
      {"_ifc.length", (unsigned long)&(_ifc.length) - (unsigned long)&_ifc, sizeof(_ifc.length)},
      comp(length),
      comp(db80),
      comp(db80.i1),
      comp(db81),
      comp(db81.array),
      comp(db81.array[52]),
      {"", 0, 0}
   };
   _interface ifc = {0};
   int dummy = sizeof(ifc.length);   
   dummy = sizeof(ifc.db80);
   dummy = (unsigned long)&(ifc.db81.i2) - (unsigned long)&ifc;
   int * i2 = (int*)((char*)(&ifc) + dummy);
   *i2 = 555;
   dummy = addrmap[6].address;
   char * c = (char*)((char*)(&_ifc) + dummy);
   *c = 44;

   return 0;
}
