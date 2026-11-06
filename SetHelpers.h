#ifndef SETHELPERS_H
#define SETHELPERS_H
#include "Node.h"
#include <iostream>
#include <unordered_set>
using namespace std;

/* type aliases */

template <class W>
using PtrSet = std::unordered_set< Node<W>*, NodePtrHash<W>, NodePtrEqual<W> >;

template <class W>
using NodeSet = std::unordered_set< Node<W>, NodeHash<W> >;

/* function declarations for set helpers */

template <class W>
bool is_disjoint(PtrSet<W> set1, PtrSet<W> set2);

template <class W>
PtrSet<W>& union_rep1(PtrSet<W>& set1, PtrSet<W> set2);

template <class W>
NodeSet<W>& union_rep1(NodeSet<W>& set1, NodeSet<W> set2);

template <class W>
NodeSet<W> ptr_to_node(PtrSet<W> set1);

/* 
the definitions, following the declarations 
for template classes in header files 
*/

template <class W>
NodeSet<W> ptr_to_node(PtrSet<W> set1){
  NodeSet<W> node_set;
  for(const auto p : set1){
    cout << (*p).v() << endl;
    node_set.insert(*p);
  }
  return node_set;
};


template <class W>
bool is_disjoint(PtrSet<W> set1, PtrSet<W> set2)
{
  bool disjoint = true;
  for(const auto& y : set2){
    if(set1.count(y)==1){
      disjoint = false;
    }
  }
  for(const auto& x : set1){
    if(set2.count(x)==1){
      disjoint = false;
    }
  }
  return disjoint;
};


template <class W>
NodeSet<W>& union_rep1(NodeSet<W>& set1, NodeSet<W> set2)
{
  set1.insert(set2.begin(),set2.end());
  return set1;
};


template <class W>
PtrSet<W>& union_rep1(PtrSet<W>& set1, PtrSet<W> set2)
{
  set1.insert(set2.begin(),set2.end());
  return set1;
};

#endif