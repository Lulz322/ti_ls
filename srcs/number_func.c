#include "../includes/ft_ls.h"

char *less_then_ten(size_t size, size_t rem)
{
	char *str;
	char *tmp;
	char *tmp2;

	tmp = ft_itoa(rem);
	if (tmp[1] && (tmp[1] >= '5' && tmp[1] <= '9'))
	{
		if (tmp[0] != '9')
			tmp[0] = tmp[0] + 1;
		else
		{
			tmp[0] = '0';
			size++;
		}
	}
	tmp[1] = '\0';
	tmp2 = ft_itoa(size);
	str = ft_memalloc(ft_strlen(tmp2) + 5);
	ft_strcat(str, tmp2);
	ft_strcat(str, ".");
	ft_strcat(str, tmp);
	free(tmp);
	free(tmp2);
	return (str);
}


char *printsize(size_t  size)
{
	static const char *SIZES[] = { "B", "K", "M", "G", "T" };
	size_t div = 0;
	size_t rem = 0;
	char *str;

	while (size >= 1024 && div < (sizeof SIZES / sizeof *SIZES))
	{
		rem = (size % 1024);
		div++;
		size /= 1024;
	}
	if (div == 0)
	{
		str = ft_itoa(size + rem / 1024);
		if (div <= 4 && ft_strlen(str) <= 3)
			ft_strcat(str, SIZES[div]);
		return (str);
	}
	if (size + rem / 1024 >= 10)
		if (rem >= 512)
			str = ft_itoa(size + rem / 1024 + 1);
		else
			str = ft_itoa(size + rem / 1024);
	else
		str = less_then_ten(size, rem);
	if (div <= 4 && ft_strlen(str) <= 3)
		ft_strcat(str, SIZES[div]);
	return (str);
}
