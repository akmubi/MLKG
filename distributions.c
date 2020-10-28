#include <math.h>
#include <malloc.h>

#include "rand.h"
#include "distributions.h"

/*
	Генератор случайных величин с непрерывным равномерным распределением
	в диапазоне [a, b]
	Вход:	rand_vars - выходной массив случайных величин
		count - размер массива
		a - параметр положения
		b - параметр масштаба
	Выход:
		rand_vars - выходной массив случайных величин 
*/
void uniform(double *rand_vars, unsigned int count, double a, double b)
{
	
	for (int i = 0; i < count; ++i)
	{
		double u = mrand() * INV_RAND_MAX;
		rand_vars[i] = a + (b - a) * u;
	}
}

/*
	Генератор Пуассоновской случайной величины
	Вход:	rand_vars - выходной массив случайных величин
		count - размер массива
		lambda - интенсивность (мат. ожидание) случайной величины
	Выход:
		rand_vars - выходной массив случайных величин 
*/
void poisson(unsigned int *rand_vars, int count, double lambda)
{
	for (int i = 0; i < count; ++i)
	{
		unsigned int j = 0;
		double p = exp(-lambda);
		double F = p;
		
		// U ~ Uniform(0, 1)
		double U = 0.0;
		uniform(&U, 1, 0, 1);

		for (; U >= F; ++j)
		{
			p = lambda * p / (j + 1);
			F += p;
		}
		rand_vars[i] = j;
	}
}