#include "AssocInfoContainerTmp.h"

using namespace std;

AssocInfoContainerTmp::AssocInfoContainerTmp()
  : _map_cluster_id_track_id()
{
}

AssocInfoContainerTmp::~AssocInfoContainerTmp() { Reset(); }

void AssocInfoContainerTmp::Reset()
{
  _map_cluster_id_track_id.clear();
}

void AssocInfoContainerTmp::identify(std::ostream& os) const
{
  os << "---ClusterTrackMap--------------------------" << endl;
  for (auto iter = _map_cluster_id_track_id.begin();
       iter != _map_cluster_id_track_id.end();
       ++iter)
  {
    os
        << "{" << iter->first
        << " -> " << iter->second
        << "}"
        << endl;
  }
}
