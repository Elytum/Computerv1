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
	char flag;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '^' && ptr++)
		{
			flag = 0;
			while (*ptr && *ptr != '+' && *ptr != '-')
			{
				if (*ptr == 'X' || *ptr == '=')
				{
					if (*ptr == '=' && flag == 1)
						break ;
					else
					{
						dprintf(1, "Here '%s'\n", ptr);
						return (0);
					}
				}
				else if (*ptr >= '0' && *ptr <= '9')
					flag = 1;
				else if (*ptr == '*' || *ptr == '/' || *ptr == '^')
					flag = 0;
				ptr++;
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
	char flag;

	ptr = str;
	write(1, WRONG_POWER_VALUE, WRONG_POWER_VALUE_LEN);
	write(1, str, strlen(str));
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
	while (*ptr)
	{
		if (*ptr == '^' && (p = ptr + 1))
		{
			flag = 0;
			c = ' ';
			while (*p && *p != '+' && *p != '-')
			{
				if (*p == 'X' || *p == '=')
				{
					if (*p == '=' && flag)
						break ;
					p++;
					c = '~';
					break ;
				}
				else if (*p >= '0' && *p <= '9')
					flag = 1;
				else if (*p == '*' || *p == '/' || *p == '^')
					flag = 0;
				p++;
			}
			while (ptr != p)
				write(1, &c, (ptr++ > 0));
		}
		else
			write(1, " ", (ptr++ > 0));
	}
	write(1, OUT_BNBN, OUT_BNBN_LEN);
	return (0);
}
