/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:22:23 by iruban            #+#    #+#             */
/*   Updated: 2019/10/07 16:22:25 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "stdlib.h"
# include <dirent.h>
# include <sys/stat.h>

/*
**#include <sys/sysmacros.h>
*/

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <inttypes.h>
# include <sys/types.h>

/*
** BONUSES
*/
# include <sys/acl.h>
# include <sys/xattr.h>

# include "../libft/includes/ft_printf.h"
# define _ERROR(ex) {ft_printf("%s\n", ex);exit(0);}
# define _ERROR_MALLOC(ex) if(!(ex)) {_ERROR("ERROR IN ALLOCATION MEMMORY")};

enum	e_bool { false, true };

# define _BOOL	typedef enum e_bool bool

_BOOL;

typedef	struct		s_cvarss
{
	bool			flag_l;
	bool			flag_a;
	bool			flag_r_big;
	bool			flag_r;
	bool			flag_t;
	bool			flag_h;
}					t_cvarss;

typedef struct		s_files
{
	char			*f_name;
	char			flags[11];
	nlink_t			links;
	char			*uid;
	char			*gid;
	char			*size;
	off_t			real_size;
	long			all_time;
	long			major;
	long			minor;
	char			*time;
	bool			is_dir;
	bool			is_perm;
	bool			is_dev;
	struct s_files	*next;
}					t_files;

typedef struct		s_dirs
{
	char			*name;
	t_files			*files;
	blkcnt_t		total;
	bool			is_mm;
	struct s_dirs	*next;
}					t_dirs;

typedef struct		s_gen
{
	t_dirs			*dirs;
	t_cvarss		cv;
	bool			is_name;
}					t_gen;

t_gen g_gen;
void				read_data();
void				add_elem(t_dirs **list, char *str);
void				print_list(t_dirs *list);
void				del_elem(t_dirs **list, t_dirs *elem);
void				mode_to_letters(int mode, char *str, char *way);
void				add_file(t_files **list, char *str,
					struct stat *buf, char *way);
void				bytes(off_t number, char size[4]);
char				*printsize(size_t	size);
void				add_beetween(t_dirs **list, char *str, bool a);
bool				is_dir(char *dirname);
bool				check_permission(char *dirname);
t_files				*sort_list_by_names (t_files *list);
t_dirs				*sort_dirs_by_names(t_dirs *dirs);
void				del_files(t_files **files);
void				add_name(t_files **list, char *str);
void				del_file(t_files **pzdc);
t_dirs				*split_head_dirs(t_dirs *dirs);
t_files				*split_head_files(t_files *files);
void				split_other_files(t_files *files);
t_dirs				*sort_dirs_by_time(t_dirs *dirs);
void				split_other_dirs(t_dirs *dirs);
t_files				*sort_list_by_time(t_files *files);
int					tty(int max_size);
void				check_bits_suid(int mode, char *str);
void				check_bits_sgid(int mode, char *str);
void				check_bits_t(int mode, char *str);
bool				check_ea(char *str);
bool				check_acl(char *str);
int					nbr_len(unsigned int nbr);
int					prepare_names(t_files *files, int what);
void				check_majors(t_files *tmp);
void				del_files(t_files **files);
int					nbr_len(unsigned int nbr);
int					is_file(char *filename, t_files **argc);
void				print_size_first(t_files *tmp, int array[9],
					char str[1024]);
void				print_size_second(t_files *tmp, int array[9],
					char str[1024]);
void				print_size(int array[9], t_files *tmp, char str[1024]);
void				add_link(t_files *elem, char *way);
t_files				*create_file_name(char *str);
void				add_name(t_files **list, char *str);
void				add_file(t_files **list, char *str,
					struct stat *buf, char *way);
void				del_file(t_files **pzdc);
char				*ft_strndup(const char *s1, size_t n);
char				*privet_first(char *qqq, char *str);
char				*privet_second(char *qqq, char *str);
char				*privet(char *str, long all_time);
char				*pars_data(char *str, long all_time);
t_files				*create_file(char *str, struct stat *buff, char *way);
t_files				*add_files_to_list(DIR *dir, t_dirs *dirs);
void				check_r_flag(t_files *files, t_dirs *dirs);
void				set_files(t_dirs *dirs, struct dirent *entry);
DIR					*open_dir(char *dirname, t_dirs *dirs);
void				set_tmp(char tmp[1025], char *name, char *f_name);
void				errrorrororo(void);
void				parsing_argc(int argc, char **argv);
void				parsing_dirs(int argc, char **argv, int i);
void				check_dirs(t_dirs *dirs);
/*
** PRINT
*/
void				print_files(t_files *list, t_dirs *dirs);
void				check_file_flags(t_files *tmp, int array);
void				prepare_to_print(t_files *files, int array[9]);
bool				print_long_files(t_files *list, int array[9], bool test);
bool				print_tty(t_files *tmp, int array[9]);
void				print_total(long i);
void				print_f_name(char *str, int i);
void				print_size(int array[9], t_files *tmp, char str[1024]);
void				to_array(int i, char tmp[1024], char *flag, bool minus);
#endif
