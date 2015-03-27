/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 10:39:25 by achazal           #+#    #+#             */
/*   Updated: 2015/03/23 10:39:26 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"

size_t		ft_nbofc(char *str, char c)
{
	char	*ptr;
	size_t	i;

	
	i = 0;
	ptr = str;
	while (*ptr)
	{
		if (*ptr++ == c)
			i++;
	}
	return (i);
}

char		**ft_splitsigns(char *str)
{
	size_t	s;
	char	**tab;
	char	**p;
	char	*ptr;
	char	*ptr2;

	s = ft_nbofc(str, '+') + ft_nbofc(str, '-');
	if (!(tab = (char **)malloc(sizeof(char *) * (s + 1))))
		return (NULL);
	p = tab;
	ptr = str;
	while (*ptr)
	{
		ptr2 = ptr + 1;
		while (*ptr2 && *ptr2 != '+' && *ptr2 != '-')
			ptr2++;
		if (!(*p = (char *)malloc(sizeof(char) * (ptr2 - ptr + 1))))
			return (NULL);
		memcpy(*p, ptr, ptr2 - ptr);
		(*p++)[ptr2 - ptr] = '\0';
		ptr = ptr2;
	}
	*p = NULL;
	return (tab);
}

double		ft_get_double(char *str)
{
	double	up;
	double	down;
	char	*ptr;

	up = atoi(str);
	ptr = str;
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	if (*ptr != '.')
		return (up);
	down = atoi(ptr + 1);
	while (down > 1)
		down /= 10;
	return (up + down);

}

double		ft_getvalue(char *str)
{
	double	v;
	char	*ptr;

	v = ft_get_double(str);
	ptr = str;
	if (*ptr == '+' || *ptr == '-')
		ptr++;
	while ((*ptr >= '0' && *ptr <= '9') || *ptr == '.')
		ptr++;
	while (*ptr)
	{
		ptr++;
		v *= ft_get_double(ptr);
		while ((*ptr >= '0' && *ptr <= '9') || *ptr == '.')
			ptr++;
	}
	return (v);
}

void		ft_inside(char *str)
{
	// size_t	v;
	double	p;
	char	*ptr;

	// if (*(str + 1) >= '0' && *(str + 1) <= '9')
	// 	v = atoi(str);
	// else
	// 	v = 1;
	ptr = strchr(str, 'X');
	if (!ptr)
		p = 0;
	else if (*(ptr + 1) != '^')
		p = 1;
	else
		p = ft_getvalue(ptr + 2);
	dprintf(1, "With %s : Power = %f, ptr = %s\n", str, p, ptr);

}

void		ft_puttest(char *str)
{
	char	c;
	char	*ptr;

	while (*str)
	{
		ptr = str + 1;
		while (*ptr && *ptr != '+' && *ptr != '-')
			ptr++;
		c = *ptr;
		*ptr = '\0';
		ft_inside(str);
		*ptr = c;
		str = ptr;
	}
}

int			ft_split(t_env *e)
{
	char	**total;
	// char	**test;

	total = ft_strsplit(e->minimized, '=');
	if (!(total[0] && total[1] && !total[2]))
		return (0);
	e->e1.str = total[0];
	e->e2.str = total[1];
	// ft_puttest(e->e1.str);
	// test = ft_splitsigns(e->e1.str);
	// ft_putstrarray(test);
	return (1);
}

int			ft_parsing_error(char *str, char here, char asked)
{
	dprintf(1, "Parsing error with line '%s' : %c instead of %c\n",
			str, here, asked);
	return (0);
}

char		*ft_getreduced(char *ptr)
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

void		ft_reduce(char **str)
{
	char	*p1;
	char	*p2;

	p1 = *str;
	p2 = *str;
	while (*p2)
	{
		if (*p2 == ' ' || *p2 == '\n' || *p2 == '\t')
			p2++;
		else
			*p1++ = *p2++;
	}
	*p1 = '\0';
}

void		ft_simplify(char **ptr)
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

void		ft_simplifysign(char **str)
{
	char	*ptr;
	char	sign;
	char	*p;

	ptr = *str;
	while (*ptr)
	{
		if (*ptr == '*')
		{
			if (*(ptr + 1) == '+')
			{
				sign = *(ptr + 1);
				*(ptr + 1) = ' ';
			}
			else if (*(ptr + 1) == '-')
			{
				*(ptr + 1) = ' ';
				p = ptr - 1;
				if (*p >= '0' && *p <= '9')
				{
					while (p != *str && *p >= '0' && *p <= '9')
						p--;
					if (*p == '+')
						*p = '-';
					else if (*p == '-')
						*p = '+';
				}
			}
		}
		ptr++;
	}
	(void)str;
}

char		*ft_simplified(char *str)
{
	char	*tmp;

	tmp = strdup(str);
	ft_reduce(&tmp);
	ft_simplify(&tmp);
	ft_reduce(&tmp);
	ft_simplifysign(&tmp);
	ft_reduce(&tmp);
	return (tmp);
}
