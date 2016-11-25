
#include <stddef.h>
#include <stdio.h>
#include <windows.h>
#include <stdarg.h>

class cl
{
public:
   cl() {};
   virtual ~cl() {};
   virtual void f1(int i) = 0;
   virtual void f2(int i) = 0;
protected:
   const char * class_name;
};

class cl1 : public cl
{
public:
   cl1()
   {
      class_name = "cl1";
   };
   virtual ~cl1() {};
   virtual void f1(int i)
   {
      printf("%s::f1(%d)\n", class_name, i);
   };
   virtual void f2(int i)
   {
      printf("%s::f2(%d)\n", class_name, i);
   };
};

class cl2 : public cl
{
public:
   cl2()
   {
      class_name = "cl2";
   };
   virtual ~cl2() {};
   virtual void f1(int i)
   {
      printf("%s::f1(%d)\n", class_name, i);
   };
   virtual void f2(int i)
   {
      printf("%s::f2(%d)\n", class_name, i);
   };
};

typedef void (cl::*IF_PTR)(int i);

int main(int argc, char* argv[])
{
   cl * x1 = new cl1;
   cl * x2 = new cl2;
   IF_PTR p = &cl::f1;
   ((*x1).*p)(111);
   ((*x2).*p)(222);
   p = &cl::f2;
   ((*x1).*p)(111);
   ((*x2).*p)(222);
   return 0;
}
