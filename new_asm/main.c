/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 18:33:29 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/15 08:04:07 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_ops	*ops_list(void)
{
	static t_ops	op_tab[] = 
	{
    	{"live", 1, {1, 0, 0}, {}, {}, 1, 10, 0, 0},
		{"ld", 2, {1, 1, 0}, {0, 0, 1}, {}, 2, 5, 1, 0},
    	{"st", 2, {0, 0, 1}, {0, 1, 1}, {}, 3, 5, 1, 0},
    	{"add", 3, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, 4, 10, 1, 0},
    	{"sub", 3, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, 5, 10, 1, 0},
    	{"and", 3, {1, 1, 1}, {1, 1, 1}, {0, 0, 1}, 6, 6, 1, 0},
    	{"or", 3, {1, 1, 1}, {1, 1, 1}, {0, 0, 1}, 7, 6, 1, 0},
    	{"xor", 3, {1, 1, 1}, {1, 1, 1}, {0, 0, 1}, 8, 6, 1, 0},
    	{"zjmp", 1, {1, 0, 0}, {}, {}, 9, 20, 0, 1},
    	{"ldi", 3, {1, 1, 1}, {1, 0, 1}, {0, 0, 1}, 10, 25, 1, 1},
    	{"sti", 3, {0, 0, 1}, {1, 1, 1}, {1, 0, 1}, 11, 25, 1, 1},
    	{"fork", 1, {1, 0, 0}, {}, {}, 12, 800, 0, 1},
    	{"lld", 2, {1, 1, 0}, {0, 0, 1}, {}, 13, 10, 1, 0},
    	{"lldi", 3, {1, 1, 1}, {1, 0, 1}, {0, 0, 1}, 14, 50, 1, 1},
    	{"lfork", 1, {1, 0, 0}, {}, {}, 15, 1000, 0, 1},
	   	{"aff", 1, {0, 0, 1}, {}, {}, 16, 2, 1, 0},
    	{0, 0, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0, 0, 0, 0}
		};
	return (op_tab);
}

void	error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

void	check_split(char **split, int count)
{
	int		i;

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

void	usage(void)
{
	ft_putendl_fd("Usage: ./asm <path/to/file.s>", STDERR_FILENO);
	exit(1);
}

void	check_malloc(void *addr)
{
	if (addr)
		return ;
	ft_putendl_fd("Unexpected error with malloc!", STDERR_FILENO);
	exit(1);
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
	if (tmp[i - 1] != '\n')
		error("No endline at the end of file!");
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
	// TESTING WITH LAST VALUABLE CHAR
	int		is_valued;

	ret.begin = prev;
	ret.last = prev;
	is_comment = 0;
	is_comchar = 0;
	is_valued = 1;
	empty = 1;
	ret.end = prev;

	while (ret.end < core->buff_size)
	{
		if (ft_isspace(core->buff[ret.end]))
		{
			if (!is_comment)
				is_valued = 0;
			if (empty)
			{
				ret.begin++;
				ret.end++;
				continue ;
			}
		}
	
		else if (core->buff[ret.end] == COMMENT_CHAR)
		{
			if (!is_comment)
			{
				is_comchar = 1;
				is_valued = 0;
			}
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
		{
			empty = 0;
			is_valued = 1;
		}
		if (is_valued)
			ret.last = ret.end;
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
				ft_strsub(core->buff, size.begin, size.last - size.begin + 1));
		
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

void	make_label(t_core *core, char *string, int i)
{
	t_label	*label;
	char	*tmp;
	int		j;

	j = 0;
	while (j < i)
	{
		if (!ft_strchr(LABEL_CHARS, string[j]))
			error("Lexical error");
		j++;
	}
	check_malloc(tmp = ft_strsub(string, 0, i));
	if (!core->labels)
	{
		check_malloc(core->labels = (t_label*)malloc(sizeof(t_label)));
		label = core->labels;
		label->prev = NULL;
	}
	else
	{
		label = core->labels;
		while (label->next)
			label = label->next;
		check_malloc(label->next = (t_label*)malloc(sizeof(t_label)));
		label->next->prev = label;
		label = label->next;
	}
	label->name = tmp;
	label->next = NULL;
}

void	push_token(t_core *core, t_token *token)
{
	t_token	*tmp;

	if (!core->tokens)
		core->tokens = token;
	else
	{
		tmp = core->tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

void	check_labels(t_core *core, t_token *token)
{
	t_label	*tmp;

	if (!core->is_label)
		return ;
	tmp = core->labels;
	while (tmp->next)
		tmp = tmp->next;
	while (core->is_label)
	{
//		printf("ASSIGNING %s TO %s\n", tmp->name, token->op.name);
		tmp->to = token;
		tmp = tmp->prev;
		core->is_label--;
	}
}

t_token	*create_token(t_core *core, char *tmp)
{
	t_ops	*op_tab;
	t_token	*token;
	int		i;

	i = 0;
	op_tab = ops_list();
	while (op_tab[i].id)
	{
		if (ft_strequ(op_tab[i].name, tmp))
			break ;
		i++;
	}
	if (!(op_tab[i].id))
		error("No such operation");

	check_malloc(token = (t_token*)malloc(sizeof(t_token)));
	token->op = op_tab[i];
//	printf("\nFOUND OP [%s]:\nid [%d], name [%s]\n\n", tmp, i, op_tab[i].name);
	token->args = NULL;
	token->next = NULL;
	check_labels(core, token);
	push_token(core, token);
	return (token);
}

void	check_args(char **split, t_token *token, int arg)
{
	int		i;
	char	*string;
	int		*exp;

	if (arg == 0)
		exp = token->op.first;
	else if (arg == 1)
		exp = token->op.second;
	else
		exp = token->op.third;
	string = split[arg];
	i = 0;
	while (string[i] && ft_isspace(string[i]))
	{
//		printf("SKIPPING!\n");
		i++;
	}
	if (!string[i])
		error("Error with args");
	if (exp[0] && string[i] == DIRECT_CHAR)
	{
		/*
		if (string[i + 1] == LABEL_CHAR)
		{
		*/
			token->args[arg].size = (token->op.tdir? 2 : 4);
			// SOMETHING LIKE %:LOOP
		/*
		}
		else
		{
		*/
			// SOMETHING LIKE %3
		/*
		}
		exit (1);
		*/
	}
	else if (exp[2] && string[i] == 'r')
	{
		token->args[arg].size = 1;
		// SOMETHING LIKE r1
	}
	else
	{
		token->args[arg].size = 2;
		// SOMETHING LIKE 10
	}
	token->size += token->args[arg].size;
	//exit(1);

	// STOPPED HERE OMG THIS IS UGLY DO SOMETHING!!!!!!!!!!1
}

void	split_free(char ***split)
{
	int i;

	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
}

void	parse_next(t_token *token, char *string)
{
	char	**split;

	check_malloc(split = ft_strsplit(string, SEPARATOR_CHAR));
	check_split(split, token->op.argc);
	token->size = 1 + token->op.argcode;
	check_malloc(token->args =
			(t_args*)malloc(sizeof(t_args) * token->op.argc));
	if (token->op.argc >= 1)
		check_args(split, token, 0);
	if (token->op.argc >= 2)
		check_args(split, token, 1);
	if (token->op.argc == 3)
		check_args(split, token, 2);
	token->remain = string;
	split_free(&split);
}

char	*crop_string(char *string, int start)
{
	char	*ret;
	int		i;

	i = start;
	while (string[i])
		i++;
	if (!i)
		return (NULL);
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

void	parse_token(t_core *core, char *string)
{
	int		i;
	int		j;
	char	*tmp;
	t_token	*token;

	i = 0;
	while (string[i])
	{
		if (string[i] == LABEL_CHAR || ft_isspace(string[i]))
			break ;
		i++;
	}

	if (!string[i])
		error("Lexical error");
	if (string[i] == LABEL_CHAR)
	{
		make_label(core, string, i++);
		core->is_label++;
		while (string[i] && ft_isspace(string[i]))
			i++;
	}
	else
		i = 0;
	j = i;

	while (string[i])
	{
		if (string[i] == LABEL_CHAR)
			error("Double label error");
		if (ft_isspace(string[i]))
			break ;
		i++;
		
	}
	if (!string[i])
		return ;
	
	check_malloc(tmp = ft_strsub(string, j, i - j));
	
//	printf("MAYBE TOKEN %s\n", tmp);
	
	token = create_token(core, tmp);

//	printf("STRING %s\n", string);
	parse_next(token, crop_string(string, i));
	token->pos = core->size;
//	printf("POS = %d\n", token->pos);
//	printf("SIZE = %d\n\n", token->size);
	core->size += token->size;
}

void	parse_cycle(t_core *core, char *string)
{
	parse_token(core, string);
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
		else
			parse_cycle(core, core->strings[i]);
		i++;
	}
}

t_core	*init_core(void)
{
	t_core *core;

	check_malloc(core = (t_core*)malloc(sizeof(t_core)));
	core->strings = NULL;
	core->buff = NULL;
	core->name = NULL;
	core->comment = NULL;
	core->tokens = NULL;
	core->labels = NULL;
	core->buff_size = 0;
	core->is_label = 0;
	core->size = 0;
	return (core);
}

int		ft_htonl(int x)
{
	return (x & 0xFF)       * 0x1000000
		+ (x & 0xFF00)     * 0x100
		+ (x & 0xFF0000)   / 0x100
		+ (x & 0xFF000000) / 0x1000000;
}

int		init_out(t_core *core, int fd)
{
	int		size;
	int		margin;
	int		magic;

	size = PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + core->size;
	check_malloc(core->out = malloc(sizeof(size)));
	ft_bzero(core->out, size);
	
	margin = 0;
	
	magic = ft_htonl(COREWAR_EXEC_MAGIC);
	
	write(fd, &magic, 4);
	margin += 4;

	write(fd, core->name, ft_strlen(core->name));
	write(fd, core->out, PROG_NAME_LENGTH + 4 - ft_strlen(core->name));
	margin += PROG_NAME_LENGTH + 4;

	magic = ft_htonl(core->size);
	write(fd, &magic, 4);
	
	margin += 4;

	write(fd, core->comment, ft_strlen(core->comment));
	write(fd, core->out, COMMENT_LENGTH + 4 - ft_strlen(core->comment));
	margin += COMMENT_LENGTH + 4;
	
	return (margin);
}

void	last_parse(t_core *core, t_token *token)
{
	// STOPPED HERE, INIT IS DONE I GUESS, JUST DONT FUCK UP WITH PARSING
}

void	encoding(t_core *core)
{
	t_token		*token;
	int			margin;
	int			fd;

	fd = open(core->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	margin = init_out(core, fd); // SEEMS LIKE DONE...
	
	token = core->tokens;
	while (token)
	{
		last_parse(core, token);
		token = token->next;
	}
	// You've got all you need, just encode it, don't mess up, it's easy
}

int main(int ac, char **av)
{
	t_core	*core;
	
	core = init_core();
	check_input(core, ac, av);
	bufftostr(core); // Probably done, but need to test it later and upgrade
		
	for (int i = 0; core->strings[i]; i++)
		printf("%s\n", core->strings[i]);

	printf("\n\nPARSER:\n\n");

	parser(core);
	
	encoding(core); // STOPPED RIGHT HERE, A FUNC UP

/*
	t_token	*tmp;
	tmp = core->tokens;
	while (tmp)
	{
		printf("TOKEN %s\n", tmp->op.name);
		tmp = tmp->next;
	}
	*/
	printf("CORE SIZE %d\n", core->size);
	return (0);
}
