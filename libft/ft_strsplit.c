/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:05:18 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/30 21:12:03 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_count_split(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			return (count);
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char		*ft_realloc_c(char *str, char c, size_t size)
{
	size_t	i;
	char	*tmp;

	if (!str)
	{
		if (!(tmp = (char*)malloc(sizeof(char) * 2)))
			return (NULL);
		tmp[0] = c;
		tmp[1] = '\0';
		return (tmp);
	}
	if (!(tmp = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i++] = c;
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

static char		**ft_null_count(void)
{
	char **str;

	if (!(str = (char**)malloc(sizeof(char*) + 1)))
		return (NULL);
	*str = NULL;
	return (str);
}

static char		**ft_memfree(char ***ret, size_t i)
{
	size_t j;

	j = 0;
	while (j < i)
	{
		if (*ret[j])
			free(*ret[j]);
		j++;
	}
	if (*ret)
		free(*ret);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	size_t	count;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (!(count = ft_count_split(s, c)))
		return (ft_null_count());
	if (!(ret = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		ret[i] = NULL;
		while (*s && *s != c)
			if (!(ret[i] = ft_realloc_c(ret[i], *s++, ++j)))
				return (ft_memfree(&ret, i));
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
