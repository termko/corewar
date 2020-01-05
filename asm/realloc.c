/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:43:58 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/17 14:58:06 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		string_check(char **buff, char c)
{
	if (c == '\0')
	{
		free(*buff);
		return (-1);
	}
	if (c == '\n')
	{
		if (*buff[0])
			return (1);
		free(*buff);
		return (-1);
	}
	return (0);
}

char	*realloc_str(char **str, int i)
{
	char	*ret;

	check_malloc(ret = ft_strnew(1024 * i));
	ret = ft_strcpy(ret, *str);
	free(*str);
	return (ret);
}
