binaries=fwt fwt2d
all:
	gcc -Wall -Wextra -pedantic-errors fwt.c -o fwt -lm
	gcc -Wall -Wextra -pedantic-errors fwt2d.c -o fwt2d -lm
clean: 
	rm -f $(binaries) *.o
