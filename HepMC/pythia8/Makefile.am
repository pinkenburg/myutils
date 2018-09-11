AUTOMAKE_OPTIONS = foreign

INCLUDES = -I$(includedir) -I$(OFFLINE_MAIN)/include -I$(OFFLINE_MAIN)/include/Pythia8 -I$(OFFLINE_MAIN)/include/HepMC

AM_LDFLAGS = -L$(libdir) -L$(OFFLINE_MAIN)/lib

bin_PROGRAMS = pythia8HepMC

pythia8HepMC_SOURCES = main42.cc

pythia8HepMC_LDADD = -lpythia8 -lHepMC


