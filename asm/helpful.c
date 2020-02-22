/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:18:46 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/22 19:45:05 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		ft_htonl(int x)
{
	return ((x & 0xFF) * 0x1000000 +
			(x & 0xFF00) * 0x100 +
			(x & 0xFF0000) / 0x100 +
			(x & 0xFF000000) / 0x1000000);
}

void	split_free(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
}

char	*crop_string(char *string, int start)
{
	char	*ret;
	int		i;

	i = start;
	while (string[i])
		i++;
	if (!i)
		error("Error with arguments, unexpected end of line");
	check_malloc(ret = ft_strnew(i - start));
	i = 0;
	while (string[start])
	{
		ret[i] = string[start];
		i++;
		start++;
	}
	return (ret);
}

void	last_valued(t_core *core)
{
	int i;
	int last;

	i = 0;
	last = 0;
	while (i < core->buff_size)
	{
		if (core->buff[i] == '\n')
			last = i;
		i++;
	}
	if (last == core->buff_size - 1)
		return ;
	i = last;
	while (i < core->buff_size)
	{
		if (core->buff[i] == COMMENT_CHAR || ft_isspace(core->buff[i]))
			return ;
		i++;
	}
	error("No newline at the end of file!");
}
