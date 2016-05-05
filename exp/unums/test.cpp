#include "unum.hpp"

#include <cassert>

void
test_isZero() {
  Unum unum;

  // Positive zero.
  unum.setStore(0x00);
  assert(unum.isZero() == 1);

  // Negative zero.
  unum.setStore(0x01);
  assert(unum.isZero() == 1);

  // Not zero.
  unum.setStore(0xff);
  assert(unum.isZero() == 0);
  unum.setStore(0x7f);
  assert(unum.isZero() == 0);
  unum.setStore(0xfe);
  assert(unum.isZero() == 0);
}

void
test_isNeg() {
  Unum unum;

  // Positive.
  unum.setStore(0x00);
  assert(unum.isNeg() == 0);
  unum.setStore(0xfe);
  assert(unum.isNeg() == 0);

  // Negative zero.
  unum.setStore(0x01);
  assert(unum.isNeg() == 0);

  // Negative.
  unum.setStore(0xff);
  assert(unum.isNeg() == 1);
  unum.setStore(0x7f);
  assert(unum.isNeg() == 1);
}

void
test_isNaN() {
  Unum unum;

  // Signalling NaN.
  unum.setStore(0xff);
  assert(unum.isNaN() == 1);

  // Queit NaN.
  unum.setStore(0xfe);
  assert(unum.isNaN() == 1);

  // Not NaN.
  unum.setStore(0x00);
  assert(unum.isNaN() == 0);
  unum.setStore(0x01);
  assert(unum.isNaN() == 0);
  unum.setStore(0x7f);
  assert(unum.isNaN() == 0);
}

void
test_isInf() {
  Unum unum;

  // +∞.
  unum.setStore(-1); // TODO: Do something more random here.
  unum.setSign(0);
  unum.setInexact(0);
  assert(unum.isInf() == 1);

  // -∞.
  unum.setStore(-1); // TODO: Do something more random here.
  unum.setSign(1);
  unum.setInexact(0);
  assert(unum.isInf() == 1);

  // Not ∞.
  unum.setStore(-1);
  unum.setInexact(1);
  assert(unum.isInf() == 0);

  unum.setStore(0);
  unum.setInexact(1);
  assert(unum.isInf() == 0);

  unum.setStore(42);
  unum.setInexact(1);
  assert(unum.isInf() == 0);
}

int main() {
  test_isZero();
  test_isNeg();
  test_isNaN();
  test_isInf();

  return 0;
}
