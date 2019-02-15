#include "MyRootContainer.h"

#include <cstdlib>

using namespace std;

MyRootContainer::MyRootContainer()
{
}

void
MyRootContainer::Reset()
{
   while(slatmap.begin() != slatmap.end())
     {
       delete slatmap.begin()->second;
       slatmap.erase(slatmap.begin());
     }
  return;
}

void
MyRootContainer::identify(ostream& os) const
{
   map<unsigned int,MyRootHit *>::const_iterator iter;
   os << "Number of slats: " << size() << endl;
   for (iter = slatmap.begin(); iter != slatmap.end(); ++iter)
     {
       os << "slat key 0x" << hex << iter->first << dec << endl;
       (iter->second)->identify();
     }
  return;
}

MyRootContainer::ConstIterator
MyRootContainer::AddScintillatorSlat(const unsigned int key, MyRootHit *newslat)
{
  if(slatmap.find(key)!=slatmap.end())
   {
     cout << "MyRootContainer::AddScintillatorSlatSpecifyKey: duplicate key: " << key << " exiting now" << endl;
     exit(1);
   }
  newslat->set_key(key);
  slatmap[key] = newslat;
  return slatmap.find(key);
}
