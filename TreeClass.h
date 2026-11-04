#ifndef TREECLASS_H
#define TREECLASS_H
#include "Node.h"
#include "SetHelpers.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

/*
template <class T>
using PtrSet = std::unordered_set<Node<T>*, NodePtrHash<T>, NodePtrEqual<T>>;
*/

template <class T>
class TreeClass
{
  private:
    std::unordered_map< Node<T>*, PtrSet<T>, NodePtrHash<T> > tree;
    std::unordered_set< Node<T>, NodeHash<T> > nodebank;
    Node<T>* root;
  public:
    TreeClass(Node<T> n1);
    PtrSet<T>& get_ch(Node<T>* n);
    void insert_parent(Node<T> new_parent);
    void insert_child(Node<T>* parent, Node<T> baby);
    void abort_child(Node<T>* parent, Node<T>* baby);
    void abort_parent(Node<T>* parent);
    bool is_tree_still();
};



template <class T>
TreeClass<T>::TreeClass(Node<T> n1)
{
  root = &n1;
  nodebank.insert(n1);
  tree[root] = {}; /* by definition, trees are nonempty and have one parent! */
};


template <class T>
void TreeClass<T>::insert_parent(Node<T> new_parent)
{
  nodebank.insert(new_parent);
  Node<T>* new_par_ptr = &new_parent;
  tree[new_par_ptr] = {};
};


template <class T>
PtrSet<T>& TreeClass<T>::get_ch(Node<T>* n)
{
  return tree[n];
};


template <class T>
void TreeClass<T>::insert_child(Node<T>* parent, Node<T> baby)
{
  if( &baby != root ){
    nodebank.insert(baby);
    Node<T>* baby_ptr = &baby;
    PtrSet<T>& children = get_ch(parent);
    children.insert(baby_ptr);
  }
};


template <class T>
void TreeClass<T>::abort_child(Node<T>* parent, Node<T>* baby)
{
  (tree[parent]).erase(baby);
  nodebank.erase( (*baby) );
};


template <class T>
void TreeClass<T>::abort_parent(Node<T>* parent)
{
  if( parent != root ){
    tree.erase(parent);
  }
  else {
    cout << "sorry, can't abort parent; she's the root!" << endl;
  } 
};


template <class T>
bool TreeClass<T>::is_tree_still()
{
  bool is_tree;
  std::unordered_set< Node<T>, NodeHash<T> > nodetotal = { *root };
  for(const auto& p : tree){
    for(const auto& q : tree){
      Node<T>* p_key=p.first;
      Node<T>* q_key=q.first;
      if( (p_key != q_key) && !is_disjoint(p.second,q.second) ){
        is_tree=false;
        return is_tree;
      }
    }
    for(const auto& e : p.second){
      nodetotal.insert(*e);
    }  
  }
  if(nodetotal != nodebank){
    is_tree=false;
    return is_tree;
  }
  is_tree = true;
  return is_tree;
}

#endif // TREECLASS_H

/*  Remember, if you instantiate a variable
of type variant, and the value happens to be an int (for example), 
the type of that variable is STILL 'variant' with the given options.
If you check whether its type is int, the answer is no!

*/