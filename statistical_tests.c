#include <malloc.h>
#include <math.h>

#include "statistical_tests.h"
#include "distributions.h"

static int combination(int n, int k)
{
	if (k >= n) return 1;
	
	int denominator = 1; 
	for (int i = n - k + 1; i <= n; ++i)
		denominator *= i;

	int numerator = 1;
	for (int i = 2; i <= k; ++i)
		numerator *= i;

	return denominator / numerator;
}


/*
*	Биномиальное распределение
*/

//	n - количество опытов
//	N - число независимых испытаний
//	p - вероятность появления события
double calculate_test_statistics_binomial(int n, int N, double p)
{	
	if (p < 0.0 || p > 1.0) return 0;

	// частоты (число опытов, в которых наблюдалось count
	// появлений события) 
	int *frequency = (int *)malloc((N + 1) * sizeof(int));
	for (int i = 0; i < n; ++i)
	{
		int count = 0;
		for (int j = 0; j < N; ++j)
			count += bernoulli(p);
		frequency[count]++;
	}

	double *threoretical = (double *)malloc((N + 1) * sizeof(double));
	for (int i = 0; i <= N; ++i)
	{
		double p = combination(N, i) * pow(p, i) * pow(1 - p, N - i);
		threoretical[i] = n * p;
	}

	double k = 0;
	for (int i = 0; i <= N; ++i)
		k += (frequency[i] - threoretical[i]) * (frequency[i] - threoretical[i]) / threoretical[i];

	free(threoretical);
	free(frequency);
	return k;
}