/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:25:33 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/25 22:20:40 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*find;
	char	*st;
	size_t	qo;

	find = (char*)needle;
	if (*find == '\0')
		return ((char*)haystack);
	while (*haystack && len--)
	{
		st = (char*)haystack;
		qo = len + 1;
		while (*find && *st && qo-- > 0)
			if (*find++ != *st++)
				break ;
		if (*find == '\0' && (*--find == *--st))
			return ((char*)haystack);
		else
		{
			find = (char*)needle;
			qo = len;
		}
		haystack++;
	}
	return (NULL);
}
