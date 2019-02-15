AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include  \
  -I`root-config --incdir`

lib_LTLIBRARIES = \
  libmemsizetest.la

AM_CXXFLAGS = \
 -Werror

AM_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib

libmemsizetest_la_LIBADD = \
  -lphool \
  -lg4detectors \
  -lfun4all

pkginclude_HEADERS = \
  GenerateHits.h \
  GenerateRootHits.h \
  MyRootContainer.h \
  MyRootHit.h \
  MyRootHitv1.h

ROOTDICTS = \
  MyRootContainer_Dict.cc \
  MyRootHit_Dict.cc \
  MyRootHitv1_Dict.cc

if MAKEROOT6
  pcmdir = $(libdir)
  nobase_dist_pcm_DATA = \
    MyRootContainer_Dict_rdict.pcm \
    MyRootHit_Dict_rdict.pcm \
    MyRootHitv1_Dict_rdict.pcm
else
  ROOT5_DICTS = \
    GenerateRootHits_Dict.cc
endif

libmemsizetest_la_SOURCES = \
  $(ROOTDICTS) \
  $(ROOT5_DICTS) \
  GenerateHits.cc \
  GenerateRootHits.cc \
  MyRootContainer.cc \
  MyRootHitv1.cc \
  MyContainer.cc \
  MyHitv1.cc


# Rule for generating table CINT dictionaries.
%_Dict.cc: %.h %LinkDef.h
	rootcint -f $@ @CINTDEFS@ -c $(DEFAULT_INCLUDES) $(AM_CPPFLAGS) $^

#just to get the dependency
%_Dict_rdict.pcm: %_Dict.cc ;

################################################
# linking tests

noinst_PROGRAMS = \
  testexternals

BUILT_SOURCES = testexternals.cc

testexternals_SOURCES = testexternals.cc
testexternals_LDADD = libmemsizetest.la

testexternals.cc:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

clean-local:
	rm -f *Dict* $(BUILT_SOURCES) *.pcm
