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

int		ft_checkequalities(char *str)
{
	char *ptr;

	if (!strchr(str, '='))
	{
		write(1, WRONG_EQUALITY_1, WRONG_EQUALITY_1_LEN);
		write(1, str, strlen(str));
		write(1, "\n", 1);
		return (0);
	}
	if (!(strchr(strchr(str, '=') + 1, '=')))
		return (1);
	write(1, WRONG_EQUALITY_2, WRONG_EQUALITY_2_LEN);
	write(1, str, strlen(str));
	ptr = str;
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
	while (*ptr)
	{
		if (*ptr == '=')
			write(1, "~", 1);
		else
			write(1, " ", 1);
		ptr++;
	}
	write(1, OUT_BNBN, OUT_BNBN_LEN);
	return (0);
}

int		ft_checklast(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	while (ptr != str && *ptr != '+' && *ptr != '-' && *ptr != '*' && *ptr != '/' && *ptr != '^')
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
	write(1, WRONG_LAST, WRONG_LAST_LEN);
	write(1, str, strlen(str));
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
	while (*ptr)
		ptr++;
	while (ptr != str && *ptr != '+' && *ptr != '-' && *ptr != '*' && *ptr != '/' && *ptr != '^')
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
	write(1, OUT_BNBN, OUT_BNBN_LEN);
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
	write(1, WRONG_POWER, WRONG_POWER_LEN);
	write(1, str, strlen(str));
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
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
	write(1, OUT_BNBN, OUT_BNBN_LEN);
	return (0);
}
