#ifndef NODEDUMP_DUMPASSOCINFOCONTAINERTMP_H
#define NODEDUMP_DUMPASSOCINFOCONTAINERTMP_H

#include "DumpObject.h"

#include <string>

class PHNode;

class DumpAssocInfoContainerTmp : public DumpObject
{
 public:
  DumpAssocInfoContainerTmp(const std::string &NodeName);
  virtual ~DumpAssocInfoContainerTmp() {}

 protected:
  int process_Node(PHNode *mynode);
};

#endif
