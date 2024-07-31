Q: Surprisingly, this program even works for files with lines that have more than 31 characters. Why?

A:
`fgets` will move the FILE* pointer ahead in each call. 
So every call in the while loop will try to read 31 character from the stream, stopping at "\n" or EOF.
Only when a `fgets` call starts at EOF will it return a null pointer and exit the loop.
