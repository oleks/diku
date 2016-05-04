#include <stdio.h>

#define SIZE (220)

#define VALUES { 0.1f, 0.3f, 0.7f }

static float ARRAY[] = VALUES;

int main() {
  float sum1 = 0.0f, sum2 = 0.0f, sum3 = 0.0f;
  size_t i, j;

  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < sizeof(ARRAY); ++j) {
      sum1 += ARRAY[j];
    }
  }

  for (j = 0; j < sizeof(ARRAY); ++j) {
    for (i = 0; i < SIZE; ++i) {
      sum2 += ARRAY[j];
    }
  }

  for (j = 0; j < sizeof(ARRAY); ++j) {
    sum3 += SIZE * ARRAY[j];
  }

  printf("%.9f\n%.9f\n%.9f\n", sum1, sum2, sum3);
  printf("%.3f %.3f %.3f\n", sum1, sum2, sum3);
}
