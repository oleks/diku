#include <fenv.h> // fesetround, FE_*
#include <stdio.h> // fprintf, stderr
#include <stdlib.h> // EXIT_*

int main() {
  size_t i;

  if (fesetround(ROUND) != 0) {
    fprintf(stderr, "Couldn't mandate rounding mode.\n");
    exit(EXIT_FAILURE);
  }

  REAL sum = START_WITH;
  for (i = 0; i < N_ADDITIONS; ++i) {
    sum += ADDEND;
  }
  printf("%f\n", sum);

  exit(EXIT_SUCCESS);
}

// Check that IEEE is actually in use on the target.
// http://stackoverflow.com/a/753018/5801152
#ifndef __STDC_IEC_559__
#error "Requires IEEE 754 floating point!"
#endif
