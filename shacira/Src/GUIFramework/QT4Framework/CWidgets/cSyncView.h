
#ifndef _cSyncView_h_
#define _cSyncView_h_

#include "base/semaphore.h"
#include "base/base_ex.h"
using namespace ecl;

#ifndef ULONG_T
typedef unsigned long ULONG_T;
typedef unsigned char UCHAR_T;
#include <malloc.h>
#include <string.h>
#define ALLOC(size) calloc(1, size);
#define FREE(ptr) free(ptr);
#endif

#define NO_OP           0
#define INSERT_OP       1
#define DELETE_OP       2
#define UPDATE_OP       3
typedef struct _sync_entry {
   ULONG_T id;
   ULONG_T id2;
   void * object;
   void * related_object;
   UCHAR_T op;
}  SYNC_ENTRY_T;
#define INVALID_POS     0xffffffff

#define deprecated

class cSyncView
{
public:
   cSyncView(ULONG_T size);
   ~cSyncView();
   void ClearSrc();
   void ClearDst();
#ifdef obsolete
   void AddSrcObject(ULONG_T pos, ULONG_T id, void * object);
#endif
#ifdef deprecated
   void AddSrcObject(ULONG_T pos, ULONG_T id, ULONG_T id2, void * object);
#endif
   void AddSrcObject(ULONG_T id, ULONG_T id2, void * object);
   void Sync();
   virtual int CompareKey(int src_pos, int dst_pos);
   virtual void DeleteObject(void * object);
   virtual void * RelatedObject(void * object);
   inline ULONG_T managedItemCount() const {return (ULONG_T)_managedItemCount;};
private:
   cMutexSem _SyncMutex;
   ATOMIC_T _managedItemCount;
   ULONG_T _Size;
   SYNC_ENTRY_T * _SrcEntries;
   SYNC_ENTRY_T * _DstEntries;
   ULONG_T _SrcCount;
   ULONG_T _DstCount;
   ULONG_T _CurrentPos;
};

#endif

