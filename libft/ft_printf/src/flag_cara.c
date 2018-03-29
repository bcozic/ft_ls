/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_cara.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 18:44:42 by bcozic            #+#    #+#             */
/*   Updated: 2017/12/09 11:47:22 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_data.h"
#include "libft.h"

int		after_ccs(char *buffer, int slen, int *nb, char *f)
{
	char	cara;
	int		len;
	int		blen;

	len = 0;
	cara = ' ';
	blen = (int)ft_strlen(buffer);
	if (!f['-'])
	{
		if (f['0'] && nb[1] <= 0)
			cara = '0';
		while (--nb[0] >= slen && nb[0] >= nb[1])
		{
			buffer[blen++] = cara;
			blen = check(buffer, blen, &len);
		}
	}
	len += write_buff(buffer);
	nb[0] -= slen;
	return (len);
}

int		flag_sl(char *flag, va_list va, int *nb, char *buff)
{
	wchar_t *uni;
	int		len;

	uni = va_arg(va, wchar_t *);
	len = after_ccs(buff, unilen(uni, -1, nb), nb, flag);
	len += write_unicode(uni, nb, 0);
	return (len);
}

int		print_mps(char *buffer, char *str, int *nb, char *f)
{
	int		blen;
	char	cara;

	cara = ' ';
	blen = (int)ft_strlen(buffer);
	if (f['0'] && nb[1] <= 0)
		cara = '0';
	if (nb[0] > 0 && !(f['s']) && !f[0] && (ft_strchr("-+ ", str[0])))
	{
		if (cara == '0')
			blen = aff_sign(buffer, str, nb, cara);
		else if (f['.'] && nb[1] > 0 && str[0] != ' '
				&& nb[1] >= (int)ft_strlen(str))
			nb[0]--;
	}
	return (blen);
}
