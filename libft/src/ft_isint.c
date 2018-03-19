/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:14:36 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/01 10:16:24 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int		ft_isint(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i + j] && ft_isdigit(str[i + j]))
		j++;
	if (j > 10 || (j == 10 && str[i + j - 1] > '2'))
		return (0);
	if (ft_atoi_unsigned(str) > (unsigned int)(INT_MAX) + 1
			|| (ft_atoi_unsigned(str) > INT_MAX && str[0] != '-'))
		return (0);
	return (1);
}
