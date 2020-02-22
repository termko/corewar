/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intmax_toa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 17:45:32 by vellery-          #+#    #+#             */
/*   Updated: 2019/06/28 17:45:34 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	count_len(intmax_t num, int base)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		count++;
		num = num / base;
	}
	return (count);
}

static void	save_str_recu(char **tmp, intmax_t val, int base)
{
	if (val < base)
	{
		**tmp = val + 48;
		(*tmp)++;
		return ;
	}
	save_str_recu(tmp, val / base, base);
	save_str_recu(tmp, val % base, base);
}

char		*ft_intmaxtoa(intmax_t val, int base)
{
	int		len;
	char	*str;
	char	*tmp;

	if (val == LLONG_MIN || val == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	len = count_len(val, base);
	len += val < 0 ? 1 : 0;
	str = ft_strnew(len);
	tmp = str;
	if (val == INT64_MIN)
	{
		*tmp++ = '-';
		*tmp++ = '9';
		val = 223372036854775808;
	}
	else if (val < 0)
	{
		*tmp++ = '-';
		val = -val;
	}
	save_str_recu(&tmp, val, base);
	return (str);
}
