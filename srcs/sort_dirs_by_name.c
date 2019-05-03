#include "../includes/ft_ls.h"

void				split_other_dirs(t_dirs *dirs)
{
	t_dirs *tmp;

	if (dirs->next && dirs->next->next)
	{
		tmp = dirs->next->next;
		dirs->next->next = tmp->next;
		tmp->next = dirs->next;
		dirs->next = tmp;
	}
}

t_dirs *split_head_dirs(t_dirs *dirs)
{
	t_dirs *head;

	head = dirs->next;
	dirs->next = head->next;
	head->next = dirs;
	return (head);
}

static int			check_split_dirs(t_dirs *dirs)
{
	if (dirs && dirs->next)
	{
		if (!st.cv.flag_r)
		{
			if (ft_strcmp(dirs->name, dirs->next->name) > 0)
				return (1);
		}
		else
			if (-ft_strcmp(dirs->name, dirs->next->name) > 0)
				return (1);
	}
	return (0);
}

t_dirs *sort_dirs_by_names(t_dirs *dirs)
{
	t_dirs *start;
	size_t			i;

	i = 1;
	while (i && !(i = 0))
		if (check_split_dirs(dirs) && ++i)
			dirs = split_head_dirs(dirs);
		else
		{
			start = dirs;
			while (start)
			{
				if (check_split_dirs(start->next) && ++i)
					split_other_dirs(start);
				start = start->next;
			}
		}
	return (dirs);
}
