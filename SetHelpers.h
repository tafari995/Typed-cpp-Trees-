#ifndef SETHELPERS_H
#define SETHELPERS_H
#include "Node.h"
#include <iostream>
#include <unordered_set>
using namespace std;

template <class W>
using PtrSet = std::unordered_set<Node<W>*, NodePtrHash<W>, NodePtrEqual<W>>;

template <class W>
bool is_disjoint(PtrSet<W> set1, PtrSet<W> set2);

template <class W>
unordered_set<W> union_rep1(unordered_set<W> set1, unordered_set<W> set2);

#endif