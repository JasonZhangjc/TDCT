#ifndef IO_H
#define IO_H

#include <iostream>

using namespace std;


class DES;
class TDS;

class IO{
public:
	static DES* inputReader(string file_path, string file_name, 
	                        DES* parent, TDS* G);
	static void readCmp(string file_path, ifstream& is, DES* parent,
	                    int size, TDS* G);
	static void readTran(ifstream& is, DES* G, int tsize, TDS* tree);
};


#endif // IO_H
