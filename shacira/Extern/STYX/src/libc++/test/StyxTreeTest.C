#include <stdio.h>
#include <string>
#include <iostream>
#include "StyxTree.h"

using namespace styx;

typedef TStyxTree<string> T_StringTree;
typedef TStyxTreeIter<T_StringTree,TI_TYPE_DF> T_DFIter;

#define NODES  7
static string nodes[] =
{
  string("0"),
  string("1"),
  string("1.1"),
  string("1.2"),
  string("1.3"),
  string("1.1.1"),
  string("1.1.2"),
  string("1.3.1"),
  string("2")
};

void prnode1(T_StringTree& t, short o, size_t l)
{
  if( o == TI_STATE_PRAE )
  {
    printf("\n%*s",(int)(2*l),"");
    cout << t.getNode().c_str();
  }
  if( l == 0 && o == TI_STATE_POST )
    printf("\n");
}

struct T_prnode : public T_StringTree::Function
{
  void operator() (T_StringTree& t, short o, size_t l)
  {
    prnode1(t,o,l);
  }
} prnode2;

bool test_pred1(T_StringTree& t)
{
  return t.getNode() == "1.3";
}

struct T_test_pred : public T_StringTree::Predicate
{
  bool operator() (T_StringTree& t)
  {
    return t.getNode() == "1.1.2";
  }
} test_pred2;

int main(int argc, char* argv[])
{ //T_StringTree dmy; 
  T_StringTree* t = 0, *r = 0, *q = 0;
  vector<T_StringTree* > l;
  t = T_StringTree::create(nodes[5]);
  l.push_back(t);
  t = T_StringTree::create(nodes[6]);
  l.push_back(t);
  r = T_StringTree::create(nodes[2],l);
  l.clear();

  t = T_StringTree::create(nodes[7]);
  l.push_back(t);
  t = T_StringTree::create(nodes[4],l);
  l.clear();

  l.push_back(r);
  r = t;
  t = T_StringTree::create(nodes[3]);
  l.push_back(t);
  l.push_back(r);
  t = T_StringTree::create(nodes[1],l);
  l.clear();

  l.push_back(t);
  t = T_StringTree::create(nodes[8]);
  l.push_back(t);
  r = T_StringTree::create(nodes[0],l);
  l.clear();

  cout << "Visitor1:\n";
  r->visit(prnode1);
  cout << "Visitor2:\n";
  r->visit(prnode2);
  q = T_StringTree::create(nodes[0]);
  cout << "Visitor3:\n";
  q->visit(prnode2);
  *q = *r;
  cout << "PARTS-SIZE=" << q->getParts().size() << "\n";
  cout << "Visitor4:\n";
  q->visit(prnode2);
  delete q;

  cout << "Find1:\n";
  t = r->find(test_pred1);
  if( t ) cout << t->getNode().c_str() << "\n";

  cout << "Find2:\n";
  t = r->find(test_pred2);
  if( t ) cout << t->getNode().c_str() << "\n";

  cout << "DF-Iterator:\n";
  T_StringTree::DF_Iter dfpos = r->dfbegin();
  while( ! dfpos.end() )
  {
    if( dfpos.getState() == TI_STATE_PRAE )
    {
      t = dfpos.getTerm();
      if( t ) cout << "PRAE: " << t->getNode().c_str() << "\n";
    }
    else
    if( dfpos.getState() == TI_STATE_POST )
    {
      t = dfpos.getTerm();
      if( t ) cout << "POST: " << t->getNode().c_str() << "\n";
    }
    ++dfpos;
  }

  cout << "BF-Iterator:\n";
  T_StringTree::BF_Iter bfpos = r->bfbegin();
  while( ! bfpos.end() )
  {
    if( bfpos.getState() == TI_STATE_PRAE )
    {
      t = bfpos.getTerm();
      if( t ) cout << "PRAE: " << t->getNode().c_str() << "\n";
    }
    else
    if( bfpos.getState() == TI_STATE_POST )
    {
      t = bfpos.getTerm();
      if( t ) cout << "POST: " << t->getNode().c_str() << "\n";
    }
    ++bfpos;
  }

  delete r;
  return 0;
}
