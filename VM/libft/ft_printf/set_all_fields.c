/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_all_fields.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <vellery-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:16:24 by vellery-          #+#    #+#             */
/*   Updated: 2020/01/30 04:19:06 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		set_param(int *param, char *format)
{
	int	i;

	i = 0;
	*param = ft_atoi(format);
	while (ft_isdigit(format[i]))
		i++;
	return (i);
}

void	set_precision(t_arg *arg, va_list va)
{
	arg->format++;
	if (*arg->format == '*')
	{
		arg->preci = va_arg(va, int);
		if (arg->preci < 0)
			arg->preci = -1;
		arg->format++;
		return ;
	}
	arg->format += set_param(&arg->preci, arg->format);
}

void	set_width(t_arg *arg, va_list va)
{
	arg->width = va_arg(va, int);
	if (arg->width < 0)
	{
		arg->flags[0] = 1;
		arg->width = -arg->width;
	}
}

void	set_fl_width_prec(t_arg *arg, va_list va)
{
	char	*tmp;
	char	*str;

	tmp = arg->format;
	str = "-+0 #*.0123456789";
	while (ft_strchr(str, *arg->format))
	{
		*arg->format == '-' ? arg->flags[0] = 1 : 0;
		*arg->format == '+' ? arg->flags[1] = 1 : 0;
		*arg->format == '#' ? arg->flags[4] = 1 : 0;
		*arg->format == ' ' ? arg->flags[3] = 1 : 0;
		*arg->format == '*' ? set_width(arg, va) : *arg->format;
		*arg->format == '0' ? arg->flags[2] = 1 : 0;
		if (*arg->format == '.')
			set_precision(arg, va);
		else if (ft_isdigit(*arg->format) && arg->preci == -1)
			arg->format += set_param(&arg->width, arg->format);
		else
			arg->format++;
	}
}

void	set_all_fields(va_list va, t_arg *arg)
{
	char	*ptr;
	int		len;

	ptr = NULL;
	arg->format++;
	if (*arg->format == '\0')
		return ;
	refresh(arg);
	set_fl_width_prec(arg, va);
	set_length(arg);
	set_type(arg, va, &ptr);
	if (ptr)
		free(ptr);
	len = ft_strlen(arg->ptr_buf_save);
	arg->buf_len += arg->width > len ? arg->width : len;
}
