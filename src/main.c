/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:31:14 by barbara           #+#    #+#             */
/*   Updated: 2018/03/29 16:30:08 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_option	option;
	t_file		*current;

	ft_bzero(&option, sizeof(t_option));
	parsing(argc, argv, &option);
	display_reg(&option)
	current = option->dir;
	while (current)
		display_infos(&option, current);
	free_option(&option);
	return (0);
}

	// DIR* directory = opendir("Makefile");
	// struct dirent *file = NULL;
	// if (directory)
	// do
	// {
	//     file = readdir(directory);

	//     // if (file)
	//     //   ft_printf("%s\n", file->d_name);
	// } while (file != NULL);
