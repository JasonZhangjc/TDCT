#include "event.h"

  // Constructors
event::event(): n_sigma{bddtrue}, set_of_src_vars{bddtrue},
                set_of_tgt_vars{bddtrue}, f_sigma{bddtrue}{}
          
event::event(string sigma): name{sigma}, ctrb{true}, n_sigma{bddtrue},
                            set_of_src_vars{bddtrue}, set_of_tgt_vars{bddtrue},
                            f_sigma{bddtrue}{}

event::event(string sigma, bool _ctrb): name{sigma}, set_of_src_vars{bddtrue},
                                        set_of_tgt_vars{bddtrue}, ctrb{_ctrb},
                                        n_sigma{bddtrue}, f_sigma{bddtrue}{}
                                       
  // Other methods
string event::getName(){return name;}

string event::printName(){
	string ctrb = (this->isCtrb()) ? "(con)" : "(unc)";
	return this->getName() + ctrb;
}

bool event::isCtrb(){return ctrb;}

void event::addContainer(DES* G){
	container.insert(G);
}

void event::insertSrc(int i){src_vars.insert(i);}

void event::insertTgt(int i){tgt_vars.insert(i);}

void event::setNSigma(bdd P){n_sigma &= P;}

bdd event::getNSigma(){return n_sigma;}

void event::setFSigma(bdd P){
	bdd next_G = bdd_exist(n_sigma, set_of_src_vars);
	bdd n_good = next_G & P;
	f_sigma = this->gamma(n_good);
}

bdd event::getFSigma(){return f_sigma;}

void event::setVarSets(){
	psrc_to_src = bdd_newpair();
	src_to_psrc = bdd_newpair();
	vector<int> temp1, temp2, temp3, temp4;
	
	copy(src_vars.begin(), src_vars.end(), back_inserter(temp1));
	copy(tgt_vars.begin(), tgt_vars.end(), back_inserter(temp3));
	for(auto& i:temp1){
		set_of_src_vars &= fdd_ithset(i-1); // v_G'
		temp2.push_back(i-1);
	}
	for(auto& i:temp3){
		set_of_tgt_vars &= fdd_ithset(i);
		temp4.push_back(i-1);
	}	
	fdd_setpairs(src_to_psrc, &temp1[0], &temp2[0], temp1.size());
	fdd_setpairs(psrc_to_src, &temp2[0], &temp1[0], temp1.size());
}

bdd event::delta(bdd pred){
	return bdd_exist(bdd_replace(pred, src_to_psrc) & n_sigma, set_of_src_vars);
	// v to v', and then eliminate all v' since set_of_src_vars only contains v'
}

bdd event::gamma(bdd pred){
	return bdd_replace(bdd_exist(pred & n_sigma, set_of_tgt_vars), psrc_to_src);
	// eliminate all v first, since set_of_tgt_vars only contains v
	// then replace v' by v
}

bdd event::handleIllegalPred(bdd& P){
	bdd ret_bdd = bddfalse;
	if(this->isCtrb()){
		n_sigma &= bdd_not(bdd_replace(P, src_to_psrc) & n_sigma); 
	}
	else{
		ret_bdd = bdd_replace(bdd_exist(bdd_replace(P, src_to_psrc) & n_sigma,
		                                            set_of_tgt_vars),
		                      psrc_to_src);
	}
	// ret_bdd is the illegal pred, should be in the form of v instead of v'
	return ret_bdd;
}


bool eCompare::operator()(const ePtr& e1, const ePtr& e2)const{
	return e1->getName() < e2->getName();
}

