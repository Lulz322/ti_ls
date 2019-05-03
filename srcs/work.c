#include "../includes/ft_ls.h"

/*
struct stat {
	dev_t     st_dev;          ID of device containing file
	ino_t     st_ino;          Inode number
	mode_t    st_mode;         File type and mode
	nlink_t   st_nlink;        Number of hard links
	uid_t     st_uid;          User ID of owner
	gid_t     st_gid;          Group ID of owner
	dev_t     st_rdev;         Device ID (if special file)
	off_t     st_size;         Total size, in bytes
	blksize_t st_blksize;      Block size for filesystem I/O
	blkcnt_t  st_blocks;       Number of 512B blocks allocated

	 Since Linux 2.6, the kernel supports nanosecond
	   precision for the following timestamp fields.
	   For the details before Linux 2.6, see NOTES.

	struct timespec st_atim;   Time of last access
	struct timespec st_mtim;   Time of last modification
	struct timespec st_ctim;   Time of last status change

#define st_atime st_atim.tv_sec       Backward compatibility
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
*/

// 1 -> | 2->nlinks 3->

bool	is_dir(char *dirname)
{
	DIR	*dir;

	if ((dir = opendir(dirname)) && !closedir(dir))
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

t_files *add_files_to_list(DIR *dir, t_dirs *dirs)
{
	struct stat 	buf;
	struct dirent	*entry;
	char tmp[1025];

	ft_bzero(tmp, 1025);
	while (dir && (entry = readdir(dir)) != NULL)
	{
		if (!st.cv.flag_a)
		{
			if (entry->d_name[0] != '.')
			{
				set_tmp(tmp, dirs->name, entry->d_name);
				lstat(tmp, &buf);
				dirs->total += buf.st_blocks;
				add_file(&dirs->files, entry->d_name, &buf, tmp);
				ft_bzero(tmp, 1025);
			}
		}
		else
			{
				set_tmp(tmp, dirs->name, entry->d_name);
				lstat(tmp, &buf);
				dirs->total += buf.st_blocks;
				add_file(&dirs->files, entry->d_name, &buf, tmp);
				ft_bzero(tmp, 1025);
			}
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

void read_data(void)
{
	DIR				*dir;
	char *q;
	t_dirs *del_me;
	t_dirs *dirs;

	dirs = st.dirs;
	if (dirs && dirs->next)
		st.is_name = true;
	while (dirs)
	{
		dir = opendir(dirs->name);
		if (st.is_name || st.cv.flag_R)
			ft_printf("%s:\n", dirs->name);
		dirs->files = add_files_to_list(dir, dirs);
		dirs->files = sort_list_by_names(dirs->files);
		if (st.cv.flag_R)
			check_R_flag(dirs->files, dirs);
		q = printsize(dirs->total);
		if(st.cv.flag_l)
			ft_printf("total %s\n", q);
		free(q);
		closedir(dir);
		print_files(dirs->files);
		if (dirs->next)
			ft_printf("\n");
		del_me = dirs;
		dirs = dirs->next;
		del_elem(&st.dirs, del_me);
  	}
}
