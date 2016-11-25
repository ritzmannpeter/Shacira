
#include "cPathGroup.h"
#include "cPath.h"

cPathGroup::cPathGroup()
{
}

cPathGroup::~cPathGroup()
{
}

void cPathGroup::Add(cPath * path)
{
   _PathList.push_back(path);
}

void cPathGroup::List(PATH_LIST_T & paths)
{
   paths = _PathList;
}

