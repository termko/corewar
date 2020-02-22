/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:27:07 by vellery-          #+#    #+#             */
/*   Updated: 2019/08/20 18:27:10 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_color(t_arg *arg)
{
	if (ft_strstr(arg->format, "red"))
		write(1, RED, 6);
	else if (ft_strstr(arg->format, "green"))
		write(1, GREEN, 6);
	else if (ft_strstr(arg->format, "blue"))
		write(1, BLUE, 6);
	else if (ft_strstr(arg->format, "magenta"))
		write(1, MAGENTA, 6);
	else if (ft_strstr(arg->format, "cyan"))
		write(1, CYAN, 6);
	else if (ft_strstr(arg->format, "yel"))
		write(1, YELLOW, 6);
	else
		return ;
	while (*arg->format++ != '}')
		;
	arg->color = 1;
}
