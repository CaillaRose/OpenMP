serialSieve: serialSieve.c
	gcc -o serialSieve serialSieve.c

threadSieve: threadSieve.c
	gcc -fopenmp -o threadSieve threadSieve.c

gauss: gauss.c
	gcc -o gauss gauss.c

threadGauss: threadGauss.c
	gcc -fopenmp -o threadGauss threadGauss.c

all: serialSieve threadSieve gauss threadGauss

clean:
	rm serialSieve threadSieve gauss threadGauss
