#ifndef MYROOTCONTAINER_H__
#define MYROOTCONTAINER_H__

#include "MyRootHit.h"

#include <phool/PHObject.h>

#include <map>
#include <set>

class MyRootContainer: public PHObject
{

  public:
  typedef std::map<unsigned int,MyRootHit *> Map;
  typedef Map::iterator Iterator;
  typedef Map::const_iterator ConstIterator;
  typedef std::pair<Iterator, Iterator> Range;
  typedef std::pair<ConstIterator, ConstIterator> ConstRange;
  typedef std::set<int>::const_iterator LayerIter;
  typedef std::pair<LayerIter, LayerIter> LayerRange;

  MyRootContainer();

  virtual ~MyRootContainer() {}

  void Reset();

  void identify(std::ostream& os = std::cout) const;

  ConstIterator AddScintillatorSlat(const unsigned int key, MyRootHit *newscintillatorSlat);
  
  //! preferred removal method, key is currently the slat id
  void RemoveScintillatorSlat(unsigned int key) {
    slatmap.erase(key);
  }

  unsigned int size( void ) const
  { return slatmap.size(); }

 protected:
  Map slatmap;

  ClassDef(MyRootContainer,1)
};

#endif
