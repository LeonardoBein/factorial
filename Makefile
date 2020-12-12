############################# Makefile ##########################
all: threads

threads:
	gcc -Wall -o main main.c array.c process.c calc.c -lm -lpthread

clean:
	rm -rf *.o main