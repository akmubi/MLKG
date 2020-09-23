/*
*	Мультипликативный линейный конгруэнтный генератор с простым модулем:
*			Z[i] = (A * Z[i - 1] + C) (mod M), где
*	A = 630360016
*	C = 0
*	M = 2^31 - 1 (2147483647)
*/

#ifndef ___RAND_H___
#	define ___RAND_H___
#	include <stdint.h>

#	define FIRST16	65535		/* 2^16 - 1*/
#	define FIRST15	32767		/* 2^15 - 1*/
#	define M	2147483647		/* 2^31 - 1 */

/* A = MUL1 * MUL2 */
#	define MUL1	24112
#	define MUL2	26143

#	define INV_RAND_MAX 4.656612875e-10	/* 1 / (2^31 - 1) */

static int32_t prev_z = 1973272912; // 0;

static int32_t mrand()
{
	int32_t low16, high15;
	
	/*Z[i - 1] * MUL1 = high15 * MUL1 + low16 * MUL1 */
	
	/* Умножение первых 16-бит Z[i - 1] на MUL1 */
	low16 = (prev_z & FIRST16) * MUL1;

	/* Умножение старших (не считая знакового бита) 15-бит 
	*  на MUL1 и прибавление той части low16, которая
	*  выходит за границы первых 16-бит 
	*/
	high15 = (prev_z >> 16) * MUL1 + (low16 >> 16);

	/* Циклический сдвиг налево на 16-бит hig15,
	*  прибавление первых 16-ти бит log16 и
	*  вычитание модуля M
	*/
	prev_z = ( (high15 & FIRST15) << 16 ) + (high15 >> 15) + (low16 & FIRST16) - M;
	
	/* Если значение prev_z не выходило за границы M, 
	*  то вернуть это значение назад
	*/
	if (prev_z < 0) prev_z += M;

	/* Тоже самое, но для MUL2 */
	/*Z[i - 1] * MUL2 = high15 * MUL2 + low16 * MUL2 */
	low16 = (prev_z & FIRST16) * MUL2;
	high15 = (prev_z >> 16) * MUL2 + (low16 >> 16);
	prev_z = ( (high15 & FIRST15) << 16 ) + (high15 >> 15) + (low16 & FIRST16) - M;
	if (prev_z < 0) prev_z += M;

	return  prev_z;
}

#endif // ___RAND_H___