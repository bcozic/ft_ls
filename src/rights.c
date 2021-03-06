/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:32:47 by bcozic            #+#    #+#             */
/*   Updated: 2018/11/15 18:57:35 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	special_device(t_file *file, t_option *option)
{
	file->is_spe = 1;
	file->majeur = ((uint64_t)(file->stat.st_rdev) & 0xff000000) >> 24;
	file->minor = (uint64_t)(file->stat.st_rdev) & 0x00ffffff;
	if (option->max_size_size < 10)
		option->max_size_size = 10;
}

static char	find_type(mode_t type, t_file *file, t_option *option)
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
	if (ret == 'c' || ret == 'b')
		special_device(file, option);
	return (ret);
}

static void	specific_perms(t_file *file, mode_t mode)
{
	char	buffer[1024];
	acl_t	acl;

	if (mode & S_ISUID)
		file->right[3] = (file->right[3] == 'x') ? 's' : 'S';
	if (mode & S_ISGID)
		file->right[6] = (file->right[6] == 'x') ? 's' : 'S';
	if (mode & S_ISVTX)
		file->right[9] = (file->right[9] == 'x') ? 't' : 'T';
	file->right[10] = ' ';
	if ((acl = acl_get_link_np(file->full_name, ACL_TYPE_EXTENDED)))
		file->right[10] = '+';
	if (listxattr(file->full_name, buffer, 1024, XATTR_NOFOLLOW) > 0)
		file->right[10] = '@';
	acl_free((void *)acl);
}

void		find_rights(t_file *file, t_option *option)
{
	int		i;
	mode_t	mode;

	mode = file->stat.st_mode;
	i = 0;
	file->right[0] = find_type(mode & S_IFMT, file, option);
	while (i < 3)
	{
		file->right[3 * i + 1] = (mode & (S_IRUSR >> (3 * i))) ? 'r' : '-';
		file->right[3 * i + 2] = (mode & (S_IWUSR >> (3 * i))) ? 'w' : '-';
		file->right[3 * i + 3] = (mode & (S_IXUSR >> (3 * i))) ? 'x' : '-';
		i++;
	}
	specific_perms(file, mode);
}
