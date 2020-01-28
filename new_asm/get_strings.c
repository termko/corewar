/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:41:34 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/28 17:56:44 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		check_commentchar(char c, int is_comchar, int is_comment)
{
	if (c == COMMENT_CHAR || c == ALT_COMMENT_CHAR)
		if (!is_comment)
			return (1);
	return (is_comchar);
}

int		check_stringsym(char c, int is_comchar, int empty, int is_comment)
{
	if (c == '\"')
	{
		if (!is_comchar)
		{
			if (empty)
				error("Unexpected string symbol (\")");
			return (is_comment ? 0 : 1);
		}
	}
	return (is_comment);
}

int     count_strings(t_core *core)
{
    int     count;
    int     i;
    int     is_comment;
    int     empty;
    int     is_comchar;

    i = -1;
    count = 0;
    is_comment = 0;
    is_comchar = 0;
    empty = 1;
    while (++i < core->buff_size)
    {
        is_comchar = check_commentchar(core->buff[i], is_comchar, is_comment);
		is_comment = check_stringsym(core->buff[i],
				is_comchar, empty, is_comment);
        if (ft_isspace(core->buff[i]) && empty)
            continue ;
		else if (core->buff[i] == '\n')
        {
            if (!is_comment)
                is_comchar = 0;
            if (!is_comment && !empty)
            {
                empty = 1;
                count++;
            }
        }
		else if (!is_comchar)
            empty = 0;
    }
    if (is_comment)
        error("Error with string symbol (\")");
    return (count);
}

// SEE HOW TO REWORK THIS

/*
int     count_strings(t_core *core)
{
    int     count;
    int     i;
    int     is_comment;
    int     empty;
    int     is_comchar;

    i = 0;
    count = 0;
    is_comment = 0;
    is_comchar = 0;
    empty = 1;

    while (i < core->buff_size)
    {
        if (ft_isspace(core->buff[i]) && empty)
        {
            i++;
            continue ;
        }

        else if (core->buff[i] == COMMENT_CHAR)
        {
            if (!is_comment)
                is_comchar = 1;
        }

        else if (core->buff[i] == '\n')
        {
            if (!is_comment)
                is_comchar = 0;
            if (!is_comment && !empty)
            {
                empty = 1;
                count++;
            }
        }

        else if (core->buff[i] == '\"')
        {
            if (!is_comchar)
            {
                if (empty)
                    error("Unexpected string symbol (\")");
                is_comment = (is_comment ? 0 : 1);
            }
        }

        else if (!is_comchar)
            empty = 0;
        i++;
    }

    if (is_comment)
        error("Error with string symbol (\")");
    return (count);
}
*/
