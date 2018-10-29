/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:40:18 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/29 19:44:31 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_bool	is_file_next(t_file *file, int nb)
{
	int i;

	i = 0;
	while (i < nb && file)
	{
		file = file->next;
		i++;
	}
	if (file)
		return (T_TRUE);
	return (T_FALSE);
}

static void		print_name(t_file *file, t_option *option)
{
	size_t	current_size;

	current_size = 0;
	if (option->flag & INODE_NUMBER)
	{
		ft_printf("%*d ", option->size_inode - 1, file->stat.st_ino);
		current_size = (size_t)option->size_inode;
	}
	current_size += (size_t)ft_printf("%s", file->name);
	if (is_file_next(file, option->nb_lines))
		ft_printf("% *c", option->max_size_name
				+ (size_t)option->size_inode - current_size, ' ');
}

void			display_col(t_file *file, t_option *option)
{
	t_file	*prec_file;
	int		i;

	prec_file = file;
	while (file)
	{
		print_name(file, option);
		if (prec_file == file)
			file = file->next;
		else
		{
			prec_file->next = prec_file->next->next;
			remov_file(&file, option);
		}
		i = 1;
		while (i < option->nb_lines && file)
		{
			prec_file = file;
			file = file->next;
			i++;
		}
	}
	write(1, "\n", 1);
	option->nb_lines--;
}
