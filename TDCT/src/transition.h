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

class badSrcDES{}; // Used to throw exceptions when non-simple source is added!
class badTgtDES{}; // Used to throw exceptions when non-simple target is added!

class transition{
private:
    set<DES*> src; 
      // set of source simple DESs - Note: source state is always a simple DES
    set<DES*> tgt; 
      // set of target simple DESs - Note: target state is always a simple DES
    event* sigma;
    
public:
    transition():sigma{nullptr}{}
    transition(event* _sigma):sigma{_sigma}{}
    event* setEvent(event* _sigma, DES* G);
    void setEvent(event* _sigma){sigma = _sigma;}
    event* getEvent(){return sigma;}
    void addSrc(istream& is, DES* G, int num_of_srcs);
    void addSrc(DES* sDES);
    void addTgt(istream& is, DES* G, int num_of_tgts);
    void addTgt(DES* tDES);
    void printTran(ostream& out);

    bdd encode(DES* G);
};

typedef unique_ptr<transition> tPtr;

#endif // TRANSITION_H
