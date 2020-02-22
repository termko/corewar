/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 22:15:59 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/06 16:54:40 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;
	void	*cont;

	list = (t_list*)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	if (!content)
	{
		cont = NULL;
		content_size = 0;
	}
	else
	{
		cont = (void*)malloc(sizeof(void) * content_size);
		if (!cont)
		{
			free(list);
			return (NULL);
		}
		cont = ft_memcpy(cont, content, content_size);
	}
	list->content = cont;
	list->content_size = content_size;
	list->next = NULL;
	return (list);
}
