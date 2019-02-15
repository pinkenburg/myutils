#ifndef MYROOTHITV1_H
#define MYROOTHITV1_H

#include "MyRootHit.h"

#include <cmath>
#include <set>
#include <map>

class MyRootHitv1 : public MyRootHit
{
 public:

  MyRootHitv1();
  virtual ~MyRootHitv1(){}

  void identify(std::ostream& os = std::cout) const;

  void add_edep(const double f, const double e, const double ly) {edep+=f; eion+= e; light_yield+=ly;}
  
  void set_key(unsigned int i) {key = i;}
  void set_light_yield(const double lightYield)  {light_yield = lightYield;}

  short get_row() const;
  short get_column() const;
  unsigned int get_key() const {return key;}
  double get_edep() const {return edep;}
  double get_eion() const {return eion;}
  double get_light_yield() const {return light_yield;}


 protected:
  unsigned int key;
  double edep;
  double eion;
  double light_yield;
   
  ClassDef(MyRootHitv1,1)
};

#endif
