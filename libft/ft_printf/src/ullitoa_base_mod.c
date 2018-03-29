/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa_base_mod.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 02:22:45 by bcozic            #+#    #+#             */
/*   Updated: 2017/12/09 11:47:52 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf_data.h"

static void	w_in_str(char *str, unsigned long long n, int base, int size)
{
	str[size] = '\0';
	while (--size >= 0)
	{
		if (base <= 10)
			str[size] = (char)((n % (unsigned int)base) + '0');
		else
		{
			if ((n % (unsigned int)base) < 10)
				str[size] = (char)((n % (unsigned int)base) + '0');
			else
				str[size] = (char)((n % (unsigned int)base) + 'a' - 10);
		}
		n /= (unsigned int)base;
	}
}

static char	*len_nb(unsigned long long n, int base, int *size)
{
	char	*str;

	while (n >= (unsigned long long)base)
	{
		*size = *size + 1;
		n /= (unsigned int)base;
	}
	if (!(str = (char *)malloc(sizeof(char) * (unsigned long)(*size + 1))))
		return (0);
	return (str);
}

char		*ft_ullitoa_base_mod(unsigned long long n, int base)
{
	char	*str;
	int		size;

	size = 1;
	if (!(str = len_nb(n, base, &size)))
		return (0);
	w_in_str(str, n, base, size);
	return (str);
}
