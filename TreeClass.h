#ifndef TREECLASS_H
#define TREECLASS_H
#include "Node.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

template <class T>
using PtrSet = std::unordered_set<Node<T>*, NodePtrHash<T>, NodePtrEqual<T>>;


template <class T>
class TreeClass
{
  private:
    std::unordered_map< Node<T>, PtrSet<T>, NodeHash<T> > tree;
  public:
    TreeClass(Node<T> n1);
    PtrSet<T>& get_ch(Node<T> n);
    void insert_parent(Node<T> new_parent);
    void insert_child(Node<T> parent, Node<T>* baby);
    void abort_child(Node<T> parent, Node<T>* baby);
    void abort_parent(Node<T> parent);
};



template <class T>
TreeClass<T>::TreeClass(Node<T> n1)
{
  tree[n1] = {}; /* by definition, trees are nonempty and have one parent! */
};


template <class T>
void TreeClass<T>::insert_parent(Node<T> new_parent)
{
  tree[new_parent] = {};
};


template <class T>
PtrSet<T>& TreeClass<T>::get_ch(Node<T> n)
{
  return tree[n];
};


template <class T>
void TreeClass<T>::insert_child(Node<T> parent, Node<T>* baby)
{
  PtrSet<T>& children = get_ch(parent);
  children.insert(baby);
};


template <class T>
void TreeClass<T>::abort_child(Node<T> parent, Node<T>* baby)
{
  (tree[parent]).erase(baby);
};


template <class T>
void TreeClass<T>::abort_parent(Node<T> parent)
{
  if(tree.size() >1){
    tree.erase(parent);
  }
  else{
    cout << "sorry, can't abort parent; trees must have at least one parent!" << endl;
  } 
};

#endif // TREECLASS_H

/*  Remember, if you instantiate a variable
of type variant, and the value happens to be an int (for example), 
the type of that variable is STILL 'variant' with the given options.
If you check whether its type is int, the answer is no!

*/