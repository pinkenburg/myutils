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
    cout << "usage: ReadHepMC3 <filename>" << endl;
    exit(1);
  }
    HepMC::ReaderAscii input_file (argv[1]);
    int i=1;
    while(!input_file.failed()) {
      HepMC::GenEvent m_genevent;
        input_file.read_event(m_genevent);
        m_genevent.set_units(HepMC::Units::GEV,HepMC::Units::CM);
        // If reading failed - exit loop
        if( input_file.failed() ) break;
	if (i==1)
	{
            shared_ptr<HepMC::GenHeavyIon>     hi = m_genevent.attribute<HepMC::GenHeavyIon>("GenHeavyIon");
            if(hi) {
                cout << " Has GenHeavyIon:       ";
                HepMC::Print::line(hi);
            }
	}
        auto vtxvec = m_genevent.vertices();
	cout << "number of vertices: " << vtxvec.size() << endl;
	auto parvec =  m_genevent.particles();
	cout << "number of particles: " << parvec.size() << endl;
            HepMC::Print::listing(m_genevent);
//            HepMC::Print::content(m_genevent);

	    cout << "read event " << m_genevent.event_number() << endl;
	i++;
    }
    return 0;
}
