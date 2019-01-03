#include "delta.h"


void delta::addTran(transition* t){
	tPtr temp(t);
	tran_list[t->getEvent()].push_back(move(temp));
	// each event has some transitions
	// in tran_list, event* is the key, vector<tPtr> are the values
}

void delta::printTranStruct(ostream& out){
	for(auto& sigma:tran_list){
		for(auto& transition:sigma.second){
			transition->printTran(out);
		}
	}
}
  
  // not clear yet ********************************************************
void delta::symbolicEncoding(DES* G, bdd add_pred){
	for(auto& tr_list:tran_list){
		bdd enc_pred = bddfalse;
		for(auto& tr:tr_list.second)
			enc_pred |= tr->encode(G); // encode is in transition.h, uses theta
			// encode transitions one by one
		tr_list.first->setNSigma(add_pred & enc_pred);
		// setNSigma is in event.h, 
		// here is the transitions encoding for each event
	}
}
