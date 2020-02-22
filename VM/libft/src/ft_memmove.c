/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:08:57 by vellery-          #+#    #+#             */
/*   Updated: 2018/11/29 20:37:21 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*to;
	char	*from;

	if (len == 0 || dst == src)
		return (dst);
	from = (char*)src;
	to = (char*)dst;
	if (to <= from || to >= from + len)
	{
		while (len--)
			*to++ = *from++;
	}
	else
	{
		from = from + len - 1;
		to = to + len - 1;
		while (len--)
			*to-- = *from--;
	}
	return (dst);
}
