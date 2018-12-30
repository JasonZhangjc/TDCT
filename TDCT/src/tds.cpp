#include "tds.h"
#include "io.h"
#include "spec.h"

TDS::TDS(string file_name, string file_path){
    root.reset(IO::inputReader(file_name, file_path, nullptr, this)); 
      // only smart pointer can use "reset()"
    init_set = false;
    supC2P = bddtrue;
}

DES* TDS::findCmp(string G){
    return root->findCmp(G); // TDS is the system, so search in root
}

event* TDS::findEvent(string s){
    auto it = Sigma.find(s);
    if (it == Sigma.end()) // it means not found!
        return nullptr;
    else return it->second.get(); // return ePtr
}

event* TDS::addEvent(istream& is){
    string e;
    bool ctrb;
    is >> e >> ctrb;
    if (Sigma[e] == nullptr) // if not in Alphabet, add to Alphabet
        Sigma[e].reset(new event(e,ctrb)); 
    return Sigma[e].get();
}

  // open-loop run of the system
void TDS::setInit(){
    P0 = root->initPred();
    Pm = root->markPred();
    for(auto& sigma:Sigma)
          // set v_sigma, v_sigma', v_sigma_S, v_sigma_T, all initializations!
        sigma.second->setVarSets(); // eTtr->setVarSets()
    init_set = true; // initial symbolic procedures are done, so "true"
}

void TDS::run(string G){
    if(!init_set)
        setInit(); // run() after setInit()
    vector<bdd> visited_states;    // used for counting number of states!
    visited_states.push_back(P0);  // push initPred into visited_states
    int num_of_tran = 0; // initialize #tran as 0, used for counting #tran!
    bdd set_of_vars = bddtrue;     // unknown set_of_vars
    bool local_simulation = false; // initialize loc_sim as false
    
    if (!G.empty()){
        DES* local_root = root->findCmp(G);
        if (local_root == nullptr){
            cerr << "Error: Local root " << G << " not found!" << endl;
            abort();
        }
          // get index of G
        int local_fdd_index = local_root->getfddDom(); // getfddDom() in des.h
        for(int i = 1; i < fdd_domainnum(); i+=2){ // index starts from 1, not 0
            if (i != local_fdd_index ) // not include the local_root
                set_of_vars &= fdd_ithset(i);
        }
        local_simulation = true;
        cout << "Open-loop behavior under the component " 
             << local_root->getName() << endl;
    }
    else { // if G is empty!
        cout << "Open loop simulation: " << endl;
    }
      // call "runRec" that is defined below
    runRec(P0, visited_states, 0, num_of_tran, local_simulation, set_of_vars);
    cout << "States: " << visited_states.size() <<
            ", Transitions: " << num_of_tran << endl;
}

void TDS::runRec(bdd current, vector<bdd>& visited_states, int curr_index,
                 int& num_of_tran, bool local, bdd &set_of_vars){
    if (local){ // if G is not empty
        cout << curr_index << ":"; 
        fdd_printset(bdd_exist(current,set_of_vars));
    }
    else {
        cout << curr_index << ":"; 
        fdd_printset(current); 
          // if G is empty, loc_sim == false, set_of_vars == empty
    }

    if ( (current & Pm) != bddfalse)
        cout << "*";
    cout << endl;
    
    for(auto& sigma:Sigma){ // for all events in the Alphabet
        bdd next = sigma.second->delta(current); 
          // forward transition of sigma, "next" is a pred
        if ( next != bddfalse ){
            num_of_tran ++;
            cout << curr_index << "-Via: " << sigma.first <<endl; 
              // "sigma.first" is a string
              // "find_if" is in <algorithm>, to find "next" in "visited_states"
            auto it = find_if(visited_states.begin(), visited_states.end(),
                      [&](auto& P){return P == next;});
              // "next_index" is the distance between 
              // "visited_states.begin()" and "next", namely the index
            int next_index = distance(visited_states.begin(),it);
            if (it == visited_states.end()){ // if not found, not visited yet
                visited_states.push_back(next);
                runRec(next, visited_states, next_index, num_of_tran, local, set_of_vars);
            }
            else if (local){
                cout << next_index << ":"; 
                fdd_printset(bdd_exist(next, set_of_vars)); 
                cout << endl;
            }
            else {
                cout << next_index << ":"; 
                fdd_printset(next); 
                  // if local == false, then set_of_vars == empty
                cout << endl;
            }
         }
    }
}

  /* specification given in dijuntive form
   * predicate corresponding to illegal set of states */
   
  // read spec.h and spec.cpp first
void TDS::supcon(string file_path){
    if(!init_set)
        setInit();
    bdd P = spec::readSpec1File(file_path, this);
    P &= spec::readSpec2File(file_path, this);
//  fdd_printset(P); cout << endl;         // used for testing spec
    createSupC2P(P);                       // defined below
//  fdd_printset(supC2P); cout << endl;    // used for testing supC2P
    for(auto& sigma:Sigma)
        sigma.second->setFSigma(supC2P);
}

  // consistent with computation algorithm in theory
void TDS::createSupC2P(bdd& P){
    bdd newBDD1 = P;
    bdd newBDD2 = P;
    do{
       newBDD1 = newBDD2;
       bdd temp = supCP(newBDD1);  // defined below
       newBDD2 = P & CR(temp);     // defined below
    }while( newBDD1 != newBDD2);   // when equal, terminate, we got the SUP
                                   // defined as Omega_p(K)
    supC2P = newBDD2;
}

  // consistent with algorithm of CR(G,.) in theory
bdd TDS::CR(bdd& P){
    bdd newBDD1 = P & Pm;
    bdd newBDD2 = P & Pm;
    do{
        newBDD1 = newBDD2;
        for(auto& sigma:Sigma){
            newBDD2 |= (P & sigma.second->gamma(newBDD1));
        }
    }while( newBDD1 != newBDD2);
    return newBDD2;
}

  // supCP(P) = neg([neg(P)])
bdd TDS::supCP(bdd& P){
    bdd temp = bdd_not(P);
    return bdd_not(Bracket(temp));
}

  // [.]
bdd TDS::Bracket(bdd& P){
    bdd newBDD1 = P;
    bdd newBDD2 = P;
    do{
        newBDD1 = newBDD2;
        for(auto& sigma:Sigma){
            if(!sigma.second->isCtrb()){
                newBDD2 |= sigma.second->gamma(newBDD1);
            }
        }
    }while( newBDD2 != newBDD1);
    return newBDD2;
}

void TDS::runUnderControl(){
    cout << "Closed loop simulation: " << endl;
    if(!init_set)
        setInit();
    vector<bdd> visited_states; // vector of bdd
    if ((P0 & supC2P) == bddfalse){
        cout << "Closed behavior is empty!" << endl;
        return;
    }
    visited_states.push_back(P0);
    int num_of_tran = 0;
    runUnderControlRec(P0, visited_states, 0, num_of_tran); // defined below
    cout << "States: " << visited_states.size() <<
            ", Transitions: " << num_of_tran << endl;
}

void TDS::runUnderControlRec(bdd current, vector<bdd>& visited_states, 
                             int curr_index, int& num_of_tran){
    cout << curr_index << ":"; fdd_printset(current);
    if ((current & Pm) != bddfalse)
        cout << "*";
    cout << endl;

    for(auto& sigma:Sigma){
        if((sigma.second->getFSigma() & current) != bddfalse){ 
          // f_sigma is a predicate
          // if f_sigma(q)=1, then sigma is enabled to occur at q.
            bdd next = sigma.second->delta(current);
            if (next != bddfalse){
                num_of_tran ++;
                cout << curr_index << "-Via: " << sigma.first << endl;
                auto it = find_if(visited_states.begin(), visited_states.end(),
                          [&](auto& P){return P == next;});
                int next_index = distance(visited_states.begin(),it);

                if (it == visited_states.end()){
                    visited_states.push_back(next);
                    runUnderControlRec(next, visited_states, 
                                       next_index, num_of_tran);
                }
                else {
                    cout << next_index << ": "; 
                    fdd_printset(next);
                    cout << endl;
                }
            }
        }
    }
}

void TDS::print(){
    cout << *root;
}

void TDS::printControlData(string file_path){
    FILE* controlled_behavior;
    string directory = file_path + "/results/controlled_behavior.txt";
    controlled_behavior = fopen(directory.c_str(),"w");
    if (controlled_behavior == nullptr){
        cerr << "Error: controlled_behavior cannot be created!" << endl;
        abort();
    }
    fdd_fprintset(controlled_behavior,supC2P); 
      // Prints the BDD "r" to "ofile" using a set notation
    fclose(controlled_behavior); // one txt for controlled_behavior
    for(auto& sigma: Sigma){ // one txt for each ctrb event
        if (sigma.second->isCtrb()){
            FILE* sigmaEN;
            string temp_dir = file_path + "/results/" + 
                              sigma.second->getName() + ".txt";
            sigmaEN = fopen(temp_dir.c_str(),"w");
            fdd_fprintset(sigmaEN, sigma.second->getFSigma());
            fclose(sigmaEN);
        }
    }

}
