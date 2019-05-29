#include "../includes/ft_ls.h"

void print_long_format(t_files *tmp, int array[7])
{
	char str[1024];

	ft_bzero(str, sizeof(str));
	to_array(array[0], str, "s ", false);
	ft_printf(str, tmp->flags);
	to_array(array[1], str, "lu ", false);
	ft_printf(str, tmp->links);
	print_f_name(tmp->UID, array[2]);
	ft_putstr("  ");
	print_f_name(tmp->GID, array[3]);
	ft_putstr("  ");
	print_size(array, tmp, str);
	to_array(array[5], str, "s ", false);
	ft_printf(str, tmp->time);
	check_file_flags(tmp, array);
}

bool	print_long_files(t_files *list, int array[9], bool test)
{
	t_files *tmp;

	tmp = list;
	prepare_to_print(list, array);
	while (tmp)
	{
		test = true;
		print_long_format(tmp, array);
		ft_printf("\n");
		tmp = tmp->next;
	}
	return (test);
}