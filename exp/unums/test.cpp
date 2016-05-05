#include "unum.hpp"
#include <cstdio>

int main() {
  Unum unum;
  unum.setStore(0x0);
  printf("> %d\n", unum.isNaN());
  printf("> %d\n", unum.isZero());
  printf("> %d\n", unum.isNeg());
  return 0;
}
