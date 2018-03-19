/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:13:16 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 20:38:40 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_elem;
	size_t	i;

	if (!(new_elem = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content && content_size)
	{
		if (!(new_elem->content = malloc(content_size)))
			return (0);
		i = 0;
		while (i < content_size)
		{
			*((char *)new_elem->content + i) = *((const char *)content + i);
			i++;
		}
		new_elem->content_size = content_size;
	}
	else
	{
		new_elem->content = NULL;
		new_elem->content_size = 0;
	}
	new_elem->next = NULL;
	return (new_elem);
}
