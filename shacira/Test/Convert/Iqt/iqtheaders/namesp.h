// Namesp.h  -  Deklarationen fuer den OPC (und Corba) Namespace

#ifndef _namesp_
#define _namesp_

#include <vector.h>
#include <set.h>
#include <comm.h>

class NameSpaceList;


//
// Konstanten
//

enum NameSpaceElementType {
   ELEMENT_LEAF,              // Element ist ein Blatt, kein 'Subdirectory'
   ELEMENT_BRANCH             // Element ist Verzweigung, ein 'Subdirectory'
};

enum NameListType {
   LIST_LEAF,                 // Nur LEAF-Elemente anzeigen
   LIST_BRANCH,               // Nur BRANCH-Elemente anzeigen
   LIST_FLAT                  // Beide Elementtypen anzeigen, bei BRANCH-Typen
};                            // inclusive aller 'Subdirectory'-Eintraege

enum NameSpaceHandleType {    // Identifiziert das Handle. Fuer zusaetzliche
   NAMESPACE_HANDLE_OPC = 0,  // Handles hier und unten die Tabelle handle
   NAMESPACE_HANDLE_CORBA     // erweitern.
};

//
// Klasse NameSpaceElement
//

class NameSpaceElement {
   char *name;
   NameSpaceElementType type; // ELEMENT_BRANCH (Verzweigung, hat Kinder),
                              // ELEMENT_LEAF (Endpunkt)
   NameSpaceList *childlist;  // Falls ELEMENT_BRANCH: Zeiger auf Container 
   long handle[2];            // Eindeutiges Handle, zum Zugriff auf ein 
                              // asoziiertes Item
public:
   NameSpaceElement ()       {name = NULL; 
                              type = ELEMENT_LEAF; 
                              childlist = NULL;}
   NameSpaceElement (char *n){name = n; 
                              type = ELEMENT_LEAF; 
                              childlist = NULL;}
   NameSpaceElement (char *n, NameSpaceHandleType hndtype, long hnd)
                             {name = n; 
                              handle[hndtype] = hnd;
                              type = ELEMENT_LEAF; 
                              childlist = NULL;}
   NameSpaceElement (const NameSpaceElement& src)
                             {if (src.name) {
                                 name = new char[strlen(src.name)+1]; 
                                 strcpy (name, src.name);
                              } else {
                                 name = NULL;
                              }
                              handle[NAMESPACE_HANDLE_OPC] = src.handle[NAMESPACE_HANDLE_OPC];
                              handle[NAMESPACE_HANDLE_CORBA] = src.handle[NAMESPACE_HANDLE_CORBA];
                              type = src.type; 
                              childlist = src.childlist;}
   ~NameSpaceElement ();
   void makeBranch (NameSpaceList *c)
                             {type = ELEMENT_BRANCH; 
                              childlist = c;}
   bool  isBranch() const    {return (type == ELEMENT_BRANCH);}
   char *getName() const     {return name;}
   NameSpaceList *getChild() const  {return childlist;}
   
   long  getOPCHandle() const       {return handle[NAMESPACE_HANDLE_OPC];}
   long  getCORBAHandle() const     {return handle[NAMESPACE_HANDLE_CORBA];}
   void  setHandle (const NameSpaceHandleType ind, long hnd) 
                                    {handle[ind] = hnd;}
   
   bool operator== (const NameSpaceElement &e2) const
                             {return (strcmp(name,e2.name) == 0);}
   bool operator== (const char *n) const
                             {return (strcmp(name,n) == 0);}
   bool operator!= (const NameSpaceElement &e2)
                             {return (strcmp(name,e2.name) != 0);}
   bool operator!= (const char *n) const
                             {return (strcmp(name,n) != 0);}
   bool operator<  (const NameSpaceElement &e2) const
                             {return (strcmp(name,e2.name) < 0);}
   bool operator<  (const char *n) const
                             {return (strcmp(name,n) < 0);}
   bool operator>  (const NameSpaceElement &e2) const
                             {return (strcmp(name,e2.name) > 0);}
   bool operator>  (const char *n) const
                             {return (strcmp(name,n) > 0);}
   bool operator<= (const NameSpaceElement &e2) const
                             {return (strcmp(name,e2.name) <= 0);}
   bool operator<= (const char *n) const
                             {return (strcmp(name,n) <= 0);}
   bool operator>= (const NameSpaceElement &e2) const
                             {return (strcmp(name,e2.name) >= 0);}
   bool operator>= (const char *n) const
                             {return (strcmp(name,n) >= 0);}
   
};


//
// Klasse NameSpaceList
//

struct NameSpaceElementPointerCompare {
   bool operator() (NameSpaceElement *e1, NameSpaceElement *e2) const
      {return *e1 < *e2;}
};

typedef set<NameSpaceElement *, NameSpaceElementPointerCompare> NameSpaceElVec;

class NameSpaceList : public NameSpaceElVec {
public:
   ~NameSpaceList();
   NameSpaceElement *searchElement (char *name) const;
   void buildNameList (NameListType type, char *prefix, 
                       vector<char *> &name_list);
};


//
// Klasse NameSpaceBrowse
//

class NameSpaceBrowse {
   NameSpaceList *root;
   NameSpaceList *act_list;
   vector<NameSpaceList *> list_stack;
   vector< char *> prefix_stack;
public:
   NameSpaceBrowse (NameSpaceList *l) {root = l; act_list = l;}
   int browseDown (char *el_name);
   int browseUp ();
   vector<char *> *getList (NameListType type);
   char *getFullName (char *name);
   long getOPCHandle (char *fullname);
   long getCORBAHandle (char *fullname);
   NameSpaceElement *getElement (char *fullname);
};

#endif  // _namesp_

