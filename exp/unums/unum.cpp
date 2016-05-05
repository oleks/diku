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
Unum::isZero()
{
  // In the absence of a zero summary bit..
  // A unum is zero if all bits after the sign bit are 0.
  unsigned m = maskAfter<this->sign>(this->bf);
  return (m & this->bf.store) == 0;
}

bool
Unum::isNaN()
{
  // In the absence of a nan summary bit..
  // A unum is NaN if all bits after the sign bit are 1.
  unsigned m = maskAfter<this->sign>(this->bf);
  return (m & this->bf.store) == (m & this->bf.typeMask);
}

bool
Unum::isNeg()
{
  // In the absence of a neg summary bit..
  // A unum is negative if the sign bit is set, and it is not zero.
  return get<this->sign>(this->bf) && !this->isZero();
}
