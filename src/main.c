/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:31:14 by barbara           #+#    #+#             */
/*   Updated: 2018/11/02 00:40:39 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_options(t_option *option, int *ret)
{
	ft_bzero(option, sizeof(t_option));
	option->first = 1;
	option->first_dir = 1;
	option->max_size_name = 8;
	option->ret = ret;
	ioctl(0, TIOCGWINSZ, &(option->size_term));
}

int			main(int argc, char **argv)
{
	t_option	option;
	t_option	*ptr;
	int			ret;

	ptr = &option;
	ret = 0;
	init_options(&option, &ret);
	option.is_arg = 1;
	parsing(argc, argv, &option);
	option.is_arg = 0;
	if (option.no_found)
		error_name_file(&option);
	if (option.files)
		display_reg(&option);
	option.in_rec = 1;
	while (option.dir)
		display_infos(&option);
	free_option(&option);
	return (ret);
}
