#ifndef ITREE_H
#define ITREE_H
#include <string>
using namespace std;

class ITree{
public:
   ITree();
   ITree(string sr);
   void sval(string s);
   string getVal();
   void print();
   ITree* left();
   ITree* right();
   void sright(ITree* sr);
   void sleft(ITree* sl);
private:
   ITree* lefty;
   ITree* righty;
   string val;
};
#endif