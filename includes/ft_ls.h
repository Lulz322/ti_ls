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
typedef struct	s_dirs
{
	char *name;
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
#endif
