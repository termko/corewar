/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <vellery-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 20:18:25 by vellery-          #+#    #+#             */
/*   Updated: 2020/02/14 06:36:15 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	func(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int			i;
	int			p;
	long long	ret;
	long long	point;

	ret = 0;
	p = 1;
	i = 0;
	while (str[i] && func(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			p = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		point = ret;
		ret = ret * 10 + (str[i] - '0');
		if (point > ret)
			return (p == -1 ? 0 : -1);
		i++;
	}
	return (ret * p);
}
