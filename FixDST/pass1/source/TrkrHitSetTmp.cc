/**
 * @file trackbase/TrkrHitSetTmp.cc
 * @author D. McGlinchey
 * @date June 2018
 * @brief Implementation of TrkrHitSetTmp
 */
#include "TrkrHitSetTmp.h"

#include "TrkrHitTmp.h"

#include <cstdlib>     // for exit
#include <iostream>
#include <type_traits>  // for __decay_and_strip<>::__type


TrkrHitSetTmp::TrkrHitSetTmp()
  : m_hitSetKey(TrkrDefs::HITSETKEYMAX)
  , m_hits()
{
}

TrkrHitSetTmp::~TrkrHitSetTmp()
{
  // frees the memory associated with the pointers gto the TrkrHitTmp objects
  Reset();
}

void TrkrHitSetTmp::print() const
{
  identify(std::cout);
}

void TrkrHitSetTmp::Reset()
{
  m_hitSetKey = TrkrDefs::HITSETKEYMAX;
  
  while ( m_hits.begin() != m_hits.end() )
  {
    delete (m_hits.begin())->second;
    m_hits.erase(m_hits.begin());
  }
  
  return;
}

void TrkrHitSetTmp::identify(std::ostream& os) const
{
  int layer = TrkrDefs::getLayer(getHitSetKey());
  int trkrid =  TrkrDefs::getTrkrId(getHitSetKey());    
  os << "TrkrHitSetTmp: "   << "       hitsetkey " << getHitSetKey() << " TrkrId " << trkrid << " layer " << layer << " nhits: " << m_hits.size() << std::endl;

  for ( auto& entry : m_hits )
  {
    std::cout << " hitkey " << entry.first << std::endl;
    (entry.second)->identify(os);
  }
}


void TrkrHitSetTmp::removeHit(TrkrDefs::hitkey key)
{

  TrkrHitSetTmp::ConstIterator it = m_hits.find(key);

  if (it != m_hits.end())
  {
    delete it->second;
    m_hits.erase(key);
  }
  else
  {
    identify();
    std::cout << "TrkrHitSetTmp::removeHit: deleting a nonexist key: " << key << " exiting now" << std::endl;
    exit(1);
  }
}



TrkrHitSetTmp::ConstIterator
TrkrHitSetTmp::addHitSpecificKey(const TrkrDefs::hitkey key, TrkrHitTmp* hit)
{
  auto ret = m_hits.insert(std::make_pair(key, hit));

  if ( !ret.second )
  {
    std::cout << "TrkrHitSetTmp::AddHitSpecificKey: duplicate key: " << key << " exiting now" << std::endl;
    exit(1);
  }
  else
  {
    return ret.first;
  }
}

TrkrHitTmp*
TrkrHitSetTmp::getHit(const TrkrDefs::hitkey key)
{
  TrkrHitSetTmp::ConstIterator it = m_hits.find(key);
  
  if (it != m_hits.end())
  {
    return it->second;
  }
  
  return nullptr;
}

TrkrHitSetTmp::ConstRange
TrkrHitSetTmp::getHits()
{
  return std::make_pair(m_hits.begin(), m_hits.end());
}
