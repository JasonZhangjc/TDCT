#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <memory>
#include <set>
#include <fdd.h>
#include <vector>
#include <algorithm>

using namespace std;


class DES;

class event{
private:
    string name;
    bool   ctrb; // event is controllable if "ctrb = true"; default is "true";
    set<DES*> container; // set of DESs that contain transitions of this event
    set<int> src_vars;   // set of correpsonding source fdd variables;
    set<int> tgt_vars;   // set of corresponding target fdd variables;
    bdd n_sigma; // encoded transition under this event; N: forward encoding
    bdd f_sigma; // synthesized control functions;       F: backward encoding
    bdd set_of_src_vars;  // \mathbf{v}'_{\sigma,S}  is a state-specific pred
    bdd set_of_tgt_vars;  // \mathbf{V}_{\sigma,T}   is a state-specific pred
    bddPair* src_to_psrc; // v_{\sigma,S}\rightarrow v'_{\sigma,S}, is used in N
    bddPair* psrc_to_src; // v'_{\sigma,S}\rightarrow v_{\sigma,S}, is used in F
                          // bddPair is used in "bdd_replace()" 
	
public:
      // Constructors
    event();
    event(string sigma);
    event(string sigma, bool _ctrb);
      // Other methods
    string getName();
    string printName();
    bool isCtrb();
    void addContainer(DES* G);
    void insertSrc(int i);
    void insertTgt(int i);
    void setNSigma(bdd P);
    bdd  getNSigma();
    void setVarSets();    // relatively complicated
    bdd delta(bdd pred);  // forward function
    bdd gamma(bdd pred);  // backward function
    void setFSigma(bdd P);
    bdd getFSigma();
    bdd handleIllegalPred(bdd& P);
};


typedef unique_ptr<event> ePtr;

class eCompare{
public:
    bool operator()(const ePtr& e1, const ePtr& e2)const;
};

#endif // EVENT_H
