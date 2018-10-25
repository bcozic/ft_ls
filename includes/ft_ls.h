/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:22:56 by barbara           #+#    #+#             */
/*   Updated: 2018/10/24 21:11:30 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct timespec	t_time;

typedef struct			s_file
{
	char				*name;
	struct stat			stat;
	size_t				max_size;
	char				right[16];
	char				*user_name;
	char				*grp_name;
	char				*link;
	struct s_file		*next;
}						t_file;

typedef enum			e_bool
{T_FALSE = 0, T_TRUE}		t_bool;

typedef struct			s_option
{
	t_file				*dir;
	t_file				*files;
	t_file				*no_found;
	t_file				*next_dir;
	char				*path;
	int					*ret;
	t_bool				l;
	t_bool				rec;
	t_bool				a;
	t_bool				rev;
	t_bool				t;
	t_bool				col;
	int					first;
	int					first_file;
	int					first_dir;
	struct winsize		size_term;
	int					nb_files;
	size_t				max_size_name;
	int					size_usr;
	int					size_grp;
	int					file_per_line;
	int					nb_lines;
	int wait;
	int					current_line;
	int					in_rec;
	int					max_size_size;
	int					size_links;
	char				no_link[4];
	size_t				dir_size;
}						t_option;

void					parsing(int argc, char **argv, t_option *option);
void					pars_file(char *str, t_option *option);
void					option_full_name(char *str, t_option *option);
void					option_short_name(char *str, t_option *option);
t_file					*insert_name(char *str, t_option *option,
							t_file **list);
t_file					*insert_time(char *str, t_option *option,
							t_file **list, t_time time);
int						cmp_time(t_time time1, t_time time2, t_option *option);
int						cmp_name(char *name1, char *name2, t_option *option);
t_file					*add_file(t_file *current, char *str, t_option *option,
							t_file **list);
void					free_option(t_option *option);
void					remov_file(t_file **file, t_option *option);
void					remov_dir(t_file *dir, t_option *option);
void					reset_size(t_option *option);
void					error_option(t_option *option,
							char *str) __attribute__((noreturn));
void					err_malloc(t_option *option) __attribute__((noreturn));
void					other_err(t_option *option) __attribute__((noreturn));
void					error_rights(t_file *file, t_option *option);
void					error_name_file(t_option *option);
void					display_no_l(t_file *file, t_option *option);
void					display_l(t_file *file, t_option *option);
void					display_reg(t_option *option);
void					display_infos(t_option *option);
char					*pad_time(t_file *file);
void					padd_name(t_option *option);
void					get_files(t_option *option, DIR *dir);
void					get_l_infos(t_option *option, t_file *file,
							struct stat buff);
void					add_file_lst(t_option *option, char *str,
							struct stat buff, char *all_path);
void					add_data(t_option *option, t_file *file,
							struct stat buff, char *all_path);
t_file					*init_new_file(char *str, t_option *option,
							t_file **list, struct stat *buff);
							t_bool		is_file_next(t_file *file, int nb);

#endif
