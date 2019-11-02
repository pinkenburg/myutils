
#include "GenerateHits.h"

#include "MyContainer.h"
#include "MyHitv1.h"

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

GenerateHits::GenerateHits(const string &name)
  : SubsysReco(name)
{
  RandomGenerator = gsl_rng_alloc(gsl_rng_mt19937);
}

GenerateHits::~GenerateHits()
{
  gsl_rng_free(RandomGenerator);
}

int GenerateHits::Init(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

int GenerateHits::InitRun(PHCompositeNode *topNode)
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

  MyContainer *g4_hits = new MyContainer();
chpNode->addNode(new PHDataNode<MyContainer>(g4_hits, "MYHITS"));
  return Fun4AllReturnCodes::EVENT_OK;

}

int GenerateHits::process_event(PHCompositeNode *topNode)
{
  if (Verbosity() > 1) cout << "GenerateHits::process_event -- entered" << endl;
  MyContainer *g4_hits =  findNode::getClass<MyContainer>(topNode,"MYHITS" );

  int nhits = 1000000;
  for (int j=0; j<nhits; ++j)
  {
    MyHit *m_Hit = new MyHitv1();
    m_Hit->set_key(j);
    for (int i=0; i<2; i++)
    {
      m_Hit->set_x(gsl_rng_uniform_pos(RandomGenerator),gsl_rng_uniform_pos(RandomGenerator));
      m_Hit->set_y(gsl_rng_uniform_pos(RandomGenerator),gsl_rng_uniform_pos(RandomGenerator));
      m_Hit->set_z(gsl_rng_uniform_pos(RandomGenerator),gsl_rng_uniform_pos(RandomGenerator));
      m_Hit->set_t(gsl_rng_uniform_pos(RandomGenerator),gsl_rng_uniform_pos(RandomGenerator));
    }
    m_Hit->add_edep(gsl_rng_uniform_pos(RandomGenerator),
gsl_rng_uniform_pos(RandomGenerator),
gsl_rng_uniform_pos(RandomGenerator));
    g4_hits->AddScintillatorSlat(m_Hit->get_key(),m_Hit);
  }
  return Fun4AllReturnCodes::EVENT_OK;
}

int GenerateHits::ResetEvent(PHCompositeNode *topNode)
{
  MyContainer *g4_hits =  findNode::getClass<MyContainer>(topNode,"MYHITS" );
  g4_hits->Reset();
  return Fun4AllReturnCodes::EVENT_OK;
}

int GenerateHits::End(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

