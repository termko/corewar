/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_prnt_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 00:00:33 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/08 00:01:50 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ex_prnt_arr(int *arr, int size)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (i < size)
	{
		ft_putnbr(arr[i]);
		if (i != size - 1)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
