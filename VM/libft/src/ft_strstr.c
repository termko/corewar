/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:07:49 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/25 22:24:33 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*find;
	char	*from;
	int		i;

	find = (char*)needle;
	from = (char*)haystack;
	if (*find == '\0' && *from == '\0')
		return ((char*)find);
	while (*from)
	{
		i = 0;
		while (from[i] == find[i] && from[i])
			i++;
		if (find[i] == '\0')
			return (from);
		from++;
	}
	return (NULL);
}
