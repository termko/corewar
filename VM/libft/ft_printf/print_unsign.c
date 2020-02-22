/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:01:47 by vellery-          #+#    #+#             */
/*   Updated: 2019/06/28 19:01:48 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		u_preci(t_arg *arg, char *str, int len, int flag)
{
	if (flag == 10)
	{
		add_char(arg, '0', arg->preci - len);
		printf_concat(arg, str, -1);
		arg->flags[1] || arg->flags[3] ? add_char(arg, ' ', arg->width -
			arg->preci - 1) : add_char(arg, ' ', arg->width - arg->preci);
	}
	else if (flag == 11)
	{
		arg->flags[1] || arg->flags[3] ?
			add_char(arg, ' ', arg->width - arg->preci - 1) :
				add_char(arg, ' ', arg->width - arg->preci);
		if ((arg->flags[3] || arg->flags[1]))
			arg->flags[3] ? add_char(arg, ' ', 1) : add_char(arg, '+', 1);
		add_char(arg, '0', arg->preci - len);
	}
}

void		usave_to_buf_minus(t_arg *arg, char *str, int len)
{
	if (arg->flags[3] || arg->flags[1])
		arg->flags[3] ? add_char(arg, ' ', 1) : add_char(arg, '+', 1);
	if (arg->preci == -1)
	{
		printf_concat(arg, str, len);
		if (arg->flags[2])
			add_char(arg, '0', arg->width - (len += arg->flags[1]
						|| arg->flags[3] ? 1 : 0));
		else if (!arg->flags[2] && arg->flags[4])
			add_some_chars(arg, str, len);
		else
			add_char(arg, ' ', arg->width - (len += arg->flags[3]
						|| arg->flags[1] ? 1 : 0));
	}
	else
		u_preci(arg, str, len, 10);
}

void		usave_to_buf_no_minus(t_arg *arg, char *str, int len)
{
	if (arg->preci <= 0)
	{
		if ((arg->flags[3] || arg->flags[1]) && arg->flags[2])
			arg->flags[3] ? add_char(arg, ' ', 1) : add_char(arg, '+', 1);
		if (arg->flags[2])
			add_char(arg, '0', arg->width - (len += arg->flags[3]
					|| arg->flags[1] ? 1 : 0));
		else if (!arg->flags[2] && arg->flags[4])
		{
			add_char(arg, ' ', arg->width - len - 1);
			printf_concat(arg, "0", 1);
		}
		else
			add_char(arg, ' ', arg->width - (len += arg->flags[3]
					|| arg->flags[1] ? 1 : 0));
		if ((arg->flags[3] || arg->flags[1]) && !arg->flags[2])
			arg->flags[3] ? add_char(arg, ' ', 1) : add_char(arg, '+', 1);
	}
	else
		u_preci(arg, str, len, 11);
	printf_concat(arg, str, -1);
}

char		*get_in_ustring(t_arg *arg, va_list va, char **ptr)
{
	uintmax_t	val;
	char		*str;

	val = va_arg(va, uintmax_t);
	if (arg->length[0] == 'h' && arg->type != 'O')
		val = arg->length[1] && arg->length[1] == 'h' ?
				(unsigned char)val : (short unsigned int)val;
	if (arg->length[0] == 'l' && arg->type != 'O')
		val = arg->length[1] && arg->length[1] == 'l' ?
				(unsigned long int)val : (long unsigned int)val;
	else if ((arg->length[0] == 'j' || arg->length[0] == 'z'))
		val = arg->length[0] == 'j' ? val : (size_t)val;
	else if (arg->length[0] == 't' && arg->type != 'O')
		val = (ptrdiff_t)val;
	else if (arg->type != 'O')
		val = (unsigned int)val;
	if (arg->type == 'u' || arg->type == 'U' ||
					arg->type == 'd' || arg->type == 'D')
		str = ft_uintmaxtoa(val, 10);
	arg->type == 'o' || arg->type == 'O' ? str = ft_uintmaxtoa(val, 8) : NULL;
	arg->type == 'x' || arg->type == 'X' || arg->type == 'p' ?
				str = ft_uintmaxtoa(val, 16) : NULL;
	arg->type == 'b' || arg->type == 'B' ? str = ft_uintmaxtoa(val, 2) : NULL;
	*ptr = str;
	return (str);
}

void		set_unsigned(t_arg *arg, va_list va, char **ptr)
{
	char	*needed;

	arg->type = *arg->format++;
	if (*(arg->format - 1) == 'U')
	{
		arg->length[0] = 'l';
		arg->length[1] = '\0';
	}
	if (arg->type == 'u' || arg->type == 'U')
	{
		arg->flags[1] = 0;
		arg->flags[3] = 0;
	}
	needed = get_in_ustring(arg, va, ptr);
	arg->l = ft_strlen(needed);
	add_mem(arg);
	arg->flags[2] = arg->flags[2] && arg->flags[0] ? 0 : arg->flags[2];
	arg->flags[2] = arg->preci >= 0 && arg->flags[2] ? 0 : arg->flags[2];
	arg->preci = arg->preci > 0 && arg->preci < arg->l ? -1 : arg->preci;
	if (arg->preci == 0 && *needed == '0')
		return (no_preci(arg));
	arg->flags[0] ? usave_to_buf_minus(arg, needed, arg->l) :
				usave_to_buf_no_minus(arg, needed, arg->l);
}
