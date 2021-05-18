/**
 * @file trackbase/TrkrHitSetTmp.h
 * @author D. McGlinchey
 * @date 4 June 2018
 * @brief Container for storing TrkrHit's
 */
#ifndef TRACKBASE_TRKRHITSETTMP_H
#define TRACKBASE_TRKRHITSETTMP_H

#include <trackbase/TrkrDefs.h>

#include <phool/PHObject.h>

#include <iostream>
#include <map>
#include <utility>           // for pair

class TrkrHitTmp;

/**
 * @brief Container for storing TrkrHitTmp's
 *
 * Container object which stores a set of TrkrHitTmp objects.
 * A single TrkrHitSetTmp is meant to represent a geometric detector object
 * which bounds clustering. Therefore, a TrkrHitSetTmp should contain all
 * TrkrHits which could belong the the same cluster.
 */
class TrkrHitSetTmp : public PHObject
{
 public:
  // iterator typedef
  typedef std::map<TrkrDefs::hitkey, TrkrHitTmp*> Map;
  typedef Map::const_iterator ConstIterator;
  typedef std::pair<ConstIterator, ConstIterator> ConstRange;
  
  //! ctor
  TrkrHitSetTmp();
  //! dtor
  virtual ~TrkrHitSetTmp();
  //! TObject functions
  void identify(std::ostream& os = std::cout) const;
  void Reset();
  void print() const;

  /**
   * @brief Set the key for this object
   * @param key
   */
  void setHitSetKey(const TrkrDefs::hitsetkey key) { m_hitSetKey = key; }

  /**
   * @brief Get the key for this object
   * @param[out] object key
   */
  TrkrDefs::hitsetkey getHitSetKey() const { return m_hitSetKey; }

  /**
   * @brief Add a hit to this container using a specific key.
   * @param[in] key Hit key
   * @param[in] hit Hit to be added.
   *
   * NOTE: This TrkrHitSetTmp takes ownership of the passed TrkrHit pointer
   * and will delete it in the Reset() method.
   */
  ConstIterator addHitSpecificKey(const TrkrDefs::hitkey key, TrkrHitTmp* hit);

  /**
   * @brief Remove a hit using its key
   * @param[in] key to be removed
   */
  void removeHit(TrkrDefs::hitkey key);

  /**
   * @brief Get a specific hit based on its index.
   * @param key of the desired hit
   * @param[out] Pointer to the desired hit. nullptr if no hit.
   *
   * Get a desired hit based on its key.
   */
  TrkrHitTmp* getHit(const TrkrDefs::hitkey key);
  
  /**
   * @brief Get all hits
   * @param[out] Pair of iterator to vector begin and end
   */
  ConstRange getHits();

  /**
   * @brief Get the number of hits stored
   * @param[out] number of hits
   */
  // Get number of hits
  unsigned int size() { return m_hits.size(); }
   
 private:
  TrkrDefs::hitsetkey m_hitSetKey; /// unique key for this object
  Map m_hits; /// storage for TrkrHitTmp objects
  ClassDef(TrkrHitSetTmp, 1);
};

#endif //TRACKBASE_TRKRHITSETTMP_H
