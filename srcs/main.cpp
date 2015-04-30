/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 10:39:16 by achazal           #+#    #+#             */
/*   Updated: 2015/03/23 10:39:18 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"

int		ft_getexpressions(t_env *e, char *line)
{
	char	*cptr;
	char	*tmp;

	cptr = strchr(line, '=');
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

void		ft_putduo(double value, double power)
{
	if (value)
	{
		if (power)
		{
			if (power == 1)
				dprintf(1, "%f * X", value);
			else
				dprintf(1, "%f * X ^ %f", value, power);
		}
		else
			dprintf(1, "%f", value);
	}
	else if (power)
	{
		if (power == 1)
			write(1, "X", 1);
		else
			dprintf(1, "X ^ %f", power);
	}
}

void		ft_putformat(t_duo *lst)
{
	t_duo	*ptr;

	if (lst == NULL)
	{
		write(1, "0", 1);
		return ;
	}
	ptr = lst;
	while (ptr)
	{
			if (ptr->value < 0)
			{
				write(1, "- ", 3);
				ft_putduo(-ptr->value, ptr->power);
			}
			else
			{
				if (ptr != lst)
					write(1, "+ ", 3);
				ft_putduo(ptr->value, ptr->power);
			}
			if (ptr->next)
				write(1, " ", 1);
		ptr = ptr->next;
	}
}

void	ft_put_simplified(t_env e)
{
	dprintf (1, "%sSimplified : %s", WHITE_COLOR, OUT_COLOR);
	ft_putformat(e.e1.elems);
	write(1, " = ", 3);
	ft_putformat(e.e2.elems);
	write(1, "\n", 1);
}

void	ft_lstpushmerge(t_duo **head, double value, double power)
{
	t_duo *ptr;
	t_duo *past;
	t_duo *dup;

	if (*head == NULL)
	{
		if (!(dup = (t_duo *)malloc(sizeof(t_duo))))
			return ;
		dup->value = value;
		dup->power = power;
		dup->next = NULL;
		*head = dup;
	}
	else
	{
		ptr = *head;
		past = NULL;
		while (ptr)
		{
			if (ptr->power >= power)
				break ;
			past = ptr;
			ptr = ptr->next;
		}
		if (ptr && ptr->power == power)
			ptr->value += value;
		else
		{
			if (!(dup = (t_duo *)malloc(sizeof(t_duo))))
				return ;
			dup->value = value;
			dup->power = power;
			dup->next = NULL;
			if (past && !ptr)
				past->next = dup;
			else if (!past)
			{
				dup->next = *head;
				*head = dup;
			}
			else
			{
				past->next = dup;
				dup->next = ptr;
			}
		}
	}
}


t_duo	*ft_merge(t_env e)
{
	t_duo *ptr;
	t_duo *merged;

	merged = NULL;
	ptr = e.e1.elems;
	while (ptr)
	{
		ft_lstpushmerge(&merged, ptr->value, ptr->power);
		ptr = ptr->next;
	}
	ptr = e.e2.elems;
	while (ptr)
	{
		ft_lstpushmerge(&merged, -ptr->value, ptr->power);
		ptr = ptr->next;
	}
	return (merged);
}

void	ft_putmerged(t_env e)
{
	dprintf(1, "%sReduced format :%s ", WHITE_COLOR, OUT_COLOR);
	ft_putformat(e.merged);
	write(1, " = 0\n", 5);
}

void	ft_cleanduos(t_duo **head)
{
	t_duo *ptr;
	t_duo *tmp;
	t_duo *past;

	past = NULL;
	ptr = *head;
	while (ptr)
	{
		if (ptr->value == 0 && ptr->power != 0)
		{
			if (past == NULL)
			{
				*head = (*head)->next;
				ptr = *head;
			}
			else
			{
				past->next = ptr->next;
				tmp = ptr;
				ptr = ptr->next;
				free(tmp);
			}
		}
		else
		{
			past = ptr;
			ptr = ptr->next;
		}
	}
}

int		ft_isseconddegree(t_duo **duos, double *a, double *b, double *c)
{
	t_duo	*ptr;
	t_duo	*next;
	int		ret;

	ret = 1;
	ptr = *duos;
	while (ptr)
	{
		if (ptr->power == 0)
			*c = ptr->value;
		else if (ptr->power == 1)
			*b = ptr->value;
		else if (ptr->power == 2)
			*a = ptr->value;
		else
		{
			ret = 0;
			break ;
		}
		ptr = ptr->next;
	}
	ptr = *duos;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	return (ret);
}

void		ft_putcanonic(t_env e)
{
	double	a;
	double	b;
	double	c;

	a = e.a;
	b = -e.b / (2 * e.a);
	c = -(e.b * e.b - 4 * e.a * e.c) / (4 * e.a * e.a);
	dprintf (1, "%sCanonic form :%s ", WHITE_COLOR, OUT_COLOR);
	if (a != 0)
	{
		if (a < 0)
			dprintf(1, "- %f ", -a);
		else
			dprintf(1, "%f ", a);
		if (b != 0)
		{
			if (b < 0)
				dprintf(1, "(X - %f) ^ 2 ", -b);
			else
				dprintf(1, "(X + %f) ^ 2 ", b);
		}
		else
			write(1, "X ^ 2", 5);
	}
	if (c < 0)
		dprintf(1, "- %f\n", -c);
	else if (c > 0)
		dprintf(1, "+ %f\n", c);
	else
		write(1, "\n", 1);
}

void	ft_putquadra(t_env e)
{
	dprintf (1, "%sQuadratic equation :%s ", WHITE_COLOR, OUT_COLOR);
	if (e.a < 0)
		dprintf(1, "- %f X ^ 2 ", -e.a);
	else if (e.a > 0)
		dprintf(1, "%f X ^ 2 ", e.a);
	if (e.b < 0)
		dprintf(1, "- %f X ", -e.b);
	else if (e.b > 0)
		dprintf(1, "+ %f X ", e.b);
	if (e.c < 0)
		dprintf(1, "- %f ", -e.c);
	else if (e.c > 0)
		dprintf(1, "+ %f ", e.c);
	write(1, "\n", 1);
}

void	ft_put_upperfacto(t_env e)
{
	if (e.x1 == e.x2)
	{
		if (e.x1 < 0)
			dprintf(1, "(X - %f) ^ 2\n", -e.x1);
		else if (e.x1 > 0)
			dprintf(1, "(X + %f) ^ 2\n", e.x1);
		else
			dprintf(1, "X ^ 2\n");
	}
	else if (e.x1 == 0)
	{
		if (e.x2 < 0)
			dprintf(1, "X (X - %f)\n", -e.x2);
		else
			dprintf(1, "X (X + %f)\n", e.x2);
	}
	else if (e.x2 == 0)
	{
		if (e.x1 < 0)
			dprintf(1, "X (X - %f)\n", -e.x1);
		else
			dprintf(1, "X (X + %f)\n", e.x1);
	}
	else
	{
		if (e.x1 < 0)
			dprintf(1, "(X - %f) ", -e.x1);
		else
			dprintf(1, "(X + %f) ", e.x1);
		if (e.x2 < 0)
			dprintf(1, "(X - %f)\n", -e.x2);
		else
			dprintf(1, "(X + %f)\n", e.x2);
	}
}

void	ft_putcomplex(double real, double imag)
{
	if (real < 0)
		dprintf(1, "- %f ", -real);
	else if (real > 0)
		dprintf(1, "+ %f ", real);
	if (imag < 0)
		dprintf(1, "- %f i ", -imag);
	else if (imag > 0)
		dprintf(1, "+ %f i ", imag);
}

void	ft_put_lowerfacto(t_env e)
{
	if (e.x1 == e.x2 && e.i1 == e.i2)
	{
		write (1, "(X ", 3);
		ft_putcomplex(-e.x1, -e.i1);
		write(1, ") ^ 2\n", 6);
	}
	else if (e.x1 == 0 && e.i1 == 0)
	{
		write (1, "X (X ", 5);
		ft_putcomplex(-e.x2, -e.i2);
		write(1, ") ^ 2\n", 6);
	}
	else if (e.x2 == 0 && e.i2 == 0)
	{
		write (1, "X (X ", 5);
		ft_putcomplex(-e.x1, -e.i1);
		write(1, ") ^ 2\n", 6);
	}
	else
	{
		write(1, "(X ", 3);
		ft_putcomplex(-e.x1, -e.i1);
		write(1, ") (X ", 5);
		ft_putcomplex(-e.x2, -e.i2);
		write(1, ")\n", 2);

	}
}

void	ft_putfactorised(t_env e)
{
	dprintf (1, "%sFactorised form :%s ", WHITE_COLOR, OUT_COLOR);
	if (e.i == 0)
	{
		ft_put_upperfacto(e);
		if (e.x1 != e.x2)
			dprintf(1, "%sSolutions are :%s X1 = %s%f%s, X2 = %s%f%s\n",
				WHITE_COLOR, OUT_COLOR,
				GREEN_COLOR, e.x1, OUT_COLOR,
				GREEN_COLOR, e.x2, OUT_COLOR);
		else
			dprintf(1, "%sSolution is%s %s%f%s\n", WHITE_COLOR, OUT_COLOR, GREEN_COLOR, e.x1, OUT_COLOR);
	}
	else
	{
		ft_put_lowerfacto(e);
		if (e.x1 != e.x2 || e.i1 != e.i2)
		{
			dprintf(1, "%sSolutions are :%s X1 = %s", WHITE_COLOR, OUT_COLOR, GREEN_COLOR);
			ft_putcomplex(e.x1, e.i1);
			dprintf(1, "%sand X2 = %s", OUT_COLOR, GREEN_COLOR);
			ft_putcomplex(e.x2, e.i2);
			dprintf (1, "%s\n", OUT_COLOR);
		}
		else
		{
			dprintf(1, "%sSolution is%s ", WHITE_COLOR, OUT_COLOR);
			dprintf(1, GREEN_COLOR);
			ft_putcomplex(e.x1, e.i1);
			dprintf(1, OUT_COLOR);
			write(1, "\n", 1);
		}
	}
}

void	ft_put_info(t_env e)
{
	if (e.a && e.b)
	{
		e.d = e.b * e.b - 4 * e.a * e.c;
		dprintf(1, "%sDelta :%s %s%f%s\n", WHITE_COLOR, OUT_COLOR, CYAN_COLOR, e.d, OUT_COLOR);
		if (e.d < 0)
		{
			e.d = -e.d;
			e.i = 1;
		}
		else
			e.i = 0;
		ft_putcanonic(e);
		ft_putquadra(e);
		if (e.d == 0)
		{
			e.i = 0;
			e.x1 = -e.b / (2 * e.a);
			e.x2 = e.x1;
			ft_putfactorised(e);
		}
		else if (e.i == 1)
		{
			e.i = 1;
			e.sd = ft_sqrt(e.d);
			e.x1 = -e.b / (2 * e.a);
			e.x2 = e.x1;
			e.i1 = e.sd / (2 * e.a);
			e.i2 = -e.i1;
			ft_putfactorised(e);
		}
		else if (e.i == 0)
		{
			e.i = 0;
			e.sd = ft_sqrt(e.d);
			e.x1 = (-e.b + e.sd) / (2 * e.a);
			e.x2 = (-e.b - e.sd) / (2 * e.a);
			ft_putfactorised(e);
		}
	}
	else if (e.c && e.b)
		dprintf(1, "X =%s %f%s\n", GREEN_COLOR, -e.c / e.b, OUT_COLOR);
	else if (e.c && e.a)
		dprintf(1, "X =%s %f%s\n", GREEN_COLOR, ft_sqrt2(-e.c / e.a), OUT_COLOR);
	else if (e.a)
		dprintf (1, "X =%s 0%s\n", GREEN_COLOR, OUT_COLOR);
	else if (e.b)
		dprintf (1, "X =%s 0%s\n", GREEN_COLOR, OUT_COLOR);
}

int		ft_checkexpressions(t_env e)
{
	int		ret;

	e.e1.elems = ft_getduo(e.e1.str);
	e.e2.elems = ft_getduo(e.e2.str);
	ft_put_simplified(e);
	e.merged = ft_merge(e);
	ft_cleanduos(&(e.merged));
	if (!e.merged || (e.merged->power == 0 && e.merged->value == 0 && e.merged->next == NULL))
	{
		dprintf (1, "%sX can be any real in order to solve this equation.%s\n", GREEN_COLOR, OUT_COLOR);
		return (0);
	}
	ft_putmerged(e);
	e.a = 0;
	e.b = 0;
	e.c = 0;
	ret = ft_isseconddegree(&(e.merged), &e.a, &e.b, &e.c);
	if (ret == 0)
		dprintf(1, "%sThe given equation is not a polynom of the second degree.%s\n", RED_COLOR, OUT_COLOR);
	else if (e.a == 0 && e.b == 0)
		dprintf(1, "%sThe given equation is impossible.%s\n", RED_COLOR, OUT_COLOR);
	else
		ft_put_info(e);
	return (1);
}

int		main(int ac, char **av)
{
	t_env	e;

	if (!(ft_verifs(ac, *(av + 1))))
		return (0);
	if (!(ft_getexpressions(&e, *(av + 1))))
		return (0);
	ft_checkexpressions(e);
}
