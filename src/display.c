/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:42:13 by bcozic            #+#    #+#             */
/*   Updated: 2018/03/29 16:50:33 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_no_l(t_files *file, int size)
{
	if ((size += option->max_size) > option->size_term.ws_col)
	{
		ft_printf("\n");
		size = 0;
	}
	return (size)
}

void	display_reg(t_option *option)
{
	int	size;

	size = 0;
	while (current)
	{
		if (option->l == TRUE)
			display_l(option->files);
		else
			size = display_no_l(option->files, size);
		remov_file(option)
	}
}

void	display_info(t_option *option, t_file *file)
{

}