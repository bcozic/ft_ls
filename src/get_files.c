/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 19:49:19 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/28 18:37:30 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_hide(char *str)
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

void		get_files(t_option *option, DIR *dir)
{
	struct dirent	*file;

	while ((file = readdir(dir)) != NULL)
	{
		if (option->a == TRUE || (check_hide(file->d_name)))
			pars_file(file->d_name, option);
	}
}

void		get_l_infos(t_option *option, t_file *file, struct stat buff)
{
	size_t	size;

	if (getpwuid(buff.st_uid) == NULL)
	{
		if (!(file->user_name = ft_itoa((int)buff.st_uid)))
			err_malloc(option);
	}
	else if (!(file->user_name = ft_strdup(getpwuid(buff.st_uid)->pw_name)))
		err_malloc(option);
	if (!(file->grp_name = ft_strdup((getgrgid(buff.st_gid))->gr_name)))
		err_malloc(option);
	if ((size = ft_strlen(file->user_name) + 2) > (size_t)option->size_usr)
		option->size_usr = (int)size;
	if ((size = ft_strlen(file->grp_name)) > (size_t)option->size_grp)
		option->size_grp = (int)size;
}

void		add_file_lst(t_option *option, char *str,
				struct stat buff, char *all_path)
{
	t_file	*new_file;
	struct stat buff2;
	struct stat *ptr_buff;

	ptr_buff = &buff2;
	if (option->l == FALSE && (buff.st_mode & S_IFMT) == S_IFLNK)
		stat(all_path, ptr_buff);
	else
		ptr_buff = &buff;
	new_file = NULL;
	if ((ptr_buff->st_mode & S_IFMT) == S_IFDIR && (!option->in_rec
		|| option->rec == TRUE) && !(option->in_rec
		&& (!ft_strcmp(".", str) || !ft_strcmp("..", str))))
	{
		new_file = (option->t == FALSE) ?
			insert_name(all_path, option, &option->dir)
			: insert_time(all_path, option, &option->dir, buff.st_mtimespec);
		ft_memcpy(&(new_file->stat), &buff, sizeof(struct stat));
	}
	if (((ptr_buff->st_mode & S_IFMT) != S_IFDIR) || option->in_rec)
	{
		new_file = (option->t == FALSE) ?
			insert_name(str, option, &option->files)
			: insert_time(str, option, &option->files, buff.st_mtimespec);
		add_data(option, new_file, buff);
		ft_memcpy(&(new_file->stat), &buff, sizeof(struct stat));
	}
}
