/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 11:19:44 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/30 09:59:02 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	w_in_split(char **split, char const *s, char c, int w)
{
	int		i;
	int		j;
	size_t	size_w;

	i = -1;
	while (s[++i])
	{
		size_w = 1;
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) || (w == -1 && s[i] != c))
		{
			if (s[i] != c)
				i--;
			j = i;
			while (s[++j] && s[j] != c)
				size_w++;
			if (!(split[++w] = (char *)malloc(sizeof(char) * size_w)))
				return ;
			size_w = 0;
			while (++i < j)
				split[w][size_w++] = s[i];
			split[w][size_w] = '\0';
			i--;
		}
	}
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**split;
	int		w;

	if (!s)
		return (0);
	i = -1;
	w = 1;
	while (s[++i])
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) || (w == 1 && s[i] != c))
			w++;
	if (!(split = (char **)malloc(sizeof(char *) * (size_t)w)))
		return (0);
	split[w - 1] = 0;
	w_in_split(split, s, c, -1);
	return (split);
}
