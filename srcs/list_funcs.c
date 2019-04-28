#include "../includes/ft_ls.h"

t_dirs *create_elem(char *str)
{
	t_dirs *elem;

	_ERROR_MALLOC(elem = (t_dirs *)malloc(sizeof(t_dirs)));
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
