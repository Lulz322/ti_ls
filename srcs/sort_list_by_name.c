#include "../includes/ft_ls.h"

void				split_other_files(t_files *files)
{
	t_files	*tmp;

	if (files->next && files->next->next)
	{
		tmp = files->next->next;
		files->next->next = tmp->next;
		tmp->next = files->next;
		files->next = tmp;
	}
}

t_files		*split_head_files(t_files *files)
{
	t_files	*head;

	head = files->next;
	files->next = head->next;
	head->next = files;
	return (head);
}

static int			check_split(t_files *files)
{
	if (files && files->next)
		if (ft_strcmp(files->f_name, files->next->f_name) > 0)
			return (1);
	return (0);
}

t_files		*sort_list_by_names(t_files *files)
{
	t_files	*start;
	size_t			i;

	i = 1;
	while (i && !(i = 0))
		if (check_split(files) && ++i)
			files = split_head_files(files);
		else
		{
			start = files;
			while (start)
			{
				if (check_split(start->next) && ++i)
					split_other_files(start);
				start = start->next;
			}
		}
	return (files);
}
