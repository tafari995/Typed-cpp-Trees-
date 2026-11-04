#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <type_traits>
#include <cstddef>
#include <functional>
using namespace std;

template <class T>
class Node {
  private:
    T value;
  public:
    Node(T v);
    void node_print();
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


// defines Node equality; two nodes are equal iff their values are equal
template <class T>
bool operator==(const Node<T>& node, const Node<T>& other) 
{
  return node.v()==other.v();
};


// turns value of type T into a string, if it's not one already
template <class T>
std::string get_string(T value) 
{
  if constexpr (std::is_same_v<T, std::string>) {
    return value; 
  } 
  else {
    return std::to_string(value); 
  }
};


// prints out value at a given node
template <class T>
void Node<T>::node_print()
{ 
  cout << "node_value = " <<  get_string(value) << endl;
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

/* claude wrote this 
bool operator==(const Node& other) const {
return value==other.value
}
claude also made up this strange little hash function and used like so...
nammespace std {
    template <class T>
    struct hash<Node<T>>{
      size_t operator()(const Node<T>& n) const {
        size_t hsh = hash<T>{}(n.v());
        return hsh;
      }
    };
}
hypothetically, this was enough to use nodes as
keys in an unordered map, though i did not test the code claude wrote!
*/

/* growing skeptical of using member 
initialization with template classes, code may work
more cleanly without initialization, and using
the standard way of defining member functions outside
of a class 
*/