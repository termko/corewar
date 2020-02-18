/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:01:34 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 02:07:57 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_labels(t_core *core, t_token *token)
{
	t_label *tmp;

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

void	label_chars(t_core *core, t_string *str, char *tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		if (!ft_strchr(LABEL_CHARS, tmp[i]))
			parse_error("Illegal characters in label", str);
		i++;
	}
}

void	make_label(t_core *core, t_string *str, int i)
{
	t_label	*label;
	char	*tmp;

	check_malloc(tmp = ft_strsub(str->string, 0, i));
	label_chars(core, str, tmp);
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
	label->to = NULL;
	label->next = NULL;
}
