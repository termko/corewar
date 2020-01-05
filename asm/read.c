/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:59:42 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/23 04:04:29 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	append_str(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
}

char	*read_line(int fd)
{
	char	*buff;
	char	c;
	int		i;
	int		check;

	check_malloc(buff = ft_strnew(1024));
	i = 1;
	while (1)
	{
		if (!(i % 1024))
			buff = realloc_str(&buff, i);
		if (read(fd, &c, 1) <= 0)
		{
			free(buff);
			return (NULL);
		}
		if ((check = string_check(&buff, c)) < 0)
			return (NULL);
		else if (check > 0)
			return (buff);
		append_str(buff, c);
		i++;
	}
}
