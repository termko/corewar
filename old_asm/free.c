/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:42:12 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 04:01:16 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_strings(t_core *core)
{
	int i;

	if (!core->strings)
		return ;
	i = 0;
	while (core->strings[i])
	{
		free(core->strings[i]);
		i++;
	}
	free(core->strings);
}

void	free_labels(t_core *core)
{
	t_label	*label;
	t_label	*tmp;

	label = core->labels;
	while (label)
	{
		tmp = label->next;
		free(label->name);
		free(label);
		label = tmp;
	}
}

void	free_tokens(t_core *core)
{
	t_token	*token;
	t_token	*tmp;
	int		i;

	token = core->tokens;
	while (token)
	{
		tmp = token->next;
		free(token->remain);
		i = 0;
		while (i < token->op.argc)
		{
			free(token->args[i].str);
			i++;
		}
		free(token->args);
		free(token);
		token = tmp;
	}
}

void	free_core(t_core **core)
{
	free((*core)->buff);
	free((*core)->file);
	free((*core)->name);
	free((*core)->comment);
	free((*core)->out);
	free_strings(*core);
	free_labels(*core);
	free_tokens(*core);
	free(*core);
}
