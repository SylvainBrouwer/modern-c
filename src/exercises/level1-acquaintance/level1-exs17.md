### Exercise 17

Q: Under the assumption that the maximum value for unsigned int is 0xFFFFFFFF, prove that -0x80000000 == 0x80000000.

A:
unsinged 0xFFFFFFFF = 2^{32} - 1
assuming one sign bit, the max signed value would be 2^{31} - 1 < 0x80000000 = 2^{31}.
0x800000000 is therefore interpreted as an unsigned value, thus -0x80000000 is also unsigned.
due to integer underflow: -0x80000000 = 0xFFFFFFFF + 1 - 0x80000000 = 0x80000000