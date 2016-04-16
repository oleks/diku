// Check that IEEE 754 is actually in use on the target.
// http://stackoverflow.com/a/753018/5801152
#ifndef __STDC_IEC_559__
#error "Requires IEEE 754/IEC 60559 floating point!"
#endif

#include <fenv.h> // fesetround, FE_*
// If GCC adhered to the C11 standard wrt. <fenv.h> completely, we would do the
// following:
//
//    Tell the compiler that the floating-point environment might be modified
//    at run-time. This disables some inlining as well:
//
//    #pragma STDC FENV_ACCESS ON
//
// Instead, this is ensured through a compiler flag. See the Makefile.

#include <stdio.h> // fprintf, stderr
#include <stdlib.h> // EXIT_*


int main() {
  volatile size_t i;

  if (fesetround(ROUND) != 0) {
    fprintf(stderr, "Couldn't mandate rounding mode.\n");
    exit(EXIT_FAILURE);
  }

  feclearexcept(FE_ALL_EXCEPT);

  volatile REAL sum = START;
  for (i = 0; i < N; ++i) {
    sum += ADDEND;
  }

#if EXCEPT != 0
  int excepts = fetestexcept(FE_ALL_EXCEPT);

  if (excepts & FE_DIVBYZERO) fprintf(stderr, "DIVBYZERO\n");
  if (excepts & FE_INEXACT)   fprintf(stderr, "INEXACT\n");
  if (excepts & FE_INVALID)   fprintf(stderr, "INVALID\n");
  if (excepts & FE_OVERFLOW)  fprintf(stderr, "OVERFLOW\n");
  if (excepts & FE_UNDERFLOW) fprintf(stderr, "UNDERFLOW\n");
#endif

  printf("%f\n", sum);

  exit(EXIT_SUCCESS);
}
