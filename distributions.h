#ifndef ___DISTRIBUTIONS_H___
#	define ___DISTRIBUTIONS_H___


// РАСПРЕДЕЛЕНИЕ ПУАССОНА 

/* X ~ Poisson(λ)*/
// rand_vars	- результирующий массив случайных величин
// count	- количество случайных величин
// lambda	- математическое ожидание случайных величин
extern void poisson		(unsigned int *rand_vars, int count, double lambda);


// РАВНОМЕРНОЕ РАСПРЕДЕЛЕНИЕ

/* X ~ Uniform(a, b) */
// rand_vars	- результирующий массив случайных величин
// count	- количество случайных величин
// a 		- начало отрезка
// b		- конец отрезка
extern void uniform		(double *rand_vars, unsigned int count, double a, double b);

#endif // ___DISTRIBUTIONS_H___