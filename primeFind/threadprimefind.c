/**
 *Mohammed Bataineh
 *
 * This program has an error counting the correct amounts
 * of prime numbers. The prime number finder itself is correct
 * but the values being passed by pthreads are wrong somehow.
 *
 * I'll most likely end up going to your office hours and asking
 * you to write a "Threads for Dumbies" book for me. RIP me.
 *
 * **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

int sum = 0; //total amount of primes
int counter = 0;

void * primeFind(void *theRange)
{
	counter++; //to tell you how many threads are created
	int num;
	int* range = (int *) theRange;
	bool isPrime = true;
	printf("THREAD START min = %d\n", range[0]);
	
	printf("THREAD START max = %d\n\n", range[1]);

	if(range[0] <= 1)
		sum--;


	for(int testVal = range[0]; testVal < range[1]; testVal++)
		{
		num = 2;
		isPrime = true;
	
		while(isPrime && num < testVal/2)
			{
			if(testVal % num == 0)
				isPrime = false;
			num++;
			}
		if(isPrime)	
			sum++;
		}

	//not sure which exit to use
	pthread_exit(0);
	return NULL;

}


int main()
{
	//The variables to change
	int rangeMin = 100;
	int rangeMax = 1000000;
	int numOfThreads = 3; 
	

	int range[2] = {rangeMin, rangeMax};
	int rangeBetween = (rangeMax - rangeMin) / numOfThreads;
	range[0] = rangeMin;
	range[1] = rangeBetween + rangeMin; 

	pthread_t thread[numOfThreads];


	for(int i = 1; i <= numOfThreads; i++)
		{
		//take the max - min and divide that to find the different ranges to use.
		pthread_create(&thread[i-1], NULL, primeFind, (void *) range); 

		sleep(1); //had to sleep because the values were somehow getting messed up for following threads
		range[0] += rangeBetween;
		range[1] += rangeBetween;
		}

	for(int j = 0; j < numOfThreads; j++)
		pthread_join(thread[j], NULL);

	printf("Total prime nums: %d\n", sum);
	printf("Number of threads created: %d\n", counter);

	return 0;
}
