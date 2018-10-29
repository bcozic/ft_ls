/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:05:17 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/29 20:49:02 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		padd_name(t_option *option)
{
	int	file_per_line;

	if (!isatty(1))
		option->size_term.ws_col = 80;
	if ((option->size_term.ws_col && isatty(1)
			&& !(option->flag & COLOMN)) || (option->flag & FORCE_COLOMN))
		file_per_line = (int)((size_t)option->size_term.ws_col
				/ (option->max_size_name + (size_t)option->size_inode));
	else
		file_per_line = 1;
	if (file_per_line == 0)
		file_per_line = 1;
	option->nb_lines = option->nb_files / file_per_line
			+ ((option->nb_files % file_per_line) ? 1 : 0);
}

static int	find_year(char *str)
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

	str_time = ctime((time_t *)(&file->time));
	time(&current_time);
	if (current_time - file->time.tv_sec < SEC_IN_SIX_MONTH
			&& file->time.tv_sec - current_time
			< SEC_IN_SIX_MONTH)
		str_time[ft_strlen(str_time) - 9] = '\0';
	else
	{
		i = find_year(str_time);
		ft_memmove(str_time + 11, str_time + i,
				ft_strlen(str_time) - (size_t)i + 1);
	}
	return (str_time);
}
