#include "io.h"
#include "tds.h"


  // read the DES files and spec files
DES* IO::inputReader(string file_path, string file_name, DES* parent, TDS* G){
	ifstream is(file_path + "/" + file_name + ".txt");
	if(is.fail()){
		cerr << "Error: Input file " << file_path + "/" + file_name + ".txt"
		     << " not found!" << endl;
		abort();
	}
	cout << "Input file" << file_path + "/" + file_name + ".txt" << " opened!";
	cout << endl;
	
	string name;	// name of DES
	string type;	// type of DES
	int size;		// size of states
	int tsize; 		// size of transitions, tsize = 0 in case of syncDES
	is >> name >> type >> size >> tsize;
	/* 	for example, a DES file looks like the following:
		X0			// name
		sync 2 0	// sync = type, 2 = size, 0 = tsize
		X1 xor
		X2 xor	       */
	if(is.fail()){
		cerr << "Error: Input file " << file_path + "/" + file_name + ".txt"
		     << " name read fail!" << endl;
		abort();
	}
	
	DES* newDES; // return newDES later
	int fdd_state = (parent) ? parent->getCmpSize() : 0; 
	// if parent is not empty, fdd_state its CmpSize, otherwise fdd_state is 0
	if(type == "xor"){
		newDES = new xorDES(name, parent, size, fdd_state);
		IO::readCmp(file_path, is, newDES, size, G);
		IO::readTran(is, newDES, tsize, G); 
		// first read components, then read transitions
		/*	for example, a xorDES is as following:
			B1  				// name
			xor 2 1   			// type, size, tsize
			B10 simple 1 0		// components
			B11 simple 0 0		// components
			1 1 B10 mu 0 B11    // transitions  */
	}
	else if(type == "sync"){
		newDES = new syncDES(name, parent, size, fdd_state);
		IO::readCmp(file_path, is, newDES, size, G);
		// syncDES doesn't have linker transitions
	}
	else{
		cerr << "Error: unknown type " << type << "in" 
		     << file_path + "/" + name + ".txt" << endl;
		abort();
	}
	cout << "Input file" << file_path + "/" + name + ".txt" << "read!" << endl;
	return newDES;
}

  // only for xorDES and syncDES
void IO::readCmp(string file_path, ifstream& is, DES* parent, int size, TDS* G){
	cout << "Reading components of "
	     << file_path + "/" + parent->getName() + ".txt!" << endl;
	for(int i=0;i<size;++i){
		string name;
		string type;
		is >> name >> type;
		DES* newDES;
		if(type == "simple"){
			bool initial;
			bool marker;
			is >> initial >> marker;
			/*	for example:
				B10 simple 1 0		// B10 = name, simple = type
				                    // 1 means it is initial
				                    // 0 means it is not marker  	*/
			if(is.fail()){
				cerr << "Error: initial & marker bits aren't set for simpleDES"
				     << name << " in " << file_path + "/" + parent->getName()
				     + ".txt!" << endl;
				abort();
			}
			newDES = new simpleDES(name, parent, parent->getCmpSize(), 
								   initial, marker);
		}
		else if(type == "xor" || type == "sync")
			newDES = IO::inputReader(file_path, name, parent, G);
		else{
			cerr << "Error: unknown type " << type << " in " 
			     << file_path + "/" + name + ".txt" << endl;
			abort();
		}
		parent->addCmp(newDES);
	}
	cout << "Components of " << file_path + "/" + parent->getName() + ".txt"
	     << " read!" << endl;
}

  // only for xorDES
void IO::readTran(ifstream& is, DES* G, int tsize, TDS* tree){
	cout << "Reading transitions of " << G->getName() << "!" << endl;
	delta* tran_struct = new delta();
	for(int i=0;i<tsize;++i){
		transition* new_tran = new transition();
		int num_of_srcs;
		int num_of_tgts;
		is >> num_of_srcs >> num_of_tgts;
		/*	for example:
			1 1 B10 mu 0 B11 	// 1 = num_of_srcs, 1 = num_of_tgts	*/
		new_tran->addSrc(is, G, num_of_srcs);      // read B10
		new_tran->setEvent(tree->addEvent(is), G); // read mu 0
		new_tran->addTgt(is, G, num_of_tgts);	   // read B11
		tran_struct->addTran(new_tran);
	}
	tran_struct->symbolicEncoding(G, G->getAddPred()); // transition encoding
	G->addDelta(tran_struct);
	cout << "Transitions of " << G->getName() << " read!" << endl;
}

