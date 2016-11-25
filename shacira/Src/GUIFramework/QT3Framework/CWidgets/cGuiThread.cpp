
#include "cGUIThread.h"
#include <qapplication.h>

static void LogPrintf(void * obj, int tm, const char * op, int line)
{
return;
   FILE * stream = fopen("events.txt", "a");
   if (stream != NULL) {
      fprintf(stream, "%d %s %p %d\n", line, op, obj, tm);
      if (_stricmp(op, "deleted") == 0) {
         fprintf(stream, "\n\n");
      }
      fclose(stream);
   }
}

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
   _ReturnCode = 0;
   __ECL_ATOMIC_SET__(_RefCount,1);
   _TerminationEvent = NULL;
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
LogPrintf(_TerminationEvent, 0, "created", __LINE__);
   }
}

void cOperation::Wait(int timeout)
{
   if (_TerminationEvent == NULL) {
LogPrintf(_TerminationEvent, timeout, "wait failed", __LINE__);
      _ReturnCode = -1;
   } else {
LogPrintf(_TerminationEvent, timeout, "wait", __LINE__);
      bool success = _TerminationEvent->wait(timeout);
      if (!success) {
LogPrintf(_TerminationEvent, timeout, "timed out", __LINE__);
         int dummy = 0;
      } else {
LogPrintf(_TerminationEvent, timeout, "completed", __LINE__);
      }
   }
}
   
cOperation::~cOperation()
{
   if (_TerminationEvent != NULL) {
LogPrintf(_TerminationEvent, 0, "deleted", __LINE__);
      delete _TerminationEvent;
   }
   _Pending--;
}

void cOperation::ExecuteOperation()
{
   _ReturnCode = Execute();
}

void cOperation::Terminate()
{
   Completed(_ReturnCode);
   if (_TerminationEvent != NULL) {
      LogPrintf(_TerminationEvent, 0, "set", __LINE__);
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

