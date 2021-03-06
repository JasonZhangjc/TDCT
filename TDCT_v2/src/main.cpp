#include <iostream>
#include <chrono>
#include "des.h"
#include "event.h"
#include "transition.h"
#include "delta.h"
#include "tds.h"

using namespace std;
using namespace std::chrono;


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
    cout << "Welcome to BDD-based Tree-DES Computation Tool Version 1" << endl;
    
    TDS temp(file_path, root_file);
    temp.print();
    temp.run();
    
      // run the supervisory control synthesis
    auto t1 = high_resolution_clock::now();
    temp.supcon(file_path);
    auto t2 = high_resolution_clock::now();
    cout << endl;
    cout << "Supervisory control synthesis took: " <<
                duration_cast<milliseconds>(t2 - t1).count() << " ms!" << endl << endl;
    
    temp.runUnderControl();
    temp.printControlData(file_path);
    
	return 0;
}
