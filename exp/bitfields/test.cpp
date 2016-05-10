#include "bitfields.hpp"
#include <cstdio>

int main() {
  Bitfields<2,4,2> bf;
  set<0>(bf, 3);
  set<1>(bf, 14);
  set<2>(bf, 3);
  printf("%x\n", get<0>(bf));
  printf("%x\n", get<1>(bf));

  return 0;
}
