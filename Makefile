binaries=fwt
all:
	gcc -Wall -Wextra -pedantic-errors fwt.c -o fwt -lm
clean: 
	rm -f $(binaries) *.o
