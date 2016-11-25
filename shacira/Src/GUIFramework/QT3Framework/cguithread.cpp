
#include "cGUIThread.h"
#include <qapplication.h>

static cGUIThread * _GUIThread = NULL;
int PostGUI(cOperationRequest * request)
{
   cOperation * operation = request->Operation();
   if (_GUIThread == NULL) {
      _GUIThread = new cGUIThread;
   }
   _GUIThread->Post(request);
   return operation->ReturnCode();
}

int PostGUI(cOperationRequest * request, int wait)
{
   cOperation * operation = request->Operation();
   if (_GUIThread == NULL) {
      _GUIThread = new cGUIThread;
   }
   _GUIThread->Post(request, wait);
   return operation->ReturnCode();
}

/// cOperation methods

int cOperation::_Pending = 0;

cOperation::cOperation()
{
   _TerminationEvent = NULL;
   _ReturnCode = 0;
   __ECL_ATOMIC_SET__(_RefCount,1);
   _Pending++;
}

void cOperation::AddRef()
{
   __ECL_ATOMIC_INCREMENT__(_RefCount);
}

void cOperation::Release()
{
   int ref_count = __ECL_ATOMIC_DECREMENT__(_RefCount);
   if (ref_count == 0) {
      delete this;
   }
}

void cOperation::Sync()
{
   if (_TerminationEvent == NULL) {
      _TerminationEvent = new cEventSem;
   }
}

void cOperation::Wait(int timeout)
{
   if (_TerminationEvent == NULL) {
      _ReturnCode = -1;
   } else {
      bool success = _TerminationEvent->wait(timeout);
      if (!success) {
         _ReturnCode = -2;
      }
   }
}
   
cOperation::~cOperation()
{
   if (_TerminationEvent != NULL) {
      cEventSem * event = _TerminationEvent;
      _TerminationEvent = NULL;
      delete event;
   }
   _Pending--;
}

void cOperation::Break()
{
   if (_TerminationEvent != NULL) {
      _TerminationEvent->set();
   }
}

void cOperation::ExecuteOperation()
{
   _ReturnCode = Execute();
}

void cOperation::Terminate()
{
   Completed(_ReturnCode);
   if (_TerminationEvent != NULL) {
      _TerminationEvent->set();
   }
}

/// cGUIThread methods

cGUIThread::cGUIThread() :
   _QTTargetObject(new cQTTargetObject(this))
{
}

cGUIThread::~cGUIThread()
{
   delete _QTTargetObject;
}

void cGUIThread::Post(cOperationRequest * request)
{
   cOperation * operation = request->Operation();
   operation->AddRef();
   QApplication::postEvent((QObject*)_QTTargetObject, request);
}

void cGUIThread::Post(cOperationRequest * request, int wait)
{
   cOperation * operation = request->Operation();
   operation->AddRef();
   operation->Sync();
   QApplication::postEvent((QObject*)_QTTargetObject, request);
   operation->Wait(wait);
}

cQTTargetObject::cQTTargetObject(cGUIThread * gui_thread) :
   _GUIThread(gui_thread)
{
}

bool cQTTargetObject::event(QEvent *e)
{
   if (e->type() == QEvent::User) {
      cOperationRequest * request = (cOperationRequest*)e;
      cOperation * operation = request->Operation();
      operation->ExecuteOperation();
      operation->Terminate();
      return TRUE;
   } else {
      // alle anderen Events weitergeben
      return QObject::event(e);
   }
}

