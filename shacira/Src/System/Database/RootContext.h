
#ifndef RootContext_h
#define RootContext_h 1

class cContext;
class RootContext
{
public:
   static void Set(cContext * context);
   static cContext * Context();
private:
   RootContext() {};
   virtual ~RootContext() {};
   static cContext * _Context;
};


#endif

