#include <unistd.h>
#include <stdio.h>

char fuckoff(double troll)
{
	while (troll > 10)
		troll -= 10;
	return (troll + '0');
}


double ft_bidule(double v)
{
	while (v > 1)
		v -= 1;
	return (v);
}

void ft_puttroll(double v)
{
	double c;
	char a;
	char lol;
	int b;

	c = v;
	while (c > 1)
	{
		a = fuckoff(c);
		write(1, &a, 1);
		c /= 10;
	}
	write(1, ".", 1);
	v = ft_bidule(v);
	lol = 0;
	while (v && v > 0)
	{
/*		lol++;
		if (lol == 6)
		{
			v *= 10;
			a = fuckoff(v);
			b = a - '0';
			v -= fuckoff(v) - '0';
			v *= 10;
            a = fuckoff(v);
			if (a - '0' > 5)
				b++;
			write (1, &b, 1);
			break ;
			}*/
		v *= 10;
		a = fuckoff(v);
		write(1, &a, 1);
		v -= fuckoff(v) - '0';
	}
}

int main(void)
{
	ft_puttroll(4567862.24464);
	dprintf(1, "\n%f\n", 42.24464);
	return (0);
}
