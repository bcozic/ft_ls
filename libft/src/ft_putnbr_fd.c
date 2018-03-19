/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbara <barbara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:01:09 by bcozic            #+#    #+#             */
/*   Updated: 2018/03/19 11:51:06 by barbara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		neg;

	neg = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		neg = -1;
	}
	if ((n >= 10) | (n <= -10))
		ft_putnbr_fd((n / 10) * neg, fd);
	ft_putchar_fd((char)((n % 10) * neg) + '0', fd);
}
