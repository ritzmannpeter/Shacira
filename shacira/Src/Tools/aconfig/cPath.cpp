
#include "cPath.h"

#define USE_LIST

PATH_MAP_T cPath::_PathMap;
PATH_LIST_T cPath::_PathList;
BOOL_T cPath::_RelativePaths = false;
BOOL_T cPath::_AbsolutePaths = false;
BOOL_T cPath::_OriginalPaths = false;

cPath::cPath(CONST_STRING_T file, BOOL_T is_directory)
{
   _IsDirectory = is_directory;
   _File = cConfigUtils::ResolveSymbols(file);
   if (_File[0] == '/') {
      _AbsPath = _File;
   } else {
      _AbsPath = cConfigUtils::FullPath(_File.c_str());
   }
   _AbsPath = cFileSystemUtils::Resolve(_AbsPath.c_str());
   _AbsPath = cConfigUtils::POSIX_Path(_AbsPath.c_str());
   if (_IsDirectory) {
      _Path = _File.c_str();
      _FileName = "";
   } else {
      _Path = cFileSystemUtils::DirName(_File.c_str());
      _FileName = cConfigUtils::FileName(_File.c_str());
   }
   _RelPath = "empty";
   cFileSystemUtils::NameComponents(_FileName.c_str(), _BaseName, _Extension);
   Store(this);
}

cPath::~cPath()
{
}

void cPath::SetBaseDirectory(CONST_STRING_T directory)
{
#ifdef USE_LIST
   PATH_LIST_T::const_iterator i = _PathList.begin();
   while (i != _PathList.end()) {
      cPath * path = (*i);
      path->SetBase(directory);
      i++;
   }
#else
   PATH_MAP_T::const_iterator i = _PathMap.begin();
   while (i != _PathMap.end()) {
      cPath * path = (*i).second;
      path->SetBase(directory);
      i++;
   }
#endif
}

void cPath::Print()
{
#ifdef USE_LIST
   PATH_LIST_T::const_iterator i = _PathList.begin();
   while (i != _PathList.end()) {
      cPath * path = (*i);
      printf("\n_File %s\n", path->File().c_str());
      printf("FileName %s\n", path->FileName().c_str());
      printf("BaseName %s\n", path->BaseName().c_str());
      printf("Extension %s\n", path->Extension().c_str());
      printf("Path %s\n", path->Path().c_str());
      printf("AbsPath %s\n", path->AbsPathx().c_str());
      printf("BaseDirectory %s\n", path->BaseDirectory().c_str());
      printf("RelPath %s\n", path->RelPath().c_str());
      printf("PathSoec %s\n", path->PathSpec().c_str());
      i++;
   }
#else
   PATH_MAP_T::const_iterator i = _PathMap.begin();
   while (i != _PathMap.end()) {
      cPath * path = (*i).second;
      printf("\n_File %s\n", path->File().c_str());
      printf("FileName %s\n", path->FileName().c_str());
      printf("BaseName %s\n", path->BaseName().c_str());
      printf("Extension %s\n", path->Extension().c_str());
      printf("Path %s\n", path->Path().c_str());
      printf("AbsPath %s\n", path->AbsPathx().c_str());
      printf("BaseDirectory %s\n", path->BaseDirectory().c_str());
      printf("RelPath %s\n", path->RelPath().c_str());
      printf("PathSoec %s\n", path->PathSpec().c_str());
      i++;
   }
#endif
}

void cPath::SetBase(CONST_STRING_T directory)
{
   _BaseDirectory = directory;
   if (!cFileSystemUtils::IsRelativePath(_Path.c_str())) {
      int dummy = 0;
   }
if (_AbsPath[0] == '/') {
   int dummy = 0;
}
   _RelPath = cConfigUtils::RelPath(directory, _AbsPath.c_str());
}

STRING_T cPath::Path()
{
   return _Path;
}

STRING_T cPath::File()
{
   return _File;
}

STRING_T cPath::FileName()
{
   return _FileName;
}

STRING_T cPath::BaseName()
{
   return _BaseName;
}

STRING_T cPath::Extension()
{
   return _Extension;
}

STRING_T cPath::AbsPathx()
{
   return _AbsPath;
}

STRING_T cPath::RelPath()
{
   if (_RelPath == "empty") {
      int dummy = 0;
   }
   return _RelPath;
}

STRING_T cPath::PathSpec()
{
   if (_RelativePaths) {
if (_RelPath == "empty") {
   int dummy = 0;
}
      if (_RelPath.size() == 0) {
         return _AbsPath;
      } else {
         return _RelPath;
      }
   }
   if (_AbsolutePaths) {
      return _AbsPath;
   }
   if (_OriginalPaths) {
      return _File;
   }
   return _AbsPath;
}

STRING_T cPath::BaseDirectory()
{
   return _BaseDirectory;
}

void cPath::Store(cPath * path)
{
#ifdef USE_LIST
   _PathList.push_back(path);
#else
   PATH_MAP_T::const_iterator i = _PathMap.find(path->AbsPathx().c_str());
   if (i == _PathMap.end()) {
      _PathMap[path->AbsPathx().c_str()] = path;
   } else {
      int dummy = 0;
   }
#endif
}

