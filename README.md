freezing-dangerzone
===================

A static, fixed blocksize memory pool written in C, that can be used as a
building block to create larger more complex pools.

Includes a C++ wrapper, and an example application using a contrived texture
implementation.

Should build on most systems using:

  `make`

If available, you can check memory leaks/bounds:

  `make valgrind`