#include <iostream>
#include "des.h"
#include "event.h"
#include "transition.h"
#include "delta.h"
#include "tds.h"

using namespace std;


int main(int argc, char *argv[]){
	
	  // initilize the BDD
	bdd_init(BDD_nodeNUM,BDD_cacheSize);
	bdd_setvarnum(10000);
	
	  // a printing callback handler
	fdd_file_hook(printHandler);
	
	if (argc != 3){
        cerr << "Error: invalid command line arguments!" << endl;
        abort;
    }
    
      // initilize the TDS
    string file_path = argv[1];
    string root_file = argv[2];
    cout << "Welcome to BDD-based Tree-DES Computation Tool" << endl;
    
    TDS temp(file_path,root_file);
    temp.print();
    temp.run();
    
      // run the supervisory control synthesis
    temp.supcon(file_path);
    temp.runUnderControl();
    temp.printControlData(file_path);
    
	return 0;
}
