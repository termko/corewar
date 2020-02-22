/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:12:47 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/25 22:18:54 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		countword(char *str, char c)
{
	int k;
	int flag;
	int i;

	k = 0;
	flag = 1;
	i = 0;
	while (str[i])
	{
		if (flag == 1 && str[i] != c)
		{
			k++;
			flag = 0;
		}
		else if (flag == 0 && str[i] == c)
			flag = 1;
		i++;
	}
	return (k);
}

static int		wordlen(char *str, char c, int i)
{
	int k;

	k = i;
	while (str[i] != c && str[i])
		i++;
	return (i - k);
}

static void		*worddel(char **ret, int k)
{
	int i;

	i = 0;
	while (i < k)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	if (!(ret = (char**)malloc(sizeof(char*) * (countword((char*)s, c) + 1))))
		return (NULL);
	i = -1;
	k = 0;
	while (s[++i])
		while (k < countword((char*)s, c))
		{
			while (s[i] && s[i] == c)
				i++;
			if (!(ret[k] = ft_strnew((wordlen((char*)s, c, i) + 1))))
				return (worddel(ret, k));
			j = 0;
			while (s[i] != c && s[i])
				ret[k][j++] = s[i++];
			ret[k++][j] = '\0';
		}
	ret[k] = NULL;
	return (ret);
}
