/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:36:40 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 18:19:41 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;

	i = 0;
	if (dst < src)
		while (i < (int)len)
		{
			*((char *)dst + i) = *((const char *)src + i);
			i++;
		}
	else
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			*((char *)dst + i) = *((const char *)src + i);
			i--;
		}
	}
	return (dst);
}
