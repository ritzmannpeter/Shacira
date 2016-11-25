
#include "FirstHeader.h"
#include "csignalmanager.h"
#include "cwidgetbase.h"

cSignalManager::cSignalManager()
{
}

cSignalManager::~cSignalManager()
{
}

void cSignalManager::ListenTo(const QString & name, CWidgetBase * sender)
{
   cPtrList * listeners = Listeners(name);
   if (listeners != NULL) {
      listeners->Add(sender);
   }
}

void cSignalManager::Signal(ULONG_T signal, const QString & sender_name, CWidgetBase * sender)
{
   if (sender_name == NULL) {
      return;
   }
   cPtrList * listeners = Listeners(sender_name);
   if (listeners != NULL) {
      cPtrList::cConstIterator i = listeners->Begin();
      if (i.First()) {
         do {
            CWidgetBase * widget = (CWidgetBase*)i.Ptr();
            if (widget != NULL) {
               widget->GUISignal(signal, sender);
            } else {
               ErrorPrintf("null widget in signal listener list\n");
            }
         } while (i.Next());
      }
   }
}

cPtrList * cSignalManager::Listeners(const QString & name)
{
   cPtrList * listeners = NULL;
   MANAGER_MAP_T::const_iterator i = _Listeners.find(name);
   if (i == _Listeners.end()) {
      listeners = new cPtrList;
      _Listeners[name] = listeners;
   } else {
      listeners = (*i).second;
   }
   return listeners;
}

