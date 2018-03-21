/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:22:56 by barbara           #+#    #+#             */
/*   Updated: 2018/03/21 11:59:34 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <stdlib.h>
#include "libft.h"

#define RED "\033[1;31m"
#define EOC "\033[0m"

typedef struct		s_dir
{
	char			*name;
	struct s_dir	*next;
}					t_dir;

typedef enum		e_bool
{FALSE, TRUE}		t_bool;

typedef struct		s_option
{
	t_dir			*dir;
	t_bool			r;
	t_bool			l;
	t_bool			rec;
	t_bool			a;
	t_bool			rev;
	t_bool			t;
}					t_option;

void				parsing(int argc, char **argv, t_option *option);
void				option_full_name(char *str, t_option *option);
void				option_short_name(char *str, t_option *option);
void				dir_name(char *str, t_option *option);
void				free_option(t_option *option);
void				display_help(t_option *option) __attribute__((noreturn));
void				error_option(t_option *option, char *str) __attribute__((noreturn));
void				error_malloc(t_option *option) __attribute__((noreturn));

#endif