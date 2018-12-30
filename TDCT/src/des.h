#ifndef DES_H
#define DES_H

#include <iostream>              // io
#include <memory>                
#include <set>                   // set template
#include <vector>
#include <algorithm>
#include "event.h"
#include "transition.h"
#include "delta.h"
#include <fstream>
#include <fdd.h>                 // bdd package

using namespace std;

extern vector<string> fdd_source_hook; // call "fdd_source_hook" from outside
void  printHandler(FILE *o, int var);  // "printHandler" is in main.cpp

enum class DEStype{SIMPLE, XOR, SYNC}; // three types of DES

  /* Since DES is an abstract class with virtual methods 
   * (some of them are pure virtual), 
   * simpleDES, xorDES and syncDES inherit the class DES. (Polymorphism) */ 
class DES{
  // A state should be considered as a DES, 
  // therefore the definition applies to every component of the system
protected:
    string name;    // name or label of the DES    e.g. G
    DES* parent;    // pointer to parent DES       e.g. The parent of G_2 is G
    int num_of_cmp; // number of components        e.g. G has two cmp: G_1, G_2
    int fdd_domain; // ID of the assigned variable         e.g. V_G2
    int fdd_state;  // value of the parent variable        e.g. g_21
    bdd add_pred;   // bdd used for encoding the path to the root in a TDS
                    // e.g. g_21 -> G_2 -> G is the path to the root G
      // Eventually the add_pred should be (v_G = G_i) & ... & (v_parent = this)
                            
public:
      // Constructors
    DES();
    DES(string _name);
    DES(string _name, DES* _parent, int noc); // noc is the number of component                   
    DES(string _name, DES* _parent, int noc, int _fdd_state);

	  // Other methods
    void setfddState(int i);
    int getfddState();

    string getName()const;
    virtual string printName()const;
    virtual int getCmpSize();           // cmp = component
    virtual DEStype getType()const = 0; // Using abstract class as API in C++

    void setPar(DES* _parent);          // a parent is a DES pointer
    DES* getPar();
    void setAddPred(bdd P);             // a predicate is a BDD
    bdd  getAddPred();

    virtual void setfddDom(int i);
    virtual int getfddDom();
    virtual DES* addCmp(DES* T);        
    virtual void addEvent(event* sigma);
    virtual void addDelta(delta* d);
    virtual bdd theta(DES* G, bool source = false, event* sigma = nullptr);
    virtual bdd initPred();                        
    virtual bdd markPred();                        
    virtual bool isInit();                         
    virtual bool isMark();                         
    virtual DES* findCmp(string _name); 

      // printing functions
    virtual ostream& print(ostream& out)const = 0;          // abstract class
    friend ostream& operator<<(ostream& out, const DES& T); // rewrite <<
};



typedef unique_ptr<DES> DESPtr; // smart pointer, in <memory>
class DESCompare{
public:
    bool operator()(const DESPtr& p1, const DESPtr& p2); 
      // rewrite () in DESCompare
	  // return (p1->getName() < p2->getName()); 
};



  // SIMPLE DES
class simpleDES: public DES{
private:
    bool initial; // default = false
    bool marker;  // default = false
	
public:
    simpleDES(string _name, DES* _parent, int _fddState,
              bool _initial = false, bool _marker = false);
    bool isInit();
    bool isMark();
    string printName()const;
    DEStype getType()const;
    ostream& print(ostream& out) const;
};



  // xorDES is the most complicated class here
class xorDES: public DES{
private:
      // set of DESPtr; order DES pointers by name in ascending order
    set<DESPtr, DESCompare> components;  
    set<event*> Sigma; // Alphabet of event labels, linker events
    dPtr tran_struct;  // dPtr is defined in delta.h
	
public:
    xorDES(string _name, DES* _parent, int noc, int _fdd_state);
    DEStype getType()const;
    void setfddDom(int i);
    int getfddDom();
    int getCmpSize();
      /* adding components: if T is already in the compenent set, 
       * a pointer to T will be returned; otherwise
       * a unique pointer of T is created and added to the component set 
       * and a pointer to this newly added component will be returned. */
    DES* addCmp(DES* T);                                   
    DES* findCmp(string G);                                
    void addEvent(event* sigma);                           
    void addDelta(delta* d);                               
    bdd initPred();                                        
    bdd markPred();
      // theta_G(q): if source == true, primed variables are used to encode!
      // "theta" is the state encoding, and "N" is the transition encoding
    bdd theta(DES* G, bool source = false, event* sigma = nullptr);
      // Prints components and transitions.
    ostream& print(ostream& out) const;
};


  // SYNC DES
class syncDES: public DES{
private:
    set<DESPtr, DESCompare> components;
public:
	  // constructor
    syncDES(string _name, DES* _parent, int noc , int _fdd_state);
	  // other methods
    int getCmpSize();
    DES* addCmp(DES* T);
    DES* findCmp(string G);
    bdd initPred();
    bdd markPred();
    DEStype getType()const;
    ostream& print(ostream& out) const;
};

#endif // DES_H
