#include "MyHitv1.h"

using namespace std;

MyHitv1::MyHitv1():
  key(0xFFFFFFFF),
  edep(0),
  eion(0),
  light_yield(0)
{
  for (int i=0; i<2; i++)
  {
    x[i] = NAN;
    y[i] = NAN;
    z[i] = NAN;
    t[i] = NAN;
  }
}

short
MyHitv1::get_row() const
{
  return (key&0xFFFF);
}

short
MyHitv1::get_column() const
{
  return (key>>16);
}

void
MyHitv1::identify(std::ostream& os)
{
  os << "row " << get_row() << " ";
  os << " column " << get_column() << " ";
  os << " energy deposition " << get_edep();
  os << " ionization energy " << get_eion();
  os << " light yield " << get_light_yield();
  os << endl;
}
