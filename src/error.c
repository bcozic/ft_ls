/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:02:45 by bcozic            #+#    #+#             */
/*   Updated: 2018/03/21 12:00:09 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_option(t_option *option)
{
	t_dir	*current;
	t_dir	*to_free;

	current = option->dir;
	while (current)
	{
		to_free = current;
		current = current ->next;
		free(to_free->name);
		free(to_free);
	}
}

void	display_help(t_option *option)
{
	ft_printf("Usage: ls [OPTION]... [FILE]...\n"
	"List information about the FILEs (the current directory by default).\n"
	"Sort entries alphabetically if none of -r nor -t is specified.\n"
	"-a, --all                  do not ignore entries starting with .\n"
	"-l                         use a long listing format\n"
	"-r, --reverse              reverse order while sorting\n"
	"-R, --recursive            list subdirectories recursively\n"
	"-t                         sort by modification time, newest first\n"
	"\t--help     display this help and exit\n\n"
	"Exit status:\n"
	"0  if OK,\n"
	"1  if minor problems (e.g., cannot access subdirectory),\n"
	"2  if serious trouble (e.g., cannot access command-line argument).\n"
	"3  if system error (failed allocation)\n");
	free_option(option);
	exit(0);
}

void	error_option(t_option *option, char *str)
{
	if (str[0] == '-' && str[1] == '-')
		ft_printf("ls: unrecognized option '%s'\n"
		"Try 'ls --help' for more information.\n", str);
	else
		ft_printf("ls: invalid option -- '%c'\n"
		"Try 'ls --help' for more information.\n", *str);
	free_option(option);
	exit(2);
}

void	error_malloc(t_option *option)
{
	ft_printf(RED"ERROR malloc\n"EOC);
	free_option(option);
	exit(2);
}