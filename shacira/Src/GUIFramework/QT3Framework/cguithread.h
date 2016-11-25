
#ifndef _cguithread_h_
#define _cguithread_h_

#define WAIT_FOR_COMPLETION   -1

#include <qobject.h>
#include <windows.h>
#include "base/eb_sema.hpp"

typedef volatile int ATOMIC_T;
#define __ECL_ATOMIC_SET__(n,v) n = v;
#define __ECL_ATOMIC_GET__(n) (n)
#define __ECL_ATOMIC_INCREMENT__(n) InterlockedIncrement((long*)&n)
#define __ECL_ATOMIC_DECREMENT__(n) InterlockedDecrement((long*)&n)

class cQTTargetObject;

/*!
 * cOperation wraps the operation that should be executed by the GUI thread
 */
class cOperation
{
public:
   friend class cGUIThread;
   friend class cQTTargetObject;
   static int _Pending;
   cOperation();
   /*!
    * get the return code
    */
   inline int ReturnCode() {return _ReturnCode;};
   /*!
    * Reference counting methods
    */
   void AddRef();
   void Release();
   void Break();
protected:
   /*!
    * Execute executes the operation
    */
   virtual int Execute() = 0;
   /*!
    * Completed is a callback to signal completion of the operation
    */
   virtual void Completed(int rc) = 0;
   /*!
    * set the return code
    */
   inline void SetReturnCode(int rc) {_ReturnCode = rc;};
   void Sync();
   void Wait(int timeout = WAIT_FOR_COMPLETION);
   ~cOperation();
   void ExecuteOperation();
   void Terminate();
protected:
   cEventSem * _TerminationEvent;
   int _ReturnCode;
private:
   ATOMIC_T _RefCount;
};

/*!
 * cOperationRequest transports and controls the operation
 * that should be executed by the GUI thread
 */
class cOperationRequest : public QEvent
{
public:
   cOperationRequest(cOperation * operation) : QEvent(QEvent::User)
   {
      _Operation = operation;
   };
   virtual ~cOperationRequest()
   {
      _Operation->Release();
   };
   inline cOperation * Operation() {return _Operation;};
protected:
   cOperation * _Operation;
};

/*!
 * cGUIThread is a class that enables operations within the gui threads context
 * some Qt functions only work properly when executed by the gui
 * thread (Qt event handler)
 */
class cGUIThread
{ 
public:
   cGUIThread();
   virtual ~cGUIThread();
   /*!
    *  post an event to the gui event handler from an arbitrary thread
    */
   void Post(cOperationRequest * request);
   void Post(cOperationRequest * request, int wait);
   /*!
    *  
    */
protected:
   cQTTargetObject * _QTTargetObject;
};


class cQTTargetObject : public QObject
{
   Q_OBJECT
public:
   cQTTargetObject(cGUIThread * gui_thread);
   virtual bool event(QEvent *e);
private:
   cGUIThread * _GUIThread;
}; 

/*!
 * object free post methods
 */
int PostGUI(cOperationRequest * request);
int PostGUI(cOperationRequest * request, int wait);

#endif

