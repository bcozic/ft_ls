/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 14:57:24 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/29 20:10:04 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*add_file(t_file *current, char *str, t_option *option, t_file **list)
{
	t_file	*new;

	if (!(new = (t_file *)ft_memalloc(sizeof(t_file))))
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
	return (new);
}

int		cmp_name(char *name1, char *name2, t_option *option)
{
	if ((ft_strcmp(name1, name2) >= 0 && !(option->flag & REVERS)) ||
			(ft_strcmp(name1, name2) <= 0 && (option->flag & REVERS)))
		return (1);
	return (0);
}

t_file	*insert_end(char *str, t_option *option, t_file **list)
{
	t_file	*current;

	current = *list;
	if (*list == NULL)
		return (add_file(NULL, str, option, list));
	while (current->next != option->next_dir && current->next)
	{
		current = current->next;
	}
	return (add_file(current, str, option, list));
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
