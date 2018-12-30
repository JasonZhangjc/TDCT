#include "io.h"
#include "tds.h"


DES* IO::inputReader(string file_path, string file_name, DES* par, TDS* G){
    ifstream is(file_path + "/" + file_name + ".txt");
    if(is.fail()){
        cerr << "Error: Input file " << file_path + "/" + file_name + ".txt"
             << " not found!" << endl;
        abort();
    }
    cout << "Inupt file" << file_path + "/" + file_name + ".txt" << " opened!";
    cout << endl;

    string name, type;
    int size, tsize; // component size and transition size, 
                     // tsize = 0 in case of sync TDSs
    is >> name >> type >> size >> tsize;
    if(is.fail()){
        cerr << "Error: Input file " << file_path + "/" + file_name + ".txt"
             << " name read fail!" << endl;
        abort();
    }

    DES* newDES; // return newDES later
    
    int fdd_state = (par)? par->getCmpSize(): 0;
    if (type == "xor"){
        newDES = new xorDES(name,par,size,fdd_state);
        IO::readCmp(file_path,is,newDES,size,G); // defined below
        IO::readTran(is,newDES,tsize,G);         // defined below
    }
    else if ( type == "sync" ){
        newDES = new syncDES(name,par,size,fdd_state);
        IO::readCmp(file_path,is,newDES,size,G); 
          // syncDES doesn't have linker transitions
    }
    else {
        cerr << "Error: Unkown type " << type << " in " <<
                file_path + "/" + name + ".txt" << endl;
        abort();
    }
    cout << "Inupt file" << file_path + "/" + name + ".txt" << " read!" << endl;
    return newDES;
}


  // only for xorDES and syncDES
void IO::readCmp(string file_path, ifstream& is, DES* parent, int size, TDS* G){
    cout << "Reading components of " <<
            file_path + "/" + parent->getName() + ".txt!" << endl;
    for( int i = 0; i < size; ++i){
        string name, type;
        is >> name >> type;
        DES* newDES;
        if ( type == "simple"){
            bool init, marker;
            is >> init >> marker;
            if (is.fail()){
                cerr <<"Error: initial and marker bits aren't set for simpleDES"
                     << name << " in " << file_path + "/" + 
                        parent->getName() + ".txt!" << endl;
                abort();
            }
            newDES = new simpleDES(name, parent, parent->getCmpSize(), 
                                   init, marker);
        }
        else if (type == "xor" || type == "sync")
            newDES = IO::inputReader(file_path, name, parent, G);
        else {
            cerr << "Error: Unkown type " << type << " in " <<
                    file_path + "/" + name + ".txt" << endl;
            abort();
        }
        parent->addCmp(newDES);
    }
    cout << "Components of " <<
            file_path + "/" + parent->getName() + ".txt" << " read!" << endl;
}


  // only for xorDES
void  IO::readTran(ifstream& is, DES* G, int tsize, TDS* tree){
    cout << "Reading transitions of " << G->getName() << "!" << endl;
    delta* tran_struct = new delta();
    for(int i = 0; i < tsize; ++i){
        transition* new_tran = new transition();
        int num_of_srcs, num_of_tgts;
        is >> num_of_srcs >> num_of_tgts;

        new_tran->addSrc(is,G,num_of_srcs);        // defined in transition.h
        new_tran->setEvent(tree->addEvent(is), G); // defined in transition.h
        new_tran->addTgt(is,G,num_of_tgts);        // defined in transition.h
        
        tran_struct->addTran(new_tran); // defined in delta.h
    }
    tran_struct->symbolicEncoding(G, G->getAddPred());
    G->addDelta(tran_struct);
    cout << "Transitions  of " << G->getName() << " read!" << endl;
}
