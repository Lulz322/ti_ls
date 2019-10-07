/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:26:54 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:26:55 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	to_array(int i, char tmp[1024], char *flag, bool minus)
{
	char *str;

	ft_bzero(tmp, 1024);
	str = ft_itoa(i);
	ft_strcat(tmp, "%");
	if (minus == true)
		ft_strcat(tmp, "-");
	ft_strcat(tmp, str);
	ft_strcat(tmp, flag);
	free(str);
}

int		prepare_links(t_files *files, int what)
{
	t_files	*tmp;
	int		max;
	int		z;

	max = 1;
	tmp = files;
	while (tmp)
	{
		if (what == 1)
			z = nbr_len(tmp->links);
		else if (what == 4)
			z = nbr_len(tmp->real_size);
		else if (what == 2)
			z = nbr_len(tmp->minor);
		else if (what == 3)
			z = nbr_len(tmp->major);
		if (max < z)
			max = z;
		tmp = tmp->next;
	}
	return (max);
}

int		prepare_names(t_files *files, int what)
{
	t_files	*tmp;
	int		i;
	int		max;

	tmp = files;
	i = 0;
	max = 1;
	while (tmp)
	{
		if (what == 1)
			i = ft_strlen(tmp->uid);
		if (what == 2)
			i = ft_strlen(tmp->gid);
		if (what == 3)
			i = ft_strlen(tmp->time);
		if (what == 4)
			i = ft_strlen(tmp->f_name);
		if (max < i)
			max = i;
		tmp = tmp->next;
	}
	return (max);
}

void	prepare_to_print(t_files *files, int array[9])
{
	array[0] = 11;
	array[1] = prepare_links(files, 1);
	array[2] = prepare_names(files, 1);
	array[3] = prepare_names(files, 2);
	array[4] = prepare_links(files, 4);
	array[5] = 12;
	if (files && files->is_dev)
	{
		array[7] = prepare_links(files, 2);
		array[8] = prepare_links(files, 3);
	}
}
