#include "../includes/ft_ls.h"


char *getUser(uid_t uid)
{
    struct passwd *pws;
    pws = getpwuid(uid);
        return (pws->pw_name);
}

char *getGroup(gid_t gid)
{
    struct group *pws;
    pws = getgrgid(gid);
        return (pws->gr_name);
}

void mode_to_letters(int mode,char *str)
{
    strcpy(str,"----------");
    if(S_ISDIR(mode))str[0]='d';
    if(S_ISCHR(mode))str[0]='c';
    if(S_ISBLK(mode))str[0]='b';
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

t_files *create_file(char *str, struct stat *buff)
{
	t_files *elem;

	_ERROR_MALLOC(elem = (t_files *)malloc(sizeof(t_files)));
	elem->f_name = ft_strdup(str);
	mode_to_letters(buff->st_mode, elem->flags);
	elem->links = buff->st_nlink;
	elem->UID = getUser(buff->st_uid);
	elem->GID = getGroup(buff->st_gid);
	bytes(buff->st_size, elem->size);
	//elem->size = buff->st_size;
	elem->next = NULL;
	return (elem);
}

void add_file(t_files **list, char *str, struct stat *buf)
{
	t_files *tmp;

	tmp = NULL;
	if (!*list)
		*list = create_file(str, buf);
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_file(str, buf);
	}
}

void print_files(t_files *list) {
	t_files *tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s %2lu %s %s %4s %s\n",
		tmp->flags, tmp->links ,tmp->UID, tmp->GID, tmp->size, tmp->f_name);
		tmp = tmp->next;
	}
}
