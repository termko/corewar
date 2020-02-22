/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:07:37 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/25 22:15:04 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*dest;
	char	*from;
	size_t	n;
	size_t	destlen;

	dest = dst;
	from = (char*)src;
	n = size;
	while (*dest && n--)
		dest++;
	destlen = dest - dst;
	n = size - destlen;
	if (n == 0)
		return (destlen + ft_strlen(from));
	while (*from)
	{
		if (n != 1)
		{
			*dest++ = *from;
			n--;
		}
		from++;
	}
	*dest = '\0';
	return (destlen + (from - src));
}
