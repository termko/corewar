/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 01:26:08 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 02:00:17 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	name_comment(t_core *core, char *string)
{
	char	*loc;

	if (ft_strstr(string, NAME_CMD_STRING) == string)
	{
		if (!(loc = ft_strchr(string, '\"')))
			error("Error with name");
		core->name = get_string(loc + 1);
	}
	else if (ft_strstr(string, COMMENT_CMD_STRING) == string)
	{
		if (!(loc = ft_strchr(string, '\"')))
			error("Error with comment");
		core->comment = get_string(loc + 1);
	}
}

int		parse_label(t_core *core, char *string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == LABEL_CHAR || ft_isspace(string[i]))
			break ;
		i++;
	}
	if (!string[i])
		error("Unexpected end of line");
	if (string[i] == LABEL_CHAR)
	{
		make_label(core, string, i++);
		core->is_label++;
		while (string[i] && ft_isspace(string[i]))
			i++;
	}
	else
		i = 0;
	return (i);
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
	if (token->op.argc >= 3)
		check_args(split, token, 2);
	token->remain = string;
	split_free(&split);
}

void	parse_token(t_core *core, char *string)
{
	int		i;
	int		j;
	char	*tmp;
	t_token	*token;

	i = parse_label(core, string);
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

void	parser(t_core *core)
{
	int		i;

	i = 0;
	while (core->strings[i])
	{
		if (i < 2)
			name_comment(core, core->strings[i]);
		else if (!core->name || !core->comment)
			error("No name or comment");
		else
			parse_token(core, core->strings[i]);
		i++;
	}
}
