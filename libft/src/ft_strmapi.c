/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:24:35 by bcozic            #+#    #+#             */
/*   Updated: 2017/11/12 17:38:13 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*rt_str;

	if (!s | !f)
		return (0);
	if (!(rt_str = (char *)malloc(ft_strlen(s) + 1)))
		return (0);
	i = 0;
	while (s[i])
	{
		rt_str[i] = f(i, s[i]);
		i++;
	}
	rt_str[i] = '\0';
	return (rt_str);
}
