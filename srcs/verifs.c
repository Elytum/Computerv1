/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 10:39:30 by achazal           #+#    #+#             */
/*   Updated: 2015/03/23 10:39:31 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"

static int		ft_doublepoints(char *str)
{
	char		n;
	char		*ptr;

	ptr = str;
	n = 0;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' ||
		(*ptr >= '0' && *ptr <= '9') || *ptr == '.')
	{
		if (*ptr == '.')
			n++;
		ptr++;
		if (n == 2)
			return (1);
	}
	return (0);
}

static int		ft_invaliddoublepoints(char *str)
{
	char		*ptr;
	char		c;

	write(1, WRONG_DOUBLE_POINTS, WRONG_DOUBLE_POINTS_LEN);
	write(1, str, strlen(str));
	write(1, BN_ENTER_RED, BN_ENTER_RED_LEN);
	ptr = str;
	while (*ptr)
	{
		if (*ptr == '.' || (*ptr >= '0' && *ptr <= '9'))
		{
			c = ft_doublepoints(ptr) ? '~' : ' ';
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

static int		ft_checkdoublepoints(char *str)
{
	char		*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '.' || (*ptr >= '0' && *ptr <= '9'))
		{
			if (ft_doublepoints(ptr))
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

int				ft_verifs2(char *line, char error, char warning)
{
	if (!(ft_checkdoublepoints(line)))
		error += 1 + ft_invaliddoublepoints(line);
	if (!(ft_checkextremval(line)))
		warning += 1 + ft_invalidextrem(line);
	if (!(ft_checksplittedval(line)))
		warning += 1 + ft_invalidsplittedval(line);
	if (error)
		return (ft_error(error));
	if (warning)
		ft_warning(warning);
	return (1);
}

int				ft_verifs(int ac, char *line)
{
	char		error;
	char		warning;

	error = 0;
	warning = 0;
	if (ac != 2)
	{
		write(1, WRONG_ARGS_NB, WRONG_ARGS_NB_LEN);
		return (0);
	}
	if (!(ft_checkequalities(line)))
		error += 1;
	if (!(ft_checkcharacters(line)))
		error += 1 + ft_invalidcharacters(line);
	if (!(ft_checkpowers(line)))
		error += 1 + ft_invalidpower(line);
	if (!(ft_checkpowerssign(line)))
		error += 1 + ft_invalidpowerssign(line);
	if (!(ft_checkpowervalue(line)))
		error += 1 + ft_invalidpowersvalue(line);
	if (!(ft_checklast(line)))
		error += 1 + ft_invalidlast(line);
	return (ft_verifs2(line, error, warning));
}
