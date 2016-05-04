#ifndef UNUM_HPP
#define UNUM_HPP

#include "bitfields.hpp"

#include <stddef.h>   // size_t
#include <stdint.h>   // uint_fast8_t

struct UnumEnv {
  size_t esizesize : 4;
  size_t fsizesize : 4;
};

class Unum {

private:
  struct UnumEnv env;
  uint8_t *unum;
};

class Ubound {

private:
  struct UnumEnv env;
  uint8_t *unum;
};

#endif // UNUM_HPP
