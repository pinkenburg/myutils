#include <iostream>

#include <HepMC/GenEvent.h>
#include <HepMC/IO_GenEvent.h>

using namespace std;
int main()
{
HepMC::IO_GenEvent ascii_out("hepmc2test.hepmc",std::ios::out);

    HepMC::GenEvent* evt = new HepMC::GenEvent( 20, 1 );
    // define the units
    evt->use_units(HepMC::Units::GEV, HepMC::Units::MM);
    //
    // create vertex 1 and vertex 2, together with their inparticles
    HepMC::GenParticle *p1 = new HepMC::GenParticle( HepMC::FourVector(1,1,1,1),1, 0);
HepMC::GenParticle *p2 = new HepMC::GenParticle( HepMC::FourVector(2,2,2,2),2, 0);
HepMC::GenParticle *p3 = new HepMC::GenParticle( HepMC::FourVector(3,3,3,3),3, 0);
HepMC::GenParticle *p4 = new HepMC::GenParticle( HepMC::FourVector(4,4,4,4),4, 0);
    HepMC::GenVertex* v1 = new HepMC::GenVertex();
    HepMC::FourVector vtx1(11.,11.,11.,0.);
    v1->set_position(vtx1);
    HepMC::GenVertex* v2 = new HepMC::GenVertex();
    HepMC::FourVector vtx2(22.,22.,22.,0.);
    v2->set_position(vtx2);
    evt->add_vertex( v1 );
    v1->add_particle_in(p1);
    v1->add_particle_out(p2);
    v1->add_particle_out(p3);
    evt->add_vertex( v2 );
v2->add_particle_in(p3);
v2->add_particle_out(p4);
ascii_out << evt;
delete evt;
//ascii_out.close();
return 0;
}
