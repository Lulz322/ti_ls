/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:39:33 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:39:34 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int			check_split_dirs(t_dirs *dirs)
{
	if (dirs && dirs->next)
	{
		if (!g_gen.cv.flag_r)
		{
			if (ft_strcmp(dirs->name, dirs->next->name) > 0)
				return (1);
		}
		else
		{
			if (-ft_strcmp(dirs->name, dirs->next->name) > 0)
				return (1);
		}
	}
	return (0);
}

static bool			is_swap(t_dirs *dirs)
{
	struct stat buf1;
	struct stat buf2;

	if (dirs && dirs->next)
	{
		lstat(dirs->name, &buf1);
		lstat(dirs->next->name, &buf2);
		if (!g_gen.cv.flag_r)
		{
			if ((long)buf1.st_mtime < (long)buf2.st_mtime)
				return (true);
		}
		else
		{
			if ((long)buf1.st_mtime > (long)buf2.st_mtime)
				return (true);
		}
	}
	return (false);
}

t_dirs				*sort_dirs_by_time(t_dirs *dirs)
{
	t_dirs			*start;
	size_t			i;

	i = 1;
	while (i && !(i = 0))
		if (is_swap(dirs) && ++i)
			dirs = split_head_dirs(dirs);
		else
		{
			start = dirs;
			while (start)
			{
				if (is_swap(start->next) && ++i)
					split_other_dirs(start);
				start = start->next;
			}
		}
	return (dirs);
}

t_dirs				*sort_dirs_by_names(t_dirs *dirs)
{
	t_dirs			*start;
	size_t			i;

	i = 1;
	while (i && !(i = 0))
		if (check_split_dirs(dirs) && ++i)
			dirs = split_head_dirs(dirs);
		else
		{
			start = dirs;
			while (start)
			{
				if (check_split_dirs(start->next) && ++i)
					split_other_dirs(start);
				start = start->next;
			}
		}
	return (dirs);
}
