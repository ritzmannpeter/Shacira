
#include <iostream.h>
#include "base/eb_str.hpp"
#include "base/eb_event.hpp"

class cName {
   cString name;
public:
   cName(cString name)
      { cName::name = name; }
   cString getName() const
      { return name; }
};

class cMySource : public cName, public cEventSource {

public:

   cMySource() : cName("src")
      { }

   enum EVENTS { evtFirst = cEventSource::evtUser,
      evtEvent1,     // Erster Event
      evtEvent2,     // Zweiter Event
      evtEvent3,     // Dritter Event
      evtUser
   };

   void genEvent1()
      { callEvent(evtEvent1); }
   void genEvent2(int p1)
      { callEvent(evtEvent2, p1); }
   void genEvent3(int p1, int p2)
      { callEvent(evtEvent3, p1, p2); }

};

class cMyTarget : public cName, public cEventTarget {

public:

   cMyTarget(cMySource& src, cString name) : cName(name)
   {
      src.addEvent(cMySource::evtEvent1, this, (EVFUNC)func1a);
      src.addEvent(cMySource::evtEvent1, this, (EVFUNC)func1b);
      src.addEvent(cMySource::evtEvent2, this, (EVFUNC_I)func2);
      src.addEvent(cMySource::evtEvent3, this, (EVFUNC_II)func3);
   }

   void func1a()
      { cerr << getName() << ": func1a called" << endl; }
   void func1b()
      { cerr << getName() << ": func1b called" << endl; }
   void func2(int a)
      { cerr << getName() << ": func2 called, a=" << a << endl; }
   void func3(int a, int b)
      { cerr << getName() << ": func3 called, a=" << a << ", b=" << b << endl; }

};

void GenEvents(cMySource& src, cString comment)
{
   cerr << "--- " << comment << " ---" << endl;
   src.genEvent1();
   src.genEvent2(1);
   src.genEvent3(1,2);
}

int main()
{
   cMySource src;
   cMyTarget targ1(src, "targ1");
   cMyTarget targ2(src, "targ2");

   GenEvents(src, "after generation");

   src.removeEvent(cMySource::evtEvent2);
   GenEvents(src, "after removing event2");

   src.removeEvent(cMySource::evtEvent3, &targ1);
   GenEvents(src, "after removing event3 from targ1");

   src.removeEvent(&targ2);
   GenEvents(src, "after removing targ2");

   return 0;
}

