### Exercise 60

Q: Describe an error scenario in which this assumption is not fulfilled.

A:
Take for example the case where the order of encodings for uppercase letters are reversed such that `'Z' - 'A' = 25`.
In that case for `B`, `hexatridecimal` would return $10 + 24 - 25 = 9$. This is obviously incorrect.