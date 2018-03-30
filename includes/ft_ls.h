/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:22:56 by barbara           #+#    #+#             */
/*   Updated: 2018/03/30 18:50:16 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "libft.h"

#define RED "\033[1;31m"
#define EOC "\033[0m"

typedef struct		s_file
{
	char			*name;
	struct stat		stat;
	size_t			max_size;
	char			right[16];
	char			*user_name;
	char			*grp_name;
	struct s_file	*next;
}					t_file;

typedef enum		e_bool
{FALSE = 0, TRUE}		t_bool;

typedef struct		s_option
{
	t_file			*dir;
	t_file			*files;
	char			*path;
	t_bool			l;
	t_bool			rec;
	t_bool			a;
	t_bool			rev;
	t_bool			t;
	struct winsize	size_term;
	int				nb_files;
	size_t			max_size_name;
	int				size_usr;
	int				size_grp;
	int				file_per_line;
	int				current_line;
	int				in_rec;
	int				max_size_size;
	int				size_links;
	int	rem;
	size_t			dir_size;
}					t_option;

void				parsing(int argc, char **argv, t_option *option);
void				pars_file(char *str, t_option *option);
void				option_full_name(char *str, t_option *option);
void				option_short_name(char *str, t_option *option);
t_file				*insert_name(char *str, t_option *option, t_file **list);
t_file				*insert_time(char *str, t_option *option, t_file **list, struct timespec time);
int					cmp_time(struct timespec time1, struct timespec time2, t_option *option);
int					cmp_name(char *name1, char *name2, t_option *option);
t_file				*add_file(t_file *current, char *str, t_option *option, t_file **list);
void				free_option(t_option *option);
void				remov_file(t_file **file);
void				reset_size(t_option *option);
void				display_help(t_option *option) __attribute__((noreturn));
void				error_option(t_option *option, char *str) __attribute__((noreturn));
void				error_malloc(t_option *option) __attribute__((noreturn));
void				error_name_file(char *str);
size_t				display_no_l(t_file *file, size_t size, t_option *option);
void				display_l(t_file *file, t_option *option);
void				display_reg(t_option *option);
void				display_infos(t_option *option);
char				*pad_time(t_file *file);
void				padd_name(t_option *option);

#endif
