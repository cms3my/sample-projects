#include "ReciNode.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

ReciNode::ReciNode(string s, string list[20]){
      int t = s.find("\"");
      string stc = s.substr(0,t);
      for (int i = 0; i < 20; i++){
         if (list[i].compare(stc) == 0)
            category = i;
      }
      ins = s.substr(t + 2);
   }
   ReciNode::ReciNode(ReciNode* r){
      ins = r->getIns();
      category = r->getCat();
   }
   string ReciNode::getIns(){
      return ins;
   }
   int ReciNode::getCat(){
      return category;
   }

