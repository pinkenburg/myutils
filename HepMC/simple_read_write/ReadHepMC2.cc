#include <iostream>

#include <HepMC/GenEvent.h>
#include <HepMC/ReaderAsciiHepMC2.h>
#include <HepMC/Print.h>

using namespace std;

int main()
{
    HepMC::ReaderAsciiHepMC2 input_file("hepmc2test.hepmc");
    while(!input_file.failed()) {
        HepMC::GenEvent evt(HepMC::Units::GEV,HepMC::Units::MM);
input_file.read_event(evt);
        // If reading failed - exit loop
        if( input_file.failed() ) break;
	cout << "read 1st event" << endl;
    }
    return 0;
}
