#include "../includes/computorv1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		ft_putstrarray(char **str)
{
	size_t	i;

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

char	*ft_strnew(size_t size)
{
	return (ft_memalloc(size + 1));
}

static char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*new;
	size_t		c;

	c = 0;
	if (s)
	{
		if (!(new = ft_strnew(len)))
			return (NULL);
		c = 0;
		while (c < len)
		{
			new[c] = s[start + c];
			c++;
		}
		return (new);
	}
	return (NULL);
}

static size_t	ft_nbr_words2(char const *s, char c1, char c2)
{
	int			i;
	int			nbr;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c1 || s[i] == c2))
			i++;
		while (s[i] && (s[i] != c1 && s[i] != c2))
			i++;
		if (s[i] != '\0' || (s[i - 1] != c1 && s[i - 1] != c2))
			nbr++;
	}
	return (nbr);
}

char			**ft_str2plit(char const *s, char c1, char c2)
{
	char		**str;
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_nbr_words2(s, c1, c2);
	str = (char **)malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		j = 0;
		while (*s && (*s == c1 || *s == c2))
			s = s + 1;
		while (*(s + j) && (*(s + j) != c1 && *(s + j) != c2))
			j++;
		*(str++) = ft_strsub(s, 0, j);
		s = s + j;
		i++;
	}
	*str = NULL;
	return (str - len);
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

int		ft_split(t_env *e)
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
	dprintf(1, "Parsing error with line '%s' : %c instead of %c\n", str, here, asked);
	return (0);
}

char	*ft_getreduced(char *ptr)
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

void	ft_simplify(char **ptr)
{
	char	*p;

	p = *ptr;
	if (!*p)
		return ;
	while (*(p + 1))
	{
		if (*p == '+' && *(p + 1) == '+')
			*p = ' ';
		else if (*p == '+' && *(p + 1) == '-')
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
		p++;
	}
}

char	*ft_simplified(char *str)
{
	char	*tmp;
	char	*ret;

	tmp = ft_getreduced(str);
	ft_simplify(&tmp);
	ret = ft_getreduced(tmp);
	free(tmp);
	return (ret);
}

int		ft_getexpressions(t_env *e, char *line)
{
	char	*cptr;
	char	*tmp;

	if (!(cptr = strchr(line, '=')) || strchr(cptr + 1, '='))
	{
		dprintf(1, "ERROR 2\n");
		return (0);
	}
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


int		ft_invalidcharacters(char *str)
{
	char *ptr;

	ptr = str;
	write(1, "\e[1;31merror: \e[0m\e[1;29minvalid character :\e[0m\n", 49);
	write(1, str, strlen(str));
	write(1, "\n\e[1;31m", 8);
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' &&
			!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
			*ptr != '-' && *ptr != '*' && *ptr != '=')
		{
			if (*ptr == 'X' && *(ptr + 1) == '^')
			{
				write (1, "  ", 2);
				ptr++;
			}
			else
				write(1, "~", 1);
		}
		else
			write (1, " ", 1);
		ptr++;
	}
	write(1, "\e[0m\n\n", 5);
	return (0);
}

int		ft_checkcharacters(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' &&
			!(*ptr >= '0' && *ptr <= '9') && *ptr != '+' &&
			*ptr != '-' && *ptr != '*' && *ptr != '=')
		{
			if (*ptr == 'X' && *(ptr + 1) == '^')
				ptr++;
			else
				return (0);
		}
		ptr++;
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ac != 2)
		return (0);
	if (!(ft_checkcharacters(*(av + 1))))
		return (ft_invalidcharacters(*(av + 1)));
	if (!(ft_getexpressions(&e, *(av + 1))))
		return (0);
	// if (!(ft_decompose(&e)))
		// return (0);
	dprintf(1, "e1 = '%s'\ne2 = '%s'\n", e.e1.str, e.e2.str);
	return (0);
	(void)av;
}