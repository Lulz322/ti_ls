#include "../includes/ft_ls.h"
#include <time.h>


char *getUser(uid_t uid)
{
    struct passwd *pws;
    pws = getpwuid(uid);
	if (pws)
        return (pws->pw_name);
	return ("?");
}

char *getGroup(gid_t gid)
{
    struct group *pws;
    pws = getgrgid(gid);
	if (pws)
        return (pws->gr_name);
	return ("?");
}

void mode_to_letters(int mode,char *str)
{
    strcpy(str,"---------- ");
    if(S_ISDIR(mode))str[0]='d';
    if(S_ISCHR(mode))str[0]='c';
    if(S_ISBLK(mode))str[0]='b';
	if(S_ISLNK(mode))str[0]='l';
    if(mode & S_IRUSR)str[1]='r';
    if(mode & S_IWUSR)str[2]='w';
    if(mode & S_IXUSR)str[3]='x';
    if(mode & S_IRGRP)str[4]='r';
    if(mode & S_IWGRP)str[5]='w';
    if(mode & S_IXGRP)str[6]='x';
    if(mode & S_IROTH)str[7]='r';
    if(mode & S_IWOTH)str[8]='w';
    if(mode & S_IXOTH)str[9]='x';
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	i;

	i = 0;
	res = ft_strnew(n);
	if (res)
		while (i < n)
		{
			res[i] = s1[i];
			i++;
		}
	return (res);
}

char  *privet(char *str, long all_time)
{
	long t;
	long half_year;
	char *jopa;
	char *tmp;
	char *qqq;

	t = (long)time(NULL);
	half_year = 15768000;
	if (t - all_time > half_year)
	{
		qqq = ft_strndup(&str[4], 7);
		jopa = ft_strndup(&str[20], 4);
		tmp = qqq;
		qqq = ft_strjoin(qqq, " ");
		free(tmp);
		tmp = qqq;
		qqq = ft_strjoin(qqq, jopa);
		free(tmp);
		free(jopa);
	}
	else
	{
		qqq = ft_strndup(&str[4], 6);
		jopa = ft_strndup(&str[10], 6);
		tmp = qqq;
		qqq = ft_strjoin(qqq, jopa);
		free(tmp);
		free(jopa);
	}
	return(qqq);
}

char *pars_data(char *str, long all_time)
{
	char *qqq;
	qqq = privet(str, all_time);

	return (qqq);
}

void add_link(t_files *elem, char *way)
{
	int len;
	char qqq[1025];
	char *tmp;

	len = readlink(way, qqq, 1025);
	qqq[len] = '\0';
	tmp = elem->f_name;
	elem->f_name = ft_strjoin(elem->f_name, " -> ");
	free(tmp);
	tmp = elem->f_name;
	elem->f_name = ft_strjoin(elem->f_name, qqq);
	free(tmp);
}

t_files *create_file(char *str, struct stat *buff, char *way)
{
	t_files *elem;

	_ERROR_MALLOC(elem = (t_files *)malloc(sizeof(t_files)));
	ft_bzero(elem, sizeof(t_files));
	elem->f_name = ft_strdup(str);
	elem->is_dir = is_dir(way);
	mode_to_letters(buff->st_mode, elem->flags);
	if (st.cv.flag_l)
	{
		if (elem->flags[0] == 'l')
			add_link(elem, way);
		elem->links = buff->st_nlink;
		elem->UID = ft_strdup(getUser(buff->st_uid));
		elem->GID = ft_strdup(getGroup(buff->st_gid));
		elem->all_time = (long)buff->st_mtime;
		elem->time = pars_data(ctime(&elem->all_time), elem->all_time);
		elem->size = printsize(buff->st_size);
		elem->real_size = (long long)buff->st_size;
		elem->major = (long)major(buff->st_rdev);
		elem->major = (long)minor(buff->st_rdev);
	}
	elem->next = NULL;
	return (elem);
}

t_files *create_file_name(char *str)
{
	t_files *elem;

	_ERROR_MALLOC(elem = (t_files *)malloc(sizeof(t_files)));
	ft_bzero(elem, sizeof(t_files));
	elem->f_name = ft_strdup(str);
	elem->is_perm = true;
	elem->next = NULL;
	return (elem);
}

void add_name(t_files **list, char *str)
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

void add_file(t_files **list, char *str, struct stat *buf, char *way)
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

void check_file_flags(t_files *tmp)
{
	if (!tmp->is_perm || !st.cv.flag_l)
	{
		if (tmp->flags[0] == 'd')
			ft_printf("MCYN(%s)  ", tmp->f_name);
		else if (ft_strequ("-rwxr-xr-x", tmp->flags))
			ft_printf("MRED(%s) ", tmp->f_name);
		else if (tmp->flags[0] == 'l')
			ft_printf("MPRP(%s) ", tmp->f_name);
		else
			ft_printf("%s ", tmp->f_name);
	}
}

void del_file(t_files **pzdc)
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

void del_files(t_files **files)
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

void print_files(t_files *list, t_dirs *dirs) {
	t_files *tmp;
	char *q;

	tmp = list;
	if(st.cv.flag_l && !tmp->is_perm)
	{
			q = printsize(dirs->total);
			ft_printf("total %s\n", q);
			free(q);
	}
	while (tmp)
	{
		if (st.cv.flag_l && !tmp->is_perm)
		{
			ft_printf("%s ", tmp->flags);
			ft_printf("%15lu ", tmp->links);
			ft_printf("%15s  ", tmp->UID);
			ft_printf("%15s ", tmp->GID);
			if (st.cv.flag_h)
				ft_printf("%15s ", tmp->size);
			else
				ft_printf("%18lld ", tmp->real_size);
			ft_printf("%15s ", tmp->time);
		}
		check_file_flags(tmp);
		if (st.cv.flag_l && !tmp->is_perm)
			ft_printf("\n");
		tmp = tmp->next;
	}
	if (!st.cv.flag_l)
		ft_printf("\n");
}
