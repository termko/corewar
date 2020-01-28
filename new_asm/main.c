/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 18:33:29 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/28 17:54:53 by ydavis           ###   ########.fr       */
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
/*
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
*/

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
	
		else if (core->buff[ret.end] == COMMENT_CHAR || core->buff[ret.end] == ALT_COMMENT_CHAR)
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
		i++;
	if (!string[i])
		error("Error with args");
	if (exp[0] && string[i] == DIRECT_CHAR)
	{
		token->args[arg].size = (token->op.tdir? 2 : 4);
		if (string[i + 1] == LABEL_CHAR)
		{
			token->args[arg].type = 4;
			// SOMETHING LIKE %:LOOP
		}
		else
		{
			token->args[arg].type = 1;
			// SOMETHING LIKE %3
		}
	}
	else if (exp[2] && string[i] == 'r')
	{
		token->args[arg].size = 1;
		// SOMETHING LIKE r1
		token->args[arg].type = 2;
	}
	else if (exp[1])
	{
		token->args[arg].size = 2;
		if (string[i] == LABEL_CHAR)
		{
			// SOMETHING LIKE :LOOP
			token->args[arg].type = 5;
		}
		else
		{
			token->args[arg].type = 3;
			// SOMETHING LIKE 10
		}
	}
	else
		error("Error with args");
	token->size += token->args[arg].size;
	check_malloc(token->args[arg].str = ft_strdup(string));
	printf("PARSED ARG [%d] OF TYPE %d OF SIZE %d: %s\n", arg,token->args[arg].type, token->args[arg].size, token->args[arg].str);

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

	token = create_token(core, tmp);

	parse_next(token, crop_string(string, i));
	token->pos = core->size;
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
	core->out = NULL;
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
	void	*tmp;
	int		size;
	int		margin;
	int		magic;

	(void)fd;
	size = PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + core->size;
	check_malloc(core->out = malloc(size));
	ft_bzero(core->out, size);

	tmp = core->out;
	margin = 0;

	magic = ft_htonl(COREWAR_EXEC_MAGIC);

	tmp = ft_memcpy(tmp, &magic, 4) + 4;
	margin += 4;

	tmp = ft_memcpy(tmp, core->name, ft_strlen(core->name)) +
		PROG_NAME_LENGTH + 4;
	margin += PROG_NAME_LENGTH + 4;

	magic = ft_htonl(core->size);
	tmp = ft_memcpy(tmp, &magic, 4) + 4;
	margin += 4;

	tmp = ft_memcpy(tmp, core->comment, ft_strlen(core->comment)) +
		COMMENT_LENGTH + 4;
	margin += COMMENT_LENGTH + 4;
	
	//write(fd, core->out, margin);

	// REFACTOR THIS SHIT PLEASE!!!!!!!!!!1

	return (margin);
}

void	direct_value(t_core *core, t_token *token, int i)
{
	char	*tmp;
	int		j;

	(void)core;
	check_malloc(tmp = ft_strtrim(token->args[i].str));
	j = 1;
	while (tmp[j])
	{
		if (tmp[j] == '+' || (!ft_isdigit(tmp[j]) && tmp[j] != '-'))
			error("Error with direct arg");
		j++;
	}
	/*
	(void)core;
	tmp = token->args[i].str;
	while (tmp && ft_isspace(*tmp))
		tmp++;
	tmp++;
	if (ft_strchr(tmp, '+') || !ft_isdigital(tmp))
		error("Error with direct arg");
*/
	token->args[i].value = ft_atoi(tmp + 1);
	printf("FOUND DIRECT VALUE %d FROM %s\n", token->args[i].value, token->args[i].str);
	free(tmp);
	token->args[i].type = 2;
}

void	register_value(t_core *core, t_token *token, int i)
{
	char	*begin;
	char	*tmp;

	(void)core;
	check_malloc(begin = ft_strtrim(token->args[i].str));
	tmp = begin + 1;
	if (!ft_isdigital(tmp) || ft_strlen(tmp) > 2)
		error("Error with register arg");
	token->args[i].value = ft_atoi(tmp);
	printf("FOUND REGISTER VALUE %d FROM %s\n", token->args[i].value, token->args[i].str);
	free(begin);
	token->args[i].type = 1;
}

void	indirect_value(t_core *core, t_token *token, int i)
{
	char	*tmp;
	int		j;

	(void)core;
	check_malloc(tmp = ft_strtrim(token->args[i].str));
	j = 0;
	while (tmp[j])
	{
		if (tmp[j] == '+')
			error("Error with indirect arg");
		if (!ft_isdigit(tmp[j]) && tmp[j] != '-')
			error("Error with indirect arg");
		j++;
	}
	token->args[i].value = ft_atoi(tmp);
	printf("FOUND INDIRECT VALUE %d FROM %s\n", token->args[i].value, token->args[i].str);
}

void	direct_label(t_core *core, t_token *token, int i)
{
	t_label	*label;
	char	*tmp;

	check_malloc(tmp = ft_strtrim(token->args[i].str));
	label = core->labels;
	while (label)
	{
		if (ft_strstr(tmp + 2, label->name))
			break ;
		label = label->next;
	}
	if (!label)
		error("No such label");
	if (!label->to)
		token->args[i].value = (int)(core->size - token->pos);
	else
		token->args[i].value = (int)(label->to->pos - token->pos);
	printf("FOUND DIRECT LABEL VALUE %d FROM %s\n", token->args[i].value, token->args[i].str);
	free(tmp);
	token->args[i].type = 2;
}

void	indirect_label(t_core *core, t_token *token, int i)
{
	char	*tmp;
	t_label	*label;

	check_malloc(tmp = ft_strtrim(token->args[i].str));
	label = core->labels;
	while (label)
	{
		if (ft_strstr(tmp + 1, label->name))
			break ;
		label = label->next;
	}
	if (!label)
		error("No such label");
	if (!label->to)
		token->args[i].value = (int)(core->size - token->pos);
	else
		token->args[i].value = (int)(label->to->pos - token->pos);
	printf("FOUND INDIRECT LABEL VALUE %d FROM %s\n", token->args[i].value, token->args[i].str);
	free(tmp);
	token->args[i].type = 3;
}

void	args_values(t_core *core, t_token *token)
{
	int		i;

	i = 0;
	while (i < token->op.argc)
	{
		if (token->args[i].type == 1)
			direct_value(core, token, i);
		else if (token->args[i].type == 2)
			register_value(core, token, i);
		else if (token->args[i].type == 3)
			indirect_value(core, token, i);
		else if (token->args[i].type == 4)
			direct_label(core, token, i);
		else if (token->args[i].type == 5)
			indirect_label(core, token, i);
		i++;
	}
}

int		paste_args(t_token *token, int margin, void *tmp)
{
	int		i;
	int		j;
	int		magic;
	char	*arr;

	i = 0;
	check_malloc(arr = ft_strnew(4));
	while (i < token->op.argc)
	{
		magic = token->args[i].value;
		j = 0;
		while (j < token->args[i].size)
		{
			printf("%x\n", magic & 0xff);
			arr[3 - j] = magic & 0xff;
			printf("MAYBE? %x\n", arr[3 - j]);
			magic = magic >> 0x8;
			j++;
		}
		while (--j >= 0)
			tmp = ft_memcpy(tmp, arr + 3 - j, 1) + 1;
		margin += token->args[i].size;
		i++;
	}
	free(arr);
	return (margin);
}

int		paste_argcode(t_token *token, int margin, void *tmp)
{
	int				i;
	int				magic;
	unsigned char	value;

	i = 0;
	value = 0;
	while (i < token->op.argc)
	{
		magic = (unsigned char)token->args[i].type;
		value |= ((magic >> 1) & 0x1) << (7 - i * 2);
		value |= (magic & 0x1) << (6 - i * 2);
		i++;
	}
	printf("argcode %x\n", value);
	ft_memcpy(tmp, &value, 1);
	return (margin + 1);
}

int		last_parse(t_core *core, t_token *token, int margin)
{
	void	*tmp;
	int		magic;

	printf("\nPARSING TOKEN %s\n", token->op.name);
	args_values(core, token);
	

	magic = token->op.id;

	printf("OP %x\n", magic);
	tmp = ft_memcpy(core->out + margin, &magic, 1) + 1;
	margin++;

	if (token->op.argcode)
		margin = paste_argcode(token, margin, tmp++);
	margin = paste_args(token, margin, tmp);
	return (margin);
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
		margin = last_parse(core, token, margin);
		token = token->next;
	}
	write(fd, core->out, margin);
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

	printf("\n\nPARSER\n");

	parser(core);
	
	printf("OK\n\nENCODER\n");

	encoding(core); // STOPPED RIGHT HERE, A FUNC UP
	
	printf("OK\n");

	return (0);
}
