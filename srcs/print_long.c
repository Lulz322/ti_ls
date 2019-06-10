#include "../includes/ft_ls.h"

void	print_links(unsigned int i, int len)
{
	int nbr_len;
	unsigned int j;
	int c;

	j = i;
	nbr_len = 1;
	while (j /= 10)
		++nbr_len;
	c = len - nbr_len;
	while (c--)
		ft_putchar(' ');
	ft_putnbr((int)i);
	ft_putchar(' ');
}

void	print_long_format(t_files *tmp, int array[7])
{
	char str[1024];

	ft_bzero(str, sizeof(str));
	ft_putstr(tmp->flags);
	ft_putstr(" ");
	print_links(tmp->links, array[1]);
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