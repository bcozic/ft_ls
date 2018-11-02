/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_islink.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 00:49:11 by bcozic            #+#    #+#             */
/*   Updated: 2018/11/02 01:21:19 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_link(t_option *option, char *all_path,
			struct stat **ptr_buff, struct stat *buff)
{
	if (!(option->flag & LONG_LIST_FORMAT)
			&& (buff->st_mode & S_IFMT) == S_IFLNK)
	{
		stat(all_path, *ptr_buff);
		if (!option->is_arg)
			return (0);
	}
	else
		*ptr_buff = buff;
	return (1);
}
