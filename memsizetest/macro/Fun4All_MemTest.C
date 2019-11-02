#if ROOT_VERSION_CODE >= ROOT_VERSION(6,00,0)
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllDummyInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>

#include <memsizetest/GenerateHits.h>
#include <memsizetest/GenerateHitsPropMap.h>
#include <memsizetest/GenerateRootHits.h>
#include <memsizetest/GenerateRootVectorHits.h>
#include <memsizetest/GenerateRootHitsPropMap.h>
#include <memsizetest/GenerateRootTCHits.h>
#include <memsizetest/GenerateRootTObjHits.h>
#include <memsizetest/GenerateMultRootTObjHits.h>
#include <memsizetest/GenerateRootTMapHits.h>

#include <phool/recoConsts.h>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libmemsizetest.so)
#endif

void Fun4All_MemTest(const int nevnt = 10)
{
  gSystem->Load("libfun4all.so");
  gSystem->Load("libmemsizetest.so");
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(1);
  recoConsts *rc = recoConsts::instance();
    rc->set_IntFlag("RANDOMSEED", 12345);

//    SubsysReco *genhits = new GenerateRootVectorHits();
//    SubsysReco *genhits = new GenerateRootHitsPropMap();
//   SubsysReco *genhits = new GenerateRootHits();
//   SubsysReco *genhits = new GenerateRootTObjHits();
   GenerateMultRootTObjHits *genhits = new GenerateMultRootTObjHits();
   genhits->SetNumObject(10);
    se->registerSubsystem(genhits);

    Fun4AllInputManager *in = new Fun4AllDummyInputManager("JADE");
    se->registerInputManager(in);

    Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", "genhits.root");
  // if (do_dst_compress) DstCompress(out);
    se->registerOutputManager(out);
    se->run(nevnt);
//    return;
    se->End();
    delete se;
    gSystem->Exit(0);

}

