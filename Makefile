############################# Makefile ##########################
all: threads

threads:
	gcc -o main main.c array.c array_math.c process.c calc.c -lm

clean:
	rm -rf *.o main