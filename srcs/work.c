#include "../includes/ft_ls.h"

bool 	check_permission(char *dirname)
{
	struct stat 	buf;

	if (!lstat(dirname, &buf) && S_ISDIR(buf.st_mode) && (!(buf.st_mode & S_IRUSR) || !(buf.st_mode & S_IXUSR)))
		return (false);
	return (true);
}

DIR *open_dir(char *dirname, t_dirs *dirs)
{
	DIR *dir;
	if (is_dir(dirname) && check_permission(dirname))
		return (dir = opendir(dirname));
	else
		ft_printf("MRED(ft_ls: %s Permission denied)\n", dirs->name);
	return (NULL);
}

bool	is_dir(char *dirname)
{
	struct stat 	buf;

	if (!lstat(dirname, &buf) && S_ISDIR(buf.st_mode))
			return (true);
	return (false);
}

void set_tmp(char tmp[1025], char *name, char *f_name) {
	int i;

	i = 0;
	while (name[i])
		i++;
	ft_strcat(tmp, name);
	if (name[i - 1] != '/')
		ft_strcat(tmp, "/");
	ft_strcat(tmp, f_name);
}
void set_files(t_dirs *dirs, struct dirent *entry)
{
	struct stat buf;
	char tmp[1025];

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


t_files *add_files_to_list(DIR *dir, t_dirs *dirs)
{
	struct dirent	*entry;

	while (dir && (entry = readdir(dir)) != NULL)
	{
		if (!st.cv.flag_a)
		{
			if (entry->d_name[0] != '.')
				set_files(dirs, entry);
		}
		else
			set_files(dirs, entry);
	}
	return(dirs->files);
}

void check_R_flag(t_files *files, t_dirs *dirs)
{
	t_files *tmp;
	char path[1025];

	tmp = files;
	ft_bzero(path, 1025);
	while (tmp)
	{
		if (tmp->is_dir && tmp->flags[0] != 'l' &&!ft_strequ(tmp->f_name, "..")
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

t_files *all_operations(t_files *files, DIR *dir, t_dirs *dirs)
{
	files = add_files_to_list(dir, dirs);
	if (st.cv.flag_t)
		files = sort_list_by_time(dirs->files);
	else
		files = sort_list_by_names(dirs->files);
	if (st.cv.flag_R)
		check_R_flag(files, dirs);
	return (files);
}

void read_data(void)
{
	DIR				*dir;
	t_dirs *del_me;
	t_dirs *dirs;

	dirs = st.dirs;
	while (dirs)
	{
		if ((dir = open_dir(dirs->name, dirs)))
		{
			if ((st.is_name || st.cv.flag_R))
				ft_printf("%s:\n", dirs->name);
			dirs->files = all_operations(dirs->files, dir, dirs);
			closedir(dir);
			print_files(dirs->files, dirs);
		}
		if (dirs->next)
			ft_printf("\n");
		del_me = dirs;
		dirs = dirs->next;
	//	del_elem(&st.dirs, del_me);
  	}
}
