### Exercise 54

Q: Under what circumstances will this program finish with success or failure return codes?

A: 
The program finishes with EXIT_FAILURE if none of the files named in argv[] can be opened. 
As soon as one file can be opened it switches to EXIT_SUCCESS (even if all other files fail).