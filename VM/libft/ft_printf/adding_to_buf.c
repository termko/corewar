/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_to_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 17:33:49 by vellery-          #+#    #+#             */
/*   Updated: 2019/06/28 17:33:51 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_concat(t_arg *arg, const char *str, int len)
{
	if (len == -1)
		while (*str)
			*arg->buf++ = *str++;
	else
		while (len--)
			*arg->buf++ = *str++;
}

void	add_char(t_arg *arg, char c, int n)
{
	while (n-- > 0)
		*arg->buf++ = c;
}

void	flag_minus(t_arg *arg)
{
	if (arg->flags[1] || arg->flags[3])
		*arg->buf++ = arg->flags[1] ? '+' : ' ';
	arg->flags[1] || arg->flags[3] ? add_char(arg, ' ', arg->width - 1)
				: add_char(arg, ' ', arg->width);
}

void	no_preci(t_arg *arg)
{
	if (!arg->flags[0])
	{
		if (arg->width)
		{
			arg->flags[1] || arg->flags[3] ? add_char(arg, ' ', arg->width - 1)
					: add_char(arg, ' ', arg->width);
			if (arg->flags[1] || arg->flags[3])
				*arg->buf++ = arg->flags[1] ? '+' : ' ';
		}
		else
		{
			if (arg->flags[1] || arg->flags[3])
				*arg->buf++ = arg->flags[1] ? '+' : ' ';
		}
	}
	else
		flag_minus(arg);
}

void	set_uppercase(char **str)
{
	char *tmp;

	tmp = *str;
	while (**str)
	{
		**str = ft_toupper(**str);
		(*str)++;
	}
	*str = tmp;
}
