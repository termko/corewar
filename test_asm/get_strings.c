/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:41:34 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 01:25:04 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		check_isspace(t_core *core, int *i, t_read r)
{
	if (ft_isspace(core->buff[*i]) && r.empty)
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}

int		check_iscomment(t_core *core, int i, t_read *r)
{
	if (core->buff[i] == COMMENT_CHAR)
	{
		if (!r->is_comment)
			r->is_comchar = 1;
		return (1);
	}
	return (0);
}

int		check_newline(t_core *core, int i, t_read *r)
{
	if (core->buff[i] == '\n')
	{
		if (!r->is_comment)
			r->is_comchar = 0;
		if (!r->is_comment && !r->empty)
		{
			r->empty = 1;
			r->count++;
		}
		return (1);
	}
	return (0);
}

int		check_quotes(t_core *core, int i, t_read *r)
{
	if (core->buff[i] == '\"')
	{
		if (!r->is_comchar)
		{
			if (!r->is_comchar)
			{
				if (r->empty)
					error("Unexpected string symbol (\")");
				r->is_comment = (r->is_comment ? 0 : 1);
			}
		}
		return (1);
	}
	return (0);
}

int		count_strings(t_core *core)
{
	t_read	r;
	int		i;

	i = 0;
	r.count = 0;
	r.is_comment = 0;
	r.is_comchar = 0;
	r.empty = 1;
	while (i < core->buff_size)
	{
		if (check_isspace(core, &i, r))
			continue ;
		else if (check_iscomment(core, i, &r))
			(void)i;
		else if (check_newline(core, i, &r))
			(void)i;
		else if (check_quotes(core, i, &r))
			(void)i;
		else if (!r.is_comchar)
			r.empty = 0;
		i++;
	}
	if (r.is_comment)
		error("Error with string symbol (\")");
	return (r.count);
}
