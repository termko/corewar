/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_matdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 00:04:17 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/08 00:05:29 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_ex_matdel(int **mat, int str)
{
	int i;

	i = 0;
	while (i < str)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
	*mat = NULL;
	return (NULL);
}
