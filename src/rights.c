/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:32:47 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/29 20:19:54 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	if (listxattr(file->full_name, buffer, 1024, XATTR_NOFOLLOW))
		file->right[10] = '@';
	acl_free((void *)acl);
}

void		find_rights(struct stat buff, t_file *file)
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
	specific_perms(file, mode);
}
