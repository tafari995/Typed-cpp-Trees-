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
    std::unordered_set< Node<T>, NodeHash<T> > nodebank;  // I think we want to rewrite the class without a nodebank
    Node<T>* root;
  public:
    TreeClass(Node<T>* n1);
    PtrSet<T>& get_ch(Node<T>* n);
    void insert_parent(Node<T>* new_parent);
    void insert_child(Node<T>* parent, Node<T>* baby);
    void abort_child(Node<T>* parent, Node<T>* baby);
    void abort_parent(Node<T>* parent);
    bool is_tree_still();
};



template <class T>
TreeClass<T>::TreeClass(Node<T>* n1)
{
  root = n1;
  tree[root] = {}; /* by definition, trees are nonempty and have one parent! */
};


template <class T>
void TreeClass<T>::insert_parent(Node<T>* new_parent)
{
  tree[new_parent] = {};
};


template <class T>
PtrSet<T>& TreeClass<T>::get_ch(Node<T>* n)
{
  return tree[n];
};


template <class T>
void TreeClass<T>::insert_child(Node<T>* parent, Node<T>* baby)
{
  PtrSet<T>& children = get_ch(parent);
  children.insert(baby);
};


template <class T>
void TreeClass<T>::abort_child(Node<T>* parent, Node<T>* baby)
{
  (tree[parent]).erase(baby);
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


/* BROKEN; needs to be fixed so it doesn't use the nodebank */
template <class T>
bool TreeClass<T>::is_tree_still()
{
  bool is_tree = true;
  std::unordered_set< Node<T>, NodeHash<T> > nodetotal = { *root };
  for(const auto& p : tree){
    for(const auto& q : tree){
      Node<T>* p_k = p.first;
      Node<T>* q_k = q.first;
      if( (p_k != q_k) && !is_disjoint(p.second,q.second) ){
        cout << "oh no, my child sets overlap!" << endl;
        is_tree = false;
      }
    }
      
  }
  for(const auto& kv : tree){
    PtrSet<T> kv2 = kv.second;
    cout << kv2.size() << endl;
    NodeSet<T> nfp = ptr_to_node(kv2);
    cout << nfp.size() << endl;
    cout << "individual nodetotal elements: ";
    for( auto n_i : nfp){
      n_i.node_print();
    }
    cout << endl;
    union_rep1(nodetotal, nfp);
  }

  // checking what the elements of both sets are by value, for debug 
  cout << "Nodebank Elements:" << endl;
  for( auto x : nodebank){
    x.node_print();
  }
  cout << "Nodetotal Elements:" << endl;
  for( auto y : nodetotal){
    y.node_print();
  }
  //debugging code ends here!
  
  if(nodetotal != nodebank){
    cout << "oh no, there are nodes in the nodebank which are neither parents nor children" << endl;
    is_tree = false;
  }
  return is_tree;
}

#endif // TREECLASS_H

/*  Remember, if you instantiate a variable
of type variant, and the value happens to be an int (for example), 
the type of that variable is STILL 'variant' with the given options.
If you check whether its type is int, the answer is no!

*/