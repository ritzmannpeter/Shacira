
#ifndef cSet_h
#define cSet_h

class TC {
public:
   TC(int e = 0)
   {
      _Element = e;
   };
   virtual ~TC()
   {
   };
   int _Element;
};

template<class T>
class cSet
{
public:
   cSet(T e);
   cSet(double e);
   void Add(T e);
   void AddTC(TC e);
   virtual ~cSet();
private:
   T _Element;
};

#endif

