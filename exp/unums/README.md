# unum

The unum is a variable bit-width number format.

A unum is composed of 6 fields:

1. a `sign` bit,
2. a variable-width `exponent`,
3. a variable-width `fraction`,
4. an `inexact` bit (called ubit in [1]),
5. a fixed-width `exponent` field size, and
6. a fixed-with `fraction` field size.

The exponent and fraction sizes are biased by 1.

**Hypothesis**: There may be benefits to fixing the exponent and fraction field
sizes at compile time for certain applications.

## Unum Layout With Conventional Bit-Widths

**Hypothesis**: It is best to consider the trade-offs that we'd have to make if
we were to adhere to conventional, fixed register width ISAs.

### 4 bits

There is not much freedom here:

* `sign`: 1
* `exponent`: 1 (exact)
* `fraction`: 1 (exact)
* `inexact`: 1
* `esize`: 0
* `fsize`: 0

There is no extra space for storing if this is the last unum in a ubound, so
this will have to be maintained extrinsically, i.e., you always either have a
collection of unums or a collection of ubounds.

### 8 bits

With 8 bits, we get a little bit more freedom.

Initially, we might consider to use all the bits:

* `sign`: 1
* `exponent`: 2 (max)
* `fraction`: 2 (max)
* `inexact`: 1
* `esize`: 1
* `fsize`: 1

Alternatively, we can introduce two summary bits:

* `negative`: 1
* `nan`: 1
* `sign`: 1
* `exponent`: 1 (max)
* `fraction`: 2 (max)
* `inexact`: 1
* `esize`: 0
* `fsize`: 1

Summary bits are great as they require no shifts, and it can suffice to
and-mask the representation and compare that with 0. It is noteworthy, that
conventional C/C++ compilers do not optimize bit-field access. (See also
[../bitfields](../bitfields).)

The `negative` summary bit is useful as there is both a positive and negative
zero, so checking the sign bit is insufficient to tell if a value is strictly
negative or not. The sign bit is also insufficient to tell if a value is less
than or equal to zero, again because there is also a positive zero. Checking
for zero requires checking if both exponent and fraction bits are set.

The `nan` summary bit is useful for a similar reason: checking for NaN requires
checking if _all_ bits, expect perhaps the sign bit, are set.

Another useful summary bit, which can put in place of either `negative` or
`nan`, is a so-called `2nd` bit, indicating whether the unum is the second unum
in a ubound or not. That is, if this information can't be stored extrinsically.

### 16 bits

If we think summary bits were a bad idea, we can gain a lot both in range and
precision:

* `sign`: 1
* `exponent`: 5 (max)
* `fraction`: 5 (max)
* `inexact`: 1
* `esize`: 2
* `fsize`: 2

Range however, is perhaps less important than precision, leaving space for
4 summary bits:

* Summary: 4
* `sign`: 1
* `exponent`: 2 (max)
* `fraction`: 5 (max)
* `inexact`: 1
* `esize`: 1
* `fsize`: 2

Three possible summary bits were described above. Two other useful summary bits
are `inf` and `zero` to check for infinity, and zero respectively.

### 32 bits

With 32 bits, we get slightly less freedom.

One option to have just one summary bit, bit keep a fairly high range:

* Summary: 2
* `sign`: 1
* `exponent`: 5 (max)
* `fraction`: 17 (max)
* `inexact`: 1
* `esize`: 2
* `fsize`: 4

We can gain summary bits by reducing the range:

* Summary: 6
* `sign`: 1
* `exponent`: 2 (max)
* `fraction`: 17 (max)
* `inexact`: 1
* `esize`: 1
* `fsize`: 4

Or by reducing the precision:

* Summary: 11
* `sign`: 1
* `exponent`: 5 (max)
* `fraction`: 9 (max)
* `inexact`: 1
* `esize`: 2
* `fsize`: 3

11 summary bits is beginning to sound a bit like "overfitting".

Juggling exponent and fraction maximum sizes is costly — they are halved or
doubled every time.

### 64 bits

TODO.

## References

1. John L. Gustafson. _The End of Error: Unum Computing_. CRC Press, 2015.
