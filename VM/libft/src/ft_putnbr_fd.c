/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:58:08 by vellery-          #+#    #+#             */
/*   Updated: 2018/11/27 20:10:51 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int copy;
	int i;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	copy = n;
	i = 1;
	while (copy / 10 > 0)
	{
		i = i * 10;
		copy = copy / 10;
	}
	while (i > 0)
	{
		ft_putchar_fd(n / i % 10 + '0', fd);
		i = i / 10;
	}
}
