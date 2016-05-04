#ifndef BITFIELDS_HPP
#define BITFIELDS_HPP

// The following class offers a C++-style approach to bit-fields, where in C we
// might use macros and masking, or actual bit-fields. It remains to be tested
// that bit-fields actually still are *that* slow, and that macros and masking
// would be more intricate than this.

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
template <> struct Store<8>   { typedef uint_fast8_t   Type; };
template <> struct Store<16>  { typedef uint_fast16_t  Type; };
template <> struct Store<32>  { typedef uint_fast32_t  Type; };
template <> struct Store<64>  { typedef uint_fast64_t  Type; };


// The Bitfields themselves.

template <unsigned... sizes>
struct Bitfields {
  typename Store<Sum<sizes...>::value>::Type store;

  template <unsigned idx, unsigned acc,
    unsigned x, unsigned... xs>
  friend unsigned getImpl(Bitfields<x, xs...>);

  template <unsigned idx, unsigned acc,
    unsigned x, unsigned... xs>
  friend void setImpl(Bitfields<x, xs...>&, unsigned value);
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
unsigned get(Bitfields<sizes...> bf) { return getImpl<idx, 0>(bf); }


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
void set(Bitfields<sizes...>& bf, unsigned v) { setImpl<idx, 0>(bf, v); }

#endif // BITFIELDS_HPP
