/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_some_shit_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:25:43 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:25:44 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	del_files(t_files **files)
{
	t_files *del_me;
	t_files *tmp;

	tmp = *files;
	while (tmp)
	{
		del_me = tmp;
		del_file(&del_me);
		tmp = tmp->next;
		free(del_me);
	}
}

int		nbr_len(unsigned int nbr)
{
	int len;

	len = 0;
	while (nbr >= 1)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

void	print_size_first(t_files *tmp, int array[9], char str[1024])
{
	int		i;

	i = 1;
	if (tmp->major != 0)
	{
		to_array(array[8], str, "lu, ", false);
		ft_printf(str, tmp->major);
	}
	else
	{
		while (++i <= array[8] + 3)
			ft_putchar(' ');
	}
	to_array(array[7], str, "lu ", false);
	ft_printf(str, tmp->minor);
}

void	print_size_second(t_files *tmp, int array[9], char str[1024])
{
	char *q;

	if (!st.cv.flag_h)
	{
		to_array(array[4], str, "lu ", false);
		ft_printf(str, tmp->real_size);
	}
	else
	{
		q = printsize(tmp->real_size);
		ft_printf("%4s ", q);
		free(q);
	}
}

void	print_size(int array[9], t_files *tmp, char str[1024])
{
	if (tmp->is_dev)
		print_size_first(tmp, array, str);
	else
		print_size_second(tmp, array, str);
}
