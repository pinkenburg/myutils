#ifndef MYROOTTCCONTAINER_H__
#define MYROOTTCCONTAINER_H__

#include "MyRootHit.h"

#include <phool/PHObject.h>

#include <set>

class TClonesArray;

class MyRootTCContainer: public PHObject
{

  public:

  MyRootTCContainer();

  virtual ~MyRootTCContainer();

  void Reset();

  void identify(std::ostream& os = std::cout) const;

  void AddScintillatorSlat(const unsigned int key, MyRootHit *newscintillatorSlat);
  
  //! preferred removal method, key is currently the slat id
  void RemoveScintillatorSlat(unsigned int key) {
  }
  unsigned int size () const;

 protected:
  TClonesArray *slatmap;

  ClassDef(MyRootTCContainer,1)
};

#endif
