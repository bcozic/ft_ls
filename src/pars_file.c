/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 12:24:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/28 18:53:35 by bcozic           ###   ########.fr       */
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
	if (mode & S_ISUID)
		file->right[3] = (file->right[3] == 'x') ? 's' : 'S';
	if (mode & S_ISGID)
		file->right[6] = (file->right[6] == 'x') ? 's' : 'S';
	if (mode & S_ISVTX)
		file->right[9] = (file->right[9] == 'x') ? 't' : 'T';
	file->right[10] = '\0';
	file->right[11] = '\0';
}

void		add_data(t_option *option, t_file *file, struct stat buff)
{
	size_t			size;

	if (option->l == TRUE)
		get_l_infos(option, file, buff);
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
	char		*all_path;
	t_bool		save;

	if (!(all_path = ft_strjoin(option->path, str)))
		err_malloc(option);
	if (lstat(all_path, &buff) == -1)
	{
		save = option->rev;
		option->rev = FALSE;
		insert_name(all_path, option, &option->no_found);
		option->rev = save;
		free(all_path);
		return ;
	}
	option->dir_size += (size_t)buff.st_blocks;
	add_file_lst(option, str, buff, all_path);
	free(all_path);
}
