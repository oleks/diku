#include "unum.hpp"
#include <cstdio>

Unum::Unum()
{
  this->bf.store = 0;
}

void
Unum::setStore(unsigned v)
{
  this->bf.store = v;
}

bool
Unum::isNaN()
{
  // In the absence of a zero summary bit..
  // A unum is NaN if all bits after the sign bit are 1.
  return (getMaskAfter<0>(this->bf) & this->bf.store) ==
    getMaskAfter<0>(this->bf);
}

bool
Unum::isZero()
{
  // In the absence of a zero summary bit..
  // A unum is zero if all bits after the sign bit are 0.
  return (getMaskAfter<0>(this->bf) & this->bf.store) == 0;
}

bool
Unum::isNeg()
{
  // In the absence of a neg summary bit..
  // A unum is negative if the sign bit is set, and it is not zero.
  return (get<0>(this->bf) == 1) && !this->isZero();
}
