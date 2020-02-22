/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 22:34:27 by vellery-          #+#    #+#             */
/*   Updated: 2020/01/05 17:38:01 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_get(t_list **file, int fd)
{
	t_list		*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!tmp)
		tmp = ft_lstnew("", fd);
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}

char	*ft_get_next(char **line, t_list *point)
{
	size_t			i;
	char			*del;

	if (ft_strchr((char *)point->content, '\n'))
	{
		*line = ft_strsub((char *)point->content, 0,\
				ft_strchr((char *)point->content, '\n')\
					- (char *)point->content);
		i = ft_strchr((char *)point->content, '\n') - (char *)point->content;
		del = point->content;
		if (i < ft_strlen((char *)point->content))
			point->content = ft_strdup(point->content + i + 1);
		free(del);
	}
	else
	{
		i = ft_strlen(point->content);
		del = point->content;
		*line = ft_strncpy(ft_strnew(i), (char *)point->content, i);
		point->content = ft_strdup(point->content + i);
		free(del);
	}
	return (*line);
}

int		get_next_line(const int fd, char **line)
{
	char			*buf;
	int				i;
	static t_list	*file;
	t_list			*point;
	char			*del;

	if (!(buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	if (fd < 0 || BUFF_SIZE < 0 || read(fd, buf, 0))
		return (-1);
	point = ft_get(&file, fd);
	while ((i = read(fd, buf, BUFF_SIZE)))
	{
		buf[i] = '\0';
		del = point->content;
		point->content = ft_strjoin((char *)point->content, buf);
		free(del);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (i < BUFF_SIZE && !ft_strlen((char *)point->content))
		return (0);
	*line = ft_get_next(line, point);
	return (1);
}
