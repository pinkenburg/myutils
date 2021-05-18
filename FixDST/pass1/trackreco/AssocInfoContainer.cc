#include "AssocInfoContainer.h"

using namespace std;

AssocInfoContainer::AssocInfoContainer()
  : _map_cluster_id_track_id()
{
}

AssocInfoContainer::~AssocInfoContainer() { Reset(); }

void AssocInfoContainer::Reset()
{
  _map_cluster_id_track_id.clear();
}

void AssocInfoContainer::identify(std::ostream& os) const
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
