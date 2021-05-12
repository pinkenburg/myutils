#ifndef NODEDUMP_DUMPTRKRHITSETCONTAINERTMP_H
#define NODEDUMP_DUMPTRKRHITSETCONTAINERTMP_H

#include <nodedump/DumpObject.h>

#include <string>

class PHNode;

class DumpTrkrHitSetContainerTmp : public DumpObject
{
 public:
  DumpTrkrHitSetContainerTmp(const std::string &NodeName);
  virtual ~DumpTrkrHitSetContainerTmp() {}

 protected:
  int process_Node(PHNode *mynode);
};

#endif
