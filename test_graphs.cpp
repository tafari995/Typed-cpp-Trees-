#include "Node.h"
#include "TreeClass.h"
using namespace std;



int main(){
  int an_int = 5;
  string a_str = "buttercup";
  Node<int> v(an_int);
  Node<std::string> w(a_str);
  v.node_print();
  w.node_print();

  TreeClass treeobj(v);
  // PtrSet<int> first_children = treeobj.get_ch(v); 
  Node<int> v2(-7);
  Node<int>* p2 = &v2;
  // first_children.insert(p2);
  treeobj.insert_child(v,p2);
  for(const auto& child : treeobj.get_ch(v)){
    (*child).node_print();
  };
  return 0;
}