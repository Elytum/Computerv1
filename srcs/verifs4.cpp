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
		write(1, SINGLE_ERROR, SINGLE_ERROR_LEN);
	else
	{
		write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
		ft_putnbr(n);
		write(1, MULT_ERROR, MULT_ERROR_LEN);
	}
	return (0);
}

int		ft_warning(char n)
{
	if (n == 1)
		write(1, SINGLE_WARNING, SINGLE_WARNING_LEN);
	else
	{
		write(1, BN_ENTER_PURPLE, BN_ENTER_PURPLE_LEN);
		ft_putnbr(n);
		write(1, MULT_WARNING, MULT_WARNING_LEN);
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
	write(1, WRONG_EXTREM, WRONG_EXTREM_LEN);
	write(1, str, strlen(str));
	write(1, BN_ENTER_PURPLE, BN_ENTER_PURPLE_LEN);
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
