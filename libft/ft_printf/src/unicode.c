/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:40:09 by bcozic            #+#    #+#             */
/*   Updated: 2017/12/12 21:16:07 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf_data.h"

int		uni_n_cara(char *flag, va_list va, int *nb, char *buff)
{
	int		len;
	wchar_t	cara;

	if (flag['S'] || flag['s'])
		len = flag_sl(flag, va, nb, buff);
	else
	{
		if (flag['C'] || (flag['c'] && flag['l']))
		{
			cara = va_arg(va, wchar_t);
			len = after_ccs(buff, unilen(&cara, 1, nb), nb, flag);
			char_unicode(cara, &len);
		}
		else
		{
			len = after_ccs(buff, 1, nb, flag);
			char_conv(va, buff, &len);
		}
	}
	if (flag['-'])
		flag_min(buff, nb, (int)ft_strlen(buff), &len);
	return (len);
}

void	char_unicode(wchar_t cara, int *len)
{
	unsigned char	str[5];
	int				i;

	cara = convert_uni(cara);
	i = -1;
	while ((str[++i] = (unsigned char)(cara >> 24)))
		cara = cara << 8;
	if (i == 0)
		i++;
	write(1, str, (size_t)i);
	*len += i;
}

int		write_unicode(wchar_t *uni, int *nb, int len)
{
	int				i;
	int				ulen;
	wchar_t			cara;
	unsigned char	str[5];

	if (!(uni))
	{
		len = (nb[1] >= 0 && nb[1] < 6) ? nb[1] : 6;
		write(1, "(null)", (size_t)len);
		return (len);
	}
	i = -1;
	while (uni[++i])
	{
		ulen = -1;
		cara = convert_uni(uni[i]);
		while ((str[++ulen] = (unsigned char)(cara >> 24)))
			cara = cara << 8;
		if (len + ulen > nb[1] && nb[1] >= 0)
			return (len);
		write(1, str, (size_t)ulen);
		len += ulen;
	}
	return (len);
}

wchar_t	convert_uni(wchar_t cara)
{
	wchar_t mask[4];

	mask[0] = (0x3F & cara);
	mask[1] = (0xFC0 & cara) << 2;
	mask[2] = (0x3F000 & cara) << 4;
	mask[3] = (0xFC0000 & cara) << 6;
	if (cara == (cara & 0x00FF))
		cara = cara << 24;
	else if (cara == (cara & 0x07FF))
		cara = (mask[0] | mask[1] | 0xC080) << 16;
	else if (cara == (cara & 0xFFFF))
		cara = (mask[0] | mask[1] | (mask[2] & 0xFFFFF) | 0xE08080) << 8;
	else
		cara = (mask[0] | mask[1] | mask[2] | mask[3] | (wchar_t)0xF0808080);
	return (cara);
}

int		unilen(wchar_t *uni, int mod, int *nb)
{
	int		len;
	int		i;
	int		ulen;

	i = -1;
	len = 0;
	if (!uni)
		return ((nb[1] < 6 && nb[1] > 0) ? nb[1] : 6);
	while (uni[++i] && mod-- != 0)
	{
		if (uni[i] == (uni[i] & 0x007F))
			ulen = 1;
		else if (uni[i] == (uni[i] & 0x07FF))
			ulen = 2;
		else if (uni[i] == (uni[i] & 0xFFFF))
			ulen = 3;
		else
			ulen = 4;
		if (ulen + len > nb[1] && mod < 0 && nb[1] >= 0)
			break ;
		len += ulen;
	}
	if (nb[1] >= 0)
		nb[1] = len;
	return (len);
}
