
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "cSyncView.h"

#define _MIN_(a,b) (((a)<(b)) ? a : b)
#define _MAX_(a,b) (((a)>(b)) ? a : b)

cSyncView * _SyncView = NULL;

static void TestIt(ULONG_T first, ULONG_T last)
{
//printf("test (%d - %d)\n", first, last);
   if (_SyncView == NULL) {
      _SyncView = new cSyncView(5000);
   }
   _SyncView->ClearSrc();
   ULONG_T id = 0;
   void * object = NULL;
   ULONG_T pos = 0;
   for (int i=first; i<=(int)last; i++) {
      id = i;
      object = (void*)i;
      _SyncView->AddSrcObject(pos, id, object);
      pos++;
   }
   _SyncView->Sync();
}


typedef struct _view_entry {
   ULONG_T id;
   void * object;
}  VIEW_ENTRY_T;

#define MAX_ENTRIES  50

class cView {
public:
   cView()
   {
      memset(_Entries, 0, sizeof(_Entries));
      _EntryCount = 0;
   };
   ~cView()
   {
   };
   void Insert(int pos, ULONG_T id, void * object)
   {
      if (_EntryCount < MAX_ENTRIES) {
         int limit = (int)_MIN_(MAX_ENTRIES,_EntryCount+1);
         for (int i=limit; i>pos; i--) {
            _Entries[i].id = _Entries[i-1].id;
            _Entries[i].object = _Entries[i-1].object;
         }
         _Entries[pos].id = id;
         _Entries[pos].object = object;
         if (_Entries[pos+1].id != id - 1) {
            int dummy = 0;
         }
         _EntryCount++;
      } else {
         printf("buffer full at %d\n", _EntryCount);
      }
   };
   void Delete(int pos, ULONG_T id, void * object)
   {
      if (_EntryCount > 0) {
         int limit = (int)_MIN_(MAX_ENTRIES-2,_EntryCount-1);
         for (int i=pos; i<limit;  i++) {
            _Entries[i].id = _Entries[i+1].id;
            _Entries[i].object = _Entries[i+1].object;
         }
         _Entries[_EntryCount-1].id = 0;
         _Entries[_EntryCount-1].object = NULL;
         _EntryCount--;
      } else {
         printf("buffer empty at %d\n", _EntryCount);
      }
   };
   int Check()
   {
      int i = 0;
      ULONG_T last_id = -1;
      for (i=0; i<(int)_EntryCount; i++) {
         if (last_id == -1) {
            last_id = _Entries[i].id;
         } else {
            ULONG_T id = _Entries[i].id;
            ULONG_T obj_id = (ULONG_T)_Entries[i].object;
            if (id != last_id - 1) {
               printf("invalid order at %d: %d != %d\n", i, id, last_id - 1);
               return i;
            }
            if (id != obj_id) {
               printf("object mismatch at %d: %d != %d\n", i, id, obj_id);
               return i;
            }
            last_id = _Entries[i].id;
         }
      }
      return -1;
   };
   void Show()
   {
#ifdef lassma
      printf("%d entries:\n", _EntryCount);
      for (int i=0; i<(int)_EntryCount; i++) {
         printf("%d %p\n", _Entries[i].id, _Entries[i].object);
      }
#endif
   };
   VIEW_ENTRY_T _Entries[MAX_ENTRIES];
   ULONG_T _EntryCount;
};

int main(int c, char* argv[])
{ 
   cView * view = new cView;
   ULONG_T pos = 1;
   ULONG_T amount = 20;
   for (ULONG_T i=1; i<5000000; i++) {
      TestIt(pos, pos + amount);
      ULONG_T delete_pos = 0;
      ULONG_T delete_elements = 0;
      ULONG_T insert_pos = 0;
      ULONG_T insert_elements = 0;
      view->Show();
      if (i % 10000 == 0) {
         printf("step %d pos %d\n", i, pos);
      }
//      Sleep(1);
      pos += 1;
//      amount = (rand() % 20) + 1;
      amount = 20;
   }
   printf("done\n");
   return 0;
}
