/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 10:39:16 by achazal           #+#    #+#             */
/*   Updated: 2015/03/23 10:39:18 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"

int		ft_getexpressions(t_env *e, char *line)
{
	char	*cptr;
	char	*tmp;

	cptr = strchr(line, '=');
	*cptr++ = '\0';
	if (!(e->e1.str = (char *)malloc(sizeof(char) * strlen(line) + 2)))
		return (0);
	e->e1.str[0] = '+';
	strcpy(e->e1.str + 1, line);
	tmp = ft_simplified(e->e1.str);
	free(e->e1.str);
	e->e1.str = tmp;
	if (!(e->e2.str = (char *)malloc(sizeof(char) * strlen(cptr) + 2)))
		return (0);
	e->e2.str[0] = '+';
	strcpy(e->e2.str + 1, cptr);
	tmp = ft_simplified(e->e2.str);
	free(e->e2.str);
	e->e2.str = tmp;
	return (1);
}

// int		ft_decompose(t_env *e)




// int		ft_invalidxpressions(t_env e)
// {
// 	// char *ptr;

// 	// ptr = str;
// 	write(1, "\e[1;31merror: \e[0m\e[1;29minvalid expression :\e[0m\n", 50);
// 	// write(1, str, strlen(str));
// 	// write(1, "\n\e[1;31m", 8);
// 	// while (*ptr)
// 	// {
// 	// 	if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' &&
// 	// 		!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
// 	// 		*ptr != '-' && *ptr != '*' && *ptr != '=')
// 	// 	{
// 	// 		if (*ptr == 'X' && *(ptr + 1) == '^')
// 	// 		{
// 	// 			write (1, "  ", 2);
// 	// 			ptr++;
// 	// 		}
// 	// 		else
// 	// 			write(1, "~", 1);
// 	// 	}
// 	// 	else
// 	// 		write (1, " ", 1);
// 	// 	ptr++;
// 	// }
// 	// write(1, "\e[0m\n\n", 5);
// 	return (0);
// 	(void)e;
// }

// int		ft_checkexpression(char *str)
// {
// 	char *ptr;

// 	ptr = str;
// 	while (*ptr)
// 	{
// 		if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' &&
// 			!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
// 			*ptr != '-' && *ptr != '*' && *ptr != '=')
// 		{
// 			if (*ptr == 'X' && *(ptr + 1) == '^')
// 				ptr++;
// 			else
// 				return (0);
// 		}
// 		ptr++;
// 	}
// 	return (1);
// 	(void)str;
// }

void	ft_compose(t_expr *e)
{
	// char	**tab;

	// tab = ft_splitsigns(e->str);
	// ft_putstrarray(tab);
	ft_puttest(e->str);
	write(1, "\n", 1);
}

int		ft_checkexpressions(t_env e)
{
	dprintf(1, "e1 = '%s'\ne2 = '%s'\n", e.e1.str, e.e2.str);
	ft_compose(&(e.e1));
	ft_compose(&(e.e2));
	// if (!(ft_checkexpression(e.e1.str)) ||
	// 	!(ft_checkexpression(e.e2.str)))
	// 	return (0);

	return (1);
}










int		main(int ac, char **av)
{
	t_env	e;

	if (!(ft_verifs(ac, *(av + 1))))
		return (0);
if (!(ft_getexpressions(&e, *(av + 1))))
return (0);
ft_checkexpressions(e);
// if (!(ft_checkexpressions(e)))
// return (ft_invalidxpressions(e));
	// if (!(ft_decompose(&e)))
		// return (0);	return (0);
	(void)av;
	(void)e;
}
