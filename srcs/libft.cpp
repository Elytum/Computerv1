/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 10:39:06 by achazal           #+#    #+#             */
/*   Updated: 2015/03/23 10:39:07 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"

void				ft_putnbr(int n)
{
	char			buff[2];

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		buff[0] = n % 10;
		write(1, buff, 1);
	}
	else
	{
		buff[0] = n + '0';
		write(1, buff, 1);
	}
}

void				ft_putstrarray(char **str)
{
	size_t			i;

	i = 0;
	if (str && str[i])
	{
		write(1, "{", 1);
		while (str[i])
		{
			write(1, " \"", 2);
			write(1, str[i], strlen(str[i]));
			write(1, "\",", 2);
			i++;
		}
		write(1, "\b }", 3);
	}
}

void				*ft_memalloc(size_t size)
{
	void			*memory;
	unsigned int	counter;
	char			*explorer;

	counter = 0;
	if (!size)
		return (NULL);
	if (!(memory = (void *)malloc(size)))
		return (NULL);
	explorer = (char *)memory;
	if (memory != NULL)
	{
		while (counter++ < size)
			*explorer++ = 0;
	}
	return (memory);
}

char				*ft_strnew_p(size_t size)
{
	return ((char *)ft_memalloc(size + 1));
}
