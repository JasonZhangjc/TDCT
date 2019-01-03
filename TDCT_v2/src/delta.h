#ifndef DELTA_H
#define DELTA_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "event.h"
#include "transition.h"

using namespace std;


class delta{
public:
	void addTran(transition* t);
	void printTranStruct(ostream& out);
	void symbolicEncoding(DES* G, bdd add_pred = bddtrue);

private:
	unordered_map<event*, vector<tPtr>> tran_list;
};

typedef unique_ptr<delta> dPtr;


#endif // DELTA_H
