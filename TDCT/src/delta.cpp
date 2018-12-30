#include "delta.h"


void delta::addTran(transition* t){
    tPtr temp(t);
    tran_list[t->getEvent()].push_back(move(temp));
}

void delta::printTranStruct(ostream& out){
    for(auto& sigma:tran_list){
        for(auto& transition:sigma.second){ 
            transition->printTran(out);
        }
    }
}

void delta::symbolicEncoding(DES* G, bdd add_pred){
    for(auto& tr_list: tran_list){
        bdd enc_pred = bddfalse;
        for(auto& tr: tr_list.second)
            enc_pred |= tr->encode(G); // "encode" in transition.h, uses "theta"
        tr_list.first->setNSigma(add_pred & enc_pred); // "setNSigma" in event.h
    }
}
