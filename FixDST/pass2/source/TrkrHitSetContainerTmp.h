#ifndef TRACKBASE_TRKRHITSETCONTAINERTMP_H
#define TRACKBASE_TRKRHITSETCONTAINERTMP_H

#include <trackbase/TrkrDefs.h>        // for hitsetkey, TrkrId

#include <phool/PHObject.h>

#include <iostream>          // for cout, ostream
#include <map>
#include <utility>           // for pair

class TrkrHitSetTmp;

/**
 * Container for TrkrHitSetTmp objects
 */
class TrkrHitSetContainerTmp : public PHObject
{
 public:
  typedef std::map<TrkrDefs::hitsetkey, TrkrHitSetTmp *> Map;
  typedef Map::iterator Iterator;
  typedef Map::const_iterator ConstIterator;
  typedef std::pair<Iterator, Iterator> Range;
  typedef std::pair<ConstIterator, ConstIterator> ConstRange;

  //! ctor
  TrkrHitSetContainerTmp();

  //! dtor
  virtual ~TrkrHitSetContainerTmp();
  //! PHObject functions
  void Reset();
  void identify(std::ostream &os = std::cout) const;

  //! Add a TrkrHitSet to the container
  ConstIterator addHitSet(TrkrHitSetTmp *newHit);
  ConstIterator addHitSetSpecifyKey(const TrkrDefs::hitsetkey key, TrkrHitSetTmp *newHit);

  //! preferred removal method, key is currently the hit id
  void removeHitSet(TrkrDefs::hitsetkey key)
  {
    m_hitmap.erase(key);
  }

  //! inefficent, use key where possible instead
  void removeHitSet(TrkrHitSetTmp *hit)
  {
    Iterator its = m_hitmap.begin();
    Iterator last = m_hitmap.end();
    for (; its != last;)
    {
      if (its->second == hit)
      {
        m_hitmap.erase(its++);
      }
      else
      {
        ++its;
      }
    }
  }

  //! find or add HitSet
  Iterator findOrAddHitSet(TrkrDefs::hitsetkey key);

  //! return all HitSets matching a given detid
  ConstRange getHitSets(const TrkrDefs::TrkrId trackerid) const;

  //! return all HitSets matching a given detid, layer
  ConstRange getHitSets(const TrkrDefs::TrkrId trackerid, const char layer) const;

  //! return all HitSets
  ConstRange getHitSets(void) const;

  //! return a given HitSet based on its key
  TrkrHitSetTmp *findHitSet(TrkrDefs::hitsetkey key);

  unsigned int size(void) const
  {
    return m_hitmap.size();
  }

 protected:
  Map m_hitmap;
  ClassDef(TrkrHitSetContainerTmp, 1)
};

#endif //TRACKBASE_TRKRHITSETCONTAINERTMP_H
