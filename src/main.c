/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:31:14 by barbara           #+#    #+#             */
/*   Updated: 2018/03/30 18:53:58 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_option	option;
	t_option	*ptr;

	ptr = &option;
	ft_bzero(&option, sizeof(t_option));
	parsing(argc, argv, &option);
	if (option.files)
		display_reg(&option);
	option.in_rec = 1;
	while (option.dir)
	{
		display_infos(&option);
		remov_file(&(ptr->dir));
	}
	free_option(&option);
	return (0);
}
