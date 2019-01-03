#include "spec.h"


bdd spec::readLiteral(istream& input, TDS* tree){
	string var;
	string value;
	input >> var >> value; // need to input a variable and a value
	// variables and the corresponding value are written in spec.txt
	DES* D1 = tree->findCmp(var);
	DES* D2 = tree->findCmp(value);
	if(D1 == nullptr || D2 == nullptr){
		string error = (D1) ? value : var;
		cerr << "Error: DES " << error << " not found in soec file!" << endl;
		abort();
	}
	if(D1->getType() != DEStype::XOR){
		cerr << "Error: DES " << var << " is not an XOR product DES!" << endl;
		abort();
	}
	return (fdd_ithvar(D1->getfddDom(), D2->getfddState()) & D1->getAddPred());
	// set v_D1 to D2, then return D1.add_pred & v_D1=D2;
}

bdd spec::readClause(istream& input, TDS* tree){
	int size_of_clause;
	input >> size_of_clause; // need to input the size_of_clause
	// size_of_clause is written in spec.txt
	bdd clause = bddtrue;
	while(size_of_clause){
		bdd literal = spec::readLiteral(input, tree);
		clause &= literal; // clause = literal & literal & ...
		size_of_clause--;
	}
	return clause;
}

bdd spec::readPred(istream& input, TDS* tree){
	int num_of_clauses;
	input >> num_of_clauses; // need to input the num_of_clauses
	// num_of_clauses is written in spec.txt
	bdd predicate = bddfalse;
	while(num_of_clauses){
		bdd clause = spec::readClause(input, tree);
		predicate |= clause; // pred = clause \/ clause \/ ...
		num_of_clauses--;
	}
	return predicate;
}

bdd spec::readSpec1File(string file_path, TDS* tree){
	ifstream input(file_path + "/spec1.txt");
	if(input.fail()){
		cerr << "Error: spec1 file not found!" << endl;
		abort();
	}
	bdd predicate = spec::readPred(input, tree);
	return bdd_not(predicate);
}

/*	for example, spec1.txt is in the following style:
	1			// num_of_clauses
	2 			// size_of_clause
	X1 A		// X1 is var, A is value
	X2 E        // X2 is var, E is value             */

bdd spec::readSpec2File(string file_path, TDS* tree){
	ifstream input(file_path + "/spec2.txt");
	if(input.fail()){
		cerr << "Error: spec2 file not found!" << endl;
		abort();
	}
	int num_of_specs;
	input >> num_of_specs; // is written in spec2.txt
	bdd predicate = bddfalse;
	while(num_of_specs){
		spec::readEventSpec(input, predicate, tree); // for each event
		num_of_specs--;
	}
	return bdd_not(predicate);
}

/* 	for example, spec2.txt is in the following style:
    1         	// num_of_specs
    tau       	// string s
	1         	// num_of_clauses
	1         	// size_of_clause
	X2 E      	// X2 is var, E is value               */

void spec::readEventSpec(istream& input, bdd& pred, TDS* tree){
	string s;
	input >> s; // input the event written in spec2.txt
	event* sigma = tree->findEvent(s);
	if(sigma == nullptr){
		cerr << "Error: Event " << s << " in spec2 not found!" << endl;
		abort();
	}
	bdd predicate = spec::readPred(input, tree);
	pred |= sigma->handleIllegalPred(predicate);
}

