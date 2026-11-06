#include "Node.h"
#include "SetHelpers.h"
#include "TreeClass.h"
using namespace std;



int main(){
  int an_int = 5;
  string a_str = "buttercup";
  Node<int> v(an_int);
  Node<std::string> w(a_str);
  // v.node_print();
  // w.node_print();
  
  int another_int = -7;
  Node<int> v_2(another_int);

  Node<int>* p = &v;
  TreeClass treeobj(p);
  Node<int>* p_2 = n2p(v_2);

  treeobj.insert_child(p,p_2);

  for(const auto& child : treeobj.get_ch(p)){
    cout << "\n" << endl;
    p2n(child).node_print();
    p2n(child).node_print();

  };
  // cout << std::boolalpha << treeobj.is_tree_still() << endl;
  return 0;
}