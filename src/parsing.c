/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:19:49 by barbara           #+#    #+#             */
/*   Updated: 2018/04/28 18:57:51 by bcozic           ###   ########.fr       */
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
		if (!ft_strncmp(argv[i], "--", 2))
			option_full_name(argv[i], option);
		else if (argv[i][0] == '-' && argv[i][1])
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

void	option_full_name(char *str, t_option *option)
{
	if (!ft_strcmp(str, "--recursive"))
		option->rec = TRUE;
	else if (!ft_strcmp(str, "--all"))
		option->a = TRUE;
	else if (!ft_strcmp(str, "--reverse"))
		option->rev = TRUE;
	else if (!ft_strcmp(str, "--help"))
		disp_help(option);
	else
		error_option(option, str);
}

void	option_short_name(char *str, t_option *option)
{
	while (*(++str))
		if (*str == 'l')
			option->l = TRUE;
		else if (*str == 'R')
			option->rec = TRUE;
		else if (*str == 'a')
			option->a = TRUE;
		else if (*str == 'r')
			option->rev = TRUE;
		else if (*str == 't')
			option->t = TRUE;
		else if (*str == '1')
		{
			option->col = TRUE;
			option->l = FALSE;
		}
		else
			error_option(option, str);
}
