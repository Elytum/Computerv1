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
	char *ptr;

	write(1, WRONG_CHARACTERS, WRONG_CHARACTERS_LEN);
	write(1, (ptr = str), strlen(str));
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' && *ptr != '.' &&
			!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
			*ptr != '-' && *ptr != '*' && *ptr != '/' && *ptr != '=' && *ptr != '^')
		{
			if (*ptr == 'X' && *(ptr + 1) == '^' && ptr++)
				write (1, "  ", 2);
			else if (*ptr != 'X' || !(*(ptr + 1) == ' ' || *(ptr + 1) == '\n' ||
				*(ptr + 1) == '\t' || !*(ptr + 1)))
				write(1, "~", 1);
			else
				write(1, " ", 1);
		}
		else
			write (1, " ", 1);
		ptr++;
	}
	write(1, OUT_BNBN, OUT_BNBN_LEN);
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
			*ptr != '-' && *ptr != '*' && *ptr != '/' && *ptr != '=' && *ptr != '^')
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
