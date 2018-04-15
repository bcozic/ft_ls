/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 12:24:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/15 14:57:07 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_link(t_file *file, t_option *option)
{
	ssize_t	len;

	char	*full_name;
	if (file->right[0] != 'l')
	{
		file->link = option->no_link;
		return ;
	}
	if (!(file->link = (char *)malloc(sizeof(char) * 256)))
		err_malloc(option);
	if (!(full_name = ft_strjoin(option->path, file->name)))
		err_malloc(option);
	ft_strcpy(file->link, " -> ");
	len = readlink(full_name, file->link + 4, 252);
	free(full_name);
	if (len == -1)
	{
		perror(NULL);
		other_err(option);
	}
	file->link[len + 4] = '\0';
}

static char	find_type(mode_t type)
{
	char	ret;

	ret = 0;
	if (type == S_IFSOCK)
		ret = 's';
	else if (type == S_IFLNK)
		ret = 'l';
	else if (type == S_IFWHT)
		ret = ' ';
	else if (type == S_IFREG)
		ret = '-';
	else if (type == S_IFDIR)
		ret = 'd';
	else if (type == S_IFCHR)
		ret = 'c';
	else if (type == S_IFBLK)
		ret = 'b';
	else if (type == S_IFIFO)
		ret = 'p';
	return (ret);
}

static void	find_rights(struct stat buff, t_file *file)
{
	int		i;
	mode_t	mode;

	mode = buff.st_mode;
	i = 0;
	file->right[0] = find_type(mode & S_IFMT);
	while (i < 3)
	{
		file->right[3 * i + 1] = (mode & (S_IRUSR >> (3 * i))) ? 'r' : '-';
		file->right[3 * i + 2] = (mode & (S_IWUSR >> (3 * i))) ? 'w' : '-';
		file->right[3 * i + 3] = (mode & (S_IXUSR >> (3 * i))) ? 'x' : '-';
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
	find_rights(buff, file);
	get_link(file, option);
	if ((size = ft_strlen(file->name) + 6) > option->max_size_name)
		option->max_size_name = size;
	option->nb_files++;
	if ((size = (size_t)ft_nbrlen(buff.st_size) + 2) >
			(size_t)option->max_size_size)
		option->max_size_size = (int)size;
	if ((size = (size_t)ft_nbrlen(buff.st_nlink) + 2) >
	(size_t)option->size_links)
		option->size_links = (int)size;
}

void		pars_file(char *str, t_option *option)
{
	struct stat	buff;
	t_file		*new_file;
	char		*all_path;

	if (!(all_path = ft_strjoin(option->path, str)))
		err_malloc(option);
	new_file = NULL;
	if (lstat(all_path, &buff) == -1)
	{
		error_name_file(str);
		free(all_path);
		return ;
	}
	option->dir_size += (size_t)buff.st_blocks;
	if ((buff.st_mode & S_IFMT) == S_IFDIR && (!option->in_rec
		|| option->rec == TRUE) && !(option->in_rec
		&& (!ft_strcmp(".", str) || !ft_strcmp("..", str))))
	{
		new_file = (option->t == FALSE) ?
			insert_name(all_path, option, &option->dir)
			: insert_time(all_path, option, &option->dir, buff.st_mtimespec);
	}
	if ((!(buff.st_mode & S_IFDIR)) || option->in_rec)
	{
		if (!(new_file = (option->t == FALSE) ?
				insert_name(str, option, &option->files)
				: insert_time(str, option, &option->files, buff.st_mtimespec)))
			err_malloc(option);
		add_data(option, new_file, buff);
	}
	ft_memcpy(&(new_file->stat), &buff, sizeof(struct stat));
	free(all_path);
}
