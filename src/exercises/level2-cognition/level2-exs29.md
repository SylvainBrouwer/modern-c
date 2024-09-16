### Exercise 29


Q: Don’t try this allocation, but compute the size that would be needed on your platform. Is allocating such a vector feasible on your platform?


A:
- Est. 8.2 billion people in the world.
- On my system sizeof(double) = 8

Thus  this would allocate 8*(8.2*10^9) B = (65.6*10^9) / 1024^3 GB = ~61 GB of memory. Which is not feasible on my system.