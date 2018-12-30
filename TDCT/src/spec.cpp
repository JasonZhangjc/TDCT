#include "spec.h"

  // The hierarchy is predicate -> clause -> literal
bdd spec::readLiteral(istream& input, TDS* tree){
    string var, value;
    input >> var >> value;
    DES* D1 = tree->findCmp(var);
    DES* D2 = tree->findCmp(value);
    if (D1 == nullptr || D2 == nullptr){
        string error = (D1)? value:var;
        cerr << "Error: DES " << error << " not found in spec file!" << endl;
        abort();
    }
      // spec must be defined for xorDES
    if (D1->getType() != DEStype::XOR){
        cerr << "Error: DES " << var << " is not an XOR product DES!" << endl;
        abort();
    }
      // fdd_ithvar(D1->getfddDom, D2->getfddState) 表示：
      // 把D1的fddDom赋值成D2的fddState
      // 再和D1的 add_pred 取交集	
    return (fdd_ithvar(D1->getfddDom(), D2->getfddState()) & D1->getAddPred());
}

  // read a clause of a DNF
bdd spec::readClause(istream& input, TDS* tree){
    int size_of_clause;
    input >> size_of_clause;
    bdd clause = bddtrue;
    while(size_of_clause){
        bdd  literal = spec::readLiteral(input, tree);
        clause &= literal;   // "and" relation
        size_of_clause--;
    }
    return clause;
}

  // Read a DNF (disjuntive normal form) predicate
bdd spec::readPred(istream& input, TDS* tree){
    int num_of_clauses;
    input >> num_of_clauses;
    bdd predicate = bddfalse;
    while(num_of_clauses){   // until it is 0
        bdd clause = spec::readClause(input, tree);
        predicate |= clause; // "or" relation
        num_of_clauses--;
    }
    return predicate;
}

bdd spec::readSpec1File(string file_path, TDS* tree){
    ifstream input(file_path + "/spec1.txt");
    if (input.fail()){
        cerr << "Error: spec1 file not found!" << endl;
        abort();
    }
    bdd predicate = spec::readPred(input, tree); // only on spec1
    return bdd_not(predicate); // illegal pred is the "negation of predicate"
}

  // The following two methods are related to "spec2.txt"
void spec::readEventSpec(istream& input, bdd& pred, TDS* tree){
    string s;
    input >> s;
    event* sigma = tree->findEvent(s);
    if (sigma == nullptr){
        cerr << "Error: Event " << s << " in spec2 not found!" << endl;
        abort();
    }
    bdd predicate = spec::readPred(input, tree);
    pred |= sigma->handleIllegalPred(predicate);    // defined in event.cpp
}

bdd spec::readSpec2File(string file_path, TDS* tree){
    ifstream input(file_path + "/spec2.txt");
    if (input.fail()){
        cerr << "Error: spec2 file not found!" << endl;
        abort();
    }
    int num_of_specs;
    input >> num_of_specs;
    bdd predicate = bddfalse;
    while (num_of_specs){
        spec::readEventSpec(input,predicate, tree); // call the above methods
        num_of_specs--;                             // a number of spec2
//        fdd_printset(predicate); cout << endl;
    }
    return bdd_not(predicate); // illegal pred is the "negation of predicate"
}
