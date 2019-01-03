#ifndef SPEC_H
#define SPEC_H

#include "tds.h"

using namespace std;


class spec{
public:
	static bdd readLiteral(istream& input, TDS* tree);
	static bdd readClause(istream& input, TDS* tree);
	static bdd readPred(istream& input, TDS* tree);
	static bdd readSpec1File(string file_path, TDS* tree);
	static bdd readSpec2File(string file_path, TDS* tree);
	static void readEventSpec(istream& input, bdd& pred, TDS* tree);
};


#endif // SPEC_H
