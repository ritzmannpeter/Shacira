/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [xmem_imp.h]         data structures used by [xmem]                      */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#ifndef True
#include "standard.h"
#endif

/* ------------------------------- Types ---------------------------------- */

AbstractType( MEM_Type );
AbstractType( MEM_Name );
#define MEM(Alpha) MEM_Name

ConcreteType( Type )
{
  Type     next;
  c_string ident;  /* the identifer of this type              */
  c_bool   isnode; /* tags a union; change later              */
  long     tag;    /* the TAG value of MEM_Names of this type */
  long     mask;   /* the mask for tags of this type          */
  void     (*dumpInfo)(/* FILE* f, MEM_Name x */);
  void     (*allNames)(/* MEM_Name x, MEM_Name act(MEM_Name x) */);
  void     (*freeInfo)(/* MEM_Name x */);
  void     (* putInfo)(/* MEM_Name x */);
  void     (* getInfo)(/* MEM_Name x */);
};

ConcreteType( Node )
{
  Type     type;
  Node     q1;
  Node     q2;
  c_byte   mark;
  c_byte   root;
  /* client data structure follow here */
};

#define XMEM_ROOTVAL_FREE (False)
#define XMEM_ROOTVAL_ROOT (True)
#define XMEM_ROOTVAL_EXTR (0xff)

ConcreteType( ExtCptr )
/* "external" C-Pointers */
{
  StdCPtr ref;
};

/* ------------------------------- Macros --------------------------------- */

#define MEM_Name_to_Node(X)       ((Node)(((c_byte*)(X))-SizeOf(Node)))
#define MEM_Name_to_Cptr(T,X)     ((T)(X))
#define MEM_Node_to_Cptr(T,X)     ((T)(((c_byte*)(X))+SizeOf(Node)))
#define MEM_Node_to_Name(X)       ((MEM_Name)(((c_byte*)(X))+SizeOf(Node)))
#define MEM_Cptr_to_old_Name(X)   ((MEM_Name)(X))
#define MEM_Cptr_to_new_Name(T,X) (MEM_toNode(T,X))
#define MEM_Cptr_to_Node(X)       ((Node)(((c_byte*)(X))-SizeOf(Node)))

#define MEM_Name_is_Node(X)   ((((long)(X))&1)==0 && (X) != NULL)
#define MEM_Name_in_Type(T,X) (MEM_Name_is_Node(X) && MEM_Name_to_Node(X)->type == (T))

/* the type of 'MEM_Name' is defined by [xmem] */

#define XTY_toC_MEM_Name(X) ((MEM_Name)(X))
#define XTY_toX_MEM_Name(X) ((MEM_Name)(X))
#define XTY_isX_MEM_Name(X) (C_True)
#define XTY_noR_MEM_Name(X) (MEM_Root_set((X),C_False))

