/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 18:33:29 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/05 23:14:59 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	usage(void)
{
	ft_putstr_fd("Usage: ./asm <path/to/file.s>\n", STDERR_FILENO);
	exit(1);
}

void	error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

void	check_malloc(void *addr)
{
	if (!addr)
	{
		ft_putstr_fd("Unexpected error with malloc!\n", STDERR_FILENO);
		exit(1);
	}
}

int		ft_isspace(char c)
{
	if (c != 9 && (c < 11 || c > 13) && c != ' ')
		return (0);
	return (1);
}

void	realloc_char(t_core *core, char *tmp, int cur, int i)
{
	char	*ret;

	check_malloc(ret = ft_strnew(cur * REALLOC_TIME + i));
	ret = ft_strcat(ret, core->buff);
	ret = ft_strcat(ret, tmp);
	free(core->buff);
	core->buff = ret;
}

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
	free(tmp);
}

t_core	*check_input(t_core *core, int ac, char **av)
{
	int		fd;

	if (ac != 2)
		usage();
	if (ft_strcmp(av[1] + ft_strlen(av[1]) - 2, ".s"))
		usage();
	if ((fd = open(av[1], 'r')) < 0)
		error("Error opening file!");
	read_file(fd, core);
	close(fd);
	return (core);
}

int		count_strings(t_core *core)
{
	int		count;
	int		i;
	int		is_comment;
	int		empty;
	int		is_comchar;

	i = 0;
	count = 0;
	is_comment = 0;
	is_comchar = 0;
	empty = 1;

	while (i < core->buff_size)
	{
		if (ft_isspace(core->buff[i]) && empty)
		{
			i++;
			continue ;
		}
	
		else if (core->buff[i] == COMMENT_CHAR)
		{
			if (!is_comment)
				is_comchar = 1;
		}
	
		else if (core->buff[i] == '\n')
		{
			if (!is_comment)
				is_comchar = 0;
			if (!is_comment && !empty)
			{
				empty = 1;
				count++;
			}
		}
	
		else if (core->buff[i] == '\"')
		{
			if (!is_comchar)
			{
				if (empty)
					error("Unexpected string symbol (\")");
				is_comment = (is_comment ? 0 : 1);
			}
		}
	
		else if (!is_comchar)
			empty = 0;
		i++;
	}

	if (is_comment)
		error("Error with string symbol (\")");
	return (count);
}

t_size	get_strsize(t_core *core, int prev)
{
	t_size	ret;
	int		is_comment;
	int		is_comchar;
	int		empty;
	
	ret.begin = prev;
	is_comment = 0;
	is_comchar = 0;
	empty = 1;
	ret.end = prev;

	while (ret.end < core->buff_size)
	{
		if (ft_isspace(core->buff[ret.end]) && empty)
		{
			ret.begin++;
			ret.end++;
			continue ;
		}
	
		else if (core->buff[ret.end] == COMMENT_CHAR)
		{
			if (!is_comment)
				is_comchar = 1;
		}
	
		else if (core->buff[ret.end] == '\n')
		{
			if (!is_comment)
			{
				if (!empty)
					return (ret);
				else
				{
					is_comchar = 0;
					ret.end++;
					ret.begin = ret.end;
					continue ;
				}
			}
		}

		else if (core->buff[ret.end] == '\"')
		{
			if (!is_comchar)
				is_comment = (is_comment ? 0 : 1);
		}

		else if (!is_comchar)
			empty = 0;
		ret.end++;
	}
	return (ret);
}

void	bufftostr(t_core *core)
{
	int		count;
	int		i;
	int		prev;
	t_size	size;

	count = count_strings(core); // DOUBLECHECK THIS PIECE OF SHIT!!!!!1
	
	check_malloc(core->strings = (char**)malloc(sizeof(char*) * (count + 1)));
	i = 0;
	prev = 0;
	while (i < count)
	{
		size = get_strsize(core, prev);
		prev = size.end;
		check_malloc(core->strings[i] =
				ft_strsub(core->buff, size.begin, size.end - size.begin));
		
		// DEBUG TESTING
		/*
		printf("STRING %d: begin %d, end %d\n", i, size.begin, size.end);
		printf("STRING:\n");
				for (int j = size.begin; j < size.end; j++)
			printf("%c", core->buff[j]);
		printf("\n\n\n");
		*/

		i++;
	}
	core->strings[i] = NULL;
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

void	name_comment(t_core *core, char *string)
{
	char	*loc;

	if (ft_strstr(string, NAME_CMD_STRING) == string)
	{
		loc = ft_strchr(string, '\"');
		if (!loc)
			error("Error with name");
		core->name = get_string(loc + 1);
	}
	else if (ft_strstr(string, COMMENT_CMD_STRING) == string)
	{
		loc = ft_strchr(string, '\"');
		if (!loc)
			error("Error with comment");
		core->comment = get_string(loc + 1);
	}
}

void	parser(t_core *core)
{
	int i;

	i = 0;
	while (core->strings[i])
	{
		if (i < 2)
			name_comment(core, core->strings[i]);
		else if (!core->name || !core->comment)
			error("No name or comment");
		// CONTINUE HERE, IT WILL BE A FUCKING NIGHTMARE
		i++;
	}
}

t_core	*init_core(void)
{
	t_core *core;

	check_malloc(core = (t_core*)malloc(sizeof(t_core)));
	core->buff_size = 0;
	core->strings = NULL;
	core->buff = NULL;
	core->parse = NULL;
	core->name = NULL;
	core->comment = NULL;
	return (core);
}

int main(int ac, char **av)
{
	t_core	*core;
	
	core = init_core();
	check_input(core, ac, av);
	bufftostr(core); // Probably done, but need to test it later and upgrade

	// DEBUG PURPOSES
	/*
	for (int i = 0; core->strings[i]; i++)
		printf("%s\n", core->strings[i]);
	*/
		
	parser(core);
	return (0);
}
