/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:19:49 by barbara           #+#    #+#             */
/*   Updated: 2018/11/15 18:40:06 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		err_no_name(t_option *option)
{
	write(2, "./ft_ls: fts_open: No such file or directory\n", 45);
	free_option(option);
	exit(1);
}

static int	short_name_part1(char *str, t_option *option)
{
	if (*str == 'A')
		option->flag |= ALL_EXCEPT;
	else if (*str == 'C')
		option->flag = (option->flag | FORCE_COLOMN)
				& (0xFFFFFFFF ^ (LONG_LIST_FORMAT | COLOMN));
	else if (*str == 'R')
		option->flag |= RECURSIVE;
	else if (*str == 'S')
		option->flag |= SORT_SIZE;
	else if (*str == 'U')
		option->flag = (option->flag | SORT_FILE_CREATION)
				& (0xFFFFFFFF ^ (SORT_LST_ACCESS | SORT_STATUS_CHANGED));
	else if (*str == 'a')
		option->flag |= ALL;
	else if (*str == 'c')
		option->flag = (option->flag | SORT_STATUS_CHANGED)
				& (0xFFFFFFFF ^ (SORT_FILE_CREATION | SORT_LST_ACCESS));
	else if (*str == 'd')
		option->flag |= DIRECTORY_LIST;
	else
		return (0);
	return (1);
}

static int	short_name_part2(char *str, t_option *option)
{
	if (*str == 'f')
		option->flag |= (NO_SORT | ALL);
	else if (*str == 'g')
		option->flag |= (DISP_GRP_NAME | LONG_LIST_FORMAT);
	else if (*str == 'i')
		option->flag |= INODE_NUMBER;
	else if (*str == 'l')
		option->flag |= LONG_LIST_FORMAT;
	else if (*str == 'r')
		option->flag |= REVERS;
	else if (*str == 't')
		option->flag |= SORT_TIME;
	else if (*str == 'u')
		option->flag = (option->flag | SORT_LST_ACCESS)
				& (0xFFFFFFFF ^ (SORT_FILE_CREATION | SORT_STATUS_CHANGED));
	else if (*str == '1')
		option->flag = (option->flag | COLOMN)
				& (0xFFFFFFFF ^ (LONG_LIST_FORMAT | FORCE_COLOMN));
	else
		return (0);
	return (1);
}

static void	option_short_name(char *str, t_option *option)
{
	while (*(++str))
		if (short_name_part1(str, option))
			continue ;
		else if (short_name_part2(str, option))
			continue ;
		else
			error_option(option, str);
}

void		parsing(int argc, char **argv, t_option *option)
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
	{
		if (!argv[i][0])
			err_no_name(option);
		pars_file(argv[i++], option);
	}
}
