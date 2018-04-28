/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:02:45 by bcozic            #+#    #+#             */
/*   Updated: 2018/04/28 18:02:00 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	disp_help(t_option *option)
{
	ft_printf("Usage: ./ft_ls [OPTION]... [FILE]...\n"
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
	{
		write(2, "ft_ls: unrecognized option '", 28);
		write(2, str, ft_strlen(str));
		write(2, "'\n", 2);
	}
	else
	{
		write(2, "ft_ls: invalid option -- '", 26);
		write(2, str, 1);
		write(2, "'\n", 2);
	}
	ft_printf("Try './ft_ls --help' for more information.\n"
			"usage: ./ft_ls [-alrRt] [--all] [--reverse]"
			" [-- recursive] [--help] [file ...]\n");
	free_option(option);
	exit(1);
}

void	err_malloc(t_option *option)
{
	write(2, "ERROR malloc\n", 13);
	free_option(option);
	exit(2);
}

void	error_name_file(t_option *option)
{
	while (option->no_found)
	{
		write(2, "ft_ls: ", 7);
		write(2, option->no_found->name, ft_strlen(option->no_found->name));
		write(2, ": No such file or directory\n", 28);
		remov_file(&option->no_found, option);
	}
	option->first = 0;
}

void	other_err(t_option *option)
{
	perror(NULL);
	free_option(option);
	exit(2);
}

void	error_rights(t_file *file)
{
	write(2, "ft_ls: ", 7);
	write(2, file->name, ft_strlen(file->name));
	write(2, ": Permission denied\n", 20);
}
