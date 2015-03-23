#include "../includes/computorv1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//clear && make re && ./computor "- + -5 * X ++ -2148000 *+ X^1 - - X^1 = 8 -+--4 + 4^"
void		ft_putnbr(int n)
{
	char	buff[2];

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		buff[0] = n % 10;
		write(1, buff, 1);
	}
	else
	{
		buff[0] = n + '0';
		write(1, buff, 1);
	}
}

void		ft_putstrarray(char **str)
{
	size_t	i;

	i = 0;
	if (str && str[i])
	{
		write(1, "{", 1);
		while (str[i])
		{
			write(1, " \"", 2);
			write(1, str[i], strlen(str[i]));
			write(1, "\",", 2);
			i++;
		}
		write(1, "\b }", 3);
	}
}

void				*ft_memalloc(size_t size)
{
	void			*memory;
	unsigned int	counter;
	char			*explorer;

	counter = 0;
	if (!size)
		return (NULL);
	if (!(memory = (void *)malloc(size)))
		return (NULL);
	explorer = (char *)memory;
	if (memory != NULL)
	{
		while (counter++ < size)
			*explorer++ = 0;
	}
	return (memory);
}

char	*ft_strnew(size_t size)
{
	return (ft_memalloc(size + 1));
}

static char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*new;
	size_t		c;

	c = 0;
	if (s)
	{
		if (!(new = ft_strnew(len)))
			return (NULL);
		c = 0;
		while (c < len)
		{
			new[c] = s[start + c];
			c++;
		}
		return (new);
	}
	return (NULL);
}

static size_t	ft_nbr_words(char const *s, char c)
{
	int			i;
	int			nbr;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] != '\0' || s[i - 1] != c)
			nbr++;
	}
	return (nbr);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**str;
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_nbr_words(s, c);
	str = (char **)malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		j = 0;
		while (*s && *s == c)
			s = s + 1;
		while (*(s + j) && *(s + j) != c)
			j++;
		*(str++) = ft_strsub(s, 0, j);
		s = s + j;
		i++;
	}
	*str = NULL;
	return (str - len);
}

int		ft_split(t_env *e)
{
	char	**total;

	total = ft_strsplit(e->minimized, '=');
	if (!(total[0] && total[1] && !total[2]))
		return (0);
	e->e1.str = total[0];
	e->e2.str = total[1];
	return (1);
}

int			ft_parsing_error(char *str, char here, char asked)
{
	dprintf(1, "Parsing error with line '%s' : %c instead of %c\n", str, here, asked);
	return (0);
}

char	*ft_getreduced(char *ptr)
{
	char	*str;
	char	*p;

	if (!(str = (char *)malloc(sizeof(char) * strlen(ptr) + 1)))
		return (0);
	p = str;
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\n' && *ptr != '\t')
			*p++ = *ptr;
		ptr++;
	}
	*p = '\0';
	return (str);
}

void	ft_simplify(char **ptr)
{
	char	*p;

	if (!*(p = *ptr))
		return ;
	while (*(p + 1))
	{
		if (*p == '+' && (*(p + 1) == '+' || *(p + 1) == '-'))
			*p = ' ';
		else if (*p == '-' && *(p + 1) == '+')
		{
			*p = ' ';
			*(p + 1) = '-';
		}
		else if (*p == '-' && *(p + 1) == '-')
		{
			*p = ' ';
			*(p + 1) = '+';
		}
		else if (*p == '^' && *(p + 1) == '+')
		{
			*p = ' ';
			*(p + 1) = '^';
		}
		p++;
	}
}

char	*ft_simplified(char *str)
{
	char	*tmp;
	char	*ret;

	tmp = ft_getreduced(str);
	ft_simplify(&tmp);
	ret = ft_getreduced(tmp);
	free(tmp);
	ft_simplify(&ret);
	tmp = ft_getreduced(ret);
	free(ret);
	return (tmp);
}

int		ft_equalserror(char *str)
{
	char *ptr;

	if (!strchr(str, '='))
	{
		write(1, "\e[1;31merror: \e[0m\e[1;29mno equality :\e[0m\n", 43);
		write(1, str, strlen(str));
		write(1, "\n", 1);
		return (0);
	}
	write(1, "\e[1;31merror: \e[0m\e[1;29mtoo many equalities :\e[0m\n", 51);
	write(1, str, strlen(str));
	ptr = str;
	write(1, "\n\e[1;31m", 8);
	while (*ptr)
	{
		if (*ptr == '=')
			write(1, "~", 1);
		else
			write(1, " ", 1);
		ptr++;
	}	
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_getexpressions(t_env *e, char *line)
{
	char	*cptr;
	char	*tmp;

	if (!(cptr = strchr(line, '=')) || strchr(cptr + 1, '='))
		return (ft_equalserror(line));
	*cptr++ = '\0';
	if (!(e->e1.str = (char *)malloc(sizeof(char) * strlen(line) + 2)))
		return (0);
	e->e1.str[0] = '+';
	strcpy(e->e1.str + 1, line);
	tmp = ft_simplified(e->e1.str);
	free(e->e1.str);
	e->e1.str = tmp;
	if (!(e->e2.str = (char *)malloc(sizeof(char) * strlen(cptr) + 2)))
		return (0);
	e->e2.str[0] = '+';
	strcpy(e->e2.str + 1, cptr);
	tmp = ft_simplified(e->e2.str);
	free(e->e2.str);
	e->e2.str = tmp;
	return (1);
}

// int		ft_decompose(t_env *e)


int		ft_invalidcharacters(char *str)
{
	char *ptr;

	ptr = str;
	write(1, "\e[1;31merror: \e[0m\e[1;29minvalid character(s) :\e[0m\n", 52);
	write(1, str, strlen(str));
	write(1, "\n\e[1;31m", 8);
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' &&
			!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
			*ptr != '-' && *ptr != '*' && *ptr != '=' && *ptr != '.')
		{
			if (*ptr == 'X' && *(ptr + 1) == '^')
			{
				write (1, "  ", 2);
				ptr++;
			}
			else if (!(*(ptr + 1) == ' ' || *(ptr + 1) == '\n' ||
				*(ptr + 1) == '\t' || !*(ptr + 1)))
				write(1, "~", 1);
			else
				write(1, " ", 1);
		}
		else
			write (1, " ", 1);
		ptr++;
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_checkcharacters(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' && *ptr != '.' &&
			!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
			*ptr != '-' && *ptr != '*' && *ptr != '=' && *ptr != '^')
		{
			if (*ptr == 'X' && *(ptr + 1) == '^')
				ptr++;
			else if (*ptr != 'X' || (*ptr == 'X' && *(ptr + 1) &&
				*(ptr + 1) != ' ' && *(ptr + 1) != '\n' &&
				*(ptr + 1) != '\t' && (*(ptr + 1) != '~')))
				return (0);
		}
		ptr++;
	}
	return (1);
}

int		ft_invalidxpressions(t_env e)
{
	// char *ptr;

	// ptr = str;
	write(1, "\e[1;31merror: \e[0m\e[1;29minvalid expression :\e[0m\n", 50);
	// write(1, str, strlen(str));
	// write(1, "\n\e[1;31m", 8);
	// while (*ptr)
	// {
	// 	if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' &&
	// 		!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
	// 		*ptr != '-' && *ptr != '*' && *ptr != '=')
	// 	{
	// 		if (*ptr == 'X' && *(ptr + 1) == '^')
	// 		{
	// 			write (1, "  ", 2);
	// 			ptr++;
	// 		}
	// 		else
	// 			write(1, "~", 1);
	// 	}
	// 	else
	// 		write (1, " ", 1);
	// 	ptr++;
	// }
	// write(1, "\e[0m\n\n", 5);
	return (0);
	(void)e;
}

int		ft_checkexpression(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' &&
			!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
			*ptr != '-' && *ptr != '*' && *ptr != '=')
		{
			if (*ptr == 'X' && *(ptr + 1) == '^')
				ptr++;
			else
				return (0);
		}
		ptr++;
	}
	return (1);
	(void)str;
}

int		ft_checkexpressions(t_env e)
{
	dprintf(1, "e1 = '%s'\ne2 = '%s'\n", e.e1.str, e.e2.str);
	if (!(ft_checkexpression(e.e1.str)) ||
		!(ft_checkexpression(e.e2.str)))
		return (0);
	return (1);
}

int		ft_nextsign(char *str)
{
	char	*ptr;
	char	sign;

	sign = '+';
	ptr = str;
	while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t' ||
		*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign = (sign == '+') ? '-' : '+';
		ptr++;
	}
	return (sign);
}

int		ft_invalidpowerssign(char *str)
{
	char *ptr;

	write(1, "\e[1;31merror: \e[0m\e[1;29minvalid power sign(s) :\e[0m\n", 53);
	write(1, str, strlen(str));
	write(1, "\n\e[1;31m", 8);
	ptr = str;
	while (*ptr)
	{
		write (1, " ", 1);
		if (*ptr == '^')
			if (ft_nextsign(ptr + 1) == '-')
			{
				ptr++;
				while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t' ||
						*ptr == '+' || *ptr == '-')
				{
					write(1, "~", 1);
					ptr++;
				}
			}
		ptr++;
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_checkpowerssign(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '^')
			if (ft_nextsign(ptr + 1) == '-')
				return (0);
		ptr++;
	}
	return (1);
}

int		ft_checkval(char *str)
{
	unsigned int	value;
	unsigned int	max;
	char			*ptr;

	ptr = str;
	value = 0;
	max = (ft_nextsign(ptr) == '+') ? MAX_INT : MIN_INT;
	while (*ptr == '+' || *ptr == '-' ||
		*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
		ptr++;
	while ((*ptr >= '0' && *ptr <= '9') ||
		*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
	{
		if (*ptr >= '0' && *ptr <= '9')
		{
			if (((value = value * 10 + *ptr - '0') > max))
				return (0);
		}
		ptr++;
	}
	return (1);
}

int		ft_checkextremval(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if ((*ptr >= '0' && *ptr <= '9') || *ptr == '+' || *ptr == '-')
		{
			if (!ft_checkval(ptr))
				return (0);
			while (*ptr == '+' || *ptr == '-' ||
				*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
				ptr++;
			while ((*ptr >= '0' && *ptr <= '9') ||
				*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
				ptr++;
		}
		else
			ptr++;
	}
	return (1);
}

int		ft_invalidextrem(char *str)
{
	char	*ptr;
	char	c;

	ptr = str;
	write(1, "\e[1;35mwarning: \e[0m\e[1;29mint limits overreached :\e[0m\n", 56);
	write(1, str, strlen(str));
	write(1, "\n\e[1;35m", 8);
	while (*ptr)
	{
		if ((*ptr >= '0' && *ptr <= '9') || *ptr == '+' || *ptr == '-')
		{
			c = (ft_checkval(ptr)) ? ' ' : '~';
			while (*ptr == '-' || *ptr == '+' ||
				*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
				write(1, &c, (ptr++ > 0));
			while ((*ptr >= '0' && *ptr <= '9') ||
				*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
				write(1, &c, (ptr++ > 0));
		}
		else
			write(1, " ", (ptr++ > 0));
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_error(char n)
{
	if (n == 1)
		write(1, "\e[1;31mOne error detected, can't process without correction\e[0m\n", 64);
	else
	{
		write(1, "\e[1;31m", 7);
		ft_putnbr(n);
		write(1, " errors detected, can't process without correction\e[0m\n", 57);
	}
	return (0);
}

int		ft_warning(char n)
{
	if (n == 1)
		write(1, "\e[1;35mOne warning detected, remember, answer might be wrong\e[0m\n", 65);
	else
	{
		write(1, "\e[1;35m", 7);
		ft_putnbr(n);
		write(1, " warnings detected, remember, answer might be wrong\e[0m\n", 56);
	}
	return (0);
}

int		ft_checkpowers(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == 'X')
		{
			ptr++;
			while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
				ptr++;
			if (*ptr != '^' && *ptr != '+' && *ptr != '-' && *ptr)
				return (0);
		}
		else
			ptr++;
	}
	return (1);
}

int		ft_invalidpower(char *str)
{
	char *ptr;
	char *p;
	char c;

	ptr = str;
	write(1, "\e[1;31merror: \e[0m\e[1;29minvalid power :\e[0m\n", 45);
	write(1, str, strlen(str));
	write(1, "\n\e[1;31m", 8);
	while (*ptr)
	{
		if (*ptr == 'X')
		{
			p = ptr + 1;
			while (*p == ' ' || *p == '\n' || *p == '\t')
				p++;
			c = (*p != '^' && *p != '+' && *p != '-' && *p) ? '~' : ' ';
			while (p != ptr)
				write(1, &c, (ptr++ > 0));
		}
		else
			write(1, " ", (ptr++ > 0));
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_checklast(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	while (ptr != str && *ptr != '+' && *ptr != '-' && *ptr != '*')
		ptr--;
	if (ptr == str)
		return (1);
	while (*ptr)
	{
		if (*ptr == 'X' || (*ptr >= '0' && *ptr <= '9'))
			return (1);
		ptr++;
	}
	return (0);
}

int		ft_invalidlast(char *str)
{
	char *ptr;
	char *p;

	ptr = str;
	write(1, "\e[1;31merror: \e[0m\e[1;29minvalid last :\e[0m\n", 44);
	write(1, str, strlen(str));
	write(1, "\n\e[1;31m", 8);
	while (*ptr)
		ptr++;
	while (ptr != str && *ptr != '+' && *ptr != '-' && *ptr != '*')
		ptr--;
	p = ptr;
	while (p != str)
	{
		write(1, " ", 1);
		p--;
	}
	while (*ptr)
	{
		write(1, "~", 1);
		ptr++;
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_checkpowervalue(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '^')
		{
			ptr++;
			while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
				ptr++;
			while (*ptr == '+' || *ptr == '-')
				ptr++;
			if (*ptr < '0' || *ptr > '9')
			{
				if (*ptr == '.')
				{
					ptr++;
					while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
						ptr++;
					if (*ptr < '0' || *ptr > '9')
						return (0);
				}
				else
					return (0);
			}
		}
		else
			ptr++;
	}
	return (1);
}

int		ft_invalidpowersvalue(char *str)
{
	char *ptr;
	char *p;
	char c;

	ptr = str;
	write(1, "\e[1;31merror: \e[0m\e[1;29minvalid power value(s) :\e[0m\n", 54);
	write(1, str, strlen(str));
	write(1, "\n\e[1;31m", 8);
	while (*ptr)
	{
		if (*ptr == '^')
		{
			p = ptr + 1;
			while (*p == ' ' || *p == '\t' || *p == '\n')
				p++;
			while (*p == '+' || *p == '-')
				p++;
			c = (*p < '0' || *p > '9') ? '~' : ' ';
			while (ptr != p)
				write(1, &c, (ptr++ > 0));
		}
		else
			write(1, " ", (ptr++ > 0));
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_doublepoints(char *str)
{
	char	n;
	char	*ptr;

	ptr = str;
	n = 0;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' ||
		(*ptr >= '0' && *ptr <= '9') || *ptr == '.')
	{
		if (*ptr == '.')
			n++;
		ptr++;
		if (n == 2)
			return (1);
	}
	return (0);
}

int		ft_checkdoublepoints(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '.' || (*ptr >= '0' && *ptr <= '9'))
		{
			if (ft_doublepoints(ptr))
				return (0);
			while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' ||
				(*ptr >= '0' && *ptr <= '9') || *ptr == '.')
				ptr++;
		}
		else
			ptr++;
	}
	return (1);
}

int		ft_invaliddoublepoints(char *str)
{
	char *ptr;
	char c;

	write(1, "\e[1;31merror: \e[0m\e[1;29mdouble point(s) detected :\e[0m\n", 56);
	write(1, str, strlen(str));
	write(1, "\n\e[1;31m", 8);
	ptr = str;
	while (*ptr)
	{
		if (*ptr == '.' || (*ptr >= '0' && *ptr <= '9'))
		{
			c = ft_doublepoints(ptr) ? '~' : ' ';
			while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' ||
				(*ptr >= '0' && *ptr <= '9') || *ptr == '.')
				write(1, &c, (ptr++ > 0));
		}
		else
			write(1, " ", (ptr++ > 0));
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_splittedval(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr == '.' || (*ptr >= '0' && *ptr <= '9'))
		ptr++;
	while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
		ptr++;
	return ((*ptr >= '0' && *ptr <= '9') || *ptr == '.');
}

int		ft_checksplittedval(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '.' || (*ptr >= '0' && *ptr <= '9'))
		{
			if (ft_splittedval(ptr))
				return (0);
			while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' ||
				(*ptr >= '0' && *ptr <= '9') || *ptr == '.')
				ptr++;
		}
		else
			ptr++;
	}
	return (1);
}

int		ft_invalidsplittedval(char *str)
{
	char *ptr;
	char c;

	write(1, "\e[1;35mwarning: \e[0m\e[1;29msplitted value(s) :\e[0m\n", 51);
	write(1, str, strlen(str));
	write(1, "\n\e[1;35m", 8);
	ptr = str;
	while (*ptr)
	{
		if (*ptr == '.' || (*ptr >= '0' && *ptr <= '9'))
		{
			c = (ft_splittedval(ptr)) ? '~' : ' ';
			while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' ||
				(*ptr >= '0' && *ptr <= '9') || *ptr == '.')
				write(1, &c, (ptr++ > 0));
		}
		else
			write(1, " ", (ptr++ > 0));
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		main(int ac, char **av)
{
	t_env	e;
	char	error;
	char	warning;

	error = 0;
	warning = 0;
	if (ac != 2)
		return (0);
	if (!(ft_checkcharacters(*(av + 1))))
		error += 1 + ft_invalidcharacters(*(av + 1));
	if (!(ft_checkpowers(*(av + 1))))
		error += 1 + ft_invalidpower(*(av + 1));
	if (!(ft_checkpowerssign(*(av + 1))))
		error += 1 + ft_invalidpowerssign(*(av + 1));
	if (!(ft_checkpowervalue(*(av + 1))))
		error += 1 + ft_invalidpowersvalue(*(av + 1));
	if (!(ft_checklast(*(av + 1))))
		error += 1 + ft_invalidlast(*(av + 1));
	if (!(ft_checkdoublepoints(*(av + 1))))
		error += 1 + ft_invaliddoublepoints(*(av + 1));
	if (!(ft_checkextremval(*(av + 1))))
		warning += 1 + ft_invalidextrem(*(av + 1));
	if (!(ft_checksplittedval(*(av + 1))))
		warning += 1 + ft_invalidsplittedval(*(av + 1));
	if (error)
		return (ft_error(error));
	if (warning)
		ft_warning(warning);
// if (!(ft_getexpressions(&e, *(av + 1))))
// return (0);
// if (!(ft_checkexpressions(e)))
// return (ft_invalidxpressions(e));
	// if (!(ft_decompose(&e)))
		// return (0);	return (0);
	(void)av;
	(void)e;
}