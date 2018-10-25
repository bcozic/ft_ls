/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:02:26 by bcozic            #+#    #+#             */
/*   Updated: 2018/05/06 15:20:59 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

void	ft_free_and_reset(int nb, ...)
{
	va_list	va;
	void	**to_free;

	va_start(va, nb);
	while (nb-- > 0)
	{
		to_free = va_arg(va, void**);
		free(*to_free);
		*to_free = NULL;
	}
	va_end(va);
}
