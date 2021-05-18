
#include "fixdstpass1.h"

#include "AssocInfoContainerTmp.h"

#include "TrkrHitTmp.h"
#include "TrkrHitSetTmp.h"
#include "TrkrHitSetContainerTmp.h"
#include "TrkrHitTruthAssocTmp.h"

#include "TrkrClusterHitAssocTmp.h"
#include "TrkrClusterContainerTmp.h"

#include <trackbase/TrkrCluster.h>

#include <trackbase/TrkrHit.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHitSetContainer.h>

#include <trackbase/TrkrClusterContainer.h>

#include <trackbase/TrkrClusterHitAssoc.h>

#include <trackbase/TrkrHitTruthAssoc.h>

#include <trackreco/AssocInfoContainer.h>

#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/PHCompositeNode.h>
#include <phool/getClass.h>
#include <phool/PHNodeIterator.h>


//____________________________________________________________________________..
fixdstpass1::fixdstpass1(const std::string &name):
 SubsysReco(name)
{
}

//____________________________________________________________________________..
fixdstpass1::~fixdstpass1()
{
}

//____________________________________________________________________________..
int fixdstpass1::Init(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);

  // Looking for the DST node
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode)
  {
    std::cout << PHWHERE << "DST Node missing, doing nothing." << std::endl;
    exit(1);
  }
  TrkrHitSetContainerTmp *hitsetcontainertmp = findNode::getClass<TrkrHitSetContainerTmp>(topNode,trkhittmpnodename);
  if (! hitsetcontainertmp)
  {
    hitsetcontainertmp = new TrkrHitSetContainerTmp();
    auto newNode = new PHIODataNode<PHObject>(hitsetcontainertmp, trkhittmpnodename, "PHObject");
    dstNode->addNode(newNode);
  }

  TrkrHitTruthAssocTmp *hittruthassoctmp = findNode::getClass<TrkrHitTruthAssocTmp>(topNode,trkhitassoctmpname);
  if (!hittruthassoctmp)
  {
    hittruthassoctmp = new TrkrHitTruthAssocTmp();
    auto newNode = new PHIODataNode<PHObject>(hittruthassoctmp,trkhitassoctmpname, "PHObject");
    dstNode->addNode(newNode);
  }

  TrkrClusterContainerTmp *clustercon = findNode::getClass<TrkrClusterContainerTmp>(topNode,trkclusconttmpname);
if (!clustercon)
{
  clustercon = new TrkrClusterContainerTmp();
  auto newNode = new PHIODataNode<PHObject>(clustercon,trkclusconttmpname, "PHObject");
dstNode->addNode(newNode);
}
  TrkrClusterHitAssocTmp *clusterhitassoc = findNode::getClass<TrkrClusterHitAssocTmp>(topNode,trkclusassoctmpname);
  if (!clusterhitassoc)
  {
    clusterhitassoc = new TrkrClusterHitAssocTmp();
    auto newNode = new PHIODataNode<PHObject>(clusterhitassoc, trkclusassoctmpname, "PHObject");
    dstNode->addNode(newNode);

  }

  AssocInfoContainerTmp *assoc = findNode::getClass<AssocInfoContainerTmp>(topNode,assoctmpname);
  if (! assoc)
  {
    assoc = new AssocInfoContainerTmp();
    auto newNode = new PHIODataNode<PHObject>(assoc, assoctmpname, "PHObject");
    dstNode->addNode(newNode);

  }
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass1::InitRun(PHCompositeNode *topNode)
{
  

  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass1::process_event(PHCompositeNode *topNode)
{
TrkrClusterContainerTmp *clustercontmp = findNode::getClass<TrkrClusterContainerTmp>(topNode,trkclusconttmpname);
TrkrClusterContainer *clustercon = findNode::getClass<TrkrClusterContainer>(topNode,trkcluscontname);
if (clustercontmp && clustercon)
{
  TrkrClusterContainer::ConstRange rng = clustercon->getClusters();
  for (TrkrClusterContainer::ConstIterator iter = rng.first; iter != rng.second; ++iter)
  {
    TrkrCluster *clus = dynamic_cast<TrkrCluster *>((iter->second)->CloneMe());
    clustercontmp->addClusterSpecifyKey(clus->getClusKey(),clus);
  }
}

  TrkrClusterHitAssocTmp *clusterhitassoctmp = findNode::getClass<TrkrClusterHitAssocTmp>(topNode,trkclusassoctmpname);
  TrkrClusterHitAssoc *clusterhitassoc = findNode::getClass<TrkrClusterHitAssoc>(topNode,trkclusassocname);
  if (clusterhitassoctmp && clusterhitassoc)
  {
    TrkrClusterHitAssoc::ConstRange rng = clusterhitassoc->getHits();
    for (TrkrClusterHitAssoc::ConstIterator iter = rng.first; iter != rng.second; ++iter)
    {
//      std::cout << "adding " << iter->first << ", " << iter->second << std::endl;
      clusterhitassoctmp->addAssoc(iter->first,iter->second);
    }
  }
  TrkrHitSetContainerTmp *hitsetcontainertmp = findNode::getClass<TrkrHitSetContainerTmp>(topNode,trkhittmpnodename);
  TrkrHitSetContainer *hitsetcontainer = findNode::getClass<TrkrHitSetContainer>(topNode,trkhitnodename);
  if (hitsetcontainertmp && hitsetcontainer)
  {
    TrkrHitSetContainer::ConstRange hitsetrange = hitsetcontainer->getHitSets();
    for (TrkrHitSetContainer::ConstIterator iter = hitsetrange.first; iter != hitsetrange.second; ++iter)
    {
//      TrkrDefs::hitsetkey node_hitsetkey = iter->first;
      TrkrHitSet *hitset = iter->second;
//      std::cout << hitset << node_hitsetkey << std::endl;
      TrkrHitSetTmp *hitsettmp = new TrkrHitSetTmp();
      hitsettmp->setHitSetKey(hitset->getHitSetKey());
      hitsetcontainertmp->addHitSetSpecifyKey(hitsettmp->getHitSetKey(),hitsettmp);
      TrkrHitSet::ConstRange single_hit_range = hitset->getHits();
      for (TrkrHitSet::ConstIterator single_hit_iter = single_hit_range.first;
	   single_hit_iter != single_hit_range.second;
	   ++single_hit_iter)
      {
	TrkrDefs::hitkey key = single_hit_iter->first;
	TrkrHit *trkhit = single_hit_iter->second;
	  TrkrHitTmp *trkhittmp = new TrkrHitTmp();
	trkhittmp->addEnergy(trkhit->getEnergy());
        trkhittmp->setAdc(trkhit->getAdc());
	hitsettmp->addHitSpecificKey(key, trkhittmp);
      }

//	std::cout << key << trkhit << std::endl;
    }
  }

  AssocInfoContainerTmp *assoctmp = findNode::getClass<AssocInfoContainerTmp>(topNode,assoctmpname);
  AssocInfoContainer *assoc = findNode::getClass<AssocInfoContainer>(topNode,assocname);

  if (assoc && assoctmp)
  {
    AssocInfoContainer::ConstRange assocrange = assoc->GetAssoc();
    for (AssocInfoContainer::ConstIterator iter = assocrange.first; iter != assocrange.second; ++iter)
    {
      assoctmp->SetClusterTrackAssoc(iter->first, iter->second);
    }
  }

  TrkrHitTruthAssocTmp *hittruthassoctmp = findNode::getClass<TrkrHitTruthAssocTmp>(topNode,trkhitassoctmpname);
  TrkrHitTruthAssoc *hittruthassoc = findNode::getClass<TrkrHitTruthAssoc>(topNode,trkhitassocname);
  if (hittruthassoctmp && hittruthassoc)
  {
    TrkrHitTruthAssoc::ConstRange ran = hittruthassoc->GetAssoc();
    for (TrkrHitTruthAssoc::ConstIterator iter = ran.first; iter != ran.second; ++iter)
    {
      hittruthassoctmp->addAssoc(iter->first, iter->second.first, iter->second.second);
    }
  }
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass1::End(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

