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

  virtual void identify(std::ostream& os = std::cout)  {
    os << "MyRootHit base class" << std::endl;
  }
  
  virtual void add_edep(const float edep, const float e, const float light_yield) {return;}

  virtual void set_key(const unsigned int) {return;}
  virtual unsigned int get_key() const {return 0xFFFFFFFF;}

  virtual short get_column() const {return 0xFFFF;}
  virtual short get_row() const {return 0xFFFF;}

  virtual void set_x(float x0, float x1) {return;}
  virtual void set_y(float y0, float y1) {return;}
  virtual void set_z(float z0, float z1) {return;}
  virtual void set_t(float t0, float t1) {return;}

  virtual float get_x(const int i) const {return NAN;}
  virtual float get_y(const int i) const {return NAN;}
  virtual float get_z(const int i) const {return NAN;}
  virtual float get_t(const int i) const {return NAN;}

  virtual float get_edep()  {return NAN;}
  virtual float get_eion()  {return NAN;}
  virtual float get_light_yield()   {return NAN;}
  
 protected:

  MyRootHit() {}
  ClassDef(MyRootHit,1)
};

#endif
