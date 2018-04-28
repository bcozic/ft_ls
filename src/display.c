/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:42:13 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/28 19:11:29 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		display_no_l(t_file *file, size_t size, t_option *option)
{
	size_t	current_size;

	if (((size += option->max_size_name) > option->size_term.ws_col
		|| option->current_line++ >= option->file_per_line) && !option->first_file)
	{
		ft_printf("\n");
		size = 0;
		option->current_line = 1;
	}
	current_size = (size_t)ft_printf("%s", file->name);
	if (file->next == NULL && ((option->dir && !option->path)
			|| (option->path && option->dir)))
	{
		write(1, "\n", 1);
		return (0);
	}
	else if (file->next && size + option->max_size_name <= option->size_term.ws_col
		&& option->current_line < option->file_per_line)
		ft_printf("% *c", option->max_size_name - current_size, ' ');
	else if (!file->next)
		write(1, "\n", 1);
	return (size);
}

void		display_l(t_file *file, t_option *option)
{
	char	*time;

	time = pad_time(file);
	ft_printf("%s%*d %-*s%-*s%*lld %s %s%s\n", file->right, option->size_links,
		file->stat.st_nlink, option->size_usr, file->user_name,
		option->size_grp, file->grp_name, option->max_size_size,
		file->stat.st_size, time + 4, file->name, file->link);
}

void		display_reg(t_option *option)
{
	size_t	size;

	size = 0;
	padd_name(option);
	option->first_file = 1;
	while (option->files)
	{
		if (option->l == TRUE)
			display_l(option->files, option);
		else
			size = display_no_l(option->files, size, option);
		remov_file(&option->files, option);
		option->first_file = 0;
	}
	if (option->first_dir && option->dir)
		ft_printf("\n");
	option->first_dir = 0;
	option->first = 0;
}

void		display_infos(t_option *option)
{
	DIR				*dir;
	t_file			*ptr_dir;

	ptr_dir = option->dir;
	if (!option->first || option->dir->next)
		ft_printf("%s:\n", option->dir->name);
	option->first = 0;
	option->first_dir = 0;
	reset_size(option);
	if ((dir = opendir(option->dir->name)))
	{
		if (!(option->path = ft_strjoin(option->dir->name, "/")))
			err_malloc(option);
			option->next_dir = option->dir->next;
			get_files(option, dir);
			closedir(dir);
	}
	else
		error_rights(ptr_dir);
	if (option->l == TRUE && option->files)
		ft_printf("total %lu\n", option->dir_size);
	remov_dir(ptr_dir, option);
	if (option->files)
		display_reg(option);
	option->next_dir = NULL;
	free(option->path);
	option->path = NULL;
	if (option->dir)
		ft_printf("\n");
}
