/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_addchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <vellery-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:33:34 by vellery-          #+#    #+#             */
/*   Updated: 2020/01/30 04:17:46 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_some_chars(t_arg *arg, char *str, int len)
{
	if ((arg->type == 'X' || arg->type == 'x' || arg->type == 'o' ||
			arg->type == 'O' || arg->type == 'b' || arg->type == 'B')
				&& *str != '0')
		arg->type == 'o' || arg->type == 'O' ? add_char(arg, ' ',
					arg->width - len - 1) : add_char(arg, ' ',
							arg->width - len - 2);
	else if ((arg->type == 'X' || arg->type == 'x' ||
				arg->type == 'b' || arg->type == 'B')
						&& *str == '0' && arg->preci != 0)
		add_char(arg, ' ', arg->width - len);
	else if ((arg->type == 'o' || arg->type == 'O') && *str == '0')
		add_char(arg, ' ', arg->width - 1);
	else if ((arg->type == 'X' || arg->type == 'x' ||
				arg->type == 'b' || arg->type == 'B')
						&& *str == '0' && arg->preci == 0)
		add_char(arg, ' ', arg->width);
}

void	save_perc(t_arg *arg)
{
	char *tmp;

	if (!arg->head)
	{
		arg->head = ft_strdup("%");
		arg->buf = arg->head + 1;
	}
	else
	{
		tmp = ft_strndup(arg->head, arg->full_len
						+ arg->buf_len + arg->char_len);
		ft_strdel(&arg->head);
		arg->head = ft_strnjoin(tmp, "%", arg->full_len +
						arg->buf_len + arg->char_len, 1);
		arg->buf = arg->head + arg->full_len + arg->char_len + 1;
		ft_strdel(&tmp);
	}
	arg->format += 2;
	arg->full_len++;
}
