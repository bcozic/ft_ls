/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:10:30 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/09 20:36:51 by bcozic           ###   ########.fr       */
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
	size = 1;
	neg = 1;
	if (n < 0)
	{
		size++;
		neg = -1;
	}
	while (cpy >= 10 || cpy <= -10)
	{
		size++;
		cpy /= 10;
	}
	if (!(str = (char *)malloc(sizeof(char) * (size_t)(size + 1))))
		return (0);
	w_in_str(str, size, neg, n);
	return (str);
}
