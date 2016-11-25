
#include "cSyncView.h"

#if !defined(SHACIRA_MAJOR)
#include <stdio.h>
#include <stdarg.h>
static char _Text[0x2000] = {0};
void ErrorPrintf(const char * fmt_str, ...)
{
   va_list ap;
   va_start(ap, fmt_str);
   vsprintf_s(_Text, sizeof(_Text) - 1, fmt_str, ap);
   fprintf(stdout, "%s", _Text);
   va_end(ap);
}
#endif

class SyncLock
{
public:
   SyncLock(ecl::cMutexSem * mutex)
      : _Mutex(mutex)
   {
      _Mutex->request();
   };
   virtual ~SyncLock()
   {
      _Mutex->release();
   };
private:
   ecl::cMutexSem * _Mutex;
};

cSyncView::cSyncView(ULONG_T size)
   : _managedItemCount(0), _CurrentPos(0)
{
   _Size = size / 4;
   _SrcEntries = (SYNC_ENTRY_T*)ALLOC(sizeof(SYNC_ENTRY_T) * _Size);
   _DstEntries = (SYNC_ENTRY_T*)ALLOC(sizeof(SYNC_ENTRY_T) * _Size);
   _SrcCount = 0;
   _DstCount = 0;
}

cSyncView::~cSyncView()
{
   FREE(_SrcEntries);
   FREE(_DstEntries);
}

void cSyncView::ClearSrc()
{
   memcpy(_DstEntries, _SrcEntries, sizeof(SYNC_ENTRY_T) * _Size);
   memset(_SrcEntries, 0, sizeof(SYNC_ENTRY_T) * _Size);
   _DstCount = _SrcCount;
  _SrcCount = 0;
}

void cSyncView::ClearDst()
{
   memset(_DstEntries, 0, sizeof(SYNC_ENTRY_T) * _Size);
   _DstCount = 0;
}

#ifdef obsolete
void cSyncView::AddSrcObject(ULONG_T pos, ULONG_T id, void * object)
{
   if (pos < _Size) {
      _SrcEntries[pos].id = id;
      _SrcEntries[pos].object = object;
      _SrcCount++;
   } else {
      ErrorPrintf("cSyncView: invalid position %d size is %d\n", pos, _Size);
   }
}
#endif

#ifdef deprecated
void cSyncView::AddSrcObject(ULONG_T pos, ULONG_T id, ULONG_T id2, void * object)
{
   if (_CurrentPos != pos) {
      ErrorPrintf("cSyncView: invalid position %d expected %d\n", pos, _CurrentPos);
   }
   if (pos < _Size) {
      _SrcEntries[pos].id = id;
      _SrcEntries[pos].id2 = id2;
      _SrcEntries[pos].object = object;
      _SrcCount++;
      _CurrentPos++;
   } else {
      ErrorPrintf("cSyncView: invalid position %d size is %d\n", pos, _Size);
   }
}
#endif

void cSyncView::AddSrcObject(ULONG_T id, ULONG_T id2, void * object)
{
   if (_CurrentPos < _Size) {
      _SrcEntries[_CurrentPos].id = id;
      _SrcEntries[_CurrentPos].id2 = id2;
      _SrcEntries[_CurrentPos].object = object;
      _SrcCount++;
      _CurrentPos++;
   } else {
      ErrorPrintf("cSyncView: invalid position %d size is %d\n", _CurrentPos, _Size);
   }
}

void cSyncView::Sync()
{
   ULONG_T src_pos = 0;
   ULONG_T dst_pos = 0;
   while (src_pos < _SrcCount ||
          dst_pos < _DstCount) {
      if (src_pos == _SrcCount) {
         _DstEntries[dst_pos].op = DELETE_OP;
         dst_pos++;
      } else if (dst_pos == _DstCount) {
         _SrcEntries[src_pos].op = INSERT_OP;
         src_pos++;
      } else {
         int pos = CompareKey(src_pos, dst_pos);
         if (pos == 0) {
            _SrcEntries[src_pos].op = UPDATE_OP;
            _SrcEntries[src_pos].related_object = _DstEntries[dst_pos].related_object;
            _DstEntries[dst_pos].op = UPDATE_OP;
            src_pos++;
            dst_pos++;
         } else {
            if (pos < 0) {
               _SrcEntries[src_pos].op = INSERT_OP;
               src_pos++;
            } else {
               _DstEntries[dst_pos].op = DELETE_OP;
               dst_pos++;
            }
         }
      }
   }
   ULONG_T inserted = 0, deleted = 0, updated = 0;
   ULONG_T i = 0;
   for (i=0; i<_DstCount; i++) {
      if (_DstEntries[i].op == DELETE_OP) {
         SyncLock __lock__(&_SyncMutex);
         void * related_object = _DstEntries[i].related_object;
         DeleteObject(related_object);
         deleted++;
         __ECL_ATOMIC_DECREMENT__(_managedItemCount);
      } else if (_DstEntries[i].op == UPDATE_OP) {
         /// nix
         updated++;
      } else if (_DstEntries[i].op == NO_OP) {
         /// nix
         updated++;
      }
   }
   for (i=0; i<_SrcCount; i++) {
      if (_SrcEntries[i].op == INSERT_OP) {
         SyncLock __lock__(&_SyncMutex);
         _SrcEntries[i].related_object = RelatedObject(_SrcEntries[i].object);
         inserted++;
         __ECL_ATOMIC_INCREMENT__(_managedItemCount);
      }
   }
   _CurrentPos = 0;
}

int cSyncView::CompareKey(int src_pos, int dst_pos)
{
   ULONG_T src_val = _SrcEntries[src_pos].id;
   ULONG_T dst_val = _DstEntries[dst_pos].id;
   if (src_val != dst_val) {
      if (src_val < dst_val) {
         return -1;
      } else {
         return 1;
      }
   } else {
      src_val = _SrcEntries[src_pos].id2;
      dst_val = _DstEntries[dst_pos].id2;
      if (src_val != dst_val) {
         if (src_val < dst_val) {
            return -1;
         } else {
            return 1;
         }
      }
   }
   return 0;
}

void cSyncView::DeleteObject(void * object)
{
}

void * cSyncView::RelatedObject(void * object)
{
   return object;
}



