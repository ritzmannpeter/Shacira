
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


