/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:35:58 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 20:34:36 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		size_str(char const *s)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	while (s[++i + k])
	{
		j = 0;
		while (s[i + j + k] == ' ' || s[i + j + k] == '\n'
				|| s[i + j + k] == '\t')
			j++;
		if (i != 0 && s[i + j + k])
			i += j;
		else
			k += j;
		if (!s[i + k])
			break ;
	}
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (0);
	i = size_str(s);
	if (!(str = malloc((size_t)i + 1)))
		return (0);
	j = 0;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j++;
	str[i] = '\0';
	k = -1;
	while (++k < i)
		str[k] = s[j + k];
	return (str);
}
