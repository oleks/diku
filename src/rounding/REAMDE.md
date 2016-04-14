A simple example of the ``creeping crud'' problem with floating point.

With single-precision floats, 10 million additions of 0.1 to a starting value
of -500,000.0 (expected value 500,000.0), here is what we get with each of
floating point's rounding modes:

    $ make
    ./sum_DOWNWARD.bin
    444000.125000
    ./sum_UPWARD.bin
    651563.250000
    ./sum_TONEAREST.bin
    456549.593750
    ./sum_TOWARDZERO.bin
    527320.187500

With double-preicision floats, and 1 billion addition of 0.1 to a starting
value of -50,000,000.0, the story is a little better, but no more encouraging:

    ./sum_DOWNWARD.bin
    49999997.176790
    ./sum_UPWARD.bin
    50000001.294038
    ./sum_TONEAREST.bin
    50000000.901881
    ./sum_TOWARDZERO.bin
    49999999.235414
