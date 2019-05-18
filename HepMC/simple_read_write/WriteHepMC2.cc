#include <iostream>

#include <HepMC/GenEvent.h>
#include <HepMC/IO_GenEvent.h>

using namespace std;
int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cout << "no argument given" << endl;
    cout << "usage: WriteHepMC3 <filename>" << endl;
    exit(1);
  }
  HepMC::IO_GenEvent ascii_out(argv[1],std::ios::out);
  int n=1;
  for (int j =1; j<3; j++)
  {
  HepMC::GenEvent* evt = new HepMC::GenEvent( 20, 1 );
  evt->set_event_number(n++);
  // define the units

    evt->use_units(HepMC::Units::GEV, HepMC::Units::MM);
    //
    // create vertex 1 and vertex 2, together with their inparticles

    HepMC::FourVector mom1(1.1,1.2,1.3,1.4);
    mom1.setX(mom1.x() * j*10);
    mom1.setY(mom1.y() * j*10);
    mom1.setZ(mom1.z() * j*10);
    mom1.setT(mom1.t() * j*10);
    HepMC::GenParticle *p1 = new HepMC::GenParticle(mom1,1, 1);

HepMC::FourVector mom_beam(2.1,2.2,2.3,2.4);
    mom_beam.setX(mom_beam.x() * j*10);
    mom_beam.setY(mom_beam.y() * j*10);
    mom_beam.setZ(mom_beam.z() * j*10);
    mom_beam.setT(mom_beam.t() * j*10);
    HepMC::GenParticle *p_beam = new HepMC::GenParticle(mom_beam,1, 1);

HepMC::FourVector mom2(2.1,2.2,2.3,2.4);
    mom2.setX(mom2.x() * j*10);
    mom2.setY(mom2.y() * j*10);
    mom2.setZ(mom2.z() * j*10);
    mom2.setT(mom2.t() * j*10);
    HepMC::GenParticle *p2 = new HepMC::GenParticle(mom2,1, 1);

HepMC::FourVector mom3(3.1,3.2,3.3,3.4);
    mom3.setX(mom3.x() * j*10);
    mom3.setY(mom3.y() * j*10);
    mom3.setZ(mom3.z() * j*10);
    mom3.setT(mom3.t() * j*10);
    HepMC::GenParticle *p3 = new HepMC::GenParticle(mom3,1, 1);

   // HepMC::FourVector mom4(4.1,4.2,4.3,4.4);
   //  mom4.setX(mom4.x() * j*10);
   //  mom4.setY(mom4.y() * j*10);
   //  mom4.setZ(mom4.z() * j*10);
   //  mom4.setT(mom4.t() * j*10);
   //  HepMC::GenParticle *p4 = new HepMC::GenParticle(mom4,1, 1);

HepMC::FourVector vtx1(11.1,11.2,11.3,11.4);
    vtx1.setX(vtx1.x() * j*10);
    vtx1.setY(vtx1.y() * j*10);
    vtx1.setZ(vtx1.z() * j*10);
    vtx1.setT(vtx1.t() * j*10);
    HepMC::GenVertex* v1 = new HepMC::GenVertex();
    v1->set_position(vtx1);

HepMC::FourVector vtx2(22.1,22.2,22.3,22.4);
    vtx2.setX(vtx2.x() * j*10);
    vtx2.setY(vtx2.y() * j*10);
    vtx2.setZ(vtx2.z() * j*10);
    vtx2.setT(vtx2.t() * j*10);
    HepMC::GenVertex* v2 = new HepMC::GenVertex();
    v2->set_position(vtx2);

    evt->add_vertex( v1 );
    v1->add_particle_in(p_beam);
    v1->add_particle_out(p1);
    v1->add_particle_out(p2);

    evt->add_vertex( v2 );
    v2->add_particle_in(p2);
    v2->add_particle_out(p3);

    ascii_out << evt;
    delete evt;
  }
//ascii_out.close();
  return 0;
}
