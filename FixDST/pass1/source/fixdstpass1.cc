
#include "fixdstpass1.h"

#include "TrkrHitTmp.h"
#include "TrkrHitSetTmp.h"
#include "TrkrHitSetContainerTmp.h"
#include "TrkrClusterHitAssocTmp.h"

#include "TpcHitTmp.h"
#include "MvtxHitTmp.h"
#include "InttHitTmp.h"


#include <trackbase/TrkrHit.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHitSetContainer.h>

#include <trackbase/TrkrClusterHitAssoc.h>

#include <mvtx/MvtxHit.h>
#include <intt/InttHit.h>
#include <tpc/TpcHit.h>

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
  TrkrClusterHitAssocTmp *clusterhitassoc = findNode::getClass<TrkrClusterHitAssocTmp>(topNode,trkclusassoctmpname);
  if (!clusterhitassoc)
  {
    clusterhitassoc = new TrkrClusterHitAssocTmp();
    auto newNode = new PHIODataNode<PHObject>(clusterhitassoc, trkclusassoctmpname, "PHObject");
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
  TrkrClusterHitAssocTmp *clusterhitassoctmp = findNode::getClass<TrkrClusterHitAssocTmp>(topNode,trkclusassoctmpname);
  TrkrClusterHitAssoc *clusterhitassoc = findNode::getClass<TrkrClusterHitAssoc>(topNode,trkclusassocname);
  if (clusterhitassoctmp && clusterhitassoc)
  {
    TrkrClusterHitAssoc::ConstRange rng = clusterhitassoc->getHits();
    for (TrkrClusterHitAssoc::ConstIterator iter = rng.first; iter != rng.second; ++iter)
    {
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
	TpcHit *tpchit = dynamic_cast<TpcHit *>(trkhit);
	TrkrHitTmp *trkhittmp = nullptr;
	if (tpchit)
	{
//	  std::cout << std::hex << key <<  std::dec << " is tpc hit" << std::endl;
	  trkhittmp = new TpcHitTmp();
	}
	else
	{
          InttHit *intthit = dynamic_cast<InttHit *>(trkhit);
	  if (intthit)
	  {
//	    std::cout << std::hex << key <<  std::dec << " is intt hit" << std::endl;
	    trkhittmp = new InttHitTmp();
	  }
	  else
	  {
	    MvtxHit *mvtxhit = dynamic_cast<MvtxHit *>(trkhit);
	    if (mvtxhit)
	    {
//	    std::cout << std::hex << key <<  std::dec << " is mvtx hit" << std::endl;
	      trkhittmp = new MvtxHitTmp();
	    }
	  }
	}
	if (! trkhittmp)
	{
           // micromegas has no separate base class
//	  std::cout << std::hex << "0x" << key <<  std::dec << " NO tpc/intt hit" << std::endl;
	  trkhittmp = new TrkrHitTmp();
	}
	trkhittmp->addEnergy(trkhit->getEnergy());
        trkhittmp->setAdc(trkhit->getAdc());
	hitsettmp->addHitSpecificKey(key, trkhittmp);
      }

//	std::cout << key << trkhit << std::endl;
    }
  }
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int fixdstpass1::End(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

