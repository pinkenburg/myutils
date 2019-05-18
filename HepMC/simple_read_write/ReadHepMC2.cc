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
//  HepMC::IO_GenEvent *ascii_in = new HepMC::IO_GenEvent("/direct/phenix+u/pinkenbu/workarea/sPHENIX/gitrepov5/macros/macros/HepMC/hepmc2test.hepmc", std::ios::in);
  HepMC::IO_GenEvent *ascii_in = new HepMC::IO_GenEvent(argv[1], std::ios::in);
  int ifirst = 0;
  while(HepMC::GenEvent *evt = ascii_in->read_next_event()) {
    cout << "evt no: " << evt->event_number() << endl;
    evt->use_units(HepMC::Units::GEV, HepMC::Units::CM);
    evt->print();
    // If reading failed - exit loop
      ifirst = 1;
    for (HepMC::GenEvent::vertex_iterator v = evt->vertices_begin();
         v != evt->vertices_end();
         ++v)
    {
      cout << "vtx x: " << (*v)->position().x()
           << ", y: " << (*v)->position().y()
           << ", z: " << (*v)->position().z()
           << ", t: " << (*v)->position().t() << endl;
      for (HepMC::GenVertex::particle_iterator p =
	     (*v)->particles_begin(HepMC::children);
           p != (*v)->particles_end(HepMC::children); ++p)
      {
//	if (!(*p)->end_vertex())
	{
	cout << "px: " << (*p)->momentum().px() 
             << ", py: " << (*p)->momentum().py() 
             << ", pz: " << (*p)->momentum().pz() 
             << ", pid: " << (*p)->pdg_id() 
             << ", status: " << (*p)->status() 
	     << endl;
	}
      }
    }
  }
  if (! ifirst)
  {
        cout << ": error type: " << ascii_in->error_type()
             << ", rdstate: " << ascii_in->rdstate() << endl;
  }
  return 0;
}
