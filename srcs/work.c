#include "../includes/ft_ls.h"

void read_data(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_dirs *dirs;

	dirs = st.dirs;
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
				printf("%s  | %lu\n",entry->d_name, entry->d_ino);
			closedir(dir);
			dirs = dirs->next;
		}
  }
}
