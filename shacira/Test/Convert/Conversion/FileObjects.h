
#ifndef _FileObjects_h_
#define _FileObjects_h_

class cSubfile;
class cRegister;
class cTextVar;
class cHeatGroup;
class cHeatText;

typedef std::map<int,cSubfile*> SUBFILE_MAP_T;
typedef std::map<int,cRegister*> REGISTER_MAP_T;
typedef std::map<int,cTextVar*> TEXTVAR_MAP_T;
typedef std::map<int,cHeatGroup*> HEATGROUP_MAP_T;
typedef std::map<int,cHeatText*> HEATTEXT_MAP_T;

typedef std::list<cSubfile*> SUBFILE_LIST_T;
typedef std::list<cRegister*> REGISTER_LIST_T;
typedef std::list<cTextVar*> TEXTVAR_LIST_T;
typedef std::list<cHeatGroup*> HEATGROUP_LIST_T;
typedef std::list<cHeatGroup*> HEATTEXT_LIST_T;

#endif






