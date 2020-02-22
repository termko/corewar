/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:12:51 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/25 22:27:57 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = 0;
	if (c == '\0')
		return (ft_strchr(s, '\0'));
	while (*s)
	{
		if (*s == (char)c)
			ret = (char*)s;
		s++;
	}
	return (ret);
}
