#include "MyRootTMapContainer.h"

#include <TString.h>

#include <cstdlib>

using namespace std;

MyRootTMapContainer::MyRootTMapContainer()
{
}

void
MyRootTMapContainer::Reset()
{
  slatmap.DeleteAll();
  return;
}

void
MyRootTMapContainer::identify(ostream& os) const
{
   map<unsigned int,MyRootHit *>::const_iterator iter;
   os << "Number of slats: " << size() << endl;
  return;
}

void
MyRootTMapContainer::AddScintillatorSlat(const unsigned int key, MyRootHit *newslat)
{
  TString *bla = new TString(Form("%d",key));
  TObject *t1 = dynamic_cast<TObject *>(bla);
  TObject *t2 = dynamic_cast<TObject *>(newslat);
  slatmap.Add(t1,t2);
  return;
}
