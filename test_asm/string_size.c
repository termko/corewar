/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 01:01:07 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 01:23:03 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		size_space(t_core *core, t_size *s, t_read *r)
{
	if (ft_isspace(core->buff[s->end]))
	{
		if (!r->is_comment)
			r->is_valued = 0;
		if (r->empty)
			s->begin = s->begin + 1;
		s->end = s->end + 1;
		return (1);
	}
	return (0);
}

int		size_comment(t_core *core, t_size s, t_read *r)
{
	char	c;

	c = core->buff[s.end];
	if (c == COMMENT_CHAR || c == ALT_COMMENT_CHAR)
	{
		if (!r->is_comment)
		{
			r->is_comchar = 1;
			r->is_valued = 0;
		}
		return (1);
	}
	return (0);
}

int		size_newline(t_core *core, t_size *s, t_read *r)
{
	if (core->buff[s->end] == '\n')
	{
		s->string++;
		if (!r->is_comment)
		{
			if (!r->empty)
				return (1);
			r->is_comchar = 0;
			s->end = s->end + 1;
			s->begin = s->end;
			return (1);
		}
	}
	return (0);
}

int		size_quote(t_core *core, t_size s, t_read *r)
{
	if (core->buff[s.end] == '\"')
	{
		if (!r->is_comchar)
		{
			r->is_valued = 1;
			r->is_comment = (r->is_comment ? 0 : 1);
		}
		return (1);
	}
	else if (!r->is_comchar)
	{
		r->empty = 0;
		r->is_valued = 1;
	}
	return (0);
}

t_size	get_strsize(t_core *core, int prev)
{
	t_size	s;
	t_read	r;

	init_readsize(prev, &s, &r);
	while (s.end < core->buff_size)
	{
		if (size_space(core, &s, &r))
			continue ;
		else if (size_comment(core, s, &r))
			(void)r;
		else if (size_newline(core, &s, &r))
		{
			if (!r.empty)
				return (s);
			continue ;
		}
		else if (size_quote(core, s, &r))
			(void)r;
		if (r.is_valued)
			s.last = s.end;
		s.end++;
	}
	return (s);
}
