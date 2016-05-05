#ifndef UNUM_HPP
#define UNUM_HPP

#include "bitfields.hpp"

class Unum {
  Bitfields<1,2,2,1,1,1> bf;
  static const unsigned sign      = 0;
  static const unsigned exponent  = 1;
  static const unsigned fraction  = 2;
  static const unsigned inexact   = 3;

public:
  Unum();

  void setStore(unsigned v);
  void setSign(unsigned v);
  void setInexact(unsigned v);

  bool isZero();
  bool isNaN();
  bool isNeg();
  bool isInf();
};

class Ubound {
  Unum left;
  Unum right;
};

#endif // UNUM_HPP
