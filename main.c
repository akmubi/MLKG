#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#include "distributions.h"
#include "statistical_tests.h"

#define N 200
#define A 2
#define B 24
#define INTERVAL_SIZE 2

int main(void)
{
	double rand_vars[N];
	uniform(rand_vars, N, A, B);

	for (int i = 0; i < N; ++i)
	{
		printf("\t%05.2lf", rand_vars[i]);
		if ((i + 1) % 10 == 0)
			putchar('\n');
	}

	int interval_count = (B - A) / INTERVAL_SIZE;
	unsigned int intervals[(B - A) / INTERVAL_SIZE];
	memset(intervals, 0, sizeof(intervals));
	
	for (int i = 0; i < N; ++i)
	{
		int truncated = (int)rand_vars[i];
		truncated -= (truncated % INTERVAL_SIZE == 1);
		truncated /= INTERVAL_SIZE;
		intervals[truncated - 1]++;
	}

	printf("Intervals :");
	for (int i = 0; i < interval_count; ++i)
		printf(" %u", intervals[i]);
	putchar('\n');

	double chi_squared = 0.0;
	int k = 0;
	pearson_uniform(intervals, interval_count, A, INTERVAL_SIZE, N, &chi_squared, &k);

	return 0;
}

/*
#define N 200

int main(void)
{

	// сгенерировать массив случайных величин 
	double lambda = 0.6;
	unsigned int rand_vars[N];
	poisson(rand_vars, N, lambda);

	for (int i = 0; i < N; ++i)
	{
		printf(" %d", rand_vars[i]);
		if ((i + 1) % 10 == 0)
			putchar('\n');
	}

	// найти максимальный элемент (max) в этом массиве
	unsigned int max = -1;
	for (int i = 0; i < N; ++i)
		if (rand_vars[i] > max)
			max = rand_vars[i];
	printf("max : %u\n")

	// создать массив с длиной (max + 1)
	unsigned int *freq = malloc((max + 1) * sizeof(*freq));

	// заполнить этот массив (freq[x[i]]++)
	for (int i = 0; i < N; ++i)
		freq[rand_vars[i]]++;

	printf("Frequencies :");
	for (unsigned int i = 0; i <= max; ++i)
		printf(" %u", freq[i]);

	puts("\nPearson test");
	double chi_square = 0.0;
	int k = 0;
	pearson_poisson(freq, max + 1, N, &chi_square, &k);

	free(freq);
	return 0;
}*/