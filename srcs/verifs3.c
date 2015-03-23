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

	write(1, WRONG_SPLIT, WRONG_SPLIT_LEN);
	write(1, str, strlen(str));
	write(1, BN_ENTER_PURPLE, BN_ENTER_PURPLE_LEN);
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
	write(1, OUT_BNBN, OUT_BNBN_LEN);
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
	write(1, WRONG_POWER_VALUE, WRONG_POWER_VALUE_LEN);
	write(1, str, strlen(str));
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
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
	write(1, OUT_BNBN, OUT_BNBN_LEN);
	return (0);
}
