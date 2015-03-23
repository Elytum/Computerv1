/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 10:39:34 by achazal           #+#    #+#             */
/*   Updated: 2015/03/23 10:39:35 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"

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
	write(1, OUT_BNBN, OUT_BNBN_LEN);
	return (0);
}