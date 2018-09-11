#include <iostream>

#include <HepMC/GenEvent.h>
#include <HepMC/ReaderAscii.h>
#include <HepMC/WriterAscii.h>
#include <HepMC/Print.h>

using namespace std;

int main()
{
  HepMC::GenEvent *evt = new HepMC::GenEvent(HepMC::Units::GEV,HepMC::Units::MM);
  HepMC::WriterAscii outfile("hepmc3test.hepmc");
auto heavyion = make_shared<HepMC::GenHeavyIon>();
heavyion->Ncoll_hard = 5;
heavyion->Ncoll = 20;
heavyion->Npart_proj = 378;
heavyion->event_plane_angle = 20.;
evt->set_heavy_ion(heavyion);
HepMC::FourVector mom1(1.,1.,1.,1.);
HepMC::GenParticlePtr p1 = make_shared<HepMC::GenParticle>(mom1,1,1);
HepMC::FourVector mom2(2.,2.,2.,2.);
HepMC::GenParticlePtr p2 = make_shared<HepMC::GenParticle>(mom2,2,2);
HepMC::FourVector mom3(3.,3.,3.,3.);
HepMC::GenParticlePtr p3 = make_shared<HepMC::GenParticle>(mom3,3,3);
HepMC::FourVector mom4(4.,4.,4.,4.);
HepMC::GenParticlePtr p4 = make_shared<HepMC::GenParticle>(mom4,4,4);

HepMC::FourVector vtx1(11.,11.,11.,0.);
HepMC::GenVertexPtr v1 = make_shared<HepMC::GenVertex>(vtx1);
HepMC::FourVector vtx2(22.,22.,22.,0.);
HepMC::GenVertexPtr v2 = make_shared<HepMC::GenVertex>(vtx2);
evt->add_particle(p1);
evt->add_particle(p2);
evt->add_particle(p3);
evt->add_vertex(v1);
evt->add_vertex(v2);

//v1->add_particle_out(p1);
v1->add_particle_in(p1);
v1->add_particle_out(p2);
v1->add_particle_out(p3);
v2->add_particle_in(p3);
v2->add_particle_out(p4);

outfile.write_event(*evt);
outfile.close();
  cout << "done" << endl;
  return 0;
}
