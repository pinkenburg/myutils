#include "MyRootHitv1.h"

using namespace std;

MyRootHitv1::MyRootHitv1():
  key(0xFFFFFFFF),
  edep(0),
  eion(0),
  light_yield(0)
{}

short
MyRootHitv1::get_row() const
{
  return (key&0xFFFF);
}

short
MyRootHitv1::get_column() const
{
  return (key>>16);
}

void
MyRootHitv1::identify(std::ostream& os) const
{
  os << "row " << get_row() << " ";
  os << " column " << get_column() << " ";
  os << " energy deposition " << get_edep();
  os << " ionization energy " << get_eion();
  os << " light yield " << get_light_yield();
  os << endl;
}
