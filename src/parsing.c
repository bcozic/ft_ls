/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:19:49 by barbara           #+#    #+#             */
/*   Updated: 2018/10/24 21:12:44 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parsing(int argc, char **argv, t_option *option)
{
	int				i;

	ioctl(0, TIOCGWINSZ, &(option->size_term));
	i = 0;
	while (++i < argc)
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
	}
	if (i == argc)
		pars_file(".", option);
	i--;
	while (++i < argc)
		pars_file(argv[i], option);
}

void	option_short_name(char *str, t_option *option)
{
	while (*(++str))
		if (*str == 'l')
			option->l = T_TRUE;
		else if (*str == 'R')
			option->rec = T_TRUE;
		else if (*str == 'a')
			option->a = T_TRUE;
		else if (*str == 'r')
			option->rev = T_TRUE;
		else if (*str == 't')
			option->t = T_TRUE;
		else if (*str == '1')
		{
			option->col = T_TRUE;
			option->l = T_FALSE;
		}
		else
			error_option(option, str);
}
