/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxTree.h]   Styx Tree Implementation (C++)                            */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2005 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_TREE_INCL
#define STYX_TREE_INCL


#include <vector>

/** @file
    Tree (iterator) templates   
*/


namespace styx
{
  using namespace std;

  /** @addtogroup StyxLibraryCPP
      C++ Scanner & parser library
  */
  //@{

  /** @addtogroup StyxTree
      Tree (iterator) templates   
  */
  //@{


  /* tree iterator declaration --------------------------------------------- */

  /** iterator type */
  enum EStyxTreeIterType
  {
    TI_TYPE_DF, ///< depth first
    TI_TYPE_BF  ///< breath first
  };
  
  /** iteration state */
  enum EStyxTreeIterState
  {
    TI_STATE_PRAE, ///< pre order
    TI_STATE_POST  ///< post order
  };

  template <class T /* tree type */, short O /* iterator type */ > 
  class TStyxTreeIter;

  /// tree iterator template
  template <class T /* tree type */, short O /* iterator type */ > 
  class TStyxTreeIter
  {
  public:
    typedef          vector<T* >               V_Tree;
    typedef typename vector<T* >::iterator     I_V_Tree;
    typedef          pair<V_Tree*, I_V_Tree >  T_Pos;
    typedef          vector<T_Pos >            T_Iter;

  protected:
    V_Tree root;  ///< root term list
    short  type;  ///< iterator type
                  ///< @link #EStyxTreeIterType (--\> definition) @endlink
    short  state; ///< iteration state
                  ///< @link #EStyxTreeIterState (--\> definition) @endlink
    T_Iter stack; ///< term list iteration stack

                    /// select next tree node in depth first order
                    /// @return (this) iterator
    TStyxTreeIter&  dfnext();
                    /// select next tree node in breath first order
                    /// @return (this) iterator
    TStyxTreeIter&  bfnext();

  public:
    /// The constructor creates an iterator for a tree.
    /// @param tree the tree
    TStyxTreeIter(T* tree);
    virtual ~TStyxTreeIter();

                           /// get current iteration state
                           /// @return current iteration state
                           /// @link #EStyxTreeIterState (--\> definition) @endlink
    virtual short          getState();
                           /// get current node based tree
                           /// @return current node based tree
    virtual T*             getTerm();
                           /// get current iteration stack
                           /// @return current iteration stack
    virtual const T_Iter&  getStack();
                           /// select next tree node
                           /// @return (this) iterator
    virtual TStyxTreeIter& operator++();
                           /// skip parts of current node based tree
                           /// @return (this) iterator
    virtual TStyxTreeIter& skip();
                           /// end of iteration ?
                           /// @return true for end of iteration
    virtual bool           end();
  };

  /* tree declaration ------------------------------------------------------ */

  template <class N /* tree node type */ > class TStyxTree;

  /// tree template
  template <class N /* tree node type */ > class TStyxTree
  {
  public:
    typedef vector<TStyxTree* > V_Tree;
    typedef TStyxTreeIter<TStyxTree,TI_TYPE_DF > DF_Iter;
    typedef TStyxTreeIter<TStyxTree,TI_TYPE_BF > BF_Iter;

    //typedef unary_function<TStyxTree&,bool> Predicate;
    /// predicate function object
    struct Predicate
    {
                   /// function operator, called for each node 
                   /// @param t current node based tree 
                   /// @return true for a node that satisfies a predicate
      virtual bool operator () (TStyxTree& t) = 0;
      virtual ~Predicate() {}
    };
    /// visitor function object
    struct Function
    {
                   /// function operator, 
                   /// called for each node in pre and post state
                   /// @param t current node based tree 
                   /// @param o current iteration state
                   /// @link #EStyxTreeIterState (--\> definition) @endlink
                   /// @param l current tree level
      virtual void operator () (TStyxTree& t, short o, size_t l) = 0;
      virtual ~Function() {}
    };

  protected:
    N      tnode;  ///< tree node
    V_Tree tparts; ///< tree parts respectively child nodes

  protected:
    TStyxTree();          ///< The constructer creates an uninitialized tree.
   
                          /// delete tree parts respectively child nodes
    virtual void          removeParts();

  public:
                          /// create a node based tree with no parts
                          /// (public tree constructor)
                          /// @param node tree node
                          /// @return the new allocated tree
    static  TStyxTree*    create(const N& node);
                          /// create a node based tree with parts
                          /// (public tree constructor)
                          /// @param node tree node
                          /// @param parts tree parts
                          /// @return the new allocated tree
    static  TStyxTree*    create(const N& node, V_Tree& parts);

    virtual ~TStyxTree(); ///< The Destructor releases all allocated nodes.

                          /// replace tree node values
                          /// @param node the tree node to assign
                          /// @return (this) tree
    virtual TStyxTree*    update(const N& node);
                          /// assignment operator
                          /// (node values will be replaced and parts copied)
                          /// @param tree the tree to assign
                          /// @return (this) tree
    virtual TStyxTree&    operator =(const TStyxTree& tree);

                          /// copy tree
                          /// (node and parts will be copied)
                          /// @param tree the tree to copy
                          /// @return the new allocated and copied tree
    static  TStyxTree*    copy(const TStyxTree* tree);

                          /// get tree node
                          /// @return tree node
    virtual N&            getNode();
                          /// get parts respectively child nodes
                          /// @return parts respectively child nodes
    virtual V_Tree&       getParts();
                          /// extract parts respectively child nodes
                          /// (resets/clears internal member)
                          /// @return parts respectively child nodes
    virtual V_Tree        extractParts();

                          /// depth first visitor
                          /// @param fun visitor function, 
                          /// called for each node in pre and post state
                          /// @param level tree level
    virtual void          visit
                          (
                            void (*fun)(TStyxTree& t, short o, size_t l), 
                            size_t level=0
                          );
                          /// depth first visitor
                          /// @param fun visitor function object, 
                          /// called for each node in pre and post state
                          /// @param level tree level
    virtual void          visit(Function& fun, size_t level=0);

                          /// find next tree node according predicate
                          /// @param fun predicate function, called for each node
                          /// @param recursive iterate all tree nodes ?
                          /// @return node based tree 
                          /// (predicate function result = true) or 0
    virtual TStyxTree*    find(bool (*fun)(TStyxTree& t), bool recursive=true);
                          /// find next tree node according predicate
                          /// @param fun predicate function object, called for each node
                          /// @param recursive iterate all tree nodes ?
                          /// @return node based tree 
                          /// (predicate function object result = true) or 0
    virtual TStyxTree*    find(Predicate& fun, bool recursive=true);

                          /// get depth first iterator
                          /// @return depth first iterator
    virtual DF_Iter       dfbegin();
                          /// get breath first iterator
                          /// @return breath first iterator
    virtual BF_Iter       bfbegin();
  };


  /* tree iterator implementation ------------------------------------------ */

  template <class T, short O> 
  TStyxTreeIter<T,O>::TStyxTreeIter(T* tree)
  { 
    type  = O;
    state = TI_STATE_PRAE;
    if( tree ) 
    { 
      root.push_back(tree);
      T_Pos p(&root,root.begin());
      stack.push_back(p);
    }
  }
  
  template <class T, short O> 
  TStyxTreeIter<T,O>::~TStyxTreeIter()
  {
    stack.clear();
  }
  
  template <class T, short O> 
  short TStyxTreeIter<T,O>::getState()
  {
    return state;
  }
  
  template <class T, short O> 
  T* TStyxTreeIter<T,O>::getTerm()
  {
    if( end() ) return 0;
    T_Pos& p = stack[stack.size()-1];
    return *p.second;
  }
  
  template <class T, short O> 
  const typename TStyxTreeIter<T,O>::T_Iter& TStyxTreeIter<T,O>::getStack()
  {
    return stack;
  }
  
  template <class T, short O> 
  TStyxTreeIter<T,O>& TStyxTreeIter<T,O>::skip()
  {
    state = TI_STATE_POST;
    return *this;
  }
  
  template <class T, short O> 
  TStyxTreeIter<T,O>& TStyxTreeIter<T,O>::bfnext()
  {
    if( end() ) return *this;
    if( state == TI_STATE_PRAE )
    { T_Pos& cur = stack[stack.size()-1];
      ++cur.second;
      if( cur.second != (*cur.first).end() )
        return *this;
      cur.second = (*cur.first).begin();
      state = TI_STATE_POST; 
    }
    else /* TI_STATE_POST */
    { T_Pos& cur = stack[stack.size()-1];
      vector<T* >& parts = (*cur.second)->getParts();
      if( !parts.empty() )
      {
        state = TI_STATE_PRAE; 
        T_Pos p(&parts,parts.begin());
        stack.push_back(p);
        return *this;
      }
      ++cur.second;
      while( !end() )
      { T_Pos& cur = stack[stack.size()-1];
        if( cur.second == (*cur.first).end() )
        {
          stack.pop_back();
          if( !end() )
          { T_Pos& cur = stack[stack.size()-1];
            if( cur.second != (*cur.first).end() )
              ++cur.second;
          }
        }
        else break;
      }
    }
    return *this;
  }
  
  template <class T, short O> 
  TStyxTreeIter<T,O>& TStyxTreeIter<T,O>::dfnext()
  {
    if( end() ) return *this;
    if( state == TI_STATE_PRAE )
    { T_Pos& cur = stack[stack.size()-1];
      vector<T* >& parts = (*cur.second)->getParts();
      if( parts.empty() )
      {
        state = TI_STATE_POST; 
        return *this;
      }
      T_Pos p(&parts,parts.begin());
      stack.push_back(p);
    }
    else /* TI_STATE_POST */
    { T_Pos& cur = stack[stack.size()-1];
      ++cur.second;
      if( cur.second != (*cur.first).end() )
      {
        state = TI_STATE_PRAE; 
        return *this;
      }
      stack.pop_back();
    }
    return *this;
  }
  
  template <class T, short O> 
  TStyxTreeIter<T,O>& TStyxTreeIter<T,O>::operator ++()
  {
    return type == TI_TYPE_DF ? dfnext() : bfnext();
  }
  
  template <class T, short O> 
  bool TStyxTreeIter<T,O>::end()
  {
    return stack.size() == 0;
  }


  /* tree implementation --------------------------------------------------- */
  
  template <class N> 
  TStyxTree<N>::TStyxTree()
  {
  }
  
  template <class N> 
  void TStyxTree<N>::removeParts()
  { 
    for( size_t cnt=tparts.size(), i=0; i < cnt; ++i )
    {
      delete tparts[i];
    }
    tparts.clear();
  }
  
  template <class N> 
  TStyxTree<N>::~TStyxTree()
  { 
    removeParts();
  }
  
  template <class N> 
  TStyxTree<N>* TStyxTree<N>::create(const N& node)
  { TStyxTree* tree = new TStyxTree();
    if( tree ) tree->tnode = node;
    return tree;
  }
  
  template <class N> 
  TStyxTree<N>* TStyxTree<N>::create(const N& node, V_Tree& parts)
  { TStyxTree* tree = new TStyxTree();
    if( tree )
    {
      tree->tnode  = node;
      tree->tparts = parts;
    }
    return tree;
  }
  
  template <class N> 
  TStyxTree<N>* TStyxTree<N>::update(const N& node)
  {
    tnode = node;
    return this;
  }
  
  template <class N> 
  TStyxTree<N>& TStyxTree<N>::operator =(const TStyxTree<N>& tree)
  {
    tnode = tree.tnode;
    if( !tparts.empty() ) removeParts();
    for( size_t cnt=tree.tparts.size(), i=0; i < cnt; ++i )
    { TStyxTree* t = new TStyxTree();
      if( ! t ) break;
      *t = *tree.tparts[i];
      tparts.push_back(t);
    }
    return *this;
  }
  
  template <class N> 
  TStyxTree<N>* TStyxTree<N>::copy(const TStyxTree<N>* tree)
  { 
    if( !tree ) return 0;
    TStyxTree* t = new TStyxTree();
    if( t ) *t = *tree;
    return t;
  }
  
  template <class N> 
  N& TStyxTree<N>::getNode()
  {
    return tnode;
  }
  
  template <class N> 
  typename TStyxTree<N>::V_Tree& TStyxTree<N>::getParts()
  {
    return tparts;
  }
  
  template <class N> 
  typename TStyxTree<N>::V_Tree TStyxTree<N>::extractParts()
  { V_Tree parts = tparts;
    tparts.clear();
    return parts;
  }
  
  template <class N> 
  void TStyxTree<N>::visit
       ( 
         void (*fun)(TStyxTree<N>& t, short o, size_t l), size_t level
       )
  { 
    if( fun ) (*fun)(*this,TI_STATE_PRAE,level);
    for( size_t cnt=tparts.size(), i=0; i < cnt; ++i )
    {
      tparts[i]->visit(fun,level+1);
    }
    if( fun ) (*fun)(*this,TI_STATE_POST,level);
  }
  
  template <class N> 
  void TStyxTree<N>::visit
       ( 
         Function& fun, size_t level
       )
  { 
    fun(*this,TI_STATE_PRAE,level);
    for( size_t cnt=tparts.size(), i=0; i < cnt; ++i )
    {
      tparts[i]->visit(fun,level+1);
    }
    fun(*this,TI_STATE_POST,level);
  }
  
  template <class N> 
  TStyxTree<N>* TStyxTree<N>::find
             (
               bool (*fun)(TStyxTree<N>& t), bool recursive
             )
  { 
    if( !fun ) return 0;
    if( (*fun)(*this) ) return this;
    for( size_t cnt=tparts.size(), i=0; i < cnt; ++i )
    {
      TStyxTree* t = recursive 
                     ? tparts[i]->find(fun,true)
                     : (*fun)(*tparts[i]) ? tparts[i] : 0;
      if( t != 0 ) return t;
    }
    return 0;
  }
  
  template <class N> 
  TStyxTree<N>* TStyxTree<N>::find
             (
               Predicate& fun, bool recursive
             )
  { 
    if( fun(*this) ) return this;
    for( size_t cnt=tparts.size(), i=0; i < cnt; ++i )
    {
      TStyxTree* t = recursive 
                     ? tparts[i]->find(fun,true)
                     : fun(*tparts[i]) ? tparts[i] : 0;
      if( t != 0 ) return t;
    }
    return 0;
  }
  
  template <class N> 
  typename TStyxTree<N>::DF_Iter TStyxTree<N>::dfbegin()
  {
    return DF_Iter(this);
  }
  
  template <class N> 
  typename TStyxTree<N>::BF_Iter TStyxTree<N>::bfbegin()
  {
    return BF_Iter(this);
  }

  //@}

  //@}

}

#endif
