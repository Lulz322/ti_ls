/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_some_shit_five.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:38:18 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:38:19 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		is_file(char *filename, t_files **argc)
{
	struct stat buf;

	if (lstat(filename, &buf))
		return (0);
	else
		add_file(argc, filename, &buf, filename);
	return (1);
}

t_dirs	*read_argc(t_files *files, t_dirs *dirs)
{
	if (files)
	{
		if (g_gen.cv.flag_t)
			files = sort_list_by_time(files);
		files = sort_list_by_names(files);
		print_files(files, dirs);
		del_files(&files);
		if (dirs)
			ft_printf("\n");
	}
	return (dirs);
}

void	check_bits_sgid(int mode, char *str)
{
	if (mode & S_IXGRP)
	{
		if (mode & S_ISGID)
			str[6] = 's';
		else
			str[6] = 'x';
	}
	else
	{
		if (mode & S_ISGID)
			str[6] = 'S';
	}
}

void	check_bits_suid(int mode, char *str)
{
	if (mode & S_IXUSR)
	{
		if (mode & S_ISUID)
			str[3] = 's';
		else
			str[3] = 'x';
	}
	else
	{
		if (mode & S_ISUID)
			str[6] = 'S';
	}
}

void	check_dirs(t_dirs *dirs)
{
	t_dirs	*tmp;
	t_files	*argc;

	argc = NULL;
	tmp = dirs;
	if (dirs && dirs->next)
		g_gen.is_name = true;
	while (tmp)
	{
		if (!is_dir(tmp->name))
		{
			if (!is_file(tmp->name, &argc))
			{
				ft_printf("MRED(ft_ls: %s isnt a folder/file!)\n", tmp->name);
				del_elem(&dirs, tmp);
			}
			else
				del_elem(&dirs, tmp);
		}
		tmp = tmp->next;
	}
	g_gen.dirs = read_argc(argc, dirs);
}
