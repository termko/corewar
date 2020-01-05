/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 18:32:45 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/05 22:36:04 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "../libft/libft.h"
# include "op.h"
# include <stdio.h> // DELETE ME!!!
# define REALLOC_TIME 4096

typedef struct	s_size
{
	int		begin;
	int		end;
}				t_size;

typedef struct	s_label
{
	
}				t_label;

typedef struct	s_parse			// ARRAY OF PARSED OBJECTS FROM EACH STRING
{

}				t_parse;

typedef struct	s_core
{
	char	*buff;
	int		buff_size;
	char	**strings;
	t_parse	**parse;
	char	*name;
	char	*comment;
}				t_core;
#endif
