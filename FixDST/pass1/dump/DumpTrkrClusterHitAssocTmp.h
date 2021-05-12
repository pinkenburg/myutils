#ifndef NODEDUMP_DUMPTRKRCLUSTERHITASSOCTMP_H
#define NODEDUMP_DUMPTRKRCLUSTERHITASSOCTMP_H

#include "DumpObject.h"

#include <string>

class PHNode;

class DumpTrkrClusterHitAssocTmp : public DumpObject
{
 public:
  DumpTrkrClusterHitAssocTmp(const std::string &NodeName);
  virtual ~DumpTrkrClusterHitAssocTmp() {}

 protected:
  int process_Node(PHNode *mynode);
};

#endif
