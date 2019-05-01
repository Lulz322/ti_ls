#include "../includes/ft_ls.h"

char *printsize(size_t  size)
{
    static const char *SIZES[] = { "", "K", "M", "G", "T" };
    size_t div = 0;
    size_t rem = 0;
	char *str;
	char *str2;

    while (size >= 1024 && div < (sizeof SIZES / sizeof *SIZES)) {
        rem = (size % 1024);
        div++;
        size /= 1024;
    }

	str = ft_itoa(size + rem / 1024);
	if ((float)size + (float)rem / 1024.0 <= 9.9 && div != 0l)
	{
		ft_strcat(str, ".");
		str2 = ft_itoa(rem);
		str2[1] = '\0';
		ft_strcat(str, str2);
		free(str2);
	}
	ft_strcat(str, SIZES[div]);

	return (str);
}
