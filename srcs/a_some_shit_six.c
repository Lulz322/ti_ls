/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_some_shit_six.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:12:15 by iruban            #+#    #+#             */
/*   Updated: 2019/10/07 16:12:16 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files			*add_files_to_list(DIR *dir, t_dirs *dirs)
{
	struct dirent	*entry;

	while (dir && (entry = readdir(dir)) != NULL)
	{
		if (!g_gen.cv.flag_a)
		{
			if (entry->d_name[0] != '.')
				set_files(dirs, entry);
		}
		else
			set_files(dirs, entry);
	}
	return (dirs->files);
}

void			check_r_flag(t_files *files, t_dirs *dirs)
{
	t_files	*tmp;
	char	path[1025];

	tmp = files;
	ft_bzero(path, 1025);
	while (tmp)
	{
		if (tmp->is_dir && tmp->flags[0] != 'l' && !ft_strequ(tmp->f_name, "..")
			&& !ft_strequ(tmp->f_name, "."))
		{
			set_tmp(path, dirs->name, tmp->f_name);
			add_beetween(&dirs, path, 0);
			ft_bzero(path, 1025);
		}
		tmp = tmp->next;
	}
	add_beetween(&dirs, path, 1);
	ft_bzero(path, 1025);
}

t_files			*all_operations(t_files *files, DIR *dir, t_dirs *dirs)
{
	files = add_files_to_list(dir, dirs);
	if (g_gen.cv.flag_t)
		files = sort_list_by_time(dirs->files);
	else
		files = sort_list_by_names(dirs->files);
	if (g_gen.cv.flag_r_big)
		check_r_flag(files, dirs);
	return (files);
}

void			read_data(void)
{
	DIR				*dir;
	t_dirs			*del_me;
	t_dirs			*dirs;

	dirs = g_gen.dirs;
	while (dirs)
	{
		if ((dir = open_dir(dirs->name, dirs)))
		{
			if ((g_gen.is_name || g_gen.cv.flag_r_big))
				ft_printf("%s:\n", dirs->name);
			dirs->files = all_operations(dirs->files, dir, dirs);
			closedir(dir);
			check_majors(dirs->files);
			print_files(dirs->files, dirs);
		}
		if (dirs->next)
			ft_printf("\n");
		del_me = dirs;
		dirs = dirs->next;
		del_elem(&g_gen.dirs, del_me);
	}
}
