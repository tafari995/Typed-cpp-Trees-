#include "SetHelpers.h"
#include "Node.h"
#include <iostream>
#include <unordered_set>
using namespace std;

template <class W>
using PtrSet = std::unordered_set<Node<W>*, NodePtrHash<W>, NodePtrEqual<W>>;

template <class W>
bool is_disjoint(PtrSet<W> set1, PtrSet<W> set2)
{
  for(const auto& y : set2){
    if(set1.count(y)==1){
      return false;
    }
  }
  return true;
};


/* may be broken but ignore for now */
template <class W>
unordered_set<W> union_rep1(unordered_set<W> set1, unordered_set<W> set2)
{
  set1.insert(set2.begin(),set2.end());
  return set1;
}