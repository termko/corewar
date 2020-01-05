/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 02:51:41 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/23 06:56:31 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "../libft/libft.h"
# include <stdio.h> // DELETE ME

typedef struct	s_arg
{
	int				id;
	int				size;
	int				value;
	struct s_arg	*next;
}				t_arg;

typedef struct	s_com
{
	int				id;
	t_arg			*args;
	int				size;
	int				mem;
	struct s_com	*next;
}				t_com;

typedef struct	s_label
{
	char			*name;
	int				to;
}				t_label;

typedef struct	s_scan
{
	char			*str;
	struct s_scan	*next;
}				t_scan;

typedef struct	s_lexer
{
	t_com			*coms;
	t_label			*labels;
}				t_lexer;

typedef struct	s_core
{
	t_scan			*sc;
	t_lexer			*lex;
	char			*name;
	char			*comment;
	void			*result;
}				t_core;

void			check_malloc(void *addr);
char			*realloc_str(char **buff, int i);
int				string_check(char **buff, char c);
char			*read_line(int fd);
#endif
