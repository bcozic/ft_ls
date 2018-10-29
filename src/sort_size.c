/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:08:46 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/29 20:20:43 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	cmp_size(int size1, int size2, t_option *option)
{
	if ((size1 > size2 && !(option->flag & REVERS)) ||
			(size1 < size2 && (option->flag & REVERS)))
		return (1);
	if (size1 == size2)
		return (0);
	return (-1);
}

t_file		*insert_size(char *str, t_option *option,
				t_file **list, struct stat *buff)
{
	t_file	*current;
	int		cmp;

	current = *list;
	if (*list == NULL || (cmp = cmp_size((int)buff->st_size,
			(int)current->stat.st_size, option)) == 1)
		return (add_file(NULL, str, option, list));
	else if (cmp == 0)
		if (cmp_name(current->name, str, option))
			return (add_file(NULL, str, option, list));
	while ((current->next != option->next_dir) && current->next)
	{
		cmp = cmp_size((int)buff->st_size,
				(int)current->next->stat.st_size, option);
		if (cmp == 1)
			return (add_file(current, str, option, list));
		else if (cmp == 0)
		{
			if (cmp_name(current->next->name, str, option))
				return (add_file(current, str, option, list));
		}
		current = current->next;
	}
	return (add_file(current, str, option, list));
}
