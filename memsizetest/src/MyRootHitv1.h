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

  void identify(std::ostream& os = std::cout) ;

  void add_edep(const float f, const float e, const float ly) {edep+=f; eion+= e; light_yield+=ly;}
  
  void set_key(unsigned int i) {key = i;}
  void set_light_yield(const float lightYield)  {light_yield = lightYield;}

  void set_x(float x0, float x1) {x[0] = x0; x[1] = x1; return;}
 void set_y(float y0, float y1) {y[0] = y0; y[1] = y1; return;}
 void set_z(float z0, float z1) {z[0] = z0; z[1] = z1; return;}
 void set_t(float t0, float t1) {t[0] = t0; t[1] = t1; return;}

 float get_x(const int i) const {return x[i];}
 float get_y(const int i) const {return y[i];}
 float get_z(const int i) const {return z[i];}
 float get_t(const int i) const {return t[i];}

  short get_row() const;
  short get_column() const;
  unsigned int get_key() const {return key;}
  float get_edep()  {return edep;}
  float get_eion()  {return eion;}
  float get_light_yield()  {return light_yield;}


 protected:
  unsigned int key;
  float x[2];
  float y[2];
  float z[2];
  float t[2];
  float edep;
  float eion;
  float light_yield;
   
  ClassDef(MyRootHitv1,1)
};

#endif
