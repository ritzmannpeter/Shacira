
#include "cvaluet.h"
#include "cvalue.h"

template <class T>
class cValueT
{
public:
   cValueT(const T & e);
   cValueT(const cValueT<T> & right);
   virtual ~cValueT();
private:
   T _Element;
};

template<class T> cValueT<T>::cValueT(const T & e)
{
   _Element = e;
}

template<class T> cValueT<T>::cValueT(const cValueT<T> & right)
{
   _Element = right._Element;
}

template <class T> cValueT<T>::~cValueT()
{
}



typedef struct _coordinates {int x; int y;} COORDINATES_T;

#include <list>

void TestValueT()
{
   COORDINATES_T c = {5,6};
   std::list<COORDINATES_T> cl;
   std::list<cValue> lv;
   cl.push_back(c);
   COORDINATES_T c1 = *cl.begin();
   cValueT<COORDINATES_T> vt1 = c1;
   cValue x = "heinz.fuzzy";
   lv.push_back(x);
   cValueT<cValue> vt2 = cValue("sepp");
   cValueT<cValue> vt3 = cValueT<cValue>(x);
   /* not working at all
   COORDINATES_T c2 = vt1;
   */
   std::list<cValue>::const_iterator i = lv.begin();
   cValue v1 = (*i);
}

