
#include "cSet.h"

template<class T> cSet<T>::cSet(T e)
{
   _Element = e;
}

template<class T> cSet<T>::cSet(double e)
{
   _Element = (T)e;
}

template <class T> cSet<T>::~cSet()
{
}

template<class T> void cSet<T>::Add(T e)
{
   _Element = (T)e;
}

template<class T> void cSet<T>::AddTC(TC e)
{
   _Element = (T)e._Element;
}


void f()
{
   TC tc(555);
   double e = 999.5555555;
   cSet<int> int_set(e);
   cSet<TC> tc_set(tc);
   int_set.AddTC(tc);
   int_set.AddTC(e);
}

