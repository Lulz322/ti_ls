/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:42:13 by iruban            #+#    #+#             */
/*   Updated: 2019/03/27 16:55:22 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "stdlib.h"
# include <dirent.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 //#include <sys/sysmacros.h>
 #include <pwd.h>
 #include <grp.h>
 #include <time.h>
 #include <inttypes.h>
# include "../libft/includes/ft_printf.h"
#define _ERROR(ex) {ft_printf("%s\n", ex);exit(0);}
# define _ERROR_MALLOC(ex) if(!(ex)) {_ERROR("ERROR IN ALLOCATION MEMMORY")};
# define g_gen st

enum	e_bool { false, true };

# define _BOOL	typedef enum e_bool bool

_BOOL;

typedef struct s_cvarss
{
	bool flag_l;
	bool flag_a;
	bool flag_R;
	bool flag_r;
	bool flag_t;
	bool flag_h;
}				t_cvarss;

typedef struct s_files
{
	char *f_name;
	char flags[11];
	nlink_t links; //unsigned int
	char *UID;
	char *GID;
	char *size;
	off_t real_size;
	long all_time;
	long major;
	long minor;
	char *time;
	bool is_dir;
	bool is_perm;
	bool is_dev;
	struct s_files *next;
}t_files;

typedef struct	s_dirs
{
	char *name;
	t_files *files;
	blkcnt_t total;
	struct s_dirs *next;
}				t_dirs;

typedef struct s_gen
{
	t_dirs *dirs;
	t_cvarss cv;
	bool is_name;
}				t_gen;

t_gen g_gen;
void read_data();
void add_elem(t_dirs **list, char *str);
void print_list(t_dirs *list);
void del_elem(t_dirs **list, t_dirs *elem);
void mode_to_letters(int mode,char *str);
void add_file(t_files **list, char *str, struct stat *buf, char *way);
void print_files(t_files *list, t_dirs *dirs);
void bytes(off_t number, char size[4]);
char *printsize(size_t  size);
void add_beetween(t_dirs **list, char *str, bool a);
bool	is_dir(char *dirname);
bool 	check_permission(char *dirname);
t_files *sort_list_by_names (t_files *list);
t_dirs *sort_dirs_by_names(t_dirs *dirs);
void del_files(t_files **files);
void add_name(t_files **list, char *str);
void del_file(t_files **pzdc);
t_dirs *split_head_dirs(t_dirs *dirs);
t_files		*split_head_files(t_files *files);
void				split_other_files(t_files *files);
t_dirs *sort_dirs_by_time(t_dirs *dirs);
void				split_other_dirs(t_dirs *dirs);
t_files		*sort_list_by_time(t_files *files);

#endif
