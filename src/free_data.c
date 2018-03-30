/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:56:12 by bcozic            #+#    #+#             */
/*   Updated: 2018/03/30 19:12:41 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_option(t_option *option)
{
	t_file	*current;
	t_file	*to_free;

	current = option->dir;
	while (current)
	{
		to_free = current;
		current = current->next;
		if (to_free->user_name)
			free(to_free->user_name);
		if (to_free->grp_name)
			free(to_free->grp_name);
		free(to_free->name);
		free(to_free);
	}
	current = option->files;
	while (current)
	{
		to_free = current;
		current = current->next;
		if (to_free->user_name)
			free(to_free->user_name);
		if (to_free->grp_name)
			free(to_free->grp_name);
		free(to_free->name);
		free(to_free);
	}
	if (option->path)
		free(option->path);
	option->path = NULL;
}

void	remov_file(t_file **file)
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

void	reset_size(t_option *option)
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
