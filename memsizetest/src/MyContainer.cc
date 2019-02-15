#include "MyContainer.h"

#include <cstdlib>

using namespace std;

MyContainer::MyContainer()
{
}

void
MyContainer::Reset()
{
   while(slatmap.begin() != slatmap.end())
     {
       delete slatmap.begin()->second;
       slatmap.erase(slatmap.begin());
     }
  return;
}

void
MyContainer::identify(ostream& os) const
{
   map<unsigned int,MyHit *>::const_iterator iter;
   os << "Number of slats: " << size() << endl;
   for (iter = slatmap.begin(); iter != slatmap.end(); ++iter)
     {
       os << "slat key 0x" << hex << iter->first << dec << endl;
       (iter->second)->identify();
     }
  return;
}

MyContainer::ConstIterator
MyContainer::AddScintillatorSlat(const unsigned int key, MyHit *newslat)
{
  if(slatmap.find(key)!=slatmap.end())
   {
     cout << "MyContainer::AddScintillatorSlatSpecifyKey: duplicate key: " << key << " exiting now" << endl;
     exit(1);
   }
  newslat->set_key(key);
  slatmap[key] = newslat;
  return slatmap.find(key);
}
