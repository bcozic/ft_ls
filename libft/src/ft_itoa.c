/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:10:30 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/15 14:11:58 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	w_in_str(char *str, int size, int neg, int n)
{
	str[size] = '\0';
	while (--size >= 0)
	{
		str[size] = (char)((n % 10) * neg) + '0';
		n /= 10;
	}
	if (neg == -1)
		str[0] = '-';
}

char		*ft_itoa(int n)
{
	int		size;
	int		cpy;
	char	*str;
	int		neg;

	cpy = n;
	neg = (n < 0) ? -1 : 1;
	size = ft_nbrlen(n);
	if (!(str = (char *)malloc(sizeof(char) * (size_t)(size + 1))))
		return (0);
	w_in_str(str, size, neg, n);
	return (str);
}
