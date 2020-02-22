/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 17:46:45 by vellery-          #+#    #+#             */
/*   Updated: 2019/06/28 17:46:46 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		save_to_buf_minus(t_arg *arg, char *str, int len, int f)
{
	if (!f && (arg->flags[1] || arg->flags[3]))
		*arg->buf++ = arg->flags[1] ? '+' : ' ';
	if (arg->preci == -1)
	{
		len ? printf_concat(arg, str, -1) : len;
		(arg->flags[1] || arg->flags[3]) && !f ?
				add_char(arg, ' ', arg->width - len - 1) :
						add_char(arg, ' ', arg->width - len);
	}
	else
	{
		f ? len-- : len;
		if (f)
			*arg->buf++ = *str++;
		add_char(arg, '0', arg->preci - len);
		len ? printf_concat(arg, str, -1) : len;
		f || arg->flags[1] || arg->flags[3] ?
				add_char(arg, ' ', arg->width - arg->preci - 1) :
						add_char(arg, ' ', arg->width - arg->preci);
	}
}

static void	set_sign(t_arg *arg, char **needed, int f, int preci)
{
	if (f && preci > 0)
		*arg->buf++ = *(*needed)++;
	else if (!f && (arg->flags[1] || arg->flags[3]) && preci > 0)
		*arg->buf++ = arg->flags[1] ? '+' : ' ';
	else if (preci < 0 && !f && arg->flags[2] &&
			(arg->flags[3] || arg->flags[1]))
		*arg->buf++ = arg->flags[1] ? '+' : ' ';
}

void		save_to_buf_no_minus(t_arg *arg, char *str, int len, int f)
{
	if (arg->preci > 0)
	{
		f || arg->flags[1] || arg->flags[3] ?
			add_char(arg, ' ', arg->width - arg->preci - 1) :
				add_char(arg, ' ', arg->width - arg->preci);
		len -= f ? 1 : 0;
		set_sign(arg, &str, f, arg->preci);
		add_char(arg, '0', arg->preci - len);
	}
	else
	{
		set_sign(arg, &str, f, arg->preci);
		if (f && arg->flags[2])
			*arg->buf++ = *str++;
		if (arg->flags[2])
			(arg->flags[1] || arg->flags[3]) && !f ?
					add_char(arg, '0', arg->width - len - 1) :
								add_char(arg, '0', arg->width - len);
		else
			(arg->flags[1] || arg->flags[3]) && !f ? add_char(arg, ' ',
				arg->width - len - 1) : add_char(arg, ' ', arg->width - len);
		if (!f && !arg->flags[2] && (arg->flags[3] || arg->flags[1]))
			*arg->buf++ = arg->flags[1] ? '+' : ' ';
	}
	printf_concat(arg, str, -1);
}

char		*get_in_string(t_arg *arg, va_list va, char **ptr)
{
	intmax_t	val;
	char		*str;

	val = va_arg(va, intmax_t);
	if (arg->length[0] == 'h')
		val = arg->length[1] && arg->length[1] == 'h' ?
				(char)val : (short int)val;
	else if (arg->length[0] == 'l')
		val = arg->length[1] && arg->length[1] == 'l' ?
				(long long int)val : (long int)val;
	else if (arg->length[0] == 'j' || arg->length[0] == 'z')
		val = arg->length[0] ? val : (size_t)val;
	else
		val = (int)val;
	str = ft_intmaxtoa(val, 10);
	*ptr = str;
	return (str);
}

void		set_d(t_arg *arg, va_list va, char **ptr)
{
	char	*needed;
	int		f;

	if (*arg->format == 'D')
	{
		arg->length[0] = 'l';
		arg->length[1] = '\0';
	}
	arg->type = *arg->format++;
	needed = get_in_string(arg, va, ptr);
	arg->l = ft_strlen(needed);
	add_mem(arg);
	if ((arg->flags[0] && arg->flags[2]) || (arg->flags[2] && arg->preci >= 0))
		arg->flags[2] = 0;
	f = *needed == '-' ? 1 : 0;
	if (arg->preci > 0 && ((!f && arg->preci < arg->l) ||
			(f && arg->preci < arg->l - 1)))
		arg->preci = -1;
	if (arg->preci == 0 && *needed == '0')
	{
		no_preci(arg);
		return ;
	}
	arg->flags[0] ? save_to_buf_minus(arg, needed, arg->l, f) :
					save_to_buf_no_minus(arg, needed, arg->l, f);
}
