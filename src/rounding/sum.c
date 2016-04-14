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
