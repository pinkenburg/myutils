#ifndef MYUTILS_GENERATEHITS_H
#define MYUTILS_GENERATEHITS_H

#include <fun4all/SubsysReco.h>

// rootcint barfs with this header so we need to hide it
#ifndef __CINT__
#include <gsl/gsl_rng.h>
#endif

class PHCompositeNode;

/// \class GenerateHits
///
/// \brief simple truth vertex smearing algorithm
///
class GenerateHits : public SubsysReco
{
 public:
  GenerateHits(const std::string &name = "GenerateHits");
  virtual ~GenerateHits();

  int Init(PHCompositeNode *topNode);
  int InitRun(PHCompositeNode *topNode);
  int process_event(PHCompositeNode *topNode);
  int End(PHCompositeNode *topNode);
  int ResetEvent(PHCompositeNode *topNode);

 private:

#ifndef __CINT__
  gsl_rng *RandomGenerator;
#endif
};

#endif
