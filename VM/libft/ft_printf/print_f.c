/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <vellery-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:58:29 by vellery-          #+#    #+#             */
/*   Updated: 2020/01/30 04:16:46 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_nan_inf(double val, int *sign)
{
	unsigned long	l;
	int				expo;
	unsigned int	mantis;

	l = *(unsigned long*)(&val);
	*sign = l >> 63 & 1;
	if (val != val)
		return (!(l >> 63 & 1) ? 1 : 2);
	mantis = ((l << 12) >> 12);
	if ((expo = ((l << 1) >> 53) - 1023) == 1024)
		return (!(l >> 63 & 1) ? 3 : 4);
	return (0);
}

void		set_f(t_arg *arg, va_list va, char **ptr)
{
	char			*needed;
	long double		val;
	int				f;
	int				flag;

	arg->type = *arg->format++;
	val = (arg->length[0] == 'L') ?
			va_arg(va, long double) : va_arg(va, double);
	if ((flag = check_nan_inf(val, &f)))
	{
		if (flag == 1 || flag == 2)
			needed = flag == 1 ? ft_strdup("nan") : ft_strdup("nan");
		if (flag == 3 || flag == 4)
			needed = flag == 3 ? ft_strdup("inf") : ft_strdup("-inf");
	}
	else if (!(needed = ft_ftoa(val, arg->preci, f)))
		return ;
	arg->l = ft_strlen(needed);
	add_mem(arg);
	*ptr = needed;
	arg->flags[4] && arg->preci == 0 ? dotset(needed, &arg->l) : arg->flags[4];
	arg->preci = arg->preci <= arg->l ? -1 : arg->preci;
	arg->flags[2] = arg->flags[0] ? 0 : arg->flags[2];
	arg->flags[0] ? save_to_buf_minus(arg, needed, arg->l, f) :
			save_to_buf_no_minus(arg, needed, arg->l, f);
}

void		dotset(char *needed, int *len)
{
	char *tmp;

	(*len)++;
	tmp = ft_strdup(needed);
	ft_strdel(&needed);
	needed = ft_strjoin(tmp, ".");
	ft_strdel(&tmp);
}
