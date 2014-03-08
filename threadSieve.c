#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

int main(int argc, char **argv)
{
    unsigned long int N;
    unsigned long int i,j,k=2;
    int option,found;
    struct timeval t1, t2, result;
    omp_set_num_threads(8);
		
    while ((option = getopt(argc, argv, "n:")) != -1) {
		switch(option) {
	
	    	case 'n':
			N = atol(optarg);
			break;

	    	default:
			printf("Enter a limit to print prime numbers up to.\n");
			exit(-1);
		}
    }

	int *primes;
	primes = (int *) malloc(N*sizeof(int));
	if (primes == NULL) {
		printf("ERROR: Failed to allocate memory.\n");
		exit(-1);
	}
			
    for (i=2; i<N; i++) {
		primes[i] = 1;
    }
 
    gettimeofday(&t1, NULL);
	while (k*k <= N) {
		#pragma omp parallel 
		{
			#pragma omp for
			for (i=k*k; i<=N; i+=k){
				primes[i] = 0;
			}
			found = FALSE;
			for (i=k+1; !found; i++) {
				if (primes[i]) {
					k = i;
					found = TRUE;
				}
			}
		}
	}		

    gettimeofday(&t2, NULL);

	if (N<= 100) {
    	printf("\nPrime numbers from 0 to %d:\n\n", N);	
    	for (i=2; i<N; i++) {
			if (primes[i])
	    		printf("%d ", i);    
    	}
    	printf("\n");
	}

	timersub(&t2, &t1, &result);
    printf("\nElapsed Time = %ld Seconds, %ld Microseconds\n\n", result.tv_sec, result.tv_usec);
	
	if (primes) {
		free(primes);
	}			
    return 0;
}
