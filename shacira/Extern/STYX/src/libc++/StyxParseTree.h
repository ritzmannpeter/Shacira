/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxParseTree.h]   Styx Parse Tree Implementation (C++)                 */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2005 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_PARSETREE_INCL
#define STYX_PARSETREE_INCL


#include <wctype.h>
#include <string>
#include <vector>
#include <map>

#include "StyxStreamParser.h"
#include "StyxTree.h"

/** @file
    Abstract Styx parse tree
*/


namespace styx
{
  using namespace std;

  /** @addtogroup StyxLibraryCPP
      C++ Scanner & parser library
  */
  //@{

  /** @addtogroup StyxParseTree
      Abstract Styx parse tree
  */
  //@{


  /* Parse tree declaration ----------------------------------------------- */

  const char* TREE_NODE_ERROR = "[error]"; ///< error node (token, production)
  const char* TREE_NODE_LIST  = "[list]";  ///< nonterminal list

  /// parse tree node template
  template <class TC /* token character type */>
  struct StyxNode
  {
    typedef basic_string<TC > tstring;
    typedef vector<string>    V_string;

    short    type; ///< symbol type
                   ///< @link #EStyxCfgSymType (--\> definition) @endlink
    V_string name; ///< terminal    --> symbol name
                   ///< nonterminal --> class symbol, symbol, production name
                   ///<              or class symbol, production name
    tstring  val;  ///< terminal value
    string   src;  ///< source identifier
    long     row;  ///< source line
    long     col;  ///< source column

           /// comment node ?
           /// @return true for a comment node
    bool   isComment()          { return styx::isComment(type); }
           /// regular token node ?
           /// @return true for a regular token node
    bool   isToken()            { return styx::isToken(type); }
           /// (single byte or unicode) keword node ?
           /// @return true for a (single byte or unicode) keword node ?
    bool   isKeyword()          { return styx::isKeyword(type); }
           /// unicode keyword node ?
           /// @return true for a unicode keword node ?
    bool   isUnicodeKeyword()    { return styx::isUnicodeKeyword(type); }
           /// nonterminal node ?
           /// @return true for a nonterminal node
    bool   isNonterminal()      { return styx::isNonterminal(type); }
           /// token or nonterminal node ?
           /// @return true for a token or nonterminal node
    bool   isTokenNonterminal() { return styx::isTokenNonterminal(type); }
           /// token or keyword node ?
           /// @return true for a token or keyword node
    bool   isTokenKeyword()     { return styx::isTokenKeyword(type); }
           /// terminal node ?
           /// @return true for a terminal node
    bool   isTerminal()         { return styx::isTerminal(type); }

           /// get regular token type
           /// @return regular token type
           ///< @link #EStyxCfgSymType (--\> definition) @endlink
    short  getTokenType()       { return styx::CFG_TYP_TOK; }
           /// get nonterminal type
           /// @return nonterminal type
           ///< @link #EStyxCfgSymType (--\> definition) @endlink
    short  getNonterminalType() { return styx::CFG_TYP_NTM; }

           /// get symbol or class name
           /// @return symbol or class name or ""
    string getSymbolName()
           {
             if( name.size() == 0 ) return "";
             return name.size() < 3 ? name[0] : name[1];
           }

           /// get class name
           /// @return class name or ""
    string getClassName()
           {
             if( name.size() == 0 ) return "";
             return name[0];
           }

           /// get production name
           /// @return production name or ""
    string getProductionName()
           {
             if( !isNonterminal() || name.size() < 2 ) return "";
             return name[name.size()-1];
           }
    
           /// nil production node ?
           /// @return true for a nil production node
    bool   isNilProduction()    
           { 
             return isNonterminal() && name.size() > 1 &&
                    styx::isNilProduction(name[name.size()-1]); 
           }
           /// cons production node ?
           /// @return true for a cons production node
    bool   isConsProduction()   
           { 
             return isNonterminal() && name.size() > 1 &&
                    styx::isConsProduction(name[name.size()-1]); 
           }
           /// ignore production node ?
           /// @return true for an ignore production node
    bool   isIgnProduction()    
           { 
             return isNonterminal() && name.size() > 1 &&
                    styx::isIgnProduction(name[name.size()-1]); 
           }
           /// list production node ?
           /// @return true for a list production node
    bool   isListProduction()   
           { 
             return getProductionName() == styx::TREE_NODE_LIST;
           }

           /// error node ?
           /// @return true for an error node
    bool   isError()   
           { 
             return name.size() == 0 ||
                    name[0] == styx::TREE_NODE_ERROR ||
                    name[name.size()-1] == styx::TREE_NODE_ERROR;
           }
  };

  /// abstract parse tree template
  template <class TC /* token character type */> 
  class TStyxParseTree : public TStyxTree<StyxNode<TC> >
  {
  public:
    typedef basic_string<TC >      tstring;
    typedef StyxNode<TC >          T_Node;
    typedef TStyxTree<T_Node>      T_BaseTree;
    typedef TStyxParseTree<TC>     T_Tree;
    typedef vector<T_BaseTree* >   V_BaseTree;
    typedef vector<T_Tree* >       V_Tree;
    typedef TStyxTreeIter<T_BaseTree,TI_TYPE_DF > DF_Iter;
    typedef TStyxTreeIter<T_BaseTree,TI_TYPE_BF > BF_Iter;

  protected:

    /// visitor function object to print a tree node
    struct T_printNode : public TStyxTree<T_Node>::Function
    {
      void operator() (T_BaseTree& t, short o, size_t l)
      { T_Node& n = t.getNode();
        if( o == TI_STATE_PRAE )
        {
          //fprintf(stdout,"\n%*s",(int)(2*l),"");
          fprintf(stdout,"\n%*s",(int)l,"");
          cout << "[";
          if( n.isComment() ) cout << "Comment";
          else
          if( n.isKeyword() ) cout << "Keyword";
          else
          {
            for( size_t cnt=n.name.size(), i=0; i < cnt; ++i )
            {
              if( i > 0 ) cout << ".";
              cout << n.name[i];
            }
          }
          cout << " (" << n.row << "," << n.col << ")";
          if( !n.isNonterminal() )
          { bool unicode = ( sizeof(TC) != sizeof(char) );
            cout << " \"";
            if( !unicode ) fprintf(stdout,"%s",(char*)n.val.c_str());
            else fprintf(stdout,"%S",(wchar_t*)n.val.c_str());
            cout << "\"";
          }
        }
        if( o == TI_STATE_POST )
          cout << "]";
      }
    };

    /// visitor function object to get a tree node value as string
    struct T_value2string : public TStyxTree<T_Node>::Function
    {
      tstring treestring;

      void operator() (T_BaseTree& t, short o, size_t l)
      { T_Node& n = t.getNode();
        if( o == TI_STATE_PRAE )
        {
          if( !n.isNonterminal() )
          { bool unicode = ( sizeof(TC) != sizeof(char) );
            if( !unicode ) 
            { char c = ' '; treestring += c; }
            else 
            { wchar_t c = L' '; treestring += c; }
            treestring += n.val;
          }
        }
      }
    };

  protected:
    /// The constructer creates an uninitialized parse tree.
    TStyxParseTree(); 
    
  public:
    /// The Destructor releases all allocated nodes.
    virtual ~TStyxParseTree();

                            // create tree node with no parts
                            // (public tree constructor)
    static  TStyxParseTree* create(const T_Node& node);
                            // create tree node with parts
                            // (public tree constructor)
    static  TStyxParseTree* create(const T_Node& node, V_Tree& parts);

                            // assignment operator
                            // (tree will be copied)
    //virtual TStyxParseTree& operator =(const TStyxParseTree& tree);
    virtual TStyxParseTree& operator =(const T_Tree& tree);

                            // copy tree
    //static  TStyxParseTree* copy(const TStyxParseTree* tree);
    static  TStyxParseTree* copy(const T_Tree* tree);

                            /// print parse tree (to stdout)
    virtual void            print();
                            /// tree --\> string
                            /// @return parse tree as string
    virtual tstring         asString();
  };


  /* Parser declaration --------------------------------------------------- */

  /// abstract tree parser template
  template <class TC /* token character type */, 
            class T=TStyxParseTree<TC> /* parse tree type */>
  class TStyxTreeParser : public TStyxStreamParser<TC,T >
  {
  public:
    typedef basic_string<TC >      tstring;
    typedef StyxNode<TC >          T_Node;
    typedef TStyxTree<T_Node>      T_BaseTree;
    typedef vector<T_BaseTree* >   V_BaseTree;
    typedef T                      T_Tree;
    typedef vector<T_Tree*>        V_Tree;
    typedef vector<T_Tree*>        V_value;
    typedef StyxToken<tstring>     T_Token;

  protected:
    typedef map<T_Tree*,V_Tree>    M_Comments;

  protected:
    T_Tree*    ParseTree;  ///< parse tree under construction
    V_Tree     CComments;  ///< unassigned comments 
    M_Comments PComments;  ///< assigned comment prefixes
    bool       conv;       ///< convert token and/or productions ?
    bool       ast;        ///< construct an abstract syntax tree ?

  protected:
                    /// delete all comment tree nodes
    virtual void    removeComments();
                    /// delete tree nodes in list
                    /// @param treelist list of tree nodes
    virtual void    removeTreeList(V_Tree& treelist);
                    // reset --> delete all tree nodes
                    // else  --> delete all tree nodes except parse tree
    virtual void    removeValues(bool reset);

                    // shift token (success=true, Value=new stack value)
    virtual bool    shift(const T_Token& Token, T_Tree*& Value);
                    // reduce production (success=true, Value=new stack value)
                    // accept || !error --> Index=production
                    // else             --> Index=nonterminal
    virtual bool    reduce
                    (
                      long Index, V_value& Values, 
                      bool accept, bool error, T_Tree*& Value
                    );
                    /// convert shift token value, if conversion is enabled 
                    /// @param TokenName external token name
                    /// @param TokenValue [changeable] token value
                    /// @return true or false on error
    virtual bool    convert(string TokenName, tstring& TokenValue);
                    /// convert reduced tree, if conversion is enabled 
                    /// @param Tree [changeable] reduced tree,
                    /// the old tree will be deleted by the parser.
                    /// @return true or false on error
    virtual bool    convert(T_Tree*& Tree);

  public:
    /// The constructor creates and initializes the tree parser.
    /// @param PTable Styx parse table
    /// @param TStream Styx scanner
    /// @param conv enable token and/or production conversion ?
    /// @param ast construct an abstract syntax tree ?
    TStyxTreeParser
    ( 
      CStyxParseTable* PTable = 0, CStyxScanner* TStream = 0, 
      bool conv = false, bool ast = false
    );
    virtual ~TStyxTreeParser();

                    /// extract constructed parse tree
                    /// (resets the internal member)
                    /// @return the constructed parse tree or 0
    virtual T_Tree* extractParseTree();
  };


  /* Parse tree implementation ----------------------------------------------- */

  template <class TC> 
  TStyxParseTree<TC>::TStyxParseTree()
  : TStyxTree<T_Node>()
  {
  }

  template <class TC> 
  TStyxParseTree<TC>::~TStyxParseTree()
  {
  }

  template <class TC> 
  TStyxParseTree<TC>* TStyxParseTree<TC>::create(const T_Node& node)
  { TStyxParseTree* tree = new TStyxParseTree();
    if( tree ) tree->tnode = node;
    return tree;
  }
  
  template <class TC> 
  TStyxParseTree<TC>* TStyxParseTree<TC>::create
                      (
                        const T_Node& node, V_Tree& parts
                      )
  { TStyxParseTree* tree = new TStyxParseTree();
    if( tree )
    {
      tree->tnode  = node;
      tree->tparts = (V_BaseTree&)parts;
    }
    return tree;
  }
  
  template <class TC> 
  TStyxParseTree<TC>& TStyxParseTree<TC>::operator =(const T_Tree& tree)
  {
    this->tnode = tree.tnode;
    if( !this->tparts.empty() ) this->removeParts();
    for( size_t cnt=tree.tparts.size(), i=0; i < cnt; ++i )
    { TStyxParseTree* t = new TStyxParseTree();
      if( ! t ) break;
      *t = *((TStyxParseTree*)tree.tparts[i]);
      this->tparts.push_back(t);
    }
    return *this;
  }

  template <class TC> 
  TStyxParseTree<TC>* TStyxParseTree<TC>::copy(const T_Tree* tree)
  { 
    if( !tree ) return 0;
    TStyxParseTree* t = new TStyxParseTree();
    if( t ) *t = *tree;
    return t;
  }

  template <class TC> 
  void TStyxParseTree<TC>::print()
  { T_printNode printNode;
    if( this->tnode.src.length() > 0 )
      cout << "\nDerivation Tree from Source : " << this->tnode.src;
    else
      cout << "\nDerivation Tree : ";
    cout << "\n";
    visit(printNode);
    cout << "\n";
  }

  template <class TC> 
  basic_string<TC> TStyxParseTree<TC>::asString()
  { T_value2string value2string;
    visit(value2string);
    return value2string.treestring;
  }


  /* Parser implementation --------------------------------------------------- */

  template <class TC, class T> 
  TStyxTreeParser<TC,T>::TStyxTreeParser
  (
    CStyxParseTable* PTable, CStyxScanner* TStream,
    bool conv, bool ast
  )
  : TStyxStreamParser<TC,T_Tree>(PTable,TStream)
  {
    ParseTree  = 0;
    this->conv = conv;
    this->ast  = ast;
  }
  
  template <class TC, class T> 
  TStyxTreeParser<TC,T>::~TStyxTreeParser()
  {
  }
  
  template <class TC, class T> 
  void TStyxTreeParser<TC,T>::removeTreeList(V_Tree& treelist)
  {
    for( size_t cnt=treelist.size(), i=0; i < cnt; ++i )
    {
      if( treelist[i] )
      {
        delete treelist[i]; treelist[i] = 0;
      }
    }
    treelist.clear();
  }
  
  template <class TC, class T> 
  void TStyxTreeParser<TC,T>::removeComments()
  { typename M_Comments::iterator pos;
    for( pos = PComments.begin(); pos != PComments.end(); ++pos )
    { 
      removeTreeList((*pos).second);
    }
    PComments.clear();
    removeTreeList(CComments);
  }
  
  template <class TC, class T> 
  void TStyxTreeParser<TC,T>::removeValues(bool reset)
  {
    removeComments();
    for( size_t cnt=this->ValueStack.size(), i=0; i < cnt; ++i )
    {
      if( this->ValueStack[i] && this->ValueStack[i] != ParseTree )
      {
        delete this->ValueStack[i]; this->ValueStack[i] = 0;
      }
    }
    if( reset && ParseTree ) 
    {
      delete ParseTree; ParseTree = 0;
    }
  }

  template <class TC, class T> 
  bool TStyxTreeParser<TC,T>::convert(string TokenName, tstring& TokenValue)
  {
    return true;
  }
  
  template <class TC, class T> 
  bool TStyxTreeParser<TC,T>::convert(T_Tree*& Tree)
  {
    return true;
  }
  
  template <class TC, class T> 
  bool TStyxTreeParser<TC,T>::shift(const T_Token& Token, T_Tree*& Value)
  { CStyxParseTable* p = (CStyxParseTable*)this->ParseTable;
    ParseTree = Value = 0;
    if( !this->initok || !p ) return false;
    long tsym = p->TerminalIndex2Symbol(Token.Index);
    if( ast && p->isComment(tsym) ) return true;
    T_Node node; 
    node.name.push_back
    (
      Token.Index >= 0 
      ? p->getSymbolName(tsym) : styx::TREE_NODE_ERROR
    );
    node.type = Token.Index >= 0
                ? p->getSymbolType(tsym) : node.getTokenType();
    node.val  = Token.Value;
    node.src  = Token.File;
    node.row  = Token.Line;
    node.col  = Token.Column;
    if( conv && !convert(node.name[0],node.val) )
    {
      error("conversion of token '" + node.name[0] + "' failed");
      return false;
    }
    T_Tree* tree = T_Tree::create(node);
    if( !tree ) 
    {
      this->error("node creation failed");
      return false;
    }
    if( node.isComment() )
      CComments.push_back(tree);
    else
    if( CComments.size() > 0 )
    {
      PComments[tree] = CComments;
      CComments.clear();
    }
    if( !node.isComment() ) ParseTree = Value = tree;
    return true;
  }
  
  template <class TC, class T> 
  bool TStyxTreeParser<TC,T>::reduce
  (
    long Index, V_value& Values, 
    bool accept, bool error, T_Tree*& Value
  )
  { CStyxParseTable* p = (CStyxParseTable*)this->ParseTable;
    ParseTree = Value = 0;
    if( !this->initok || !p || !this->Scanner ) return false;
    T_Node node; 
    long tsym = ( accept || !error )
                ? p->getProductionNonterminal(Index)
                : p->NonterminalIndex2Symbol(Index),
         tcls = p->NonterminalIndex2Symbol
                (
                  p->NonterminalIndex2Class(p->NonterminalSymbol2Index(tsym))
                );
    node.name.push_back(p->getSymbolName(tcls));
    if( !ast )
    {
      node.name.push_back(p->getSymbolName(tsym));
    }
    node.type = node.getNonterminalType();
    node.name.push_back
    (
      ( !error ) ? p->getProductionName(Index) : styx::TREE_NODE_ERROR
    );
    node.src = this->Scanner->getFile();
    if( Values.size() > 0 )
    {
      node.row = Values[0]->getNode().row;
      node.col = Values[0]->getNode().col;
    }
    else
    {
      node.row = this->Scanner->getLine();
      node.col = this->Scanner->getCol();
    }
    V_Tree parts;
    for( size_t cnt = Values.size(), i = 0; i < cnt; ++i )
    {
      if( !Values[i] ) continue;
      if( !ast && PComments.size() > 0 )
      { typename M_Comments::iterator pos = PComments.find(Values[i]);
        if( pos != PComments.end() )
        {
          parts.insert(parts.end(),(*pos).second.begin(),(*pos).second.end());
          PComments.erase(pos);
        }
      }
      if( ast && node.isConsProduction() && !Values[i]->getNode().isKeyword() )
      {
        if( Values[i]->getNode().isNilProduction() )
        {
          delete Values[i];
        }
        else
        if( Values[i]->getNode().isListProduction() )
        { V_BaseTree listparts = Values[i]->extractParts();
          for( size_t cnt=listparts.size(), j=0; j < cnt; ++j )
          {
            parts.push_back((T_Tree*)listparts[j]);
          }
          delete Values[i];
        }
        else parts.push_back(Values[i]);
      }
      else
      if( !ast || !Values[i]->getNode().isKeyword() )
        parts.push_back(Values[i]);
      else delete Values[i];
    }
    if( !ast && CComments.size() > 0 )
    {
      parts.insert(parts.end(),CComments.begin(),CComments.end());
      CComments.clear();
    }
    if( ast && node.isConsProduction() )
    {
      node.name[node.name.size()-1] = styx::TREE_NODE_LIST;
    }
    if( ast && node.isIgnProduction() )
    {
      if( parts.size() != 1 )
      {
        this->error
        (
          "reduction of ignore production '" + 
          node.name[0] + "." + node.name[1] + "' failed"
        );
        removeTreeList(parts);
        return false;
      }
      return ( ParseTree = Value = parts.front() ) != 0;
    }
    T_Tree* tree = T_Tree::create(node,parts);
    if( !tree ) 
    {
      this->error("node creation failed");
      removeTreeList(parts);
      return false;
    }
    Value = tree;
    if( conv && !convert(Value) )
    {
      this->error("conversion of nonterminal '" + node.name[0] + "' failed");
      if( Value != tree ) delete tree;
      ParseTree = Value;
      return false;
    }
    if( Value != tree ) delete tree;
    ParseTree = Value;
    return true;
  }
  
  template <class TC, class T> 
  T* TStyxTreeParser<TC,T>::extractParseTree()
  { T_Tree* tree = ParseTree;
    ParseTree = 0;
    return tree; 
  }

  typedef TStyxTreeParser<char>    TStyxTreeParserS;
  typedef TStyxTreeParser<wchar_t> TStyxTreeParserU;

  //@}

  //@}
}

#endif
