/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_nb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:08:30 by bcozic            #+#    #+#             */
/*   Updated: 2017/12/09 11:47:04 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf_data.h"

char	*conv_nbr(va_list va, char *f, int *nb)
{
	char	*str;
	int		base;

	base = chr_base(f, va);
	str = 0;
	if (f['d'] || f['D'] || f['i'])
		str = signed_conv(va, f, 10);
	else
		str = unsigned_conv(va, f, base);
	if (f['.'] && nb[1] == 0 && str[0] == '0')
		nb[0]++;
	return (str);
}

int		chr_base(char *f, va_list va)
{
	if (f['o'] || f['O'])
		return (8);
	if (f['x'] || f['X'] || f['p'] || f['P'])
		return (16);
	if (f['b'])
		return (2);
	if (f['B'])
		return (va_arg(va, int));
	return (10);
}

char	*signed_conv(va_list va, char *f, int base)
{
	char	mod;
	char	*str;

	mod = '\0';
	if (f[' '])
		mod = ' ';
	if (f['+'])
		mod = '+';
	if (f['l'] == 2)
		str = ft_llitoa_base_mod(va_arg(va, long long), base, mod);
	else if (f['z'] || f['j'] || f['l'] || f['D'])
		str = ft_llitoa_base_mod((long long)va_arg(va, long), base, mod);
	else if (f['h'] == 1)
		str = ft_llitoa_base_mod((long long)(short)va_arg(va, int), base, mod);
	else if (f['h'] == 2)
		str = ft_llitoa_base_mod((long long)(char)va_arg(va, int), base, mod);
	else
		str = ft_llitoa_base_mod((long long)va_arg(va, int), base, mod);
	return (str);
}

char	*unsigned_conv(va_list va, char *f, int base)
{
	char	*str;

	if (f['l'] == 2 || f['p'] || f['P'])
		str = ft_ullitoa_base_mod(va_arg(va, unsigned long long), base);
	else if (f['z'] || f['j'] || f['l'] || f['O'] || f['U'])
		str = ft_ullitoa_base_mod((unsigned long long)va_arg(va,
					unsigned long), base);
	else if (f['h'] == 1)
		str = ft_llitoa_base_mod((long long)(unsigned short)va_arg(va,
					unsigned int), base, '\0');
	else if (f['h'] == 2)
		str = ft_llitoa_base_mod((long long)(unsigned char)va_arg(va,
					unsigned int), base, '\0');
	else
		str = ft_llitoa_base_mod((long long)va_arg(va,
					unsigned int), base, '\0');
	return (str);
}

void	char_conv(va_list va, char *buff, int *len)
{
	char	cara;

	cara = (char)va_arg(va, int);
	if (cara == '\0')
	{
		*len += 1;
		write(1, &cara, 1);
		return ;
	}
	buff[0] = cara;
}
