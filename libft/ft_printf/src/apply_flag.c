/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:08:38 by bcozic            #+#    #+#             */
/*   Updated: 2017/12/08 18:25:14 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_data.h"

int		apply_hash(char *f, char *buffer, int blen)
{
	if (f['x'] || f['X'] || f['o'] || f['O'] || f['p'] || f['P'])
	{
		buffer[blen++] = '0';
		if (f['x'] || f['p'])
			buffer[blen++] = 'x';
		else if (f['X'] || f['P'])
			buffer[blen++] = 'X';
	}
	return (blen);
}

void	cpt_hash_n_up(char *flag, char *str, int *nb)
{
	if (flag['#'] && str[0] != '0')
	{
		if (flag['x'] || flag['X'])
			nb[0] -= 2;
		else if (flag['o'] || flag['O'])
			nb[0]--;
	}
	else if (flag['p'] || flag['P'])
		nb[0] -= 2;
	if (flag['X'] || flag['P'])
		ft_strup(str);
}

int		cara_after(char *buffer, char *str, int *nb, char *f)
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
		if (((f['#'] && str[0] != '0') || f['p'] || f['P']) && cara == '0')
			blen = apply_hash(f, buffer, blen);
		blen = print_mps(buffer, str, nb, f);
		while (--nb[0] >= (int)ft_strlen(str) && nb[0] >= nb[1])
		{
			blen = check(buffer, blen, &len);
			buffer[blen++] = cara;
		}
	}
	if (((f['#'] && str[0] != '0') || f['p'] || f['P']) && cara != '0')
		blen = apply_hash(f, buffer, blen);
	if (f['.'] && nb[1] > 0)
		len += point_flag(buffer, str, nb, f);
	return (len);
}

int		point_flag(char *buffer, char *str, int *nb, char *f)
{
	int		blen;
	int		slen;
	int		len;

	len = 0;
	slen = (int)ft_strlen(str);
	blen = (int)ft_strlen(buffer);
	if (!(f['s']) && (ft_strchr("-+ ", str[0])) && !f[0])
	{
		if (str[0] == ' ')
			slen--;
		blen = aff_sign(buffer, str, nb, ' ');
	}
	if ((f['o'] || f['O']) && f['#'])
		nb[1]--;
	while (--nb[1] >= slen)
	{
		buffer[blen++] = '0';
		blen = check(buffer, blen, &len);
		nb[0]--;
	}
	nb[1] = 1;
	return (len);
}

void	flag_min(char *buffer, int *nb, int blen, int *len)
{
	while (--nb[0] >= 0)
	{
		buffer[blen++] = ' ';
		blen = check(buffer, blen, len);
	}
}
