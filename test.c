#include <stdio.h>
#include <stdlib.h>

double ft_atod(char *str)
{
	double sup;
	double inf;

	sup = 0;
	while (*str >= '0' && *str <= '9')
		sup = sup * 10 + *str++ - '0';
	if (*str != '.')
		return (sup);
	str++;
	inf = 0;
	while (*str >= '0' && *str <= '9')
		inf = (inf * 10 + *str++ - '0');
	while (*--str != '.')
		inf /= 10;
	return (sup + inf);
}

int main(void)
{
	dprintf(1, "%f\n", ft_atod("425435430.00004524"));
	dprintf(1, "%f\n", 425435430.00004524);
	return (0);
}
