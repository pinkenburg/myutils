#ifndef NODEDUMP_DUMPTRKRCLUSTERCONTAINERTMP_H
#define NODEDUMP_DUMPTRKRCLUSTERCONTAINERTMP_H

#include "DumpObject.h"

#include <string>

class PHNode;

class DumpTrkrClusterContainerTmp : public DumpObject
{
 public:
  DumpTrkrClusterContainerTmp(const std::string &NodeName);
  virtual ~DumpTrkrClusterContainerTmp() {}

 protected:
  int process_Node(PHNode *mynode);
};

#endif
