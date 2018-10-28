/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:56:12 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/28 20:40:47 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		remov_item(t_file *it, t_option *option)
{
	if (it->user_name)
		free(it->user_name);
	if (it->grp_name)
		free(it->grp_name);
	if (it->name)
		free(it->name);
	if (it->full_name)
		free(it->full_name);
	if (it->link != option->no_link && it->link)
		free(it->link);
	free(it);
}

void			free_option(t_option *option)
{
	t_file	*current;
	t_file	*to_free;

	current = option->dir;
	option->dir = NULL;
	if (current == NULL)
		current = option->files;
	while (current)
	{
		to_free = current;
		current = current->next;
		remov_item(to_free, option);
		if (current == NULL)
		{
			current = option->files;
			option->files = NULL;
		}
	}
	if (option->path)
		free(option->path);
}

void			remov_file(t_file **file, t_option *option)
{
	t_file	*to_free;

	to_free = *file;
	*file = (*file)->next;
	remov_item(to_free, option);
}

void			remov_dir(t_file *dir, t_option *option)
{
	t_file	*current;
	t_file	*to_free;

	if (dir->full_name == option->dir->full_name)
	{
		remov_file(&option->dir, option);
		return ;
	}
	current = option->dir;
	if (!current->next)
		return ;
	while (current->next->full_name != dir->full_name)
	{
		current = current->next;
		if (current == NULL)
			return ;
	}
	to_free = current->next;
	current->next = current->next->next;
	remov_item(to_free, option);
}

void			reset_size(t_option *option)
{
	option->nb_files = 0;
	option->max_size_name = 8;
	option->size_usr = 0;
	option->size_grp = 0;
	option->max_size_size = 0;
	option->dir_size = 0;
	option->size_links = 0;
}
