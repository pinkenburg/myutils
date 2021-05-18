#include "DumpAssocInfoContainerTmp.h"

#include <phool/PHIODataNode.h>

#include <fixdstpass1/AssocInfoContainerTmp.h>

#include <map>
#include <ostream>
#include <string>
#include <utility>

using namespace std;

typedef PHIODataNode<AssocInfoContainerTmp> MyNode_t;

DumpAssocInfoContainerTmp::DumpAssocInfoContainerTmp(const string &NodeName)
  : DumpObject(NodeName)
{
  return;
}

int DumpAssocInfoContainerTmp::process_Node(PHNode *myNode)
{
  AssocInfoContainerTmp *associnfocontainer = nullptr;
  MyNode_t *thisNode = static_cast<MyNode_t *>(myNode);
  if (thisNode)
  {
    associnfocontainer = thisNode->getData();
  }
  if (associnfocontainer)
  {
    associnfocontainer->identify(*fout);
  }
  return 0;
}
