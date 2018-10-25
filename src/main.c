/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:31:14 by barbara           #+#    #+#             */
/*   Updated: 2018/10/24 14:14:03 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_option	option;
	t_option	*ptr;
	int			ret;

	ptr = &option;
	ret = 0;
	ft_bzero(&option, sizeof(t_option));
	option.first = 1;
	option.first_dir = 1;
	option.max_size_name = 8;
	option.ret = &ret;
	parsing(argc, argv, &option);
	if (option.no_found)
		error_name_file(&option);
	if (option.files)
		display_reg(&option);
	option.in_rec = 1;
	while (option.dir)
	{
		display_infos(&option);
	}
	free_option(&option);
	return (ret);
}
