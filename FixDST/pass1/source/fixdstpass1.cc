
#include "fixdstpass1.h"

#include "AssocInfoContainerTmp.h"

#include "TrkrHitTmp.h"
#include "TrkrHitSetTmp.h"
#include "TrkrHitSetContainerTmp.h"
#include "TrkrHitTruthAssocTmp.h"

#include "TrkrClusterHitAssocTmp.h"
#include "TrkrClusterContainerTmp.h"

#include <mvtx/MvtxHit.h>
#include <intt/InttHit.h>
#include <tpc/TpcHit.h>

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
int fixdstpass1::InitRun(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);

  // Looking for the DST node
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode)
  {
    std::cout << PHWHERE << "DST Node missing, doing nothing." << std::endl;
    exit(1);
  }

  AssocInfoContainer *assoc = findNode::getClass<AssocInfoContainer>(topNode,assocname);
  if (assoc)
  {
    AssocInfoContainerTmp *assoctmp = findNode::getClass<AssocInfoContainerTmp>(topNode,assoctmpname);
    if (! assoctmp)
    {
      assoctmp = new AssocInfoContainerTmp();
      auto newNode = new PHIODataNode<PHObject>(assoctmp, assoctmpname, "PHObject");
      dstNode->addNode(newNode);

    }
  }

  TrkrClusterContainer *clustercon = findNode::getClass<TrkrClusterContainer>(topNode,trkcluscontname);
  if (clustercon)
  {
    TrkrClusterContainerTmp *clustercontmp = findNode::getClass<TrkrClusterContainerTmp>(topNode,trkclusconttmpname);
    if (!clustercontmp)
    {
      clustercontmp = new TrkrClusterContainerTmp();
      auto newNode = new PHIODataNode<PHObject>(clustercontmp,trkclusconttmpname, "PHObject");
      dstNode->addNode(newNode);
    }
  }

  TrkrClusterHitAssoc *clusterhitassoc = findNode::getClass<TrkrClusterHitAssoc>(topNode,trkclusassocname);
  if (clusterhitassoc)
  {
    TrkrClusterHitAssocTmp *clusterhitassoctmp = findNode::getClass<TrkrClusterHitAssocTmp>(topNode,trkclusassoctmpname);
    if (!clusterhitassoctmp)
    {
      clusterhitassoctmp = new TrkrClusterHitAssocTmp();
      auto newNode = new PHIODataNode<PHObject>(clusterhitassoctmp, trkclusassoctmpname, "PHObject");
      dstNode->addNode(newNode);

    }
  }

  TrkrHitSetContainer *hitsetcontainer = findNode::getClass<TrkrHitSetContainer>(topNode,trkhitnodename);
  if (hitsetcontainer)
  {
    TrkrHitSetContainerTmp *hitsetcontainertmp = findNode::getClass<TrkrHitSetContainerTmp>(topNode,trkhittmpnodename);
    if (! hitsetcontainertmp)
    {
      hitsetcontainertmp = new TrkrHitSetContainerTmp();
      auto newNode = new PHIODataNode<PHObject>(hitsetcontainertmp, trkhittmpnodename, "PHObject");
      dstNode->addNode(newNode);
    }
  }

  TrkrHitTruthAssoc *hittruthassoc = findNode::getClass<TrkrHitTruthAssoc>(topNode,trkhitassocname);
  if (hittruthassoc)
  {
    TrkrHitTruthAssocTmp *hittruthassoctmp = findNode::getClass<TrkrHitTruthAssocTmp>(topNode,trkhitassoctmpname);
    if (!hittruthassoctmp)
    {
      hittruthassoctmp = new TrkrHitTruthAssocTmp();
      auto newNode = new PHIODataNode<PHObject>(hittruthassoctmp,trkhitassoctmpname, "PHObject");
      dstNode->addNode(newNode);
    }
  }

  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass1::Init(PHCompositeNode *topNode)
{
  

  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass1::process_event(PHCompositeNode *topNode)
{

// Assoc Info
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

        TpcHit *tpchit = dynamic_cast<TpcHit *>(trkhit);
	if (tpchit)
	{
//	  std::cout << std::hex << key <<  std::dec << " is tpc hit" << std::endl;
	  trkhittmp->set_hittype(TrkrHitTmp::HitType::tpchit);
	}
	else
	{
          InttHit *intthit = dynamic_cast<InttHit *>(trkhit);
	  if (intthit)
	  {
//	    std::cout << std::hex << key <<  std::dec << " is intt hit" << std::endl;
	    trkhittmp->set_hittype(TrkrHitTmp::HitType::intthit);
	  }
	  else
	  {
	    MvtxHit *mvtxhit = dynamic_cast<MvtxHit *>(trkhit);
	    if (mvtxhit)
	    {
//	    std::cout << std::hex << key <<  std::dec << " is mvtx hit" << std::endl;
	      trkhittmp->set_hittype(TrkrHitTmp::HitType::mvtxhit);
	    }
	    else
	    {
	      trkhittmp->set_hittype(TrkrHitTmp::HitType::micromegashit);
	    }
	  }
	}
	hitsettmp->addHitSpecificKey(key, trkhittmp);
      }

//	std::cout << key << trkhit << std::endl;
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

