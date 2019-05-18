AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = \
  -I$(includedir) \
  -I/opt/sphenix/core/HepMC3/include \
  -I$(OFFLINE_MAIN)/include \
  -I`root-config --incdir`

AM_LDFLAGS = \
  -L$(libdir) \
  -L/opt/sphenix/core/HepMC3/lib \
  -L$(OFFLINE_MAIN)/lib \
  -L$(OPT_SPHENIX)/lib


bin_PROGRAMS = \
  WriteHepMC2 \
  WriteHepMC3 \
  ReadHepMC2 \
  ReadHepMC32 \
  ReadHepMC3

WriteHepMC2_CPPFLAGS = \
  -I$(includedir) \
  -I/opt/sphenix/core/HepMC-2.06.09/include \
  -I$(OFFLINE_MAIN)/include \
  -I`root-config --incdir`

WriteHepMC2_SOURCES = \
  WriteHepMC2.cc

WriteHepMC2_LDADD = \
  /opt/sphenix/core/HepMC-2.06.09/lib/libHepMC.so

ReadHepMC2_CPPFLAGS = \
  -I$(includedir) \
  -I/opt/sphenix/core/HepMC-2.06.09/include \
  -I$(OFFLINE_MAIN)/include \
  -I`root-config --incdir`

ReadHepMC2_SOURCES = \
  ReadHepMC2.cc

ReadHepMC2_LDADD = \
  /opt/sphenix/core/HepMC-2.06.09/lib/libHepMC.so

WriteHepMC3_SOURCES = \
  WriteHepMC3.cc

WriteHepMC3_LDADD = \
  -lHepMC

ReadHepMC3_SOURCES = \
  ReadHepMC3.cc

ReadHepMC32_SOURCES = \
  ReadHepMC32.cc

ReadHepMC3_LDADD = \
  -lHepMC

ReadHepMC32_LDADD = \
  -lHepMC

