/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:56:12 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/13 21:28:52 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*switch_to_free(t_option *option)
{
	t_file *file;

	file = option->files;
	option->files = NULL;
	return (file);
}

void			free_option(t_option *option)
{
	t_file	*current;
	t_file	*to_free;

	current = option->dir;
	option->dir = NULL;
	if (current == NULL)
		switch_to_free(option);
	while (current)
	{
		to_free = current;
		current = current->next;
		if (to_free->user_name)
			free(to_free->user_name);
		if (to_free->grp_name)
			free(to_free->grp_name);
		if (to_free->name)
			free(to_free->name);
		if (to_free->link != option->no_link)
			free(to_free->link);
		free(to_free);
		if (current == NULL)
			switch_to_free(option);
	}
	if (option->path)
		free(option->path);
}

void			remov_file(t_file **file)
{
	t_file	*to_free;

	to_free = *file;
	*file = to_free->next;
	if (to_free->user_name)
		free(to_free->user_name);
	if (to_free->grp_name)
		free(to_free->grp_name);
	free(to_free->name);
	free(to_free);
}

void			reset_size(t_option *option)
{
	option->nb_files = 0;
	option->max_size_name = 0;
	option->size_usr = 0;
	option->size_grp = 0;
	option->file_per_line = 0;
	option->current_line = 0;
	option->max_size_size = 0;
	option->dir_size = 0;
	option->size_links = 0;
}
