/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:00:03 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 04:14:09 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	size_t	j;
	size_t	i;
	char	*ret;

	if (!s)
		return (NULL);
	while (*s && (*s == 9 || *s == 10 || *s == 32))
		s++;
	j = ft_strlen(s);
	while (j != 0 && (s[j - 1] == 9 || s[j - 1] == 10 || s[j - 1] == 32))
		j--;
	if (!(ret = ft_strnew(j)))
		return (NULL);
	i = 0;
	while (i < j)
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
}
