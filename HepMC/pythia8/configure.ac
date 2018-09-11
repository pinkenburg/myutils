AC_INIT(configure.in)

AM_INIT_AUTOMAKE(pythia8HepMC, 1.00)

AC_PROG_CXX(CC g++)
AC_PROG_LIBTOOL

if test $ac_cv_prog_gxx = yes; then
  CXXFLAGS="$CXXFLAGS -Wall -pthread -Werror"
fi

AC_OUTPUT(Makefile)
