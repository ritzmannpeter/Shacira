/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [scn_gen.c]                Scanner Generator                             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* TODO                                                        */
/* -  Write a document on the source                           */

#include "scn_io.h"

#include "list.h"
#include "ctx_app.h"
#include "scn_imp.h"

/*!
  <p>The module [scn_gen] supports the construction of regular sets and
  produces the scanner definitions as base for the 
  <a href="scn_base.htm">scan streams</a>.
  <p>The complexity of the scanner is linear. A consequence of this design-goal 
  is its restriction to a one-character-lookahead.
  <p>The construction of regular sets is reentrant.
  There also exists a reentrant version of the scanner production.<br>
*/

/*I------------------------- Type of regular sets ------------------------- */

AbstractType(RegSet_T); /* Regular Set */

/* -- Graph for finite automation -- */

#define RegSet_IMP(X) ((regset_t)(X))
#define RegSet_ADT(X) ((RegSet_T)(X))

ConcreteType(regset_t)
{
  int          id;
  List(faNode) Nodes; /* !empty; fst == start */
};

ConcreteType(faNode)
{
  int           id;
  regset_t      Belongs;
  List(faNode)  Source;  /* list of "source" nodes */
  int           term;    /* terminal state if > 0 */
  List(dfaEdge) Edges;
  int           flag1;
  int           flag2;
};

ConcreteType(dfaEdge)
{
  wc_char dfa_lower;
  wc_char dfa_upper;
  faNode  dfa_toNode;
};

ConcreteType(nfaEdge)
{
  wc_char      nfa_lower;
  wc_char      nfa_upper;
  List(faNode) nfa_toNodes;
};

/* -- Edge constructor -- */

static dfaEdge newDfaEdge(wc_char lower, wc_char upper, faNode toNode)
{ dfaEdge res = New(dfaEdge);
  res->dfa_lower  = lower;
  res->dfa_upper  = upper;
  res->dfa_toNode = toNode;
  return res;
}

static nfaEdge newNfaEdge(wc_char lower, wc_char upper, List(faNode) toNodes)
{ nfaEdge res = New(nfaEdge);
  res->nfa_lower   = lower;
  res->nfa_upper   = upper;
  res->nfa_toNodes = toNodes;
  return res;
}

/*I-------------------------- Disposing ----------------------------------- */

static void freeNothing(Abs_T dummy)
{
}

static void freeNfaEdge(nfaEdge x)
{
  freeList(x->nfa_toNodes, freeNothing);
  FreeMem(x);
}

static void freeDfaNode(faNode x)
/* frees dfa node */
{
  freeList(x->Source, freeNothing);
  freeList(x->Edges, FreeMem);
  FreeMem(x);
}

void RegSet_Free(RegSet_T g)
/* frees regular set 'g' */
{
  freeList(RegSet_IMP(g)->Nodes, (void (*)(Abs_T x)) freeDfaNode);
  FreeMem(g);
}

/*I-------------------------- RegSet Constructors ------------------------- */

/*!
  <p>The resulting regular sets when applying one of the following functions
     have to be released.
*/

/* -- basic graph constructors -- */

static int RegSet_TId = 1;

RegSet_T RegSet_Epsilon(void)
/* epsilon "" */
{ faNode s0   = New(faNode);
  regset_t res = New(regset_t);
#if defined( _MSDOS ) || defined( _WIN32 )
  res->id     = InterlockedIncrement(&RegSet_TId);
#else
  res->id     = RegSet_TId ++;
#endif
  res->Nodes  = cons(s0,NULL);
  s0->id      = 0;
  s0->Belongs = res;
  s0->Source  = NULL;
  s0->term    = True; /* terminal */
  s0->Edges   = NULL;
  s0->flag1   = 0;
  s0->flag2   = 0;
  return RegSet_ADT(res);
}

RegSet_T RegSet_Empty(void)
/* empty set '' */
{ faNode s0    = New(faNode);
  regset_t res = New(regset_t);
#if defined( _MSDOS ) || defined( _WIN32 )
  res->id      = InterlockedIncrement(&RegSet_TId);
#else
  res->id      = RegSet_TId ++;
#endif
  res->Nodes   = cons(s0,NULL);
  s0->id       = 0;
  s0->Belongs  = res;
  s0->Source   = NULL;
  s0->term     = False; /* non - terminal */
  s0->Edges    = NULL;
  s0->flag1    = 0;
  s0->flag2    = 0;
  return RegSet_ADT(res);
}

RegSet_T RegSet_Range(wc_char dfa_lower, wc_char dfa_upper)
/* character range L .. U */
{ faNode s0   = New(faNode);
  faNode s1   = New(faNode);
  regset_t res = New(regset_t);
  c_bug
  (
    ((unsigned long)dfa_lower) <= ((unsigned long)dfa_upper), 
    "RegSet_Range(%ld,%ld) must be a range",
    ((unsigned long)dfa_lower),((unsigned long)dfa_upper)
  );
#if defined( _MSDOS ) || defined( _WIN32 )
  res->id     = InterlockedIncrement(&RegSet_TId);
#else
  res->id     = RegSet_TId ++;
#endif
  res->Nodes  = cons(s0,cons(s1,NULL));
  s0->id      = 0;
  s0->Belongs = res;
  s0->Source  = NULL;
  s0->term    = False; /* non - terminal */
  s0->Edges   = cons(newDfaEdge(dfa_lower,dfa_upper,s1),NULL);
  s0->flag1   = 0;
  s0->flag2   = 0;
  s1->id      = 1;
  s1->Belongs = res;
  s1->Source  = NULL;
  s1->term    = True; /* terminal */
  s1->Edges   = NULL;
  s1->flag1   = 0;
  s1->flag2   = 0;
  return RegSet_ADT(res);
}

RegSet_T RegSet_Char(wc_char c)
/* character 'c' */
{
  return RegSet_Range(c,c);
}

/* -- Graph Combinator -- */

static int lex(int A, int B) { return A ? A : B; }

static bool compNodes(faNode a, faNode b)
/* order Nodes */
{
  return lex( a->Belongs->id - b->Belongs->id, a->id - b->id );
}

static List(faNode) insertState(faNode x, List(faNode) y)
/* inserts a state into a source id */
/* we keep them ordered for identification */
{
  return empty(y)                        ? cons(x,y)
       : compNodes(x,fst(faNode,y)) == 0 ? y
       : compNodes(x,fst(faNode,y)) <  0 ? cons(x,y)
       : ((*rst_ref(y) = insertState(x,rst(y))), y);
}

static List(nfaEdge) copyEdges
                     (
                       List(dfaEdge) x, RegSet_T lambdaFrom, RegSet_T lambdaTo
                     )
/* copies an DFA-Edge to a NFA-Edge extending lambda edges */
{
  if (empty(x))
    return NULL;
  else
  { List(faNode) src = NULL;
    faNode nod = fst(dfaEdge,x)->dfa_toNode;
    src = insertState(nod,src);
    if (nod->Belongs == RegSet_IMP(lambdaFrom) && nod->term > 0)
      src = insertState(fst(faNode,RegSet_IMP(lambdaTo)->Nodes),src);
    return cons(newNfaEdge(fst(dfaEdge,x)->dfa_lower,
                        fst(dfaEdge,x)->dfa_upper,
                        src ),
                copyEdges(rst(x), lambdaFrom,lambdaTo) );
  }
}

static List(faNode) nodesUnion(List(faNode) x, List(faNode) y)
{
  if ( empty(x) &&  empty(y))
    return NULL;
  if ( empty(x) && !empty(y))
    return cons(fst(faNode,y),nodesUnion(NULL,rst(y)));
  if (!empty(x) &&  empty(y))
    return cons(fst(faNode,x),nodesUnion(rst(x),NULL));
  if (compNodes(fst(faNode,x),fst(faNode,y)) < 0)
    return cons(fst(faNode,x),nodesUnion(rst(x),y));
  else
  if (compNodes(fst(faNode,x),fst(faNode,y)) > 0)
    return cons(fst(faNode,y),nodesUnion(x,rst(y)));
  else
    return cons(fst(faNode,x),nodesUnion(rst(x),rst(y)));
}

static bool equalStates(List(faNode) x, List(faNode) y)
{
  for (; !empty(x) && !empty(y); x=rst(x), y=rst(y))
    if (fst(faNode,x) != fst(faNode,y))
      return False;
  return empty(x) && empty(y);
}

static List(nfaEdge) consMerge(nfaEdge x, List(nfaEdge) y)
/* joins two edges if possible */
{
  if (!empty(y) &&
      x->nfa_upper+1 == fst(nfaEdge,y)->nfa_lower &&
      equalStates(x->nfa_toNodes,fst(nfaEdge,y)->nfa_toNodes) )
  {
    fst(nfaEdge,y)->nfa_lower = x->nfa_lower;
    freeNfaEdge(x);
    return y;
  }
  else
    return cons(x,y);
}

static List(nfaEdge) mergeEdges(List(nfaEdge) x, List(nfaEdge) y)
/* merges NFA-Edges x with NFA-Edges y */
/* Note that both lists are freed */
{ nfaEdge xe, ye; List(nfaEdge) xy, res;
  if (empty(x)) return y;
  if (empty(y)) return x;
  xy = x; xe = fst(nfaEdge,x); x = rst(x); FreeMem(xy);
  xy = y; ye = fst(nfaEdge,y); y = rst(y); FreeMem(xy);
  if (xe->nfa_upper > ye->nfa_upper)
  {
    { nfaEdge       a = xe, b = ye; xe = b; ye = a; }
    { List(nfaEdge) a = x,  b = y;  x  = b; y  = a; }
  }
  if (xe->nfa_upper < ye->nfa_lower)
    return consMerge(xe,mergeEdges(x,cons(ye,y)));
  /* we have a true intersection here */
  res = consMerge
        (
          newNfaEdge(MAX(xe->nfa_lower,ye->nfa_lower),
                  xe->nfa_upper,
                  nodesUnion(xe->nfa_toNodes, ye->nfa_toNodes) ),
          mergeEdges(x,
                     xe->nfa_upper < ye->nfa_upper
                     ? cons(newNfaEdge((wc_char)(xe->nfa_upper+1),
					                   ye->nfa_upper,
                                       nodesUnion(ye->nfa_toNodes, NULL)
                                   ),y )
                     : y )
        );
  if (xe->nfa_lower > ye->nfa_lower)
  { nfaEdge a = xe, b = ye; xe = b; ye = a; }
  if (xe->nfa_lower < ye->nfa_lower)
    res = consMerge(newNfaEdge(xe->nfa_lower, (wc_char)(ye->nfa_lower-1),
                               nodesUnion(xe->nfa_toNodes,NULL) ), res );
  freeNfaEdge(xe); freeNfaEdge(ye);
  return res;
}

/* -- */

static faNode identifySource(RegSet_T g, List(faNode) x)
/* identify state in g with Source equal to x */
{ List(faNode) *t; int i; faNode s0;
  for(i = 0, t = &RegSet_IMP(g)->Nodes; !empty(*t); i += 1, t = rst_ref(*t))
    if (equalStates( fst(faNode,*t)->Source, x))
    { freeList(x, freeNothing); return fst(faNode,*t); }
  s0 = New(faNode);
  s0->id      = i;
  s0->Belongs = RegSet_IMP(g);
  s0->Source  = x;
  s0->term    = False;
  s0->Edges   = NULL;
  s0->flag1   = 0;
  s0->flag2   = 0;
  *t = cons(s0,NULL);
  return s0;
}

static List(faNode) NfaToDfaEdges(RegSet_T g, List(nfaNode) x)
/* translates NfaEdges to DdfaEdges identifying or adding states to g */
{ List(nfaNode) t;
  for(t = x; !empty(t); t = rst(t))
  { nfaEdge e = fst(nfaEdge,t);
    ((dfaEdge)e)->dfa_toNode = identifySource(g, e->nfa_toNodes);
  }
  return (List(faNode)) x;
}

static List(faNode) RegSet_Starts
                    (
                      List(RegSet_T) graphs,
                      RegSet_T lambdaFrom,
                      RegSet_T lambdaTo
                    )
/* returns the list of start nodes of graphs */
/* frees x */
{ List(RegSet_T) x; List(faNode) y; faNode n;
  if (empty(graphs)) return NULL;
  x = rst(graphs);
  n = fst(faNode,fst(regset_t,graphs)->Nodes);
  FreeMem(graphs);
  y = RegSet_Starts(x, lambdaFrom,lambdaTo);
  if (n->Belongs == lambdaFrom && n->term > 0)
    y = insertState(fst(faNode,RegSet_IMP(lambdaTo)->Nodes),y);
  return insertState(n,y);
}

static RegSet_T RegSet_Merge
                (
                  List(RegSet_T) graphs, RegSet_T lambdaFrom, RegSet_T lambdaTo
                )
{ faNode s0   = New(faNode);
  List(faNode) Todo;
  regset_t res = New(regset_t);
#if defined( _MSDOS ) || defined( _WIN32 )
  res->id     = InterlockedIncrement(&RegSet_TId);
#else
  res->id     = RegSet_TId ++;
#endif
  res->Nodes  = cons(s0,NULL);
  s0->id      = 0;
  s0->Belongs = res;
  s0->Source  = RegSet_Starts(graphs,lambdaFrom,lambdaTo);
  s0->term    = False;
  s0->Edges   = NULL;
  s0->flag1   = 0;
  s0->flag2   = 0;
  for (Todo = res->Nodes; !empty(Todo); Todo = rst(Todo))
  { List(faNode) Nds; List(nfaEdge) NfaEdges = NULL;
    for( Nds = fst(faNode,Todo)->Source; !empty(Nds); Nds = rst(Nds))
      NfaEdges = mergeEdges
                 (
                   NfaEdges,
                   copyEdges(fst(faNode,Nds)->Edges,lambdaFrom,lambdaTo)
                 );
    fst(faNode,Todo)->Edges = NfaToDfaEdges(res, NfaEdges);
  }
  return RegSet_ADT(res);
}

/* -- graph reduction -- */

/* Ziel:    von allen Zustaenden aus kann ein terminaler Zustand erreicht */
/*          werden.                                                       */
/* Methode: entferne alle anderen                                         */

#define reachesNxt flag1
#define reachesTrm flag2

static void reachNodes(regset_t reg)
/* build the closure of terminal nodes via egdes */
{ List(faNode) nodes; List(dfaEdges) edges; bool changed = True;
  while (changed)
  { changed = False;
    for (nodes = reg->Nodes; !empty(nodes); nodes = rst(nodes))
    { faNode nod = fst(faNode,nodes);
      for (edges = nod->Edges; !empty(edges); edges = rst(edges))
        nod->reachesNxt |= fst(dfaEdge,edges)->dfa_toNode->reachesTrm;
    }
    for (nodes = reg->Nodes; !empty(nodes); nodes = rst(nodes))
    { faNode nod = fst(faNode,nodes);
      changed |= (nod->reachesNxt != nod->reachesTrm);
      nod->reachesTrm |= nod->reachesNxt;
    }
  }
}

static List(dfaEdge) combineRanges(List(dfaEdge) edges)
/* combines ranges if possible */
{ dfaEdge e1, e2; List(dfaEdge) rest;
  if (empty(edges) || empty(rst(edges))) return edges;
  rest = combineRanges(rst(edges));
  *rst_ref(edges) = rest;
  e1 = fst(dfaEdge,edges);
  e2 = fst(dfaEdge,rst(edges));
  if (e1->dfa_upper+1 != e2->dfa_lower || e1->dfa_toNode != e2->dfa_toNode)
    return edges;
  /* combine */
  e2->dfa_lower = e1->dfa_lower;
  FreeMem(e1); FreeMem(edges);
  return rest;
}

static void reduceGraph(RegSet_T g)
/* reduce graph g */
{ List(faNode) nods, *nodsp; int i;
  /* initialize marks */
  for (nods = RegSet_IMP(g)->Nodes; !empty(nods); nods = rst(nods))
  { faNode nod = fst(faNode,nods);
    nod->reachesTrm = (nod->term > 0);
    nod->reachesNxt = (nod->term > 0);
  }
  /* mark */
  reachNodes(RegSet_IMP(g));
  fst(faNode,RegSet_IMP(g)->Nodes)->reachesTrm = True;
  /* remove all edges leading to blind states */
  for (nods = RegSet_IMP(g)->Nodes; !empty(nods); nods = rst(nods))
  { faNode nod = fst(faNode,nods); List(dfaEdge) *edges;
    for (edges = &nod->Edges; !empty(*edges); )
    { dfaEdge edge = fst(dfaEdge,*edges);
      if (!edge->dfa_toNode->reachesTrm)
      { List(dfaEdge) here = *edges;
        *edges = rst(*edges); FreeMem(edge); FreeMem(here);
      }
      else
        edges = rst_ref(*edges);
    }
    nod->Edges = combineRanges(nod->Edges);
  }
  /* remove all blind states */
  for (i = 0, nodsp = &RegSet_IMP(g)->Nodes; !empty(*nodsp); )
  { faNode nod = fst(faNode,*nodsp);
    if (!nod->reachesTrm)
    { List(faNode) here = *nodsp; *nodsp = rst(*nodsp); FreeMem(here); FreeMem(nod); }
    else
    { nod->id = i; i += 1; nodsp = rst_ref(*nodsp); }
  }
}

/* -- graph minimation -- */

/* Ziel:    der Graph enthaelt keine aequivalenten Zustaende */
/* Methode: entferne alle aequivalenten Zustaende            */

#define currEquiv flag1
#define prevEquiv flag2

static faNode findNode(RegSet_T g, int NodeId)
{ List(faNode) nods;
  for (nods = RegSet_IMP(g)->Nodes; !empty(nods); nods = rst(nods))
    if ( fst(faNode,nods)->id == NodeId )
      return fst(faNode,nods);
  C_BUG; return NULL; /* dummy */
}

static bool sameEquiv(List(faNode) nods)
/* copy curr to prev; return true if all same */
{ bool res = True;
  for (; !empty(nods); nods = rst(nods))
  { faNode nod = fst(faNode,nods);
    res = res && (nod->prevEquiv == nod->currEquiv);
    nod->prevEquiv = nod->currEquiv;
  }
  return res;
}

static bool sameEquivClass(List(dfaEdge) edgs1, List(dfaEdge) edgs2)
/* return if both edge-lists are equivalent relative to prevEquiv */
{ dfaEdge edg1, edg2 ;
Loop1:
  if (empty(edgs1) && empty(edgs2)) return True;
  if (empty(edgs1) || empty(edgs2)) return False;
  edg1 = fst(dfaEdge,edgs1);
  edg2 = fst(dfaEdge,edgs2);
  if (edg1->dfa_lower != edg2->dfa_lower) return False;
Loop2:
  if (edg1->dfa_toNode->prevEquiv != edg2->dfa_toNode->prevEquiv) return False;
  if (edg1->dfa_upper == edg2->dfa_upper)
  {
    edgs1 = rst(edgs1); edgs2 = rst(edgs2);
    goto Loop1;
  }
  else
  if (edg1->dfa_upper < edg2->dfa_upper)
  {
    if (empty(rst(edgs1)) ||
        edg1->dfa_upper+1 != ((dfaEdge)rst(edgs1))->dfa_lower)
      return False;
    edgs1 = rst(edgs1); edg1 = fst(dfaEdge,edgs1);
    goto Loop2;
  }
  else
  {
    if (empty(rst(edgs2)) ||
        edg2->dfa_upper+1 != ((dfaEdge)rst(edgs2))->dfa_lower)
      return False;
    edgs2 = rst(edgs2); edg2 = fst(dfaEdge,edgs2);
    goto Loop2;
  }
}

static void minimizeGraph(RegSet_T g)
/* reduce graph g */
{ List(faNode) nods, nods1, nods2, *nodsp; int i;
  /* initialize equivalence */
  for (nods1 = RegSet_IMP(g)->Nodes; !empty(nods1); nods1 = rst(nods1))
  { faNode nod1 = fst(faNode,nods1), nod2;
    for (nods2 = RegSet_IMP(g)->Nodes; !empty(nods2); nods2 = rst(nods2))
    { nod2 = fst(faNode,nods2); if (nod1->term == nod2->term) break; }
    nod2 = fst(faNode,nods2);
    nod1->prevEquiv = -1; nod1->currEquiv = nod2->id;
  }
  while (!sameEquiv(RegSet_IMP(g)->Nodes))
  { /* next equivalence */
    for (nods1 = RegSet_IMP(g)->Nodes; !empty(nods1); nods1 = rst(nods1))
    { faNode nod1 = fst(faNode,nods1), nod2;
      for (nods2 = RegSet_IMP(g)->Nodes; !empty(nods2); nods2 = rst(nods2))
      { nod2 = fst(faNode,nods2);
        if (nod1->prevEquiv == nod2->prevEquiv &&
            sameEquivClass(nod1->Edges, nod2->Edges))
          break;
      }
      nod2 = fst(faNode,nods2);
      nod1->currEquiv = nod2->id;
    }
  }
  /* patch the edges */
  for (nods = RegSet_IMP(g)->Nodes; !empty(nods); nods = rst(nods))
  { faNode nod = fst(faNode,nods); List(dfaEdge) edges;
    for (edges = nod->Edges; !empty(edges); edges = rst(edges))
    { dfaEdge edge = fst(dfaEdge,edges);
      edge->dfa_toNode = findNode(g,edge->dfa_toNode->currEquiv);
    }
    nod->Edges = combineRanges(nod->Edges);
  }
  /* drop all equivalents beside first */
  for (i = 0, nodsp = &RegSet_IMP(g)->Nodes; !empty(*nodsp); )
  { faNode nod = fst(faNode,*nodsp);
    if (nod->currEquiv != nod->id)
    {
      List(faNode) here = *nodsp; *nodsp = rst(*nodsp);
      FreeMem(here); freeDfaNode(nod);
    }
    else
    { nod->id = i; i += 1; nodsp = rst_ref(*nodsp); }
  }
}

static bool hasTerminal(List(faNode) x, RegSet_T a)
/* whether a terminal state of 'a' is in source list 'x' */
{
  for (; !empty(x); x = rst(x))
  { faNode nod = fst(faNode,x);
    if (nod->Belongs == RegSet_IMP(a) && nod->term > 0)
      return True;
  }
  return False;
}

/* -- graph operations -- */

RegSet_T RegSet_Copy(RegSet_T a)
/* copies regular set 'a' */
{ RegSet_T res; List(faNode) lst;
  res = RegSet_Merge( cons(a,NULL), NULL,NULL );
  for (lst = RegSet_IMP(res)->Nodes; !empty(lst); lst = rst(lst))
  { faNode nod = fst(faNode,lst);
    nod->term = hasTerminal(nod->Source,a);
    freeList(nod->Source, freeNothing); nod->Source = NULL;
  }
  return res;
}

RegSet_T RegSet_Union(RegSet_T a, RegSet_T b)
/* union a | b */
{ RegSet_T res; List(faNode) lst;
  if (a == b) return RegSet_Copy(a);
  res = RegSet_Merge( cons(a,cons(b, NULL)), NULL,NULL );
  for (lst = RegSet_IMP(res)->Nodes; !empty(lst); lst = rst(lst))
  { faNode nod = fst(faNode,lst);
    nod->term = hasTerminal(nod->Source,a) || hasTerminal(nod->Source,b);
    freeList(nod->Source, freeNothing); nod->Source = NULL;
  }
  reduceGraph(res); minimizeGraph(res);
  return res;
}

RegSet_T RegSet_Intersection(RegSet_T a, RegSet_T b)
/* intersection a ^ b */
{ RegSet_T res; List(faNode) lst;
  if (a == b) return RegSet_Copy(a);
  res = RegSet_Merge( cons(a,cons(b, NULL)), NULL,NULL );
  for (lst = RegSet_IMP(res)->Nodes; !empty(lst); lst = rst(lst))
  { faNode nod = fst(faNode,lst);
    nod->term = hasTerminal(nod->Source,a) && hasTerminal(nod->Source,b);
    freeList(nod->Source, freeNothing); nod->Source = NULL;
  }
  reduceGraph(res); minimizeGraph(res);
  return res;
}

RegSet_T RegSet_Difference(RegSet_T a, RegSet_T b)
/* difference a - b */
{ RegSet_T res; List(faNode) lst;
  if (a == b) return RegSet_Empty();
  res = RegSet_Merge( cons(a,cons(b, NULL)), NULL,NULL );
  for (lst = RegSet_IMP(res)->Nodes; !empty(lst); lst = rst(lst))
  { faNode nod = fst(faNode,lst);
    nod->term = hasTerminal(nod->Source,a) && !hasTerminal(nod->Source,b);
    freeList(nod->Source, freeNothing); nod->Source = NULL;
  }
  reduceGraph(res); minimizeGraph(res);
  return res;
}

RegSet_T RegSet_Concat(RegSet_T a, RegSet_T b)
/* concatenation a b */
{ RegSet_T res,c; List(faNode) lst;
  c = (a == b) ? RegSet_Copy(a) : b;
  res = RegSet_Merge( cons(a,NULL), a,c );
  for (lst = RegSet_IMP(res)->Nodes; !empty(lst); lst = rst(lst))
  { faNode nod = fst(faNode,lst);
    nod->term = hasTerminal(nod->Source,b);
    freeList(nod->Source, freeNothing); nod->Source = NULL;
  }
  if (a==b) RegSet_Free(c);
  reduceGraph(res);
  minimizeGraph(res);
  return res;
}

RegSet_T RegSet_Star(RegSet_T a)
/* iteration { a } */
{ RegSet_T res; List(faNode) lst;
  res = RegSet_Merge( cons(a,NULL), a,a );
  for (lst = RegSet_IMP(res)->Nodes; !empty(lst); lst = rst(lst))
  { faNode nod = fst(faNode,lst);
    nod->term = hasTerminal(nod->Source,a) ||
                fst(faNode,nod->Source) == fst(faNode,RegSet_IMP(a)->Nodes);
    freeList(nod->Source, freeNothing); nod->Source = NULL;
  }
  reduceGraph(res); minimizeGraph(res);
  return res;
}

/* -- combinations -- */

RegSet_T RegSet_CsetN(wc_string s,int len)
/* character set '...'[0:len) */
{
  if (len > 0)
  { RegSet_T a = RegSet_Char((wc_char)(0xffffffffUL & ((unsigned long)s[0])));
    RegSet_T b = RegSet_CsetN(s+1,len-1);
    RegSet_T c = RegSet_Union(a, b);
    RegSet_Free(a); RegSet_Free(b);
    return c;
  }
  else
    return RegSet_Empty();
}

RegSet_T RegSet_Cset(wc_string s)
/* character set '...' */
{
  return RegSet_CsetN(s,WCStrLen(s));
}

RegSet_T RegSet_StringN(wc_string s,int len)
/* character sequence / string "..."[0:len) */
{
  if (len > 0)
  { RegSet_T a = RegSet_Char((wc_char)(0xffffffffUL & ((unsigned long)s[0])));
    RegSet_T b = RegSet_StringN(s+1,len-1);
    RegSet_T c = RegSet_Concat(a, b);
    RegSet_Free(a); RegSet_Free(b);
    return c;
  }
  else
    return RegSet_Epsilon();
}

RegSet_T RegSet_String(wc_string s)
/* character sequence / string "..." */
{
  return RegSet_StringN(s,WCStrLen(s));
}

RegSet_T RegSet_Option(RegSet_T a)
/* option [ a ] */
{ RegSet_T b = RegSet_Epsilon();
  RegSet_T c = RegSet_Union(a,b);
  RegSet_Free(b);
  return c;
}

RegSet_T RegSet_Plus(RegSet_T a)
/* iteration a + */
{ RegSet_T b = RegSet_Star(a);
  RegSet_T c = RegSet_Concat(a,b);
  RegSet_Free(b);
  return c;
}

RegSet_T RegSet_Plus_ntimes(RegSet_T a, int n)
/* iteration { a } n-times, n >= 0 */
{ RegSet_T res = RegSet_Epsilon();
  int i;
  for( i=0; i < n; ++i )
  { RegSet_T c = RegSet_Concat(res,a);
    RegSet_Free(res);
    res = c;
  }
  return res;
}

RegSet_T RegSet_Plus_range(RegSet_T a, int lwr, int upr)
/* iteration { a } lwr-times .. upr-times, lwr >= 0, upr >= 0 */
{ RegSet_T res = RegSet_Plus_ntimes(a,lwr);
  int i;
  for( i=lwr+1; i <= upr; ++i )
  { RegSet_T b = RegSet_Option(a);
    RegSet_T c = RegSet_Concat(res,b);
    RegSet_Free(b);
    RegSet_Free(res);
    res = c;
  }
  return res;
}

bool RegSet_isChar(RegSet_T a)
/* a = 'x' ? */
{ faNode s0 = fst(faNode,RegSet_IMP(a)->Nodes);
  bool res  =  !empty(rst(RegSet_IMP(a)->Nodes))
            &&  empty(rst(rst(RegSet_IMP(a)->Nodes)))
            && !empty(s0->Edges)     && empty(rst(s0->Edges));
  dfaEdge e = res ? fst(dfaEdge,s0->Edges) : NULL;
  return res && e->dfa_lower == e->dfa_upper;
}

wc_char RegSet_charVal(RegSet_T a)
/* x; assertion: a = 'x' */
{ wc_char res;
  bug0( RegSet_isChar(a), "single character set requiered" );
  res = fst(dfaEdge,fst(faNode,RegSet_IMP(a)->Nodes)->Edges)->dfa_lower;
  return res;
}

/*I----------------------- Scanner production ----------------------------- */

/* -- The Production Of The Scanner -- */

struct DefinedGraphs
{
  string  name;
  int     usage;
  RegSet_T value;
};

#define MAX_ENTRIES 100
ExternalType(ScnDfn_T) /* Scanner production handle */
{
  struct DefinedGraphs Table[MAX_ENTRIES];
  int       topEntry;
  string    Scn_name;
  scn_t     dyckpat[MAX_ENTRIES];
  bool      ConflictFlag;
  void (*prMsg)(c_string msg);
};

static ConcreteImp(ScnDfn_T) CurScnDfn; /* current scanner production */
static bool                  Scn_defining = False;


static void Scn_dfnBegin_aux(ScnDfn_T scndfn, string name, c_bool* defining)
{
  bug0(!(*defining),"already defining a scanner");
  scndfn->Scn_name   = StrCopy(name);
  *defining          = C_True;
  scndfn->prMsg      = (void (*)(c_string msg))NULL;
  scndfn->topEntry   = 1;
  scndfn->dyckpat[0] = (scn_t)NULL;
  scndfn->Table[0].name  = SCN_TOK_Other;
  scndfn->Table[0].usage = 0;
  scndfn->Table[0].value = (RegSet_T)NULL;
/*
  scndfn->topEntry   = 2;
  scndfn->dyckpat[1] = (scn_t)NULL;
  scndfn->Table[1].name  = StrCopy("[empty]");
  scndfn->Table[1].usage = 0;
  scndfn->Table[1].value = RegSet_Epsilon();
*/
}

void Scn_dfnBegin(string name)
/* begins a scanner definition; 
   uses 'name' as identifier 
*/
{
  Scn_dfnBegin_aux(&CurScnDfn,name,&Scn_defining);
}

ScnDfn_T Scn_dfnBegin_reentrant(string name)
/* reentrant version of Scn_dfnBegin */
{ ScnDfn_T scndfn   = New(ScnDfn_T);
  c_bool   defining = C_False;
  Scn_dfnBegin_aux(scndfn,name,&defining);
  return scndfn;
}

void Scn_setMsgFun(void (*prMsg)(c_string msg))
/* defines 'prMsg' as default message function */
{
  CurScnDfn.prMsg = prMsg;
}

void Scn_setMsgFun_reentrant(ScnDfn_T curdfn, void (*prMsg)(c_string msg))
/* reentrant version of Scn_setMsgFun */
{
  BUG_NULL(curdfn);
  curdfn->prMsg = prMsg;
}

static void Scn_dfnToken_aux
            (
              ScnDfn_T scndfn,
              string name, byte tok_flags, RegSet_T value,
              c_bool defining
            )
{ int i;
  if (defining) {
    for (i = 1; i < scndfn->topEntry; i++)
      bug1(strcmp(scndfn->Table[i].name,name), "duplicate name \'%s\'", name);
    if (scndfn->topEntry < MAX_ENTRIES) {
      scndfn->Table[scndfn->topEntry].name  = StrCopy(name);
      scndfn->Table[scndfn->topEntry].usage = tok_flags;
      if( value != (RegSet_T)NULL )
        scndfn->Table[scndfn->topEntry].value = RegSet_Copy(value);
      else
        scndfn->Table[scndfn->topEntry].value = (RegSet_T)NULL;
      scndfn->dyckpat[scndfn->topEntry] = (scn_t)NULL;
      scndfn->topEntry += 1;
    } else {
      bug0(scndfn->topEntry < MAX_ENTRIES, "too many tokens defined");
    }
  } else {
    bug0(defining,"missing Scn_dfnBegin");
  }
}

void Scn_dfnToken(string name, byte tok_flags, RegSet_T value)
/* adds a new token to the scanner under production 
   'name' : identifier
   'flags': attributes ( see [scn_base] )
   'value': regular set 
*/
{
  Scn_dfnToken_aux(&CurScnDfn,name,tok_flags,value,Scn_defining);
}

void Scn_dfnToken_reentrant
     (
       ScnDfn_T curdfn, string name, byte tok_flags, RegSet_T value
     )
/* reentrant version of Scn_dfnToken */
{ 
  BUG_NULL(curdfn);
  Scn_dfnToken_aux(curdfn,name,tok_flags,value,C_True);
}

void Scn_dfnDyckToken
     (
       string name, byte tok_flags, 
       RegSet_T left, Scn_T dyck
     )
/* adds a new dyck token to the scanner under production;
   consumes 'dyck' 
   'name' : identifier
   'flags': attributes ( see [scn_base] )
   'left' : regular set for left paranthesis
   'dyck' : dyck scanner ( left, inner and right token )
*/
{ scn_t scn = Scn_IMP(dyck);
  Scn_dfnToken_aux(&CurScnDfn,name,tok_flags,left,Scn_defining);
  CurScnDfn.dyckpat[CurScnDfn.topEntry-1] = 
    /*( scn == (scn_t)NULL ) ? (scn_t)NULL :*/ scn;
}

void Scn_dfnDyckToken_reentrant
     (
       ScnDfn_T curdfn, string name, byte tok_flags,
       RegSet_T left, Scn_T dyck
     )
/* reentrant version of Scn_dfnToken */
{ scn_t scn = Scn_IMP(dyck);
  BUG_NULL(curdfn);
  Scn_dfnToken_aux(curdfn,name,tok_flags,left,C_True);
  curdfn->dyckpat[curdfn->topEntry-1] = 
    /*( scn == (scn_t)NULL ) ? (scn_t)NULL :*/ scn;
}

static void pConflicts(ScnDfn_T scndfn, List(faNode) nodes)
{
  if (length(nodes) > 1)
  { void (*prMsg)(c_string msg) = scndfn->prMsg;
    if( prMsg == (void (*)(c_string msg))NULL )
      prMsg = prMsg_stderr;
    scndfn->ConflictFlag = True;
    (*prMsg)("Conflict between ");
    for (;!empty(nodes); nodes = rst(nodes))
    { faNode node = fst(faNode,nodes);
      (*prMsg)("'");
      (*prMsg)(scndfn->Table[node->Belongs->id].name);
      (*prMsg)("'");
      if (length(nodes) > 1)
      {
        if (length(nodes) == 2)
          (*prMsg)(" and ");
        else
          (*prMsg)(", ");
      }
    }
    (*prMsg)(".\n");
  }
}

static List(faNode) terminalSource(List(faNode) nodes)
/* removes all non-terminal states from the source of a node */
{
  if(empty(nodes))
    return nodes;
  else
  { List(faNode) r = terminalSource(rst(nodes));
    if( fst(faNode,nodes)->term )
    { *rst_ref(nodes) = r; return nodes; }
    else
    { FreeMem(nodes); return r; }
  }
}

static void terminalScanner(ScnDfn_T scndfn, RegSet_T graph)
/* removes all non-terminal states from the sources of a graph */
{ List(faNode) nodes = RegSet_IMP(graph)->Nodes;
  for (; !empty(nodes); nodes = rst(nodes))
  { faNode node = fst(faNode,nodes);
    node->Source = terminalSource(node->Source);
    node->term = empty(node->Source)
                 ? 0
                 : fst(faNode,node->Source)->Belongs->id;
    pConflicts(scndfn,node->Source);
  }
}

/* new version of scanner table production */

static Scn_T ScnTable (ScnDfn_T scndfn, RegSet_T scanner)
{ int i, j, edgcnt, dyckcnt, states = length(RegSet_IMP(scanner)->Nodes);
  long    *StaEdg;
  short   *StaFin;
  wc_char *EdgeC;
  long    *EdgeS;
  List(faNode) nodes; List(dfaEdge) edges;
  wc_char clow;
  scn_t   res;
  /* count edges */
  edgcnt = 0;
  for (nodes = RegSet_IMP(scanner)->Nodes; !empty(nodes); nodes = rst(nodes))
  { faNode node = fst(faNode,nodes);
    clow = 0;
    for (edges = node->Edges; !empty(edges); edges = rst(edges))
    { dfaEdge edge = fst(dfaEdge,edges);
      edgcnt += (clow < edge->dfa_lower)+1;
      clow = edge->dfa_upper+1;
    }
    if (clow < SCN_CHAR_SET_SIZE) edgcnt += 1;
  }
  /*
  assert0
  (
    (((long)edgcnt) & 0xFFFF0000L) == 0,
    "Too many edges. Reduce token complexity"
  );
  */
  /* count dyck tokens */
  dyckcnt = 0;
  for( i=0; i < scndfn->topEntry; ++i )
    if( scndfn->dyckpat[i] != (scn_t)NULL )
      ++dyckcnt;
  /* make edges and states */
  StaEdg = (long*   )NewMem( (states+1) * sizeof(long   ) );
  StaFin = (short*  )NewMem( states     * sizeof(short  ) );
  EdgeC  = (wc_char*)NewMem( edgcnt     * sizeof(wc_char) );
  EdgeS  = (long*   )NewMem( edgcnt     * sizeof(long   ) );
  edgcnt = 0;
  for (nodes = RegSet_IMP(scanner)->Nodes; !empty(nodes); nodes = rst(nodes))
  { faNode node = fst(faNode,nodes);
    StaEdg[node->id] = edgcnt;
    StaFin[node->id] = node->term;
    clow = 0;
    for (edges = node->Edges; !empty(edges); edges = rst(edges))
    { dfaEdge edge = fst(dfaEdge,edges);
      if (clow < edge->dfa_lower)
      {
        EdgeC[edgcnt] = clow; EdgeS[edgcnt] = 0; edgcnt += 1;
      }
      EdgeC[edgcnt] = edge->dfa_lower;
      EdgeS[edgcnt] = edge->dfa_toNode->id+1;
      clow = edge->dfa_upper+1;
      edgcnt += 1;
    }
    if (clow < SCN_CHAR_SET_SIZE)
    {
      EdgeC[edgcnt] = clow; EdgeS[edgcnt] = 0; edgcnt += 1;
    }
    for (i = 0; i < (edgcnt-StaEdg[node->id])/2; i ++)
    { wc_char t;
      t = EdgeC[StaEdg[node->id]+i];
          EdgeC[StaEdg[node->id]+i] = EdgeC[edgcnt-1-i];
                                      EdgeC[edgcnt-1-i] = t;
      t = (wc_char)EdgeS[StaEdg[node->id]+i];
          EdgeS[StaEdg[node->id]+i] = EdgeS[edgcnt-1-i];
                                      EdgeS[edgcnt-1-i] = t;
    }
  }
  StaEdg[states] = edgcnt;
  /* make scanner structure */
  res = New(scn_t);
  res->Name    = scndfn->Scn_name;
  res->States  = states;
  res->Tokens  = scndfn->topEntry;
  res->StaEdg  = StaEdg;
  res->StaFin  = StaFin;
  res->EdgeC   = EdgeC;
  res->EdgeS   = EdgeS;
  res->TokId   = (string*)NewMem((scndfn->topEntry) * sizeof(string));
  res->Flags   = (byte  *)NewMem((scndfn->topEntry) * sizeof(byte));
  res->Groups  = 0;
  res->GrpScn  = (scn_t*)NULL;
  res->Switch  = (short*)NULL;
  res->dyckcnt = dyckcnt;
  res->dyckidx = dyckcnt > 0
                 ? (short*)NewMem(dyckcnt * sizeof(short)) 
                 : (short*)NULL;
  res->dyckpat = dyckcnt > 0 
                 ? (scn_t*)NewMem(dyckcnt * sizeof(scn_t)) 
                 : (scn_t*)NULL;
  for (i = 0; i < scndfn->topEntry; i++)
    res->TokId[i] = StrCopy(scndfn->Table[i].name);
  for (i = 0; i < scndfn->topEntry; i++)
    res->Flags[i] = scndfn->Table[i].usage;
  for (i=0, j=0; i < scndfn->topEntry && j < dyckcnt; i++)
  {
    if( scndfn->dyckpat[i] != (scn_t)NULL )
    {
      res->dyckpat[j] = scndfn->dyckpat[i];
      res->dyckidx[j] = (short)i;
      j++;
    }
  }
  /* free temporaries */
  RegSet_Free(scanner);
  /* done */
  return Scn_ADT(res);
}

/* -- graph printer -- */

static void pGraphList
     (
       List(Abs_T) x, int Indent, 
       void (*pMember)(Abs_T x, StdCPtr any), StdCPtr any
     )
{ void (*prMsg)(c_string msg) = ((ScnDfn_T)any)->prMsg;
  char buf[STD_BUFFLEN+1]; int i;
  if( prMsg == (void (*)(c_string msg))NULL )
    prMsg = prMsg_stdout;
  (*prMsg)("[");
  if (Indent >= 0 && !empty(x)) 
  {
    sprintf(buf,"\n%*s",Indent,"");
    (*prMsg)(buf);
  }
  for (i = 0; !empty(x); x = rst(x), i +=1 )
  {
    (*pMember)(fst(Abs_T,x),any);
    if (!empty(rst(x)))
      if (Indent >= 0 || (i+1) % 4 == 0)
      { (*prMsg)(","); 
        sprintf(buf,"\n%*s",(Indent>=0?Indent:7),"");
        (*prMsg)(buf);
      }
      else
        (*prMsg)(", ");
      else
        if (Indent >= 0)
        {
          sprintf(buf,"\n%*s",Indent,"");
          (*prMsg)(buf);
        }
  }
  (*prMsg)("]");
}

static void pSource(faNode x, ScnDfn_T scndfn)
{ void (*prMsg)(c_string msg) = scndfn->prMsg;
  char buf[STD_BUFFLEN+1];
  if( prMsg == (void (*)(c_string msg))NULL )
    prMsg = prMsg_stdout;
  sprintf(buf,"%d(", x->Belongs->id);
  (*prMsg)(buf);
  (*prMsg)(scndfn->Table[x->Belongs->id].name);
  (*prMsg)(")");
}

static void pChar(wc_char wc, ScnDfn_T scndfn)
{ byte c = (byte)wc;
  void (*prMsg)(c_string msg) = scndfn->prMsg;
  char buf[STD_BUFFLEN+1];
  if( prMsg == (void (*)(c_string msg))NULL )
    prMsg = prMsg_stdout;
  if( ((wc_char)c) == wc )
    switch (c)
    {
      case ' '  : sprintf(buf,"\\_"); break;
      case '\f' : sprintf(buf,"\\p"); break;
      case '\n' : sprintf(buf,"\\n"); break;
      case '\r' : sprintf(buf,"\\r"); break;
      case '\\' :
      case '\'' :
      case '\"' :
      case '`'  : sprintf(buf,"\\%c",c); break;
      //default : if (32 < c && c < 127)
      default : if ( isascii(c) && isprint(c) )
                  sprintf(buf,"%c",c);
                else
                  sprintf(buf,"%02x",c);
    }
  else
    sprintf(buf,"%08lx",(long unsigned int)wc);
  (*prMsg)(buf);
}

static void pEdge(dfaEdge x, ScnDfn_T scndfn)
{ void (*prMsg)(c_string msg) = scndfn->prMsg;
  char buf[STD_BUFFLEN+1];
  if( prMsg == (void (*)(c_string msg))NULL )
    prMsg = prMsg_stdout;
  (*prMsg)("(");
  if (x->dfa_lower != x->dfa_upper)
  { pChar(x->dfa_lower,scndfn); (*prMsg)(" - "); }
  else
    (*prMsg)("     ");
  pChar(x->dfa_upper,scndfn);
  sprintf(buf," : %2d)", x->dfa_toNode->id );
  (*prMsg)(buf);
}

static void pNfaEdge(nfaEdge x, ScnDfn_T scndfn)
{ byte cl = (byte)x->nfa_lower,
       cu = (byte)x->nfa_upper;
  void (*prMsg)(c_string msg) = scndfn->prMsg;
  char buf[STD_BUFFLEN+1];
  if( prMsg == (void (*)(c_string msg))NULL )
    prMsg = prMsg_stdout;
  if( ((wc_char)cl) == x->nfa_lower && ((wc_char)cu) == x->nfa_upper )
  {
    (*prMsg)("({\'");
    pChar(x->nfa_lower,scndfn);
    (*prMsg)("\'..\'");
    pChar(x->nfa_upper,scndfn);
    (*prMsg)("\'}");
  }
  else
  {
    sprintf
    (
      buf,"({%08lx..%08lx}, ", 
      (long unsigned int)x->nfa_lower, (long unsigned int)x->nfa_upper
    );
    (*prMsg)(buf);
  }
  pGraphList(x->nfa_toNodes,-1,(void (*)(Abs_T x,StdCPtr any))pSource,scndfn);
  (*prMsg)(")");
}

static void pNfaEdges(List(nfaEdge) x, ScnDfn_T scndfn)
{
  pGraphList(x,-1,(void (*)(Abs_T x,StdCPtr any))pNfaEdge,scndfn);
}

static void pNode(faNode x, ScnDfn_T scndfn)
{ void (*prMsg)(c_string msg) = scndfn->prMsg;
  char buf[STD_BUFFLEN+1];
  if( prMsg == (void (*)(c_string msg))NULL )
    prMsg = prMsg_stdout;
  sprintf(buf,"%2d %2d ", x->id, x->term);
  (*prMsg)(buf);
  sprintf(buf,"(%2d %2d) ", x->flag1, x->flag2);
  (*prMsg)(buf);
  pGraphList(x->Source,-1,(void (*)(Abs_T x,StdCPtr any))pSource,scndfn);
  (*prMsg)("\n      ");
  pGraphList(x->Edges,-1,(void (*)(Abs_T x,StdCPtr any))pEdge,scndfn);
}

void RegSet_Print(RegSet_T x)
/* prints regular set to stdout; for debugging */
{ void (*prMsg)(c_string msg) = CurScnDfn.prMsg;
  char buf[STD_BUFFLEN+1];
  if( prMsg == (void (*)(c_string msg))NULL )
    prMsg = prMsg_stdout;
  sprintf(buf,"RegSet_T %d =\n",RegSet_IMP(x)->id);
  (*prMsg)(buf);
  pGraphList
  (
    RegSet_IMP(x)->Nodes,0,(void (*)(Abs_T x,StdCPtr any))pNode,&CurScnDfn
  );
  (*prMsg)("\n");
}

void RegSet_Print_reentrant(ScnDfn_T curdfn, RegSet_T x)
/* reentrant version of RegSet_Print */
{ void (*prMsg)(c_string msg);
  char buf[STD_BUFFLEN+1];
  BUG_NULL(curdfn);
  prMsg = curdfn->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL )
    prMsg = prMsg_stdout;
  sprintf(buf,"RegSet_T %d =\n",RegSet_IMP(x)->id);
  (*prMsg)(buf);
  pGraphList(RegSet_IMP(x)->Nodes,0,(void (*)(Abs_T x,StdCPtr any))pNode,curdfn);
  (*prMsg)("\n");
}

static Scn_T Scn_dfnEnd_aux
             (
               ScnDfn_T scndfn, c_bool diagnose, c_bool* defining
             )
{ int i; List(RegSet_Ts) graphs = NULL;
  RegSet_T scanner; Scn_T scn;
  bug0((*defining),"no definition");
  for (i = 1; i < scndfn->topEntry; i++)
  {
    if( scndfn->Table[i].value != (RegSet_T)NULL )
    {
      graphs = cons(scndfn->Table[i].value,graphs);
      fst(regset_t,graphs)->id = i;
    }
  }
  scndfn->ConflictFlag = False;
  scanner = RegSet_Merge(graphs, NULL,NULL);
  terminalScanner(scndfn,scanner);
  bug0(!scndfn->ConflictFlag,"aborted due to conflicts");
  if (diagnose) RegSet_Print_reentrant(scndfn,scanner);
  scn = ScnTable(scndfn,scanner);
  for (i = 1; i < scndfn->topEntry; i++)
  { 
    FreeMem(scndfn->Table[i].name); 
    if( scndfn->Table[i].value != (RegSet_T)NULL )
      RegSet_Free(scndfn->Table[i].value); 
  }
  *defining = C_False;
  return scn;
}

Scn_T Scn_dfnEnd(bool diagnose)
/* completes and creates scanner definition
   diagnose --> prints scanner definiton
*/
{ 
  return Scn_dfnEnd_aux(&CurScnDfn,diagnose,&Scn_defining);
}

Scn_T Scn_dfnEnd_reentrant(ScnDfn_T curdfn, bool diagnose)
/* reentrant version of Scn_dfnEnd;
   consumes 'curdfn'
*/
{ c_bool defining = C_True; 
  Scn_T  scn      = (Scn_T)NULL;
  BUG_NULL(curdfn);
  scn = Scn_dfnEnd_aux(curdfn,diagnose,&defining);
  FreeMem(curdfn);
  return scn;
}

/*I----------------------- Scanner group production ------------------------ */

#define MAX_GROUP_ENTRIES 50

Scn_T ScnGrp_dfnBegin(c_string name)
/* begins a scanner group definition; 
   uses 'name' as identifier 
*/
{ scn_t res;
  res = New(scn_t);
  res->Name    = StrCopy(name);
  res->States  = 0;
  res->Tokens  = 0;
  res->StaEdg  = (long*     )NULL;
  res->StaFin  = (short*    )NULL;
  res->EdgeC   = (wc_char*  )NULL;
  res->EdgeS   = (long*     )NULL;
  res->TokId   = (string*   )NULL;
  res->Flags   = (byte*     )NULL;
  res->Groups  = 0;
  res->GrpScn  = (scn_t*    )NewMem(sizeof(scn_t)*MAX_GROUP_ENTRIES);
  res->Switch  = (short*    )NULL;
  res->dyckcnt = 0;
  res->dyckidx = (short*    )NULL;
  res->dyckpat = (scn_t*    )NULL;
  return res;
}

void ScnGrp_dfnScanner(Scn_T group, Scn_T scanner)
/* adds 'scanner' to 'group'; consumes 'scanner' */
{ scn_t g = Scn_IMP(group), s = Scn_IMP(scanner);
  int i;
  BUG_NULL(g); BUG_NULL(s);
  bug1(s->Groups == 0,"scanner group '%s' not allowed",s->Name);
  bug1(s->Switch == (short*)NULL,"scanner '%s' already in group",s->Name);
  bug0(g->Groups < MAX_GROUP_ENTRIES,"too many scanner defined");
  for( i=0; i < g->Groups; ++i )
  {
    bug1
    ( 
      strcmp(g->GrpScn[i]->Name,s->Name), 
      "scanner with name '%s' already defined",s->Name 
    );
  }
  g->GrpScn[g->Groups] = s;
  g->Groups += 1;
  s->Switch = (short*)NewMem(sizeof(short)*s->Tokens);
  for( i=0; i < s->Tokens; ++i ) s->Switch[i] = -1;
}

void ScnGrp_dfnSwitch(Scn_T group, c_string from, c_string token, c_string to)
/* adds context switch information for 'group';
   'token' in scanner 'from' switches to scanner 'to'
*/
{ scn_t g = Scn_IMP(group);
  int sfidx = -1, stidx = -1, i;
  BUG_NULL(g); 
  for( i=0; i < g->Groups; ++i )
  {
    if( !strcmp(g->GrpScn[i]->Name,from) )
      sfidx = i;
    if( !strcmp(g->GrpScn[i]->Name,to) )
      stidx = i;
    if( sfidx >= 0 && stidx >= 0 ) break;
  }
  assert0( sfidx >= 0 && stidx >= 0, "scanner not found" );
  for( i=0; i < g->GrpScn[sfidx]->Tokens; ++i )
  {
    if( !strcmp(g->GrpScn[sfidx]->TokId[i],token) )
    {
      g->GrpScn[sfidx]->Switch[i] = stidx; break;
    }
  }
  assert0( i < g->GrpScn[sfidx]->Tokens, "token not found" );
}

int ScnGrp_dfnEnd(Scn_T group)
/* completes definition for 'group'; 
   returns number of unreachable scanners 
*/
{ scn_t g = Scn_IMP(group);
  short* glink; int res = 0, i, j;
  BUG_NULL(g); 
  glink = (short*)NewMem(sizeof(short)*g->Groups);
  for( i=0; i < g->Groups; ++i )
  {
    glink[i] = ( i == 0 );
  }
  for( i=0; i < g->Groups; ++i )
  {
    for( j=0; j < g->GrpScn[i]->Tokens; ++j )
    {
      if( g->GrpScn[i]->Switch[j] >= 0 )
        glink[g->GrpScn[i]->Switch[j]] = 1;
    }
  }
  for( i=0; i < g->Groups; ++i )
  {
    if( glink[i] == 0 ) ++res;
  }
  FreeMem(glink);
  return res;
}
