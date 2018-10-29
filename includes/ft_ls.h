/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:22:56 by barbara           #+#    #+#             */
/*   Updated: 2018/10/29 20:21:27 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define SEC_IN_SIX_MONTH		15778463

# define ALL_EXCEPT				0x1
# define FORCE_COLOMN			0x2
# define RECURSIVE				0x4
# define SORT_SIZE				0x8
# define SORT_FILE_CREATION		0x10
# define ALL					0x20
# define SORT_STATUS_CHANGED	0x40
# define DIRECTORY_LIST			0x80
# define NO_SORT				0x100
# define DISP_GRP_NAME			0x200
# define INODE_NUMBER			0x400
# define LONG_LIST_FORMAT		0x800
# define REVERS					0x1000
# define SORT_TIME				0x2000
# define SORT_LST_ACCESS		0x4000
# define COLOMN					0x8000

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
	char				*full_name;
	struct stat			stat;
	struct timespec		time;
	size_t				max_size;
	char				right[16];
	char				*user_name;
	char				*grp_name;
	char				*link;
	struct s_file		*next;
}						t_file;

typedef enum			e_bool
{T_FALSE = 0, T_TRUE}	t_bool;

typedef struct			s_option
{
	t_file				*dir;
	t_file				*files;
	t_file				*no_found;
	t_file				*next_dir;
	char				*path;
	int					*ret;
	uint32_t			flag;
	int					first;
	int					first_dir;
	int					nb_files;
	int					size_usr;
	int					size_grp;
	int					nb_lines;
	int					in_rec;
	int					max_size_size;
	int					size_links;
	int					size_inode;
	char				no_link[4];
	struct winsize		size_term;
	size_t				max_size_name;
	size_t				dir_size;
}						t_option;

void					parsing(int argc, char **argv, t_option *option);
void					pars_file(char *str, t_option *option);
t_file					*insert_name(char *str, t_option *option,
							t_file **list);
t_file					*insert_time(char *str, t_option *option,
							t_file **list, t_time time_spec);
t_file					*insert_size(char *str, t_option *option, t_file **list,
							struct stat *buff);
t_file					*insert_end(char *str, t_option *option, t_file **list);
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
void					display_reg(t_option *option);
void					display_infos(t_option *option);
char					*pad_time(t_file *file);
void					padd_name(t_option *option);
void					get_files(t_option *option, DIR *dir);
void					get_l_infos(t_option *option, t_file *file,
							struct stat buff);
void					add_file_lst(t_option *option, char *str,
							struct stat *buff, char *all_path);
void					add_data(t_option *option, t_file *file,
							struct stat *buff, char *all_path);
void					find_rights(struct stat buff, t_file *file);
void					display_col(t_file *file, t_option *option);
int						cmp_name(char *name1, char *name2, t_option *option);

#endif
