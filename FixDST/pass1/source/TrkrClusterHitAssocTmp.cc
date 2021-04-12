/**                                                                                                                                                                                                       
 * @file trackbase/TrkrClusterHitAssocTmp.cc
 * @author D. McGlinchey
 * @date June 2018
 * @brief TrkrClusterHitAssocTmp implementation
 */

#include "TrkrClusterHitAssocTmp.h"

#include <ostream>  // for operator<<, endl, basic_ostream, ostream, basic_o...

TrkrClusterHitAssocTmp::TrkrClusterHitAssocTmp() 
  : m_map()
{
}


TrkrClusterHitAssocTmp::~TrkrClusterHitAssocTmp()
{
}

void 
TrkrClusterHitAssocTmp::Reset()
{
  m_map.clear();
}

void 
TrkrClusterHitAssocTmp::identify(std::ostream &os) const
{
  os << "-----TrkrClusterHitAssocTmp-----" << std::endl;
  os << "Number of associations: " << m_map.size() << std::endl;

  for ( auto& entry : m_map )
  {
    // os << "   cluster key: 0x" << std::hex << entry.first << std::dec
    os << "   cluster key: "  << entry.first << std::dec
       << " hit key: " << entry.second << std::endl;
  }

  os << "------------------------------" << std::endl;

  return;

}

void 
TrkrClusterHitAssocTmp::addAssoc(TrkrDefs::cluskey ckey, unsigned int hidx)
{
  m_map.insert(std::make_pair(ckey, hidx));
}

TrkrClusterHitAssocTmp::ConstRange 
TrkrClusterHitAssocTmp::getHits(TrkrDefs::cluskey ckey)
{
  ConstRange retpair;
  retpair.first = m_map.lower_bound(ckey);
  retpair.second = m_map.upper_bound(ckey);
  return retpair;
}
