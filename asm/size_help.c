/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 01:21:23 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 01:22:14 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_readsize(int prev, t_size *s, t_read *r)
{
	s->begin = prev;
	s->last = prev;
	s->end = prev;
	s->string = 0;
	r->is_comment = 0;
	r->is_comchar = 0;
	r->is_valued = 0;
	r->empty = 1;
}
