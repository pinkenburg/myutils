#include "DumpTrkrHitSetContainerTmp.h"

#include <phool/PHIODataNode.h>

#include <fixdstpass2/TrkrHitTmp.h>
#include <fixdstpass2/TrkrHitSetTmp.h>
#include <fixdstpass2/TrkrHitSetContainerTmp.h>

#include <map>
#include <ostream>
#include <string>
#include <utility>

using namespace std;

typedef PHIODataNode<TrkrHitSetContainerTmp> MyNode_t;

DumpTrkrHitSetContainerTmp::DumpTrkrHitSetContainerTmp(const string &NodeName)
  : DumpObject(NodeName)
{
  return;
}

int DumpTrkrHitSetContainerTmp::process_Node(PHNode *myNode)
{
  TrkrHitSetContainerTmp *trkrhitsetcontainer = nullptr;
  MyNode_t *thisNode = static_cast<MyNode_t *>(myNode);
  if (thisNode)
  {
    trkrhitsetcontainer = thisNode->getData();
  }
  if (trkrhitsetcontainer)
  {
    TrkrHitSetContainerTmp::ConstIterator hiter;
    TrkrHitSetContainerTmp::ConstRange begin_end = trkrhitsetcontainer->getHitSets();
    *fout << "size: " << trkrhitsetcontainer->size() << endl;
    for (hiter = begin_end.first; hiter != begin_end.second; ++hiter)
    {
      TrkrHitSetTmp *trkrhitset = hiter->second;
      TrkrHitSetTmp::ConstIterator tsetiter;
      TrkrHitSetTmp::ConstRange trset_begin_end = trkrhitset->getHits();
      for (tsetiter = trset_begin_end.first; tsetiter != trset_begin_end.second; ++tsetiter)
      {
        TrkrHitTmp *hit = tsetiter->second;
        *fout << "id: " << tsetiter->first << endl;
        *fout << "edep: " << hit->getEnergy() << endl;
        *fout << "adc: " << hit->getAdc() << endl;
        *fout << "hittype: " << hit->get_hittype() << endl;
      }
    }
  }
  return 0;
}
