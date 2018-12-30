#include "transition.h"
#include "des.h"
#include "event.h"

event* transition::setEvent(event* _sigma, DES* G){
    G->addEvent(_sigma);
    this->setEvent(_sigma); 
    return _sigma;
}

void transition::addSrc(istream& is, DES* G, int num_of_srcs){
    for(int j = 0; j < num_of_srcs; ++j){
        string source;
        is >> source;
        DES* srcs = G->findCmp(source); 
          // returns the name of DES that contain source
        if(srcs == nullptr){
            cerr << "Error: source DES " << source
                 << "not found in " << G->getName() << endl;
            abort();
        }
        this->addSrc(srcs); // see the method below
    }
}

void transition::addSrc(DES* sDES){
    if(simpleDES* s = dynamic_cast<simpleDES*>(sDES)){
        src.insert(sDES);
        return;
    }
    else throw badSrcDES();
}

void transition::addTgt(istream& is, DES* G, int num_of_tgts){
    for(int j = 0; j < num_of_tgts; ++j){
        string target;
        is >> target;
        DES* tgts = G->findCmp(target);
        if (tgts == nullptr){
            cerr << "Error: destination DES " << target
                 << "not found in " << G->getName() << endl;
            abort();
        }
        this->addTgt(tgts);
    }
}

void transition::addTgt(DES* tDES){
    if(simpleDES* s = dynamic_cast<simpleDES*>(tDES)){
        tgt.insert(tDES);
        return;
    }
    else throw badTgtDES();
}

void transition::printTran(ostream& out){
    out << "from: (";
    for(auto& source:src)
        out << source->getName() << ",";
    out << "\b) via: " << sigma->printName() << " to: (";
    for(auto& target:tgt)
        out << target->getName() << ",";
    out << "\b)" << endl;
    return;
}

bdd transition::encode(DES* G){
    bdd srcBDD = bddtrue;
    bdd tgtBDD = bddtrue;
    for(auto& s:src)
        srcBDD &= G->theta(s,true, sigma); 
          // theta is the tran encode if there is source and sigma
    for(auto& t:tgt)
        tgtBDD &= G->theta(t,false,sigma);
    return srcBDD & tgtBDD;
}
