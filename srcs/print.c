/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:28:07 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:28:08 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

bool	print_names(int array[9], t_files *tmp, bool test)
{
	if (g_gen.cv.flag_l)
		test = print_long_files(tmp, array, test);
	else
		test = print_tty(tmp, array);
	return (test);
}

void	print_files(t_files *list, t_dirs *dirs)
{
	bool	test;
	int		array[7];

	test = false;
	ft_bzero(array, sizeof(array));
	array[6] = prepare_names(list, 4);
	if (list && dirs)
		print_total(dirs->total);
	test = print_names(array, list, test);
	if (!g_gen.cv.flag_l && test == true)
		ft_printf("\n");
}

void	print_total(long i)
{
	char *q;

	if (g_gen.cv.flag_l)
	{
		if (!g_gen.cv.flag_h)
			ft_printf("total %lld\n", i);
		else
		{
			q = printsize(i);
			ft_printf("total %s\n", q);
			free(q);
		}
	}
}
