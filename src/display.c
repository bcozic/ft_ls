/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:42:13 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/28 20:44:41 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bool		is_file_next(t_file *file, int nb)
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

void		display_no_l(t_file *file, t_option *option)
{
	t_file *prec_file;
	size_t	current_size;
	int i;

	prec_file = file;
	while (file)
	{
		current_size = (size_t)ft_printf("%s", file->name);

		if (is_file_next(file, option->nb_lines))
			ft_printf("% *c", option->max_size_name - current_size, ' ');
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

void		display_l(t_file *file, t_option *option)
{
	char	*time;

	time = pad_time(file);
	if (option->flag & DISP_GRP_NAME)
		ft_printf("%s%*d %-*s%*lld %s %s%s\n", file->right, option->size_links,
				file->stat.st_nlink,
				option->size_grp, file->grp_name, option->max_size_size,
				file->stat.st_size, time + 4, file->name, file->link);
	else
		ft_printf("%s%*d %-*s%-*s%*lld %s %s%s\n", file->right, option->size_links,
				file->stat.st_nlink, option->size_usr, file->user_name,
				option->size_grp, file->grp_name, option->max_size_size,
				file->stat.st_size, time + 4, file->name, file->link);
}

void		display_reg(t_option *option)
{
	padd_name(option);
	while (option->files)
	{
		if (option->flag & LONG_LIST_FORMAT)
			display_l(option->files, option);
		else
		{
			display_no_l(option->files, option);
			// if (!option->files->next && ((option->dir && !option->path)
			// 		|| (option->path && option->dir)))
			// 	write(1, "\n", 1);
		}
		remov_file(&option->files, option);
	}
	if (option->first_dir && option->dir)
		ft_printf("\n");
	option->first_dir = 0;
	option->first = 0;
}

static void	reset_after_display_dir(t_option *option)
{
	option->next_dir = NULL;
	ft_free_and_reset(1, &option->path);
	if (option->dir)
		ft_printf("\n");
}

void		display_infos(t_option *option)
{
	DIR				*dir;
	t_file			*ptr_dir;

	ptr_dir = option->dir;
	if (!option->first || option->dir->next)
		ft_printf("%s:\n", option->dir->full_name);
	option->first = 0;
	option->first_dir = 0;
	reset_size(option);
	if ((dir = opendir(option->dir->full_name)))
	{
		if (!(option->path = ft_strjoin(option->dir->full_name, "/")))
			err_malloc(option);
		option->next_dir = option->dir->next;
		get_files(option, dir);
		closedir(dir);
	}
	else
		error_rights(ptr_dir, option);
	if ((option->flag & LONG_LIST_FORMAT) && option->files)
		ft_printf("total %lu\n", option->dir_size);
	remov_dir(ptr_dir, option);
	if (option->files)
		display_reg(option);
	reset_after_display_dir(option);
}
