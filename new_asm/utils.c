/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:35:09 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/28 17:36:50 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		ft_isdigital(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

void    check_split(char **split, int count)
{
    int     i;

    i = 0;
    while (i < count)
    {
        if (!split[i])
            error("Lack of arguments");
        i++;
    }
    if (split[i])
        error("Too much arguments");
}

void    check_malloc(void *addr)
{
    if (addr)
        return ;
    ft_putendl_fd("Unexpected error with malloc!", STDERR_FILENO);
    exit(1);
}

int     ft_isspace(char c)
{
    if (c != 9 && (c < 11 || c > 13) && c != ' ')
        return (0);
    return (1);
}

void    realloc_char(t_core *core, char *tmp, int cur, int i)
{
    char    *ret;

    check_malloc(ret = ft_strnew(cur * REALLOC_TIME + i));
    ret = ft_strcat(ret, core->buff);
    ret = ft_strcat(ret, tmp);
    free(core->buff);
    core->buff = ret;
}
