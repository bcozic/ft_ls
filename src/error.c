/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:02:45 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/24 18:50:06 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_option(t_option *option, char *str)
{
	write(2, "./ft_ls: illegal option -- '", 28);
	write(2, str, 1);
	write(2, "'\n", 2);
	ft_printf("usage: ./ft_ls [-alrRt] [file ...]\n");
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
		write(2, "./ft_ls: ", 9);
		write(2, option->no_found->name, ft_strlen(option->no_found->name));
		write(2, ": No such file or directory\n", 28);
		remov_file(&option->no_found, option);
	}
	option->first = 0;
	*(option->ret) = 1;
}

void	other_err(t_option *option)
{
	perror(NULL);
	free_option(option);
	exit(2);
}

void	error_rights(t_file *file, t_option *option)
{
	write(2, "./ft_ls: ", 9);
	write(2, file->name, ft_strlen(file->name));
	write(2, ": Permission denied\n", 20);
	*(option->ret) = 1;
}
