/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 12:24:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/11/15 18:13:17 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_link(t_file *file, t_option *option)
{
	ssize_t	len;

	if (file->right[0] != 'l')
	{
		file->link = option->no_link;
		return ;
	}
	if (!(file->link = (char *)malloc(sizeof(char) * 256)))
		err_malloc(option);
	ft_strcpy(file->link, " -> ");
	len = readlink(file->full_name, file->link + 4, 252);
	if (len == -1)
	{
		perror(NULL);
		other_err(option);
	}
	file->link[len + 4] = '\0';
}

static void	which_display_time(t_option *option, t_file *file)
{
	if (option->flag & SORT_LST_ACCESS)
		file->time = file->stat.st_atimespec;
	else if (option->flag & SORT_FILE_CREATION)
		file->time = file->stat.st_birthtimespec;
	else if (option->flag & SORT_STATUS_CHANGED)
		file->time = file->stat.st_ctimespec;
	else
		file->time = file->stat.st_mtimespec;
}

static void	add_data_file(t_option *option, t_file *file)
{
	size_t			size;

	if (option->flag & LONG_LIST_FORMAT)
		get_l_infos(option, file);
	size = ft_strlen(file->name) + 1;
	while (size > option->max_size_name)
		option->max_size_name += 8;
	option->nb_files++;
	if ((size = (size_t)ft_nbrlen(file->stat.st_size) + 2) >
			(size_t)option->max_size_size)
		option->max_size_size = (int)size;
	if ((size = (size_t)ft_nbrlen(file->stat.st_nlink) + 1) >
	(size_t)option->size_links)
		option->size_links = (int)size;
	if ((option->flag & INODE_NUMBER)
			&& ((size = (size_t)ft_nbrlen((int)file->stat.st_ino) + 1)
			> (size_t)option->size_inode))
		option->size_inode = (int)size;
}

void		add_data(t_option *option, t_file *file,
				struct stat *buff, char *all_path)
{
	file->full_name = all_path;
	ft_memcpy(&(file->stat), buff, sizeof(struct stat));
	find_rights(file, option);
	get_link(file, option);
	if (!option->is_reg)
		add_data_file(option, file);
	which_display_time(option, file);
}

void		pars_file(char *str, t_option *option)
{
	struct stat	buff;
	char		*all_path;
	t_bool		save;

	if (!(all_path = ft_strjoin(option->path, str)))
		err_malloc(option);
	if (lstat(all_path, &buff) == -1)
	{
		save = option->flag;
		option->flag &= (0XFFFFFFFF ^ REVERS);
		insert_name(str, option, &option->no_found);
		option->flag = save;
		free(all_path);
		return ;
	}
	option->dir_size += (size_t)buff.st_blocks;
	add_file_lst(option, str, &buff, all_path);
}
