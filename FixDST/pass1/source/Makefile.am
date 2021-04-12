AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include \
  -I$(ROOTSYS)/include

AM_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib \
  -L$(OFFLINE_MAIN)/lib64

pkginclude_HEADERS = \
  TrkrClusterHitAssocTmp.h \
  TrkrHitTmp.h \
  fixdstpass1.h

ROOTDICTS = \
  TrkrClusterHitAssocTmp_Dict.cc \
  TrkrHitTmp_Dict.cc

pcmdir = $(libdir)
nobase_dist_pcm_DATA = \
  TrkrClusterHitAssocTmp_Dict_rdict.pcm \
  TrkrHitTmp_Dict_rdict.pcm

lib_LTLIBRARIES = \
  libfixdstpass1.la

libfixdstpass1_la_SOURCES = \
  fixdstpass1.cc \
  TrkrClusterHitAssocTmp.cc \
  TrkrClusterHitAssocTmp_Dict.cc \
  TrkrHitTmp.cc \
  TrkrHitTmp_Dict.cc

libfixdstpass1_la_LIBADD = \
  -lphool \
  -lSubsysReco

# Rule for generating table CINT dictionaries.
%_Dict.cc: %.h %LinkDef.h
	rootcint -f $@ @CINTDEFS@ $(DEFAULT_INCLUDES) $(AM_CPPFLAGS) $^

#just to get the dependency
%_Dict_rdict.pcm: %_Dict.cc ;


BUILT_SOURCES = testexternals.cc

noinst_PROGRAMS = \
  testexternals

testexternals_SOURCES = testexternals.cc
testexternals_LDADD   = libfixdstpass1.la

testexternals.cc:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

clean-local:
	rm -f $(BUILT_SOURCES)
