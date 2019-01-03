#ifndef TDS_H
#define TDS_H

#include "des.h"

#define BDD_nodeNUM 1000000
#define BDD_cacheSize 10000

using namespace std;


class TDS{
public:
	  // Constructor:
	TDS(string file_name, string file_path);
	
	event* addEvent(istream& is);
	event* findEvent(string e);	
	DES* findCmp(string G);
	
	void setInit();
	void run(string G = "");
	void runRec(bdd current, vector<bdd>& visited_states, int curr_index,
				int& num_of_tran, bool local, bdd& set_of_vars);
				
	void supcon(string file_path);
	void createSupC2P(bdd& P);
	bdd CR(bdd& P);
	bdd supCP(bdd& P);
	bdd Bracket(bdd& P);
	
	void runUnderControl();
	void runUnderControlRec(bdd current, vector<bdd>& visited_states, 
							int curr_index, int& num_of_tran);
	
	void print();
	void printControlData(string file_path);

private:
	DESPtr root;
	unordered_map<string, ePtr> Sigma;
	bool init_set;
	bdd P0;
	bdd Pm;
	bdd supC2P;
};


#endif // TDS_H

