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
	write(1, "Simplified : ", 13);
	ft_putformat(e.e1.elems);
	write(1, " = ", 3);
	ft_putformat(e.e2.elems);
	write(1, "\n", 1);
}

void	ft_lstpushmerge(t_duo **head, float value, float power)
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
	write(1, "Merged format : ", 16);
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

int		ft_checkexpressions(t_env e)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	sd;
	int		ret;
	double	x1;
	double	x2;

	e.e1.elems = ft_getduo(e.e1.str);
	e.e2.elems = ft_getduo(e.e2.str);
	ft_put_simplified(e);
	e.merged = ft_merge(e);
	ft_cleanduos(&(e.merged));
	ft_putmerged(e);
	a = 0;
	b = 0;
	c = 0;
	ret = ft_isseconddegree(&(e.merged), &a, &b, &c);
	if (ret == 0)
		write(1, "The given equation is not a polynom of the second degree.\n", 58);
	else if (a == 0 && b == 0)
		write(1, "The given equation does not contain X and by so is impossible.\n", 63);
	else
	{
		d = b * b - 4 * a * c;
		sd = ft_sqrt(d);
		dprintf(1, "Canonic form : %f (x + %f) ^ 2 + %f\n", a, -b / (2 * a), -(b * b - 4 * a * c) / (4 * a * a));
		dprintf(1, "Quadratic equation : %f + %f X + %f X^2\n", a, b, c);
		dprintf(1, "Delta = %f, sqrt(delta) = %f\n", d, sd);
		if (d > 0)
		{
			x1 = (-b + sd) / (2 * a);
			x2 = (-b - sd) / (2 * a);
			dprintf(1, "Factorised form : (x - %f) (x - %f)\n", x1, x2);
			dprintf(1, "X1 = %f, X2 = %f\n", x1, x2);
		}
	}
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
// if (!(ft_checkexpressions(e)))
// return (ft_invalidxpressions(e));
	// if (!(ft_decompose(&e)))
		// return (0);	return (0);
	(void)av;
	(void)e;
}
