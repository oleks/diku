# Numerical Exploration with GDB

The GNU Debugger (GDB) is a ubiquitous debugging tool for systems programming
in the realm of Unix-like operating systems. Armed with GDB, you can explore
the run-time behaviour of _any_ binary.

The following note will attempt to introduce you to GDB by using it for the
exploration of the low-level behaviour of baseline numerical computations. This
is far from a conventional use of GDB: The hope is that you get both an
introduction to how computers perform numerical computation, as well as a
practical introduction to GDB.

GDB can relate each run-time computational step to either (1) a line of source
code you've written, or (2) the assembly code actually being run. If GDB has
support for your programming language, GDB can keep you informed about which
line of source code the binary is currently at. If not, it can at you about the
underlying assembly instructions being executed, the current state of the
registers and memory.
