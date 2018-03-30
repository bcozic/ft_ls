/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 12:24:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/03/30 19:47:56 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	find_type(mode_t type)
{
	if ((type & S_IFSOCK) == S_IFSOCK)
		return ('s');
	if (type & S_IFREG)
		return ('-');
	if (type & S_IFDIR)
		return ('d');
	if (type & S_IFCHR)
		return ('c');
	if (type & S_IFBLK)
		return ('b');
	if (type & S_IFLNK)
		return ('l');
	if (type & S_IFIFO)
		return ('p');
	return (0);
}

static void	find_rights(struct stat buff, t_file *file)
{
	int	i;

	i = 0;
	file->right[0] = find_type(buff.st_mode);
	while (i < 3)
	{
		file->right[3 * i + 1] = (buff.st_mode & (S_IRUSR >> (3 * i))) ? 'r' : '-';
		file->right[3 * i + 2] = (buff.st_mode & (S_IWUSR >> (3 * i))) ? 'w' : '-';
		file->right[3 * i + 3] = (buff.st_mode & (S_IXUSR >> (3 * i))) ? 'x' : '-';
		i++;
	}
	file->right[10] = '\0';
	file->right[11] = '\0';
}

static void	add_data(t_option *option, t_file *file, struct stat buff)
{
	size_t			size;

	if (option->l == TRUE)
	{
		file->user_name = ft_strdup((getpwuid(buff.st_uid))->pw_name);
		file->grp_name = ft_strdup((getgrgid(buff.st_gid))->gr_name);
		if ((size = ft_strlen(file->user_name) + 2) > (size_t)option->size_usr)
			option->size_usr = (int)size;
		if ((size = ft_strlen(file->grp_name)) > (size_t)option->size_grp)
			option->size_grp = (int)size;
	}
	find_rights(buff, file);
	if ((size = ft_strlen(file->name) + 8) > option->max_size_name)
		option->max_size_name = size;
	option->nb_files++;
	if ((size = (size_t)ft_nbrlen(buff.st_size) + 2) > (size_t)option->max_size_size)
		option->max_size_size = (int)size;
	if ((size = (size_t)ft_nbrlen(buff.st_nlink) + 2) > (size_t)option->size_links)
		option->size_links = (int)size;
}

void		pars_file(char *str, t_option *option)
{
	struct stat	buff;
	t_file		*new_file;
	char		*all_path;
	if (!(all_path = ft_strjoin(option->path, str)))
		error_malloc(option);
	new_file = NULL;
	if (stat(all_path, &buff) == -1)
	{
		error_name_file(str);
		free(all_path);
		return ;
	}
	option->dir_size += (size_t)buff.st_blocks;
	if ((buff.st_mode & S_IFDIR) && (buff.st_mode & S_IFSOCK) != S_IFSOCK && (!option->in_rec || option->rec == TRUE))
	{
		new_file = (option->t == FALSE) ? insert_name(all_path, option, &option->dir)
			: insert_time(all_path, option, &option->dir, buff.st_mtimespec);
	}
	if ((!(buff.st_mode & S_IFDIR)) || option->in_rec)
	{
		new_file = (option->t == FALSE) ? insert_name(str, option, &option->files)
			: insert_time(str, option, &option->files, buff.st_mtimespec);
		add_data(option, new_file, buff);
	}
	ft_memcpy(&(new_file->stat), &buff, sizeof(struct stat));
	free(all_path);
}
