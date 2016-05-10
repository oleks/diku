#ifndef BITFIELDS_HPP
#define BITFIELDS_HPP

// A C++-style approach to efficient bit-fields.
//
// Bitfields uses C++ templates to generate (hopefully) efficient bit-fiddling
// code according to well-known bit-fiddling laws.
//
// Conventional bit-fields will do more than is necessary to access e.g. a
// 1-bit field. See bitfields.c for an example, and in particular, try to `make
// show_bitfields.o`.
//
// It remains to be shown that good old "manual" macros and masking would be
// more tedious than this.
//
// Heavily inspired by:
//
// Andrei Alexandrescu — Writing Quick Code in C++, Quickly
// https://youtu.be/ea5DiCg8HOY
//    Credit: Tudor Bosman

#include <cstdio>

#include <cstdint>  // uint_*

using namespace std;


// Compile-time summation.

template <unsigned... xs>
struct Sum;

template <unsigned x>
struct Sum<x> {
  enum { value = x };
};

template <unsigned x, unsigned... xs>
struct Sum<x, xs...> {
  enum { value = x + Sum<xs...>::value };
};


// Stores of various compile-time sizes.

template <unsigned n_bits>
struct Store;

// Specialize it for 8, 16, 32, and 64 bits.
template <> struct Store<4>   { typedef uint_fast8_t   Type; };
template <> struct Store<8>   { typedef uint_fast8_t   Type; };
template <> struct Store<16>  { typedef uint_fast16_t  Type; };
template <> struct Store<32>  { typedef uint_fast32_t  Type; };
template <> struct Store<64>  { typedef uint_fast64_t  Type; };


// The Bitfields themselves.

template <unsigned... sizes>
struct Bitfields {
  typename Store<Sum<sizes...>::value>::Type store;
  static const typename Store<Sum<sizes...>::value>::Type typeMask = (-1);


  template <unsigned idx, unsigned acc,
    unsigned x, unsigned... xs>
  unsigned getImpl();

  template <unsigned idx, unsigned acc,
    unsigned x, unsigned... xs>
  void setImpl(unsigned value);
};


// Get a field.

template <unsigned... sizes>
template <unsigned idx, unsigned acc,
  unsigned x, unsigned... xs>
unsigned Bitfields<sizes...>::getImpl()
{
  static_assert(idx <= sizeof...(xs), "Invalid bitfield access");
  if (idx == 0) {
    if (x == 1) { // Gotta Go Fast!
      return (this->store & 1u << acc) != 0;
    }
    return (this->store >> acc) & ((1u << x) - 1);
  }
  return this->getImpl<idx - 1, acc + x, xs...>();
}

template <unsigned idx, unsigned x, unsigned... xs>
unsigned get(Bitfields<x, xs...> bf)
{
  return bf.getImpl<idx, 0, x, xs...>();
}

// Set a field.

template <unsigned... sizes>
template <unsigned idx, unsigned acc,
  unsigned x, unsigned... xs>
void Bitfields<sizes...>::setImpl(unsigned v)
{
  static_assert(idx <= sizeof...(xs), "Invalid bitfield access");
  if (idx == 0) {
    if (x == 1) { // Gotta Go Fast!
      this->store = (this->store & ~(1u << acc)) | ((v & 1u) << acc);
    } else {
      unsigned m = (1u << x) - 1;
      this->store = (this->store & ~(m << acc)) | ((v & m) << acc);
    }
    return;
  }
  this->setImpl<idx - 1, acc + x, xs...>(v);
}

template <unsigned idx, unsigned x, unsigned... xs>
void set(Bitfields<x, xs...>& bf, unsigned v)
{
  bf.setImpl<idx, 0, x, xs...>(v);
}

#endif // BITFIELDS_HPP
