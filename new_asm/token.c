/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:13:52 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 02:16:54 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

t_token	*create_token(t_core *core, char *tmp)
{
	t_token	*token;
	t_ops	*op_tab;
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
