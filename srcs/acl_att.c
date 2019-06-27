#include "../includes/ft_ls.h"

bool		check_acl(char *str)
{
	acl_t	acl;

	if ((acl = acl_get_file(str, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl);
		return (true);
	}
	else if ((acl = acl_get_file(str, ACL_TYPE_DEFAULT)))
	{
		acl_free(acl);
		return (true);
	}
	else
		return (false);
}

bool		check_ea(char *str)
{
	return ((listxattr(str, NULL, 0, XATTR_NOFOLLOW) > false ? true : false));
}

