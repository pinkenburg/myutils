#ifndef MYUTILS_GENERATEROOTTCHITS_H
#define MYUTILS_GENERATEROOTTCHITS_H

#include <fun4all/SubsysReco.h>

// rootcint barfs with this header so we need to hide it
#ifndef __CINT__
#include <gsl/gsl_rng.h>
#endif

class PHCompositeNode;

/// \class GenerateRootTCHits
///
/// \brief simple truth vertex smearing algorithm
///
class GenerateRootTCHits : public SubsysReco
{
 public:
  GenerateRootTCHits(const std::string &name = "GenerateRootTCHits");
  virtual ~GenerateRootTCHits();

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
