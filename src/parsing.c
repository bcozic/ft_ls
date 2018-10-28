/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:19:49 by barbara           #+#    #+#             */
/*   Updated: 2018/10/28 21:05:22 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parsing(int argc, char **argv, t_option *option)
{
	int				i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--") == 0)
		{
			i++;
			break ;
		}
		if (argv[i][0] == '-' && argv[i][1])
			option_short_name(argv[i], option);
		else
			break ;
		i++;
	}
	if (i == argc)
		pars_file(".", option);
	while (i < argc)
		pars_file(argv[i++], option);
}

void	option_short_name(char *str, t_option *option)
{
	while (*(++str))
		if (*str == 'l')
			option->flag |= LONG_LIST_FORMAT;
		else if (*str == 'g')
			option->flag |= (DISP_GRP_NAME | LONG_LIST_FORMAT);
		else if (*str == 'R')
			option->flag |= RECURSIVE;
		else if (*str == 'a')
			option->flag |= ALL;
		else if (*str == 'f')
			option->flag |= (NO_SORT | ALL);
		else if (*str == 'r')
			option->flag |= REVERS;
		else if (*str == 't')
			option->flag |= SORT_TIME;
		else if (*str == 'd')
			option->flag |= DIRECTORY_LIST;
		else if (*str == 'u')
			option->flag |= SORT_LST_ACCESS;
		else if (*str == 'U')
			option->flag |= SORT_FILE_CREATION;
		else if (*str == '1')
			option->flag = (option->flag | COLOMN) & (0xFFFFFFFF ^ LONG_LIST_FORMAT);
		else
			error_option(option, str);
}
