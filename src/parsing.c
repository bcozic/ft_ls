/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:19:49 by barbara           #+#    #+#             */
/*   Updated: 2018/03/21 11:59:56 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	add_directory(t_dir *current, char *str, t_option *option)
{
	t_dir	*new;

	if (!(new = (t_dir *)malloc(sizeof(t_dir))))
		error_malloc(option);
	if (current == option->dir)
	{
		new->next = option->dir;
		option->dir = new;
	}
	else
	{
		new->next = current->next;
		current->next = new;
	}
	new->name = ft_strdup(str);
}

void	parsing(int argc, char **argv, t_option *option)
{
	while (--argc > 0)
	{
		if (!ft_strncmp(argv[argc], "--", 2))
			option_full_name(argv[argc], option);
		else if (argv[argc][0] == '-')
			option_short_name(argv[argc], option);
		else
			dir_name(argv[argc], option);
	}
	if (option->dir == NULL)
		add_directory(option->dir, ".", option);
}

void	option_full_name(char *str, t_option *option)
{
	if (!ft_strcmp(str, "--recursive"))
		option->rec = TRUE;
	else if (!ft_strcmp(str, "--all"))
		option->a = TRUE;
	else if (!ft_strcmp(str, "--reverse"))
		option->rev = TRUE;
	else if (!ft_strcmp(str, "--help"))
		display_help(option);
	else
		error_option(option, str);
}

void	option_short_name(char *str, t_option *option)
{
	while (*(++str))
		if (*str == 'l')
			option->l = TRUE;
		else if (*str == 'R')
			option->rec = TRUE;
		else if (*str == 'a')
			option->a = TRUE;
		else if (*str == 'r')
			option->rev = TRUE;
		else if (*str == 't')
			option->t = TRUE;
		else
			error_option(option, str);
}

void	dir_name(char *str, t_option *option)
{
	t_dir	*current;

	current = option->dir;
	if ((option->dir == NULL) || (ft_strcmp(option->dir->name, str)) < 0)
	{
		add_directory(current, str, option);
		return ;
	}
	while (current->next)
	{
		if (ft_strcmp(current->name, str) < 0)
		{
			add_directory(current, str, option);
			return ;
		}
	}
	add_directory(current, str, option);
}