/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:09:09 by iruban            #+#    #+#             */
/*   Updated: 2019/10/07 16:09:10 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

int		tty(int max_size)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	if (max_size == 0)
		return (w.ws_col - 1);
	return ((w.ws_col / (max_size + 1)));
}

void	set_all_true(t_files *tmp)
{
	t_files *start;

	start = tmp;
	while (start)
	{
		start->is_dev = true;
		start = start->next;
	}
}

void	check_majors(t_files *tmp)
{
	t_files *start;

	start = tmp;
	while (start)
	{
		if (start->flags[0] == 'c' || start->flags[0] == 'b')
		{
			set_all_true(tmp);
			return ;
		}
		start = start->next;
	}
}
