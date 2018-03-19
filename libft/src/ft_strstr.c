/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:12:35 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 20:26:19 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *haystack, const char *needle)
{
	int		i;
	int		j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = -1;
	while (haystack[++i])
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			j++;
			if (needle[j] == 0)
				return ((char *)haystack + i);
		}
	}
	return (0);
}
