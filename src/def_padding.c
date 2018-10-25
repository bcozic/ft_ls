/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:05:17 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/24 21:13:22 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		padd_name(t_option *option)
{
	if (option->size_term.ws_col && isatty(1) && option->col == T_FALSE)
		option->file_per_line = (int)((size_t)option->size_term.ws_col / option->max_size_name);
	else
		option->file_per_line = 1;
	if (option->file_per_line == 0)
		option->file_per_line = 1;
	option->nb_lines = option->nb_files / option->file_per_line + ((option->nb_files % option->file_per_line) ? 1 : 0);
}

static int	fine_year(char *str)
{
	int	i;

	i = (int)ft_strlen(str);
	while (ft_isspace(str[i - 1]))
		--i;
	str[i] = '\0';
	while (ft_isdigit(str[i - 1]))
		--i;
	i--;
	return (i);
}

char		*pad_time(t_file *file)
{
	time_t	current_time;
	char	*str_time;
	int		i;

	str_time = ctime((time_t *)(&file->stat.st_mtimespec));
	time(&current_time);
	if (current_time - file->stat.st_mtimespec.tv_sec < 60 * 60 * 24 * 180
			&& current_time - file->stat.st_mtimespec.tv_sec
			> -60 * 60 * 24 * 180)
		str_time[ft_strlen(str_time) - 9] = '\0';
	else
	{
		i = fine_year(str_time);
		ft_memmove(str_time + 11, str_time + i,
			ft_strlen(str_time) - (size_t)i + 1);
	}
	return (str_time);
}
