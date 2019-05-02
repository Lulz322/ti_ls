#include "../includes/ft_ls.h"
#include <time.h>


char *getUser(uid_t uid)
{
    struct passwd *pws;
    pws = getpwuid(uid);
	if (pws)
        return (pws->pw_name);
	return (0);
}

char *getGroup(gid_t gid)
{
    struct group *pws;
    pws = getgrgid(gid);
	if (pws)
        return (pws->gr_name);
	return (0);
}

void mode_to_letters(int mode,char *str)
{
    strcpy(str,"----------");
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

char *pars_data(char *str)
{
	int i;
	char *qqq;
	int j;

	j = 0;
	i = 4;
	qqq = (char *)malloc(sizeof(char) * 13);
	while (i < 16)
		qqq[j++] = str[i++];
	qqq[j] = '\0';
	return (qqq);

}

t_files *create_file(char *str, struct stat *buff, char *way)
{
	t_files *elem;

	_ERROR_MALLOC(elem = (t_files *)malloc(sizeof(t_files)));
	ft_bzero(elem, sizeof(t_files));
	elem->f_name = ft_strdup(str);
	elem->is_dir = is_dir(way);
	if (st.cv.flag_l)
	{
		mode_to_letters(buff->st_mode, elem->flags);
		elem->links = buff->st_nlink;
		elem->UID = getUser(buff->st_uid);
		elem->GID = getGroup(buff->st_gid);
		elem->all_time = buff->st_mtim;
		elem->time = pars_data(ctime(&elem->all_time.tv_sec));
		elem->size = printsize(buff->st_size);
	}
	elem->next = NULL;
	return (elem);
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

void print_files(t_files *list) {
	t_files *tmp;

	tmp = list;
	while (tmp)
	{
		if (st.cv.flag_l)
			printf("%s %3lu %s %s %4s %s %s\n",
			tmp->flags, tmp->links ,tmp->UID, tmp->GID, tmp->size,
			tmp->time, tmp->f_name);
		else
			if (tmp->is_dir)
				ft_printf("MBLU(%s)  ", tmp->f_name);
			else
				ft_printf("%s  ", tmp->f_name);
		tmp = tmp->next;
	}
	printf("\n");
}
