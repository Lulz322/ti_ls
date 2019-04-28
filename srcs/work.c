#include "../includes/ft_ls.h"

void read_data()
{
	DIR				*dir;
	struct dirent	*entry;
	t_dirs *dirs;

	dirs = st.dirs;
	while (dirs)
	{
		if ((dir = opendir(dirs->name)) == NULL)
		{
			_ERROR("opendir() error");
		}
		else
		 	printf("contents of root:");
		while ((entry = readdir(dir)) != NULL)
			printf("  %s\n", entry->d_name);
		closedir(dir);
		dirs = dirs->next;
  }
}
