#ifndef TRACKRECO_ASSOCINFOCONTAINERTMP_H
#define TRACKRECO_ASSOCINFOCONTAINERTMP_H

#include <phool/PHObject.h>

#include <trackbase/TrkrDefs.h>

#include <iostream>              // for cout, ostream
#include <map>
#include <utility>               // for pair
#include <vector>                // for vector

class AssocInfoContainerTmp : public PHObject
{
 public:
  typedef std::multimap<TrkrDefs::cluskey, unsigned int> ClusterTrackMap;
  typedef ClusterTrackMap::const_iterator ConstIterator;
  typedef std::pair<ConstIterator, ConstIterator> ConstRange;

  AssocInfoContainerTmp();
  virtual ~AssocInfoContainerTmp();

  void Reset();
  void identify(std::ostream& os = std::cout) const;

  void SetClusterTrackAssoc(const TrkrDefs::cluskey& cluster_id, const unsigned int& track_id)
  {
    _map_cluster_id_track_id.insert(ClusterTrackMap::value_type(cluster_id, track_id));
  }

  std::vector<unsigned int> GetTracksFromCluster(const TrkrDefs::cluskey& cluster_id) const
  {
    std::vector<unsigned int> ret;
    for (auto iter = _map_cluster_id_track_id.lower_bound(cluster_id);
         iter != _map_cluster_id_track_id.upper_bound(cluster_id); ++iter)
    {
      ret.push_back(iter->second);
    }
    return ret;
  }

  ConstRange GetAssoc() {return make_pair(_map_cluster_id_track_id.begin(), _map_cluster_id_track_id.end());}

 private:
  ClusterTrackMap _map_cluster_id_track_id;

  ClassDef(AssocInfoContainerTmp, 1)
};

#endif
