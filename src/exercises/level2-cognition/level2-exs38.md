### Exercise 38


Q: Find out which compiler arguments produce assembler output for your platform.


A:
On my platform (using gcc x86_64-win32-seh-rev0, Built by MinGW-Builds project), the -S flag generates assembly as output.
e.g. : `gcc -S filename.c`