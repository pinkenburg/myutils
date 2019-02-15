
#include "GenerateRootHits.h"

#include "MyRootContainer.h"
#include "MyRootHitv1.h"

#include <g4main/PHG4TruthInfoContainer.h>

#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/PHCompositeNode.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHRandomSeed.h>
#include <phool/getClass.h>

#include <gsl/gsl_randist.h>

#include <cmath>
#include <iostream>

using namespace std;

GenerateRootHits::GenerateRootHits(const string &name)
  : SubsysReco(name)
{
  RandomGenerator = gsl_rng_alloc(gsl_rng_mt19937);
}

GenerateRootHits::~GenerateRootHits()
{
  gsl_rng_free(RandomGenerator);
}

int GenerateRootHits::Init(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

int GenerateRootHits::InitRun(PHCompositeNode *topNode)
{

  unsigned int seed = PHRandomSeed();  // fixed random seed handled in PHRandomSeed()
  gsl_rng_set(RandomGenerator, seed);
  PHNodeIterator iter(topNode);

  // Looking for the DST node
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode)
  {
    cout << PHWHERE << "DST Node missing, doing nothing." << endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }

  // store the BBC stuff under a sub-node directory
  PHCompositeNode *chpNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "CHP"));
  if (!chpNode)
  {
    chpNode = new PHCompositeNode("CHP");
    dstNode->addNode(chpNode);
  }

  MyRootContainer *g4_hits = new MyRootContainer();
chpNode->addNode(new PHIODataNode<PHObject>(g4_hits, "G4HITS", "PHObject"));
  return Fun4AllReturnCodes::EVENT_OK;

}

int GenerateRootHits::process_event(PHCompositeNode *topNode)
{
  if (Verbosity() > 1) cout << "GenerateRootHits::process_event -- entered" << endl;
  MyRootContainer *g4_hits =  findNode::getClass<MyRootContainer>(topNode,"G4HITS" );

  int nhits = 1000000;
  for (int j=0; j<nhits; ++j)
  {
    MyRootHit *m_Hit = new MyRootHitv1();
    m_Hit->set_key(j);
    m_Hit->add_edep(gsl_rng_uniform_pos(RandomGenerator),
gsl_rng_uniform_pos(RandomGenerator),
gsl_rng_uniform_pos(RandomGenerator));
    g4_hits->AddScintillatorSlat(m_Hit->get_key(),m_Hit);
  }
  return Fun4AllReturnCodes::EVENT_OK;
}

int GenerateRootHits::End(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

