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

static int	ft_invalid_operation(char *str)
{
	write(1, WRONG_OPERATORS, WRONG_OPERATORS_LEN);
	write(1, str, strlen(str));
	write(1, "\n", 1);
	return (0);
}

int			ft_next_operation(char *str, int flag)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if ((*ptr == '*' || *ptr == '/' || *ptr == '^') && ptr++)
		{
			if (flag == -1)
				return (ft_invalid_operation(str));
			flag = -1;
		}
		else if ((*ptr == '+' || *ptr == '-' || *ptr == '=') && ptr++)
			flag = 0;
		else if ((*ptr >= '0' && *ptr <= '9') || *ptr == '.')
		{
			if (flag == 1)
				return (ft_invalid_operation(str));
			flag = 1;
			while ((*ptr >= '0' && *ptr <= '9') || *ptr == '.')
				ptr++;
		}
		else if (*ptr == 'X')
		{
			if (flag == 2)
				return (ft_invalid_operation(str));
			flag = 2;
			ptr++;
		}
		else
			ptr++;
	}
	return (1);
}