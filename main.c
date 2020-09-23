#include <stdio.h>
#include "distributions.h"

int main(void)
{
	for (int i = 0; i < 10; ++i)
	{
		printf("%g\n", uniform(0, 100));
	}
	return 0;
}