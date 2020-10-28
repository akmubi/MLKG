#include <math.h>
#include <stdio.h>
#include <malloc.h>

#include "statistical_tests.h"

#define SQRT3 1.732050807

/*
	Вычисление факториала числа
	Вход: value - число, факториал которого надо вычислить
	Выход: факториал числа value
*/
static unsigned int factorial(unsigned int value)
{
	unsigned int f = 1;
	for (unsigned int i = 1; i <= value; ++i)
		f *= i;
	return f;
}

/*
	Проверка Пуассоновской случайной величины по критерию Пирсона
	Вход:	freq - интервалы частотами
		count - количество интервалов
		start - начало 0-го интервала времени
		interval_size - длина i-го интервала
		n - количество испытаний
	Выход:
		chi_squared - эмпирическое значение частоты по критерию Пирсона
		k - число степеней свободы
*/
void pearson_uniform(unsigned int *freq, unsigned int count, unsigned int start, unsigned int interval_size, int n, double *chi_squared, int *k)
{
	// найдём середины интервалов
	int *x = malloc(count * sizeof(*x));
	for (int i = 0; i < count; ++i)
		x[i] = ( (2 * i + 1) * interval_size + 2 * start ) / interval_size;

	printf("x* :");
	for (int i = 0; i < count; ++i)
		printf(" %d", x[i]);

	// вычисляем выборочную среднюю
	double average = 0.0;
	for (int i = 0; i < count; ++i)
		average += x[i] * freq[i];
	average /= n;

	printf("\nAverage : %.4lf\n", average);

	// вычисляем среднеквадратическое отклонение
	double s = 0.0;
	for (int i = 0; i < count; ++i)
		s += (x[i] - average) * (x[i] - average) * freq[i];
	s /= n;
	printf("Variance : %.4lf\n", s);

	s = sqrt(s);
	printf("Standard deviation : %.4lf\n", s);

	free(x);

	// найдём оценки параметров a* и b*
	double a = average - SQRT3 * s;
	double b = average + SQRT3 * s;

	printf("a* = %.4lf, b* = %.4lf\n", a, b);

	// найдем плотность предполагаемого распределения
	double f = 1 / (b - a);
	printf("Density function : %.4lf\n", f);

	// найдём теоретические частоты
	double *theor = malloc(count * sizeof(*theor));
	
	theor[0] = n * f * (start + interval_size - a);
	
	for (int i = 1; i < count - 1; ++i)
		theor[i] = n * f * interval_size;
	
	theor[count - 1] = n * f * ( b - (interval_size * (count - 1) + start) );

	printf("Theoretical observations :");
	for (int i = 0; i < count; ++i)
		printf(" %.4lf", theor[i]);

	// вычислим эмпирическое значение хи-квардат критерия
	double sum = 0.0;
	for (int i = 0; i < count; ++i)
		sum += (freq[i] - theor[i]) * (freq[i] - theor[i]) / theor[i];

	free(theor);

	printf("\nchi squared statistic : %.4lf\n", sum);
	printf("degrees of freedom : %u\n", count - 3);

	*chi_squared = sum;
	*k = count - 3;
}


/*
	Проверка Пуассоновской случайной величины по критерию Пирсона
	Вход:	freq - частоты
		count - количество частот
		n - количество испытаний
	Выход:
		chi_squared - эмпирическое значение частоты по критерию Пирсона
		k - число степеней свободы
*/
void pearson_poisson(unsigned int *freq, unsigned int count, int n, double *chi_squared, int *k)
{
	// вычислим выборочную среднюю
	double average = 0.0;
	for (unsigned int i = 0; i < count; ++i)
		average += freq[i] * i;
	average /= n;
	printf("Average : %.4lf\n", average);

	// примем за lambda = выборочная средняя
	// вычислим вероятности по формуле p_i = exp(-lambda) * lambda^i / i!
	// вычислим теоретические частоты
	double *theor = malloc(count * sizeof(*theor));

	printf("Probabilities :");
	for (unsigned int i = 0; i < count; ++i)
	{
		double p = exp(-average) * pow(average, i) / (double)factorial(i);
		printf(" %.4lf", p);
		theor[i] = p;
	}
	
	printf("\nTheoretical observations :");
	for (unsigned int i = 0; i < count; ++i)
	{
		theor[i] *= n;
		printf(" %.4lf", theor[i]);
	}

	// объединим малочисленные частоты и соответствующие теоретические
	int last_index = count - 1;
	while (last_index > 0 && freq[last_index] < MIN_FREQUENCY_VALUE)
	{
		freq[last_index - 1] += freq[last_index];
		theor[last_index - 1] += theor[last_index];
		last_index--;
	}
	
	printf("\nAfter joining\n");
	printf("\tFrequencies :");
	for (int i = 0; i <= last_index; ++i)
		printf(" %u", freq[i]);
	
	printf("\n\tTheoretical frequencies :");
	for (int i = 0; i <= last_index; ++i)
		printf(" %.4lf", theor[i]);
	printf("\nlast_index : %d\n", last_index);

	// вычислим эмпирическое значение хи-квардат критерия
	double sum = 0.0;
	for (int i = 0; i <= last_index; ++i)
		sum += (freq[i] - theor[i]) * (freq[i] - theor[i]) / theor[i];

	free(theor);

	printf("chi squared statistic : %.4lf\n", sum);
	printf("degrees of freedom : %d\n", last_index - 1);

	*chi_squared = sum;
	*k = last_index - 1;
}