/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:22:18 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 02:53:09 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_core	*init_core(void)
{
	t_core *core;

	check_malloc(core = (t_core*)malloc(sizeof(t_core)));
	core->strs = NULL;
	core->buff = NULL;
	core->name = NULL;
	core->comment = NULL;
	core->tokens = NULL;
	core->labels = NULL;
	core->out = NULL;
	core->buff_size = 0;
	core->is_label = 0;
	core->size = 0;
	return (core);
}

int		init_out(t_core *core)
{
	void	*tmp;
	int		size;
	int		margin;
	int		magic;

	size = PROG_NAME_LENGTH + COMMENT_LENGTH + core->size + 16;
	check_malloc(core->out = malloc(size));
	ft_bzero(core->out, size);
	tmp = core->out;
	margin = 0;
	magic = ft_htonl(COREWAR_EXEC_MAGIC);
	tmp = ft_memcpy(tmp, &magic, 4) + 4;
	margin += 4;
	tmp = ft_memcpy(tmp, core->name, ft_strlen(core->name)) +
		PROG_NAME_LENGTH + 4;
	margin += PROG_NAME_LENGTH + 4;
	magic = ft_htonl(core->size);
	tmp = ft_memcpy(tmp, &magic, 4) + 4;
	margin += 4;
	tmp = ft_memcpy(tmp, core->comment, ft_strlen(core->comment)) +
		COMMENT_LENGTH + 4;
	margin += COMMENT_LENGTH + 4;
	return (margin);
}
