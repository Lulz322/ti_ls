/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:08:59 by iruban            #+#    #+#             */
/*   Updated: 2019/10/07 16:09:02 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

bool		check_permission(char *dirname)
{
	struct stat	buf;

	if (!lstat(dirname, &buf) && S_ISDIR(buf.st_mode)
	&& (!(buf.st_mode & S_IRUSR)
	|| !(buf.st_mode & S_IXUSR)))
		return (false);
	return (true);
}

DIR			*open_dir(char *dirname, t_dirs *dirs)
{
	DIR *dir;

	if (is_dir(dirname) && check_permission(dirname))
		return (dir = opendir(dirname));
	else
		ft_printf("MRED(ft_ls: %s Permission denied)\n", dirs->name);
	return (NULL);
}

bool		is_dir(char *dirname)
{
	struct stat	buf;

	if (!lstat(dirname, &buf) && S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}

void		set_tmp(char tmp[1025], char *name, char *f_name)
{
	int i;

	i = 0;
	while (name[i])
		i++;
	ft_strcat(tmp, name);
	if (name[i - 1] != '/')
		ft_strcat(tmp, "/");
	ft_strcat(tmp, f_name);
}

void		set_files(t_dirs *dirs, struct dirent *entry)
{
	struct stat	buf;
	char		tmp[1025];

	ft_bzero(tmp, 1025);
	set_tmp(tmp, dirs->name, entry->d_name);
	if (lstat(tmp, &buf) != -1)
	{
		lstat(tmp, &buf);
		add_file(&dirs->files, entry->d_name, &buf, tmp);
		dirs->total += buf.st_blocks;
	}
	else
		add_name(&dirs->files, entry->d_name);
	ft_bzero(tmp, 1025);
}
