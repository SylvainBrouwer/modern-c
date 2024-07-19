### Exercise 14
Q: Show that if the maximum unsigned is 2^{16}-1, then -0x8000 has value 32768, too.

A: 
First note: 0x8000 = 32768 > 2^{15} - 1, therefore 0x8000 and thus -0x8000 cannot be signed.
Now due to wraparound for unsigned values, -0x8000 is interpreted as 2^{16}-0x8000, which is also 32768.
