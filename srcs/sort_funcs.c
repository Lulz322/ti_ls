/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:39:05 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:39:07 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_dirs				*split_head_dirs(t_dirs *dirs)
{
	t_dirs *head;

	head = dirs->next;
	dirs->next = head->next;
	head->next = dirs;
	return (head);
}

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

t_files				*split_head_files(t_files *files)
{
	t_files	*head;

	head = files->next;
	files->next = head->next;
	head->next = files;
	return (head);
}
