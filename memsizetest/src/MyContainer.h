#ifndef MYCONTAINER_H__
#define MYCONTAINER_H__

#include "MyHit.h"

#include <iostream>
#include <map>
#include <set>

class MyContainer
{

  public:
  typedef std::map<unsigned int,MyHit *> Map;
  typedef Map::iterator Iterator;
  typedef Map::const_iterator ConstIterator;
  typedef std::pair<Iterator, Iterator> Range;
  typedef std::pair<ConstIterator, ConstIterator> ConstRange;
  typedef std::set<int>::const_iterator LayerIter;
  typedef std::pair<LayerIter, LayerIter> LayerRange;

  MyContainer();

  virtual ~MyContainer() {}

  void Reset();

  void identify(std::ostream& os = std::cout) const;

  ConstIterator AddScintillatorSlat(const unsigned int key, MyHit *newscintillatorSlat);
  
  //! preferred removal method, key is currently the slat id
  void RemoveScintillatorSlat(unsigned int key) {
    slatmap.erase(key);
  }

  unsigned int size( void ) const
  { return slatmap.size(); }

 protected:
  Map slatmap;

};

#endif
