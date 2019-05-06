#include "../includes/ft_ls.h"

static bool			check_split(t_files *files)
{
	if (files && files->next)
	{
		if (!st.cv.flag_r)
		{
			if (ft_strcmp(files->f_name, files->next->f_name) > 0)
				return (true);
		}
		else
			if (-ft_strcmp(files->f_name, files->next->f_name) > 0)
				return (true);
	}
	return (false);
}

static bool			is_swap(t_files *files)
{
	if (files && files->next)
	{
		if (!st.cv.flag_r)
		{
			if (files->all_time < files->next->all_time)
				return (true);
		}
		else
			if (files->all_time > files->next->all_time)
				return (true);
	}
	return (false);
}


t_files		*sort_list_by_time(t_files *files)
{
	t_files	*start;
	size_t			i;

	i = 1;
	while (i && !(i = 0))
		if (is_swap(files) && ++i)
			files = split_head_files(files);
		else
		{
			start = files;
			while (start)
			{
				if (is_swap(start->next) && ++i)
					split_other_files(start);
				start = start->next;
			}
		}
	return (files);
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
