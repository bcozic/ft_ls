/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 12:24:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/03/29 16:20:58 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	pars_file(char *str, t_option *option)
{
	struct stat	buff;
	t_file		*new_file;

	if (stat(str, &buff) == -1)
	{
		error_name_file(str);
		return ;
	}
	if (buff.st_mode & S_IFDIR)
	{
		new_file = (option->t == FALSE) ? insert_name(str, option, &option->dir)
			: insert_time(str, option, &option->dir, buff.st_mtimespec);
		new_file->type = DIRECTORY;
	}
	else if (buff.st_mode & S_IFREG)
	{
		new_file = (option->t == FALSE) ? insert_name(str, option, &option->files)
			: insert_time(str, option, &option->files, buff.st_mtimespec);
			new_file->type = REG;
	}
	else
		return ;
	ft_memcpy(&(new_file->stat), &buff, sizeof(struct stat));
}
