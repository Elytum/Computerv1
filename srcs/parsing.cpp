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
#include <math.h>

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

void			ft_valuespushback(t_values **values, char sign, double v)
{
	t_values	*new_pp;
	t_values	*ptr;


	if (!(new_pp = (t_values *)malloc(sizeof(t_values))))
		return ;
	new_pp->sign = sign;
	new_pp->v = v;
	new_pp->next = NULL;
	if (!*values)
		*values = new_pp;
	else
	{
		ptr = *values;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_pp;
	}
}

void			ft_putvalues(t_values *ptr)
{
	dprintf(1, "Test : ");
	while (ptr)
	{
		dprintf(1, ((ptr->next) ? "%c %f " : "%c %f\n"), ptr->sign, ptr->v);
		ptr = ptr->next;
	}
}

double			ft_solvevalues(t_values **head)
{
	t_values	*ptr;
	t_values	*tmp;
	double		v;

	ptr = *head;
	while (ptr->next)
	{
		if (ptr->next->sign == '^')
		{
			tmp = ptr->next;
			ptr->v = ft_pow(ptr->v, tmp->v);
			ptr->next = ptr->next->next;
			free(tmp);
		}
		else
			ptr = ptr->next;
	}
	ptr = *head;
	while (ptr->next)
	{
		tmp = ptr->next;
		if (tmp->sign == '*')
			ptr->v *= tmp->v;
		else if (tmp->sign == '/')
			ptr->v /= tmp->v;
		ptr->next = ptr->next->next;
		free(tmp);
	}
	v = ptr->v;
	if (ptr->sign == '-')
		v *= -1;
	free(ptr);
	return (v);
}

double			ft_getvalue(char *str)
{
	char		*ptr;
	t_values	*values;
	char		sign;
	double		v;

	// dprintf(1, "Launching with '%s'\n", str);
	values = NULL;
	if (*str == '^')
		sign = '+';
	else
		sign = *str;
	ptr = str + 1;
	ft_valuespushback(&values, sign, strtod(ptr, NULL));
	// if (*ptr == '+' || *ptr == '-')
		// ptr++;
	while ((*ptr >= '0' && *ptr <= '9') || *ptr == '.')
		ptr++;
	while (*ptr && *ptr != 'X' && *(ptr + 1) && *(ptr + 1) != 'X')
	{
		ft_valuespushback(&values, *ptr, strtod(ptr + 1, NULL));
		while (++ptr && ((*ptr >= '0' && *ptr <= '9') || *ptr == '.'))
			;
	}
	// ft_putvalues(values);
	v = ft_solvevalues(&values);
	// dprintf(1, "Returning %f\n", v);
	return (v);
}

t_duo		*ft_inside(char *str)
{
	char	*ptr;
	t_duo	*duo;

	if (!(duo = (t_duo *)malloc(sizeof(t_duo))))
		return (NULL);
	duo->next = NULL;
	duo->value = 0;
	if (*(str + 1) >= '0' && *(str + 1) <= '9')
		duo->value = ft_getvalue(str);
	else
		duo->value = 1;
	ptr = strchr(str, 'X');
	if (!ptr)
		duo->power = 0;
	else if (*(ptr + 1) != '^')
		if (ptr != str && *(ptr - 1) == '-')
			duo->power = -1;
		else
			duo->power = 1;
	else
		duo->power = ft_getvalue(ptr + 1);
	// if (ptr && ptr != str && *(ptr - 1) != '*')
	// 	v = 1;
	// dprintf(1, "With %s : Value = %f, Power = %f, ptr = %s\n", str, duo->value, duo->power, ptr);
	return (duo);
}

void		ft_lstinsert(t_duo **head, t_duo *new_pp)
{
	t_duo	*ptr;

	if (new_pp->value == 0)
		return ;
	if (!*head)
		*head = new_pp;
	else
	{
		ptr = *head;
		if (new_pp->power < ptr->power)
		{
			new_pp->next = *head;
			*head = new_pp;
		}
		else
		{
			while (ptr->next && new_pp->power > ptr->next->power)
				ptr = ptr->next;
			new_pp->next = ptr->next;
			ptr->next = new_pp;
		}
	}
}

t_duo		*ft_getduo(char *str)
{
	char	c;
	char	*ptr;
	t_duo	*lst;

	t_duo	*tmp;

	lst = NULL;
	while (*str)
	{
		ptr = str + 1;
		while (*ptr && *ptr != '+' && *ptr != '-')
			ptr++;
		c = *ptr;
		*ptr = '\0';
		tmp = ft_inside(str);
		dprintf(1, "'%s' : %f and %f\n", str, tmp->value, tmp->power);
		ft_lstinsert(&lst, ft_inside(str));
		*ptr = c;
		str = ptr;
	}
	return (lst);
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
	// ft_getduo(e->e1.str);
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
		if (*ptr == '*' || *ptr == '/')
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
