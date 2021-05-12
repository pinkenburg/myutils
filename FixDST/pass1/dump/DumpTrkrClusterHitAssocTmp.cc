#include "DumpTrkrClusterHitAssocTmp.h"

#include <phool/PHIODataNode.h>

#include <fixdstpass1/TrkrClusterHitAssocTmp.h>

#include <map>
#include <ostream>
#include <string>
#include <utility>

using namespace std;

typedef PHIODataNode<TrkrClusterHitAssocTmp> MyNode_t;

DumpTrkrClusterHitAssocTmp::DumpTrkrClusterHitAssocTmp(const string &NodeName)
  : DumpObject(NodeName)
{
  return;
}

int DumpTrkrClusterHitAssocTmp::process_Node(PHNode *myNode)
{
  TrkrClusterHitAssocTmp *trkrclusterhitassoc = nullptr;
  MyNode_t *thisNode = static_cast<MyNode_t *>(myNode);
  if (thisNode)
  {
    trkrclusterhitassoc = thisNode->getData();
  }
  if (trkrclusterhitassoc)
  {
    trkrclusterhitassoc->identify(*fout);
  }
  return 0;
}
