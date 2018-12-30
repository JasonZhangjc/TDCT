#include "des.h"


vector<string> fdd_source_hook;

void  printHandler(FILE *o, int var){
    fprintf(o, "%s", fdd_source_hook[var].c_str()); // "c_str()": C++ to C
}


  // DES class methods:
  // Construcctors
DES::DES(): name{""}, parent{nullptr}, add_pred{bddtrue}{}
DES::DES(string _name): name{_name}, parent{nullptr},
    num_of_cmp{0}, add_pred{bddtrue}{}              // bddtrue is default   
DES::DES(string _name, DES* _parent, int noc): name{_name},
    parent{_parent}, num_of_cmp{noc}, add_pred{bddtrue}{}    
  // add_pred is more like the "active compnent“
  // add_pred: from root to current DES
DES::DES(string _name, DES* _parent, int noc, int _fdd_state): name{_name},
    parent{_parent}, num_of_cmp{noc}, fdd_state{_fdd_state}{
      // if the DES is the root, then "add_pred" is bddtrue
    if (_parent ==  nullptr)
        add_pred = bddtrue;
      // if the DES is a cmp of a syncDES, the "add_pred" inherits its parent
    else if (_parent->getType() == DEStype::SYNC)
        add_pred = _parent->getAddPred();
      // if the DES is a cmp of an xorDES, then the "add_pred" is
      // (add_pred of its parent) & (v_parent = this)
      // Eventually add_pred should be (v_G = G_i) & ... & (v_parent = this)
    else
        add_pred = _parent->getAddPred() &          // set parent to this state
                    fdd_ithvar(_parent->getfddDom(), _fdd_state); 
}

  // Other public methods:
void DES::setfddState(int i){ fdd_state = i;} // ID of current DES w.r.t parent
int DES::getfddState(){return fdd_state;}
string DES::getName()const{return name;}
string DES::printName()const {return name;}
int DES::getCmpSize(){return 0;}
void DES::setPar(DES* _parent){parent = _parent;}
DES* DES::getPar(){return parent;}
void DES::setAddPred(bdd P){add_pred = P;}         
bdd  DES::getAddPred(){return add_pred;}

void DES::setfddDom(int i){
    cerr << "Error: setfddDom called on " << this->getName() << "!" << endl;
    abort();
}
int DES::getfddDom(){
    cerr << "Error: getfddDom called on " << this->getName() << "!" << endl;
    abort();
}
DES* DES::addCmp(DES* T){
    cerr << "Error: addCmp called on " << this->getName() << "." << endl;
    abort();
}
void DES::addEvent(event* sigma){
    cerr << "Error: addEvent called on " << this->getName() << "." << endl;
    abort();
}
void DES::addDelta(delta* d){
    cerr << "Error: addDelta called on " << this->getName() << "." << endl;
    abort();
}
bdd DES::theta(DES* G, bool source, event* sigma){
    cerr << "Error: theta called on " << this->getName() << "." << endl;
    abort();
}
bdd DES::initPred(){
    cerr << "Error: initPred called on " << this->getName() << "." << endl;
    abort();
}
bdd DES::markPred(){
    cerr << "Error: markPred called on " << this->getName() << "." << endl;
    abort();
}

bool DES::isInit(){return false;}
bool DES::isMark(){return false;}
DES* DES::findCmp(string _name){return nullptr;}
ostream& operator<<(ostream& out, const DES& T) {return T.print(out);} 



  // Be used to decide the order of eles in set "components" 
bool DESCompare::operator()(const DESPtr& p1, const DESPtr& p2){
    return p1->getName() < p2->getName();
}



  // simpleDES class methods:
simpleDES::simpleDES(string _name, DES* _parent, int _fdd_state,
    bool _initial, bool _marker):
	DES(_name, _parent, 0, _fdd_state),initial{_initial}, marker{_marker} {}

bool simpleDES::isInit(){return initial;}
bool simpleDES::isMark(){return marker;}

string simpleDES::printName()const {
    string pr_name = name;
    if (marker) pr_name += "*";
    if (initial) pr_name += "(i)";
    return pr_name;
}

DEStype simpleDES::getType()const{return DEStype::SIMPLE;}

ostream& simpleDES::print(ostream& out) const{
    out << this->getName(); 
    return out;
}



  // xorDES class methods
  // constructor
  // every time when construct an xorDES, also create a "fdd_extdomain"
xorDES::xorDES(string _name, DES* _parent, int noc, int _fdd_state):
    DES(_name,_parent, noc, _fdd_state) {
      // add new fdd variable
      // fddDomain - 1 will be the primed variable
      // init a vector with only two eles: temp[0]==temp[1]==noc
    vector<int> temp{noc, noc};                       
      // &temp[0] is the address of temp, add to fdd
      // returns the number of finite domain blocks defined by fdd_extdomain
    fdd_extdomain(&temp[0], temp.size());   
      // which is 2-1=1         
    this->setfddDom(fdd_domainnum() - 1);             
      // add this' and this												    
    fdd_source_hook.push_back(this->getName() + "'"); 
      // "fdd_source_hook" is a vector of string
    fdd_source_hook.push_back(this->getName());       
}

  // other methods
DEStype xorDES::getType()const{return DEStype::XOR;}
void xorDES::setfddDom(int i){ fdd_domain = i;}
int xorDES::getfddDom(){return fdd_domain;}
int xorDES::getCmpSize(){return components.size();}

  // add components
DES* xorDES::addCmp(DES* T){
    DESPtr temp(T);                          // init a DES Pointer, point to T
    auto it = components.insert(move(temp)); // add temp into components
    return it.first->get();                  // return the DES just added in
}

  // find the DES G in the xorDES, if found return G, if not return nullptr
DES* xorDES::findCmp(string G){
    if (this->getName() == G)
        return this;
    for(auto& c:components){
        if( c->getName() == G)
            return c.get();
        else{
            DES* comp = c->findCmp(G); // Recursively call "findCmp"
            if(comp != nullptr)
                return comp;
        }
    }
    return nullptr;
}

void xorDES::addEvent(event* sigma){
    Sigma.insert(sigma); // check posssibility of checking local coupling
}

void xorDES::addDelta(delta* d){
    tran_struct.reset(d); // "tran_struct" is a dPtr defined in delta.h
}

  // check whether this DES is a init, or whether a init state is in this DES 
bdd xorDES::initPred(){
    for(auto& c:components){
        if (c->isInit())
            return (this->theta(c.get()) & add_pred); 
              // add_pred is encoding for current state
              // and the state has an init cmp
          // only simpleDES has init and mark, 
          // if c is not simple, it doesn't satisfy last if statement
        else if (c->getType() != DEStype::SIMPLE){
            bdd pred = c->initPred();                 // recursive
            if (pred != bddfalse)
                return pred;
        }
    }
    return bddfalse;
}

bdd xorDES::markPred(){
    bdd pred = bddfalse;
    for(auto& c:components){
        if (c->isMark())
            pred |= this->theta(c.get()); // not necessary with "prime"
              // | is or, pred will be x \/ y \/ ... \/ other marker states
        else if (c->getType() != DEStype::SIMPLE){
            pred |= c->markPred();
        }
    }
    return pred & add_pred; // return encoding of current DES & marker cmp
}

  // Very important! state encoding: theta
  // also include transition encoding: N_sigma
bdd xorDES::theta(DES* G, bool source, event* sigma){
  // usually the default of "source" is false, the default of "sigma" is nullptr
  // so no "no prime", and not related to source and target at most of times
    bdd ret_bdd = bddtrue;
    DES* curr_sys = G;
    while(curr_sys != this){
        if (curr_sys == nullptr){
            cerr << "Error in encoding " << G->getName()
                 << " inside " << this->getName() << "!" << endl;
            abort();
        }
		  // if the parent of curr_sys is a syncDES, continue,
		  // since the components of syncDES have no linker transitions
        else if ( syncDES* pt = dynamic_cast<syncDES*>(curr_sys->getPar())){
            curr_sys = curr_sys->getPar();
            continue;
        }
		  // theta_G(q): if source == true, 
		  // then primed variables are used to encode
		  // the variable of curr_sys.parent = curr_sys.state
        else if (source){ // encodes the source!
            ret_bdd &= fdd_ithvar(curr_sys->getPar()->getfddDom() - 1, 
                                 curr_sys->getfddState()); // state encoding
                                                           // i-1: prime
            if (sigma != nullptr)
            	sigma->insertSrc(curr_sys->getPar()->getfddDom());   
            	  // "insertSrc" is in event.cpp\h
                  // add curr_sys.parent to sigma.source_set
        }
        else{ // encodes the target!
              // usually the normal state encoding
            ret_bdd &= fdd_ithvar(curr_sys->getPar()->getfddDom(),
                             curr_sys->getfddState());     // state encoding
              // these two lines just put events and DES in sigma-related set
            if (sigma != nullptr)
            	sigma->insertTgt(curr_sys->getPar()->getfddDom());   
            	  // "insertTgt" is in event.cpp\h
            	  // add curr_sys.parent to sigma.target_set
        }
        curr_sys = curr_sys->getPar();  // from bottom to top
    }
    return ret_bdd;
}

ostream& xorDES::print(ostream& out) const{
      // first, output all non-simple DES that are cmp of this xorDES
    for(auto& c:components){
        simpleDES* pt = dynamic_cast<simpleDES*>(c.get()); 
          // if c is not a simpleDES, output c at once.
        if(pt == nullptr)
            out << *c;
    }
      // second, its own components are outputed.
    out << this->getName() <<"\nComponents are: " << endl;
    for(auto& c:components)
        out << c->getfddState() << ":" <<c->printName() << " ";
    out << "\nEvents are: " << endl;
    for(auto& sigma:Sigma)
        out << sigma->printName() << " ";
    out << "\nTransitions are: " << endl;
      // output transitions
    if(tran_struct != nullptr)
        tran_struct->printTranStruct(out);    
    out << "--------**------------" << endl;
    return out;
}



  // syncDES class methods
syncDES::syncDES(string _name, DES* _parent, int noc , int _fdd_state)
    :DES(_name, _parent, noc, _fdd_state){}

int syncDES::getCmpSize(){return components.size();}

DES* syncDES::addCmp(DES* T){
    DESPtr temp(T);                           
    auto it = components.insert(move(temp));
    return it.first->get();                  
}

DES* syncDES::findCmp(string G){
    for(auto& c:components){
        if( c->getName() == G)
            return c.get();            // get() is a method in set template
        else{
            DES* comp = c->findCmp(G); // recursive
            if(comp != nullptr)
                return comp;
        }
    }
    return nullptr;
}

  // call initPred in xorDES
bdd syncDES::initPred(){
    bdd pred = bddtrue;
    for(auto& c:components)
        pred &= c->initPred(); // pred = pred & initPred
    return pred;
}

  // call markPred in xorDES
bdd syncDES::markPred(){
    bdd pred = bddtrue;
    for(auto& c:components)
        pred &= c->markPred(); // pred = pred & markPred
    return pred;
}

DEStype syncDES::getType()const{return DEStype::SYNC;}

ostream& syncDES::print(ostream& out) const{
      // First, output all non-simple components.
    for(auto& c:components){
        simpleDES* pt = dynamic_cast<simpleDES*>(c.get());
        if(pt == nullptr)
            out << *c;
    }
      // Second, its own components are outputed.
      // unlike xorDES, syncDES doesn't output events
    out << this->getName() << "\nComponents are: " << endl;
    for(auto& c:components)
        out << c->getfddState() << ":" <<c->printName() << " ";
    out << "\n--------**------------" << endl;
    return out;
}


