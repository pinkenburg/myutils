// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef FIXDSTPASS2_H
#define FIXDSTPASS2_H

#include <fun4all/SubsysReco.h>

#include <string>

class PHCompositeNode;

class fixdstpass2 : public SubsysReco
{
 public:

  fixdstpass2(const std::string &name = "fixdstpass2");

  virtual ~fixdstpass2();

  /** Called during initialization.
      Typically this is where you can book histograms, and e.g.
      register them to Fun4AllServer (so they can be output to file
      using Fun4AllServer::dumpHistos() method).
   */
  int Init(PHCompositeNode *topNode) override;

  /** Called for first event when run number is known.
      Typically this is where you may want to fetch data from
      database, because you know the run number. A place
      to book histograms which have to know the run number.
   */
  int InitRun(PHCompositeNode *topNode) override;

  /** Called for each event.
      This is where you do the real work.
   */
  int process_event(PHCompositeNode *topNode) override;

  /// Called at the end of all processing.
  int End(PHCompositeNode *topNode) override;

 private:

  std::string assocname = "AssocInfoContainer";
  std::string assoctmpname = "AssocInfoContainer_TMP";
  std::string trkhitnodename = "TRKR_HITSET";
  std::string trkhittmpnodename = "TRKR_HITSET_TMP";
  std::string trkhitassocname = "TRKR_HITTRUTHASSOC";
  std::string trkhitassoctmpname = "TRKR_HITTRUTHASSOC_TMP";
  std::string trkcluscontname = "TRKR_CLUSTER";
  std::string trkclusconttmpname = "TRKR_CLUSTER_TMP";
  std::string trkclusassocname = "TRKR_CLUSTERHITASSOC";
  std::string trkclusassoctmpname = "TRKR_CLUSTERHITASSOC_TMP";

  std::string micromegasgeomname = "CYLINDERGEOM_MICROMEGAS";
  std::string micromegasgeomfullname = "CYLINDERGEOM_MICROMEGAS_FULL";
};

#endif // FIXDSTPASS2_H
