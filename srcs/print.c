#include "../includes/ft_ls.h"

bool	print_names(int array[9], t_files *tmp, bool test)
{
	if (st.cv.flag_l)
		test = print_long_files(tmp, array, test);
	else
		test = print_tty(tmp, array);
	return (test);
}

void print_files(t_files *list, t_dirs *dirs)
{
	bool test;
	int array[7];

	test = false;
	ft_bzero(array, sizeof(array));
	array[6] = prepare_names(list, 4);
	if (list && dirs)
		print_total(dirs->total);
	test = print_names(array, list, test);
	if (!st.cv.flag_l && test == true)
		ft_printf("\n");
}

void print_total(long i)
{
	char *q;

	if(st.cv.flag_l)
	{
			if (!st.cv.flag_h)
				ft_printf("total %lld\n", i);
			else
			{
				q = printsize(i);
				ft_printf("total %s\n", q);
				free(q);
			}
	}
}