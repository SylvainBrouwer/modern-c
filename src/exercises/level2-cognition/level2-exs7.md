### Exercise 7

Q: The function rat_get_prod can produce intermediate values that may cause it to produce wrong results,
even if the mathematical result of the multiplication is representable in rat. How is that?

A:
If `rat x` and/or `rat y` are not normalized, the product for the numerator or denominator in the intermediate representation may cause an overflow.