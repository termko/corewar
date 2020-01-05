/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 02:49:28 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/23 06:46:34 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	usage(void)
{
	ft_putendl_fd("Usage: ./asm <sourcefile.s>", STDERR_FILENO);
	exit(1);
}

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

void	check_malloc(void *addr)
{
	if (!addr)
	{
		error_msg("Unexpected error with malloc! Exiting...");
		exit(1);
	}
}

t_core	*init_core(char **av)
{
	t_core	*core;
	char	*str;
	int		fd;

	check_malloc(core = (t_core*)malloc(sizeof(t_core)));
	check_malloc(core->sc = (t_scan*)malloc(sizeof(t_scan)));
	check_malloc(core->lex = (t_lexer*)malloc(sizeof(t_lexer)));
	core->name = NULL;
	core->comment = NULL;
	core->lex->coms = NULL;
	core->lex->labels = NULL;
	core->sc->str = NULL;
	core->sc->next = NULL;
	if ((fd = open(av[1], 'r')) < 0)
		error_msg("Cannot open file.");
	// STOPPED HERE, HOW TO ORGANIZE THINGS..?
	// SCANNER -> LEXER -> PARSER..?
	// OR JUST SCANNER -> LEXER..?
	// DONT FORGET TO USE OP.H THOROUGHLY
	return (core);
}

void	check_name(char **av)
{
	int	len;

	len = ft_strlen(av[1]);
	if (ft_strcmp(".s", av[1] + len - 2))
		error_msg("Wrong file extension.");
}

int		main(int ac, char **av)
{
	t_core	*core;

	if (ac < 2)
		usage();
	check_name(av);
	core = init_core(av);
	return (0);
}
