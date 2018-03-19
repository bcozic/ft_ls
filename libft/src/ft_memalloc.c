/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:38:24 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 20:30:23 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*tab;
	size_t	i;

	if (!(tab = malloc(size)))
		return (0);
	i = 0;
	while (i < size)
	{
		*((char *)tab + i) = 0;
		i++;
	}
	return (tab);
}
