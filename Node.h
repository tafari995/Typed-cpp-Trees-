#ifndef NODE_H
#define NODE_H
#include "NodeHelpers.h"
#include <iostream>
#include <string>
#include <type_traits>
#include <cstddef>
#include <functional>
using namespace std;

// Node Class Definition
template <class T>
class Node {
  private:
    T value;
  public:
    Node(T v);
    void node_print() const;
    const T& v() const;
    
};


// Node Class Constructor
template <class T>
Node<T>::Node(T v)
{
  value = v;
};


// gets node value
template <class T>
const T& Node<T>::v() const 
{
  return value;
};


// prints out value at a given node
template <class T>
void Node<T>::node_print() const
{ 
  cout << "node_value = " <<  get_string(value) << endl;
};


//---------------------------------------------------

// NODE EQUALITY

// defines Node equality; two nodes are equal iff their values are equal
template <class T>
bool operator==(const Node<T>& node, const Node<T>& other) 
{
  return node.v()==other.v();
};


// adds hash to node class, uses hash of the node value
template <class T>
struct NodeHash {
  std::size_t operator()(const Node<T>& n) const {
    std::size_t hsh = std::hash<T>{}(n.v());
    return hsh;
  }
};

//---------------------------------------------------------

// pointer -> node -> pointer converter functions

/* BROKEN: currently, these functions are not inverses of each other,
but I want them to be so that nodes don't change values when we 
convert them to pointers and back again */

template <class T>
Node<T>* n2p(Node<T> node)
{
  Node<T>* ptr = &node;
  return ptr;
};

template <class T>
Node<T> p2n(Node<T>* ptr)
{
  return *ptr;
};

//---------------------------------------------------------

// NODE POINTER HASH AND EQUALITY 

// Custom Hash: Hashes the 'value' member of the pointed-to object
template <class T>
struct NodePtrHash {
    std::size_t operator()(const Node<T>* ptr) const {
        return std::hash<T>{}( (*ptr).v() );
    }
};


// Custom Equal: Compares the 'value' member of the pointed-to objects
template <class T>
struct NodePtrEqual {
    bool operator()(const Node<T>* lhs, const Node<T>* rhs) const {
        return (*lhs).v() == (*rhs).v();
    }
};
   

#endif // NODE_H


/* growing skeptical of using member 
initialization with template classes, code may work
more cleanly without initialization, and using
the standard way of defining member functions outside
of a class 
*/