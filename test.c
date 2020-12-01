#include <stdio.h>

int		main(void)
{
	int a = 15, b = 31;
	a |= 1 << 4;
	b &= ~(1 << 3);
	printf("%d   %d", a, b);
	return (0);
}
