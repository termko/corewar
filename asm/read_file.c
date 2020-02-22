/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:39:47 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/22 19:46:43 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	read_file(int fd, t_core *core)
{
	int		cur;
	int		i;
	char	*tmp;

	check_malloc(core->buff = ft_strnew(REALLOC_TIME));
	cur = 0;
	while (1)
	{
		check_malloc(tmp = ft_strnew(REALLOC_TIME));
		i = read(fd, tmp, REALLOC_TIME);
		if (i <= 0)
			break ;
		realloc_char(core, tmp, cur, i);
		core->buff_size = cur * REALLOC_TIME + i;
		cur++;
		if (i < REALLOC_TIME)
			break ;
		free(tmp);
	}
	last_valued(core);
	free(tmp);
}

t_core	*check_input(t_core *core, int ac, char **av)
{
	int		fd;
	int		len;

	if (ac != 2)
		usage();
	len = ft_strlen(av[1]);
	if (ft_strcmp(av[1] + len - 2, ".s"))
		usage();
	if ((fd = open(av[1], 'r')) < 0)
		error("Error opening file!");
	check_malloc(core->file = ft_strnew(len + 2));
	core->file = ft_strncat(core->file, av[1], len - 1);
	core->file = ft_strcat(core->file, "cor");
	read_file(fd, core);
	close(fd);
	return (core);
}

void	new_string(t_core *core, t_size size, int count)
{
	t_string	*string;

	if (!core->strs)
	{
		check_malloc(core->strs = (t_string*)malloc(sizeof(t_string)));
		string = core->strs;
	}
	else
	{
		string = core->strs;
		while (string->next)
			string = string->next;
		check_malloc(string->next = (t_string*)malloc(sizeof(t_string)));
		string = string->next;
	}
	if (size.last - size.begin + 1 <= 0)
		string->string = NULL;
	else
	{
		check_malloc(string->string =
			ft_strsub(core->buff, size.begin, size.last - size.begin + 1));
	}
	string->id = count;
	string->next = NULL;
}

void	bufftostr(t_core *core)
{
	int		count;
	int		prev;
	t_size	size;

	prev = 0;
	count = 1;
	while (prev < core->buff_size)
	{
		size = get_strsize(core, prev);
		count += size.string - 1;
		prev = size.end;
		new_string(core, size, count);
	}
}

char	*get_string(char *loc)
{
	char	*ret;
	int		i;

	i = 0;
	while (loc[i])
	{
		if (loc[i] == '\"')
			break ;
		i++;
	}
	if (loc[i + 1])
		error("String error");
	check_malloc(ret = ft_strnew(i));
	i = 0;
	while (loc[i])
	{
		if (loc[i] == '\"')
			break ;
		ret[i] = loc[i];
		i++;
	}
	return (ret);
}
