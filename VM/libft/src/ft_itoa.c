/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:31:16 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/04 21:41:10 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_itoa(int n)
{
	long	num;
	char	*str;
	long	count;

	if (n == 0 || n == -2147483648)
		return (n == 0 ? ft_strdup("0") : ft_strdup("-2147483648"));
	count = 0;
	num = n;
	while (num)
	{
		count++;
		num = num / 10;
	}
	if (!(str = ft_strnew(count)))
		return (NULL);
	num = n;
	while (count > 0)
	{
		str[--count] = num % 10 + '0';
		num = num / 10;
	}
	return (str);
}
