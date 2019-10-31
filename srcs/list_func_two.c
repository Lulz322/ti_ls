/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:05:49 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:05:50 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*get_user(uid_t uid)
{
	struct passwd *pws;

	pws = getpwuid(uid);
	if (pws)
		return (pws->pw_name);
	return ("?");
}

char	*get_group(gid_t gid)
{
	struct group *pws;

	pws = getgrgid(gid);
	if (pws)
		return (pws->gr_name);
	return ("?");
}

void	mode_to_letters_two(char *str, int mode)
{
	if (mode & S_IRGRP)
		str[4] = 'r';
	if (mode & S_IWGRP)
		str[5] = 'w';
	if (mode & S_IXGRP)
		str[6] = 'x';
	check_bits_sgid(mode, str);
	if (mode & S_IROTH)
		str[7] = 'r';
	if (mode & S_IWOTH)
		str[8] = 'w';
	check_bits_t(mode, str);
}

void	mode_to_letters(int mode, char *str, char *path)
{
	strcpy(str, "---------- ");
	if (S_ISDIR(mode))
		str[0] = 'd';
	if (S_ISCHR(mode))
		str[0] = 'c';
	if (S_ISBLK(mode))
		str[0] = 'b';
	if (S_ISLNK(mode))
		str[0] = 'l';
	if (mode & S_IRUSR)
		str[1] = 'r';
	if (mode & S_IWUSR)
		str[2] = 'w';
	if (mode & S_IXUSR)
		str[3] = 'x';
	check_bits_suid(mode, str);
	if (check_acl(path))
		str[10] = '+';
	if (check_ea(path))
		str[10] = '@';
	mode_to_letters_two(str, mode);
}

t_files	*create_file(char *str, struct stat *buff, char *way)
{
	t_files *elem;

	_ERROR_MALLOC(elem = (t_files *)malloc(sizeof(t_files)));
	ft_bzero(elem, sizeof(t_files));
	elem->f_name = ft_strdup(str);
	elem->is_dir = is_dir(way);
	mode_to_letters(buff->st_mode, elem->flags, way);
	elem->all_time = (long)buff->st_mtime;
	if (g_gen.cv.flag_l)
	{
		if (elem->flags[0] == 'l')
			add_link(elem, way);
		elem->links = buff->st_nlink;
		elem->uid = ft_strdup(get_user(buff->st_uid));
		elem->gid = ft_strdup(get_group(buff->st_gid));
		elem->time = pars_data(ctime(&elem->all_time), elem->all_time);
		elem->size = printsize(buff->st_size);
		elem->real_size = (long long)buff->st_size;
		elem->major = (long)major(buff->st_rdev);
		elem->minor = (long)minor(buff->st_rdev);
	}
	elem->next = NULL;
	return (elem);
}
