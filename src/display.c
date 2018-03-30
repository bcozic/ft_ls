/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:42:13 by bcozic            #+#    #+#             */
/*   Updated: 2018/03/30 19:49:29 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	display_no_l(t_file *file, size_t size, t_option *option)
{
	size_t	current_size;

	if ((size += option->max_size_name) > option->size_term.ws_col
		|| option->current_line++ >= option->file_per_line)
	{
		ft_printf("\n");
		size = 0;
		option->current_line = 1;
	}
	current_size = (size_t)ft_printf("%s", file->name);
	if (file->next == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	ft_printf("% *c", option->max_size_name - current_size, ' ');
	return (size);
}

void	display_l(t_file *file, t_option *option)
{
	char	*time;

	time = pad_time(file);
	ft_printf("%s%*d %-*s%-*s%*lld %s %s\n", file->right, option->size_links, file->stat.st_nlink, option->size_usr, file->user_name, option->size_grp, file->grp_name, option->max_size_size, file->stat.st_size, time + 4, file->name);
}

void	display_reg(t_option *option)
{
	size_t	size;

	size = 0;
	padd_name(option);
	while (option->files)
	{
		if (option->l == TRUE)
			display_l(option->files, option);
		else
			size = display_no_l(option->files, size, option);
		remov_file(&option->files);
	}
}

void	display_infos(t_option *option)
{
	DIR				*dir;
	struct dirent	*file;

	if (option->nb_files != 0)
		ft_printf("\n%s:\n", option->dir->name);
	else if (option->dir->next)
		ft_printf("%s:\n", option->dir->name);
	reset_size(option);
	dir = opendir(option->dir->name);
	if (!(option->path = ft_strjoin(option->dir->name, "/")))
		error_malloc(option);
	while ((file = readdir(dir)) != NULL)
	{
		if (file->d_name[0] != '.' || option->a == TRUE)
			pars_file(file->d_name, option);
	}
	closedir(dir);
	if (option->l == TRUE)
		ft_printf("total %lu\n", option->dir_size);
	if (option->files)
		display_reg(option);
	free(option->path);
	option->path = NULL;
}
