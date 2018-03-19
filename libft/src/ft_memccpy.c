/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:06:03 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 18:22:09 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)dst + i) = *((const unsigned char *)src + i);
		if ((unsigned char)c == *((unsigned char *)dst + i))
		{
			return (((unsigned char *)dst + i + 1));
		}
		i++;
	}
	return (NULL);
}
