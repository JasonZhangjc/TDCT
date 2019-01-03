#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <algorithm>

#include <fdd.h>

using namespace std;

class DES;

class event{
public:
	  // Constructors:
	event();
	event(string sigma);
	event(string sigma, bool _ctrb);
	  // Name relevant
	string getName();
	string printName();
	  
	bool isCtrb();
	
	void addContainer(DES* G);
	
	void insertSrc(int i);
	void insertTgt(int i);
	
	void setNSigma(bdd P);
	bdd getNSigma();

	void setFSigma(bdd P);
	bdd getFSigma();
	
	void setVarSets();
	
	bdd delta(bdd pred);
	bdd gamma(bdd pred);
	
	bdd handleIllegalPred(bdd& P);

private:
	string name;
	bool ctrb;
	set<DES*> container;
	set<int> src_vars;
	set<int> tgt_vars;
	bdd n_sigma;
	bdd f_sigma;
	bdd set_of_src_vars;
	bdd set_of_tgt_vars;
	bddPair* src_to_psrc;
	bddPair* psrc_to_src;
};


typedef unique_ptr<event> ePtr;

class eCompare{
public:
	bool operator () (const ePtr& e1, const ePtr& e2)const;
};


#endif // EVENT_H
