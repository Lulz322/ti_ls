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

void read_data(void)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat 	*buf;
	t_dirs *dirs;

	dirs = st.dirs;
	buf = malloc(sizeof(struct stat));
	while (dirs)
	{
		if ((dir = opendir(dirs->name)) == NULL)
		{
			ft_printf("MRED(%s isnt a folder!)\n", dirs->name);
			dirs = dirs->next;
		}
		else
		{
			printf("contents of '%s' :\n", dirs->name);
			while (st.dirs && dir && dirs && (entry = readdir(dir)) != NULL)
			{
				stat(entry->d_name, buf);
				printf("%ld\n", buf->st_nlink);
				add_file(&dirs->files, entry->d_name, buf);
			}
			closedir(dir);
			print_files(dirs->files);
			dirs = dirs->next;
		}
  }
}
