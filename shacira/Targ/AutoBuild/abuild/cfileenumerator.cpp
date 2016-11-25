
#include "cfileenumerator.h"
#include "cdirectoryutils.h"

void cFileEnumerator::Process()
{
   unsigned long flags = _Recursive ? WALK_RECURSIVE : 0;
   STRING_LIST_T source_files;
   cDirectoryUtils::FileList(source_files, _Path.c_str(), flags);
   STRING_LIST_T::const_iterator i = source_files.begin();
   while (i != source_files.end()) {
      STRING_T file = (*i);
      File(file.c_str());
      i++;
   }
}

