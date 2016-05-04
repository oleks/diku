#include "bitfields.hpp"
#include <cstdio>

int main() {
  Bitfields<4,1,4,16,1,2,4> unum;
  unum.store = 0;
  set<1>(unum, 5);
  printf("> %x\n", get<1>(unum));
  printf("> %lx\n", unum.store);

  return 0;
}
