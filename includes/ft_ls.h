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

t_cvarss g_flags;
void read_data();
#endif
