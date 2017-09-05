#include "ITree.h"
#include <iostream>
using namespace std;


ITree::ITree(){
lefty = NULL;
righty = NULL;
val = "";
}
ITree::ITree(string sr){
lefty = NULL;
righty = NULL;
val = sr;
}
void ITree::print(){
  if (lefty != NULL)
    lefty->print();
  cout << val << " , ";
  if (righty != NULL)
    righty->print();
}
void ITree::sval(string s){
val = s;
}
string ITree::getVal(){
return val; 
}
ITree* ITree::left(){
return lefty;
}
ITree* ITree::right(){
return righty;
}
void ITree::sright(ITree* sr){
righty = sr;
}
void ITree::sleft(ITree* sl){
lefty = sl;
}

