/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa_base_mod.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 02:22:45 by bcozic            #+#    #+#             */
/*   Updated: 2017/12/09 11:47:43 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf_data.h"

static void	w_in_str(char *str, long long n, int base, int size)
{
	int		neg;

	neg = 1;
	if (n < 0)
		neg = -1;
	str[size] = '\0';
	while (--size >= 0)
	{
		if (base <= 10)
			str[size] = (char)((n % base) * neg + '0');
		else
		{
			if ((n % base) * neg < 10)
				str[size] = (char)((n % base) * neg + '0');
			else
				str[size] = (char)((n % base) * neg + 'a' - 10);
		}
		n /= base;
	}
	if (neg == -1 && base == 10)
		str[0] = '-';
}

static char	*len_nb(long long n, int base, int *size)
{
	char	*str;

	if (n < 0 && base == 10)
		*size = *size + 1;
	while (n >= base || n <= -base)
	{
		*size = *size + 1;
		n /= base;
	}
	if (!(str = (char *)malloc(sizeof(char) * (unsigned long)(*size + 1))))
		return (0);
	return (str);
}

char		*ft_llitoa_base_mod(long long n, int base, char mode)
{
	char	*str;
	int		size;

	size = 1;
	if (mode != '\0' && n >= 0)
		size = 2;
	if (!(str = len_nb(n, base, &size)))
		return (0);
	w_in_str(str, n, base, size);
	if (mode != '\0' && str[0] != '-')
		str[0] = mode;
	return (str);
}
