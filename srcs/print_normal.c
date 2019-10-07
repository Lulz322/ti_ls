/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:43:00 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:43:01 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#define QWE(str) {ft_printf(str);print_f_name(tmp->f_name, array[6]);}
#define OK {print_f_name(tmp->f_name, array[6]);ft_printf(" ");}

void			print_f_name(char *str, int i)
{
	int len;

	len = ft_strlen(str);
	ft_putstr(str);
	while (len++ < i)
		ft_putchar(' ');
}

void			check_file_flags(t_files *tmp, int array[7])
{
	char str[1024];

	to_array(array[6], str, "s", true);
	if (!tmp->is_perm || !g_gen.cv.flag_l)
	{
		if (tmp->flags[0] == 'd')
		{
			QWE("MCYN(%");
			ft_printf(" MCYN()%");
		}
		else if (ft_strequ("-rwxr-xr-x ", tmp->flags))
		{
			QWE("MRED(%");
			ft_printf(" MCYN()%");
		}
		else if (tmp->flags[0] == 'l')
		{
			QWE("MPRP(%");
			ft_printf(" MPRP()%");
		}
		else
			OK;
	}
}

unsigned int	max_name(t_files *tmp)
{
	t_files	*start;
	int		i;

	i = -1;
	start = tmp;
	while (start)
	{
		if (i < (int)ft_strlen(start->f_name))
			i = (int)ft_strlen(start->f_name);
		start = start->next;
	}
	return (i);
}

unsigned int	count_files(t_files *tmp)
{
	t_files	*start;
	int		i;

	i = -1;
	start = tmp;
	while (start)
	{
		++i;
		start = start->next;
	}
	return (i);
}

bool			print_tty(t_files *tmp, int array[9])
{
	t_files	*print;
	int		i;
	int		j;
	int		z;

	j = -1;
	i = -1;
	z = (int)(count_files(tmp) / tty(max_name(tmp))) + 1;
	while (++j < (int)(count_files(tmp) / tty(max_name(tmp))) + 1)
	{
		print = tmp;
		i = -1;
		while (++i < j)
			print = print->next;
		i = -1;
		while (print)
		{
			if (++i % z == 0)
				check_file_flags(print, array);
			print = print->next;
		}
		if (j + 1 < (int)(count_files(tmp) / tty(max_name(tmp))) + 1)
			ft_printf("\n");
	}
	return (true);
}
