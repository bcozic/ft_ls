/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrflags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:08:56 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/22 19:42:19 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_data.h"

int		chr_arg(va_list va, const char *restrict format, int *i, char *buffer)
{
	int		nb[2];
	char	buff_f[256];
	int		len;

	len = 0;
	ft_bzero(buff_f, 256);
	ft_bzero(nb, sizeof(int) * 2);
	*i = save_flags(format, *i, buff_f, nb);
	if (buff_f['*'])
		nb[0] = va_arg(va, int);
	len = send_flag(va, buff_f, buffer, nb);
	return (len);
}

int		save_flags(const char *restrict format, int i, char *buff_f, int *nb)
{
	int			j;
	int			end;

	while (format[++i])
	{
		j = -1;
		end = 0;
		while (VALID_F[++j])
			if (VALID_F[j] == format[i])
				end = add_flag(buff_f, i, j, format);
		i = chr_digit(format, i, nb, &end);
		if (end == 0)
		{
			buff_f[0] = format[i];
			return (i);
		}
		if (end == 2)
			return (i);
	}
	return (i);
}

int		add_flag(char *buff_f, int i, int j, const char *restrict format)
{
	if (!buff_f[(int)format[i]])
		buff_f[(int)format[i]] = 1;
	if ((format[i] == 'l' || format[i] == 'h')
			&& format[i] == format[i + 1])
		buff_f[(int)format[i]] = 2;
	if (format[i] == LIST_CONV[j])
		return (2);
	return (1);
}

int		chr_digit(const char *restrict format, int i, int *nb, int *end)
{
	if (ft_isdigit(format[i]) && format[i] != '0')
	{
		nb[0] = ft_atoi(format + i);
		*end = 1;
		while (ft_isdigit(format[i + 1]))
			i++;
	}
	else if (format[i] == '.')
	{
		if (ft_isdigit(format[i + 1]))
		{
			nb[1] = ft_atoi(format + i + 1);
			*end = 1;
			while (ft_isdigit(format[i + 1]))
				i++;
		}
		else
			nb[1] = 0;
	}
	return (i);
}
