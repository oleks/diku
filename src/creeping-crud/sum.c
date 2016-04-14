#include <stdio.h>
#include <fenv.h>

int main() {
  size_t i;

  fesetround(ROUND);

  REAL sum = START_WITH;
  for (i = 0; i < N_ADDITIONS; ++i) {
    sum += ADDEND;
  }
  printf("%f\n", sum);
}

// Check that IEEE is actually in use on the target.
// http://stackoverflow.com/a/753018/5801152
#ifndef __STDC_IEC_559__
#error "Requires IEEE 754 floating point!"
#endif
