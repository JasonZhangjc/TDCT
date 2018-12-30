#ifndef DELTA_H
#define DELTA_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "event.h"
#include "transition.h"

using namespace std;


  // This class implements the transition structure of an XOR TDS.
class delta{
private:
    unordered_map<event*, vector<tPtr>> tran_list; 
      // tPtr is the transition pointer
      // key: event pointer, value: vector of transition pointer
    
public:
    void addTran(transition* t);
    void printTranStruct(ostream& out);
      /* The following method encodes all transitions inside
       * DES G. "add_pred" is G's encoding predicate, (state encoding) 
       * used for encoding transitions in lower levels. */
    void symbolicEncoding(DES* G, bdd add_pred = bddtrue);
};

typedef unique_ptr<delta> dPtr;


#endif // DELTA_H
