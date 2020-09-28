#ifndef ___STATISTICAL_TESTS_H___
#	define ___STATISTICAL_TESTS_H___
#	include <stdbool.h>

/* Критерий согласия Пирсона (критерий согласия хи-квадрат) */


// БИНОМИАЛЬНОЕ РАСПРЕДЕЛЕНИЕ

extern double calculate_test_statistics_binomial(int n, int N, double p);


#endif // ___STATISTICAL_TESTS_H___