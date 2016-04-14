A simple example of the "creeping crud" problem with IEEE floating point.

With single-precision floats, 10 million additions of 0.1 to a starting value
of -500,000.0 (expected value 500,000.0), here is what we get with each of
the IEEE rounding modes:

    $ make
    ...
    ./sum_DOWNWARD.bin
    444000.125000
    ./sum_UPWARD.bin
    651563.250000
    ./sum_TONEAREST.bin
    456549.593750
    ./sum_TOWARDZERO.bin
    527320.187500

With double-precision floats, and 1 billion additions of 0.1 to a starting
value of -50,000,000.0, the story is a little better, but no more encouraging:

    $ make REAL=double N=1000000000 START=-50000000.0
    ...
    ./sum_DOWNWARD.bin
    49999997.176790
    ./sum_UPWARD.bin
    50000001.294038
    ./sum_TONEAREST.bin
    50000000.901881
    ./sum_TOWARDZERO.bin
    49999999.235414

To change the value added in each iteration, set `ADDEND`.

For instance, this example was inspired by the example on page 120 of [John L.
Gustafson, The End of Error: Unum Computing, CRC Press,
2015](https://www.crcpress.com/The-End-of-Error-Unum-Computing/Gustafson/9781482239867).
This example can be reproduced as follows:

    $ make N=1000000000 ADDEND=1.0 START=0.0
    ...
    ./sum_DOWNWARD.bin
    16777216.000000
    ./sum_UPWARD.bin
    inf
    ./sum_TONEAREST.bin
    16777216.000000
    ./sum_TOWARDZERO.bin
    16777216.000000

Actually, 100 million (rather than 1 billion) additions is sufficient to the
same end, and illustrates how "creeping crud" makes some additions "get stuck",
indicating, perhaps a fixed-point error analysis technique:

    $ make N=100000000 ADDEND=1.0 START=0.0
    ...
    ./sum_DOWNWARD.bin
    16777216.000000
    ./sum_UPWARD.bin
    16500654080.000000
    ./sum_TONEAREST.bin
    16777216.000000
    ./sum_TOWARDZERO.bin
    16777216.000000

Post-Scriptum
-------------

The `Makefile` is slightly unconventional as it always recompiles the source
code. This is because there is no way to ask if command-line arguments have
changed since last invocation. Perhaps it would've been better as a shell
script, but this gets the job done.
