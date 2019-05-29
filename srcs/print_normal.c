#include "../includes/ft_ls.h"

void print_f_name(char *str, int i)
{
	int len;

	len = ft_strlen(str);
	ft_putstr(str);
	while (len++ < i)
		ft_putchar(' ');
}

void check_file_flags(t_files *tmp, int array[7])
{
	char str[1024];

	to_array(array[6], str, "s", true);
	if (!tmp->is_perm || !st.cv.flag_l)
	{
		if (tmp->flags[0] == 'd')
		{
			ft_printf("MCYN(%");
			print_f_name(tmp->f_name, array[6]);
			ft_printf(" MCYN()%");
		}
		else if (ft_strequ("-rwxr-xr-x ", tmp->flags))
		{
			ft_printf("MRED(");
			print_f_name(tmp->f_name, array[6]);
			ft_printf(" MCYN()%");
		}
		else if (tmp->flags[0] == 'l')
		{
			ft_printf("MPRP(");
			print_f_name(tmp->f_name, array[6]);
			ft_printf(" MPRP()%");
		}
		else
		{
			print_f_name(tmp->f_name, array[6]);
			ft_printf(" ");
		}
	}
}

bool	print_tty(t_files *tmp, int array[9])
{
	t_files *print;

	print = tmp;
	while (print)
	{
		check_file_flags(print, array);
		print = print->next;
	}
	return true;
}