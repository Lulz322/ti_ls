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
 #include <pwd.h>
 #include <grp.h>
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
}				t_cvarss;

typedef struct s_files
{
	char *f_name;
	char flags[11];
	__nlink_t links; //unsigned int
	char *UID;
	char *GID;
	char *size;
	struct timespec all_time;
	char *time;
	bool is_dir;
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
}				t_gen;

t_gen g_gen;
void read_data();
void add_elem(t_dirs **list, char *str);
void print_list(t_dirs *list);
void del_elem(t_dirs **list, t_dirs *elem);
void mode_to_letters(int mode,char *str);
void add_file(t_files **list, char *str, struct stat *buf, char *way);
void print_files(t_files *list);
void bytes(off_t number, char size[4]);
char *printsize(size_t  size);
void add_beetween(t_dirs **list, char *str, bool a);
bool	is_dir(char *dirname);
t_files *sort_list_by_names (t_files *list);
#endif
