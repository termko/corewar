/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:38:56 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 04:28:51 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	args_values(t_core *core, t_token *token)
{
	int		i;

	i = 0;
	while (i < token->op.argc)
	{
		if (token->args[i].type == 1)
			direct_value(token, i);
		else if (token->args[i].type == 2)
			register_value(token, i);
		else if (token->args[i].type == 3)
			indirect_value(token, i);
		else if (token->args[i].type == 4)
			direct_label(core, token, i);
		else if (token->args[i].type == 5)
			indirect_label(core, token, i);
		else
			parse_error("Unknown error parsing args", token->str);
		i++;
	}
}

int		paste_args(t_token *token, int margin, void *tmp)
{
	int		i;
	int		j;
	int		magic;
	char	*arr;

	i = 0;
	check_malloc(arr = ft_strnew(4));
	while (i < token->op.argc)
	{
		magic = token->args[i].value;
		j = 0;
		while (j < token->args[i].size)
		{
			arr[3 - j] = magic & 0xff;
			magic = magic >> 0x8;
			j++;
		}
		while (--j >= 0)
			tmp = ft_memcpy(tmp, arr + 3 - j, 1) + 1;
		margin += token->args[i].size;
		i++;
	}
	free(arr);
	return (margin);
}

int		paste_argcode(t_token *token, int margin, void *tmp)
{
	int				i;
	int				magic;
	unsigned char	value;

	i = 0;
	value = 0;
	while (i < token->op.argc)
	{
		magic = (unsigned char)token->args[i].type;
		value |= ((magic >> 1) & 0x1) << (7 - i * 2);
		value |= (magic & 0x1) << (6 - i * 2);
		i++;
	}
	ft_memcpy(tmp, &value, 1);
	return (margin + 1);
}

int		last_parse(t_core *core, t_token *token, int margin)
{
	void	*tmp;

	args_values(core, token);
	tmp = ft_memcpy(core->out + margin, &(token->op.id), 1) + 1;
	margin++;
	if (token->op.argcode)
		margin = paste_argcode(token, margin, tmp++);
	return (paste_args(token, margin, tmp));
}

void	encoder(t_core *core)
{
	t_token	*token;
	int		margin;
	int		fd;

	margin = init_out(core);
	token = core->tokens;
	while (token)
	{
		margin = last_parse(core, token, margin);
		token = token->next;
	}
	if (!(fd = open(core->file, O_CREAT | O_RDWR | O_TRUNC, 0777)))
		error("Error opening output file");
	if (margin != write(fd, core->out, margin))
		error("Wrote wrong number of bytes");
	ft_putstr_fd("Writing output program to ", STDOUT_FILENO);
	ft_putendl_fd(core->file, STDOUT_FILENO);
}
