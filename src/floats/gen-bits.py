#!/usr/bin/env python3

import random

BOUND = 1000

N_DIGITS = 1
N_BITS = 24

def showBits(n, bound):

  if n == 0:
    print("0"*N_BITS + "\t0\t.00\ty")
    return

  m = n

  j = 0
  while m < bound:
    m = m * 2
    j += 1

  m -= bound

  bits = []
  for i in range(N_BITS):
    m = m * 2
    if m > bound:
      bits.append("1")
      m -= bound
    else:
      bits.append("0")

  bottomed = "n"
  if m == 0:
    bottomed = "y"

  print("".join(bits) + "\t" + str(j) + ("\t.%02u" % n) + "\t" + bottomed)

def main():
  n = 0
  while n < BOUND:
    showBits(n, BOUND)
    n += 1

if __name__ == "__main__":
  main()
