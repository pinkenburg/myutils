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
  GenerateHitsPropMap.h \
  GenerateRootHits.h \
  GenerateRootVectorHits.h \
  GenerateRootHitsPropMap.h \
  GenerateRootTCHits.h \
  GenerateMultRootTObjHits.h \
  GenerateRootTObjHits.h \
  GenerateRootTMapHits.h \
  MyRootContainer.h \
  MyRootVectorContainer.h \
  MyRootTCContainer.h \
  MyRootTObjContainer.h \
  MyRootTMapContainer.h \
  MyRootHit.h \
  MyRootHitv1.h \
  MyRootHitv2.h

ROOTDICTS = \
  MyRootContainer_Dict.cc \
  MyRootVectorContainer_Dict.cc \
  MyRootTCContainer_Dict.cc \
  MyRootTObjContainer_Dict.cc \
  MyRootTMapContainer_Dict.cc \
  MyRootHit_Dict.cc \
  MyRootHitv1_Dict.cc \
  MyRootHitv2_Dict.cc

if MAKEROOT6
  pcmdir = $(libdir)
  nobase_dist_pcm_DATA = \
    MyRootContainer_Dict_rdict.pcm \
    MyRootVectorContainer_Dict_rdict.pcm \
    MyRootTCContainer_Dict_rdict.pcm \
    MyRootTObjContainer_Dict_rdict.pcm \
    MyRootTMapContainer_Dict_rdict.pcm \
    MyRootHit_Dict_rdict.pcm \
    MyRootHitv1_Dict_rdict.pcm \
    MyRootHitv2_Dict_rdict.pcm
else
  ROOT5_DICTS = \
    GenerateRootHits_Dict.cc
    GenerateRootTCHits_Dict.cc
    GenerateRootTMapHits_Dict.cc
endif

libmemsizetest_la_SOURCES = \
  $(ROOTDICTS) \
  $(ROOT5_DICTS) \
  GenerateHits.cc \
  GenerateHitsPropMap.cc \
  GenerateRootHits.cc \
  GenerateRootVectorHits.cc \
  GenerateRootHitsPropMap.cc \
  GenerateRootTCHits.cc \
  GenerateRootTObjHits.cc \
  GenerateMultRootTObjHits.cc \
  GenerateRootTMapHits.cc \
  MyRootContainer.cc \
  MyRootVectorContainer.cc \
  MyRootTCContainer.cc \
  MyRootTObjContainer.cc \
  MyRootTMapContainer.cc \
  MyRootHitv1.cc \
  MyRootHitv2.cc \
  MyContainer.cc \
  MyHitv1.cc \
  MyHitv2.cc


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
