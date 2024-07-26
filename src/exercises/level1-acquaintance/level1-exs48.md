Q: Prove equation (14). $$T_{fibCache(n)} = n \times C_3$$


A: 
Technically not the case as n=1 and n=2 have a different constant C0.
Then each computation for n>2 is a constant time lookup and addition with constant C3.
So:
- $$T_{fibCache(1)} = C_0$$
- $$T_{fibCache(2)} = C_0$$
- $$T_{fibCache(n)} = T_{fibCache(1)} + $$T_{fibCache(2)} + \Sigma_{i=3}^{n}C_{3} = 2C_{0} + (n-2)C_{3} = nC_{3} + (2C_{0} - 2C_{3}) = nC_{3} + constant$$

Asymptotically this goes to the equation 14.
