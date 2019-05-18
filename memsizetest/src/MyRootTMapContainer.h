#ifndef MYROOTTMAPCONTAINER_H__
#define MYROOTTMAPCONTAINER_H__

#include "MyRootHit.h"

#include <phool/PHObject.h>

#include <TMap.h>

class MyRootTMapContainer: public PHObject
{

  public:

  MyRootTMapContainer();

  virtual ~MyRootTMapContainer() {}

  void Reset();

  void identify(std::ostream& os = std::cout) const;

  void AddScintillatorSlat(const unsigned int key, MyRootHit *newscintillatorSlat);
  
  //! preferred removal method, key is currently the slat id
  /* void RemoveScintillatorSlat(unsigned int key) { */
  /*   slatmap.DeleteEntry(key); */
  /* } */

  unsigned int size( void ) const
  { return slatmap.Capacity(); }

 protected:
  TMap slatmap;

  ClassDef(MyRootTMapContainer,1)
};

#endif
