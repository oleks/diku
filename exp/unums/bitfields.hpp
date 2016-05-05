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
// It remains to be tested that pure macros and masking would be more intricate
// than this.
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
  typename Store<Sum<sizes...>::value>::Type typeMask = (-1);


  template <unsigned idx, unsigned acc,
    unsigned x, unsigned... xs>
  friend unsigned getImpl(Bitfields<x, xs...>);

  template <unsigned idx, unsigned acc,
    unsigned x, unsigned... xs>
  friend void setImpl(Bitfields<x, xs...>&, unsigned value);


  template <unsigned idx, unsigned acc,
    unsigned x, unsigned... xs>
  friend unsigned maskUntilImpl(Bitfields<x, xs...>);
};


// Get a field.

template <unsigned idx, unsigned acc,
  unsigned size, unsigned... sizes>
unsigned getImpl(Bitfields<size, sizes...> bf)
{
  static_assert(idx <= sizeof...(sizes), "Invalid bitfield access");
  if (idx == 0) {
    if (size == 1) { // Gotta Go Fast!
      return (bf.store & 1u << acc) != 0;
    }
    return (bf.store >> acc) & ((1u << size) - 1);
  }
  return getImpl<idx - (idx ? 1 : 0), acc + (idx ? size : 0)>(bf);
}

template <unsigned idx, unsigned... sizes>
unsigned get(Bitfields<sizes...> bf)
{
  return getImpl<idx, 0>(bf);
}

// Set a field.

template <unsigned idx, unsigned acc,
  unsigned size, unsigned... sizes>
void setImpl(Bitfields<size, sizes...>& bf, unsigned v)
{
  static_assert(idx <= sizeof...(sizes), "Invalid bitfield access");
  if (idx == 0) {
    if (size == 1) { // Gotta Go Fast!
      bf.store = (bf.store & ~(1u << acc)) | ((v & 1u) << acc);
    } else {
      unsigned m = (1u << size) - 1;
      bf.store = (bf.store & ~(m << acc)) | ((v & m) << acc);
    }
    return;
  }
  setImpl<idx - (idx ? 1 : 0), acc + (idx ? size : 0)>(bf, v);
}

template <unsigned idx, unsigned... sizes>
void set(Bitfields<sizes...>& bf, unsigned v)
{
  setImpl<idx, 0>(bf, v);
}


// Get a field mask.

template <unsigned idx, unsigned acc,
  unsigned size, unsigned... sizes>
unsigned maskUntilImpl(Bitfields<size, sizes...> bf)
{
  static_assert(idx <= sizeof...(sizes), "Invalid bitfield access");
  if (idx == 0) {
    return (1u << size << acc) - 1;
  }
  return maskUntilImpl<idx - (idx ? 1 : 0), acc + (idx ? size : 0)>(bf);
}

template <unsigned idx, unsigned... sizes>
unsigned maskUntil(Bitfields<sizes...> bf)
{
  return maskUntilImpl<idx, 0>(bf);
}

template <unsigned idx, unsigned... sizes>
unsigned maskAfter(Bitfields<sizes...> bf)
{
  return ~(maskUntil<idx>(bf));
}

#endif // BITFIELDS_HPP
