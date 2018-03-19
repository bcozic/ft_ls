/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 12:32:45 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 20:27:24 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = -1;
	while (s1[++i] || s2[i])
		if (s1[i] != s2[i])
			return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
	return (0);
}
