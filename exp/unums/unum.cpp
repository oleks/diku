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
	unsigned m = maskAfter<0>(this->bf);
  // In the absence of a nan summary bit..
  // A unum is NaN if all bits after the sign bit are 1.
  return (m & this->bf.store) == (m & this->bf.typeMask);
}

bool
Unum::isZero()
{
  // In the absence of a zero summary bit..
  // A unum is zero if all bits after the sign bit are 0.
  return (maskAfter<0>(this->bf) & this->bf.store) == 0;
}

bool
Unum::isNeg()
{
  // In the absence of a neg summary bit..
  // A unum is negative if the sign bit is set, and it is not zero.
  return get<0>(this->bf) && !this->isZero();
}
