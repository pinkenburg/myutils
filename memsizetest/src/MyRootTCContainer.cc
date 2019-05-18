#include "MyRootTCContainer.h"

#include "MyRootHitv1.h"

#include <TClonesArray.h>
#include <cstdlib>

using namespace std;

static int TCSize = 1000;

MyRootTCContainer::MyRootTCContainer()
{
  slatmap = new TClonesArray("MyRootHitv1",TCSize);
}

MyRootTCContainer::~MyRootTCContainer()
{
  slatmap->Clear();
  delete slatmap;
}

unsigned int MyRootTCContainer::size() const
{
  return slatmap->GetEntriesFast();
}

void
MyRootTCContainer::Reset()
{
  slatmap->Clear();
  slatmap->Expand(TCSize);
  return;
}

void
MyRootTCContainer::identify(ostream& os) const
{
   map<unsigned int,MyRootHit *>::const_iterator iter;
   os << "Number of slats: " << size() << endl;
  return;
}

void
MyRootTCContainer::AddScintillatorSlat(const unsigned int key, MyRootHit *newslat)
{
  TClonesArray &Hit = *slatmap;
  // cout << "Adding hit, entries: " << slatmap->GetEntriesFast() << endl;
  // cout << "size: " << slatmap->GetSize() << endl;
  int size = slatmap->GetSize();
  if (size <= slatmap->GetEntriesFast())
  {
    slatmap->Expand(size+1000);
  }
  MyRootHit *hit = new(Hit[slatmap->GetEntriesFast()]) MyRootHitv1();
  hit->add_edep(newslat->get_edep(), newslat->get_eion(), newslat->get_light_yield());
  hit->set_key(newslat->get_key());
}
