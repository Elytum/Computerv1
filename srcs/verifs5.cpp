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

	write(1, WRONG_POWER_SIGN, WRONG_POWER_SIGN_LEN);
	write(1, str, strlen(str));
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
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
	write(1, OUT_BNBN, OUT_BNBN_LEN);
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

int		ft_invalidcharacters(char *str)
{
	char *p;

	write(1, WRONG_CHARACTERS, WRONG_CHARACTERS_LEN);
	write(1, (p = str), strlen(str));
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
	while (*p)
	{
		if (*p != ' ' && *p != '\n' && *p != '\t' && *p != 'X' && *p != '*' && *p != '/' && *p != '+' &&
			*p != '-' && *p != '^' && *p != '.' && *p != '=' && !(*p >= '0' && *p <= '9'))
			write(1, "~", 1);
		else
			write(1, " ", 1);
		p++;
	}
	write(1, OUT_BNBN, OUT_BNBN_LEN);
	return (0);
}

int		ft_checkcharacters(char *str)
{
	char *p;

	p = str;
	while (*p)
	{
		if (*p != ' ' && *p != '\n' && *p != '\t' && *p != 'X' && *p != '*' && *p != '/' && *p != '+' &&
			*p != '-' && *p != '^' && *p != '.' && *p != '=' && !(*p >= '0' && *p <= '9'))
			return (0);
		p++;
	}
	return (1);
}
