
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>






int main()
{
	int num;
	bool isPrime = true;	
	int primeCount = 0;

	int rangeMin = 100;
	int rangeMax = 1000000;

	printf("Finding primes in the range of [%d - %d]\n", rangeMin, rangeMax);

	if(rangeMin == 1)
		primeCount =- 1;

	for(int testval = rangeMin; testval < rangeMax; testval++)
		{
		num = 2;
		isPrime = true;
	
		while(isPrime && num < testval/2)
			{
			if(testval % num == 0)
				isPrime = false;
			num++;
			}
		if(isPrime)
			primeCount++;

		}
	
	printf("Number of Primes: %d\n", primeCount);
	return 0;
}
		

