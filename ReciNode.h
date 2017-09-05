#ifndef RECINODE_H
#define RECINODE_H
#include <string>
#include <vector>
using namespace std;
class ReciNode{
public:
   ReciNode(string s, string list[20]);
   ReciNode(ReciNode* r);
   int getCat();
   string getIns();
private:
   int category;
   string ins;
};

#endif
