/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 17:46:09 by vellery-          #+#    #+#             */
/*   Updated: 2019/06/28 17:46:12 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_char(t_arg *arg, va_list va)
{
	char	needed;

	arg->type = *arg->format++;
	add_mem(arg);
	needed = (char)va_arg(va, int);
	if (!arg->flags[0])
		arg->flags[2] ? add_char(arg, '0', arg->width - 1)
						: add_char(arg, ' ', arg->width - 1);
	*arg->buf++ = needed;
	if (needed == (char)0 && !arg->width)
		arg->char_len++;
	if (arg->flags[0])
		add_char(arg, ' ', arg->width - 1);
}

void	str_minus_flag(t_arg *arg, char *str, int len)
{
	if (arg->preci == -1)
	{
		printf_concat(arg, str, len);
		add_char(arg, ' ', arg->width - len);
	}
	else
	{
		len ? printf_concat(arg, str, arg->preci) : len;
		add_char(arg, ' ', arg->width - arg->preci);
	}
}

void	str_no_minus_flag(t_arg *arg, char *str, int len)
{
	if (arg->preci == -1)
	{
		add_char(arg, ' ', arg->width - len);
		printf_concat(arg, str, len);
	}
	else
	{
		add_char(arg, ' ', arg->width - arg->preci);
		len ? printf_concat(arg, str, arg->preci) : len;
	}
}

void	set_string(t_arg *arg, va_list va)
{
	char	*needed;

	arg->type = *arg->format++;
	needed = va_arg(va, char *);
	if (needed == NULL)
		needed = "(null)";
	else if (*needed == '\0' && !arg->width)
		return (add_mem_empty(arg));
	arg->l = ft_strlen(needed);
	add_mem(arg);
	arg->preci = arg->preci >= arg->l ? -1 : arg->preci;
	if (arg->flags[0])
		str_minus_flag(arg, needed, arg->l);
	else
		str_no_minus_flag(arg, needed, arg->l);
}
