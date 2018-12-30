#ifndef TDS_H
#define TDS_H

#include "des.h"

#define BDD_nodeNUM 1000000 // will be used in main.cpp
#define BDD_cacheSize 10000 // will be used in main.cpp

using namespace std;

  // TDS is the outer structure of DES, namely Tree_DES
class TDS{
private:
    DESPtr root;          // root node
    unordered_map<string, ePtr> Sigma; // key: string, value: event pointer
    bool init_set;        // initial symbolic procedures done if "true"
    bdd P0;               // Initial predicate
    bdd Pm;               // Marker predicate
    bdd supC2P;           // Supremal controllable behavior
    
public:
    TDS(string file_name, string file_path); // related to io
    event* addEvent(istream& is);
    DES* findCmp(string G);
    event* findEvent(string e);
    void setInit();
    
      // open-loop run of the system
    void run(string G = "");
    void runRec(bdd current, vector<bdd>& visited_states,
                int curr_index, int& num_of_tran,
                bool local, bdd& set_of_vars);

      /* specification given in dijuntive form
       * predicate corresponding to illegal set of states
       * bdd readSpecFile(string filePath); */

      // sysnthesis functions
    void supcon(string file_path);
    void createSupC2P(bdd& P); // supremal controllable behavior
    bdd CR(bdd& P);            // coreachable
    bdd supCP(bdd& P);
    bdd Bracket(bdd& P);       // [.]
    
      // closed-loop run of the system
    void runUnderControl();
    void runUnderControlRec(bdd current, vector<bdd>&
                            visited_states, int curr_index, int& num_of_tran);
      // print func
    void print();
    void printControlData(string file_path);
};

#endif // TDS_H
