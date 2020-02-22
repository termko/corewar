/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:28:34 by vellery-          #+#    #+#             */
/*   Updated: 2019/06/28 19:28:36 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	refresh(t_arg *arg)
{
	arg->flags[0] = 0;
	arg->flags[1] = 0;
	arg->flags[2] = 0;
	arg->flags[3] = 0;
	arg->flags[4] = 0;
	arg->width = 0;
	arg->preci = -1;
	arg->length[0] = '\0';
	arg->length[1] = '\0';
	arg->type = '\0';
}

void	depend_on_type(t_arg *arg, char *str)
{
	if (arg->type == 'x' && *str != '0')
		printf_concat(arg, "0x", 2);
	else if (arg->type == 'X' && *str != '0')
		printf_concat(arg, "0X", 2);
	else if ((arg->type == 'o' || arg->type == 'O') && *str != '0')
		printf_concat(arg, "0", 1);
	else if (arg->type == 'b' && *str != '0')
		printf_concat(arg, "0b", 2);
	else if (arg->type == 'B' && *str != '0')
		printf_concat(arg, "0B", 2);
}

int		capit(char type)
{
	if (type >= 65 && type <= 90)
		return (1);
	return (0);
}

int		lower(char type)
{
	if (type >= 97 && type <= 122)
		return (1);
	return (0);
}

int		set_spaces(t_arg *arg, char *str)
{
	if ((arg->type == 'b' || arg->type == 'B' ||
			arg->type == 'x' || arg->type == 'X') && *str != '0')
		return (2);
	else if ((arg->type == 'o' || arg->type == 'O') && *str != '0')
		return (1);
	return (0);
}
