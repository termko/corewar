/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 06:50:23 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/15 07:19:00 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		count_char(int num, int base)
{
	int		i;

	i = 1;
	while (num >= base)
	{
		num /= base;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(int num, int base, int len)
{
	static char	alphabet[] = "0123456789abcdef";
	char		*ret;
	int			size;
	int			i;

	if (num == 0)
		return ("0");
	i = 0;
	size = count_char(num, base);
	check_malloc(ret = ft_strnew(len));
	while (num > 0)
	{
		ret[len - i - 1] = alphabet[num % base];
		num /= base;
		i++;
	}
	return (ret);
}
