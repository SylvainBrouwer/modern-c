### Exercise 5
Q: Describe the use of the parameters argc and argv in listing 3.1.

A: 
- argc indicates the number of command line args (including the program name which is at index 0).
- argv stores pointers to these args ending with an extra NULL pointer (as per the C specs).