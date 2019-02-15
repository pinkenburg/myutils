#ifndef MYROOTHIT_H
#define MYROOTHIT_H


#include <phool/PHObject.h>
#include <cmath>
#include <map>
#include <set>

class MyRootHit : public PHObject
{
 public:
  
  virtual ~MyRootHit(){}

  virtual void identify(std::ostream& os = std::cout) const {
    os << "MyRootHit base class" << std::endl;
  }
  
  virtual void add_edep(const double edep, const double e, const double light_yield) {return;}

  virtual void set_key(const unsigned int) {return;}
  virtual unsigned int get_key() const {return 0xFFFFFFFF;}

  virtual short get_column() const {return 0xFFFF;}
  virtual short get_row() const {return 0xFFFF;}

  virtual double get_edep() const {return NAN;}
  virtual double get_eion() const {return NAN;}
  virtual double get_light_yield() const  {return NAN;}
  
 protected:

  MyRootHit() {}
  ClassDef(MyRootHit,1)
};

#endif
