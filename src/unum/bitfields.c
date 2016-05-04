#include <stdint.h>

static struct unum {
  unsigned int sign: 1;
  unsigned int exponent: 1;
  unsigned int fraction: 1;
  unsigned int inexact: 1;
} unum;

int main() {
  // Getting each bit-field takes a shift followed by an and-mask.
  return unum.fraction + unum.inexact;
}
