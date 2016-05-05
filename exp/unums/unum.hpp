#ifndef UNUM_HPP
#define UNUM_HPP

#include "bitfields.hpp"

#include <stddef.h>   // size_t
#include <stdint.h>   // uint_fast8_t

class Unum {
  Bitfields<1,2,2,1,1,1> bf;

public:
  Unum();

  void setStore(unsigned v);

  bool isNaN();
  bool isZero();
  bool isNeg();
};

class Ubound {
  Unum left;
  Unum right;
};

#endif // UNUM_HPP
