/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 02:03:27 by bcozic            #+#    #+#             */
/*   Updated: 2017/12/09 11:44:43 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf_data.h"

int		send_flag(va_list va, char *flag, char *buffer, int *nb)
{
	char	*str;
	int		len;

	len = 0;
	str = 0;
	if (!flag['.'])
		nb[1] = -1;
	if (flag['c'] || flag['C'] || flag['S'] || (flag['s'] && flag['l']))
		len += uni_n_cara(flag, va, nb, buffer);
	else
		str = conv_arg(va, flag, nb);
	if (str)
	{
		cpt_hash_n_up(flag, str, nb);
		if (flag['.'] && nb[1] < (int)ft_strlen(str) && flag['s'])
			str[nb[1]] = '\0';
		if (flag['s'] || flag['%'])
			nb[1] = -1;
		len += add_string(buffer, str, nb, flag);
		free(str);
	}
	return (len);
}

char	*conv_arg(va_list va, char *f, int *nb)
{
	char	*str;

	str = 0;
	if (f['p'] || f['P'] || f['d'] || f['D'] || f['i'] || f['o'] || f['O']
			|| f['u'] || f['U'] || f['x'] || f['X'] || f['b'] || f['B'])
		str = conv_nbr(va, f, nb);
	else if (f['s'])
	{
		if ((str = va_arg(va, char *)))
			str = ft_strdup(str);
		else
			str = ft_strdup("(null)");
	}
	else if (f['%'])
		str = ft_strdup("%");
	else if (f[0])
	{
		if (!(str = malloc(sizeof(char) * 2)))
			return (0);
		str[0] = f[0];
		str[1] = '\0';
	}
	return (str);
}

int		add_string(char *buffer, char *str, int *nb, char *f)
{
	int		i;
	char	cara;
	int		len;
	int		blen;

	i = -1;
	len = cara_after(buffer, str, nb, f);
	cara = ((!(f['-']) && f['0']) || nb[1] == 1) ? '0' : ' ';
	blen = (int)ft_strlen(buffer);
	while (str[++i])
	{
		if (f['.'] && nb[1] <= 0 && str[0] == '0'
				&& !((f['o'] || f['O']) && f['#']))
		{
			if (nb[0] > 0)
				buffer[blen++] = cara;
			break ;
		}
		buffer[blen++] = str[i];
		blen = check(buffer, blen, &len);
		nb[0]--;
	}
	if (f['-'] && nb[0] > 0)
		flag_min(buffer, nb, blen, &len);
	return (len);
}
