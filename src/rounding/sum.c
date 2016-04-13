#include <stdio.h>

int main() {
  size_t i;

  float sum = 0.0;
  for (i = 0; i < 1000000000; ++i) {
    sum += 1.0;
  }
  printf("%f\n", sum);
}
