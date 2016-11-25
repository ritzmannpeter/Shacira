
#include <iostream.h>

#define __Multiple_Inheritance_Error_2__

#if defined __Multiple_Inheritance_Error_1__

   class TARGET {
   public:
      typedef void (TARGET::*EVFUNC)();

      struct EVENT {
   #ifdef __FEHLER_Falscher_This_Pointer__
         EVENT(TARGET *o, EVFUNC f)
            { obj = o; func = f; }
   #else /* So sieht's besser aus... */
         EVENT(void *o, EVFUNC f)
            { obj = (TARGET*)o; func = f; }
   #endif
         TARGET *obj;
         EVFUNC func;
      };

   };

   class A {
   public:
      virtual ~A() { }
   };

   class B : public A, public TARGET {
   public:
      B() { cerr << this << endl; }
      void f() { cerr << "B::f(" << this << ")" << endl; }
   };

   int main()
   {
      B b;
      TARGET::EVENT ev(&b, (TARGET::EVFUNC)b.f);
      (ev.obj->*ev.func)();
      return 0;
   }

#elif defined __Multiple_Inheritance_Error_2__

   #define _CRTDBG_MAP_ALLOC 
   #include <stdlib.h>
   #include <crtdbg.h>

   #define _export __declspec(dllexport)

   class _export A {
   public:
      A();
      ~A();
   };

   A::A() { }
   A::~A() { }

   main()
   {
      _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG)|_CRTDBG_LEAK_CHECK_DF);

      A *pa = new A;
      delete pa;
      return 0;
   }

#endif
