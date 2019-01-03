#ifndef TRANSITION_H
#define TRANSITION_H

#include <iostream>
#include <memory>
#include <istream>
#include <set>

#include <fdd.h>

using namespace std;

class event;
class DES;

class badSrcDES{};
class badTgtDES{};

class transition{
public:
	  // Constructors:
	transition():sigma{nullptr}{}
	transition(event* _sigma):sigma{_sigma}{}
	  // Event relevant:
	event* setEvent(event* _sigma, DES* G);
	void setEvent(event* _sigma){sigma = _sigma;}
	event* getEvent(){return sigma;}
	  // Source and target relevant:
	void addSrc(istream& is, DES* G, int num_of_srcs);
	void addSrc(DES* sDES);
	void addTgt(istream& is, DES* G, int num_of_tgts);
	void addTgt(DES* tDES);
	  // Print relevant
	void printTran(ostream& out);
	  // Encode relevant
	bdd encode(DES* G);

private:
	set<DES*> src;
	set<DES*> tgt;
	event* sigma;
};


typedef unique_ptr<transition> tPtr;


#endif // TRANSITION_H
