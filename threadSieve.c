#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

int main(int argc, char **argv)
{
    unsigned long int N = 16;
    unsigned long int i,j;
    int *primes,option,k=2,found;
    struct timeval t1, t2;
    double elapsedTime;
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
		
    primes = malloc(sizeof(int)*N);
    if(primes == NULL) {
		printf("Error: Failed to allocate memory.\n");
		exit(-1);
    }	
    for (i=2; i<N; i++) {
		primes[i] = 1;
    }
 
    gettimeofday(&t1, NULL);
    /*#pragma omp parallel 
    {
	tid= omp_get_thread_num();
	if (tid == 0) {	
	    nthreads = omp_get_num_threads();
	    printf("Number of threads: %d\n", nthreads);
	}*/
	
	while (k*k <= N) {
		#pragma omp parallel for
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

    gettimeofday(&t2, NULL);

	if (N<= 100) {
    	printf("\nPrime numbers from 0 to %d:\n\n", N);	
    	for (i=2; i<N; i++) {
			if (primes[i])
	    		printf("%d ", i);    
    	}
    	printf("\n");
	}

    elapsedTime = (t2.tv_sec - t1.tv_sec)*1000000;
    elapsedTime += (t2.tv_usec - t1.tv_usec);
    printf("\nElapsed Time = %.1f mu_seconds\n", elapsedTime);
			
    free(primes);
    return 0;
}