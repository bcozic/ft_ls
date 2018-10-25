/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 14:57:24 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/24 21:12:24 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*add_file(t_file *current, char *str, t_option *option, t_file **list)
{
	t_file	*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		err_malloc(option);
	if (current == NULL)
	{
		new->next = *list;
		*list = new;
	}
	else
	{
		new->next = current->next;
		current->next = new;
	}
	if (!(new->name = ft_strdup(str)))
		err_malloc(option);
	new->user_name = NULL;
	new->grp_name = NULL;
	new->link = NULL;
	return (new);
}

t_file	*insert_name(char *str, t_option *option, t_file **list)
{
	t_file	*current;

	current = *list;
	if (*list == NULL || cmp_name(current->name, str, option))
		return (add_file(NULL, str, option, list));
	while (current->next != option->next_dir && current->next)
	{
		if (cmp_name(current->next->name, str, option))
			return (add_file(current, str, option, list));
		current = current->next;
	}
	return (add_file(current, str, option, list));
}

int		cmp_time(t_time time1, t_time time2, t_option *option)
{
	if ((time1.tv_sec > time2.tv_sec && option->rev == T_FALSE) ||
			(time1.tv_sec < time2.tv_sec && option->rev == T_TRUE))
		return (1);
	if (time1.tv_sec == time2.tv_sec)
		return (0);
	return (-1);
}

int		cmp_name(char *name1, char *name2, t_option *option)
{
	if ((ft_strcmp(name1, name2) >= 0 && option->rev == T_FALSE) ||
			(ft_strcmp(name1, name2) <= 0 && option->rev == T_TRUE))
		return (1);
	return (0);
}

t_file	*insert_time(char *str, t_option *option, t_file **list, t_time time)
{
	t_file	*current;
	int		cmp;

	current = *list;
	if (*list == NULL || (cmp = cmp_time(time,
			current->stat.st_mtimespec, option)) == 1)
		return (add_file(NULL, str, option, list));
	else if (cmp == 0)
		if (cmp_name(current->name, str, option))
			return (add_file(NULL, str, option, list));
	while (current->next != option->next_dir && current->next)
	{
		if ((cmp = cmp_time(time, current->next->stat.st_mtimespec, option)
				== 1))
			return (add_file(current, str, option, list));
		else if (cmp == 0)
			if (cmp_name(current->next->name, str, option))
				return (add_file(current, str, option, list));
		current = current->next;
	}
	return (add_file(current, str, option, list));
}
