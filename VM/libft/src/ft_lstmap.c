/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:04:11 by vellery-          #+#    #+#             */
/*   Updated: 2019/01/26 15:58:58 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tree;
	t_list *head;

	if (!lst || !f)
		return (NULL);
	tree = ft_lstnew(lst->content, lst->content_size);
	if (!tree)
		return (NULL);
	tree = f(lst);
	head = tree;
	while (lst->next)
	{
		tree->next = f(lst->next);
		tree = tree->next;
		lst = lst->next;
	}
	tree = NULL;
	return (head);
}
