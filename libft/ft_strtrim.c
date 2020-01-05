/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:00:03 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/29 16:15:43 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char		*ft_realloc_c(char *str, char c, size_t size)
{
	size_t	i;
	char	*tmp;

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
	return (tmp);
}

static size_t	ft_count_trim(char const *s)
{
	size_t i;
	size_t last;

	i = 0;
	last = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
			last = i;
		i++;
	}
	return (last);
}

char			*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	size;
	char	*ret;

	if (!s)
		return (NULL);
	while (*s && (*s == 9 || *s == 10 || *s == 32))
		s++;
	size = ft_count_trim(s);
	i = 0;
	while (i <= size)
	{
		if (!(ret = ft_realloc_c(ret, s[i], i + 1)))
			return (NULL);
		i++;
	}
	return (ret);
}
