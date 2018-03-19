/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:18:05 by bcozic            #+#    #+#             */
/*   Updated: 2017/11/13 11:05:57 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	**new_list;
	t_list	*current;

	if (!lst || !f)
		return (0);
	if (!(new_list = (t_list **)malloc(sizeof(t_list *) * ft_lstlen(lst))))
		return (0);
	*new_list = f(lst);
	current = *new_list;
	lst = lst->next;
	while (lst)
	{
		current->next = f(lst);
		lst = lst->next;
		current = current->next;
	}
	return (*new_list);
}
