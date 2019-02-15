#ifndef MYUTILS_GENERATEROOTHITS_H
#define MYUTILS_GENERATEROOTHITS_H

#include <fun4all/SubsysReco.h>

// rootcint barfs with this header so we need to hide it
#ifndef __CINT__
#include <gsl/gsl_rng.h>
#endif

class PHCompositeNode;

/// \class GenerateRootHits
///
/// \brief simple truth vertex smearing algorithm
///
class GenerateRootHits : public SubsysReco
{
 public:
  GenerateRootHits(const std::string &name = "GenerateRootHits");
  virtual ~GenerateRootHits();

  int Init(PHCompositeNode *topNode);
  int InitRun(PHCompositeNode *topNode);
  int process_event(PHCompositeNode *topNode);
  int End(PHCompositeNode *topNode);

 private:

#ifndef __CINT__
  gsl_rng *RandomGenerator;
#endif
};

#endif
