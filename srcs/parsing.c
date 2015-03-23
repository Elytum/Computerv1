/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 10:39:25 by achazal           #+#    #+#             */
/*   Updated: 2015/03/23 10:39:26 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"

int			ft_split(t_env *e)
{
	char	**total;

	total = ft_strsplit(e->minimized, '=');
	if (!(total[0] && total[1] && !total[2]))
		return (0);
	e->e1.str = total[0];
	e->e2.str = total[1];
	return (1);
}

int			ft_parsing_error(char *str, char here, char asked)
{
	dprintf(1, "Parsing error with line '%s' : %c instead of %c\n",
			str, here, asked);
	return (0);
}

char		*ft_getreduced(char *ptr)
{
	char	*str;
	char	*p;

	if (!(str = (char *)malloc(sizeof(char) * strlen(ptr) + 1)))
		return (0);
	p = str;
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\n' && *ptr != '\t')
			*p++ = *ptr;
		ptr++;
	}
	*p = '\0';
	return (str);
}

void		ft_simplify(char **ptr)
{
	char	*p;

	if (!*(p = *ptr))
		return ;
	while (*(p + 1))
	{
		if (*p == '+' && (*(p + 1) == '+' || *(p + 1) == '-'))
			*p = ' ';
		else if (*p == '-' && *(p + 1) == '+')
		{
			*p = ' ';
			*(p + 1) = '-';
		}
		else if (*p == '-' && *(p + 1) == '-')
		{
			*p = ' ';
			*(p + 1) = '+';
		}
		else if (*p == '^' && *(p + 1) == '+')
		{
			*p = ' ';
			*(p + 1) = '^';
		}
		p++;
	}
}

char		*ft_simplified(char *str)
{
	char	*tmp;
	char	*ret;

	tmp = ft_getreduced(str);
	ft_simplify(&tmp);
	ret = ft_getreduced(tmp);
	free(tmp);
	ft_simplify(&ret);
	tmp = ft_getreduced(ret);
	free(ret);
	return (tmp);
}
