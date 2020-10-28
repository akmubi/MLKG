#ifndef ___STATISTICAL_TESTS_H___
#	define ___STATISTICAL_TESTS_H___

#	define MIN_FREQUENCY_VALUE 5

/* Критерий согласия Пирсона (критерий согласия хи-квадрат) */

/* РАВНОМЕРНОЕ РАСПРЕДЕЛЕНИЕ */
// freq			- интервалы с частотами
// count		- количество интервалов
// start		- начало 0-го интервала времени
// inverval_size	- длина i-го интервала
// n			- число независимых испытаний
// chi_square		- эмпирическое значение частоты по критерию Пирсона
// k			- число степеней свободы
extern void pearson_uniform(unsigned int *freq, unsigned int count, unsigned int start, unsigned int inverval_size, int n, double *chi_square, int *k);

/* РАСПРЕДЕЛЕНИЕ ПУАССОНА */
// freq			- частоты
// count		- количество частот
// n			- количество испытаний
// chi_square		- эмпирическое значение частоты по критерию Пирсона
// k			- число степеней свободы
extern void pearson_poisson(unsigned int *freq, unsigned int count, int n, double *chi_square, int *k);


#endif // ___STATISTICAL_TESTS_H___