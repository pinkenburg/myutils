#ifndef NODEDUMP_DUMPTRKRHITTRUTHASSOCTMP_H
#define NODEDUMP_DUMPTRKRHITTRUTHASSOCTMP_H

#include "DumpObject.h"

#include <string>

class PHNode;

class DumpTrkrHitTruthAssocTmp : public DumpObject
{
 public:
  DumpTrkrHitTruthAssocTmp(const std::string &NodeName);
  virtual ~DumpTrkrHitTruthAssocTmp() {}

 protected:
  int process_Node(PHNode *mynode);
};

#endif
