/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmaxtoa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:49:19 by vellery-          #+#    #+#             */
/*   Updated: 2019/10/17 11:49:24 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	count_len(uintmax_t num, int base)
{
	int		count;

	count = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		count++;
		num /= base;
	}
	return (count);
}

static void	save_str_recu(char **tmp, uintmax_t val, int base)
{
	char	*digits;

	digits = "0123456789abcdef";
	if (val < (uintmax_t)base)
	{
		**tmp = digits[val];
		(*tmp)++;
		return ;
	}
	save_str_recu(tmp, val / base, base);
	save_str_recu(tmp, val % base, base);
}

char		*ft_uintmaxtoa(uintmax_t val, int base)
{
	int		len;
	char	*str;
	char	*tmp;

	len = count_len(val, base);
	if (!(str = ft_strnew(len)))
		return (NULL);
	tmp = str;
	save_str_recu(&tmp, val, base);
	return (str);
}
