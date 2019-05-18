#include <iostream>

#include <HepMC/GenEvent.h>
#include <HepMC/ReaderAscii.h>
#include <HepMC/WriterAscii.h>
#include <HepMC/Print.h>

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cout << "no argument given" << endl;
    cout << "usage: WriteHepMC3 <filename>" << endl;
    exit(1);
  }
  HepMC::WriterAscii outfile(argv[1]);
  int n=1;
  for (int j =1; j<3; j++)
  {
  HepMC::GenEvent *evt = new HepMC::GenEvent(HepMC::Units::GEV,HepMC::Units::MM);
  evt->set_event_number(n++);
auto heavyion = make_shared<HepMC::GenHeavyIon>();
heavyion->Ncoll_hard = 5;
heavyion->Ncoll = 20;
heavyion->Npart_proj = 378;
heavyion->event_plane_angle = 20.;
evt->set_heavy_ion(heavyion);
HepMC::FourVector mom1(1.1,1.2,1.3,1.4);
mom1 *= j*10;
HepMC::GenParticlePtr p1 = make_shared<HepMC::GenParticle>(mom1,1,1);
HepMC::FourVector mom_beam(2.1,2.2,2.3,2.4);
mom_beam *= j*10;
HepMC::GenParticlePtr p_beam = make_shared<HepMC::GenParticle>(mom_beam,1,1);

HepMC::FourVector mom2(2.1,2.2,2.3,2.4);
mom2 *= j*10;
HepMC::GenParticlePtr p2 = make_shared<HepMC::GenParticle>(mom2,2,2);
HepMC::FourVector mom3(3.1,3.2,3.3,3.4);
mom3 *= j*10;
HepMC::GenParticlePtr p3 = make_shared<HepMC::GenParticle>(mom3,3,3);
HepMC::FourVector mom4(4.1,4.2,4.3,4.4);
mom4 *= j*10;
HepMC::GenParticlePtr p4 = make_shared<HepMC::GenParticle>(mom4,4,4);

HepMC::FourVector vtx1(11.1,11.2,11.3,11.4);
vtx1 *= j*10;
HepMC::GenVertexPtr v1 = make_shared<HepMC::GenVertex>(vtx1);

HepMC::FourVector vtx2(22.1,22.2,22.3,22.4);
vtx2 *= j*10;
HepMC::GenVertexPtr v2 = make_shared<HepMC::GenVertex>(vtx2);
/*
evt->add_particle(p2);
evt->add_particle(p3);
*/
//evt->add_particle(p1);
//evt->add_particle(p_beam);
v1->add_particle_in(p_beam);
v1->add_particle_out(p1);
v1->add_particle_out(p2);
v2->add_particle_in(p2);
v2->add_particle_out(p3);
evt->add_vertex(v1);
evt->add_vertex(v2);
/*
evt->add_vertex(v2);

v1->add_particle_in(p1);
v1->add_particle_out(p2);
v1->add_particle_out(p3);
v2->add_particle_in(p3);
v2->add_particle_out(p4);
*/
outfile.write_event(*evt);
  }

outfile.close();
  cout << "done" << endl;
  return 0;
}
