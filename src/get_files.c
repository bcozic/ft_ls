/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 19:49:19 by bcozic            #+#    #+#             */
/*   Updated: 2018/11/02 01:58:42 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		check_hide(char *str)
{
	int	i;

	i = (int)ft_strlen(str);
	while (--i >= 0 && (str[i] != '/' || i == (int)ft_strlen(str)))
	{
		if (str[i] == '.' && (i == 0 || str[i - 1] == '/'))
			return (0);
	}
	return (1);
}

void			get_files(t_option *option, DIR *dir)
{
	struct dirent	*file;

	while ((file = readdir(dir)) != NULL)
		if ((option->flag & ALL) || (check_hide(file->d_name))
				|| ((option->flag & ALL_EXCEPT)
						&& ft_strcmp(file->d_name, ".")
						&& ft_strcmp(file->d_name, "..")))
			pars_file(file->d_name, option);
}

void			get_l_infos(t_option *option, t_file *file)
{
	size_t	size;

	if (getpwuid(file->stat.st_uid) == NULL)
	{
		if (!(file->user_name = ft_itoa((int)file->stat.st_uid)))
			err_malloc(option);
	}
	else if (!(file->user_name =
			ft_strdup(getpwuid(file->stat.st_uid)->pw_name)))
		err_malloc(option);
	if (!(file->grp_name = ft_strdup((getgrgid(file->stat.st_gid))->gr_name)))
		err_malloc(option);
	if ((size = ft_strlen(file->user_name) + 2) > (size_t)option->size_usr)
		option->size_usr = (int)size;
	if ((size = ft_strlen(file->grp_name)) > (size_t)option->size_grp)
		option->size_grp = (int)size;
}

static t_file	*init_new_file(char *str, t_option *option,
				t_file **list, struct stat *buff)
{
	if (option->flag & NO_SORT)
		return (insert_end(str, option, list));
	if (option->flag & SORT_SIZE)
		return (insert_size(str, option, list, buff));
	else if (option->flag & SORT_TIME)
	{
		if (option->flag & SORT_LST_ACCESS)
			return (insert_time(str, option, list, buff->st_atimespec));
		else if (option->flag & SORT_FILE_CREATION)
			return (insert_time(str, option, list, buff->st_birthtimespec));
		else if (option->flag & SORT_STATUS_CHANGED)
			return (insert_time(str, option, list, buff->st_ctimespec));
		else
			return (insert_time(str, option, list, buff->st_mtimespec));
	}
	else
		return (insert_name(str, option, list));
}

void			add_file_lst(t_option *option, char *str,
				struct stat *buff, char *all_path)
{
	struct stat	*ptr_buff;
	int			reg;
	struct stat	buff2;

	ptr_buff = &buff2;
	reg = is_link(option, all_path, &ptr_buff, buff);
	if ((ptr_buff->st_mode & S_IFMT) == S_IFDIR && reg && (!option->in_rec
			|| (option->flag & RECURSIVE)) && !(option->in_rec
			&& (!ft_strcmp(".", str) || !ft_strcmp("..", str)))
			&& !(option->flag & DIRECTORY_LIST))
	{
		option->is_reg = 1;
		add_data(option, init_new_file(str, option, &option->dir, buff),
				buff, ft_strdup(all_path));
		option->is_reg = 0;
	}
	if (((ptr_buff->st_mode & S_IFMT) != S_IFDIR) || option->in_rec
			|| (option->flag & DIRECTORY_LIST))
		add_data(option, init_new_file(str, option, &option->files, buff),
				buff, all_path);
	else
		free(all_path);
}
