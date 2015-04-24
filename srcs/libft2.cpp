/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 10:39:10 by achazal           #+#    #+#             */
/*   Updated: 2015/03/23 10:39:11 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"

static char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*new_p;
	size_t		c;

	c = 0;
	if (s)
	{
		if (!(new_p = ft_strnew_p(len)))
			return (NULL);
		c = 0;
		while (c < len)
		{
			new_p[c] = s[start + c];
			c++;
		}
		return (new_p);
	}
	return (NULL);
}

static size_t	ft_nbr_words(char const *s, char c)
{
	int			i;
	int			nbr;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] != '\0' || s[i - 1] != c)
			nbr++;
	}
	return (nbr);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**str;
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_nbr_words(s, c);
	str = (char **)malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		j = 0;
		while (*s && *s == c)
			s = s + 1;
		while (*(s + j) && *(s + j) != c)
			j++;
		*(str++) = ft_strsub(s, 0, j);
		s = s + j;
		i++;
	}
	*str = NULL;
	return (str - len);
}
