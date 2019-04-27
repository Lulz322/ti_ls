#include "../includes/ft_ls.h"

void read_data()
{
	DIR *dir;
	struct dirent *entry;

if ((dir = opendir("/")) == NULL)
{
      	_ERROR("opendir() error");
}
else
 	printf("contents of root:");
 while ((entry = readdir(dir)) != NULL)
	printf("  %s\n", entry->d_name);
  closedir(dir);
}
