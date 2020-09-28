#ifndef ___DISTRIBUTIONS_H___
#	define ___DISTRIBUTIONS_H___

/*
*  ДИСКРЕТНЫЕ СЛУЧАЙНЫЕ ВЕЛИЧИНЫ
*/


// РАСПРЕДЕЛЕНИЕ БЕРНУЛЛИ

/* X ~ Bernoulli(p) */
extern int bernoulli(double p);


// БИНОМИАЛЬНОЕ РАСПРЕДЕЛЕНИЕ

/* X ~ Binomial(n, p) */
extern int binomial(int n, double p);


// РАСПРЕДЕЛЕНИЕ ПУАССОНА 

/* X ~ Poisson(λ)*/
extern int poisson(double lambda);


/*
*  НЕПРЕРЫВНЫЕ СЛУЧАЙНЫЕ ВЕЛИЧИНЫ
*/


// РАВНОМЕРНОЕ РАСПРЕДЕЛЕНИЕ

/* X ~ Uniform(0, 1) */
extern double standard_uniform();

/* X ~ Uniform(a, b) */
extern double uniform(double a, double b);


// ЭКСПОНЕНЦИАЛЬНОЕ РАСПРЕДЕЛЕНИЕ

/* X ~ Exponential(λ) */
extern double exponential(double lambda);

#endif // ___DISTRIBUTIONS_H___