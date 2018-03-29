/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 13:51:27 by bcozic            #+#    #+#             */
/*   Updated: 2017/12/08 16:46:16 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"
#include "ft_printf_data.h"
#include "libft.h"

int		ft_printf(const char *restrict format, ...)
{
	va_list	va;
	int		len;

	if (format == 0)
	{
		write(2, "ERROR : NULL in first printf's parameter\n", 41);
		return (1);
	}
	va_start(va, format);
	len = print_string(va, format);
	va_end(va);
	return (len);
}

int		write_buff(char *buffer)
{
	size_t	len;

	len = ft_strlen(buffer);
	write(1, buffer, len);
	ft_bzero(buffer, 2048);
	return ((int)len);
}

int		print_string(va_list va, const char *restrict format)
{
	static char	buffer[2048];
	int			i;
	int			len;
	int			blen;

	ft_bzero(buffer, 2048);
	i = -1;
	len = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			len += chr_arg(va, format, &i, buffer);
			if (!format[i])
				break ;
		}
		else
		{
			blen = check(buffer, (int)ft_strlen(buffer), &len);
			buffer[blen] = format[i];
		}
	}
	len += write_buff(buffer);
	return (len);
}

int		check(char *buffer, int blen, int *len)
{
	if (blen > 2040)
	{
		*len += write_buff(buffer);
		return (0);
	}
	return (blen);
}

int		aff_sign(char *buffer, char *str, int *nb, char cara)
{
	int		blen;

	blen = (int)ft_strlen(buffer);
	if (str[0] != ' ')
	{
		buffer[blen++] = str[0];
		nb[1]++;
		nb[0]--;
	}
	else if (cara == '0')
	{
		buffer[blen++] = ' ';
		nb[0]--;
	}
	ft_memmove(str, str + 1, ft_strlen(str));
	return (blen);
}
