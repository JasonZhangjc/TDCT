#include "event.h"

  // Constructors
event::event():n_sigma{bddtrue}, set_of_src_vars{bddtrue},
    set_of_tgt_vars{bddtrue}, f_sigma{bddtrue}{}
    
event::event(string sigma): name{sigma}, ctrb{true}, n_sigma{bddtrue},
    set_of_src_vars{bddtrue}, set_of_tgt_vars{bddtrue}, f_sigma{bddtrue}{}
    
event::event(string sigma, bool _ctrb): name{sigma},
    set_of_src_vars{bddtrue}, set_of_tgt_vars{bddtrue},
    ctrb{_ctrb}, n_sigma{bddtrue}, f_sigma{bddtrue}{}
    
  // other methods
string event::getName(){return name;}

string event::printName(){
    string ctrb = (this->isCtrb())? "(con)":"(unc)";
    return this->getName()+ctrb;
}

bool event::isCtrb(){return ctrb;}

void event::addContainer(DES* G){
    container.insert(G);
}

void event::insertSrc(int i){src_vars.insert(i);}  // insert ID of the variable
void event::insertTgt(int i){tgt_vars.insert(i);}  // insert ID of the variable
void event::setNSigma(bdd P){n_sigma &= P;}        // n_sigma = n_sigma & P
bdd  event::getNSigma(){return n_sigma;}

void event::setVarSets(){
    psrc_to_src = bdd_newpair();
    src_to_psrc = bdd_newpair();
    vector<int> temp1, temp2, temp3, temp4; // need 4 temps!
      // if use back_inserter, then the order is kept.
      // copy vars from a "set" to a "vector"
    copy(src_vars.begin(), src_vars.end(), back_inserter(temp1));
    copy(tgt_vars.begin(), tgt_vars.end(), back_inserter(temp3));
      // Unclear
    for(auto& i:temp1){
          // copy from a "vector" to a "bdd"
        set_of_src_vars &= fdd_ithset(i-1);     // source: i-1
        temp2.push_back(i - 1);
    }

    for(auto& i:temp3){
        set_of_tgt_vars &= fdd_ithset(i);       // target: i 
        temp4.push_back(i - 1);
    }
      // "fdd_setpairs" defines n pairs for finite domain blocks.
      // "bddPair" is used for "bdd_replace"
      // source == prime == i-1 
      // target == non-prime == i 
    fdd_setpairs(src_to_psrc,&temp1[0], &temp2[0], temp1.size()); 
    fdd_setpairs(psrc_to_src,&temp2[0], &temp1[0], temp1.size()); 
}

  // Those two transition functions are consistent with theory
  // remove i-1 and remain i
  // Forward transition function
bdd event::delta(bdd pred){
    return bdd_exist( // "bdd_exist": Removes all occurences in r of variables 
                      // in the set var by existential quantification.
                     bdd_replace(pred,src_to_psrc) & n_sigma,      
                     set_of_src_vars); // bdd_replace(BDD r,bddPair* pair)                 
}

  // gamma
  // Backward transition function
bdd event::gamma(bdd pred){
    return bdd_replace(// first remove all occurences in pred & n_sigma of vars
    			    // in set_of_tgt_vars, then replace from prime to non-prime
                       bdd_exist( pred & n_sigma,
                       set_of_tgt_vars), psrc_to_src);
}

bdd event::getFSigma(){return f_sigma;}

  // shown in theory
void event::setFSigma(bdd P){
    bdd next_G = bdd_exist(n_sigma,set_of_src_vars);
    bdd n_good = next_G & P;
    f_sigma = this->gamma(n_good);
}

/*
 * This method is used to handle type2 specifications.
 * P is the predicate at which this event must not occur.
 * If event is controllable, we modify its transition predicate,
 * else, we return the conjunction of P and the eligbility predicate;
 */
 
 /* if sigma is controllable, then disable it at source
  * if sigma is unctrb, then prevent it from reaching source */
bdd event::handleIllegalPred(bdd& P){
    bdd ret_BDD = bddfalse;
    if (this->isCtrb()){
        n_sigma &= bdd_not(bdd_replace(P,src_to_psrc) //"bdd_not" Negates a bdd
                           & n_sigma);
    }
    else{
        ret_BDD = bdd_replace(
                    bdd_exist(
                        bdd_replace(P,src_to_psrc)&n_sigma,
                        set_of_tgt_vars),
                    psrc_to_src);
    }
      // ret_BDD is actually the pred of sigma source
    return ret_BDD; // return the "illegal" pred
}

bool eCompare::operator()(const ePtr& e1, const ePtr& e2)const{
    return e1->getName() < e2->getName();
}
