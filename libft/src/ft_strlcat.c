/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:33:47 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 20:24:10 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(dst) > size)
		return (ft_strlen(src) + size);
	i = ft_strlen(dst);
	j = 0;
	while (i + j < size - 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i + j < size)
		dst[i + j] = '\0';
	return (ft_strlen(src) + i);
}
