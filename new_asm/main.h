/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 18:32:45 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/28 17:50:17 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "../libft/libft.h"
# include "op.h"
# include <stdio.h> // DELETE ME!!!
# define REALLOC_TIME 4096

typedef struct	s_args
{
	int		size;
	int		type;	// 1 = %3, 2 = r3, 3 = 3, 4 = %:LOOP, 5 = :LOOP
	char	*str;
	int		value;
}				t_args;

typedef struct	s_ops
{
	char		*name;
	int			argc;
	int			first[3];
	int			second[3];
	int			third[3];
	int			id;
	int			cost;
	int			argcode;
	int			tdir;
}				t_ops;

typedef struct	s_token			// PARSED TOKENS (OBJECTS)
{
	t_ops			op;
	t_args			*args;
	int				size;
	int				pos;
	char			*remain;
	struct s_token	*next;
}				t_token;

typedef struct	s_size
{
	int		begin;
	int		last;
	int		end;
}				t_size;

typedef struct	s_label			// LABELS (NAME AND TO)
{
	char			*name;
	t_token			*to;
	struct s_label	*next;
	struct s_label	*prev;
}				t_label;

typedef struct	s_core
{
	char	*buff;
	char	*file;
	int		buff_size;
	char	**strings;
	t_label	*labels;
	t_token	*tokens;
	int		size;
	int		is_label;
	char	*name;
	char	*comment;
	void	*out;
}				t_core;

void			check_malloc(void *addr);
int				ft_isdigital(char *str);
void			check_split(char **split, int count);
void			realloc_char(t_core *core, char *tmp, int cur, int i);
int				ft_isspace(char c);
void			error(char *msg);
void			usage(void);
int				count_strings(t_core *core);
void			read_file(int fd, t_core *core);
t_core			*check_input(t_core *core, int ac, char **av);
void			bufftostr(t_core *core);
char			*get_string(char *loc);
t_size			get_strsize(t_core *core, int prev);
#endif
