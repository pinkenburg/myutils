
#include "fixdstpass2.h"

#include "AssocInfoContainerTmp.h"

#include "TrkrHitTmp.h"
#include "TrkrHitSetTmp.h"
#include "TrkrHitSetContainerTmp.h"
#include "TrkrClusterHitAssocTmp.h"
#include "TrkrHitTruthAssocTmp.h"
#include "TrkrClusterContainerTmp.h"


#include <trackbase/TrkrClusterv1.h>
#include <trackbase/TrkrClusterContainerv1.h>

#include <trackbase/TrkrHitv1.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHitSetContainer.h>
#include <trackbase/TrkrHitSetContainerv1.h>

#include <trackbase/TrkrClusterHitAssocv1.h>
#include <trackbase/TrkrHitTruthAssocv1.h>

#include <trackreco/AssocInfoContainer.h>
#include <trackreco/AssocInfoContainerv1.h>

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

  AssocInfoContainer *assoc = findNode::getClass<AssocInfoContainer>(topNode,assocname);
  if (! assoc)
  {
    assoc = new AssocInfoContainerv1();
    auto newNode = new PHIODataNode<PHObject>(assoc, assocname, "PHObject");
    trkNode->addNode(newNode);

  }

  TrkrClusterContainer *clustercon = findNode::getClass<TrkrClusterContainer>(topNode,trkcluscontname);
if (!clustercon)
{
  clustercon = new TrkrClusterContainerv1();
  auto newNode = new PHIODataNode<PHObject>(clustercon,trkcluscontname, "PHObject");
trkNode->addNode(newNode);
}

  TrkrClusterHitAssoc *clusterhitassoc = findNode::getClass<TrkrClusterHitAssoc>(topNode,trkclusassocname);
  if (!clusterhitassoc)
  {
    clusterhitassoc = new TrkrClusterHitAssocv1();
    auto newNode = new PHIODataNode<PHObject>(clusterhitassoc, trkclusassocname, "PHObject");
    trkNode->addNode(newNode);

  }

  TrkrHitSetContainer *hitsetcontainer = findNode::getClass<TrkrHitSetContainer>(topNode,trkhitnodename);
  if (! hitsetcontainer)
  {
    hitsetcontainer = new TrkrHitSetContainerv1();
    auto newNode = new PHIODataNode<PHObject>(hitsetcontainer, trkhitnodename, "PHObject");
    trkNode->addNode(newNode);
  }

  TrkrHitTruthAssoc *hittruthassoc = findNode::getClass<TrkrHitTruthAssoc>(topNode,trkhitassocname);
  if (!hittruthassoc)
  {
    hittruthassoc = new TrkrHitTruthAssocv1();
    auto newNode = new PHIODataNode<PHObject>(hittruthassoc,trkhitassocname, "PHObject");
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

  AssocInfoContainerTmp *assoctmp = findNode::getClass<AssocInfoContainerTmp>(topNode,assoctmpname);
  AssocInfoContainer *assoc = findNode::getClass<AssocInfoContainer>(topNode,assocname);

  if (assoc && assoctmp)
  {
    AssocInfoContainerTmp::ConstRange assocrange = assoctmp->GetAssoc();
    for (AssocInfoContainerTmp::ConstIterator iter = assocrange.first; iter != assocrange.second; ++iter)
    {
      assoc->SetClusterTrackAssoc(iter->first, iter->second);
    }
  }

TrkrClusterContainerTmp *clustercontmp = findNode::getClass<TrkrClusterContainerTmp>(topNode,trkclusconttmpname);
TrkrClusterContainer *clustercon = findNode::getClass<TrkrClusterContainer>(topNode,trkcluscontname);
if (clustercontmp && clustercon)
{
  TrkrClusterContainerTmp::ConstRange rng = clustercontmp->getClusters();
  for (TrkrClusterContainerTmp::ConstIterator iter = rng.first; iter != rng.second; ++iter)
  {
    TrkrCluster *clus = dynamic_cast<TrkrCluster *>((iter->second)->CloneMe());
    clustercon->addClusterSpecifyKey(clus->getClusKey(),clus);
  }
}

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

  TrkrHitTruthAssocTmp *hittruthassoctmp = findNode::getClass<TrkrHitTruthAssocTmp>(topNode,trkhitassoctmpname);
  TrkrHitTruthAssoc *hittruthassoc = findNode::getClass<TrkrHitTruthAssoc>(topNode,trkhitassocname);
  if (hittruthassoctmp && hittruthassoc)
  {
    TrkrHitTruthAssocTmp::ConstRange ran = hittruthassoctmp->GetAssoc();
    for (TrkrHitTruthAssocTmp::ConstIterator iter = ran.first; iter != ran.second; ++iter)
    {
      hittruthassoc->addAssoc(iter->first, iter->second.first, iter->second.second);
    }
  }

  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass2::End(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

