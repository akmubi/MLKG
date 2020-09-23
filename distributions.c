#include <math.h>

#include "rand.h"
#include "distributions.h"


/*
*	Равномерное распределение
*/

double standard_uniform()
{
	return mrand() * INV_RAND_MAX;
}

double uniform(double a, double b)
{
	return a + (b - a) * standard_uniform();
}


/*
*	Распределение Бернулли
*/

int bernoulli(double p)
{
	return (standard_uniform() <= p);
}

/*
*	Биномиальное распределение
*/

int binomial(int n, double p)
{
	int X = 0;
	for (int i = 0; i < n; ++i)
		X += bernoulli(p);
	return X;
}


/*
*	Распределение Пуассона
*/

int poisson(double lambda)
{
	double U = standard_uniform();
	
	int i = 0;
	double p = exp(-lambda);
	double F = p;

	for (; U >= F; ++i)
	{
		p = lambda * p / (i + 1);
		F += p;
	}
	return i;
}

double exponential(double lambda)
{
	/* Тут мы можем использовать лишь log(u) вместо
	*  log(1 - u), поскольку 1 - u и u имеют одно и
	*  то же распределение Uniform(0, 1)
	*/
	return -log(standard_uniform()) / lambda;
}

// TODO:
// 1. Лоу Кельтон + продолжение теории по терверу	(x)
// 2. закончить с дискретными						(v)
// 3. начать непрерывные							(v)
// 4. проверка по критерию Пирсона					(x)
// 5. просмотреть лекцию							(x)
// 6. конспект тервера								(x)