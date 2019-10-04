/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 18:47:36 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 18:58:01 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*less_then_ten(size_t size, size_t rem)
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

static char	*fuck(size_t size, int rem, int div)
{
	char				*str;
	static const char	*sizzzzzz[] = { "B", "K", "M", "G", "T" };

	str = ft_itoa(size + rem / 1024);
	if (div <= 4 && ft_strlen(str) <= 3)
		ft_strcat(str, sizzzzzz[div]);
	return (str);
}

char		*printsize(size_t size)
{
	static const char	*sizzzzzz[] = { "B", "K", "M", "G", "T" };
	size_t				div;
	size_t				rem;
	char				*str;

	div = 0;
	rem = 0;
	while (size >= 1024 && div < (sizeof(sizzzzzz) / sizeof(*sizzzzzz)))
	{
		rem = (size % 1024);
		div++;
		size /= 1024;
	}
	if (div == 0)
		return (fuck(size, rem, div));
	if (size + rem / 1024 >= 10)
		if (rem >= 512)
			str = ft_itoa(size + rem / 1024 + 1);
		else
			str = ft_itoa(size + rem / 1024);
	else
		str = less_then_ten(size, rem);
	if (div <= 4 && ft_strlen(str) <= 3)
		ft_strcat(str, sizzzzzz[div]);
	return (str);
}
