/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uintmax_toa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:21:03 by vellery-          #+#    #+#             */
/*   Updated: 2019/06/28 19:21:04 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static void	save_ustr_recu(char **tmp, uintmax_t val, int base)
{
	char *digits;

	digits = "0123456789abcdef";
	if (val < (uintmax_t)base)
	{
		**tmp = digits[val];
		(*tmp)++;
		return ;
	}
	save_ustr_recu(tmp, val / base, base);
	save_ustr_recu(tmp, val % base, base);
}

static int	count_len(uintmax_t val, int base)
{
	int	count;

	count = 0;
	if (val == 0)
		return (1);
	while (val)
	{
		count++;
		val = val / base;
	}
	return (count);
}

char		*ft_uintmaxtoa(uintmax_t val, int base)
{
	int		len;
	char	*str;
	char	*tmp;

	len = count_len(val, base);
	str = ft_strnew(len);
	tmp = str;
	save_ustr_recu(&tmp, val, base);
	return (str);
}
