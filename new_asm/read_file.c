/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:39:47 by ydavis            #+#    #+#             */
/*   Updated: 2020/01/28 17:41:23 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void    read_file(int fd, t_core *core)
{
    int     cur;
    int     i;
    char    *tmp;

    check_malloc(core->buff = ft_strnew(REALLOC_TIME));
    cur = 0;
    while (1)
    {
        check_malloc(tmp = ft_strnew(REALLOC_TIME));
        i = read(fd, tmp, REALLOC_TIME);
        if (i <= 0)
            break ;
        realloc_char(core, tmp, cur, i);
        core->buff_size = cur * REALLOC_TIME + i;
        cur++;
        if (i < REALLOC_TIME)
            break ;
        free(tmp);
    }
    if (tmp[i - 1] != '\n')
        error("No endline at the end of file!");
    free(tmp);
}

t_core  *check_input(t_core *core, int ac, char **av)
{
    int     fd;
    int     len;

    if (ac != 2)
        usage();
    len = ft_strlen(av[1]);
    if (ft_strcmp(av[1] + len - 2, ".s"))
        usage();
    if ((fd = open(av[1], 'r')) < 0)
        error("Error opening file!");
    check_malloc(core->file = ft_strnew(len + 2));
    core->file = ft_strncat(core->file, av[1], len - 1);
    core->file = ft_strcat(core->file, "cor");
    read_file(fd, core);
    close(fd);
    return (core);
}

void    bufftostr(t_core *core)
{
    int     count;
    int     i;
    int     prev;
    t_size  size;

    count = count_strings(core); // DOUBLECHECK THIS PIECE OF SHIT!!!!!1

    check_malloc(core->strings = (char**)malloc(sizeof(char*) * (count + 1)));
    i = 0;
    prev = 0;
    while (i < count)
    {
        size = get_strsize(core, prev);
        prev = size.end;
        check_malloc(core->strings[i] =
                ft_strsub(core->buff, size.begin, size.last - size.begin + 1));
        i++;
    }
    core->strings[i] = NULL;
}

char    *get_string(char *loc)
{
    char    *ret;
    int     i;

    i = 0;
    while (loc[i])
    {
        if (loc[i] == '\"')
            break ;
        i++;
    }
    if (loc[i + 1])
        error("String error");
    check_malloc(ret = ft_strnew(i));
    i = 0;
    while (loc[i])
    {
        if (loc[i] == '\"')
            break ;
        ret[i] = loc[i];
        i++;
    }
    return (ret);
}
