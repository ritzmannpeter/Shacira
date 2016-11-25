
#include "base/eb_elo.hpp"




class cMyOperation : public cEloOperation {
   cString sig;
public:
   cMyOperation(cString sig)
      { cMyOperation::sig = sig; }
protected:
   void onExecOperation(cEloSelection * /*selection*/, cEloElement * /*target*/)
      { cerr << "exec " << getSignature() << endl; }
   cString onGetSignature() const { return sig; }
   cString onGetMenuText() const { return "Menu entry " + sig; }
   cString onGetHelpText() const { return "Help for " + sig; }
};



class cMyElement : public cEloElement {
public:
   cMyElement(cEloElementDescription *descr) : cEloElement(descr) { }
protected:
   cString onGetSignature() const { return "cMyElement"; }
   cString onGetKey() const { return getSignature(); }
   cString onGetName() const { return getSignature(); }
   cString onGetDescr() const { return getName(); }
};




class cMyManager : public cEloOperationManager {

public:
   cMyManager()
   {
      addOperation(new cMyOperation("OP1"));
      addOperation(new cMyOperation("OP2"));
      addOperation(new cMyOperation("OP3"));
      addOperation(new cMyOperation("OP4"));
      addOperation(new cMyOperation("OP5"));
      addOperation(new cMyOperation("OP6"));
   }

protected:
   cString onGetSignature() const
      { return "cMyManager"; }

} MyManager;




class cMyElementDescription1 : public cEloElementDescription {

public:
   cMyElementDescription1()
   {
      registerOperation(&MyManager, "OP1");
      registerOperation(&MyManager, "OP2");
      registerOperation(&MyManager, "OP3");
   }

protected:
   virtual cString onGetSignature() const
      { return "cMyElementDescription1"; }
   virtual cString onGetName() const
      { return getSignature(); }
   virtual cString onGetDescr() const
      { return getName(); }

} MyElementDescription1;




class cMyElementDescription2 : public cEloElementDescription {

public:
   cMyElementDescription2()
   {
      inheritFrom(&MyElementDescription1);
      registerOperation(&MyManager, "OP3");
      registerOperation(&MyManager, "OP4");
      registerOperation(&MyManager, "OP5");
   }

protected:
   virtual cString onGetSignature() const
      { return "cMyElementDescription2"; }
   virtual cString onGetName() const
      { return getSignature(); }
   virtual cString onGetDescr() const
      { return getName(); }

} MyElementDescription2;




int main()
{
   cMyElement e1(&MyElementDescription1);
   cMyElement e2(&MyElementDescription2);

   cEloSelection sel;
   sel.clearSelection();
   sel.addElement(&e1);
   sel.addElement(&e2);

   sel.execOperation("OP1");
   sel.execOperation("OP2");
   sel.execOperation("OP3");
   sel.execOperation("OP4");
   sel.execOperation("OP5");
   sel.execOperation("OP6");

   return 0;
}


