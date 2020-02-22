/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 17:35:41 by vellery-          #+#    #+#             */
/*   Updated: 2019/08/20 18:11:58 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static double	ft_pow(double val, int pow)
{
	if (pow == 0)
		return (1);
	if (pow == 1)
		return (val);
	return (val * ft_pow(val, pow - 1));
}

static void		set_int(intmax_t val, char *str, int count)
{
	if (val == 0)
		str[count] = '0';
	while (val)
	{
		str[--count] = val % 10 + '0';
		val /= 10;
	}
}

static int		len(intmax_t num)
{
	int		count;

	if (num < 0)
		num = -num;
	count = 0;
	while (num > 0 && ++count && (num /= 10))
		;
	return (count);
}

static void		set_decim(long double val, int *i, int preci, char *str)
{
	unsigned long int	n;

	n = val;
	str[*i] = (preci) ? '.' : '\0';
	while (preci--)
	{
		val = (val - n) * 10.0;
		n = val;
		str[++*i] = n + '0';
	}
}

char			*ft_ftoa(long double val, int preci, int sign)
{
	unsigned long int	num;
	char				*str;
	int					i;

	preci = preci < 0 ? 6 : preci;
	sign = val < 0 ? 1 : sign;
	val = sign ? -val : val;
	val += (preci >= 0) ? 5.000001 / ft_pow(10, preci + 1) : 0;
	num = val;
	i = len(num) + sign;
	if (!(str = ft_strnew((i + preci + (preci > 0 ? 1 : 0) + 1))))
		return (NULL);
	str[0] = (sign) ? '-' : '\0';
	set_int(num, str, i);
	i += (num == 0 ? 1 : 0);
	set_decim(val, &i, preci, str);
	return (str);
}
