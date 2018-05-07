CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	
runTest: testme
	./testme

all: testme
	
default: testme runTest

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno *.out