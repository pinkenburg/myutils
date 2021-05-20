#include "DumpTrkrClusterContainerTmp.h"

#include <phool/PHIODataNode.h>

#include <trackbase/TrkrCluster.h>
#include <fixdstpass2/TrkrClusterContainerTmp.h>

#include <map>
#include <ostream>
#include <string>
#include <utility>

using namespace std;

typedef PHIODataNode<TrkrClusterContainerTmp> MyNode_t;

DumpTrkrClusterContainerTmp::DumpTrkrClusterContainerTmp(const string &NodeName)
  : DumpObject(NodeName)
{
  return;
}

int DumpTrkrClusterContainerTmp::process_Node(PHNode *myNode)
{
  TrkrClusterContainerTmp *trkrclustercontainer = nullptr;
  MyNode_t *thisNode = static_cast<MyNode_t *>(myNode);
  if (thisNode)
  {
    trkrclustercontainer = thisNode->getData();
  }
  if (trkrclustercontainer)
  {
    TrkrClusterContainerTmp::ConstIterator hiter;
    TrkrClusterContainerTmp::ConstRange begin_end = trkrclustercontainer->getClusters();
    *fout << "size: " << trkrclustercontainer->size() << endl;
    for (hiter = begin_end.first; hiter != begin_end.second; ++hiter)
    {
      TrkrCluster *trkrcluster = hiter->second;
      *fout << "getX: " << trkrcluster->getX() << endl;
      *fout << "getY: " << trkrcluster->getY() << endl;
      *fout << "getZ: " << trkrcluster->getZ() << endl;
      *fout << "getAdc: " << trkrcluster->getAdc() << endl;
      *fout << "getPhiSize: " << trkrcluster->getPhiSize() << endl;
      *fout << "getPhiError: " << trkrcluster->getPhiError() << endl;
      *fout << "getRPhiError: " << trkrcluster->getRPhiError() << endl;
      *fout << "getZError: " << trkrcluster->getZError() << endl;
    }
  }
  return 0;
}
