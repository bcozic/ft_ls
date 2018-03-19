/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 13:10:51 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/24 07:26:17 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *str, size_t size, size_t new_size)
{
	void	*new_str;

	if (!(new_str = (void *)malloc(new_size)))
	{
		if (str)
			free(str);
		return (0);
	}
	if (str)
	{
		ft_memcpy(new_str, str, size);
		free(str);
	}
	return (new_str);
}
