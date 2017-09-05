#include <stdio.h>
#include <math.h>
#include "ITree.h"
#include "ReciNode.h"
#include <iostream>
#include <fstream>
#include <string>
class DTMake{

   vector<string> feats;
   string cate[20];
   vector<ReciNode*> dat;

public: DTMake(vector<string> test, vector<string> ingr){
    cate[0] = "british";
    cate[1] = "brazilian";
    cate[2] = "cajun_creole";
    cate[3] = "chinese";
    cate[4] =  "filipino";
    cate[5] = "french";
    cate[6] = "greek";
    cate[7] = "indian";
    cate[8] = "irish";
    cate[9] = "italian";
    cate[10] = "jamaican";
    cate[11] = "japanese";
    cate[12] = "korean";
    cate[13] = "mexican";
    cate[14] = "moroccan";
    cate[15] = "russian";
    cate[16] = "southern_us";
    cate[17] = "spanish";
    cate[18] = "thai";
    cate[19] = "vietnamese";

     for (int i = 0; i < test.size(); i++){
       dat.push_back(new ReciNode(test[i], cate));
     }
     for (int j = 0; j < ingr.size(); j++)
       feats.push_back(ingr[j]);
   }

public: string getCate(int i){
  return cate[i];
}
public: vector<ReciNode*> getDat(){
    return dat;
  }

  // calculates entropy of the base system
   double catEnt(int cats[]){
   double ent = 0.0;
   double sum = 0.0;
      for (int i = 0; i < 20; i+= 1){
         sum += cats[i];
      }
      for (int i = 0; i < 20; i+= 1){
        if (cats[i] != 0)
         ent -= (((double)cats[i] / (double)sum) * log2((double)cats[i] / (double)sum));
      }
      return ent;
   }

  // calculates gain for a given split
  double catGain(int catz[], int catztwo[], int ocats[]){
       double oent = catEnt(ocats);
       double loss = 0.0;
       double sum = 0.0, osum = 0.0, tsum = 0.0;
   for (int i = 0; i < 20; i+= 1){
     sum += (double)catz[i];
     osum += (double)ocats[i];
      tsum += (double)catztwo[i];
   }
   loss += ((sum / osum) * catEnt(catz)) + ((tsum / osum) * catEnt(catztwo));
       return (oent - loss);
   }

    //determines what feature should be the next split
  string split(vector<ReciNode*> vr, string n){
      int max = 0;
      double currmax = 0.0;
      for (int i = 0; i < feats.size(); i+= 1){
        int catcount[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int acount[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int count[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for ( int j = 0; j < vr.size(); j++){
	  if ((*vr[j]).getIns().find(feats[i]) == std::string::npos)
	    catcount[(*vr[j]).getCat()] += 1;
          else
            acount[(*vr[j]).getCat()] += 1;
          count[(*vr[j]).getCat()] += 1;
        }
        
        double tmax = catGain(catcount, acount, count);
        if (tmax > currmax && feats[i].find(n) == std::string::npos){
	  currmax = tmax;
          max = i;
        }
      }
      return feats[max];
    }

    //determines whether a leaf node has been reached 
    string leafName(vector<ReciNode*> l){
      int max = 0, sum = 0, maxpos = 0, j = 0, k = l.size();
      int acount[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      while (j < k){
         acount[(*l[j]).getCat()] += 1;
         //cout <<  acount[(*l[j]).getCat()] << "\n";
         sum += 1;
         if (max < acount[(*l[j]).getCat()]){
	   max = acount[(*l[j]).getCat()];
           maxpos = (*l[j]).getCat();
         }
         j+=1;
      }
      if ((((double)max) / (double)sum) > 0.75){
	return cate[maxpos];
      }
      return "no";
    }

    //recurses to build the decision tree
public: ITree* make(ITree* startNode, vector<ReciNode*> curr, string nope){
      string t = leafName(curr);
      ITree * startsNode = new ITree();
      if ((t.compare("no")) != 0){
	(*startsNode).sval(t);
        return startsNode;
      }
      string nn = split(curr, nope);
      (*startsNode).sval(nn);
      vector<ReciNode*> a, b;
      for (int i = 0; i < curr.size(); i++){
	size_t found = ((*curr[i]).getIns().find((*startsNode).getVal()));
	if (found != std::string::npos){
	  a.push_back(new ReciNode(curr[i]));
        }
        else{
          b.push_back(new ReciNode(curr[i]));
	}
        delete curr[i];
      }
      (*startsNode).sleft(make(new ITree(), a, nope + "," + nn));
      (*startsNode).sright(make(new ITree(), b, nope + "," + nn));
      delete startNode;
      return startsNode;
    };
    };
     
//method to guess the category of recipe given with the given decision tree
     string decide(ReciNode ab, ITree * at){
       if(at->left() == NULL && at->right() == NULL)
	 return at->getVal();
       if(ab.getIns().find(at->getVal()) == std::string::npos)
         return decide(ab, at->right());
       return decide(ab, at->left());
     } 

int main(){
  int wtot = 0, tot = 0;
  for (int q = 0; q < 6; q++){
  ifstream filin;
  ifstream ingreds;
  filin.open("training.csv");
  ingreds.open("ingredients.txt");
  vector<string> i;
  vector<string> d;
  vector<string> check;
  while (ingreds.good()){
    string ti;
    getline(ingreds, ti);
    i.push_back(ti.substr(ti.find_first_of("\"") + 1, ti.find_last_of("\"") - 1));
  }
  string ti;
  getline(filin, ti, '0');
  for (int j = 0; j <= 1793; j++){
    getline(filin,ti);
    ti = ti.substr(ti.find_first_of("\"") + 1);
    if (j % 6 != q)
       d.push_back(ti);
    else
      check.push_back(ti);
  }

  DTMake tre(d, i);
  ITree * head = new ITree();
  ITree * newHead = tre.make(head, tre.getDat(), "");
  DTMake ctre(check, i);
  vector<ReciNode*> toch = ctre.getDat();
  int correct = 0;
  for (int i = 0; i < toch.size(); i++){
    if(ctre.getCate(toch[i]->getCat()).compare(decide(*toch[i], newHead)) == 0)
      correct += 1;
    else
      wtot += 1;
    tot += 1;
  }
  cout << "for fold " << q + 1 << ", " << (1 - ((double)correct / (double)toch.size()))*100 << " percent error \n";
  }
  cout << "\nin total, error is at " << ((double)wtot / (double)tot)*100 << " percent \n\n";
  return 0;
}



