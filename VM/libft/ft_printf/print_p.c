/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:00:42 by vellery-          #+#    #+#             */
/*   Updated: 2019/06/28 19:00:43 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_no_minus(t_arg *arg, char *str, int len)
{
	if (arg->preci == -1)
	{
		if (arg->flags[2])
		{
			printf_concat(arg, "0x", 2);
			add_char(arg, '0', arg->width - len - 2);
		}
		else
		{
			add_char(arg, ' ', arg->width - len - 2);
			printf_concat(arg, "0x", 2);
		}
		printf_concat(arg, str, len);
	}
	else if (arg->preci == 0)
		printf_concat(arg, "0x", 2);
	else
	{
		add_char(arg, ' ', arg->width - arg->preci - 2);
		printf_concat(arg, "0x", 2);
		add_char(arg, '0', arg->preci - len);
		printf_concat(arg, str, len);
	}
}

void	p_minus(t_arg *arg, char *str, int len)
{
	printf_concat(arg, "0x", 2);
	if (arg->preci == -1)
	{
		printf_concat(arg, str, len);
		add_char(arg, ' ', arg->width - len - 2);
	}
	else if (arg->preci == 0)
		printf_concat(arg, "0x", 2);
	else
	{
		add_char(arg, '0', arg->preci - 2);
		printf_concat(arg, str, len);
		add_char(arg, ' ', arg->width - arg->preci - len);
	}
}

void	set_ptr(t_arg *arg, va_list va, char **ptr)
{
	char	*needed;
	int		f;

	arg->type = *arg->format++;
	arg->length[0] = 'l';
	needed = get_in_ustring(arg, va, ptr);
	arg->l = ft_strlen(needed);
	add_mem(arg);
	arg->width = arg->width <= arg->l ? 0 : arg->width;
	if (*needed != '0')
		arg->preci = arg->preci <= arg->l ? -1 : arg->preci;
	f = (*needed == '0') ? 1 : 0;
	if (!arg->flags[0])
		p_no_minus(arg, needed, arg->l);
	else
		p_minus(arg, needed, arg->l);
}

void	invalid_type(t_arg *arg)
{
	arg->l = ft_strlen(arg->format);
	add_mem(arg);
	if (arg->flags[0])
	{
		while (*arg->format)
			*arg->buf++ = *arg->format++;
		add_char(arg, ' ', arg->width - arg->l);
	}
	else
	{
		arg->flags[2] ? add_char(arg, '0', arg->width - arg->l) :
				add_char(arg, ' ', arg->width - arg->l);
		while (*arg->format)
			*arg->buf++ = *arg->format++;
	}
}
