#include "../includes/ft_ls.h"

t_dirs *create_elem(char *str)
{
	t_dirs *elem;

	_ERROR_MALLOC(elem = (t_dirs *)malloc(sizeof(t_dirs)));
	ft_bzero(elem, sizeof(t_dirs));
	elem->name = ft_strdup(str);
	elem->next = NULL;
	return (elem);
}

void add_elem(t_dirs **list, char *str)
{
	t_dirs *tmp;

	tmp = NULL;
	if (!*list)
		*list = create_elem(str);
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_elem(str);
	}
}

void print_list(t_dirs *list) {
	t_dirs *tmp;
	int i;

	i = 1;
	tmp = list;
	while (tmp)
	{
		ft_printf("[%d]  %s\n", i++, tmp->name);
		tmp = tmp->next;
	}
}

void add_beetween(t_dirs **list, char *str, bool a)
{
	t_dirs *tmp;
	t_dirs *eby;
	t_dirs *save_next;
	static t_dirs *save;

	if (a == 1)
	{
		save = NULL;
		return ;
	}
	tmp = *list;
	if (save)
		while (tmp != save)
			tmp = tmp->next;
	save_next = tmp->next;
	eby = tmp;
	eby->next = create_elem(str);
	eby->next->next = save_next;
	save = eby->next;
}


void del_elem(t_dirs **list, t_dirs *elem)
{
	t_dirs *tmp;
	t_dirs *save;

	tmp = *list;
	save = tmp;
	while (tmp != elem) {
		save = tmp;
		tmp = tmp->next;
	}
	if (*list == tmp)
		*list = (*list)->next;
	save->next = tmp->next;
	free(tmp->name);
	del_files(&tmp->files);
	free(tmp);
}
