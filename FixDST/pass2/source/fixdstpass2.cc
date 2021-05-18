
#include "fixdstpass2.h"

#include "TrkrHitTmp.h"
#include "TrkrHitSetTmp.h"
#include "TrkrHitSetContainerTmp.h"
#include "TrkrClusterHitAssocTmp.h"
#include "TpcHitTmp.h"
#include "MvtxHitTmp.h"
#include "InttHitTmp.h"

#include <trackbase/TrkrHitv1.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHitSetContainer.h>

#include <trackbase/TrkrClusterHitAssocv1.h>

#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/PHCompositeNode.h>
#include <phool/getClass.h>
#include <phool/PHNodeIterator.h>


//____________________________________________________________________________..
fixdstpass2::fixdstpass2(const std::string &name):
 SubsysReco(name)
{
}

//____________________________________________________________________________..
fixdstpass2::~fixdstpass2()
{
}

//____________________________________________________________________________..
int fixdstpass2::Init(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);

  // Looking for the DST node
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode)
  {
    std::cout << PHWHERE << "DST Node missing, doing nothing." << std::endl;
    exit(1);
  }
  PHNodeIterator dstiter(dstNode);
  PHCompositeNode *trkNode = dynamic_cast<PHCompositeNode *>(dstiter.findFirst("PHCompositeNode","TRKR"));
  if (!trkNode)
  {
    trkNode = new PHCompositeNode("TRKR");
    dstNode->addNode(trkNode);
  }
  TrkrHitSetContainer *hitsetcontainer = findNode::getClass<TrkrHitSetContainer>(topNode,trkhitnodename);
  if (! hitsetcontainer)
  {
    hitsetcontainer = new TrkrHitSetContainer();
    auto newNode = new PHIODataNode<PHObject>(hitsetcontainer, trkhitnodename, "PHObject");
    trkNode->addNode(newNode);
  }
  TrkrClusterHitAssoc *clusterhitassoc = findNode::getClass<TrkrClusterHitAssoc>(topNode,trkclusassocname);
  if (!clusterhitassoc)
  {
    clusterhitassoc = new TrkrClusterHitAssocv1();
    auto newNode = new PHIODataNode<PHObject>(clusterhitassoc, trkclusassocname, "PHObject");
    trkNode->addNode(newNode);

  }
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass2::InitRun(PHCompositeNode *topNode)
{
  

  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass2::process_event(PHCompositeNode *topNode)
{
  TrkrClusterHitAssocTmp *clusterhitassoctmp = findNode::getClass<TrkrClusterHitAssocTmp>(topNode,trkclusassoctmpname);
  TrkrClusterHitAssoc *clusterhitassoc = findNode::getClass<TrkrClusterHitAssoc>(topNode,trkclusassocname);
  if (clusterhitassoctmp && clusterhitassoc)
  {
    TrkrClusterHitAssocTmp::ConstRange rng = clusterhitassoctmp->getHits();
    for (TrkrClusterHitAssocTmp::ConstIterator iter = rng.first; iter != rng.second; ++iter)
    {
      clusterhitassoc->addAssoc(iter->first,iter->second);
    }
  }

  TrkrHitSetContainerTmp *hitsetcontainertmp = findNode::getClass<TrkrHitSetContainerTmp>(topNode,trkhittmpnodename);
  TrkrHitSetContainer *hitsetcontainer = findNode::getClass<TrkrHitSetContainer>(topNode,trkhitnodename);
  if (hitsetcontainertmp && hitsetcontainer)
  {
    TrkrHitSetContainerTmp::ConstRange hitsetrange = hitsetcontainertmp->getHitSets();
    for (TrkrHitSetContainerTmp::ConstIterator iter = hitsetrange.first; iter != hitsetrange.second; ++iter)
    {
//      TrkrDefs::hitsetkey node_hitsetkey = iter->first;
      TrkrHitSetTmp *hitsettmp = iter->second;
//      std::cout << hitset << node_hitsetkey << std::endl;
      TrkrHitSet *hitset = new TrkrHitSet();
      hitset->setHitSetKey(hitsettmp->getHitSetKey());
      hitsetcontainer->addHitSetSpecifyKey(hitset->getHitSetKey(),hitset);
      TrkrHitSetTmp::ConstRange single_hit_range = hitsettmp->getHits();
      for (TrkrHitSetTmp::ConstIterator single_hit_iter = single_hit_range.first;
	   single_hit_iter != single_hit_range.second;
	   ++single_hit_iter)
      {
	TrkrDefs::hitkey key = single_hit_iter->first;
	TrkrHitTmp *trkhittmp = single_hit_iter->second;
	TrkrHit *trkhit = new TrkrHitv1();
	trkhit->addEnergy(trkhittmp->getEnergy());
        trkhit->setAdc(trkhittmp->getAdc());
	hitset->addHitSpecificKey(key, trkhit);
      }

//	std::cout << key << trkhit << std::endl;
    }
  }
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass2::End(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

