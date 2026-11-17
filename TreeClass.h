#ifndef TREECLASS_H
#define TREECLASS_H
#include "Node.h"
#include "SetHelpers.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;


template <class T>
class TreeClass
{
  private:
    std::unordered_map< Node<T>*, PtrSet<T>, NodePtrHash<T> > tree;
    PtrSet<T> family;  
    Node<T>* root;
  public:
    TreeClass(Node<T>* n1);
    PtrSet<T>& get_full_family();
    PtrSet<T>& get_ch(Node<T>* n);
    void insert_parent(Node<T>* new_parent);
    void insert_child(Node<T>* parent, Node<T>* baby);
    void abort_child(Node<T>* parent, Node<T>* baby);
    void abort_parent(Node<T>* parent);
    bool is_tree_still();
    int tree_search(Node<T>* lost_node);
};



template <class T>
TreeClass<T>::TreeClass(Node<T>* n1)
{
  root = n1;
  family = { root };
  tree[root] = {}; /* by definition, trees are nonempty and have one parent! */
};


template <class T>
PtrSet<T>& TreeClass<T>::get_full_family()
{
  for(const auto& kv : tree){
    const PtrSet<T>& v = kv.second;
    family.insert(kv.first);
    family.insert(v.begin(),v.end());
  }
  return family;
};


template <class T>
PtrSet<T>& TreeClass<T>::get_ch(Node<T>* n)
{
  return tree[n];
};


template <class T>
void TreeClass<T>::insert_parent(Node<T>* new_parent)
{
  family.insert(new_parent);
  tree[new_parent] = {};
};


template <class T>
void TreeClass<T>::insert_child(Node<T>* parent, Node<T>* baby)
{
  family.insert(baby);
  PtrSet<T>& children = get_ch(parent);
  children.insert(baby);
};


template <class T>
void TreeClass<T>::abort_child(Node<T>* parent, Node<T>* baby)
{
  family.erase(baby);
  (tree[parent]).erase(baby);
};


template <class T>
void TreeClass<T>::abort_parent(Node<T>* parent)
{
  if( parent != root ){
    family.erase(parent);
    tree.erase(parent);
  }
  else {
    cout << "sorry, can't abort parent; she's the root!" << endl;
  } 
};


/* BROKEN; needs to be fixed so it doesn't use the nodebank */
template <class T>
bool TreeClass<T>::is_tree_still()
{
  bool is_tree = true;
  PtrSet<T>  nodes_accounted_for = { root };

  for(const auto& p : tree){
    for(const auto& q : tree){
      const Node<T>* p_k=p.first;
      const Node<T>* q_k=q.first;
      if( (p_k != q_k) && !is_disjoint(p.second,q.second) ){
        cout << "oh no, my child sets overlap!" << endl;
        is_tree = false;
      }
    }    
  }

  for(const auto& kv : tree){
    const PtrSet<T>& kids = kv.second;
    union_rep1(nodes_accounted_for, kids);
  }
  
  if(nodes_accounted_for != family){
    cout << "oh no, there are nodes in the family which are unaccounted for!" << endl;
    is_tree = false;
  }
  return is_tree;
}

template <class T>
int TreeClass<T>::tree_search(Node<T>* lost_node)
{
  PtrSet<T> current_depth = { root };
  int j = 0;
  while(j< family.size()){
    PtrSet<T> next_depth = {};
    if( current_depth.find(lost_node) != current_depth.end() ){
      cout << "We found the node we sought, with ( " << endl; 
      (*lost_node).node_print(); 
      cout << " )" << endl;
      return j;
    }
    else{
      for(const auto& n : current_depth){
        union_rep1(next_depth, tree[n]);
      } 
    }
    current_depth = next_depth;
    j+=1;
  }
  return -1;
}

#endif // TREECLASS_H

/*  Remember, if you instantiate a variable
of type variant, and the value happens to be an int (for example), 
the type of that variable is STILL 'variant' with the given options.
If you check whether its type is int, the answer is no!

*/