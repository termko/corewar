/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 04:31:16 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/06 22:07:40 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*from;
	unsigned char	*to;

	if (n == 0 || dst == src)
		return (NULL);
	i = 0;
	from = (unsigned char*)src;
	to = (unsigned char*)dst;
	while (i < n)
	{
		to[i] = from[i];
		if (to[i] == (unsigned char)c)
			return (to + i + 1);
		i++;
	}
	return (NULL);
}
