/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_some_shit_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:25:38 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:25:39 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	add_link(t_files *elem, char *way)
{
	int		len;
	char	qqq[1025];
	char	*tmp;

	len = readlink(way, qqq, 1025);
	qqq[len] = '\0';
	tmp = elem->f_name;
	elem->f_name = ft_strjoin(elem->f_name, " -> ");
	free(tmp);
	tmp = elem->f_name;
	elem->f_name = ft_strjoin(elem->f_name, qqq);
	free(tmp);
}

t_files	*create_file_name(char *str)
{
	t_files *elem;

	_ERROR_MALLOC(elem = (t_files *)malloc(sizeof(t_files)));
	ft_bzero(elem, sizeof(t_files));
	elem->f_name = ft_strdup(str);
	elem->is_perm = true;
	elem->next = NULL;
	return (elem);
}

void	add_name(t_files **list, char *str)
{
	t_files *tmp;

	tmp = NULL;
	if (!*list)
		*list = create_file_name(str);
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_file_name(str);
	}
}

void	add_file(t_files **list, char *str, struct stat *buf, char *way)
{
	t_files *tmp;

	tmp = NULL;
	if (!*list)
		*list = create_file(str, buf, way);
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_file(str, buf, way);
	}
}

void	del_file(t_files **pzdc)
{
	t_files *del_me;

	del_me = *pzdc;
	if (st.cv.flag_l)
	{
		free(del_me->UID);
		free(del_me->GID);
		free(del_me->size);
		free(del_me->time);
	}
	free(del_me->f_name);
}
