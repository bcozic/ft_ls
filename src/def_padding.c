/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:05:17 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/22 19:50:07 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	padd_name(t_option *option)
{
	int	rest;

	if (option->size_term.ws_col && isatty(1) && option->col == FALSE)
	{
		option->file_per_line = (int)(((size_t)option->nb_files *
			option->max_size_name) / (size_t)option->size_term.ws_col);
		option->file_per_line += ((int)(((size_t)option->nb_files *
			option->max_size_name) % (size_t)option->size_term.ws_col)) ? 1 : 0;
	}
	else
		option->file_per_line = option->nb_files;
	if (option->file_per_line == 0)
		option->file_per_line = option->nb_files;
	rest = (option->nb_files % option->file_per_line) ? 1 : 0;
	option->file_per_line = option->nb_files / option->file_per_line + rest;
}

char	*pad_time(t_file *file)
{
	time_t	current_time;
	char	*str_time;

	str_time = ctime((time_t *)(&file->stat.st_mtimespec));
	time(&current_time);
	if (current_time - file->stat.st_mtimespec.tv_sec < 60 * 60 * 24 * 180)
		str_time[ft_strlen(str_time) - 9] = '\0';
	else
	{
		str_time[ft_strlen(str_time) - 1] = '\0';
		ft_memmove(str_time + 11, str_time + 19, 6);
	}
	return (str_time);
}
