/// MPFR Version Insepctor
///
/// Shamelessly copied from the MPFR documentation:
/// http://www.mpfr.org/mpfr-current/mpfr.html#Installing-MPFR
///
/// GLPL Version 3, 29 June 2007
/// Copyright (c) 2007 Free Software Foundation, Inc. <http://fsf/org/>


#include <stdio.h>
#include <mpfr.h>
int main (void)
{
  printf ("MPFR library: %-12s\nMPFR header:  %s (based on %d.%d.%d)\n",
          mpfr_get_version (), MPFR_VERSION_STRING, MPFR_VERSION_MAJOR,
          MPFR_VERSION_MINOR, MPFR_VERSION_PATCHLEVEL);
  return 0;
}
