#ifndef MYUTILS_GENERATEROOTTMAPHITS_H
#define MYUTILS_GENERATEROOTTMAPHITS_H

#include <fun4all/SubsysReco.h>

// rootcint barfs with this header so we need to hide it
#ifndef __CINT__
#include <gsl/gsl_rng.h>
#endif

class PHCompositeNode;

/// \class GenerateRootTMapHits
///
/// \brief simple truth vertex smearing algorithm
///
class GenerateRootTMapHits : public SubsysReco
{
 public:
  GenerateRootTMapHits(const std::string &name = "GenerateRootTMapHits");
  virtual ~GenerateRootTMapHits();

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
