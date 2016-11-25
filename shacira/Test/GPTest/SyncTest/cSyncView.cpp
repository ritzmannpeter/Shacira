
#include "cSyncView.h"

cSyncView::cSyncView(ULONG_T size)
{
   _Size = size;
#ifdef DYNAMIC_OBJECT
   _SrcEntries = (SYNC_ENTRY_T*)ALLOC(sizeof(SYNC_ENTRY_T) * _Size);
   _DstEntries = (SYNC_ENTRY_T*)ALLOC(sizeof(SYNC_ENTRY_T) * _Size);
#else
   memset(_SrcEntries, 0, sizeof(_SrcEntries));
   memset(_DstEntries, 0, sizeof(_DstEntries));
#endif
   _SrcCount = 0;
   _DstCount = 0;
}

cSyncView::~cSyncView()
{
#ifdef DYNAMIC_OBJECT
   FREE(_SrcEntries);
   FREE(_DstEntries);
#endif
}

void cSyncView::ClearSrc()
{
#ifdef DYNAMIC_OBJECT
   memcpy(_DstEntries, _SrcEntries, sizeof(SYNC_ENTRY_T) * _Size);
   memset(_SrcEntries, 0, sizeof(SYNC_ENTRY_T) * _Size);
#else
   memcpy(_DstEntries, _SrcEntries, sizeof(_SrcEntries));
   memset(_SrcEntries, 0, sizeof(_SrcEntries));
#endif
   _DstCount = _SrcCount;
  _SrcCount = 0;
}

void cSyncView::ClearDst()
{
   memset(_DstEntries, 0, sizeof(SYNC_ENTRY_T) * _Size);
   _DstCount = 0;
}

void cSyncView::AddSrcObject(ULONG_T pos, ULONG_T id, void * object)
{
   _SrcEntries[pos].id = id;
   _SrcEntries[pos].object = object;
   _SrcCount++;
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
         void * related_object = _DstEntries[i].related_object;
         DeleteObject(related_object);
         deleted++;
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
         _SrcEntries[i].related_object = RelatedObject(_SrcEntries[i].object);
         inserted++;
      }
   }
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
   FILE * stream = fopen("e:\\temp\\synctest.log", "a");
   if (stream != NULL) {
      fprintf(stream, "delete object %08.8d\n", (ULONG_T)object);
      fclose(stream);
   }
   printf("delete object %08.8d\n", (ULONG_T)object);
}

void * cSyncView::RelatedObject(void * object)
{
   void * related_object = (void*)(((ULONG_T)object) + 1000000);
   FILE * stream = fopen("e:\\temp\\synctest.log", "a");
   if (stream != NULL) {
      fprintf(stream, "insert related object for %08.8d\n", (ULONG_T)related_object);
      fclose(stream);
   }
   printf("insert related object for %08.8d\n", (ULONG_T)related_object);
   return related_object;
}



