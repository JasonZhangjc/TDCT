#ifndef DES_H
#define DES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <memory>
  // finite domain blocks
#include <fdd.h>
  // des, event, transition, delta are four main components
#include "event.h"
#include "transition.h"
#include "delta.h"

using namespace std;

extern vector<string> fdd_source_hook;
void printHandler(FILE *o, int var);

enum class DEStype{SIMPLE, 
                   XOR, 
                   SYNC};
                   
class DES{
public:
  	  // Construnctor
  	DES();
  	DES(string _name);
  	DES(string _name, DES* _parent, int noc);
  	DES(string _name, DES* _parent, int noc, int _fdd_State);
  	  // Other methods
  	  // Name relevant
  	string getName()const;
  	virtual string printName()const; // if not specific, cannot print name
  	  // Parent relevant
  	void setPar(DES* _parent);
  	DES* getPar();
  	  // Component relevant       // if not specific, cannot handle Cmp
  	virtual int getCmpSize();
  	virtual DES* addCmp(DES* T);
  	virtual DES* findCmp(string _name);
  	  // fdd_domain relevant      // if not specific, cannot handle fdd_domain
  	virtual void setfddDom(int i);   
  	virtual int getfddDom();
  	  // fdd_state relevant
  	void setfddState(int i);
  	int getfddState();
  	  // add_pred relevant
  	void setAddPred(bdd P);
  	bdd getAddPred();
  	  // Type relevant
  	virtual DEStype getType()const = 0; // pure virtual func for type
  	  // Event relevant
  	virtual void addEvent(event* sigma);
  	  // delta relevant
  	virtual void addDelta(delta* d);
  	  // theta relevant
  	virtual bdd theta(DES* G, bool source = false, event* sigma = nullptr);
  	  // Initial relevant
    virtual bool isInit();
    virtual bdd initPred();
      // Marker relevent
    virtual bool isMark();
    virtual bdd markPred();
      // Print relevant
    virtual ostream& print(ostream& out)const = 0;
    friend ostream& operator<<(ostream& out, const DES& T); // << overload

protected:
	string name;
	DES* parent;
	int num_of_cmp;
	int fdd_domain; // ID
	int fdd_state;  // state
	bdd add_pred;
};


typedef unique_ptr<DES> DESPtr;
class DESCompare{
public:
	bool operator()(const DESPtr& p1, const DESPtr& p2);
};


  // SIMPLE DES
class simpleDES: public DES{
public:
 	  // Constructor
 	simpleDES(string _name, DES* _parent, int _fdd_state, 
 	          bool _initial = false, bool _marker = false);
 	bool isInit();
 	bool isMark();
 	string printName()const; // virtual in DES class, overload
 	DEStype getType()const;
 	ostream& print(ostream& out)const;
 	
private:
	bool initial;
	bool marker;
};


  // XOR DES
class xorDES: public DES{
public:
  	  // Constructor
	xorDES(string _name, DES* _parent, int noc, int _fdd_state);
	  // Other methods
	DEStype getType()const;
	void setfddDom(int i);
	int getfddDom();
	
	int getCmpSize();
	DES* addCmp(DES* T);
	DES* findCmp(string G);
	
	void addEvent(event* sigma);
	
	void addDelta(delta* d);
	
	bdd initPred();
	bdd markPred();
	
	bdd theta(DES* G, bool source = false, event* sigma = nullptr);
	
	ostream& print(ostream& out)const;	
	
private:
	set<DESPtr, DESCompare> components;
	set<event*> Sigma;
	dPtr tran_struct; // delta
};


  // SYNC DES
class syncDES: public DES{
public:
	  // Constructor
	syncDES(string _name, DES* _parent, int noc, int _fdd_state);
	  // Other methods
	DEStype getType()const;
	
	int getCmpSize();
	DES* addCmp(DES* T);
	DES* findCmp(string G);
	
	bdd initPred();
	bdd markPred();
	
	ostream& print(ostream& out)const;
	
private:
	set<DESPtr, DESCompare> components;
};


#endif // DES_H
